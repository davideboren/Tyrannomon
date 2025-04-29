#include <Monster.h>

Monster::Monster(){
    this->_x = 64 - 16;
    this->_y = 128 - 32 - 12;
    this->_xdir = 1;
    this->_ydir = 0;
    this->_w = 32;
    this->_h = 32;
    this->_sx = 0;
    this->_sy = 0;

    _age = 0;
    _lifespan = 10;
    _evo_mask = false;

    _bound_l = -16;
    _bound_r = 112;
}

Monster::Monster(MonsterName name){
    this->setCharacter(name);
}

void Monster::setCharacter(MonsterName name){
    MrBitmap mrb = MrBitmap();
    int w = mrb.get_width(MonsterDB[name].filepath)*2;
    int h = mrb.get_height(MonsterDB[name].filepath)*2;
    spr.deleteSprite();
    spr.createSprite(w,h);
    mrb.loadBmp(MonsterDB[name].filepath, &(this->spr), 2);
    _data = MonsterDB[name];
    _name = name;

    //Convert  to halfseconds
    _lifespan = _data.lifespan*120;
}

MonsterName Monster::get_name(){
    return _data.name;
}

int Monster::get_age(){
    return _age;
}

bool Monster::evo_ready(){
    return _age >= _lifespan;
}

void Monster::evolve(){
    int num_evos = 0; 
    for(int i = 0; i < 8; i++){
        if(MonsterDB[_name].evos[i] != Empty){
            num_evos++;
        }
    }
    int evo_choice = random(0, num_evos);
    MonsterName next_mon = MonsterDB[_name].evos[evo_choice];
    setCharacter(next_mon);
    _age = 0;
    _evo_mask = false;
    if (this->_data.stage == digitama){
        _x = 64 - 16;
        _y = 128 - 32 - 12;
    }
}

void Monster::update(Event events[10]){
    _age++;

    if(false){
        Serial.print(_age);
        Serial.print("/");
        Serial.println(_lifespan);
    }

    if(_age >= _lifespan){
        evolve();
        queue.push(REFRESH_BG);
    }
    //Evo grid mask
    if(_data.stage != digitama && _data.stage != baby){
        int time_left = _lifespan - _age;
        bool need_mask = time_left < 600 || _lifespan - time_left < 600;
        if(_evo_mask != need_mask){
                _evo_mask = !_evo_mask;
                MrBitmap mrb = MrBitmap();
                if(_evo_mask){
                    mrb.loadBmp(MonsterDB[_name].filepath, &(this->spr), 2, 0x5e06);
                }
                else {
                    mrb.loadBmp(MonsterDB[_name].filepath, &(this->spr), 2);
                }
        }
    }

    //Bounds
    if (_x <= _bound_l) _xdir =  1; 
    else if (_x >= _bound_r) _xdir = -1; 

    else if (!random(4) && this->_data.stage != digitama){ //Change direction
        if (_xdir != 0)     { _xdir =  0; }
        else if (random(2)) { _xdir =  1; }
        else                { _xdir = -1; }
    }

    _x += _xdir*_data.speed;
    
    //Hatch logic
    if (this->_data.stage == digitama && _age >= this->_lifespan - 8){
        this->_sx = SPR_STAND2_X;
        this->_sy = SPR_STAND2_Y;
        if (_age >= this->_lifespan - 4){
            this->_sx = SPR_HATCH_X;
            this->_sy = SPR_HATCH_Y;
        }
        else if (_age == this->_lifespan - 8){
            _x -= 2;
        }
        else if (_age == this->_lifespan - 6){
            _x -= 4;
        }
        else if (_age == this->_lifespan - 5 || _age == this->_lifespan - 7){
            _x += 4;
        }
    }
    else if(this->_sx == SPR_STAND2_X && this->_sy == SPR_STAND2_Y){
        int dice = 1;
        if(this->_data.stage != digitama){
            dice = random(6);
        }
        if(dice == 5){
            this->_sx = SPR_HAPPY_X;
            this->_sy = SPR_HAPPY_Y;
        }
        else if(dice == 4){
            this->_sx = SPR_ANGRY_X;
            this->_sy = SPR_ANGRY_Y;
        }
        else{
            this->_sx = SPR_STAND1_X;
            this->_sy = SPR_STAND1_Y;
        }
    }
    else {
        this->_sx = SPR_STAND2_X;
        this->_sy = SPR_STAND2_Y;
    }
}