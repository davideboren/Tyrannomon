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
        int _lifespan;
        bool _evo_mask;

        int _bound_l, _bound_r;

        void setCharacter(MonsterName name);
        MonsterName get_name();
        int get_age();
        bool evo_ready();
        void evolve();
        void update();

};

#endif //_MONSTER_H_