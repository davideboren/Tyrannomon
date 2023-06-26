#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <Arduino.h>

#include <global.h>
#include <TFT_eSprite_X.h>
#include <MrBitmap.h>
#include <MonsterDefs.h>

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
        void setSprite(String filename);

};

#endif //_ENTITY_H_