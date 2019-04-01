#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <complex.h>
#include <fftw3.h>
#include <bcm2835.h>

#include "BCI_NeuroSerial.h"
#include "SPI_Definitions.h"

extern pid_t procPID;

pthread_t controllerTID;
pthread_t workersTIDs[CHANNELS];

extern pthread_attr_t controllerData;
extern pthread_attr_t fftWorkersData[CHANNELS];

extern sem_t fftLocks[CHANNELS][2];
extern sem_t startSampling;

extern sigset_t workerSet;

extern __thread void (*closeRoutine)(void);

/* Threads spawned by sampler. */
void *fftWorker(void *index);
void *controller(void *arg);

/* SPI commands needed for sampling. */
char readDataCmd[] = {RDATA, NOP, NOP, NOP,
                      NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP,
                      NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP,
                      NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP};
char readData[sizeof readDataCmd];

/* FFT data. */
double *fftSamples[CHANNELS];
unsigned char tempSamples[CHANNELS][NSAMPLES][3];

fftw_plan plans[CHANNELS];
fftw_complex *fftValues[CHANNELS];

/* Functions in this file. */
void *sampler(void *arg);
void samplerTermination(void);

/* Thread that samples data with the TI board. */
void *sampler(void *arg) {
    UNUSED(arg);
    closeRoutine = samplerTermination;
    pthread_sigmask(SIG_SETMASK, &workerSet, NULL);
    // Prepare for FFT.
    for (int i = 0; i < CHANNELS; i++) {
        fftSamples[i] = fftw_alloc_real(NSAMPLES);
        fftValues[i] = fftw_alloc_complex(FFTSAMPLES);
        plans[i] = fftw_plan_dft_r2c_1d(NSAMPLES, fftSamples[i], fftValues[i],
                                        FFTW_MEASURE);
    }
    // Spawn FFT workers threads.
    for (int i = 0; i < CHANNELS; i++) {
        if (pthread_create(&(workersTIDs[i]), &(fftWorkersData[i]),
                           fftWorker, (void *)i)) {
            fprintf(stderr, "ERROR: Failed to spawn #%d FFT worker thread.\n",
                    i + 1);
            kill(procPID, SIGTERM);
            pthread_exit(NULL);
        }
    }
    // Open SPI interface at high frequency and configure it.
    if (!bcm2835_spi_begin()) {
        fprintf(stderr, "ERROR: Failed to open SPI interface.\n");
        kill(procPID, SIGTERM);
        pthread_exit(NULL);
    }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE1);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_32);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
    printf("SPI interface opened for sampling.\n");
    // Spawn controller thread.
    if (pthread_create(&controllerTID, &controllerData, controller, NULL)) {
        fprintf(stderr, "ERROR: Failed to spawn controller thread.\n");
        kill(procPID, SIGTERM);
        pthread_exit(NULL);
    }
    // Wait for sampling start signal.
    sem_wait(&startSampling);
    printf("Sampling started.\n");
    // Start conversions (SOC).
    bcm2835_gpio_write(START, HIGH);
    // Wait for ADCs to settle and ignore first two samples.
    while (bcm2835_gpio_lev(DRDY) != LOW);
    while (bcm2835_gpio_lev(DRDY) != HIGH);
    // Infinite loop of sampling.
    for (;;) {
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
}

/* Termination routine for sampler thread. */
void samplerTermination(void) {
    // Stop conversions.
    bcm2835_gpio_write(START, LOW);
    // Close SPI interface.
    bcm2835_spi_end();
    // Kill FFT worker threads.
    for (int i = 0; i < CHANNELS; i++)
        pthread_kill(workersTIDs[i], SIGUSR1);
    // Kill controller thread.
    pthread_kill(controllerTID, SIGUSR1);
    // Join with worker threads and destroy FFT data.
    for (int i = 0; i < CHANNELS; i++) {
        pthread_join(workersTIDs[i], NULL);
        fftw_destroy_plan(plans[i]);
        fftw_free(fftSamples[i]);
        fftw_free(fftValues[i]);
    }
    // Join with controller thread.
    pthread_join(controllerTID, NULL);
    pthread_exit(NULL);
}
