// Skeet Shooter - Nathaniel Ferguson

//Includes ----------------
#include <stm32f30x.h>   // 
#include <f3d_uart.h>    //
#include <f3d_lcd_sd.h>  //
#include <f3d_i2c.h>     //
#include <f3d_led.h>     //
#include <f3d_accel.h>   //
#include <f3d_nunchuk.h> //
#include <f3d_rtc.h>     //
#include <f3d_dac.h>     //
#include <f3d_systick.h> //
#include <ff.h>          //
#include <diskio.h>      //
#include <math.h>        //
#include <stdio.h>       //
#include <stdlib.h>      //
#include <string.h>      //
#include <fcntl.h>       //
#include <bmp.h>         //
// End Of Includes --------

//Audio Stuff ----------------------------
#define TIMER 20000                     //
#define AUDIOBUFSIZE 128                //
                                        //
extern uint8_t Audiobuf[AUDIOBUFSIZE];  //
extern int audioplayerHalf;             //
extern int audioplayerWhole;            //
//----------------------------------------


//Image/SD Functions ---------------------------------
struct bmpfile_magic magic;                         //
struct bmpfile_header header;                       //
BITMAPINFOHEADER info;                              //
FATFS Fatfs;		// File system object           //
FIL Fil;		    // File object                  //
BYTE Buff[512];		// File read buffer             //
FRESULT rc;			// Result code                  //
DIR dir;			// Directory object             //
FILINFO fno;		// File information object      //
UINT bw, br;                                        //
unsigned int retval;                                //
                                                    //
void die (FRESULT rc) {                             //
  printf("Failed with rc=%u.\n", rc);//Show error code
  while (1);                                        //
}                                                   //
//----------------------------------------------------

// MISC VARS -------------------
char highScoreStr[3];       // High score char string
char scoreStr[3];           // Current score char string
int gameTimer = 10000;      // Adjust for game duration
int shotCooldownMax = 300;  // Adjust for shot cooldown timer
int shotCooldown = 0;       // Used to count our current cooldown amount
int highScore;              // Stores our high score
uint8_t aimX = 100;         //
uint8_t aimY = 100;         // Inits our aiming coords, just need them to start as
uint8_t paimX = 100;        // something roughly in the middle of the screen
uint8_t paimY = 100;        //
uint8_t aimRadius = 7;      // Adjust for a bigger/smaller reticle
int fuseTime = 500;         // Time between discs launching
int fuseCount = 0;          // Current countdown for disc launching
float pdiscX = 0;           //
float pdiscY = 0;           // Inits our disc coords, just need to start them as
float discX = 0;            // something hidden enough
float discY = 0;            //
uint8_t maxDiscRadius = 6;  // Adjust for the max size we wan our discs to be
uint8_t currDiscRadius = 0; // Current size of the disc - start at 0 for invisible disc
uint8_t singleLaunch = 1;   // boolean used for ensuring only one disc launches at a time
int discLifespan = 0;       // Counts how long our current disc has been active
int score = 0;              // Current score
float pitch = 0.f;          // Init a value for our board's pitch
float roll = 0.f;           // Init a value for our board's roll
float prevP = 0.0f;         // Init a value for our board's previous pitch
float prevR = 0.0f;         // Init a value for our board's previous roll
uint8_t currX, currY, prevX, prevY; // Declaring values for our circle draws, which will be used later
uint8_t mode = 0;           // Boolean for our game mode - 0 = Joystick, 1 = Board tilt
uint8_t discLaunchSetting = 0;      // Inits a value for which location/angle we want to launch our disc
int aimSpeed = 2;           // Adjust for faster/slower aiming - gamefeel
float tiltingScale = 1.5f;  // Adjust for how sensitive tilt on our board is - gamefeel
//---------------------------------

int main(void){
  
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  
  f3d_uart_init();              // Used to print to serialT for debugging
  printf("Start inits\n");
  f3d_led_init();               // Used to init our board LEDs
  printf("LED init\n");
  f3d_delay_init();             // Used to init our delay driver
  printf("delay init\n");
  f3d_i2c1_init();              // Used to init our Nintendo Nunchuk
  printf("i2c1 init\n");
  delay(10);                    // Delay for the i2c1 init - need to add a small buffer
  f3d_timer2_init();
  printf("timer2 init\n");
  f3d_dac_init();               // Used to init our audio
  printf("dac init\n");
  f3d_rtc_init();               // Used to init our file storage
  printf("rtc init\n");
  f3d_user_btn_init();          // Used to init the blue user button on our board
  printf("btn init\n");
  f3d_systick_init();           // Used to init our interrupts for faster rendering
  printf("systick init\n");
  f3d_lcd_init();               // Used to init our LCD screen
  printf("lcd init\n");
  f3d_accel_init();             // Used to init our gyroscope (named accelerometer many years ago, but it's the gyroscope)
  printf("accel init\n");
  delay(10);
  f3d_nunchuk_init();           // Used to init our Nunchuk. This goes last because it fails most often
  delay(10);                    // Also contains a print statement inside to verify if it initialized
  printf("Startup Complete\n");

  nunchuk_t nun;                // Ref variable for our nunchuk controller
  f3d_nunchuk_read(&nun);       // Get initial input for nunchuk

  int i = 0;
  int j = 0;

  float accelVals[3] = {0.f, 0.f, 0.f};     // float vector, which will be updated with the gyro feedback of our board

  shotCooldown = shotCooldownMax;           // Our shot cooldown being set to the max value, it counts up to the max, verifying it is ready to fire

  delay(100);
  currDiscRadius = maxDiscRadius;           // Discs will shrink as they move across the screen, this init's it to be full size

  /// Inits our start screen - waits for blue button input to work
  setupStartScreen();
  
  /// Inits our game screen
  setupGameScreen();

  /// Loads our high score from our SD card file
  loadHighScore();

  /// Loop runs until gameTimer reaches 0 - this is when the game will end
  /// Not a perfect implementation, because gameTimer will tick down faster if there
  /// are less processes, but a stretch goal, if time had provided, would have been to find
  /// a stable c timer, independent of CPU clock speed
  while(gameTimer > 0){
    
    /// Reads the player aim and draws our aiming reticle
    playerAim()
    
    discLaunchingAndMovement();

    playerHitDetection();
          
    gameTimer--;
  }

  /// Writes a new highscore if our current score is higher than our read score
  if (score > highScore){
    printf("\nUpdating the score.\n");
    rc = f_open(&Fil, "SCORE.TXT", FA_WRITE | FA_CREATE_ALWAYS);
    if (rc) die(rc);
    
    rc = f_write(&Fil, scoreStr, 2, &bw);
    if (rc) die(rc);
    printf("%u bytes written.\n", bw);
    
    printf("\nClose the file.\n");
    rc = f_close(&Fil);
    if (rc) die(rc);
  }

  /// Displays our game-over screen
  f3d_lcd_fillScreen2(BLACK);
  f3d_lcd_drawString(10, 60, "GAME OVER", RED, BLACK);
  f3d_lcd_drawString(0,70, "THANKS FOR PLAYING", WHITE, BLACK);
  f3d_dac_playFile("wegothim.wav");                             // Plays an audio file - requirement of the project

  return 0;
}

/// Calculates if the radius of our disc and our aiming reticle overlap at all
/// d = disc, a = player aim, r = radius, x/y = coords
int detectCollision(int dx, int dy, int ax, int ay, int dr, int ar){
  if ((sqrt(pow(dx-ax,2)) + sqrt(pow(dy-ay,2))) <= dr + ar)
    return 1;
  else
    return 0;
}


int setupStartScreen() {
    /// Drawing Start Screen
    f3d_lcd_fillScreen2(BLACK);
    f3d_lcd_drawString(10, 60, "PRESS USER BUTTON", BLUE, BLACK);
    f3d_lcd_drawString(30, 70, "TO START", WHITE, BLACK);

    while (1) {
        if (user_btn_read())                                                // Waits for user button input to begin the game
            break;                                                            // - constraint of the project
    }
    return 0;
}

int setupGameScreen() {
    uint16_t toPush[128][128];
    struct bmppixel bp[128];
    f_mount(0, &Fatfs);// Register volume work area
    f3d_lcd_fillScreen2(BLACK);


    /// This block loads our image from SD, and sets it to our required format
    rc = f_open(&Fil, "bliss.bmp", FA_READ);
    if (rc) die(rc);
    rc = f_read(&Fil, &magic, 2, &br);
    rc = f_read(&Fil, &header, sizeof(header), &br);
    rc = f_read(&Fil, &info, sizeof(info), &br);
    rc = f_lseek(&Fil, header.bmp_offset);

    ///This block converts each of the colors in our image from 24-bit to 16 via bitshifts in the RGB channels
    for (i = 127; i >= 0; i--) {
        rc = f_read(&Fil, &bp, sizeof(bp), &br);
        for (j = 127; j >= 0; j--) {
            if (rc) {
                printf("Failing at pixel %d, %d\n", i, j);                                      // Defensive programming to return which pixel is being failed, if a read error occurs
                die(rc);
            }
            //24 to 16 conversion
            toPush[i][j] = (bp[j].b >> 3 << 11) | (bp[j].g >> 2 << 5) | (bp[j].r >> 3);
        }
    }

    f3d_lcd_setAddrWindow(0, 32, 127, 159, MADCTLGRAPHICS);                                   // Preps our LCD reigon to be drawn on


    /// Pushes our image to the screen, one row at a time
    for (i = 0; i < 128; i++) {
        f3d_lcd_pushColor(toPush[i], 128);
    }

    rc = f_close(&Fil);                                                                   // Close our file to prevent SD corruption
    printf("Closed the file.\n");

    return 0;
}

int loadHighScore() {
    printf("Opening score file\n");
    rc = f_open(&Fil, "SCORE.TXT", FA_READ);
    if (rc) die(rc);
    //Type file content
    while (1) {
        rc = f_read(&Fil, Buff, sizeof Buff, &br);	            // Read a chunk of file 
        if (rc || !br) 
            break;			                                    // Error or end of file 
        for (i = 0; i < br; i++)		                        // Type the data 
            highScoreStr[i] = Buff[i];
    }
    if (rc) die(rc);                                            // Sends the program to our infinite death loop if RC had an issue

    rc = f_close(&Fil);
    if (rc) die(rc);                                            // Sends the program to our infinite death loop if RC had an issue
    printf("Closed score file\n");
    printf("Score: %d", score);
    highScore = atoi(highScoreStr);
    sprintf(highScoreStr, "%d", highScore);                     //Parses score to a string

    /// Displays our high score on our screen
    f3d_lcd_drawString(0, 5, "Score: 0", WHITE, BLACK);
    f3d_lcd_drawString(0, 20, "HighScore:", WHITE, BLACK);
    f3d_lcd_drawString(60, 20, highScoreStr, WHITE, BLACK);

    return 0;
}

int playerAim() {
    f3d_nunchuk_read(&nun);                         // Reading our nunchuk input to move the reticle

    ///This block will switch our input control from nunchuk to board tilt if the blue input button is pressed
    if (user_btn_read()) {
        if (mode == 0)
            mode = 1;
        else
            mode = 0;
        delay(50);                                    // Delay is to prevent user button being read as pressed multiple times if pressed slowly
    }

    /// This adds/subtracts aimSpeed from our X/Y coords, depending on the reading of the joystick on our nunchuk,
    /// only if we are in the joystick aim mode, however
    if (mode == 0) {
        if (nun.jx >= 240) //right
            aimX += aimSpeed;
        if (nun.jx == 0) //left
            aimX -= aimSpeed;
        if (nun.jy > 200) //up
            aimY -= aimSpeed;
        if (nun.jy == 0) //down
            aimY += aimSpeed;
    }
    /// If we are in the board tilt aim mode, then we want to take the pitch/roll read from the board and 
    /// Adjust the aiming reticle accordingly
    else if (mode == 1) {

        /// Board tilt read, and pitch/roll calculations from raw gyro data
        f3d_accel_read(accelVals);
        pitch = f3d_accel_calculate_pitch(accelVals);
        roll = f3d_accel_calculate_roll(accelVals);
        aimX = ST7735_width / 2 + (180.0 / M_PI * -roll * tiltingScale);              // tiltingScale is a constant used to adjust the maximum gyro read
        aimY = ST7735_height / 2 + (180.0 / M_PI * -pitch * tiltingScale);            // with the dimensions of the board, this is a "game feel" number
    }

    /// These four if statements make sure our aiming reticle does not move beyond the out-of-bounds region on our LCD
    /// Causing us to crash, and also confuse the player on why their reticle disappeared
    if (aimX - aimRadius < 0)
        aimX = 0 + aimRadius;
    if (aimY - aimRadius < 31)
        aimY = 32 + aimRadius;
    if (aimX + aimRadius > 126)
        aimX = 127 - aimRadius;
    if (aimY + aimRadius > 158)
        aimY = 158 - aimRadius;

    /// This draws our reticle, and sets the previous aim X and Y values to be the current values, for use on the next loop
    f3d_lcd_drawCircleTransparent(paimX, paimY, aimX, aimY, aimRadius, RED, BLUE, 1, (uint16_t *)toPush);
    paimX = aimX;
    paimY = aimY;

    if (shotCooldown > 0)         // Prevents the player from just holding down the trigger to constantly shoot
        shotCooldown--;

    return 0;
}

/// Launches our discs and contains the logic for moving the disc across the screen, while shrinking it
int discLaunchingAndMovement() {
    fuseCount++;                                    // Increments our fuse, timing the duration between discs launching
    srand((int)nun.ax * nun.ay + nun.az);           // Uses the nunchuk X, Y, and Z gyro readings because the gyros are broken and it's practically random

    /// Enters this if we have reached the threshold for launching our disc
    if (fuseCount >= fuseTime)
    {
        if (singleLaunch) {                          // Our singleLaunch variable acts as a flag to ensure we ony shoot one disc per fuse cycle
            discLaunchSetting = rand() % 5;           // Generates a random number, 0-4, which determines which of five launch angles/points happens 
        }
        /// Disc launch Setting 0
        if (discLaunchSetting == 0) {
            if (singleLaunch) {                        // Spawns our disc at the starting coords and sets our launch flag to false
                discY = 150;
                discX = 123;
                singleLaunch = 0;
            }
            pdiscY = discY;
            pdiscX = discX;
            if (discY > 33 + currDiscRadius)          // Moves our disc up/down
                discY -= 0.75;
            if (discX > 1 + currDiscRadius)           // Moves our disc left/right
                discX -= 1.5;
        }
        /// Disc launch Setting 1
        else if (discLaunchSetting == 1) {
            if (singleLaunch) {
                discY = 150;
                discX = 2;
                singleLaunch = 0;
            }
            pdiscY = discY;
            pdiscX = discX;
            if (discY > 33 + currDiscRadius)
                discY -= 0.75;
            if (discX < 128 + currDiscRadius)
                discX += 1.5;
        }
        /// Disc launch Setting 2
        else if (discLaunchSetting == 2) {
            if (singleLaunch) {
                discY = 150;
                discX = 2;
                singleLaunch = 0;
            }

            pdiscY = discY;
            pdiscX = discX;
            if (discY > 33 + currDiscRadius)
                discY -= 1.5;
            if (discX < 128 + currDiscRadius)
                discX += 0.75;
        }
        /// Disc launch Setting 3
        else if (discLaunchSetting == 3) {
            if (singleLaunch) {
                discY = 150;
                discX = 123;
                singleLaunch = 0;
            }

            pdiscY = discY;
            pdiscX = discX;
            if (discY > 33 + currDiscRadius)
                discY -= 1.5;
            if (discX < 128 + currDiscRadius)
                discX -= 0.75;
        }
        /// Disc launch Setting 4
        else if (discLaunchSetting == 4) {
            if (singleLaunch) {
                discY = 150;
                discX = 64;
                singleLaunch = 0;
            }

            pdiscY = discY;
            pdiscX = discX;
            if (discY > 33 + currDiscRadius)
                discY -= 1.0;
            if (discX < 128 + currDiscRadius)
                discX += 0;
        }

        discLifespan++;
        f3d_lcd_fillCircleTransparent((int)pdiscX, (int)pdiscY, (int)discX, (int)discY, currDiscRadius, WHITE, BLUE, 1, (uint16_t *)toPush); // Draws our filled circle, including our background

    }

    /// This block shrinks our disc's radius by one every 10 ticks/movements of our disc
    if (discLifespan > 10) {
        printf("discX: %d, discY: %d\n", discX, discY);

        if (currDiscRadius > 0)
            currDiscRadius--;

        discLifespan = 0;
        f3d_lcd_restoreArea(discX, discY, currDiscRadius + 1, (uint16_t *)toPush);        // This fixes artifacting that occurs as a result of a shrinking disc and our implementation of circle draws
    }

    /// This block will "destroy" our disc when the lifespan runs out (radius == 0), and signal that we are available to launch another disc
    if (currDiscRadius == 0) {
        fuseCount = 0;
        singleLaunch = 1;
        f3d_lcd_restoreArea(discX, discY, currDiscRadius + 1, (uint16_t *)toPush);
        currDiscRadius = maxDiscRadius;
        printf("resetting disc\n");
    }
    return 0;
}

int playerHitDetection() {

    /// This is successful if our trigger has been pulled, our cooldown is at 0, and if there is overlap in the radii of our aiming reticle and the disc
    if (nun.z && shotCooldown == 0 && detectCollision((int)discX, (int)discY, aimX, aimY, currDiscRadius, aimRadius)) {
        f3d_led_all_on();                               // Flash the LEDs - skinner box
        shotCooldown = shotCooldownMax;                 // Resets our shoot cooldown
        delay(75);                                      // Pauses the game screen for a brief time on hit, good gamefeel! Feels more powerful
        f3d_led_all_off();
        f3d_lcd_restoreArea(discX, discY, currDiscRadius, (uint16_t *)toPush);          // Erases where the disc was
        currDiscRadius = 0;
        discY = 0;
        discX = 0;

        /// Updating our score display
        score++;
        sprintf(scoreStr, "%d", score);
        f3d_lcd_fillArea(35, 0, 90, 15, BLACK);
        f3d_lcd_drawString(40, 6, scoreStr, WHITE, BLACK);
    }
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif
