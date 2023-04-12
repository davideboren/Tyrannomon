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

Monster::Monster(MonsterName name){
    this->setCharacter(name);
}

void Monster::setCharacter(MonsterName name){
    spr.createSprite(48,64);
    MrBitmap mrb = MrBitmap();
    mrb.loadBmp(MonsterDB[name].filename, &(this->spr));
}

void Monster::update(){
    //Bounds
    if      ( _x <= -8 )    { _xdir =  1; }
    else if ( _x >= 56 )    { _xdir = -1; }

    else if (!random(4)){ //Change direction
        if (_xdir != 0)     { _xdir =  0; }
        else if (random(2)) { _xdir =  1; }
        else                { _xdir = -1; }
    }

    _x += _xdir * 2;

    if(this->_sx == SPR_STAND2_X && this->_sy == SPR_STAND2_Y){
        int dice = random(6);
        if(dice == 5){
            this->_sx = SPR_HAPPY_X;
            this->_sy = SPR_HAPPY_Y;
        }
        else if(dice == 4){
            this->_sx = SPR_ANGRY_X;
            this->_sy = SPR_ANGRY_Y;
        }
        else{
            this->_sx = SPR_STAND1_X;
            this->_sy = SPR_STAND1_Y;
        }
    }
    else {
        this->_sx = SPR_STAND2_X;
        this->_sy = SPR_STAND2_Y;
    }
}