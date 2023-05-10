#include <Arduino.h>
#include <SD.h>
#include <TFT_eSPI.h>
#include <global.h>
#include <Monster.h>

#include "../lib/TFT_eSprite_X/TFT_eSprite_X.h"
#include "../lib/MrBitmap/MrBitmap.h"


TFT_eSPI tft = TFT_eSPI();

TFT_eSprite_X scene = TFT_eSprite_X(&tft);

Entity bg;
Monster mon;

Entity* entities[10];

void setup() {

  Serial.begin(9600);
  
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(0x8);
  //while(!Serial);

  if(!SD.begin(SD_CS)){
    Serial.println("SD not found.");
    return;
  } else {
    Serial.println("SD initialized.");
  }


  entities[0] = &bg;
  entities[1] = &mon;

  bg.setDimensions(64,64);
  bg.setSprite("bg2.bmp",64,64);
  mon.setCharacter(Tyrannomon);

  scene.createSprite(64,64);

}

void loop() {

  for(int i = 0; i < 10; i++){
    if(entities[i] != NULL){
      entities[i]->update();
      entities[i]->pushSprite(&scene);
    }
  }

  scene.pushImageScaled(&tft,0,0);

  delay(350);
}