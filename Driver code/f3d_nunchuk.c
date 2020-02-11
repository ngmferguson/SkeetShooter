
#include <f3d_i2c.h>
#include <f3d_i2c2.h>
#include <f3d_nunchuk.h>
#include <f3d_uart.h>
#include <stdlib.h>
#include <stdio.h>


#define NUNCHUK_ADDRESS 0xA4

void f3d_nunchuk_init(void) {
  printf("begin nunchuk inits\n\n");
  uint8_t realb = 0x00;
  uint8_t buf = 0x55;
  uint8_t buf2 = 0x00;
  uint8_t buf3 = 0x55;
  uint8_t buf4 = 0x00;
  ///NUNCHUK 1 INITS
  /// Uncomment corresponding lines for a nintendo 1st party controller or a 3rd party knockoff
  // Nintendo
  f3d_i2c1_write(NUNCHUK_ADDRESS,0x40,&realb);
  // Knockoff
  //f3d_i2c1_write(NUNCHUK_ADDRESS,0xf0,&buf); 
  //f3d_i2c1_write(NUNCHUK_ADDRESS,0xfb,&buf2);
  printf("nun1 works\n");                       // Verification
  ///NUNCHUK 2 INITS
  /// Uncomment corresponding lines for a nintendo 1st party controller or a 3rd party knockoff
  /// Only uncomment if we are using multiple controllers
  //Nintendo
  //f3d_i2c2_write(NUNCHUK_ADDRESS, 0x40, buf4);
  //Knockoff
  //f3d_i2c2_write(NUNCHUK_ADDRESS,0xf0,&buf3);
  //f3d_i2c2_write(NUNCHUK_ADDRESS,0xfb,&buf4);
  //printf("nun2 works\n");                     // Verification, used to see if Nunchuk 1 or 2 failed to init (they fail often)
}

/// Reads data from our nunchuk
/// such as tilt, joystick, and button inputs
void f3d_nunchuk_read(nunchuk_t *n) {
  uint8_t data[6] = {0,0,0,0,0,0};
  int i;
  unsigned short tmp;

  f3d_i2c1_read_nunchuk(0xA5, data, 6);
  n->jx = data[0];
  n->jy = data[1];

  tmp = data[2];
  tmp = tmp << 2;
  n->ax = tmp | ((data[5] & 0x0C) >> 2);

  tmp = data[3];
  tmp = tmp << 2;
  n->ay = tmp | ((data[5] & 0x30) >> 4);

  tmp = data[4];
  tmp = tmp << 2;
  n->az = tmp | ((data[5] & 0xC0) >> 6);

  switch (data[5] & 0x03) {
  case 2:
    n->z = 1;
    n->c = 0;
    break;
  case 1:
    n->z = 0;
    n->c = 1;
    break;
  case 0:
    n->z = 1;
    n->c = 1;
    break;
  case 3:
    n->z = 0;
    n->c = 0;
    break;
  }
}

/// Reads our second, optional nunchuk
void f3d_nunchuk_read2(nunchuk_t *n) {
  uint8_t data[6] = {0,0,0,0,0,0};
  int i;
  unsigned short tmp;

  f3d_i2c2_read_nunchuk(0xA5, data, 6);
  n->jx = data[0];
  n->jy = data[1];

  tmp = data[2];
  tmp = tmp << 2;
  n->ax = tmp | ((data[5] & 0x0C) >> 2);

  tmp = data[3];
  tmp = tmp << 2;
  n->ay = tmp | ((data[5] & 0x30) >> 4);

  tmp = data[4];
  tmp = tmp << 2;
  n->az = tmp | ((data[5] & 0xC0) >> 6);

  switch (data[5] & 0x03) {
  case 2:
    n->z = 1;
    n->c = 0;
    break;
  case 1:
    n->z = 0;
    n->c = 1;
    break;
  case 0:
    n->z = 1;
    n->c = 1;
    break;
  case 3:
    n->z = 0;
    n->c = 0;
    break;
  }
}

/* f3d_nunchuk.c ends here */
