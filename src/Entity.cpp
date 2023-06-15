#include <Entity.h>

Entity::Entity(){
    this->_x = 0;
    this->_y = 0;
    this->_xdir = 1;
    this->_ydir = 0;
    this->_w = 16;
    this->_h = 16;
    this->_sx = 0;
    this->_sy = 0;
}

void Entity::pushSprite(TFT_eSprite_X *bg){
  this->spr.pushToSpriteCropped(
    bg,
    this->_x, this->_y,
    this->_xdir,
    this->_sx, this->_sy,
    this->_w, this->_h,
    0xF81F);
}

void Entity::pushSprite2x(TFT_eSprite_X *bg){
  this->spr.pushToSprite2x(
    bg,
    this->_x, this->_y,
    this->_xdir,
    this->_sx, this->_sy,
    this->_w, this->_h,
    0xF81F);
}

void Entity::setSprite(String filename){
    MrBitmap mrb = MrBitmap();
    this->_w = mrb.get_width(filename);
    this->_h = mrb.get_height(filename);
    spr.createSprite(this->_w, this->_h);
    mrb.loadBmp(filename, &(this->spr));
}

void Entity::update(){
}