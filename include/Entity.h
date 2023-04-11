#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <Arduino.h>
#include <global.h>
#include "../lib/TFT_eSprite_X/TFT_eSprite_X.h"

class Entity {

    public:

        //Coordinates
        int32_t _x, _y;

        //Spritesheet crop parameters
        int32_t _sx, _sy, _w, _h;
        int8_t _xdir, _ydir;
        
        TFT_eSprite_X spr = TFT_eSprite_X(&tft);

        void update();
        void pushSprite(TFT_eSprite_X *bg);

};

#endif //_ENTITY_H_