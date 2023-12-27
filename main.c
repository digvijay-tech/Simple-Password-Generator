#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


enum Intensity {
    Default = 8,
    Strong = 12,
    Solid = 16,
    Complex = 18,
    Intense = 24
};

// Checkout my git repo for basic XORShift implementation: https://github.com/digvijay-tech/xorShift-Algorithm 
// implementing XORShift function to generate 32-bit random integers
uint32_t xorShift(uint32_t *state) {
    uint32_t x = *state;

    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;

    // removing the '-' sign from the result
    x &= 0x7FFFFFFF;

    *state = x;
    return x;
}


void generate(int intensity) {
    int nums[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    char u_alphas[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
    char l_alphas[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};
    char specials[] = {'>', '^', '$', '!', '@', '%', '<', ',', '.', '|', '~', ':', ';', '$', '#', '@', '!', '&', '`', '?', '\0'};


    // initialize seed
    uint32_t seed = (uint32_t)time(NULL);


    for (int i = 0; i < intensity; i++) {
        int r_num = xorShift(&seed);

        // 4 characters array = 4 x 3 x 2 x 1 = 24
        // generating random number for selecting one if the array randomly
        int x24_roll = (int)(r_num % (25 - 0 - 1));

        // switching between arrays
        // special characters range
        if (x24_roll >= 0 && x24_roll < 5) {
            int result = (int)(r_num % (19 - 0 - 1));
            printf("%c", specials[result]);
        }

        // Numbers range
        if (x24_roll >= 5 && x24_roll < 9) {
            int result = (int)(r_num % (9 - 0 - 1));
            printf("%d", nums[result]);
        }

        // Uppercase alphabates range
        if (x24_roll >= 9  && x24_roll < 18) {
            int result = (int)(r_num % (27 - 0 - 1));
            printf("%c", u_alphas[result]);
        }

        // Lowercase alphabates range
        if (x24_roll >= 18  && x24_roll < 24) {
            int result = (int)(r_num % (27 - 0 - 1));
            printf("%c", l_alphas[result]);
        }
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    // check for no arguments
    if (argc <= 1) {
        puts("No Argument Found!");
        return 1;
    }

    // set intensity
    enum Intensity intensity = Default;

    int user_input = atoi(argv[1]);

    switch (user_input) {
        case Default:
            printf("Intensity set to DEFAULT, password length: %d\n", Default);
            generate(Default);
            break;
        case Strong:
            printf("Intensity set to STRONG, password length: %d\n", Strong);
            generate(Strong);
            break;
        case Solid:
            printf("Intensity set to SOLID, password length: %d\n", Solid);
            generate(Solid);
            break;
        case Complex:
            printf("Intensity set to COMPLEX, password length: %d\n", Complex);
            generate(Complex);
            break;
        case Intense:
            printf("Intensity set to INTENSE, password length: %d\n", Intense);
            generate(Intense);
            break;
        default:
            printf("Please Provide Valid Argument!\n");
            return 1;
    }

    return 0;
}
