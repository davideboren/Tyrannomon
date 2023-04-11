#include <Arduino.h>
#include <SD.h>
#include <TFT_eSPI.h>
#include <global.h>
#include <Monster.h>

#include "../lib/TFT_eSprite_X/TFT_eSprite_X.h"
#include "../lib/MrBitmap/MrBitmap.h"


TFT_eSPI tft = TFT_eSPI();

TFT_eSprite_X bg = TFT_eSprite_X(&tft);
TFT_eSprite_X scene = TFT_eSprite_X(&tft);

Monster mon;

void setup() {

  Serial.begin(9600);
  //while(!Serial);

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(0x8);

  if(!SD.begin(SD_CS)){
    Serial.println("SD not found.");
    return;
  } else {
    Serial.println("SD initialized.");
  }

  mon.setCharacter("tyr_fsht.bmp");

  MrBitmap mrbg = MrBitmap();
  bg.createSprite(64,64);
  mrbg.loadBmp("bg.bmp",&bg);

  scene.createSprite(64,64);

}

void loop() {

  bg.pushToSprite(&scene,0,0);
  mon.update();
  mon.pushSprite(&scene);
  scene.pushImageScaled(&tft,0,0);

  delay(370);

  bg.pushToSprite(&scene,0,0);
  mon.update();
  mon.pushSprite(&scene);
  scene.pushImageScaled(&tft,0,0);

  delay(370);
}