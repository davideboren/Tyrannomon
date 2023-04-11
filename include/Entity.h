#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <Arduino.h>
#include <global.h>
#include "../lib/TFT_eSprite_X/TFT_eSprite_X.h"
#include "../lib/MrBitmap/MrBitmap.h"

class Entity {

    public:

        Entity();

        //Coordinates
        int32_t _x, _y;

        //Spritesheet crop parameters
        int32_t _sx, _sy, _w, _h;
        int8_t _xdir, _ydir;
        
        TFT_eSprite_X spr = TFT_eSprite_X(&tft);

        virtual void update();
        void pushSprite(TFT_eSprite_X *bg);

        void setSprite(String filename, uint16_t w, uint16_t h);
        void setDimensions(int32_t w, int32_t h);

};

#endif //_ENTITY_H_