

/*
 *
 * ssd1306utf8_wqy14
 *
 *
 * File Name           : ssd1306utf8_wqy14.h
 * Date                : 14.07.2024
 * Font size in bytes  : FF
 * Font width          : 14
 * Font height         : 14
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Type_Indicator;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Ascii_Char_Count;
 *     uint16_t   font_Utf8_Section_Start;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 *
 *     uint16_t    font_Utf8_Indicator;
 *     uint8_t     font_Utf8_Glyph_Width;
 *     uint8_t     font_Utf8_Glyph_Count;
 *
 *     uint8_t    utf8_Glyph_Metadata[];
 *                  // contains unicode code, glyph width (optional), and glyph data start position
 *                  // length = glyph_count * ((use_utf8_extension_plane ? 3 : 2) + (utf8_fixed_width ? 0 : 1) + ( 3 : 2))
 *
 *     uint8_t    utf8_Glyph_Data[];
 *                  // bit data of utf8 glyphs
 */

#ifndef SSD1306UTF8_WQY14_H
#define SSD1306UTF8_WQY14_H

#define SSD1306UTF8_WQY14_WIDTH 14
#define SSD1306UTF8_WQY14_HEIGHT 14

static const uint8_t ssd1306utf8_wqy14[] = {
    0x00, 0x04, // type indicator
    0x0E,       // width
    0x0E,       // height
    0x20,       // first char
    0x60,       // char count
    0x04, 0xB6, // utf8 section start

    // char widths
    0x02, 0x01, 0x03, 0x08, 0x07, 0x0A, 0x08, 0x01, 0x03, 0x03,
    0x05, 0x07, 0x01, 0x04, 0x01, 0x04, 0x06, 0x03, 0x06, 0x06,
    0x07, 0x06, 0x06, 0x06, 0x06, 0x06, 0x01, 0x01, 0x06, 0x06,
    0x06, 0x06, 0x0D, 0x09, 0x07, 0x08, 0x08, 0x07, 0x07, 0x09,
    0x07, 0x01, 0x05, 0x08, 0x07, 0x09, 0x07, 0x09, 0x07, 0x09,
    0x08, 0x07, 0x07, 0x07, 0x09, 0x0D, 0x08, 0x09, 0x08, 0x02,
    0x04, 0x02, 0x05, 0x08, 0x02, 0x06, 0x06, 0x05, 0x06, 0x06,
    0x04, 0x06, 0x06, 0x01, 0x02, 0x06, 0x01, 0x09, 0x06, 0x06,
    0x06, 0x06, 0x04, 0x05, 0x04, 0x06, 0x07, 0x09, 0x06, 0x07,
    0x06, 0x03, 0x01, 0x03, 0x07, 0x07,

    // font data
    0x00, 0x00, 0x00, 0x00,                                                                                                                                     // <space> 0x20
    0xFE, 0x14,                                                                                                                                                 // 33
    0x1E, 0x00, 0x1E, 0x00, 0x00, 0x00,                                                                                                                         // 34
    0x90, 0x90, 0xF8, 0x96, 0x90, 0xF8, 0x96, 0x90, 0x00, 0x1C, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,                                                             // 35
    0x18, 0x24, 0x22, 0xFF, 0x42, 0x42, 0x84, 0x08, 0x10, 0x10, 0x3C, 0x10, 0x08, 0x04,                                                                         // 36
    0x1C, 0x22, 0x22, 0x1C, 0xC0, 0x30, 0x8C, 0x42, 0x40, 0x80, 0x00, 0x00, 0x10, 0x0C, 0x00, 0x00, 0x0C, 0x10, 0x10, 0x0C,                                     // 37
    0x80, 0x5C, 0x22, 0x62, 0x92, 0x0C, 0x80, 0x00, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x0C, 0x08, 0x10,                                                             // 38
    0x1E, 0x00,                                                                                                                                                 // 39
    0xF0, 0x0C, 0x02, 0x1C, 0x60, 0x80,                                                                                                                         // 40
    0x02, 0x0C, 0xF0, 0x80, 0x60, 0x1C,                                                                                                                         // 41
    0x04, 0x14, 0x0E, 0x14, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                 // 42
    0x40, 0x40, 0x40, 0xF8, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00,                                                                         // 43
    0x00, 0x70,                                                                                                                                                 // 44
    0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,                                                                                                             // 45
    0x00, 0x10,                                                                                                                                                 // 46
    0x00, 0xC0, 0x38, 0x06, 0x18, 0x04, 0x00, 0x00,                                                                                                             // 47
    0xFC, 0x02, 0x02, 0x02, 0x02, 0xFC, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x0C,                                                                                     // 48
    0x08, 0x04, 0xFE, 0x00, 0x00, 0x1C,                                                                                                                         // 49
    0x0C, 0x02, 0x02, 0x82, 0x42, 0x3C, 0x10, 0x18, 0x14, 0x10, 0x10, 0x10,                                                                                     // 50
    0x0C, 0x02, 0x22, 0x22, 0x22, 0xDC, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x0C,                                                                                     // 51
    0x80, 0x40, 0x30, 0x08, 0x04, 0xFE, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1C, 0x04,                                                                         // 52
    0x38, 0x16, 0x12, 0x12, 0x12, 0xE2, 0x0C, 0x10, 0x10, 0x10, 0x18, 0x04,                                                                                     // 53
    0xF8, 0x44, 0x22, 0x22, 0x22, 0xC4, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x0C,                                                                                     // 54
    0x02, 0x02, 0x02, 0xE2, 0x1A, 0x06, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,                                                                                     // 55
    0xDC, 0x22, 0x22, 0x22, 0x22, 0xDC, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x0C,                                                                                     // 56
    0x3C, 0x42, 0x42, 0x42, 0x22, 0xFC, 0x08, 0x10, 0x10, 0x10, 0x08, 0x04,                                                                                     // 57
    0x08, 0x10,                                                                                                                                                 // 58
    0x08, 0x70,                                                                                                                                                 // 59
    0x40, 0xA0, 0xA0, 0x10, 0x10, 0x08, 0x00, 0x00, 0x00, 0x04, 0x04, 0x08,                                                                                     // 60
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                     // 61
    0x08, 0x10, 0x10, 0xA0, 0xA0, 0x40, 0x08, 0x04, 0x04, 0x00, 0x00, 0x00,                                                                                     // 62
    0x0C, 0x02, 0x82, 0x42, 0x22, 0x1C, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,                                                                                     // 63
    0xE0, 0x18, 0x04, 0xC4, 0x22, 0x12, 0x12, 0x12, 0xA2, 0x72, 0x04, 0x08, 0xF0, 0x0C, 0x30, 0x40, 0x4C, 0x90, 0x90, 0x90, 0x88, 0x9C, 0x90, 0x50, 0x4C, 0x20, // 64
    0x00, 0x80, 0xE0, 0x9C, 0x82, 0x9C, 0xE0, 0x80, 0x00, 0x18, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x18,                                                 // 65
    0xFE, 0x22, 0x22, 0x22, 0x22, 0x22, 0xDC, 0x1C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0C,                                                                         // 66
    0xF8, 0x04, 0x02, 0x02, 0x02, 0x02, 0x04, 0x08, 0x04, 0x08, 0x10, 0x10, 0x10, 0x10, 0x08, 0x04,                                                             // 67
    0xFE, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0xF8, 0x1C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x04,                                                             // 68
    0xFE, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,                                                                         // 69
    0xFE, 0x22, 0x22, 0x22, 0x22, 0x22, 0x02, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 70
    0xF8, 0x04, 0x02, 0x02, 0x02, 0x42, 0x42, 0x44, 0xC8, 0x04, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x04,                                                 // 71
    0xFE, 0x20, 0x20, 0x20, 0x20, 0x20, 0xFE, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C,                                                                         // 72
    0xFE, 0x1C,                                                                                                                                                 // 73
    0x00, 0x00, 0x00, 0x00, 0xFE, 0x0C, 0x10, 0x10, 0x10, 0x0C,                                                                                                 // 74
    0xFE, 0x80, 0x40, 0x20, 0x50, 0x88, 0x04, 0x02, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x10,                                                             // 75
    0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,                                                                         // 76
    0xFE, 0x0C, 0x30, 0xC0, 0x00, 0xC0, 0x30, 0x0C, 0xFE, 0x1C, 0x00, 0x00, 0x04, 0x18, 0x04, 0x00, 0x00, 0x1C,                                                 // 77
    0xFE, 0x04, 0x18, 0x60, 0x80, 0x00, 0xFE, 0x1C, 0x00, 0x00, 0x00, 0x04, 0x08, 0x1C,                                                                         // 78
    0xF8, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0xF8, 0x04, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x04,                                                 // 79
    0xFE, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 80
    0xF8, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0xF8, 0x04, 0x08, 0x10, 0x10, 0x10, 0x14, 0x08, 0x1C, 0x10,                                                 // 81
    0xFE, 0x42, 0x42, 0x42, 0xC2, 0x42, 0x42, 0x3C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x10,                                                             // 82
    0x1C, 0x22, 0x22, 0x22, 0x42, 0x42, 0x8C, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0C,                                                                         // 83
    0x02, 0x02, 0x02, 0xFE, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,                                                                         // 84
    0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x04, 0x08, 0x10, 0x10, 0x10, 0x08, 0x04,                                                                         // 85
    0x06, 0x18, 0x60, 0x80, 0x00, 0x80, 0x60, 0x18, 0x06, 0x00, 0x00, 0x00, 0x04, 0x18, 0x04, 0x00, 0x00, 0x00,                                                 // 86
    0x06, 0x38, 0xC0, 0x00, 0xC0, 0x3C, 0x02, 0x3C, 0xC0, 0x00, 0xC0, 0x38, 0x06, 0x00, 0x00, 0x04, 0x18, 0x04, 0x00, 0x00, 0x00, 0x04, 0x18, 0x04, 0x00, 0x00, // 87
    0x02, 0x0C, 0x90, 0x60, 0x60, 0x90, 0x0C, 0x02, 0x10, 0x0C, 0x00, 0x00, 0x00, 0x04, 0x0C, 0x10,                                                             // 88
    0x02, 0x04, 0x18, 0x20, 0xC0, 0x20, 0x18, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00,                                                 // 89
    0x00, 0x02, 0x82, 0x42, 0x22, 0x1A, 0x06, 0x02, 0x10, 0x18, 0x14, 0x10, 0x10, 0x10, 0x10, 0x10,                                                             // 90
    0xFE, 0x02, 0xFC, 0x80,                                                                                                                                     // 91
    0x06, 0x38, 0xC0, 0x00, 0x00, 0x00, 0x04, 0x18,                                                                                                             // 92
    0x02, 0xFE, 0x80, 0xFC,                                                                                                                                     // 93
    0x20, 0x1C, 0x02, 0x1C, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                                                 // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,                                                             // 95
    0x02, 0x04, 0x00, 0x00,                                                                                                                                     // 96
    0x10, 0x88, 0x48, 0x48, 0x48, 0xF0, 0x0C, 0x10, 0x10, 0x10, 0x08, 0x1C,                                                                                     // 97
    0xFE, 0x10, 0x08, 0x08, 0x08, 0xF0, 0x1C, 0x08, 0x10, 0x10, 0x10, 0x0C,                                                                                     // 98
    0xF0, 0x08, 0x08, 0x08, 0x10, 0x0C, 0x10, 0x10, 0x10, 0x08,                                                                                                 // 99
    0xF0, 0x08, 0x08, 0x08, 0x10, 0xFE, 0x0C, 0x10, 0x10, 0x10, 0x08, 0x1C,                                                                                     // 100
    0xF0, 0x48, 0x48, 0x48, 0x48, 0x70, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x08,                                                                                     // 101
    0x08, 0xFC, 0x0A, 0x0A, 0x00, 0x1C, 0x00, 0x00,                                                                                                             // 102
    0xF0, 0x08, 0x08, 0x08, 0x10, 0xF8, 0x4C, 0x90, 0x90, 0x90, 0x88, 0x7C,                                                                                     // 103
    0xFE, 0x10, 0x08, 0x08, 0x08, 0xF0, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x1C,                                                                                     // 104
    0xFA, 0x1C,                                                                                                                                                 // 105
    0x00, 0xFA, 0x80, 0x7C,                                                                                                                                     // 106
    0xFE, 0x80, 0x40, 0xA0, 0x10, 0x08, 0x1C, 0x00, 0x00, 0x00, 0x0C, 0x10,                                                                                     // 107
    0xFE, 0x1C,                                                                                                                                                 // 108
    0xF8, 0x10, 0x08, 0x08, 0xF0, 0x10, 0x08, 0x08, 0xF0, 0x1C, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x1C,                                                 // 109
    0xF8, 0x10, 0x08, 0x08, 0x08, 0xF0, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x1C,                                                                                     // 110
    0xF0, 0x08, 0x08, 0x08, 0x08, 0xF0, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x0C,                                                                                     // 111
    0xF8, 0x10, 0x08, 0x08, 0x08, 0xF0, 0xFC, 0x08, 0x10, 0x10, 0x10, 0x0C,                                                                                     // 112
    0xF0, 0x08, 0x08, 0x08, 0x10, 0xF8, 0x0C, 0x10, 0x10, 0x10, 0x08, 0xFC,                                                                                     // 113
    0xF8, 0x10, 0x08, 0x08, 0x1C, 0x00, 0x00, 0x00,                                                                                                             // 114
    0x30, 0x48, 0x48, 0x48, 0x90, 0x08, 0x10, 0x10, 0x10, 0x0C,                                                                                                 // 115
    0x08, 0xFE, 0x08, 0x08, 0x00, 0x1C, 0x10, 0x10,                                                                                                             // 116
    0xF8, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x0C, 0x10, 0x10, 0x10, 0x08, 0x1C,                                                                                     // 117
    0x18, 0x60, 0x80, 0x00, 0x80, 0x60, 0x18, 0x00, 0x00, 0x04, 0x18, 0x04, 0x00, 0x00,                                                                         // 118
    0x18, 0xE0, 0x00, 0xE0, 0x18, 0xE0, 0x00, 0xE0, 0x18, 0x00, 0x04, 0x18, 0x04, 0x00, 0x04, 0x18, 0x04, 0x00,                                                 // 119
    0x08, 0x30, 0xC0, 0xC0, 0x30, 0x08, 0x10, 0x0C, 0x00, 0x00, 0x0C, 0x10,                                                                                     // 120
    0x18, 0x60, 0x80, 0x00, 0x80, 0x60, 0x18, 0x00, 0x80, 0x8C, 0x70, 0x0C, 0x00, 0x00,                                                                         // 121
    0x08, 0x08, 0x88, 0x68, 0x18, 0x08, 0x10, 0x18, 0x14, 0x10, 0x10, 0x10,                                                                                     // 122
    0x80, 0x7C, 0x02, 0x00, 0x7C, 0x80,                                                                                                                         // 123
    0xFE, 0xFC,                                                                                                                                                 // 124
    0x02, 0x7C, 0x80, 0x80, 0x7C, 0x00,                                                                                                                         // 125
    0x40, 0x20, 0x20, 0x60, 0x40, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                         // 126
    0xFC, 0x04, 0x04, 0x04, 0x04, 0x04, 0xFC, 0x1C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1C,                                                                         // 127

    0x00, 0x03,             // utf8 type indicator
    0x0E,                   // utf8 glyph width
    0x00, 0x44,             // utf8 glyph count

    0x4e, 0xd, 0x5, 0xcb,
    0x4e, 0x2d, 0x5, 0xe7,
    0x4e, 0x8e, 0x6, 0x3,
    0x4f, 0x5c, 0x6, 0x1f,
    0x4f, 0xdd, 0x6, 0x3b,
    0x50, 0x5c, 0x6, 0x57,
    0x51, 0x73, 0x6, 0x73,
    0x52, 0xa0, 0x6, 0x8f,
    0x53, 0x47, 0x6, 0xab,
    0x53, 0x8b, 0x6, 0xc7,
    0x53, 0xcd, 0x6, 0xe3,
    0x53, 0xd1, 0x6, 0xff,
    0x53, 0xef, 0x7, 0x1b,
    0x54, 0x11, 0x7, 0x37,
    0x54, 0x4a, 0x7, 0x53,
    0x56, 0xde, 0x7, 0x6f,
    0x57, 0x28, 0x7, 0x8b,
    0x59, 0x31, 0x7, 0xa7,
    0x5b, 0x58, 0x7, 0xc3,
    0x5b, 0xf9, 0x7, 0xdf,
    0x5c, 0x6, 0x7, 0xfb,
    0x5d, 0xe5, 0x8, 0x17,
    0x5d, 0xf2, 0x8, 0x33,
    0x5e, 0x76, 0x8, 0x4f,
    0x5e, 0x8f, 0x8, 0x6b,
    0x5f, 0x0, 0x8, 0x87,
    0x60, 0x1, 0x8, 0xa3,
    0x62, 0xe9, 0x8, 0xbf,
    0x63, 0x9, 0x8, 0xdb,
    0x63, 0xd0, 0x8, 0xf7,
    0x64, 0xad, 0x9, 0x13,
    0x65, 0x3e, 0x9, 0x2f,
    0x65, 0x70, 0x9, 0x4b,
    0x65, 0x87, 0x9, 0x67,
    0x66, 0x3e, 0x9, 0x83,
    0x66, 0xf4, 0x9, 0x9f,
    0x67, 0x2c, 0x9, 0xbb,
    0x67, 0x3a, 0x9, 0xd7,
    0x6b, 0x62, 0x9, 0xf3,
    0x6b, 0x63, 0xa, 0xf,
    0x6c, 0x42, 0xa, 0x2b,
    0x6d, 0x41, 0xa, 0x47,
    0x6e, 0x90, 0xa, 0x63,
    0x70, 0xed, 0xa, 0x7f,
    0x72, 0x48, 0xa, 0x9b,
    0x72, 0x59, 0xa, 0xb7,
    0x72, 0xb6, 0xa, 0xd3,
    0x75, 0x35, 0xa, 0xef,
    0x7a, 0xb, 0xb, 0xb,
    0x7f, 0x6e, 0xb, 0x27,
    0x80, 0xfd, 0xb, 0x43,
    0x84, 0x57, 0xb, 0x5f,
    0x84, 0xdd, 0xb, 0x7b,
    0x88, 0x4c, 0xb, 0x97,
    0x8a, 0x0, 0xb, 0xb3,
    0x8b, 0x66, 0xb, 0xcf,
    0x8b, 0xbe, 0xb, 0xeb,
    0x8b, 0xed, 0xc, 0x7,
    0x8b, 0xf7, 0xc, 0x23,
    0x8d, 0x25, 0xc, 0x3f,
    0x8f, 0x6e, 0xc, 0x5b,
    0x8f, 0x7d, 0xc, 0x77,
    0x8f, 0xd0, 0xc, 0x93,
    0x8f, 0xd4, 0xc, 0xaf,
    0x90, 0x9, 0xc, 0xcb,
    0x91, 0x4d, 0xc, 0xe7,
    0x9a, 0xd8, 0xd, 0x3,
    0x9f, 0x7f, 0xd, 0x1f,

    0x04,0x04,0x04,0x84,0x44,0x24,0xF4,0x0C,0x0C,0x44,0x84,0x04,0x04,0x04,0x04,0x02,
    0x01,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x01,0x06,0x00,/*"不",0*/
    0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x01,
    0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x01,0x00,/*"中",1*/
    0x40,0x40,0x44,0x44,0x44,0x44,0xFC,0x44,0x44,0x44,0x44,0x44,0x40,0x40,0x00,0x00,
    0x00,0x00,0x10,0x20,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"于",2*/
    0x40,0x20,0xF8,0x46,0x20,0x18,0x0E,0xF8,0xF8,0x48,0x48,0x48,0x48,0x08,0x00,0x00,
    0x3F,0x00,0x00,0x00,0x00,0x3F,0x3F,0x02,0x02,0x02,0x02,0x02,/*"作",3*/
    0x40,0x20,0xF8,0x06,0x80,0xBC,0xA4,0xA4,0xA4,0xE4,0xA4,0xA4,0xBC,0x80,0x00,0x00,
    0x3F,0x00,0x10,0x08,0x04,0x02,0x02,0x3F,0x02,0x04,0x08,0x10,/*"保",4*/
    0x40,0x20,0xF8,0x06,0x04,0x04,0x74,0x54,0x54,0x56,0x54,0x74,0x04,0x04,0x00,0x00,
    0x3F,0x00,0x03,0x05,0x05,0x25,0x25,0x3D,0x05,0x05,0x05,0x03,/*"停",5*/
    0x00,0x10,0x12,0x14,0x18,0x10,0xF0,0x18,0x18,0x14,0x12,0x10,0x10,0x00,0x21,0x21,
    0x11,0x09,0x05,0x03,0x01,0x03,0x03,0x05,0x09,0x11,0x21,0x21,/*"关",6*/
    0x10,0x10,0x10,0xFE,0x10,0x10,0xF0,0x00,0x00,0xF8,0x08,0x08,0x08,0xF8,0x20,0x10,
    0x0C,0x03,0x10,0x20,0x1F,0x00,0x00,0x3F,0x10,0x10,0x10,0x3F,/*"加",7*/
    0x80,0x88,0x88,0x88,0xF8,0x84,0x86,0x84,0x84,0xFE,0x80,0x80,0x80,0x80,0x00,0x20,
    0x10,0x0C,0x03,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,/*"升",8*/
    0x00,0x00,0xFC,0x04,0x84,0x84,0x84,0xF4,0xF4,0x84,0x84,0x84,0x84,0x04,0x20,0x18,
    0x07,0x20,0x20,0x20,0x20,0x3F,0x3F,0x20,0x20,0x22,0x2C,0x20,/*"压",9*/
    0x00,0x00,0xFC,0x24,0xE4,0x24,0x24,0x22,0x22,0x22,0xE2,0x22,0x00,0x00,0x20,0x18,
    0x07,0x20,0x20,0x11,0x0A,0x04,0x04,0x0B,0x10,0x20,0x20,0x20,/*"反",10*/
    0x00,0x30,0x2C,0x20,0xE0,0xBE,0xA0,0xA0,0xA0,0xA0,0xA4,0xA8,0x20,0x20,0x10,0x08,
    0x24,0x23,0x21,0x12,0x14,0x08,0x08,0x0C,0x12,0x21,0x20,0x20,/*"发",11*/
    0x04,0x04,0xE4,0x24,0x24,0x24,0xE4,0x04,0x04,0x04,0x04,0xFC,0x04,0x04,0x00,0x00,
    0x07,0x02,0x02,0x02,0x07,0x00,0x00,0x10,0x20,0x1F,0x00,0x00,/*"可",12*/
    0x00,0xF8,0x08,0x08,0xCC,0x4A,0x48,0x48,0x48,0xC8,0x08,0x08,0xF8,0x00,0x00,0x3F,
    0x00,0x00,0x03,0x02,0x02,0x02,0x02,0x03,0x10,0x20,0x1F,0x00,/*"向",13*/
    0xC0,0xA0,0x9C,0x88,0x88,0x88,0xFE,0x88,0x88,0x88,0x88,0x88,0x88,0x80,0x00,0x00,
    0x3E,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x3E,0x00,0x00,/*"告",14*/
    0x00,0xFC,0x04,0x04,0xE4,0x24,0x24,0x24,0x24,0xE4,0x04,0x04,0xFC,0x00,0x00,0x3F,
    0x10,0x10,0x13,0x11,0x11,0x11,0x11,0x13,0x10,0x10,0x3F,0x00,/*"回",15*/
    0x08,0x88,0xC8,0x38,0x0E,0x08,0x08,0x08,0x08,0xE8,0x08,0x08,0x08,0x08,0x01,0x00,
    0x3F,0x00,0x20,0x21,0x21,0x21,0x21,0x3F,0x21,0x21,0x21,0x20,/*"在",16*/
    0xC0,0xA0,0x9C,0x90,0x90,0x90,0xFE,0x90,0x90,0x90,0x90,0x90,0x80,0x80,0x20,0x20,
    0x10,0x08,0x04,0x02,0x01,0x02,0x02,0x04,0x08,0x10,0x20,0x20,/*"失",17*/
    0x08,0x08,0x88,0xE8,0x18,0x2E,0x28,0x28,0x28,0xA8,0x68,0x28,0x08,0x08,0x02,0x01,
    0x00,0x3F,0x02,0x02,0x02,0x22,0x22,0x3F,0x02,0x02,0x02,0x02,/*"存",18*/
    0x08,0x28,0x48,0x88,0x78,0x10,0x10,0x90,0x90,0x10,0x10,0xFE,0x10,0x10,0x10,0x08,
    0x06,0x01,0x06,0x00,0x00,0x00,0x00,0x13,0x20,0x1F,0x00,0x00,/*"对",19*/
    0x00,0x08,0x90,0xFE,0x20,0x10,0x88,0x56,0x56,0x24,0x14,0xEC,0x04,0x00,0x02,0x01,
    0x00,0x3F,0x01,0x01,0x02,0x05,0x05,0x11,0x21,0x1F,0x01,0x01,/*"将",20*/
    0x00,0x08,0x08,0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x20,0x20,
    0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x20,0x20,/*"工",21*/
    0x00,0xE4,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0xFC,0x00,0x00,0x00,0x00,0x1F,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x21,0x20,0x3C,0x00,/*"已",22*/
    0x80,0x88,0x88,0x8A,0xFC,0x88,0x88,0x88,0x88,0xFC,0x8A,0x88,0x88,0x80,0x00,0x20,
    0x10,0x0C,0x03,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,/*"并",23*/
    0x00,0x00,0xFC,0x84,0x84,0x94,0x94,0xB6,0xB6,0xD4,0xB4,0x94,0x84,0x84,0x20,0x18,
    0x07,0x00,0x00,0x00,0x10,0x20,0x20,0x1F,0x00,0x00,0x02,0x01,/*"序",24*/
    0x80,0x80,0x84,0x84,0xFC,0x84,0x84,0x84,0x84,0xFC,0x84,0x84,0x80,0x80,0x00,0x20,
    0x10,0x0C,0x03,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,/*"开",25*/
    0x88,0x88,0x48,0x28,0x18,0x2E,0x48,0x08,0x08,0x18,0x28,0x48,0x88,0x88,0x10,0x0C,
    0x00,0x1C,0x20,0x21,0x26,0x20,0x20,0x20,0x38,0x02,0x0C,0x00,/*"态",26*/
    0x08,0x08,0xFE,0x88,0x48,0x44,0x4C,0x34,0x34,0xE4,0x34,0x4C,0x44,0x40,0x11,0x21,
    0x1F,0x00,0x04,0x05,0x05,0x05,0x05,0x3F,0x05,0x05,0x05,0x04,/*"择",27*/
    0x08,0x08,0xFE,0x88,0x48,0x98,0x88,0x8A,0x8A,0xEC,0x88,0x88,0x88,0x98,0x11,0x21,
    0x1F,0x00,0x00,0x20,0x22,0x15,0x15,0x08,0x0C,0x13,0x20,0x20,/*"按",28*/
    0x08,0x08,0xFE,0x88,0x48,0x80,0xBE,0xAA,0xAA,0xAA,0xAA,0xAA,0xBE,0x80,0x11,0x21,
    0x1F,0x00,0x20,0x10,0x0E,0x10,0x10,0x3F,0x24,0x24,0x24,0x20,/*"提",29*/
    0x08,0x08,0xFE,0x88,0x90,0x54,0x3C,0x14,0x14,0xFC,0x12,0x3A,0x56,0x90,0x11,0x21,
    0x1F,0x00,0x00,0x3F,0x15,0x15,0x15,0x1F,0x15,0x15,0x3F,0x00,/*"播",30*/
    0x08,0x08,0xFA,0x4C,0x48,0xE8,0x28,0x70,0x70,0x8E,0x08,0x88,0x78,0x08,0x20,0x18,
    0x07,0x10,0x20,0x1F,0x20,0x10,0x10,0x09,0x06,0x09,0x10,0x20,/*"放",31*/
    0x4A,0x2C,0x98,0x7E,0x18,0x2C,0x4A,0x30,0x30,0xCE,0x08,0x88,0x78,0x08,0x21,0x25,
    0x17,0x09,0x15,0x23,0x21,0x10,0x10,0x09,0x06,0x09,0x10,0x20,/*"数",32*/
    0x08,0x08,0x08,0x38,0xC8,0x0A,0x0C,0x08,0x08,0xC8,0x38,0x08,0x08,0x08,0x20,0x20,
    0x20,0x10,0x08,0x05,0x02,0x05,0x05,0x08,0x10,0x20,0x20,0x20,/*"文",33*/
    0x00,0x00,0x7C,0x54,0x54,0xD4,0x54,0xD4,0xD4,0x54,0x54,0x7C,0x00,0x00,0x20,0x21,
    0x22,0x2C,0x20,0x3F,0x20,0x3F,0x3F,0x20,0x28,0x24,0x23,0x20,/*"显",34*/
    0x04,0x04,0xF4,0x54,0x54,0x54,0x54,0xFC,0xFC,0x54,0x54,0xF4,0x04,0x04,0x20,0x20,
    0x21,0x23,0x15,0x09,0x15,0x13,0x13,0x21,0x21,0x21,0x20,0x20,/*"更",35*/
    0x08,0x08,0x08,0x88,0x48,0x28,0xFE,0x28,0x28,0x48,0x88,0x08,0x08,0x08,0x04,0x02,
    0x01,0x04,0x04,0x04,0x3F,0x04,0x04,0x04,0x04,0x01,0x02,0x04,/*"本",36*/
    0x10,0x10,0xD0,0xFE,0x50,0x90,0x00,0xFC,0xFC,0x04,0x04,0xFC,0x00,0x00,0x04,0x03,
    0x00,0x3F,0x00,0x20,0x18,0x07,0x07,0x00,0x00,0x1F,0x20,0x38,/*"机",37*/
    0x00,0x00,0xE0,0x00,0x00,0x00,0xFE,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x20,0x20,
    0x3F,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x20,0x20,/*"止",38*/
    0x04,0x04,0xC4,0x04,0x04,0x04,0xFC,0x84,0x84,0x84,0x84,0x84,0x84,0x04,0x20,0x20,
    0x3F,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x20,0x20,/*"正",39*/
    0x10,0x10,0x50,0x90,0x10,0x10,0xFE,0x10,0x10,0x10,0x92,0x54,0x10,0x10,0x10,0x10,
    0x08,0x04,0x12,0x21,0x1F,0x01,0x01,0x02,0x04,0x08,0x10,0x10,/*"求",40*/
    0x10,0x22,0x84,0x00,0x44,0x64,0x54,0x4E,0x4E,0x44,0x44,0x64,0xC4,0x04,0x02,0x3E,
    0x01,0x20,0x10,0x0F,0x00,0x1F,0x1F,0x00,0x1F,0x20,0x20,0x3C,/*"流",41*/
    0x10,0x22,0x84,0x40,0xFC,0x04,0xF4,0x54,0x54,0x5C,0x54,0x54,0xF4,0x04,0x02,0x3E,
    0x21,0x18,0x07,0x10,0x0D,0x11,0x11,0x21,0x1F,0x01,0x05,0x18,/*"源",42*/
    0x48,0x48,0xFE,0x28,0x00,0x28,0xC8,0x7E,0x7E,0x88,0x08,0xF8,0x00,0x00,0x21,0x1A,
    0x01,0x00,0x0A,0x31,0x00,0x08,0x08,0x31,0x00,0x09,0x32,0x07,/*"热",43*/
    0x00,0xFC,0x20,0x20,0x3E,0x20,0xFC,0x24,0x24,0x24,0x22,0x22,0xE2,0x00,0x30,0x0F,
    0x01,0x01,0x3F,0x10,0x2F,0x21,0x21,0x12,0x0C,0x13,0x20,0x20,/*"版",44*/
    0x02,0x32,0x2A,0x22,0x22,0xA2,0x22,0xFE,0xFE,0x22,0x22,0x22,0x22,0x00,0x08,0x08,
    0x04,0x02,0x01,0x10,0x20,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,/*"牙",45*/
    0x08,0x10,0x80,0xFE,0x10,0x10,0x10,0x10,0x10,0xFE,0x10,0x12,0x14,0x10,0x02,0x01,
    0x00,0x3F,0x20,0x10,0x0C,0x03,0x03,0x00,0x03,0x0C,0x10,0x20,/*"状",46*/
    0xF8,0x48,0x48,0x48,0xFE,0x48,0x48,0x48,0x48,0x48,0xF8,0x00,0x00,0x00,0x03,0x02,
    0x02,0x02,0x1F,0x22,0x22,0x22,0x22,0x22,0x23,0x20,0x3C,0x00,/*"电",47*/
    0x24,0xA4,0xFC,0xA2,0x22,0x80,0xBC,0xA4,0xA4,0xA4,0xA4,0xA4,0xBC,0x00,0x06,0x01,
    0x3F,0x00,0x01,0x20,0x24,0x24,0x24,0x3F,0x24,0x24,0x24,0x20,/*"程",48*/
    0x20,0x2E,0x2A,0xEA,0xAE,0xAA,0xBA,0xAA,0xAA,0xAE,0xEA,0x2A,0x2E,0x20,0x20,0x20,
    0x20,0x3F,0x2A,0x2A,0x2A,0x2A,0x2A,0x2A,0x3F,0x20,0x20,0x20,/*"置",49*/
    0x10,0xD8,0x56,0x50,0x54,0xD8,0x10,0x3E,0x3E,0x48,0x48,0x44,0x44,0x70,0x00,0x3F,
    0x05,0x05,0x25,0x3F,0x00,0x1F,0x1F,0x24,0x24,0x22,0x22,0x38,/*"能",50*/
    0x84,0x84,0xA4,0xA4,0xAE,0xA4,0xF4,0xA4,0xA4,0xEE,0xA4,0xB4,0x84,0x84,0x08,0x08,
    0x04,0x3E,0x2A,0x2B,0x2A,0x2A,0x2A,0x2A,0x3E,0x00,0x00,0x00,/*"著",51*/
    0x04,0xE4,0x04,0x04,0xFE,0x04,0x84,0x74,0x74,0x2E,0x64,0xA4,0x24,0x04,0x20,0x20,
    0x3E,0x22,0x23,0x3E,0x22,0x3E,0x3E,0x22,0x22,0x3E,0x20,0x20,/*"蓝",52*/
    0x90,0x48,0xE4,0x12,0x00,0x20,0x24,0x24,0x24,0x24,0xE4,0x24,0x24,0x20,0x00,0x00,
    0x3F,0x00,0x00,0x00,0x00,0x10,0x10,0x20,0x1F,0x00,0x00,0x00,/*"行",53*/
    0x08,0x08,0xA8,0xA8,0xA8,0xAA,0xAC,0xA8,0xA8,0xA8,0xA8,0xA8,0x08,0x08,0x00,0x00,
    0x3E,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x3E,0x00,0x00,/*"言",54*/
    0x92,0x8A,0xBE,0xAA,0xBA,0xCE,0xBA,0x88,0x88,0xC6,0xAC,0x94,0xAC,0xC4,0x00,0x00,
    0x3A,0x2A,0x2A,0x2A,0x2A,0x2A,0x2A,0x2A,0x2A,0x3A,0x00,0x00,/*"警",55*/
    0x20,0x22,0xEC,0x00,0x40,0xA0,0x9E,0x82,0x82,0x82,0x82,0x9E,0xA0,0x20,0x00,0x00,
    0x1F,0x08,0x24,0x20,0x11,0x0A,0x0A,0x04,0x0A,0x11,0x20,0x20,/*"设",56*/
    0x20,0x22,0xEC,0x00,0x84,0x94,0x94,0xF4,0xF4,0x9C,0x94,0x94,0xF4,0x84,0x00,0x00,
    0x1F,0x08,0x04,0x3E,0x12,0x12,0x12,0x12,0x12,0x12,0x3E,0x00,/*"语",57*/
    0x20,0x22,0xEC,0x00,0x44,0x54,0xD4,0x54,0x54,0x7E,0x54,0x54,0xD4,0x44,0x00,0x00,
    0x1F,0x08,0x04,0x00,0x3F,0x05,0x05,0x05,0x05,0x25,0x3F,0x00,/*"请",58*/
    0xFC,0x04,0xF4,0x04,0xFC,0x40,0x20,0x5E,0x5E,0x88,0x08,0x88,0x78,0x08,0x23,0x18,
    0x07,0x08,0x13,0x00,0x20,0x10,0x10,0x09,0x06,0x09,0x10,0x20,/*"败",59*/
    0x68,0x58,0xEE,0x48,0x48,0x48,0x20,0x10,0x10,0xC8,0x06,0x08,0x90,0x20,0x04,0x04,
    0x3F,0x02,0x02,0x02,0x00,0x00,0x00,0x1F,0x22,0x21,0x20,0x3C,/*"轮",60*/
    0x50,0x54,0xD4,0x7E,0x54,0x54,0x50,0x10,0x10,0xFE,0x10,0x14,0xD8,0x10,0x08,0x0B,
    0x0A,0x3F,0x0A,0x0A,0x28,0x10,0x10,0x09,0x06,0x0B,0x10,0x3C,/*"载",61*/
    0x20,0x22,0xEC,0x00,0x20,0x24,0xA4,0x64,0x64,0x24,0x24,0x24,0x20,0x20,0x20,0x10,
    0x0F,0x10,0x24,0x26,0x25,0x24,0x24,0x24,0x25,0x26,0x2C,0x20,/*"运",62*/
    0x40,0x42,0xCC,0x00,0x00,0xFC,0x24,0xE4,0xE4,0x24,0x24,0x22,0xE2,0x00,0x20,0x10,
    0x0F,0x10,0x2C,0x23,0x30,0x28,0x28,0x25,0x22,0x25,0x28,0x30,/*"返",63*/
    0x20,0x22,0xEC,0x00,0x50,0x4C,0xC8,0x48,0x48,0x7E,0xC8,0x48,0x48,0x40,0x20,0x10,
    0x0F,0x10,0x28,0x26,0x21,0x20,0x20,0x20,0x27,0x28,0x28,0x2E,/*"选",64*/
    0xE4,0x24,0xFC,0x24,0xFC,0x24,0xE4,0x00,0x00,0xC4,0x44,0x44,0x7C,0x00,0x3F,0x15,
    0x14,0x14,0x14,0x15,0x3F,0x00,0x00,0x1F,0x20,0x20,0x20,0x3C,/*"配",65*/
    0x04,0x04,0x04,0x74,0x54,0x54,0x56,0x54,0x54,0x54,0x74,0x04,0x04,0x04,0x00,0x3F,
    0x01,0x1D,0x15,0x15,0x15,0x15,0x15,0x15,0x1D,0x21,0x3F,0x00,/*"高",66*/
    0x40,0x40,0x40,0x78,0x40,0x40,0xC0,0x7E,0x7E,0x48,0x48,0x48,0x40,0x40,0x00,0x3F,
    0x20,0x28,0x24,0x22,0x21,0x22,0x22,0x24,0x28,0x20,0x3F,0x00,/*"齿",67*/
};

#endif
