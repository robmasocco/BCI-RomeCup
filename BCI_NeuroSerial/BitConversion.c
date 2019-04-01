/* Converts a string of bits in CP2 in a 32 bit integer considering ENOB,
 * Effective Number Of Bits.
 */
double convertBit(const unsigned char *bytes, int nByte, int enob, int invert) {
    int number = 0;
    int power = 1;
    int startByte;
    int finalByte;
    int stepByte;
    int startBit = 8 * nByte - enob;
    int finalBit = 8 * nByte - 1;
    int sign;
    int bit;
    int byte;

    // Set the variable to read the bytes in the correct order
    if (invert == 1) {
        startByte = nByte - 1;
        finalByte = 0;
        stepByte = -1;
    } else {
        startByte = 0;
        finalByte = nByte - 1;
        stepByte = 1;
    }

    // Check CP2 sign reading last bit
    sign = ((*(bytes + finalByte) >> 7) & 1);

    // Loops init
    bit = 0;
    byte = startByte;

    // Bits before enob are constant (0 if positive number, 1 if negative)
    while (bit < startBit) {
        number += sign * power;
        power = 2 * power;

        bit++;
        if (bit % 8 == 0)
            byte += stepByte;
    }

    // Bits in the enob, excluding the last one
    while (bit < finalBit) {
        number += ((*(bytes + byte) >> (bit % 8)) & 1) * power;
        power = 2 * power;

        bit++;
        if (bit % 8 == 0)
            byte += stepByte;
    }

    // Last bit is considered negative in CP2
    number -= sign * power;

    return number;
}
