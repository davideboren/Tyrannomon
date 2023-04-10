#include <Arduino.h>
#include <SD.h>
#include <TFT_eSPI.h>

#include "../lib/TFT_eSprite_X/TFT_eSprite_X.h"
#include "../lib/MrBitmap/MrBitmap.h"

TFT_eSPI tft = TFT_eSPI();

TFT_eSprite_X bg = TFT_eSprite_X(&tft);
TFT_eSprite_X spr = TFT_eSprite_X(&tft);
TFT_eSprite_X scene = TFT_eSprite_X(&tft);

//BitmapBoy t1, t2, bg;
MrBitmap t0;

int mx, my, mdir;

void setup() {

  Serial.begin(9600);
  //while(!Serial);

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ST7735_ORANGE);

  if(!SD.begin(SD_CS)){
    Serial.println("SD not found.");
    return;
  } else {
    Serial.println("SD initialized.");
  }

  MrBitmap t0 = MrBitmap();
  spr.createSprite(48,32);
  t0.loadBmp("tyr_fsht.bmp",&spr);

  MrBitmap mrbg = MrBitmap();
  bg.createSprite(64,64);
  mrbg.loadBmp("bg.bmp",&bg);

  scene.createSprite(64,64);

  mx = 24; 
  my = 44;
  mdir = -1;

}

void loop() {

  if(mx <= 0 - 8){
    mdir = 1;
  }
  else if(mx >= 64 - 8){
      mdir = -1;
  }
  else{
    mdir = random(3) - 1;
  }

  mx += mdir * 2;
  bg.pushToSprite(&scene,0,0);
  uint32_t emotion = 0;
  if(!random(3)) emotion = 32;
  spr.pushToSpriteCropped(&scene,mx,my,mdir,emotion,0,16,16,0xF81F);
  scene.pushImageScaled(&tft,0,0);

  delay(370);

  mx += mdir * 2;
  bg.pushToSprite(&scene,0,0);
  spr.pushToSpriteCropped(&scene,mx,my,mdir,16,0,16,16,0xF81F);
  scene.pushImageScaled(&tft,0,0);

  delay(370);
}