
#ifndef Jingyuan_H
#define Jingyuan_H

#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Jingyuan{
    void Setup_Jingyuan(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void After_turn(Ally *ptr);
    void Before_attack(Ally *ptr, Combat_data &data_);
    void After_attack(Ally *ptr, Combat_data &data_);
    void Start_game(Ally *ptr);
    void Ult_func(Ally *ptr);//*
    void Fix_Slow_Jingyuan(Ally *ptr);
    bool Temp_Turn_Condition(Unit *ptr);
    bool Robin_temp(Unit *ptr);
    bool Temp_ult_Condition(Ally *ptr);

    /*
    void Setup_Jingyuan(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Before_turn(Ally *ptr);
    void After_turn(Ally *ptr);
    void Before_attack(Ally *ptr, Combat_data &data_);
    void After_attack(Ally *ptr, Combat_data &data_);
    void Buff_func(Ally *ptr, Combat_data &data_);
    void Dot_func(Enemy *target, Ally *ptr, double Dot_ratio);
    void Toughness_break_func(Ally *ptr, Enemy *target, int num);
    void Enemy_hit_func(Ally *ptr, Enemy *target);
    void Start_game(Ally *ptr);
    void Start_wave(Ally *ptr);
    void Apply_debuff_func(Ally *ptr, Enemy *target, int total_debuff);
    void Hit_func(Ally *ptr, int Hit_cnt);
    void Ult_func(Ally *ptr);//*
    */
    void Fix_Slow_Jingyuan(Ally *ptr){

        ptr->stats->Total_substats=20;
        ptr->stats->Separate_sub=20;
        ptr->stats->Substats[0].second = 20;

         ptr->stats->Char_func.Reset_func = [](Ally *ptr){
        ptr->Atk_percent["None"]+=28;
        ptr->Crit_rate["None"]+=12;
        ptr->Def_percent["None"]+=12.5;


        //relic
        ptr->Crit_rate["None"]+=32.4;
        ptr->Atk_percent["None"]+=43.2;
        ptr->Dmg_bonus_each_element["Lightning"]["None"]+=38.8;
        ptr->Atk_percent["None"]+=43.2;

        //LL
        ptr->stats->Stack["LL_stack"]=3;
        ptr->stats->Summon_ptr->Atv_stats->Flat_speed=0;
        ptr->stats->Summon_ptr->Atv_stats->Speed_percent=0;
        };

    }
    void Reset(Ally *ptr){
        ptr->Atk_percent["None"]+=28;
        ptr->Crit_rate["None"]+=12;
        ptr->Def_percent["None"]+=12.5;


        //relic
        ptr->Crit_rate["None"]+=32.4;
        ptr->Atv_stats->Flat_speed+=25;
        ptr->Dmg_bonus_each_element["Lightning"]["None"]+=38.8;
        ptr->Atk_percent["None"]+=43.2;

        //substats
        ptr->Atv_stats->Flat_speed+=11.5;

        //LL
        ptr->stats->Stack["LL_stack"]=3;
        ptr->stats->Summon_ptr->Atv_stats->Flat_speed=0;
        ptr->stats->Summon_ptr->Atv_stats->Speed_percent=0;

        
    }
    void Setup_Jingyuan(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->stats->Base_hp = 1164;
        Ally_unit[num]->stats->Base_atk = 698;
        Ally_unit[num]->stats->Base_def = 485;
        Ally_unit[num]->Atv_stats->Base_speed = 99;
        Ally_unit[num]->stats->Max_energy = 130;
        Ally_unit[num]->stats->Ult_cost = 130;
        Ally_unit[num]->stats->Eidolon = E;
        Ally_unit[num]->stats->Element_type = "Lightning";
        Ally_unit[num]->stats->Path = "Erudition";
        Ally_unit[num]->Atv_stats->Character_num = num;
        Ally_unit[num]->Atv_stats->Name = "Jingyuan";
        Ally_unit[num]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Atv_stats->ptr_to_unit = Ally_unit[num].get();
        unit[num] = Ally_unit[num]->Atv_stats->ptr_to_unit;
        Ally_unit[num]->stats->Ult_priority = 2;

        //substats
        Ally_unit[num]->stats->Total_substats=15;
        Ally_unit[num]->stats->Separate_sub=15;
        Ally_unit[num]->stats->Reroll_check=1;

        Ally_unit[num]->stats->Substats.push_back({"Crit_dam",15});
        Ally_unit[num]->stats->Substats.push_back({"Crit_rate",0});
        Ally_unit[num]->stats->Substats.push_back({"Atk_percent",0});

        Ally_unit[num]->stats->Max_damage_Substats.resize(Ally_unit[num]->stats->Substats.size());


        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        Ally_unit[num]->Turn_func = Turn_func;
        Ally_unit[num]->stats->Ult_func = Ult_func;
        Ally_unit[num]->stats->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->stats->Char_func.Start_game_func = Start_game;




        
        

        Ally_unit[num]->stats->Char_func.Reset_func = Reset;

        //LL
        Ally_unit[num]->stats->Summon_ptr =  make_unique<Unit>();
        Ally_unit[num]->stats->Summon_ptr->Atv_stats->Base_speed = 60;
        Ally_unit[num]->stats->Summon_ptr->Atv_stats->Character_num = num;
        Ally_unit[num]->stats->Summon_ptr->Atv_stats->Name = "LL";
        Ally_unit[num]->stats->Summon_ptr->Atv_stats->Side = "Summon";
        Ally_unit[num]->stats->Summon_ptr->Atv_stats->ptr_to_unit = Ally_unit[num]->stats->Summon_ptr.get();
        Ally_unit[num]->stats->Summon_ptr->Turn_func = [](Unit *ptr){
            auto ally_ptr = dynamic_cast<Ally*>(Ally_unit[ptr->Atv_stats->Character_num].get());
            if(ally_ptr->stats->Stack["LL_stack"]>=6){
                ally_ptr->Crit_dam["Summon"]+=25;
            }
            Combat_data temp;
            temp.Action_type.first = "Attack";
            temp.Action_type.second = "Fua";
            temp.Damage_type.push_back("Fua");
            temp.Damage_type.push_back("Summon");
            temp.Damage_element="Lightning";
            temp.Target_type="Blast";
            temp.Turn_reset = 1;
            temp.num = ptr->Atv_stats->Character_num;
            //cout<<"                         LL stack = "<<Ally_unit[1]->stats->Stack["LL_stack"]<<endl;
            for(int i=1;i<=Ally_unit[ptr->Atv_stats->Character_num]->stats->Stack["LL_stack"];i++){
                temp.Damage_spilt.Main.push_back({66,0,0,5});
                if(Ally_unit[ptr->Atv_stats->Character_num]->stats->Eidolon>=1){
                    temp.Damage_spilt.Adjacent.push_back({33,0,0,0});
                }else{
                    temp.Damage_spilt.Adjacent.push_back({66*0.25,0,0,0});
                }
                
            }

            if(ally_ptr->stats->Stack["LL_stack"]>=6){
                ally_ptr->Crit_dam["Summon"]-=25;
            }
    
            turn->Flat_speed = 0;
            ally_ptr->stats->Stack["LL_stack"] = 3;
            
            
            if(Ally_unit[ptr->Atv_stats->Character_num]->stats->Eidolon>=2){
            if(ally_ptr->stats->Buff_countdown["Swing_Skies_Squashed"]<=ptr->Atv_stats->turn_cnt){
                ptr->Dmg_bonus["Basic_Attack"]+=20;
                ptr->Dmg_bonus["Skill"]+=20;
                ptr->Dmg_bonus["Ultimate"]+=20;
            }
            ally_ptr->stats->Buff_countdown["Swing_Skies_Squashed"] = ptr->Atv_stats->turn_cnt+2;
            }
            Action_bar.push(temp);
            

        };

        
        

         
            
    }
    void Turn_func(Unit *ptr){
        
        Combat_data temp;
        temp.Turn_reset=true;
        temp.num = ptr->Atv_stats->Character_num;
        if((sp<=Sp_Safety && Robin_temp(ptr)||ptr->Atv_stats->turn_cnt==1)&&Sp_status=="Negative"){
            cout<<"                      **********Basic"<<endl;
                Skill_point(1);
                temp.Target_type = "Single_target";
                temp.Action_type.first = "Attack";
                temp.Action_type.second = "Basic_Attack";
                temp.Damage_element="Lightning";
                temp.Damage_type.push_back("Basic_Attack");
                temp.Damage_spilt.Main.push_back({55,0,0,5.5});
                temp.Damage_spilt.Main.push_back({45,0,0,4.5});
                Increase_energy(Ally_unit[ptr->Atv_stats->Character_num]->stats.get(),20);


        }else{
        Skill_point(-1);
        Increase_energy(Ally_unit[ptr->Atv_stats->Character_num]->stats.get(),30);
        temp.Target_type = "Aoe";
        temp.Action_type.first = "Attack";
        temp.Action_type.second = "Skill";
        temp.Damage_element="Lightning";
        temp.Damage_type.push_back("Skill");
        temp.Buff_type.push_back("Buff");
        temp.Damage_spilt.Main.push_back({40,0,0,4});
        temp.Damage_spilt.Main.push_back({30,0,0,3});
        temp.Damage_spilt.Main.push_back({30,0,0,3});

        temp.Damage_spilt.Adjacent.push_back({40,0,0,4});
        temp.Damage_spilt.Adjacent.push_back({30,0,0,3});
        temp.Damage_spilt.Adjacent.push_back({30,0,0,3});

        temp.Damage_spilt.Other.push_back({40,0,0,4});
        temp.Damage_spilt.Other.push_back({30,0,0,3});
        temp.Damage_spilt.Other.push_back({30,0,0,3});
        
        auto ally_ptr = dynamic_cast<Ally*>(ptr);

        if(ally_ptr->stats->Buff_countdown["War_Marshal"]<ally_ptr->Atv_stats->turn_cnt||((turn->Character_num!=ptr->Atv_stats->Character_num||turn->Side!="Ally")&&ally_ptr->stats->Buff_countdown["War_Marshal"]==ally_ptr->Atv_stats->turn_cnt)){
            ally_ptr->Crit_rate["None"]+=10;

        }
        ally_ptr->stats->Buff_countdown["War_Marshal"] = ally_ptr->Atv_stats->turn_cnt+2;
        ally_ptr->stats->Stack["LL_stack"]+=2;
        if(ally_ptr->stats->Stack["LL_stack"]>=10){
            ally_ptr->stats->Summon_ptr->Atv_stats->Flat_speed=70;
            Speed_Buff(ally_ptr->stats->Summon_ptr->Atv_stats.get(),0,0);
        }else{
            Speed_Buff(ally_ptr->stats->Summon_ptr->Atv_stats.get(),0,20);
        }
        
        }
        Action_bar.push(temp);
        
        
        
    }

    void Ult_func(Ally *ptr){
        if(((turn->Name!="Jingyuan"||Ult_After_Turn==1)&&Robin_temp(ptr)) || !Ult_use_check(ptr))return;
            Combat_data temp;
            cout<<"                      Jingyuan Ult"<<endl;
            temp.num = ptr->Atv_stats->Character_num;
            temp.Action_type.first = "Attack";
            temp.Action_type.second = "Ultimate";
            temp.Damage_type.push_back("Ultimate");
            temp.Damage_element="Lightning";
            temp.Target_type="Aoe";
            temp.Damage_spilt.Main.push_back({200,0,0,20});
            temp.Damage_spilt.Adjacent.push_back({200,0,0,20});
            temp.Damage_spilt.Other.push_back({200,0,0,20});
            ptr->stats->Stack["LL_stack"]+=3;
            if(ptr->stats->Stack["LL_stack"]>=10){
            ptr->stats->Summon_ptr->Atv_stats->Flat_speed=70;
            Speed_Buff(ptr->stats->Summon_ptr->Atv_stats.get(),0,0);
        }else{
            Speed_Buff(ptr->stats->Summon_ptr->Atv_stats.get(),0,30);
        }
            
            Action_bar.push(temp);
            Deal_damage();
    }
    void After_turn(Ally *ptr){
        if(!(ptr->Atv_stats->Character_num == turn->Character_num && turn->Side=="Ally"))return;
        if(ptr->stats->Buff_countdown["War_Marshal"]==ptr->Atv_stats->turn_cnt){
            ptr->Crit_rate["None"]-=10;
        }
        if(ptr->stats->Eidolon>=2&&ptr->stats->Buff_countdown["Swing_Skies_Squashed"]==ptr->Atv_stats->turn_cnt){
                ptr->Dmg_bonus["Basic_Attack"]-=20;
                ptr->Dmg_bonus["Skill"]-=20;
                ptr->Dmg_bonus["Ultimate"]-=20;
        }
    }
    void Start_game(Ally *ptr){
        if(ptr->stats->Technique==1){
            ptr->stats->Stack["LL_stack"]+=3;
            Speed_Buff(ptr->stats->Summon_ptr->Atv_stats.get(),0,30);
        }
        Increase_energy(ptr->stats.get(),15);
    }
    bool Temp_Turn_Condition(Unit *ptr){
        return true;
    }
    bool Temp_ult_Condition(Ally *ptr){
        return true;
    }
    bool Robin_temp(Unit *ptr){
        if(Robin_num!=0&&Ally_unit[Robin_num]->Atv_stats->Base_speed==-1){
            return false;
        }
        return true;
    }
}
#endif