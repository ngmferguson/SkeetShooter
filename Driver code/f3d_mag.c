
#include <f3d_i2c.h>
#include <f3d_mag.h>
#include <math.h>
#include <stdio.h>

/// Init's our board's compass
void f3d_mag_init() {
  // MAG I2C Address = 0x3C 

  uint8_t value = 0; 
 
  value = 0x14;                  //Temp sensor disable,30Hz Output Rate 
  f3d_i2c1_write(0x3C, 0x00,  &value); // Mag (0x3C), CRA (0x00) 

  value = 0xE0;                      // +/- 8.1 Gauss Full Scale
  f3d_i2c1_write(0x3C, 0x01, &value); // Mag (0x3C), CRB (0x01)

  value = 0x00;                      // Continuous Conversion
  f3d_i2c1_write(0x3C, 0x02, &value); // Mag (0x3C), MR  (0x23)
}

void f3d_mag_read(float *mag_data) {
  uint8_t buffer[6];
  int i;
  
  f3d_i2c1_read(0x3C, 0x03, buffer,2);   // Read X Axis
  f3d_i2c1_read(0x3C, 0x07, buffer+2,2); // Read Y Axis
  f3d_i2c1_read(0x3C, 0x05, buffer+4,2); // Read Z Axis (notice that Z is out of order in the chip). 
  
  for (i=0; i<2; i++) {
    mag_data[i]=(float)((int16_t)(((uint16_t)buffer[2*i] << 8) + buffer[2*i+1]))/230;
  }
  mag_data[2]=(float)((int16_t)(((uint16_t)buffer[4] << 8) + buffer[5]))/205;
}

/// Compensates our reading with board tilt.
void f3d_mag_compensate(float *mag_data, float pitch, float roll, float *output){
  output[0] = mag_data[0] * cos(pitch) + mag_data[2] * sin(pitch);
  output[1] = mag_data[0] * (sin(roll) * sin(pitch)) + mag_data[1] * cos(roll) - mag_data[2] * (sin(roll) * cos(pitch));
}




float inline f3d_mag_calculate_heading(float *mag_data){

  return 180.0 + atan2(mag_data[1],mag_data[0])*180.0f/M_PI;

}



/* f3d_mag.c ends here */
