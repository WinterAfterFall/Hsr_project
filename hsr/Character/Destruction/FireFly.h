#ifndef FireFly_H
#define FireFly_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace FireFly{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Ult_func(Ally *ptr);//*
    void After_turn(Ally *ptr);
    void Start_game(Ally *ptr);
    
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->stats->Base_hp = 815;
        Ally_unit[num]->stats->Base_atk = 524;
        Ally_unit[num]->stats->Base_def = 776;
        Ally_unit[num]->Atv_stats->Base_speed = 104;
        Ally_unit[num]->stats->Max_energy = 240;
        Ally_unit[num]->stats->Ult_cost = 240;
        Ally_unit[num]->stats->Eidolon = E;
        Ally_unit[num]->stats->Element_type = "Fire";
        Ally_unit[num]->stats->Path = "Destruction";
        Ally_unit[num]->Atv_stats->Character_num = num;
        Ally_unit[num]->Atv_stats->Name = "FireFly";
        Ally_unit[num]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Atv_stats->ptr_to_unit = Ally_unit[num].get();
        unit[num] = Ally_unit[num]->Atv_stats->ptr_to_unit;

        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        
        // Ally_unit[num]->Turn_func = Turn_func;
        // Ally_unit[num]->stats->Ult_func = Ult_func;
        // Ally_unit[num]->stats->Char_func.Reset_func = Reset;
        // Ally_unit[num]->stats->Char_func.After_turn_func = After_turn;
        // Ally_unit[num]->stats->Char_func.Start_game_func = Start_game;
        
        //substats
        Ally_unit[num]->stats->Total_substats=15;
        Ally_unit[num]->stats->Separate_sub=15;
        Ally_unit[num]->stats->Reroll_check=1;

        Ally_unit[num]->stats->Substats.push_back({"Crit_dam",15});
        Ally_unit[num]->stats->Substats.push_back({"Crit_rate",0});
        Ally_unit[num]->stats->Substats.push_back({"Atk_percent",0});

        Ally_unit[num]->stats->Max_damage_Substats.resize(Ally_unit[num]->stats->Substats.size());
    }
    void Reset(Ally *ptr){
        ptr->Break_effect["None"]+=37.3;
        ptr->Atv_stats->Flat_speed+=5;

        //relic
        ptr->Atk_percent["None"]+=43.2;
        ptr->Atv_stats->Flat_speed+=25;
        ptr->Atk_percent["None"]+=43.2;
        ptr->Break_effect["None"]+=64.8;
        
        

        //substats


    }
    

    

    
}
#endif
