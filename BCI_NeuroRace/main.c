#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

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

/* Main thread. Bootstraps the application. */
int main() {
    printf("Hello, World!\n");
    return 0;
}