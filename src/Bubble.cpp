#include <Bubble.h>

Bubble::Bubble(){
    this->_x = random(0,128);
    this->_y = -16;

    this->setSprite("sprites/fx/bubble.bmp");
}

void Bubble::update(){
    //Respawn after floating off
    if(this->_y < 0 && !random(15)){
        this ->_y = 132;
    }

    this->_x += random(-4,4);
    this->_y -= 4;
}