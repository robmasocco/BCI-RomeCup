#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include <bcm2835.h>

#include "BCI_NeuroRace.h"
// TODO Cut out unnecessary libraries.

#define UNUSED(arg) (void)arg

extern pthread_t samplerTID;

/* Thread-specific signal handler. */
__thread void(*closeRoutine)(void) = NULL;

/* Program termination procedure, run by main thread. */
void terminate(int sig) {
    UNUSED(sig);
    // Kill all threads by signaling the sampler.
    pthread_kill(samplerTID, SIGUSR1);
    // Wait for sampler thread to join (it's the last that'll close).
    if (pthread_join(samplerTID, NULL)) {
        fprintf(stderr, "ERROR: Failed to join sampler thread.\n");
        bcm2835_close();
        exit(EXIT_FAILURE);
    }
    // Now the rest of the main thread will be executed (only the termination
    // procedure).
}

/* Worker threads termination procedure.
 * Only invokes thread-specific routines.
 */
void closeThread(int sig) {
    UNUSED(sig);
    closeRoutine();
}
