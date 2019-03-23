#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <complex.h>
#include <fftw3.h>
#include <bcm2835.h>

#include "BCI_SamplingTest.h"
#include "SPI_Definitions.h"

pthread_t printerTID;
pthread_t workersTIDs[CHANNELS];

extern pthread_attr_t printerData;
extern pthread_attr_t fftWorkersData[CHANNELS];

extern sem_t fftLocks[CHANNELS][2];

extern void *fftWorker(void *index);
extern void *printer(void *arg);

char readDataCmd[] = {RDATA, NOP, NOP, NOP,
                      NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP,
                      NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP,
                      NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP};
char readData[sizeof readDataCmd];

double *fftSamples[CHANNELS];
unsigned char tempSamples[CHANNELS][NSAMPLES][3];

fftw_plan plans[CHANNELS];
fftw_complex *fftValues[CHANNELS];

void *sampler(void *arg) {
    UNUSED(arg);
    // Prepare for FFT.
    for (int i = 0; i < CHANNELS; i++) {
        fftSamples[i] = fftw_alloc_real(NSAMPLES);
        fftValues[i] = fftw_alloc_complex(FFTSAMPLES);
        plans[i] = fftw_plan_dft_r2c_1d(NSAMPLES, fftSamples[i], fftValues[i],
                                        FFTW_MEASURE);
    }
    // Spawn printer thread.
    if (pthread_create(&printerTID, &printerData, printer, NULL)) {
        fprintf(stderr, "ERROR: Failed to printer thread.\n");
        pthread_exit(NULL);
    }
    // Spawn FFT workers threads.
    for (int i = 0; i < CHANNELS; i++) {
        if (pthread_create(&(workersTIDs[i]), &(fftWorkersData[i]),
                           fftWorker, (void *)i)) {
            fprintf(stderr, "ERROR: Failed to spawn #%d FFT worker thread.\n",
                    i + 1);
            pthread_exit(NULL);
        }
    }
    // Open SPI interface at high frequency and configure it.
    if (!bcm2835_spi_begin()) {
        fprintf(stderr, "ERROR: Failed to open SPI interface.\n");
        pthread_exit(NULL);
    }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE1);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_32);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
    printf("SPI interface opened for sampling.\n");
    // Do the sampling test.
    printf("Press ENTER to start the sampling test "
           "(will do %d runs)...", ACQUISITIONS);
    getchar();
    // Start conversions (SOC).
    bcm2835_gpio_write(START, HIGH);
    // Wait for ADCs to settle and ignore first two samples.
    while (bcm2835_gpio_lev(DRDY) != LOW);
    while (bcm2835_gpio_lev(DRDY) != HIGH);
    // Acquire one set of samples to set up the filter.
    /*for (int i = 0; i < NSAMPLES; i++) {
        // Wait for falling edge on DRDY (EOC).
        while (bcm2835_gpio_lev(DRDY) != LOW);
        // Read data.
        bcm2835_spi_transfernb(readDataCmd, readData, sizeof readDataCmd);
        // Copy samples.
        for (int t = 0; t < CHANNELS; t++)
            memcpy(tempSamples[t][i], readData + 4 + (t * 3), 3);
        // Wait for next rising edge on EOC.
        while (bcm2835_gpio_lev(DRDY) != HIGH);
    }
    // Notify workers.
    for (int i = 0; i < CHANNELS; i++)
        sem_post(&(fftLocks[i][0]));
    // Wait for data acquisition by workers.
    for (int i = 0; i < CHANNELS; i++)
        sem_wait(&(fftLocks[i][1]));
    printf("Channel filters ready.\n");*/
    // Do the acquisitions.
    for (int k = 0; k < ACQUISITIONS; k++) {
        for (int i = 0; i < NSAMPLES; i++) {
            // Wait for falling edge on DRDY (EOC).
            while (bcm2835_gpio_lev(DRDY) != LOW);
            // Read data.
            bcm2835_spi_transfernb(readDataCmd, readData, sizeof readDataCmd);
            // Copy samples.
            for (int t = 0; t < CHANNELS; t++)
                memcpy(tempSamples[t][i], readData + 4 + (t * 3), 3);
            // Wait for next rising edge on EOC.
            while (bcm2835_gpio_lev(DRDY) != HIGH);
        }
        // Notify workers.
        for (int i = 0; i < CHANNELS; i++)
            sem_post(&(fftLocks[i][0]));
        // Wait for data acquisition by workers.
        for (int i = 0; i < CHANNELS; i++)
            sem_wait(&(fftLocks[i][1]));
    }
    // Stop conversions.
    bcm2835_gpio_write(START, LOW);
    // Close SPI interface.
    bcm2835_spi_end();
    pthread_join(printerTID, NULL);
    for (int i = 0; i < CHANNELS; i++) {
        pthread_join(workersTIDs[i], NULL);
        fftw_destroy_plan(plans[i]);
        fftw_free(fftSamples[i]);
        fftw_free(fftValues[i]);
    }
    pthread_exit(NULL);
}
