#include <Monster.h>

Monster::Monster(){
    this->_x = 32 - 8;
    this->_y = 64 - 16 - 4;
    this->_xdir = 1;
    this->_ydir = 0;
    this->_w = 16;
    this->_h = 16;
    this->_sx = 0;
    this->_sy = 0;
}

Monster::Monster(String name){
    this->setCharacter(name);
}

void Monster::setCharacter(String name){
    spr.createSprite(48,64);
    MrBitmap mrb = MrBitmap();
    mrb.loadBmp(name, &(this->spr));
}

void Monster::update(){
    if(_x <= -8){
        _xdir = 1;
    }
    else if(_x >= 64 + 8){
        _xdir = -1;
    }
    else{
        _xdir = random(3) - 1;
    }

    _x += _xdir * 2;
    this->_sx = abs(_sx - 16);
}