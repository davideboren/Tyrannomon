#include <Monster.h>

Monster::Monster(){
    this->_x = 32 - 8;
    this->_y = 64 - 16 - 4;
    this->_xdir = 1;
    this->_ydir = 0;
    this->_w = 16;
    this->_h = 16;
    this->_sx = 0;
    this->_sy = 0;

    this->_age = 0;
}

Monster::Monster(MonsterName name){
    this->setCharacter(name);
}

void Monster::setCharacter(MonsterName name){
    spr.createSprite(48,64);
    MrBitmap mrb = MrBitmap();
    mrb.loadBmp(MonsterDB[name].filepath, &(this->spr));
    _data = MonsterDB[name];
    _name = name;
}

MonsterName Monster::get_name(){
    return _data.name;
}

int Monster::get_age(){
    return _age;
}

bool Monster::evo_ready(){
    return _age >= _data.lifespan;
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
    if (this->_data.stage == digitama){
        _x = 32 - 8;
        _y = 64 - 16 - 4;
    }
}

void Monster::update(){
    _age++;
    //Bounds
    if      ( _x <= -8 )    { _xdir =  1; }
    else if ( _x >= 56 )    { _xdir = -1; }

    else if (!random(4) && this->_data.stage != digitama){ //Change direction
        if (_xdir != 0)     { _xdir =  0; }
        else if (random(2)) { _xdir =  1; }
        else                { _xdir = -1; }
    }

    _x += _xdir*_data.speed;
    
    //Hatch logic
    if (this->_data.stage == digitama && _age >= this->_data.lifespan - 8){
        this->_sx = SPR_STAND2_X;
        this->_sy = SPR_STAND2_Y;
        if (_age >= this->_data.lifespan - 4){
            this->_sx = SPR_HATCH_X;
            this->_sy = SPR_HATCH_Y;
        }
        else if (_age == this->_data.lifespan - 8){
            _x -= 1;
        }
        else if (_age == this->_data.lifespan - 6){
            _x -= 2;
        }
        else if (_age == this->_data.lifespan - 5 || _age == this->_data.lifespan - 7){
            _x += 2;
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