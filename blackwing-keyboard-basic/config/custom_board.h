#include <stdint.h>

#include "nrf_gpio.h"

#define COMPILE_RIGHT
// #define COMPILE_LEFT


#ifdef COMPILE_LEFT

#define PIPE_NUMBER 0

#define S00 NRF_GPIO_PIN_MAP(1,  2)
#define S01 NRF_GPIO_PIN_MAP(0,  7)
#define S02 NRF_GPIO_PIN_MAP(0,  5)
#define S03 NRF_GPIO_PIN_MAP(0,  4)
#define S04 NRF_GPIO_PIN_MAP(0, 31)
#define S05 NRF_GPIO_PIN_MAP(1, 14)

#define S10 NRF_GPIO_PIN_MAP(1,  1)
#define S11 NRF_GPIO_PIN_MAP(1,  9)
#define S12 NRF_GPIO_PIN_MAP(0, 16)
#define S13 NRF_GPIO_PIN_MAP(1,  7)
#define S14 NRF_GPIO_PIN_MAP(0, 26)
// #define S14 NRF_GPIO_PIN_MAP(1,  6)  // Fix for second broken left half
#define S15 NRF_GPIO_PIN_MAP(1, 12)

#define S20 NRF_GPIO_PIN_MAP(1,  3)
#define S21 NRF_GPIO_PIN_MAP(0, 12)
#define S22 NRF_GPIO_PIN_MAP(0, 13)
#define S23 NRF_GPIO_PIN_MAP(1,  5)
#define S24 NRF_GPIO_PIN_MAP(0,  6)
#define S25 NRF_GPIO_PIN_MAP(0, 25)
// #define S25 NRF_GPIO_PIN_MAP(0, 15)  // Fix for broken left half

#define S30 NRF_GPIO_PIN_MAP(1,  0)
#define S31 NRF_GPIO_PIN_MAP(0, 22)
#define S32 NRF_GPIO_PIN_MAP(0, 14)
#define S33 NRF_GPIO_PIN_MAP(0, 24)
// #define S33 NRF_GPIO_PIN_MAP(0, 15)  // Fix for second broken left half
#define S34 NRF_GPIO_PIN_MAP(0,  8)
#define S35 NRF_GPIO_PIN_MAP(0, 11)

#define S40 NRF_GPIO_PIN_MAP(0, 21)
#define S41 NRF_GPIO_PIN_MAP(0, 23)
#define S42 NRF_GPIO_PIN_MAP(0, 17)
#define S43 NRF_GPIO_PIN_MAP(0, 20)
#define S44 NRF_GPIO_PIN_MAP(0, 27)
#define S45 NRF_GPIO_PIN_MAP(1,  8)

#define S50 NRF_GPIO_PIN_MAP(0, 19)

#endif


#ifdef COMPILE_RIGHT

#define PIPE_NUMBER 1

#define S00 NRF_GPIO_PIN_MAP(0, 31)  // 15
#define S01 NRF_GPIO_PIN_MAP(0, 19)  // 16
#define S02 NRF_GPIO_PIN_MAP(1, 14)  // 17
#define S03 NRF_GPIO_PIN_MAP(1,  1)  // 18
#define S04 NRF_GPIO_PIN_MAP(0, 16)  // 19
#define S05 NRF_GPIO_PIN_MAP(1,  7)  // 20

#define S10 NRF_GPIO_PIN_MAP(0,  4)  // 9
#define S11 NRF_GPIO_PIN_MAP(0, 21)  // 10
#define S12 NRF_GPIO_PIN_MAP(1, 12)  // 11
#define S13 NRF_GPIO_PIN_MAP(1,  3)  // 12
#define S14 NRF_GPIO_PIN_MAP(0, 13)  // 13
#define S15 NRF_GPIO_PIN_MAP(1,  5)  // 14

#define S20 NRF_GPIO_PIN_MAP(0,  5)  // 3
#define S21 NRF_GPIO_PIN_MAP(0, 26)  // 4
#define S22 NRF_GPIO_PIN_MAP(0, 25)  // 5
#define S23 NRF_GPIO_PIN_MAP(1,  0)  // 6
#define S24 NRF_GPIO_PIN_MAP(0, 14)  // 7
#define S25 NRF_GPIO_PIN_MAP(0, 24)  // 8

#define S30 NRF_GPIO_PIN_MAP(0,  7)  // 25
#define S31 NRF_GPIO_PIN_MAP(0,  6)  // 24
#define S32 NRF_GPIO_PIN_MAP(0, 11)  // 30
// #define S32 NRF_GPIO_PIN_MAP(1, 11)  // 5  // Fix for second broken right half
#define S33 NRF_GPIO_PIN_MAP(0, 22)  // 0
#define S34 NRF_GPIO_PIN_MAP(0, 15)  // 1
#define S35 NRF_GPIO_PIN_MAP(0, 20)  // 2

#define S40 NRF_GPIO_PIN_MAP(0, 12)  // 22
#define S41 NRF_GPIO_PIN_MAP(0, 23)  // 23
#define S42 NRF_GPIO_PIN_MAP(0,  8)  // 26
// #define S42 NRF_GPIO_PIN_MAP(1, 10)  // 26  // Fix for second broken right half
#define S43 NRF_GPIO_PIN_MAP(0, 27)  // 27
#define S44 NRF_GPIO_PIN_MAP(1,  8)  // 28
#define S45 NRF_GPIO_PIN_MAP(0, 17)  // 29

#define S50 NRF_GPIO_PIN_MAP(1,  9)  // 21

#endif

#define INPUT_MASK (((uint64_t)1)<<S00) | \
                   (((uint64_t)1)<<S01) | \
                   (((uint64_t)1)<<S02) | \
                   (((uint64_t)1)<<S03) | \
                   (((uint64_t)1)<<S04) | \
                   (((uint64_t)1)<<S05) | \
                   (((uint64_t)1)<<S10) | \
                   (((uint64_t)1)<<S11) | \
                   (((uint64_t)1)<<S12) | \
                   (((uint64_t)1)<<S13) | \
                   (((uint64_t)1)<<S14) | \
                   (((uint64_t)1)<<S15) | \
                   (((uint64_t)1)<<S20) | \
                   (((uint64_t)1)<<S21) | \
                   (((uint64_t)1)<<S22) | \
                   (((uint64_t)1)<<S23) | \
                   (((uint64_t)1)<<S24) | \
                   (((uint64_t)1)<<S25) | \
                   (((uint64_t)1)<<S30) | \
                   (((uint64_t)1)<<S31) | \
                   (((uint64_t)1)<<S32) | \
                   (((uint64_t)1)<<S33) | \
                   (((uint64_t)1)<<S34) | \
                   (((uint64_t)1)<<S35) | \
                   (((uint64_t)1)<<S40) | \
                   (((uint64_t)1)<<S41) | \
                   (((uint64_t)1)<<S42) | \
                   (((uint64_t)1)<<S43) | \
                   (((uint64_t)1)<<S44) | \
                   (((uint64_t)1)<<S45) | \
                   (((uint64_t)1)<<S50)
