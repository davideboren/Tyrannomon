#include "TFT_eSprite_X.h"

bool TFT_eSprite_X::pushToSpriteCropped(TFT_eSprite_X *dspr, int32_t x, int32_t y, int8_t dir, 
    int32_t sx, int32_t sy, int32_t sw, int32_t sh, uint16_t transp) {

        if ( !_created  || !dspr->_created) return false; // Check Sprites exist

        // Check destination sprite compatibility
        int8_t ds_bpp = dspr->getColorDepth();
        if (_bpp == 16 && ds_bpp != 16 && ds_bpp !=  8) return false;
        if (_bpp ==  8 && ds_bpp !=  8) return false;
        if (_bpp ==  4 || ds_bpp ==  4) return false;
        if (_bpp ==  1 && ds_bpp !=  1) return false;

        bool oldSwapBytes = dspr->getSwapBytes();
        uint16_t sline_buffer[width()];

        transp = transp>>8 | transp<<8;

        // Scan destination bounding box and fetch transformed pixels from source Sprite
        for (int32_t ys = sy; ys < sy + sh; ys++) {
            int32_t ox = x;
            uint32_t pixel_count = 0;

            if(dir == -1){ //This is stupid but it will work for now
                for (int32_t xs = sx; xs < sx + sw; xs++) {
                //for (int32_t xs = sx + sw - 1; xs >= sx; xs--) { // Flip ver.
                    uint16_t rp = 0;
                    if (_bpp == 16) rp = _img[xs + ys * width()];
                    else { rp = readPixel(xs, ys); rp = rp>>8 | rp<<8; }
                    //dspr->drawPixel(xs, ys, rp);

                    if (transp == rp) {
                        if (pixel_count) {
                        dspr->pushImage(ox, y, pixel_count, 1, sline_buffer, _bpp);
                        ox += pixel_count;
                        pixel_count = 0;
                        }
                        ox++;
                    }
                    else {
                        sline_buffer[pixel_count++] = rp;
                    }
                }
            }
            else {
                //for (int32_t xs = sx; xs < sx + sw; xs++) {
                for (int32_t xs = sx + sw - 1; xs >= sx; xs--) { // Flip ver.
                    uint16_t rp = 0;
                    if (_bpp == 16) rp = _img[xs + ys * width()];
                    else { rp = readPixel(xs, ys); rp = rp>>8 | rp<<8; }
                    //dspr->drawPixel(xs, ys, rp);

                    if (transp == rp) {
                        if (pixel_count) {
                        dspr->pushImage(ox, y, pixel_count, 1, sline_buffer, _bpp);
                        ox += pixel_count;
                        pixel_count = 0;
                        }
                        ox++;
                    }
                    else {
                        sline_buffer[pixel_count++] = rp;
                    }
                }
            }



            if (pixel_count) dspr->pushImage(ox, y, pixel_count, 1, sline_buffer);
            y++;
        }
        dspr->setSwapBytes(oldSwapBytes);
        return true;
    }
