/*
LedMatrix.h

Copyright (c) 2015 Aaron Groom

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef LedMatrix_h
#define LedMatrix_h

#include "Arduino.h"
#include <avr/pgmspace.h>
#include "font_5x7_col.h"
#include "font_8x8_col.h"

// MAX7219 Operation Register Codes
#define OP_NOOP         0
#define OP_DECODEMODE   9
#define OP_INTENSITY    10
#define OP_SCANLIMIT    11
#define OP_SHUTDOWN     12
#define OP_DISPLAYTEST  15

#define FONT5x7         5
#define FONT8x8         8
#define RAD             0.0174532925

/*
   The maximum number of devices can be modified to suit individual needs.
   If not using all 24, reduce to save memory. The hard limit is 32 x 32 
   displays (1,024 total) due to the use of unsigned 8-bit integers;
   however, the ATmega328 only has 2k of dynamic memory so only about 190
   can be used before running out of memory.
*/
#define MAX_DEVICES     48

class LedMatrix {

   public:
      
      /* 
       * Constructor for class if using default i/o pins.
       * @param   dispRows    Number of 8x8 display rows
       * @param   dispCols	   Number of 8x8 display columns
       */      
      LedMatrix(uint8_t dispRows, uint8_t dispCols);
      
      /* 
       * Overload constructor for class.
       * @param   dispRows    Number of 8x8 display rows
       * @param   dispCols	   Number of 8x8 display columns
       * @param   mosi        Data pin
       * @param   clk         Clock pin
       * @param   cs          Chip select/load pin
       */
      LedMatrix(uint8_t dispRows, uint8_t dispCols, uint8_t mosi, uint8_t clk, uint8_t cs);
      
      /* 
       * Sets the intensity level of leds
       * @param   intensity   Intensity value (0-15)
       */
      void setIntensity(uint8_t intensity);
      
      /* 
       * Sets the shutdown mode of MAX7219 drivers
       * @param   val         1 = Shutdown mode, 0 = Normal operation
       */
		void shutdown(bool val);
      
      /* 
       * Sets the font to display
       * @param   font        Font to display (5x7 or 8x8)
       */
      void setFont(uint8_t newFont);
      
      /* 
       * Sets the value of a single led
       * @param   x           X coordinate of led
       * @param   y           Y coordinate of led
       * @param   val         1 = On, 0 = Off
       */
      void setLed(uint8_t x, uint8_t y, bool val);
      
      /* 
       * Updates the display.
       */
      void update(void);
      
      /* 
       * Clears all values in the led array, but does not clear the screen.
       */
      void clear(void);
      
      /* 
       * Clears all values in the led array, and clears the screen. It's the 
       * same as running clear() then update().
       */
      void clearScreen(void);
      
      /* 
       * Sets the delay time, in miliseconds, for scrolling text.
       * @param   val         Delay time
       */
		void scrollDelay(uint8_t val);
      
      /* 
       * Draws a single character.
       * @param   c           Character to draw
       * @param   x           X coordinate of the top left corner
       * @param   y           Y coordinate of the top left corner
       */
      void drawChar(char c, uint8_t x, uint8_t y);
      
      /* 
       * Scrolls a single character onto the matrix from the right to left
       * @param   c           Character to scroll
       * @param   dispRow     8x8 Display row to scroll character on
       */
      void scrollChar(uint8_t c, uint8_t dispRow);
      
      /* 
       * Draws a line from one point to another. 
       * @param   x1          X coordinate of the first point
       * @param   y1          Y coordinate of the first point
       * @param   x2          X coordinate of the second point
       * @param   y2          Y coordinate of the second point
       */
      void line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
      
      /* 
       * Draws a triangle
       * @param   x1          X coordinate of the first vertex
       * @param   y1          Y coordinate of the first vertex
       * @param   x2          X coordinate of the second vertex
       * @param   y2          Y coordinate of the second vertex
       * @param   x3          X coordinate of the third vertex
       * @param   y3          Y coordinate of the third vertex
       */
		void triangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3);
		
      /* 
       * Draws any quadrilateral, with the points listed as parameters 
       * in a clockwise or counter-clockwise direction.
       * @param   x1          X coordinate of the first vertex
       * @param   y1          Y coordinate of the first vertex
       * @param   x2          X coordinate of the second vertex
       * @param   y2          Y coordinate of the second vertex
       * @param   x3          X coordinate of the third vertex
       * @param   y3          Y coordinate of the third vertex
       * @param   x4          X coordinate of the fourth vertex
       * @param   y4          Y coordinate of the fourth vertex
       */
      void quad(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, uint8_t x4, uint8_t y4);
      
      /* 
       * Draws a rectangle, using the first two coordinates as the top left 
       * corner and the last two as the width/height.
       * @param   x           X coordinate of the top left corner
       * @param   y           Y coordinate of the top left corner
       * @param   w           The width of the rectangle
       * @param   h           The height of the rectangle
       */
		void rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
      
      /* 
       * Draws a circle, using the first two parameters as the center 
       * coordinates and the last as the radius.
       * @param   x           X coordinate of the center
       * @param   y           Y coordinate of the center
       * @param   radius      Radius of the circle
       */
		void circle(uint8_t h, uint8_t k, uint8_t radius);
      
      /* 
       * Draws an ellipse, using the first two parameters as the center 
       * coordinates and the last two as the width/height.
       * @param   x           X coordinate of the center
       * @param   y           Y coordinate of the center
       * @param   w           The width of the ellipse
       * @param   h           The height of the ellipse
       */
		void ellipse(uint8_t h, uint8_t k, uint8_t a, uint8_t b);
		
   private:
      
      uint8_t SPI_MOSI;       // MOSI (data) Pin
      uint8_t SPI_CLK;        // Clock pin
      uint8_t SPI_CS;         // Chip select (load/latch) pin
      
      uint8_t DISP_ROWS;      // Number of 8x8 display rows
      uint8_t DISP_COLS;      // Number of 8x8 display columns
      uint8_t NUM_DEVICES;    // Total number of displays/devices
      uint8_t NUM_COLS;       // Total number of led columns
      uint8_t NUM_ROWS;       // Total number of led rows
      uint8_t SPI_BYTES;      // Number of SPI bytes for data packet
      
      /* 
       * The pixels array holds 8 bytes per 8x8 display and is arranged 
       * so that the first display (row 0, col 0) has values 0-7. 
       * Each new column begins where the prev column ended and each new 
       * row starts where the previous row ended. For 4 display, arraged 2x2
       * would look like:
       *           COL 0          COL 1
       * ROW 0  pixels[0-7]    pixels[8-15]
       * ROW 1  pixels[16-23]  pixels[24-31]
       */
      uint8_t pixels[MAX_DEVICES * 8];    // Led matrix array values
      uint8_t spiData[MAX_DEVICES * 2];   // SPI data packet (2 bytes per display)
      uint8_t charBuffer[8];              // Character read buffer
      uint8_t sDelay;                     // Scroll delay
      uint8_t font;                       // Current font width
      
      /* 
       * Class initializations. Needed for multiple contructors.
       * @param   dispRows    Number of 8x8 display rows
       * @param   dispCols	   Number of 8x8 display columns
       * @param   mosi        Data pin
       * @param   clk         Clock pin
       * @param   cs          Chip select/load pin
       */
      void init(uint8_t dispRows, uint8_t dispCols, uint8_t mosi, uint8_t clk, uint8_t cs);
      
      /* 
       * Shifts all the leds in a single display row one position to the left.
       * @param   dispRow     Display row to shift starting at 0
       */
      void shiftLeft(uint8_t dispRow);
            
      /* 
       * Reads a single character from the selected font table into the charBuffer[] array.
       * @param   c           Character to buffer
       */
      void bufferChar(uint8_t c);
      
      /* 
       * Sets the operation code for all displays
       * @param   opcode      MAX7219 Register adderess (0-15)
       * @param   val         Register data value
       */
      void setOPCode(volatile uint8_t opcode, volatile uint8_t val);
      
      /* 
       * Writes the data packet in spiData[] array.
       */
      void spiWrite(void);
      
      /* 
       * Writes a single data byte to the SPI_MOSI pin.
       * @param   val         Data byte to write
       */
      void shiftOutFast(volatile uint8_t val);
};

#endif