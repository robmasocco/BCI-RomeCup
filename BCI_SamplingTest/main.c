#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>
#include <pthread.h>
#include <semaphore.h>
#include <bcm2835.h>

#include "BCI_SamplingTest.h"

/* Thread metadata. */
pthread_attr_t samplerData, printerData;
pthread_attr_t fftWorkersData[CHANNELS];
struct sched_param samplerSched, printerSched;
struct sched_param fftWorkersSched[CHANNELS];
cpu_set_t samplerSet, printerSet;
cpu_set_t fftWorkersSets[CHANNELS];
int workersCores[CHANNELS] = {FFT_O1_CORE, FFT_O2_CORE};
pthread_t initializerTID, samplerTID;
sem_t fftLocks[CHANNELS][2];
sem_t printerLocks[CHANNELS][2];
void *initializerExCode;

extern void *boardInitializer(void *arg);
extern void *sampler(void *arg);

int main(void) {
    // Set main thread niceness.
    if (setpriority(PRIO_PROCESS, 0, MAIN_NICE) < 0) {
        fprintf(stderr, "ERROR: Failed to set main thread niceness.\n");
        exit(EXIT_FAILURE);
    }
    printf("Main thread niceness set.\n");
    // Initialize semaphores.
    for (int i = 0; i < CHANNELS; i++) {
        sem_init(&(fftLocks[i][0]), 0, 0);
        sem_init(&(fftLocks[i][1]), 0, 0);
    }
    for (int i = 0; i < CHANNELS; i++) {
        sem_init(&(printerLocks[i][0]), 0, 1);
        sem_init(&(printerLocks[i][1]), 0, 0);
    }
    // Initialize scheduling levels.
    samplerSched.sched_priority = SCHED_LEVEL;
    printerSched.sched_priority = SCHED_LEVEL;
    for (int i = 0; i < CHANNELS; i++) {
        fftWorkersSched[i].sched_priority = SCHED_LEVEL;
    }
    // Initialize thread attributes.
    pthread_attr_init(&samplerData);
    pthread_attr_init(&printerData);
    for (int i = 0; i < CHANNELS; i++) {
        pthread_attr_init(&(fftWorkersData[i]));
    }
    // Set scheduling values inheritance.
    pthread_attr_setinheritsched(&samplerData, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setinheritsched(&printerData, PTHREAD_EXPLICIT_SCHED);
    for (int i = 0; i < CHANNELS; i++) {
        pthread_attr_setinheritsched(&(fftWorkersData[i]),
                PTHREAD_EXPLICIT_SCHED);
    };
    // Set scheduling policies.
    pthread_attr_setschedpolicy(&samplerData, SAMPLER_POLICY);
    pthread_attr_setschedpolicy(&printerData, PRINTER_POLICY);
    for (int i = 0; i < CHANNELS; i++) {
        pthread_attr_setschedpolicy(&(fftWorkersData[i]), WORKERS_POLICY);
    };
    // Set thread scheduling parameters.
    pthread_attr_setschedparam(&samplerData, &samplerSched);
    pthread_attr_setschedparam(&printerData, &printerSched);
    for (int i = 0; i < CHANNELS; i++) {
        pthread_attr_setschedparam(&(fftWorkersData[i]), &(fftWorkersSched[i]));
    };
    // Initialize CPU affinity masks.
    CPU_ZERO(&samplerSet);
    CPU_ZERO(&printerSet);
    for (int i = 0; i < CHANNELS; i++)
        CPU_ZERO(&(fftWorkersSets[i]));
    CPU_SET(SAMPLER_CORE, &samplerSet);
    CPU_SET(PRINTER_CORE, &printerSet);
    for (int i = 0; i < CHANNELS; i++)
        CPU_SET(workersCores[i], &(fftWorkersSets[i]));
    // Set CPU affinity masks.
    pthread_attr_setaffinity_np(&samplerData, sizeof(cpu_set_t), &samplerSet);
    pthread_attr_setaffinity_np(&printerData, sizeof(cpu_set_t), &printerSet);
    for (int i = 0; i < CHANNELS; i++)
        pthread_attr_setaffinity_np(&(fftWorkersData[i]), sizeof(cpu_set_t),
                &(fftWorkersSets[i]));
    // Initialize bcm2835 library.
    if (!bcm2835_init()) {
        fprintf(stderr, "ERROR: Failed to initialize bcm2835 library.\n");
        exit(EXIT_FAILURE);
    }
    printf("bcm2835 library initialized.\n");
    // Set GPIO pins.
    bcm2835_gpio_fsel(START, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RESET, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(CLKSEL, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(DRDY, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(DRDY, BCM2835_GPIO_PUD_UP);
    printf("GPIO pins set.\n");
    // Set clock source and conversions pin.
    bcm2835_delay(POWERUP_DELAY);
    bcm2835_gpio_write(CLKSEL, LOW);
    bcm2835_delay(POWERUP_DELAY);
    bcm2835_gpio_write(START, LOW);
    bcm2835_gpio_write(RESET, HIGH);
    bcm2835_delay(INIT_DELAY);
    printf("GPIO pins initialized.\n");
    // Reset digital logic.
    bcm2835_gpio_write(RESET, LOW);
    bcm2835_delay(RESET_DELAY);
    bcm2835_gpio_write(RESET, HIGH);
    bcm2835_delay(POST_RESET_DELAY);
    printf("Digital logic reset.\n");
    // Spawn board initializer thread.
    printf("Spawning initializer thread...\n");
    if (pthread_create(&initializerTID, &samplerData, boardInitializer, NULL)) {
        fprintf(stderr, "ERROR: Failed to spawn initializer thread.\n");
        bcm2835_close();
        exit(EXIT_FAILURE);
    }
    if (pthread_join(initializerTID, &initializerExCode)) {
        fprintf(stderr, "ERROR: Failed to join initializer thread.\n");
        bcm2835_close();
        exit(EXIT_FAILURE);
    }
    if (initializerExCode == (void *)EXIT_FAILURE) {
        fprintf(stderr, "ERROR: Failed to initialize board.\n");
        bcm2835_close();
        exit(EXIT_FAILURE);
    }
    // Spawn sampler thread.
    if (pthread_create(&samplerTID, &samplerData, sampler, NULL)) {
        fprintf(stderr, "ERROR: Failed to spawn sampler thread.\n");
        bcm2835_close();
        exit(EXIT_FAILURE);
    }
    if (pthread_join(samplerTID, NULL)) {
        fprintf(stderr, "ERROR: Failed to join sampler thread.\n");
        bcm2835_close();
        exit(EXIT_FAILURE);
    }
    // Close everything.
    bcm2835_gpio_set_pud(DRDY, BCM2835_GPIO_PUD_OFF);
    if (!bcm2835_close()) {
        fprintf(stderr, "ERROR: Failed to close bcm2835 library.\n");
        exit(EXIT_FAILURE);
    }
    pthread_attr_destroy(&samplerData);
    pthread_attr_destroy(&printerData);
    for (int i = 0; i < CHANNELS; i++) {
        pthread_attr_destroy(&(fftWorkersData[i]));
        sem_destroy(&(fftLocks[i][0]));
        sem_destroy(&(fftLocks[i][1]));
        sem_destroy(&(printerLocks[i][0]));
        sem_destroy(&(printerLocks[i][1]));
    }
    printf("All done!\n");
    exit(EXIT_SUCCESS);
}
