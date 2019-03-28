#define PIN11 8
#define PIN13 7
#define MAXSTEPS11 355

/* Variable to bypass the timers bit resolution limit. */
unsigned int steps11 = 0;

/* Board setup. */
void setup(void) {
    // Initialize LED pins.
    pinMode(PIN11, OUTPUT);
    pinMode(PIN13, OUTPUT);
    digitalWrite(PIN11, LOW);
    digitalWrite(PIN13, LOW);
    noInterrupts();  // Disable all interrupts.
    // Initialize timer1 (16 bit, 26 Hz).
    // Reset registers.
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    // Configure timer1 registers.
    OCR1A = 2405;             // Compare Match (16 MHz/256/26 Hz).
    TCCR1B |= (1 << WGM12);   // CTC mode.
    TCCR1B |= (1 << CS12);    // Prescaler: 256.
    TIMSK1 |= (1 << OCIE1A);  // Enable Timer Compare interrupt.
    // Initialize timer2 (8 bit, 22 Hz).
    // Reset registers.
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;
    // Configure timer2 registers.
    OCR2A = 222;              // Compare Match (16 MHz/8/22 Hz) (hacked).
    TCCR2B |= (1 << WGM22);   // CTC mode.
    TCCR2B |= (1 << CS21);    // Prescaler: 8.
    TIMSK2 |= (1 << OCIE2A);  // Enable Timer Compare interrupt.
    interrupts();  // Enable all interrupts again.
}

/* Timer1 compare ISR. */
ISR(TIMER1_COMPA_vect) {
    digitalWrite(PIN13, digitalRead(PIN13) ^ 1);  // Toggle 13 Hz LED.
}

/* Timer2 compare ISR. */
ISR(TIMER2_COMPA_vect) {
    steps11++;
    if (steps11 >= MAXSTEPS11) {
        digitalWrite(PIN11, digitalRead(PIN11) ^ 1);  // Toggle 11 Hz LED.
        steps11 = 0;
    }
}

/* Endless loop of nothing. */
void loop(void) {}
