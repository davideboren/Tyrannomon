/*
// TFT_eSprite with extra draw functions for rendering from sprite sheets.
// Everything sounds cooler with an X at the end
*/

#ifndef _TFT_ESPRITE_X_H_
#define _TFT_ESPRITE_X_H_

#include <TFT_eSPI.h>

class TFT_eSprite_X : public TFT_eSprite {
    using TFT_eSprite::TFT_eSprite;

    public:
        bool pushToSpriteCropped(TFT_eSprite_X *dspr, int32_t dx, int32_t dy, int8_t dir, 
            int32_t sx, int32_t sy, int32_t sw, int32_t sh, uint16_t transparent);
        bool pushSpriteScaled(TFT_eSPI *tft, int32_t x, int32_t y);
        void pushImageScaled(TFT_eSPI *tft, int32_t x, int32_t y);
};

#endif // _TFT_ESPRITE_X_H_