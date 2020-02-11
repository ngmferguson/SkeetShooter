#include <stdint.h>

const uint8_t ASCII[] = {
  0x00, 0x00, 0x00, 0x00, 0x00,  // 0 
  0x3E, 0x5B, 0x4F, 0x5B, 0x3E,  // 1 
  0x3E, 0x6B, 0x4F, 0x6B, 0x3E,  // 2 
  0x1C, 0x3E, 0x7C, 0x3E, 0x1C,  // 3 
  0x18, 0x3C, 0x7E, 0x3C, 0x18,  // 4 
  0x1C, 0x57, 0x7D, 0x57, 0x1C,  // 5 
  0x1C, 0x5E, 0x7F, 0x5E, 0x1C,  // 6 
  0x00, 0x18, 0x3C, 0x18, 0x00,  // 7 
  0xFF, 0xE7, 0xC3, 0xE7, 0xFF,  // 8 
  0x00, 0x18, 0x24, 0x18, 0x00,  // 9 
  0xFF, 0xE7, 0xDB, 0xE7, 0xFF,  // 10
  0x30, 0x48, 0x3A, 0x06, 0x0E,  // 11
  0x26, 0x29, 0x79, 0x29, 0x26,  // 12
  0x40, 0x7F, 0x05, 0x05, 0x07,  // 13
  0x40, 0x7F, 0x05, 0x25, 0x3F,  // 14
  0x5A, 0x3C, 0xE7, 0x3C, 0x5A,  // 15
  0x7F, 0x3E, 0x1C, 0x1C, 0x08,  // 16
  0x08, 0x1C, 0x1C, 0x3E, 0x7F,  // 17
  0x14, 0x22, 0x7F, 0x22, 0x14,  // 18
  0x5F, 0x5F, 0x00, 0x5F, 0x5F,  // 19
  0x06, 0x09, 0x7F, 0x01, 0x7F,  // 20
  0x00, 0x66, 0x89, 0x95, 0x6A,  // 21
  0x60, 0x60, 0x60, 0x60, 0x60,  // 22
  0x94, 0xA2, 0xFF, 0xA2, 0x94,  // 23
  0x08, 0x04, 0x7E, 0x04, 0x08,  // 24
  0x10, 0x20, 0x7E, 0x20, 0x10,  // 25
  0x08, 0x08, 0x2A, 0x1C, 0x08,  // 26
  0x08, 0x1C, 0x2A, 0x08, 0x08,  // 27
  0x1E, 0x10, 0x10, 0x10, 0x10,  // 28
  0x0C, 0x1E, 0x0C, 0x1E, 0x0C,  // 29
  0x30, 0x38, 0x3E, 0x38, 0x30,  // 30
  0x06, 0x0E, 0x3E, 0x0E, 0x06,  // 31
  0x00, 0x00, 0x00, 0x00, 0x00,  // 32 space
  0x00, 0x00, 0x5F, 0x00, 0x00,  // 33 !
  0x00, 0x07, 0x00, 0x07, 0x00,  // 34 "
  0x14, 0x7F, 0x14, 0x7F, 0x14,  // 35 #
  0x24, 0x2A, 0x7F, 0x2A, 0x12,  // 36 $
  0x23, 0x13, 0x08, 0x64, 0x62,  // 37 %
  0x36, 0x49, 0x56, 0x20, 0x50,  // 38 &
  0x00, 0x08, 0x07, 0x03, 0x00,  // 39 '
  0x00, 0x1C, 0x22, 0x41, 0x00,  // 40 (
  0x00, 0x41, 0x22, 0x1C, 0x00,  // 41 )
  0x2A, 0x1C, 0x7F, 0x1C, 0x2A,  // 42 *
  0x08, 0x08, 0x3E, 0x08, 0x08,  // 43 +
  0x00, 0x80, 0x70, 0x30, 0x00,  // 44 ,
  0x08, 0x08, 0x08, 0x08, 0x08,  // 45 -
  0x00, 0x00, 0x60, 0x60, 0x00,  // 46 .
  0x20, 0x10, 0x08, 0x04, 0x02,  // 47 /
  0x3E, 0x51, 0x49, 0x45, 0x3E,  // 48 0
  0x00, 0x42, 0x7F, 0x40, 0x00,  // 49 1
  0x72, 0x49, 0x49, 0x49, 0x46,  // 50 2
  0x21, 0x41, 0x49, 0x4D, 0x33,  // 51 3
  0x18, 0x14, 0x12, 0x7F, 0x10,  // 52 4
  0x27, 0x45, 0x45, 0x45, 0x39,  // 53 5
  0x3C, 0x4A, 0x49, 0x49, 0x31,  // 54 6
  0x41, 0x21, 0x11, 0x09, 0x07,  // 55 7
  0x36, 0x49, 0x49, 0x49, 0x36,  // 56 8
  0x46, 0x49, 0x49, 0x29, 0x1E,  // 57 9
  0x00, 0x00, 0x14, 0x00, 0x00,  // 58 :
  0x00, 0x40, 0x34, 0x00, 0x00,  // 59 ;
  0x00, 0x08, 0x14, 0x22, 0x41,  // 60 <
  0x14, 0x14, 0x14, 0x14, 0x14,  // 61 =
  0x00, 0x41, 0x22, 0x14, 0x08,  // 62 >
  0x02, 0x01, 0x59, 0x09, 0x06,  // 63 ?
  0x3E, 0x41, 0x5D, 0x59, 0x4E,  // 64 @
  0x7C, 0x12, 0x11, 0x12, 0x7C,  // 65 A
  0x7F, 0x49, 0x49, 0x49, 0x36,  // 66 B
  0x3E, 0x41, 0x41, 0x41, 0x22,  // 67 C
  0x7F, 0x41, 0x41, 0x41, 0x3E,  // 68 D
  0x7F, 0x49, 0x49, 0x49, 0x41,  // 69 E
  0x7F, 0x09, 0x09, 0x09, 0x01,  // 70 F
  0x3E, 0x41, 0x41, 0x51, 0x73, 
  0x7F, 0x08, 0x08, 0x08, 0x7F, 
  0x00, 0x41, 0x7F, 0x41, 0x00, 
  0x20, 0x40, 0x41, 0x3F, 0x01, 
  0x7F, 0x08, 0x14, 0x22, 0x41, 
  0x7F, 0x40, 0x40, 0x40, 0x40, 
  0x7F, 0x02, 0x1C, 0x02, 0x7F, 
  0x7F, 0x04, 0x08, 0x10, 0x7F, 
  0x3E, 0x41, 0x41, 0x41, 0x3E, 
  0x7F, 0x09, 0x09, 0x09, 0x06, 
  0x3E, 0x41, 0x51, 0x21, 0x5E, 
  0x7F, 0x09, 0x19, 0x29, 0x46, 
  0x26, 0x49, 0x49, 0x49, 0x32, 
  0x03, 0x01, 0x7F, 0x01, 0x03, 
  0x3F, 0x40, 0x40, 0x40, 0x3F, 
  0x1F, 0x20, 0x40, 0x20, 0x1F, 
  0x3F, 0x40, 0x38, 0x40, 0x3F, 
  0x63, 0x14, 0x08, 0x14, 0x63, 
  0x03, 0x04, 0x78, 0x04, 0x03, 
  0x61, 0x59, 0x49, 0x4D, 0x43, 
  0x00, 0x7F, 0x41, 0x41, 0x41, 
  0x02, 0x04, 0x08, 0x10, 0x20, 
  0x00, 0x41, 0x41, 0x41, 0x7F, 
  0x04, 0x02, 0x01, 0x02, 0x04, 
  0x40, 0x40, 0x40, 0x40, 0x40, 
  0x00, 0x03, 0x07, 0x08, 0x00, 
  0x20, 0x54, 0x54, 0x78, 0x40, 
  0x7F, 0x28, 0x44, 0x44, 0x38, 
  0x38, 0x44, 0x44, 0x44, 0x28, 
  0x38, 0x44, 0x44, 0x28, 0x7F, 
  0x38, 0x54, 0x54, 0x54, 0x18, 
  0x00, 0x08, 0x7E, 0x09, 0x02, 
  0x18, 0xA4, 0xA4, 0x9C, 0x78, 
  0x7F, 0x08, 0x04, 0x04, 0x78, 
  0x00, 0x44, 0x7D, 0x40, 0x00, 
  0x20, 0x40, 0x40, 0x3D, 0x00, 
  0x7F, 0x10, 0x28, 0x44, 0x00, 
  0x00, 0x41, 0x7F, 0x40, 0x00, 
  0x7C, 0x04, 0x78, 0x04, 0x78, 
  0x7C, 0x08, 0x04, 0x04, 0x78, 
  0x38, 0x44, 0x44, 0x44, 0x38, 
  0xFC, 0x18, 0x24, 0x24, 0x18, 
  0x18, 0x24, 0x24, 0x18, 0xFC, 
  0x7C, 0x08, 0x04, 0x04, 0x08, 
  0x48, 0x54, 0x54, 0x54, 0x24, 
  0x04, 0x04, 0x3F, 0x44, 0x24, 
  0x3C, 0x40, 0x40, 0x20, 0x7C, 
  0x1C, 0x20, 0x40, 0x20, 0x1C, 
  0x3C, 0x40, 0x30, 0x40, 0x3C, 
  0x44, 0x28, 0x10, 0x28, 0x44, 
  0x4C, 0x90, 0x90, 0x90, 0x7C, 
  0x44, 0x64, 0x54, 0x4C, 0x44, 
  0x00, 0x08, 0x36, 0x41, 0x00, 
  0x00, 0x00, 0x77, 0x00, 0x00, 
  0x00, 0x41, 0x36, 0x08, 0x00, 
  0x02, 0x01, 0x02, 0x04, 0x02, 
  0x3C, 0x26, 0x23, 0x26, 0x3C, 
  0x1E, 0xA1, 0xA1, 0x61, 0x12, 
  0x3A, 0x40, 0x40, 0x20, 0x7A, 
  0x38, 0x54, 0x54, 0x55, 0x59, 
  0x21, 0x55, 0x55, 0x79, 0x41, 
  0x21, 0x54, 0x54, 0x78, 0x41, 
  0x21, 0x55, 0x54, 0x78, 0x40, 
  0x20, 0x54, 0x55, 0x79, 0x40, 
  0x0C, 0x1E, 0x52, 0x72, 0x12, 
  0x39, 0x55, 0x55, 0x55, 0x59, 
  0x39, 0x54, 0x54, 0x54, 0x59, 
  0x39, 0x55, 0x54, 0x54, 0x58, 
  0x00, 0x00, 0x45, 0x7C, 0x41, 
  0x00, 0x02, 0x45, 0x7D, 0x42, 
  0x00, 0x01, 0x45, 0x7C, 0x40, 
  0xF0, 0x29, 0x24, 0x29, 0xF0, 
  0xF0, 0x28, 0x25, 0x28, 0xF0, 
  0x7C, 0x54, 0x55, 0x45, 0x00, 
  0x20, 0x54, 0x54, 0x7C, 0x54, 
  0x7C, 0x0A, 0x09, 0x7F, 0x49, 
  0x32, 0x49, 0x49, 0x49, 0x32, 
  0x32, 0x48, 0x48, 0x48, 0x32, 
  0x32, 0x4A, 0x48, 0x48, 0x30, 
  0x3A, 0x41, 0x41, 0x21, 0x7A, 
  0x3A, 0x42, 0x40, 0x20, 0x78, 
  0x00, 0x9D, 0xA0, 0xA0, 0x7D, 
  0x39, 0x44, 0x44, 0x44, 0x39, 
  0x3D, 0x40, 0x40, 0x40, 0x3D, 
  0x3C, 0x24, 0xFF, 0x24, 0x24, 
  0x48, 0x7E, 0x49, 0x43, 0x66, 
  0x2B, 0x2F, 0xFC, 0x2F, 0x2B, 
  0xFF, 0x09, 0x29, 0xF6, 0x20, 
  0xC0, 0x88, 0x7E, 0x09, 0x03, 
  0x20, 0x54, 0x54, 0x79, 0x41, 
  0x00, 0x00, 0x44, 0x7D, 0x41, 
  0x30, 0x48, 0x48, 0x4A, 0x32, 
  0x38, 0x40, 0x40, 0x22, 0x7A, 
  0x00, 0x7A, 0x0A, 0x0A, 0x72, 
  0x7D, 0x0D, 0x19, 0x31, 0x7D, 
  0x26, 0x29, 0x29, 0x2F, 0x28, 
  0x26, 0x29, 0x29, 0x29, 0x26, 
  0x30, 0x48, 0x4D, 0x40, 0x20, 
  0x38, 0x08, 0x08, 0x08, 0x08, 
  0x08, 0x08, 0x08, 0x08, 0x38, 
  0x2F, 0x10, 0xC8, 0xAC, 0xBA, 
  0x2F, 0x10, 0x28, 0x34, 0xFA, 
  0x00, 0x00, 0x7B, 0x00, 0x00, 
  0x08, 0x14, 0x2A, 0x14, 0x22, 
  0x22, 0x14, 0x2A, 0x14, 0x08, 
  0xAA, 0x00, 0x55, 0x00, 0xAA, 
  0xAA, 0x55, 0xAA, 0x55, 0xAA, 
  0x00, 0x00, 0x00, 0xFF, 0x00, 
  0x10, 0x10, 0x10, 0xFF, 0x00, 
  0x14, 0x14, 0x14, 0xFF, 0x00, 
  0x10, 0x10, 0xFF, 0x00, 0xFF, 
  0x10, 0x10, 0xF0, 0x10, 0xF0, 
  0x14, 0x14, 0x14, 0xFC, 0x00, 
  0x14, 0x14, 0xF7, 0x00, 0xFF, 
  0x00, 0x00, 0xFF, 0x00, 0xFF, 
  0x14, 0x14, 0xF4, 0x04, 0xFC, 
  0x14, 0x14, 0x17, 0x10, 0x1F, 
  0x10, 0x10, 0x1F, 0x10, 0x1F, 
  0x14, 0x14, 0x14, 0x1F, 0x00, 
  0x10, 0x10, 0x10, 0xF0, 0x00, 
  0x00, 0x00, 0x00, 0x1F, 0x10, 
  0x10, 0x10, 0x10, 0x1F, 0x10, 
  0x10, 0x10, 0x10, 0xF0, 0x10, 
  0x00, 0x00, 0x00, 0xFF, 0x10, 
  0x10, 0x10, 0x10, 0x10, 0x10, 
  0x10, 0x10, 0x10, 0xFF, 0x10, 
  0x00, 0x00, 0x00, 0xFF, 0x14, 
  0x00, 0x00, 0xFF, 0x00, 0xFF, 
  0x00, 0x00, 0x1F, 0x10, 0x17, 
  0x00, 0x00, 0xFC, 0x04, 0xF4, 
  0x14, 0x14, 0x17, 0x10, 0x17, 
  0x14, 0x14, 0xF4, 0x04, 0xF4, 
  0x00, 0x00, 0xFF, 0x00, 0xF7, 
  0x14, 0x14, 0x14, 0x14, 0x14, 
  0x14, 0x14, 0xF7, 0x00, 0xF7, 
  0x14, 0x14, 0x14, 0x17, 0x14, 
  0x10, 0x10, 0x1F, 0x10, 0x1F, 
  0x14, 0x14, 0x14, 0xF4, 0x14, 
  0x10, 0x10, 0xF0, 0x10, 0xF0, 
  0x00, 0x00, 0x1F, 0x10, 0x1F, 
  0x00, 0x00, 0x00, 0x1F, 0x14, 
  0x00, 0x00, 0x00, 0xFC, 0x14, 
  0x00, 0x00, 0xF0, 0x10, 0xF0, 
  0x10, 0x10, 0xFF, 0x10, 0xFF, 
  0x14, 0x14, 0x14, 0xFF, 0x14, 
  0x10, 0x10, 0x10, 0x1F, 0x00, 
  0x00, 0x00, 0x00, 0xF0, 0x10, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 
  0xFF, 0xFF, 0xFF, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xFF, 0xFF, 
  0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 
  0x38, 0x44, 0x44, 0x38, 0x44, 
  0x7C, 0x2A, 0x2A, 0x3E, 0x14, 
  0x7E, 0x02, 0x02, 0x06, 0x06, 
  0x02, 0x7E, 0x02, 0x7E, 0x02, 
  0x63, 0x55, 0x49, 0x41, 0x63, 
  0x38, 0x44, 0x44, 0x3C, 0x04, 
  0x40, 0x7E, 0x20, 0x1E, 0x20, 
  0x06, 0x02, 0x7E, 0x02, 0x02, 
  0x99, 0xA5, 0xE7, 0xA5, 0x99, 
  0x1C, 0x2A, 0x49, 0x2A, 0x1C, 
  0x4C, 0x72, 0x01, 0x72, 0x4C, 
  0x30, 0x4A, 0x4D, 0x4D, 0x30, 
  0x30, 0x48, 0x78, 0x48, 0x30, 
  0xBC, 0x62, 0x5A, 0x46, 0x3D, 
  0x3E, 0x49, 0x49, 0x49, 0x00, 
  0x7E, 0x01, 0x01, 0x01, 0x7E, 
  0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 
  0x44, 0x44, 0x5F, 0x44, 0x44, 
  0x40, 0x51, 0x4A, 0x44, 0x40, 
  0x40, 0x44, 0x4A, 0x51, 0x40, 
  0x00, 0x00, 0xFF, 0x01, 0x03, 
  0xE0, 0x80, 0xFF, 0x00, 0x00, 
  0x08, 0x08, 0x6B, 0x6B, 0x08,
  0x36, 0x12, 0x36, 0x24, 0x36, 
  0x06, 0x0F, 0x09, 0x0F, 0x06, 
  0x00, 0x00, 0x18, 0x18, 0x00, 
  0x00, 0x00, 0x10, 0x10, 0x00, 
  0x30, 0x40, 0xFF, 0x01, 0x01, 
  0x00, 0x1F, 0x01, 0x01, 0x1E, 
  0x00, 0x19, 0x1D, 0x17, 0x12, 
  0x00, 0x3C, 0x3C, 0x3C, 0x3C, 
  0x00, 0x00, 0x00, 0x00, 0x00, 
};
