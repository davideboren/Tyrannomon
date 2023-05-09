#include "MrBitmap.h"

//Load BMP file from SD card into TFT_eSprite_X
//Based on Bodmer's bmp draw function
void MrBitmap::loadBmp(String filename, TFT_eSprite_X* spr) {
  // Open requested file on SD card
  String filepath = "/" + filename;
  this->bmpFS = SD.open(filepath.c_str(), FILE_READ);

  if (!bmpFS)
  {
    Serial.print("File not found");
    return;
  }

  uint32_t seekOffset;
  uint16_t w, h, row;
  uint8_t  r, g, b;

  if (this->read16(bmpFS) == 0x4D42)
  {
    this->read32(bmpFS);
    this->read32(bmpFS);
    seekOffset = this->read32(bmpFS);
    this->read32(bmpFS);
    w = this->read32(bmpFS);
    h = this->read32(bmpFS);

    if ((this->read16(bmpFS) == 1) && (this->read16(bmpFS) == 24) && (this->read32(bmpFS) == 0))
    {

      bmpFS.seek(seekOffset);

      uint16_t padding = (4 - ((w * 3) & 3)) & 3;
      uint8_t lineBuffer[w * 3 + padding];

      for (row = 0; row < h; row++) {
        
        bmpFS.read(lineBuffer, sizeof(lineBuffer));
        uint8_t*  bptr = lineBuffer;
        
        // Convert 24 to 16 bit colours
        for (uint16_t col = 0; col < w; col++)
        {
          b = *bptr++;
          g = *bptr++;
          r = *bptr++;
          if(!(r == 0xFF && g == 0x00 && b == 0xFF)){
            //TFT is too heavy on blue tones, adjust colors accordingly
            int r_adj = (int)r*1.25;
            if(r_adj > 255){
              r_adj = 255;
            }
            r = (uint8_t)r_adj;
            b *= 0.9;
          }
          uint16_t color = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
          spr->drawPixel(col, h - row - 1, color);
        }

        // Push the pixel row to screen, pushImage will crop the line if needed
        // y is decremented as the BMP image is drawn bottom up
        //tft->pushImage(x, y--, w, 1, (uint16_t*)lineBuffer);
      }
    }
    else Serial.println("BMP format not recognized.");
  }
  bmpFS.close();
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t MrBitmap::read16(File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t MrBitmap::read32(File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

