#include "MrBitmap.h"

//Load BMP file from SD card into TFT_eSprite_X
//Based on Bodmer's bmp draw function
void MrBitmap::loadBmp(String filename, TFT_eSprite_X* spr, int scale) {
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
          if(0){
            if(!(r == 0xFF && g == 0x00 && b == 0xFF)){
              //TFT is too heavy on blue tones, adjust colors accordingly
              int r_adj = (int) r*1.3;
              if(r_adj > 255){
                r_adj = 255;
              }
              int g_adj = (int) g*1.05;
              if(g_adj > 255){
                g_adj = 255;
              }
              r = (uint8_t)r_adj;
              g = (uint8_t)g_adj;
              b *= 0.85;
            }
          }
          uint16_t color = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
          if(scale == 2){
            int y_pos = h - row - 1;
            spr->drawPixel(col*2, y_pos*2, color);
            spr->drawPixel(col*2 + 1, y_pos*2, color);
            spr->drawPixel(col*2, y_pos*2 + 1, color);
            spr->drawPixel(col*2 + 1, y_pos*2 + 1, color);
          }
          else{
            spr->drawPixel(col, h - row - 1, color);
          }
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

void MrBitmap::loadBmp(String filename, TFT_eSprite_X* spr, int scale, uint16_t fill) {
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

          uint16_t color = 0x2945;
          if(r == 0xFF && g == 0x00 && b == 0xFF){
            color = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
          }
          else if(row % 3 == 0 || col % 3 == 0){
            color = fill;
          }
          if(scale == 2){
            int y_pos = h - row - 1;
            spr->drawPixel(col*2, y_pos*2, color);
            spr->drawPixel(col*2 + 1, y_pos*2, color);
            spr->drawPixel(col*2, y_pos*2 + 1, color);
            spr->drawPixel(col*2 + 1, y_pos*2 + 1, color);
          }
          else{
            spr->drawPixel(col, h - row - 1, color);
          }
        }

        //Rescan sprite for outline
        //Todo: fix when sprites are hugging on the sheet
        for(int y = 0; y < h*2; y++){
          for(int x = 0; x < w*2; x++){
            if(spr->readPixel(x,y) == 0xF81F){
              continue;
            }
            uint16_t left_px = x == 0 ? 0xF81F : spr->readPixel(x-1, y);
            uint16_t right_px = x == w ? 0xF81F : spr->readPixel(x+1, y);
            uint16_t top_px = y == 0 ? 0xF81F : spr->readPixel(x, y-1);
            uint16_t bottom_px = y == h ? 0xF81F : spr->readPixel(x, y+1);
            if(left_px == 0xF81F){
              spr->drawPixel(x,y,fill);
              spr->drawPixel(x+1,y,fill);
            }
            if(right_px == 0xF81F){
              spr->drawPixel(x,y,fill);
              spr->drawPixel(x-1,y,fill);
            }
            if(top_px == 0xF81F){
              spr->drawPixel(x,y,fill);
              spr->drawPixel(x,y+1,fill);
            }
            if(bottom_px == 0xF81F){
              spr->drawPixel(x,y,fill);
              spr->drawPixel(x,y-1,fill);
            } 
          }
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
uint16_t MrBitmap::get_width(String filename){
  // Open requested file on SD card
  String filepath = "/" + filename;
  this->bmpFS = SD.open(filepath.c_str(), FILE_READ);

  if (!bmpFS)
  {
    Serial.print("File not found");
    return 0;
  }

  uint16_t w, h;

  if (this->read16(bmpFS) == 0x4D42)
  {
    for(int i = 0; i < 4; i++){
      this->read32(bmpFS);
    }
    w = this->read32(bmpFS);
    h = this->read32(bmpFS);
    return w;
  }
  return 0;
}

uint16_t MrBitmap::get_height(String filename){
  // Open requested file on SD card
  String filepath = "/" + filename;
  this->bmpFS = SD.open(filepath.c_str(), FILE_READ);

  if (!bmpFS)
  {
    Serial.print("File not found");
    return 0;
  }

  uint16_t w, h;

  if (this->read16(bmpFS) == 0x4D42)
  {
    for(int i = 0; i < 4; i++){
      this->read32(bmpFS);
    }
    w = this->read32(bmpFS);
    h = this->read32(bmpFS);
    return h;
  }
  return 0;
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

