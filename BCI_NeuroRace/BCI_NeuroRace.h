#define UNUSED(arg) (void)arg

/* GPIO and SPI pins. */
#define START RPI_V2_GPIO_P1_29  // START PIN
#define DRDY RPI_V2_GPIO_P1_31   // DATA READY PIN
#define RESET RPI_V2_GPIO_P1_33  // RESET PIN
#define CLKSEL RPI_V2_GPIO_P1_35 // CLOCK SELECTION PIN
#define PWDN RPI_V2_GPIO_P1_37   // POWER DOWN PIN

/* Time constants. */
#define INIT_RESET_DELAY 100
#define POST_INIT_RESET_DELAY 5
#define POWERUP_DELAY 2
#define INIT_DELAY 5
#define RESET_DELAY 1
#define POST_RESET_DELAY 5

/* Thread scheduling settings. */
#define SAMPLER_POLICY SCHED_FIFO
#define WORKERS_POLICY SCHED_FIFO
#define CONTROLLER_POLICY SCHED_RR
#define CALIBRATOR_POLICY SCHED_RR
#define SCHED_LEVEL 99
#define MAIN_NICE -20
#define SAMPLER_CORE 0
#define FFT_O1_CORE 2
#define FFT_O2_CORE 3
#define CONTROLLER_CORE 1
#define CALIBRATOR_CORE 1

/* Sampling parameters. */
#define FILTER_RUNS 1
#define NSAMPLES 8000
#define FFTSAMPLES ((NSAMPLES / 2) + 1)
#define ENOB 19
#define CHANNELS 2
#define MAXCHANNELS 8
#define BINS 6
#define CALIBRATION_RUNS 7
#define CALIBRATION_SECONDS 3
