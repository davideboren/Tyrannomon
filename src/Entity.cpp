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

void Entity::setSprite(String filename, uint16_t w, uint16_t h){
    spr.createSprite(w,h);
    MrBitmap mrb = MrBitmap();
    mrb.loadBmp(filename, &(this->spr));
}

void Entity::setDimensions(int32_t w, int32_t h){
  this->_w = w;
  this->_h = h;
}

MonsterName Entity::get_name(){
  return Empty;
}

int Entity::get_age(){
  return 0;
}

void Entity::update(){
}