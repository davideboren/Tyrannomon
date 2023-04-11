#include <Entity.h>

void Entity::pushSprite(TFT_eSprite_X *bg){
  this->spr.pushToSpriteCropped(
    bg,
    this->_x, this->_y,
    this->_xdir,
    this->_sx, this->_sy,
    this->_w, this->_h,
    0xF81F);
}