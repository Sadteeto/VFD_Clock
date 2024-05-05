/**
 * @file pinsdef.h
 * @brief Defines pin mappings and segment display patterns for a VFD clock.
 */

#define VFDOUT 2
#define VFCLK 3
#define VFLOAD 4
#define VFBLANK 5
#define GPSTX 6
#define GPSRX 7


#define DIGIT_1 (1 << 31)
#define DIGIT_2 (1 << 30)
#define DIGIT_3 (1 << 29)
#define DIGIT_4 (1 << 28)
#define DIGIT_5 (1 << 27)
#define DIGIT_6 (1 << 26)
#define DIGIT_7 (1 << 25)
#define DIGIT_8 (1 << 24)
#define SEGMENT_G (1 << 23)
#define SEGMENT_F (1 << 22)
#define SEGMENT_E (1 << 21)
#define SEGMENT_D (1 << 20)
#define SEGMENT_C (1 << 19)
#define SEGMENT_B (1 << 18)
#define SEGMENT_A (1 << 17)
#define DIGIT_0 (1 << 16)
#define SEGMENT_DOT (1 << 8)

#define SEGMENT_SHOW_0  (SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F)         // 0
#define SEGMENT_SHOW_1  (SEGMENT_B | SEGMENT_C)                                                       // 1
#define SEGMENT_SHOW_2  (SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G)                    // 2
#define SEGMENT_SHOW_3  (SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G)                    // 3
#define SEGMENT_SHOW_4  (SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G)                                // 4
#define SEGMENT_SHOW_5  (SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G)                    // 5
#define SEGMENT_SHOW_6  (SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G)        // 6
#define SEGMENT_SHOW_7  (SEGMENT_A | SEGMENT_B | SEGMENT_C)                                            // 7
#define SEGMENT_SHOW_8  (SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G) // 8
#define SEGMENT_SHOW_9  (SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G)        // 9

#define SEGMENT_SHOW_A  (SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_E | SEGMENT_F | SEGMENT_G)        // A
#define SEGMENT_SHOW_C  (SEGMENT_A | SEGMENT_D | SEGMENT_E | SEGMENT_F)       
#define SEGMENT_SHOW_E  (SEGMENT_A | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G)                    // E
#define SEGMENT_SHOW_F  (SEGMENT_A | SEGMENT_E | SEGMENT_F | SEGMENT_G)                                // F
#define SEGMENT_SHOW_G  (SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F)                    // G
#define SEGMENT_SHOW_H  (SEGMENT_B | SEGMENT_C | SEGMENT_E | SEGMENT_F | SEGMENT_G)                    // H
#define SEGMENT_SHOW_I  (SEGMENT_B | SEGMENT_C)                                                        // I
#define SEGMENT_SHOW_J  (SEGMENT_B | SEGMENT_C | SEGMENT_D)                                            // J
#define SEGMENT_SHOW_L  (SEGMENT_D | SEGMENT_E | SEGMENT_F)                                            // L
#define SEGMENT_SHOW_O  (SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F)        // O
#define SEGMENT_SHOW_P  (SEGMENT_A | SEGMENT_B | SEGMENT_E | SEGMENT_F | SEGMENT_G)                    // P
#define SEGMENT_SHOW_S  (SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G)                    // S
#define SEGMENT_SHOW_T  (SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G)                                // T
#define SEGMENT_SHOW_U  (SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F)                    // U
#define SEGMENT_SHOW_Z  (SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G)                    // Z
#define SEGMENT_SHOW_DASH (SEGMENT_G)                                                                 // -
#define SEGMENT_SHOW_NONE 0





