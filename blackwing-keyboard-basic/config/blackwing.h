
#define COMPILE_RIGHT
// #define COMPILE_LEFT


#ifdef COMPILE_LEFT

#define PIPE_NUMBER 0

#define S00 27
#define S01 26
#define S02 23
#define S03 22
#define S04 21
#define S05 20

#define S10 0
#define S11 30
#define S12 24
#define S13 25
#define S14 29
#define S15 28

#define S20 6
#define S21 5
#define S22 4
#define S23 3
#define S24 2
#define S25 1

#define S30 12
#define S31 11
#define S32 10
#define S33 9
#define S34 8
#define S35 7

#define S40 18
#define S41 17
#define S42 16
#define S43 15
#define S44 14
#define S45 13

#define S50 19

#endif


#ifdef COMPILE_RIGHT

#define PIPE_NUMBER 1

#define S00 15
#define S01 16
#define S02 17
#define S03 18
#define S04 19
#define S05 20

#define S10 9
#define S11 10
#define S12 11
#define S13 12
#define S14 13
#define S15 14

#define S20 3
#define S21 4
#define S22 5
#define S23 6
#define S24 7
#define S25 8

#define S30 25
#define S31 24
#define S32 30
#define S33 0
#define S34 1
#define S35 2

#define S40 22
#define S41 23
#define S42 26
#define S43 27
#define S44 28
#define S45 29

#define S50 21

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
