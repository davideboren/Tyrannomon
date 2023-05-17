#ifndef _MONSTER_H_
#define _MONSTER_H_

#include <Arduino.h>

#include <global.h>
#include <TFT_eSprite_X.h>
#include <MrBitmap.h>
#include <Entity.h>
#include <MonsterDefs.h>

class Monster : public Entity{

    public:
        Monster();
        Monster(MonsterName name);

        MonsterRef _data;
        MonsterName _name;
        int _age;

        void setCharacter(MonsterName name);
        MonsterName get_name();
        int get_age();
        void update();

};

#endif //_MONSTER_H_