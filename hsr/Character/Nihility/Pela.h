
#ifndef Pela_H
#define Pela_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Pela{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Ult_func(Ally *ptr);//*
    void After_turn(Ally *ptr);
    void After_attack(Ally *ptr, Combat_data &data_);
    void Start_game(Ally *ptr);
    void Tune_stats(Ally *ptr);
    
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->stats->Base_hp = 988;
        Ally_unit[num]->stats->Base_atk = 547;
        Ally_unit[num]->stats->Base_def = 463;
        Ally_unit[num]->Atv_stats->Base_speed = 105;
        Ally_unit[num]->stats->Max_energy = 110;
        Ally_unit[num]->stats->Ult_cost = 110;
        Ally_unit[num]->stats->Eidolon = E;
        Ally_unit[num]->stats->Element_type = "Ice";
        Ally_unit[num]->stats->Path = "Nihility";
        Ally_unit[num]->Atv_stats->Character_num = num;
        Ally_unit[num]->Atv_stats->Name = "Pela";
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
        Ally_unit[num]->stats->Char_func.After_attack_func = After_attack;
        Ally_unit[num]->stats->Char_func.Start_game_func = Start_game;
        Ally_unit[num]->stats->Tune_stats_func = Tune_stats;

        //substats
        Ally_unit[num]->stats->Total_substats=20;
        Ally_unit[num]->stats->Separate_sub=20;

        Ally_unit[num]->stats->Substats.push_back({"Speed",20});

        Ally_unit[num]->stats->Max_damage_Substats.resize(Ally_unit[num]->stats->Substats.size());


    }
    void Reset(Ally *ptr){
        ptr->Dmg_bonus_each_element["Ice"]["None"]+=22.4;
        ptr->Atk_percent["None"]+=18;
        ptr->Effect_hit_rate+=10;

        //relic
        ptr->Effect_hit_rate+=43.2;
        ptr->Atv_stats->Flat_speed+=25;
        ptr->Atk_percent["None"]+=43.2;
        ptr->stats->Energy_recharge+=19.4;

        //substats

    }
    void Turn_func(Unit *ptr){
        Skill_point(1);
        Combat_data data_;
        data_.num = ptr->Atv_stats->Character_num;
        data_.Turn_reset = 1;

        data_.Action_type.first="Attack";
        data_.Action_type.second = "Basic_Attack";

        data_.Damage_element="Ice";
        data_.Damage_type.push_back("Basic_Attack");

        data_.Target_type="Single_target";
        data_.Damage_spilt.Main.push_back({55,0,0,5});
        data_.Damage_spilt.Main.push_back({55,0,0,5});
        Action_bar.push(data_);
        auto ally_ptr = dynamic_cast<Ally*>(ptr);
        Increase_energy(ally_ptr->stats.get(),20);
    }
    void Ult_func(Ally *ptr){
        for(int i=1;i<=Total_enemy;i++){
            if(Enemy_unit[i]->stats->Debuff["Zone_Suppression"]==0)break;
            if(i==Total_enemy)return;
        }
        if(!Ult_use_check(ptr))return;
        Combat_data data_;
        data_.num = ptr->Atv_stats->Character_num;

        data_.Action_type.first="Attack";
        data_.Action_type.second = "Ultimate";

        data_.Damage_element="Ice";
        data_.Damage_type.push_back("Ultimate");

        data_.Target_type="Single_target";
        data_.Damage_spilt.Main.push_back({108,0,0,20});
        data_.Damage_spilt.Adjacent.push_back({108,0,0,20});
        data_.Damage_spilt.Other.push_back({108,0,0,20});
        Action_bar.push(data_);
        for(int i=1;i<=Total_enemy;i++){
            Apply_debuff(ptr,Enemy_unit[i].get(),1);
            if(Enemy_unit[i]->stats->Debuff["Zone_Suppression"]==0){
                Enemy_unit[i]->stats->Debuff["Zone_Suppression"]=1;
                Enemy_unit[i]->Def_shred["None"]+=42;
                ++Enemy_unit[i]->stats->Total_debuff;
            }
            Enemy_unit[i]->stats->Debuff_time_count["Zone_Suppression"] = Enemy_unit[i]->Atv_stats->turn_cnt + 2;
        }
        Deal_damage();

    }
    void After_turn(Ally *ptr){
        if(turn->Side=="Enemy"){
            if(Enemy_unit[turn->Character_num]->stats->Debuff_time_count["Zone_Suppression"]==Enemy_unit[turn->Character_num]->Atv_stats->turn_cnt){
                Enemy_unit[turn->Character_num]->stats->Debuff["Zone_Suppression"]=0;
                Enemy_unit[turn->Character_num]->Def_shred["None"]-=42;
                --Enemy_unit[turn->Character_num]->stats->Total_debuff;
            }
            if(Enemy_unit[turn->Character_num]->stats->Debuff_time_count["Pela_Technique"]==turn->turn_cnt){
                Enemy_unit[turn->Character_num]->Def_shred["None"]-=20;
                --Enemy_unit[turn->Character_num]->stats->Total_debuff;
            }
        }
    }
    void After_attack(Ally *ptr, Combat_data &data_){
        if(data_.num!=ptr->Atv_stats->Character_num)return;
            int sz2 = data_.Damage_spilt.Adjacent.size();
            int sz3 = data_.Damage_spilt.Other.size();
        for(int i=1;i<=Total_enemy;i++){

            if(Enemy_unit[i]->stats->Target_type=="Main"){
                if(Enemy_unit[i]->stats->Total_debuff==0)continue;
                Increase_energy(ptr->stats.get(),11);
                break;
            }
            
            if(0<sz2 && Enemy_unit[i]->stats->Target_type=="Adjacent"){
                if(Enemy_unit[i]->stats->Total_debuff==0)continue;
                Increase_energy(ptr->stats.get(),11);
                break;
            }
            
            if(0<sz3 && Enemy_unit[i]->stats->Target_type=="Other"){
                if(Enemy_unit[i]->stats->Total_debuff==0)continue;
                Increase_energy(ptr->stats.get(),11);
                break;
            }
            
            
        }
        if(ptr->stats->Eidolon>=6){
            for(int i=1;i<=Total_enemy;i++){

            if(Enemy_unit[i]->stats->Target_type=="Main"){
                Combat_data temp = Combat_data();
                temp.num = ptr->Atv_stats->Character_num;

                temp.Action_type.first = "Attack";
                temp.Action_type.second = "Additional";

                temp.Damage_element = "Ice";
                temp.Damage_type.push_back("Additional");

                temp.Target_type = "Single_target";
        
                Cal_Additional_damage(temp,Enemy_unit[i].get(),{40,0,0,0});
            }
            
            if(0<sz2 && Enemy_unit[i]->stats->Target_type=="Adjacent"){
                Combat_data temp = Combat_data();
                temp.num = ptr->Atv_stats->Character_num;

                temp.Action_type.first = "Attack";
                temp.Action_type.second = "Additional";

                temp.Damage_element = "Ice";
                temp.Damage_type.push_back("Additional");

                temp.Target_type = "Single_target";
        
                Cal_Additional_damage(temp,Enemy_unit[i].get(),{40,0,0,0});
            }
            
            if(0<sz3 && Enemy_unit[i]->stats->Target_type=="Other"){
                Combat_data temp = Combat_data();
                temp.num = ptr->Atv_stats->Character_num;

                temp.Action_type.first = "Attack";
                temp.Action_type.second = "Additional";

                temp.Damage_element = "Ice";
                temp.Damage_type.push_back("Additional");

                temp.Target_type = "Single_target";
        
                Cal_Additional_damage(temp,Enemy_unit[i].get(),{40,0,0,0});
            }
            
            
        }
        }
    }
    void Start_game(Ally *ptr){
        
        if(ptr->stats->Technique==1){
        for(int i=1;i<=Total_enemy;i++){
            
                Apply_debuff(ptr,Enemy_unit[i].get(),1);
                Enemy_unit[i]->Def_shred["None"]+=20;
                Enemy_unit[i]->stats->Debuff_time_count["Pela_Technique"]=2;
                ++Enemy_unit[i]->stats->Total_debuff;
                
        }
            Increase_energy(ptr->stats.get(),20);
        }

    }
    void Tune_stats(Ally *ptr){
        Cal_effect_hit_rate(ptr,100);
    }
    

    
}
#endif
