
// #define COMPILE_RIGHT
#define COMPILE_LEFT


#ifdef COMPILE_LEFT

#define PIPE_NUMBER 0

#define S00 16
#define S01 12
#define S02 22
#define S03 17
#define S04 18
#define S05 19

#define S10 8
#define S11 9
#define S12 10
#define S13 13
#define S14 14
#define S15 15

#define S20 2
#define S21 3
#define S22 4
#define S23 5
#define S24 6
#define S25 7

#define S30 29
#define S31 25
#define S32 24
#define S33 30
#define S34 0
#define S35 1

#define S40 27
#define S41 26
#define S42 23
#define S43 22
#define S44 21
#define S45 20

#define S50 28

#endif


#ifdef COMPILE_RIGHT

#define PIPE_NUMBER 1

#define S00 26
#define S01 25
#define S02 24
#define S03 23
#define S04 22
#define S05 21

#define S10 1
#define S11 0
#define S12 30
#define S13 29
#define S14 28
#define S15 27

#define S20 7
#define S21 6
#define S22 5
#define S23 4
#define S24 3
#define S25 2

#define S30 13
#define S31 12
#define S32 11
#define S33 10
#define S34 9
#define S35 8

#define S40 15
#define S41 16
#define S42 17
#define S43 18
#define S44 19
#define S45 20

#define S50 14

#endif

#define INPUT_MASK (1<<S00 | \
                    1<<S01 | \
                    1<<S02 | \
                    1<<S03 | \
                    1<<S04 | \
                    1<<S05 | \
                    1<<S10 | \
                    1<<S11 | \
                    1<<S12 | \
                    1<<S13 | \
                    1<<S14 | \
                    1<<S15 | \
                    1<<S20 | \
                    1<<S21 | \
                    1<<S22 | \
                    1<<S23 | \
                    1<<S24 | \
                    1<<S25 | \
                    1<<S30 | \
                    1<<S31 | \
                    1<<S32 | \
                    1<<S33 | \
                    1<<S34 | \
                    1<<S35 | \
                    1<<S40 | \
                    1<<S41 | \
                    1<<S42 | \
                    1<<S43 | \
                    1<<S44 | \
                    1<<S45 | \
                    1<<S50)


// Low frequency clock source to be used by the SoftDevice
#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_SYNTH,           \
                                 .rc_ctiv       = 0,                                \
                                 .rc_temp_ctiv  = 0,                                \
                                 .xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM}
