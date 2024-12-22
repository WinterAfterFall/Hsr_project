
#ifndef Aventurine_H
#define Aventurine_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Aventurine{
    void Set_up(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Ult_func(Ally *ptr);//*
    void After_turn(Ally *ptr);
    void Before_attack(Ally *ptr, Combat_data &data_);
    void Enemy_hit_func(Ally *ptr, Enemy *target);

    void Set_up(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->stats->Base_hp = 1203;
        Ally_unit[num]->stats->Base_atk = 446;
        Ally_unit[num]->stats->Base_def = 655;
        Ally_unit[num]->Atv_stats->Base_speed = 106;
        Ally_unit[num]->stats->Max_energy = 110;
        Ally_unit[num]->stats->Ult_cost = 110;
        Ally_unit[num]->stats->Eidolon = E;
        Ally_unit[num]->stats->Element_type = "Imaginary";
        Ally_unit[num]->stats->Path = "Preservation";
        Ally_unit[num]->Atv_stats->Character_num = num;
        Ally_unit[num]->Atv_stats->Name = "Aventurine";
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
        Ally_unit[num]->stats->Char_func.Before_attack_func = Before_attack;
        Ally_unit[num]->stats->Char_func.Enemy_hit_func = Enemy_hit_func;
        
    }
    void Reset(Ally *ptr){
        ptr->Dmg_bonus_each_element["Imaginary"]["None"]+=14.4;
        ptr->Def_percent["None"]+=35;

        //relic
        ptr->Def_percent["None"]+=54;
        ptr->Atv_stats->Flat_speed+=25;
        ptr->Def_percent["None"]+=54;
        if(ptr->stats->Eidolon==0){
            ptr->Def_percent["None"]+=54;
        }else{
            ptr->stats->Energy_recharge+=19.4;
        }
        

        //substats
        ptr->Def_percent["None"]+=68.04; //14
        ptr->Atv_stats->Flat_speed+=13.8; //6
        if(ptr->stats->Eidolon>=1){
        for(int i=1;i<=Total_ally;i++){
            Ally_unit[i]->Crit_dam["None"]+=20;
        }
        }


    }
    void Turn_func(Unit *ptr){
        Combat_data temp;
        if(ptr->Atv_stats->turn_cnt<=4||ptr->Atv_stats->turn_cnt%3!=2||Ally_unit[ptr->Atv_stats->Character_num]->stats->Eidolon>=1){
            Skill_point(1);
            temp.num = ptr->Atv_stats->Character_num;
            temp.Turn_reset = 1;

            temp.Action_type.first = "Attack";
            temp.Action_type.second = "Basic_Attack";

            temp.Damage_element = "Imaginary";
            temp.Damage_type.push_back("Basic_Attack");

            temp.Target_type = "Single_target";
            temp.Damage_spilt.Main.push_back({0,0,100,10});
            
            Increase_energy(Ally_unit[ptr->Atv_stats->Character_num]->stats.get(),20);
            if(Ally_unit[ptr->Atv_stats->Character_num]->stats->Eidolon>=2){
                ++Ally_unit[ptr->Atv_stats->Character_num]->stats->Buff_note["Basic_Attack_Target_Choose"];
                if(Ally_unit[ptr->Atv_stats->Character_num]->stats->Buff_note["Basic_Attack_Target_Choose"]>Total_enemy||Ally_unit[ptr->Atv_stats->Character_num]->stats->Buff_note["Basic_Attack_Target_Choose"]>3){
                    Ally_unit[ptr->Atv_stats->Character_num]->stats->Buff_note["Basic_Attack_Target_Choose"]=1;
                }
                if(Enemy_unit[Ally_unit[ptr->Atv_stats->Character_num]->stats->Buff_note["Basic_Attack_Target_Choose"]]->stats->Debuff["Bounded_Rationality"]==0){
                    Enemy_unit[Ally_unit[ptr->Atv_stats->Character_num]->stats->Buff_note["Basic_Attack_Target_Choose"]]->Respen["None"]+=12;
                    Enemy_unit[Ally_unit[ptr->Atv_stats->Character_num]->stats->Buff_note["Basic_Attack_Target_Choose"]]->stats->Debuff["Bounded_Rationality"]=1;
                    ++Enemy_unit[Ally_unit[ptr->Atv_stats->Character_num]->stats->Buff_note["Basic_Attack_Target_Choose"]]->stats->Total_debuff;
                }
                Enemy_unit[Ally_unit[ptr->Atv_stats->Character_num]->stats->Buff_note["Basic_Attack_Target_Choose"]]->stats->Debuff_time_count["Bounded_Rationality"]=Enemy_unit[Ally_unit[ptr->Atv_stats->Character_num]->stats->Buff_note["Basic_Attack_Target_Choose"]]->Atv_stats->turn_cnt+3;
                Apply_debuff(Ally_unit[ptr->Atv_stats->Character_num].get(),Enemy_unit[Ally_unit[ptr->Atv_stats->Character_num]->stats->Buff_note["Basic_Attack_Target_Choose"]].get(),1);
               

            }
        }else{
            Skill_point(-1);
            temp.num = ptr->Atv_stats->Character_num;
            temp.Turn_reset = 1;

            temp.Action_type.first = "Buff";
            temp.Action_type.second = "Skill";

            temp.Buff_type.push_back("Shield");

            temp.Target_type = "Aoe";
            Increase_energy(Ally_unit[ptr->Atv_stats->Character_num]->stats.get(),30);
        }
        Action_bar.push(temp);
        if(ptr->Atv_stats->turn_cnt%3==2){
            Combat_data temp2;
            temp2.num = ptr->Atv_stats->Character_num;

            temp2.Action_type.first = "Attack";
            temp2.Action_type.second = "Fua";

            temp2.Damage_element = "Imaginary";
            temp2.Damage_type.push_back("Fua");
            temp2.Buff_type.push_back("Shield");

            temp2.Target_type = "Bounce";
            temp2.Damage_spilt.Main.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Main.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Main.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Main.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Adjacent.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Adjacent.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Adjacent.push_back({0,0,25,1.0/3.0});
            Action_bar.push(temp2);
        }
        
    }
    void Ult_func(Ally *ptr){
        if(Ult_use_check(ptr)){
            
            Combat_data temp;
            temp.num = ptr->Atv_stats->Character_num;

            temp.Action_type.first = "Attack";
            temp.Action_type.second = "Ultimate";

            temp.Damage_element = "Imaginary";
            temp.Damage_type.push_back("Ultimate");

            temp.Target_type = "Single_target";
            temp.Damage_spilt.Main.push_back({0,0,270,10});
            Action_bar.push(temp);
            ptr->stats->Stack["Shot_Loaded_Right"]+=4;
            if(ptr->stats->Eidolon>=1){
                Combat_data temp3;
                temp3.num = ptr->Atv_stats->Character_num;

                temp3.Action_type.first = "Buff";
                temp3.Action_type.second = "Ultimate";

                temp3.Buff_type.push_back("Shield");

                temp3.Target_type = "Aoe";
                Action_bar.push(temp3);
            }
            if(ptr->stats->Stack["Shot_Loaded_Right"]>=7){
                ptr->stats->Stack["Shot_Loaded_Right"]-=7;
                Combat_data temp2;
            temp2.num = ptr->Atv_stats->Character_num;

            temp2.Action_type.first = "Attack";
            temp2.Action_type.second = "Fua";

            temp2.Damage_element = "Imaginary";
            temp2.Damage_type.push_back("Fua");
            temp2.Buff_type.push_back("Shield");
            
            temp2.Target_type = "Bounce";
            temp2.Damage_spilt.Main.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Main.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Main.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Main.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Adjacent.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Adjacent.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Adjacent.push_back({0,0,25,1.0/3.0});
            Action_bar.push(temp2);
            }
            Apply_debuff(ptr,Enemy_unit[Main_Enemy_num].get(),1);
            if(Enemy_unit[Main_Enemy_num]->stats->Debuff["Roulette_Shark"]==0){
                Enemy_unit[Main_Enemy_num]->Crit_dam["None"]+=15;
                Enemy_unit[Main_Enemy_num]->stats->Debuff["Roulette_Shark"]=1;
                ++Enemy_unit[Main_Enemy_num]->stats->Total_debuff;
            }
            Enemy_unit[Main_Enemy_num]->stats->Debuff_time_count["Roulette_Shark"]= 3 + Enemy_unit[Main_Enemy_num]->Atv_stats->turn_cnt;
            Deal_damage();
        }
    }
    void After_turn(Ally *ptr){
        if(turn->Name=="Enemy_Main"&&Enemy_unit[turn->Character_num]->stats->Debuff_time_count["Roulette_Shark"]==turn->turn_cnt){
            Enemy_unit[Main_Enemy_num]->Crit_dam["None"]-=15;
                Enemy_unit[Main_Enemy_num]->stats->Debuff["Roulette_Shark"]=0;
            --Enemy_unit[Main_Enemy_num]->stats->Total_debuff;
        }
        if(turn->Side=="Enemy"&&Enemy_unit[turn->Character_num]->stats->Debuff_time_count["Bounded_Rationality"]==turn->turn_cnt&&Enemy_unit[turn->Character_num]->stats->Debuff["Bounded_Rationality"]==1){
            Enemy_unit[turn->Character_num]->Respen["None"]-=12;
            Enemy_unit[turn->Character_num]->stats->Debuff["Bounded_Rationality"]=0;
            --Enemy_unit[turn->Character_num]->stats->Total_debuff;
        }
    }
    void Before_attack(Ally *ptr, Combat_data &data_){
        if(Ally_unit[data_.num]->Atv_stats->Name=="Aventurine"){
            ptr->Crit_rate["None"]-=ptr->stats->Buff_note["Leverage"];
            if(((ptr->Def_percent["None"]*ptr->stats->Base_def)+ptr->Def_flat["None"])>=1600);
            ptr->stats->Buff_note["Leverage"] = floor(((ptr->Def_percent["None"]*ptr->stats->Base_def)+ptr->Def_flat["None"]-1600)/100)*2;
            if(ptr->stats->Buff_note["Leverage"]>=48){
                ptr->stats->Buff_note["Leverage"] = 48;
            }
            ptr->Crit_rate["None"]+=ptr->stats->Buff_note["Leverage"];

        }
    }
    void Enemy_hit_func(Ally *ptr, Enemy *target){
        ptr->stats->Stack["Shot_Loaded_Right"]+=5;
        if(ptr->stats->Stack["Shot_Loaded_Right"]>=7){
                ptr->stats->Stack["Shot_Loaded_Right"]-=7;
                Combat_data temp2;
            temp2.num = ptr->Atv_stats->Character_num;

            temp2.Action_type.first = "Attack";
            temp2.Action_type.second = "Fua";

            temp2.Damage_element = "Imaginary";
            temp2.Damage_type.push_back("Fua");
            temp2.Buff_type.push_back("Shield");
            
            temp2.Target_type = "Bounce";
            temp2.Damage_spilt.Main.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Main.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Main.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Main.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Adjacent.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Adjacent.push_back({0,0,25,1.0/3.0});
            temp2.Damage_spilt.Adjacent.push_back({0,0,25,1.0/3.0});
            Action_bar.push(temp2);
            Deal_damage();
            }
    }
}
#endif
