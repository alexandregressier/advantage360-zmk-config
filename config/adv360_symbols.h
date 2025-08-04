#pragma once

#include <dt-bindings/zmk/keys.h>

// Must be set before including helper.h
#define HOST_OS 2
// = macOS
#include "zmk-helpers/helper.h"
#undef UC_MACRO
#define UC_MACRO(name, unicode_bindings) \
    / { \
        macros { \
            name: name { \
                compatible = "zmk,behavior-macro"; \
                #binding-cells = <0>; \
                wait-ms = <10>; \
                tap-ms = <15>; \
                bindings = <OS_UNICODE_LEAD>, \
                          <&macro_wait_time 5>, \
                          <&macro_tap unicode_bindings>, \
                          <&macro_wait_time 5>, \
                          <OS_UNICODE_TRAIL>; \
            }; \
        }; \
    };

#define ZMK_UNICODE_SINGLE_SHIFTED(name, S0, S1, S2, S3) \
    UC_MACRO(name ## _shifted, &kp S0 &kp S1 &kp S2 &kp S3) \
    UC_MODMORPH(name, &none, &name ## _shifted)

// Quotes
ZMK_UNICODE_SINGLE_SHIFTED(u_curly_apostrophe, N2, N0, N1, N9) // ’ RIGHT SINGLE QUOTATION MARK (codepoint 8217, #o20031, #x2019), e.g., don’t

ZMK_UNICODE_SINGLE(u_left_curly_single_quote, N2, N0, N1, N8) // ‘ LEFT SINGLE QUOTATION MARK (codepoint 8216, #o20030, #x2018)

ZMK_UNICODE_SINGLE_SHIFTED(u_left_curly_double_quotes, N2, N0, N1, C) // “ LEFT DOUBLE QUOTATION MARK (codepoint 8220, #o20034, #x201c)
ZMK_UNICODE_SINGLE(u_right_curly_double_quotes, N2, N0, N1, D) // ” RIGHT DOUBLE QUOTATION MARK (codepoint 8221, #o20035, #x201d)

ZMK_UNICODE_SINGLE(u_guillemet_left,  N0, N0, A, B) // « LEFT-POINTING DOUBLE ANGLE QUOTATION MARK (codepoint 171, #o253, #xab)
ZMK_UNICODE_SINGLE(u_guillemet_right, N0, N0, B, B) // » RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK (codepoint 187, #o273, #xbb)

// Punctuation
ZMK_UNICODE_SINGLE(u_ellipsis, N2, N0, N2, N6) // … HORIZONTAL ELLIPSIS (codepoint 8230, #o20046, #x2026)
ZMK_UNICODE_SINGLE(u_interpunct, N0, N0, B, N7) // · MIDDLE DOT (codepoint 183, #o267, #xb7)

ZMK_UNICODE_SINGLE(u_en_dash, N2, N0, N1, N3) // – EN DASH (codepoint 8211, #o20023, #x2013)
ZMK_UNICODE_SINGLE(u_em_dash, N2, N0, N1, N4) // — EM DASH (codepoint 8212, #o20024, #x2014)

// Currencies
ZMK_UNICODE_SINGLE_SHIFTED(u_euro, N2, N0, A, C)  // € EURO SIGN (codepoint 8364, #o20254, #x20ac)

// Math
ZMK_UNICODE_SINGLE(u_multiplication, N0, N0, D, N7) // × MULTIPLICATION SIGN (codepoint 215, #o327, #xd7)
ZMK_UNICODE_SINGLE(u_division, N0, N0, F, N7) // ÷ DIVISION SIGN (codepoint 247, #o367, #xf7)
ZMK_UNICODE_SINGLE(u_almost_equal_to, N2, N2, N4, N8) // ≈ ALMOST EQUAL TO (codepoint 8776, #o21110, #x2248)

// French
ZMK_UNICODE_PAIR(fr_a_grave, N0, N0, E, N0, N0, N0, C, N0) // à LATIN SMALL LETTER A WITH GRAVE (codepoint 224, #o340, #xe0) / À LATIN CAPITAL LETTER A WITH GRAVE (codepoint 192, #o300, #xc0)
ZMK_UNICODE_PAIR(fr_a_circumflex, N0, N0, E, N2, N0, N0, C, N2) // â LATIN SMALL LETTER A WITH CIRCUMFLEX (codepoint 226, #o342, #xe2) / Â LATIN CAPITAL LETTER A WITH CIRCUMFLEX (codepoint 194, #o302, #xc2)

ZMK_UNICODE_PAIR(fr_e_acute, N0, N0, E, N9, N0, N0, C, N9) // é LATIN SMALL LETTER E WITH ACUTE (codepoint 233, #o351, #xe9) / É LATIN CAPITAL LETTER E WITH ACUTE (codepoint 201, #o311, #xc9)
ZMK_UNICODE_PAIR(fr_e_grave, N0, N0, E, N8, N0, N0, C, N8) // è LATIN SMALL LETTER E WITH GRAVE (codepoint 232, #o350, #xe8) / È LATIN CAPITAL LETTER E WITH GRAVE (codepoint 200, #o310, #xc8)
ZMK_UNICODE_PAIR(fr_e_circumflex, N0, N0, E, A, N0, N0, C, A) // ê LATIN SMALL LETTER E WITH CIRCUMFLEX (codepoint 234, #o352, #xea) / Ê LATIN CAPITAL LETTER E WITH CIRCUMFLEX (codepoint 202, #o312, #xca)

ZMK_UNICODE_PAIR(fr_i_circumflex, N0, N0, E, E, N0, N0, C, E) // î LATIN SMALL LETTER I WITH CIRCUMFLEX (codepoint 238, #o356, #xee) / Î LATIN CAPITAL LETTER I WITH CIRCUMFLEX (codepoint 206, #o316, #xce)
ZMK_UNICODE_PAIR(fr_i_diaeresis, N0, N0, E, F, N0, N0, C, F) // ï LATIN SMALL LETTER I WITH DIAERESIS (codepoint 239, #o357, #xef) / Ï LATIN CAPITAL LETTER I WITH DIAERESIS (codepoint 207, #o317, #xcf)

ZMK_UNICODE_PAIR(fr_o_circumflex, N0, N0, F, N4, N0, N0, D, N4) // ô LATIN SMALL LETTER O WITH CIRCUMFLEX (codepoint 244, #o364, #xf4) / Ô LATIN CAPITAL LETTER O WITH CIRCUMFLEX (codepoint 212, #o324, #xd4)

ZMK_UNICODE_SINGLE(fr_u_grave, N0, N0, F, N9) // ù LATIN SMALL LETTER U WITH GRAVE (codepoint 249, #o361, #xf9)
ZMK_UNICODE_PAIR(fr_u_circumflex, N0, N0, F, B, N0, N0, D, B) // û LATIN SMALL LETTER U WITH CIRCUMFLEX (codepoint 251, #o363, #xfb) / Û LATIN CAPITAL LETTER U WITH CIRCUMFLEX (codepoint 219, #o333, #xdb)

ZMK_UNICODE_PAIR(fr_c_cedilla, N0, N0, E, N7, N0, N0, C, N7) // ç LATIN SMALL LETTER C WITH CEDILLA (codepoint 231, #o347, #xe7) / Ç LATIN CAPITAL LETTER C WITH CEDILLA (codepoint 199, #o307, #xc7)
