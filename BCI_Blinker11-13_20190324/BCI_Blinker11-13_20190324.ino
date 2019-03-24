#define PIN11 8
#define PIN13 7

/* Blinking times in microseconds, 50% duty cycle, with slight corrections
 * on the frequencies due to rounding done by the uC logic (seen with logic
 * analyzer).
 */
const long double time11 = (0.5 / 11.015) * 1000000.0;
const long double time13 = (0.5 / 13.017) * 1000000.0;

long double prev11Time = 0.0;
long double prev13Time = 0.0;
long double currTime;

int state11 = LOW;
int state13 = LOW;

void setup(void) {
    pinMode(PIN11, OUTPUT);
    pinMode(PIN13, OUTPUT);
    digitalWrite(PIN11, LOW);
    digitalWrite(PIN13, LOW);
}

void loop(void) {
    // Get current time in us (will overflow after ~70 minutes).
    currTime = (long double)micros();
    // Check 11 Hz period.
    if (currTime - prev11Time >= time11) {
        digitalWrite(PIN11, !state11);
        state11 = !state11;
        prev11Time = currTime;
    }
    // Check 13 Hz period.
    if (currTime - prev13Time >= time13) {
        digitalWrite(PIN13, !state13);
        state13 = !state13;
        prev13Time = currTime;
    }
}
