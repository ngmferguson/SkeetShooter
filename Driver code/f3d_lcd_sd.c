//Authos: Nathaniel Ferguson and Will Smith
/* Code: */
#include <f3d_lcd_sd.h>
#include <f3d_delay.h>
#include <glcdfont.h>
#include <bmp.h>
#include <math.h>
#include <stdio.h>
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))
#define max(X,Y) (((X) > (Y)) ? (X) : (Y))


static uint8_t madctlcurrent = MADVAL(MADCTLGRAPHICS);

void f3d_lcd_sd_interface_init(void) {
  /* vvvvvvvvvvv pin initialization for the LCD goes here vvvvvvvvvv*/ 

  //OUT inits
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  //AF inits
  GPIO_InitTypeDef GPIO_InitStructureAF;
  //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  GPIO_StructInit(&GPIO_InitStructureAF);
  GPIO_InitStructureAF.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructureAF.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructureAF.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructureAF.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructureAF.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB,&GPIO_InitStructureAF);

  //Setting alternate functions
  GPIO_PinAFConfig(GPIOB, 13, GPIO_AF_5);
  
  GPIO_PinAFConfig(GPIOB, 14, GPIO_AF_5);

  GPIO_PinAFConfig(GPIOB, 15, GPIO_AF_5);
  
  LCD_CS_DEASSERT();
  SD_CS_HIGH();
  
  
  /* ^^^^^^^^^^^ pin initialization for the LCD goes here ^^^^^^^^^^ */
 
  // Section 4.1 SPI2 configuration
  // Note: you will need to add some code in the last three functions
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 , ENABLE);
  SPI_InitTypeDef SPI_InitStructure;
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPI2, &SPI_InitStructure);
  SPI_RxFIFOThresholdConfig(SPI2, SPI_RxFIFOThreshold_QF);
  SPI_Cmd(SPI2, ENABLE);

  // LAB 11 UNDER HERE
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  
} 


struct lcd_cmdBuf {
  uint8_t command;
  uint8_t delay;
  uint8_t len;
  uint8_t data [16];
};

static const struct lcd_cmdBuf initializers[] = {
  // SWRESET Software reset
  { 0x01, 150, 0, 0},
  // SLPOUT Leave sleep mode
  { 0x11, 150, 0, 0},
  // FRMCTR1, FRMCTR2 Frame Rate configuration -- Normal mode, idle
  // frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
  { 0xB1, 0, 3, { 0x01, 0x2C, 0x2D }},
  { 0xB2, 0, 3, { 0x01, 0x2C, 0x2D }},
  // FRMCTR3 Frame Rate configureation -- partial mode
  { 0xB3, 0, 6, { 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D }},
  // INVCTR Display inversion (no inversion)
  { 0xB4, 0, 1, { 0x07 }},
  /* ... */
  /*! llcmdstop2 !*/
  /*! llcmdstart3 !*/
  // PWCTR1 Power control -4.6V, Auto mode
  { 0xC0, 0, 3, { 0xA2, 0x02, 0x84}},
  // PWCTR2 Power control VGH25 2.4C, VGSEL -10, VGH = 3 * AVDD
  { 0xC1, 0, 1, { 0xC5}},
  // PWCTR3 Power control, opamp current smal, boost frequency
  { 0xC2, 0, 2, { 0x0A, 0x00 }},
  // PWCTR4 Power control, BLK/2, opamp current small and medium low
  { 0xC3, 0, 2, { 0x8A, 0x2A}},
  // PWRCTR5, VMCTR1 Power control
  { 0xC4, 0, 2, { 0x8A, 0xEE}},
  { 0xC5, 0, 1, { 0x0E }},
  // INVOFF Don't invert display
  { 0x20, 0, 0, 0},
  // Memory access directions. row address/col address, bottom to top refesh (10.1.27)
  { ST7735_MADCTL, 0, 1, {MADVAL(MADCTLGRAPHICS)}},
  // Color mode 16 bit (10.1.30
  { ST7735_COLMOD, 0, 1, {0x05}},
  // Column address set 0..127
  { ST7735_CASET, 0, 4, {0x00, 0x00, 0x00, 0x7F }},
  // Row address set 0..159
  { ST7735_RASET, 0, 4, {0x00, 0x00, 0x00, 0x9F }},
  // GMCTRP1 Gamma correction
  { 0xE0, 0, 16, {0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D,
		  0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10 }},
  // GMCTRP2 Gamma Polarity corrction
  { 0xE1, 0, 16, {0x03, 0x1d, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D,
		  0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10 }},
  // DISPON Display on
  { 0x29, 100, 0, 0},
  // NORON Normal on
  { 0x13, 10, 0, 0},
  // End
  { 0, 0, 0, 0}
};

void f3d_lcd_init(void) {
  const struct lcd_cmdBuf *cmd;

  f3d_lcd_sd_interface_init();    // Setup SPI2 Link and configure GPIO pins
  LCD_BKL_ON();                   // Enable Backlight

  // Make sure that the chip select and reset lines are deasserted
  LCD_CS_DEASSERT();              // Deassert Chip Select

  LCD_RESET_DEASSERT();           
  delay(100);
  LCD_RESET_ASSERT();
  delay(100);
  LCD_RESET_DEASSERT();
  delay(100);

  // Write initialization sequence to the lcd
  for (cmd=initializers; cmd->command; cmd++) {
    LcdWrite(LCD_C,&(cmd->command),1);
    if (cmd->len)
      LcdWrite(LCD_D,cmd->data,cmd->len);
    if (cmd->delay) {
      delay(cmd->delay);
    }
  }
}

static void LcdWrite(char dc,const char *data,int nbytes) {
  GPIO_WriteBit(LCD_PORT,GPIO_PIN_DC,dc); // dc 1 = data , 0 = control
  GPIO_ResetBits(LCD_PORT,GPIO_PIN_SCE);
  spiReadWrite(SPILCD,0,data,nbytes,LCDSPEED);
  GPIO_SetBits(LCD_PORT,GPIO_PIN_SCE);
}

static void LcdWrite16(char dc,const uint16_t *data,int cnt) {
  GPIO_WriteBit(LCD_PORT,GPIO_PIN_DC,dc); 
  GPIO_ResetBits(LCD_PORT,GPIO_PIN_SCE);
  spiReadWrite16(SPILCD,0,data,cnt,LCDSPEED);
  GPIO_SetBits(LCD_PORT,GPIO_PIN_SCE);
}

int spiReadWrite(SPI_TypeDef *SPIx, uint8_t *rbuf,
		 const uint8_t *tbuf, int cnt, uint16_t speed) {
  int i;
  SPIx->CR1 = (SPIx->CR1 & ~SPI_BaudRatePrescaler_256) | speed;
 
  if ((cnt > 4) && !(cnt & 1)) {
    return xchng_datablock(SPIx, 0, tbuf, rbuf , cnt);
  }
  else {
    for (i = 0; i < cnt; i++){
      SPI_SendData8(SPIx, tbuf ? *tbuf++ : 0xff);
      while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
      if (rbuf) {
	*rbuf++ = SPI_ReceiveData8(SPIx);
      } else  {
	SPI_ReceiveData8(SPIx);
      }
    }
    return i;
  }
}

int spiReadWrite16(SPI_TypeDef *SPIx, uint16_t *rbuf,
		   const uint16_t *tbuf, int cnt, uint16_t speed) {
  int i;
  SPIx->CR1 = (SPIx->CR1 & ~SPI_BaudRatePrescaler_256) | speed;
  SPI_DataSizeConfig(SPIx, SPI_DataSize_16b);
  if ((cnt > 4) && !(cnt & 3)) {
    i =  xchng_datablock(SPIx, 1, tbuf, rbuf , cnt);
  }
  else {
    for (i = 0; i < cnt; i++){
      SPI_I2S_SendData16(SPIx, tbuf ? *tbuf++ : 0xffff);
      while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
      if (rbuf) {
	*rbuf++ = SPI_I2S_ReceiveData16(SPIx);
      } else {
	SPI_I2S_ReceiveData16(SPIx);
      }
    }
  }
  SPI_DataSizeConfig(SPIx, SPI_DataSize_8b);
  return i;
}

void f3d_lcd_setAddrWindow ( uint16_t x0 , uint16_t y0 , uint16_t x1 , uint16_t y1 , uint8_t madctl) {
  madctl = MADVAL ( madctl );
  if ( madctl != madctlcurrent ){
    f3d_lcd_writeCmd(ST7735_MADCTL);
    LcdWrite(LCD_D, &madctl, 1);
    madctlcurrent = madctl ;
  }
  f3d_lcd_writeCmd(ST7735_CASET);
  LcdWrite16(LCD_D,&x0,1);
  LcdWrite16(LCD_D,&x1,1);
  f3d_lcd_writeCmd(ST7735_RASET);
  LcdWrite16(LCD_D,&y0,1);
  LcdWrite16(LCD_D,&y1,1);
  f3d_lcd_writeCmd(ST7735_RAMWR);
}

void f3d_lcd_pushColor(uint16_t *color,int cnt) {
  LcdWrite16(LCD_D,color,cnt);
}

static void f3d_lcd_writeCmd(uint8_t c) {
  LcdWrite(LCD_C,&c,1);
}

void f3d_lcd_fillScreen(uint16_t color) {
  uint8_t x,y;
  f3d_lcd_setAddrWindow (0,0,ST7735_width-1,ST7735_height-1,MADCTLGRAPHICS);
  for (x=0;x<ST7735_width;x++) {
    for (y=0;y<ST7735_height; y++) {
      f3d_lcd_pushColor(&color,1);
    }
  }
}

void f3d_lcd_fillScreen2(uint16_t color) {
  uint8_t y;
  uint16_t x[ST7735_width];
  for (y = 0; y < ST7735_width; y++) x[y] = color;
  f3d_lcd_setAddrWindow (0,0,ST7735_width-1,ST7735_height-1,MADCTLGRAPHICS);
  for (y=0;y<ST7735_height; y++) {
    f3d_lcd_pushColor(x,ST7735_width);
  }
}

/// Fills area from x0,y0 to x1,y1 with specified color
void f3d_lcd_fillArea(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color){
  uint16_t i;
  uint16_t width = x1 - x0;
  uint16_t cArray[width];
  for (i = 0; i < width; i++) cArray[i] = color;
  f3d_lcd_setAddrWindow(x0, y0, x1, y1, MADCTLGRAPHICS);
  for (i = y0; i < y1; i++) f3d_lcd_pushColor(cArray, width);
}

/// When given a background buffer array, fills in the section of background within square radius
/// Used in final project for some edge cases when drawing
void f3d_lcd_restoreArea(int x, int y, uint16_t radius, uint16_t * background){
  int minX = x - radius;
  int minY = y - radius;
  int maxX = x + radius;
  int maxY = y + radius;
  int width = maxX - minX;
  int height = maxY - minY;
  uint16_t coords[height][width]; //2D array
  int i,j;

  //Filling data for a circle
  // iterate Y then X
  for(i = 0; i < height; i++)
    for(j = 0; j < width; j++)
	      coords[i][j] = *((background+((i+y-32-radius)*128)) + j + x - radius);
    
  
  f3d_lcd_setAddrWindow(minX,minY,maxX-1,maxY-1,MADCTLGRAPHICS);
  for (i = 0; i < height; i++){
    f3d_lcd_pushColor(coords[i],width);
  }
}

/// Draws a circle outline on our screen
void f3d_lcd_drawCircle(uint16_t px, uint16_t py,uint16_t nx, uint16_t ny, uint16_t radius, uint16_t color, uint16_t bgColor){
  uint16_t dummy[1][1];
  f3d_lcd_drawCircleTransparent(px, py, nx, ny, radius, color, bgColor, 0, (uint16_t *)dummy);
}

/// Draws a circle with a transparent background on our screen. The "transparency" is just drawing our background coords where we should be "Transparent"
void f3d_lcd_drawCircleTransparent(uint16_t px, uint16_t py,uint16_t nx, uint16_t ny, uint16_t radius, uint16_t color, uint16_t bgColor, int transparent, uint16_t * background){
  /// Calculating various variables to be used later
  int minX = max(0,min(px-radius,nx-radius));
  int minY = max(0,min(py - radius, ny-radius));
  int maxX = min(ST7735_width, max(px + radius, nx + radius));
  int maxY = min(ST7735_height, max(py + radius, ny + radius));
  int width = maxX - minX;
  int height = maxY - minY;
  uint16_t coords[height][width]; //2D array
  int i,j;
  int dist; 

  //Filling data for a circle
  // iterate Y then X
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      dist = sqrt(pow(j + minX - nx, 2) + pow(i + minY - ny, 2)) + 1;
      if (dist == radius){ //change to <= for a circle fill
	coords[i][j] = color;
      } 
      else {
        /// Since we use this function as a generic circle draw, transparent or not, this is the logic that either fills in a solid background color
          /// or our designated background image (if transparent)
	    if(!transparent)
	      coords[i][j] = bgColor;
	    else{ //TRANSPARENT
	      coords[i][j] = *((background+((i+ny-32-radius)*128)) + j + nx - radius); // This increments our pointer memory location by our desired coordinate
	    }
      }
    }
  }
  f3d_lcd_setAddrWindow(minX,minY,maxX-1,maxY-1,MADCTLGRAPHICS);
  /// Draws the actual circle to the rows which change
  for (i = 0; i < height; i++){
    f3d_lcd_pushColor(coords[i],width);
  }
     
}

/// Same as DrawCircle, but draws a circle filled in with color
void f3d_lcd_fillCircle(uint16_t px, uint16_t py,uint16_t nx, uint16_t ny, uint16_t radius, uint16_t color, uint16_t bgColor){
  uint16_t dummy[1][1];
  f3d_lcd_fillCircleTransparent(px, py, nx, ny, radius, color, bgColor, 0,(uint16_t *)dummy);
  
}

/// Same as drawCircleTransparent, but draws a filled in circle, with the edges of the square bounds being our background image
void f3d_lcd_fillCircleTransparent(uint16_t px, uint16_t py,uint16_t nx, uint16_t ny, uint16_t radius, uint16_t color, uint16_t bgColor, int transparent, uint16_t *background){
  int minX = max(0,min(px-radius,nx-radius));
  int minY = max(0,min(py - radius, ny-radius));
  int maxX = min(ST7735_width, max(px + radius, nx + radius));
  int maxY = min(ST7735_height, max(py + radius, ny + radius));
  int width = maxX - minX;
  int height = maxY - minY;
  uint16_t coords[height][width]; //2D array
  int i,j;
  int dist; 

  //Filling data for a circle
  // iterate Y then X
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      dist = sqrt(pow(j + minX - nx, 2) + pow(i + minY - ny, 2)) + 1;
      if (dist <= radius){ //change to == for a circle outline
	coords[i][j] = color;
      } 
      else {
          /// Since we use this function as a generic circle draw, transparent or not, this is the logic that either fills in a solid background color
            /// or our designated background image (if transparent)
	    if (!transparent)
	      coords[i][j] = bgColor;
	    else{
	      coords[i][j] = *((background+((i+ny-32-radius)*128)) + j + nx - radius); // This increments our pointer memory location by our desired coordinate
	    }
      }
    }
  }
  f3d_lcd_setAddrWindow(minX,minY,maxX-1,maxY-1,MADCTLGRAPHICS);
  for (i = 0; i < height; i++){
    f3d_lcd_pushColor(coords[i],width);
  }
    
}

/// Draws an individual pixel
void f3d_lcd_drawPixel(uint8_t x, uint8_t y, uint16_t color) {
  if ((x >= ST7735_width) || (y >= ST7735_height)) return;
  f3d_lcd_setAddrWindow(x,y,x+1,y+1,MADCTLGRAPHICS);
  f3d_lcd_pushColor(&color,1);
}

/// Draws a letter on the screen
void f3d_lcd_drawChar(uint8_t x, uint8_t y, unsigned char c, uint16_t color, uint16_t background_color) {
  int i, j;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 8; j++){ 
      f3d_lcd_drawPixel(x+i,y+j, background_color);
    }
  }
  for (i = 0; i < 5; i++) {
    uint8_t byte = ASCII[c*5 + i];
    for (j = 0; j < 8; j++){
      if (byte & (1)) {
	f3d_lcd_drawPixel(x+i,y+j, color);
      }
      byte >>= 1;
    }
  }
}

/// Draws a word on the screen
void f3d_lcd_drawString(uint8_t x, uint8_t y, char *c, uint16_t color, uint16_t background_color) {
  while (c && *c) {
    f3d_lcd_drawChar(x, y, *c++, color, background_color);
    x += 6;
    if (x + 5 >= ST7735_width) {
      y += 10;
      x = 0;
    }
  }
}

static int xchng_datablock(SPI_TypeDef *SPIx, int half, const void *tbuf, void *rbuf, unsigned count) {
  DMA_InitTypeDef DMA_InitStructure;
  uint16_t dummy[] = {0xffff};
 
  DMA_Channel_TypeDef *rxChan;
  DMA_Channel_TypeDef *txChan;
  uint32_t dmaflag;
 
  if (count & 1)
    return -1;
 
  if (SPIx == SPI1) {
    rxChan = DMA1_Channel2;
    txChan = DMA1_Channel3;
    dmaflag = DMA1_FLAG_TC2;
  }
  else if (SPIx == SPI2) {
    rxChan = DMA1_Channel4;
    txChan = DMA1_Channel5;
    dmaflag = DMA1_FLAG_TC4;
  }
  else
    return -1;
 
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(SPIx->DR));
  if (half) {
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  }
  else {
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  }
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_BufferSize = count;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
 
  DMA_DeInit(rxChan);
  DMA_DeInit(txChan);
 
  if (rbuf) {
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)rbuf;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  }
  else {
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) dummy;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  }
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_Init(rxChan, &DMA_InitStructure);
 
  if (tbuf) {
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)tbuf;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  }
  else {
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) dummy;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  }
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_Init(txChan, &DMA_InitStructure);
 
  // Enable channels
  DMA_Cmd(rxChan, ENABLE);
  DMA_Cmd(txChan, ENABLE);
 
  // Enable SPI TX/RX request
  SPI_I2S_DMACmd(SPIx, SPI_I2S_DMAReq_Rx | SPI_I2S_DMAReq_Tx, ENABLE);
 
  // Wait for completion
  while (DMA_GetFlagStatus(dmaflag) == RESET) { ; }
 
  // Disable channels
  DMA_Cmd(rxChan, DISABLE);
  DMA_Cmd(txChan, DISABLE);
  SPI_I2S_DMACmd(SPIx, SPI_I2S_DMAReq_Rx | SPI_I2S_DMAReq_Tx, DISABLE);
  return count;
}

/* f3d_lcd_sd.c ends here */
