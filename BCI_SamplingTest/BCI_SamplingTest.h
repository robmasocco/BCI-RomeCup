#include <sched.h>

#define UNUSED(arg) (void)arg

/* GPIO and SPI pins. */
#define START RPI_V2_GPIO_P1_29  // START PIN
#define DRDY RPI_V2_GPIO_P1_31   // DATA READY PIN
#define RESET RPI_V2_GPIO_P1_33  // RESET PIN
#define CLKSEL RPI_V2_GPIO_P1_35 // CLOCK SELECTION PIN

/* Time constants. */
#define POWERUP_DELAY 2
#define INIT_DELAY 5
#define RESET_DELAY 1
#define POST_RESET_DELAY 5

/* Thread scheduling settings. */
#define SAMPLER_POLICY SCHED_FIFO
#define WORKERS_POLICY SCHED_FIFO
#define PRINTER_POLICY SCHED_RR
#define SCHED_LEVEL 99
#define MAIN_NICE -20
#define SAMPLER_CORE 0
#define FFT_O1_CORE 2
#define FFT_O2_CORE 3
#define PRINTER_CORE 1

/* Sampling parameters. */
#define NSAMPLES 4000
#define FFTSAMPLES ((NSAMPLES / 2) + 1)
#define ACQUISITIONS 30
#define ENOB 19
#define CHANNELS 2
#define MAXCHANNELS 8
