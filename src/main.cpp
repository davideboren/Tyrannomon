#include <Arduino.h>
#include <SD.h>
#include <TFT_eSPI.h>
#include <EEPROM.h>

#include <global.h>
#include <TFT_eSprite_X.h>
#include <MrBitmap.h>
#include <Monster.h>
#include <Bubble.h>

TFT_eSPI tft = TFT_eSPI();

EventQueue queue = EventQueue();

TFT_eSprite_X scene = TFT_eSprite_X(&tft);

String current_bg;
Entity bg;

Monster mon;

Entity* entities[10];
Bubble* bubbles[3];

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(0));
  
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(0x8);
  //while(!Serial);

  if(!SD.begin(SD_CS)){
    Serial.println("SD not found.");
    return;
  } else {
    Serial.println("SD initialized.");
  }

  for(int i = 0; i < 3; i++){
    bubbles[i] = new Bubble;
  }

  entities[0] = &bg;

  EEPROM.begin(64);
  MonsterName stored_mon;
  EEPROM.get(0, stored_mon);
  if(stored_mon == Empty){
    stored_mon = RandomEgg;
  }
  mon.setCharacter(stored_mon);
  //mon.setCharacter(RandomEgg);
  int stored_age;
  EEPROM.get(32, stored_age);
  mon._age = stored_age;

  current_bg = mon._data.bg;
  bg.setSprite(current_bg);

  scene.createSprite(bg._w, bg._h);
}

void loop() {
  EEPROM.put(0, mon.get_name());
  EEPROM.put(32, mon.get_age());
  EEPROM.commit();

  for(int i = 0; i < 10; i++){
    if(queue.events[i] == REFRESH_BG){
      bg.setSprite(mon._data.bg);
    }
  }
  queue.clear();

  for(int i = 0; i < 10; i++){
    if(entities[i] != NULL){
      entities[i]->update();
      entities[i]->pushSprite(&scene);
    }
  }


  mon.update(queue.events);
  mon.pushSprite(&scene);

  if(current_bg == "bg/bg_underwater.bmp"){
    for(int i = 0; i < 3; i++){
      bubbles[i]->update();
      bubbles[i]->pushSprite(&scene);
    }
  }

  scene.pushSprite(0,0);
 
  delay(250);
}