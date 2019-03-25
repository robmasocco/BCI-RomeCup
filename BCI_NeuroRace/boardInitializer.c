#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <bcm2835.h>

#include "SPI_Definitions.h"
#include "BCI_NeuroRace.h"

/* SPI commands needed for board setup. */
char channelsAddrs[] = {CH1SET_ADDR, CH2SET_ADDR, CH3SET_ADDR, CH4SET_ADDR,
                        CH5SET_ADDR, CH6SET_ADDR, CH7SET_ADDR, CH8SET_ADDR};

char config1Settings[] = {WREG | CONFIG1_ADDR, WREG_NUM, CONFIG1_SETS};
char config3Settings[] = {WREG | CONFIG3_ADDR, WREG_NUM, CONFIG3_SETS};
char config4Settings[] = {WREG | CONFIG4_ADDR, WREG_NUM, CONFIG4_SETS};
char misc1Settings[]   = {WREG | MISC1_ADDR,   WREG_NUM, MISC1_SETS  };

char settingsCheck[]   = {RREG | CONFIG1_ADDR, RREG_VAL,
                          NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP,
                          NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP,
                          NOP, NOP, NOP, NOP, NOP, NOP, NOP};

char settingsChOut[sizeof settingsCheck];

/* Thread that sets up the board for sampling. */
void *boardInitializer(void *arg) {
    UNUSED(arg);
    // Open and set SPI interface.
    if (!bcm2835_spi_begin()) {
        fprintf(stderr, "ERROR: Failed to open SPI interface.\n");
        pthread_exit((void *)EXIT_FAILURE);
    }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE1);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
    printf("SPI interface opened for board initialization.\n");
    // Stop continuous conversions.
    bcm2835_spi_transfer(SDATAC);
    bcm2835_delay(SDATAC_DELAY);
    printf("Continuous conversions stopped.\n");
    // Set CONFIG3 register.
    bcm2835_spi_transfern(config3Settings, sizeof config3Settings);
    printf("CONFIG3 register set.\n");
    bcm2835_delay(PD_REFBUF_DELAY);
    // Set CONFIG1 register.
    bcm2835_spi_transfern(config1Settings, sizeof config1Settings);
    printf("CONFIG1 register set.\n");
    // Set CONFIG4 register.
    bcm2835_spi_transfern(config4Settings, sizeof config4Settings);
    printf("CONFIG4 register set.\n");
    // Set MISC1 register.
    bcm2835_spi_transfern(misc1Settings, sizeof misc1Settings);
    printf("MISC1 register set.\n");
    // Set sampling channels.
    for (int i = 0; i < CHANNELS; i++) {
        char chEn[] = {WREG | channelsAddrs[i], WREG_NUM, CHnSET_EN};
        bcm2835_spi_transfern(chEn, sizeof chEn);
        printf("Enabled channel %d for sampling.\n", i + 1);
    }
    // Disable unused channels.
    for (int j = CHANNELS; j < MAXCHANNELS; j++) {
        char chDis[] = {WREG | channelsAddrs[j], WREG_NUM, CHnSET_DIS};
        bcm2835_spi_transfern(chDis, sizeof chDis);
        printf("Disabled channel %d.\n", j + 1);
    }
    // Validate settings reading back registers.
    bcm2835_spi_transfernb(settingsCheck, settingsChOut,
                           sizeof settingsCheck);
    if ((settingsChOut[2]  != CONFIG1_SETS) ||  // Check CONFIG 1.
        (settingsChOut[4]  != CONFIG3_SETS) ||  // Check CONFIG 3.
        (settingsChOut[6]  != CHnSET_EN)    ||  // Check Channel 1.
        (settingsChOut[7]  != CHnSET_EN)    ||  // Check Channel 2.
        (settingsChOut[8]  != CHnSET_DIS)   ||  // Check Channel 3.
        (settingsChOut[9]  != CHnSET_DIS)   ||  // Check Channel 4.
        (settingsChOut[10] != CHnSET_DIS)   ||  // Check Channel 5.
        (settingsChOut[11] != CHnSET_DIS)   ||  // Check Channel 6.
        (settingsChOut[12] != CHnSET_DIS)   ||  // Check Channel 7.
        (settingsChOut[13] != CHnSET_DIS)   ||  // Check Channel 8.
        (settingsChOut[22] != MISC1_SETS)   ||  // Check MISC1.
        (settingsChOut[24] != CONFIG4_SETS) ){  // Check CONFIG4.
        fprintf(stderr, "ERROR: Failed to initialize registers.\n");
        bcm2835_spi_end();
        pthread_exit((void *)EXIT_FAILURE);
    } else printf("Registers successfully initialized.\n");
    bcm2835_spi_end();
    pthread_exit((void *)EXIT_SUCCESS);
}
