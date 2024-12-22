
#ifndef Luocha_H
#define Luocha_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Luocha{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Ult_func(Ally *ptr);//*
    void After_turn(Ally *ptr);
    void Start_game(Ally *ptr);
    
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->stats->Base_hp = 1280;
        Ally_unit[num]->stats->Base_atk = 756;
        Ally_unit[num]->stats->Base_def = 363;
        Ally_unit[num]->Atv_stats->Base_speed = 101;
        Ally_unit[num]->stats->Max_energy = 100;
        Ally_unit[num]->stats->Ult_cost = 100;
        Ally_unit[num]->stats->Eidolon = E;
        Ally_unit[num]->stats->Element_type = "Imaginary";
        Ally_unit[num]->stats->Path = "Abundance";
        Ally_unit[num]->Atv_stats->Character_num = num;
        Ally_unit[num]->Atv_stats->Name = "Luocha";
        Ally_unit[num]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Atv_stats->ptr_to_unit = Ally_unit[num].get();
        unit[num] = Ally_unit[num]->Atv_stats->ptr_to_unit;

        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        
        Ally_unit[num]->Turn_func = Turn_func;
        Ally_unit[num]->stats->Ult_func = Ult_func;
        Ally_unit[num]->stats->Char_func.Reset_func = Reset;
        Ally_unit[num]->stats->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->stats->Char_func.Start_game_func = Start_game;
    }
    void Reset(Ally *ptr){
        ptr->Atk_percent["None"]+=28;
        ptr->Hp_percent["None"]+=18;
        ptr->Def_percent["None"]+=12.5;

        //relic
        // bonus heal +35.7
        ptr->Atv_stats->Flat_speed+=25;
        ptr->Atk_percent["None"]+=43.2;
        ptr->stats->Energy_recharge+=19.4;
        
        

        //substats
        ptr->Atk_percent["None"]+=19.44; //5

        ptr->Atv_stats->Flat_speed+=34.5; //15


    }
    void Turn_func(Unit *ptr){
        Skill_point(1);
        Combat_data data_;
        data_.num = ptr->Atv_stats->Character_num;
        data_.Turn_reset = 1;

        data_.Action_type.first="Attack";
        data_.Action_type.second = "Basic_Attack";

        data_.Damage_element="Imaginary";
        data_.Damage_type.push_back("Basic_Attack");

        data_.Target_type="Single_target";
        data_.Damage_spilt.Main.push_back({30,0,0,3});
        data_.Damage_spilt.Main.push_back({30,0,0,3});
        data_.Damage_spilt.Main.push_back({40,0,0,4});
        Action_bar.push(data_);
        auto ally_ptr = dynamic_cast<Ally*>(ptr);
        Increase_energy(ally_ptr->stats.get(),20);
        if(ptr->Atv_stats->turn_cnt%2==1){
        data_ = Combat_data();
        data_.num = ptr->Atv_stats->Character_num;

        data_.Action_type.first="Buff";
        data_.Action_type.second = "Skill";

        data_.Damage_element="Imaginary";
        data_.Buff_type.push_back("Heal");

        data_.Target_type="Special";
        Action_bar.push(data_);
        Increase_energy(ally_ptr->stats.get(),30);
        ++ally_ptr->stats->Stack["Abyss_Flower"];
        if(ally_ptr->stats->Stack["Abyss_Flower"]==2){
            ally_ptr->stats->Buff_countdown["Cycle_of_Life"]= 2 + ptr->Atv_stats->turn_cnt;
            if(ally_ptr->stats->Eidolon>=1){
                for(int i=1;i<=Total_ally;i++){
                    Ally_unit[i]->Atk_percent["None"]+=20;
                }
            }
        }
        }
    }
    void Ult_func(Ally *ptr){
        if(ptr->stats->Stack["Abyss_Flower"]>=2)return;
        if(!Ult_use_check(ptr))return;
        Combat_data data_;
        data_.num = ptr->Atv_stats->Character_num;

        data_.Action_type.first="Attack";
        data_.Action_type.second = "Ultimate";

        data_.Damage_element="Imaginary";
        data_.Damage_type.push_back("Ultimate");

        data_.Target_type="Single_target";
        data_.Damage_spilt.Main.push_back({200,0,0,20});
        data_.Damage_spilt.Adjacent.push_back({200,0,0,20});
        data_.Damage_spilt.Other.push_back({200,0,0,20});
        Action_bar.push(data_);
        ++ptr->stats->Stack["Abyss_Flower"];
        if(ptr->stats->Stack["Abyss_Flower"]==2){
            ptr->stats->Buff_countdown["Cycle_of_Life"]= 2 + ptr->Atv_stats->turn_cnt ;
            if(ptr->stats->Eidolon>=1){
                for(int i=1;i<=Total_ally;i++){
                    Ally_unit[i]->Atk_percent["None"]+=20;
                }
            }
        }
        Deal_damage();
    }
    void After_turn(Ally *ptr){
        if(turn->Name=="Luocha"){
        
            if(ptr->stats->Buff_countdown["Cycle_of_Life"]==ptr->Atv_stats->turn_cnt){
                if(ptr->stats->Eidolon>=1){
                for(int i=1;i<=Total_ally;i++){
                    Ally_unit[i]->Atk_percent["None"]-=20;
                }
            }
            ptr->stats->Stack["Abyss_Flower"]=0;
            }
        }
    }
    void Start_game(Ally *ptr){
        if(ptr->stats->Technique==1){
            ptr->stats->Stack["Abyss_Flower"]=2;
            ptr->stats->Buff_countdown["Cycle_of_Life"]= 2 + ptr->Atv_stats->turn_cnt ;
            if(ptr->stats->Eidolon>=1){
                for(int i=1;i<=Total_ally;i++){
                    Ally_unit[i]->Atk_percent["None"]+=20;
                }
            }
        }
    }

    

    
}
#endif
