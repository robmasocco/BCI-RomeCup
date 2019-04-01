/* Registers's addresses. */
#define CONFIG1_ADDR (char)0x01
#define CONFIG3_ADDR (char)0x03
#define CONFIG4_ADDR (char)0x17
#define MISC1_ADDR   (char)0x15
#define CH1SET_ADDR  (char)0x05
#define CH2SET_ADDR  (char)0x06
#define CH3SET_ADDR  (char)0x07
#define CH4SET_ADDR  (char)0x08
#define CH5SET_ADDR  (char)0x09
#define CH6SET_ADDR  (char)0x0A
#define CH7SET_ADDR  (char)0x0B
#define CH8SET_ADDR  (char)0x0C

/* Commands. */
#define SDATAC   (char)0x11       // Stop ADC conversions.
#define WREG     (char)0x40       // Write register (to be OR'd with address).
#define WREG_NUM (char)0x00       // Number of registers to write - 1.
#define RREG     (char)0x20       // Read register (to be OR'd with address).
#define NOP      (char)0x00       // No operation.
#define RREG_VAL (char)0x16       // Number of registers to read to validate.
#define RDATA    (char)0x12       // Read converted data.

/* Registers defaults. */
#define CONFIG1_DEFAULT (char)0x90
#define CONFIG3_DEFAULT (char)0x60
#define CONFIG4_DEFAULT (char)0x00
#define MISC1_DEFAULT   (char)0x00
#define CHnSET_DEFAULT  (char)0x00

/* Registers settings. */
#define PD_REFBUF   (char)0x80
#define BIASREF_INT (char)0x08
#define SAMPLE_FREQ (char)0x02    // 4 kSPS
#define SINGLE_SHOT (char)0x04
#define SRB1        (char)0x20
#define PGA         (char)0x30    // Gain: 6
#define PDn_EN      (char)0x00
#define PDn_DIS     (char)0x80
#define MUXn        (char)0x00

/* Registers configurations. */
#define CONFIG1_SETS (CONFIG1_DEFAULT | SAMPLE_FREQ)
#define CONFIG3_SETS (CONFIG3_DEFAULT | PD_REFBUF | BIASREF_INT)
#define CONFIG4_SETS (CONFIG4_DEFAULT | SINGLE_SHOT)
#define MISC1_SETS   (MISC1_DEFAULT | SRB1)
#define CHnSET_EN    (CHnSET_DEFAULT | PDn_EN | MUXn | PGA)
#define CHnSET_DIS   (CHnSET_DEFAULT | PDn_DIS)

/* SPI timings (ms). */
#define SDATAC_DELAY 1
#define PD_REFBUF_DELAY 5
