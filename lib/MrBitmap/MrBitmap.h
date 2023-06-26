#ifndef _MR_BITMAP_H_
#define _MR_BITMAP_H_

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SD.h>

#include "../TFT_eSprite_X/TFT_eSprite_X.h"

class MrBitmap {
    public:
        void loadBmp(String filename, TFT_eSprite_X* spr, int scale);
        uint16_t get_width(String filename);
        uint16_t get_height(String filename);
    private:

        File bmpFS;

        uint16_t read16(File &f);
        uint32_t read32(File &f);
};

#endif //_MR_BITMAP_H_