#include <Arduino.h>
#include <SD.h>
#include <TFT_eSPI.h>
#include <EEPROM.h>

#include <global.h>
#include <TFT_eSprite_X.h>
#include <MrBitmap.h>
#include <Monster.h>

TFT_eSPI tft = TFT_eSPI();

TFT_eSprite_X scene = TFT_eSprite_X(&tft);

String current_bg;
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

  EEPROM.begin(64);
  MonsterName stored_mon;
  EEPROM.get(0, stored_mon);
  if(stored_mon == Empty){
    stored_mon = RandomEgg;
  }
  mon.setCharacter(stored_mon);
  int stored_age;
  EEPROM.get(32, stored_age);
  mon._age = stored_age;

  current_bg = mon._data.bg;
  bg.setDimensions(64,64);
  bg.setSprite(current_bg,64,64);

  scene.createSprite(64,64);
}

void loop() {
  EEPROM.put(0, mon.get_name());
  EEPROM.put(32, mon.get_age());
  EEPROM.commit();

  while(mon.evo_ready()){
    mon.evolve();
    bg.setSprite(mon._data.bg, 64, 64);
  }

  for(int i = 0; i < 10; i++){
    if(entities[i] != NULL){
      entities[i]->update();
      entities[i]->pushSprite(&scene);
    }
  }

  mon.update();
  mon.pushSprite(&scene);

  scene.pushImageScaled(&tft,0,0);

  delay(400);
}