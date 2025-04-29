#ifndef _BUBBLE_H_
#define _BUBBLE_H_

#include <Arduino.h>

#include <global.h>
#include <TFT_eSprite_X.h>
#include <MrBitmap.h>
#include <Entity.h>

class Bubble : public Entity {

    public:
        Bubble();

        void update();
};

#endif //_BUBBLE_H_