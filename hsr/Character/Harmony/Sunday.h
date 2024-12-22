
#ifndef Sunday_H
#define Sunday_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Sunday{
    void Setup_Slow_Sunday(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Setup_Fast_Sunday(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset_Slow_Sunday(Ally *ptr);
    void Reset_Fast_Sunday(Ally *ptr);
    void Turn_func_Slow_Sunday(Unit *ptr);
    void Turn_func_Fast_Sunday(Unit *ptr);
    void Before_turn(Ally *ptr);
    void After_turn(Ally *ptr);
    void Before_attack(Ally *ptr, Combat_data &data_);
    void Start_game(Ally *ptr);
    void Ult_func(Ally *ptr);//*
    void Buff_func(Ally *ptr, Combat_data &data_);
    bool Robin_temp(Unit *ptr);

    


    
    void Reset_Slow_Sunday(Ally *ptr){
        ptr->Crit_dam["None"]+=37.3;
        ptr->Def_percent["None"]+=12.5;

        //relic
        ptr->Crit_dam["None"]+=64.8;
        ptr->Atv_stats->Flat_speed+=25;
        ptr->Hp_percent["None"]+=43.2;
        ptr->stats->Energy_recharge+=19.4;

        //substats
        ptr->Crit_dam["None"]+=110.2;
        ptr->Atv_stats->Flat_speed+=2.3;
    }
    void Reset_Fast_Sunday(Ally *ptr){
        ptr->Crit_dam["None"]+=37.3;
        ptr->Def_percent["None"]+=12.5;

        //relic
        ptr->Crit_dam["None"]+=64.8;
        ptr->Atv_stats->Flat_speed+=25;
        ptr->Hp_percent["None"]+=43.2;
        ptr->stats->Energy_recharge+=19.4;

        //substats
        ptr->Atv_stats->Flat_speed+=29.9;
        ptr->Crit_dam["None"]+=40.6;
    }
    void Setup_Slow_Sunday(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->stats->Base_hp = 1242;
        Ally_unit[num]->stats->Base_atk = 640;
        Ally_unit[num]->stats->Base_def = 533;
        Ally_unit[num]->Atv_stats->Base_speed = 96;
        Ally_unit[num]->stats->Max_energy = 130;
        Ally_unit[num]->stats->Ult_cost = 130;
        Ally_unit[num]->stats->Eidolon = E;
        Ally_unit[num]->stats->Element_type = "Imaginary";
        Ally_unit[num]->stats->Path = "Harmony";
        Ally_unit[num]->Atv_stats->Character_num = num;
        Ally_unit[num]->Atv_stats->Name = "Sunday";
        Ally_unit[num]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Atv_stats->ptr_to_unit = Ally_unit[num].get();
        unit[num] = Ally_unit[num]->Atv_stats->ptr_to_unit;

        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        Ally_unit[num]->Turn_func = Turn_func_Slow_Sunday;
        Ally_unit[num]->stats->Ult_func = Ult_func;
        Ally_unit[num]->stats->Char_func.Reset_func = Reset_Slow_Sunday;
        Ally_unit[num]->stats->Char_func.Before_turn_func = Before_turn;
        Ally_unit[num]->stats->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->stats->Char_func.Before_attack_func = Before_attack;
        Ally_unit[num]->stats->Char_func.Start_game_func = Start_game;


    }
    void Setup_Fast_Sunday(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->stats->Base_hp = 1242;
        Ally_unit[num]->stats->Base_atk = 640;
        Ally_unit[num]->stats->Base_def = 533;
        Ally_unit[num]->Atv_stats->Base_speed = 96;
        Ally_unit[num]->stats->Max_energy = 130;
        Ally_unit[num]->stats->Ult_cost = 130;
        Ally_unit[num]->stats->Eidolon = E;
        Ally_unit[num]->stats->Element_type = "Imaginary";
        Ally_unit[num]->stats->Path = "Harmony";
        Ally_unit[num]->Atv_stats->Character_num = num;
        Ally_unit[num]->Atv_stats->Name = "Sunday";
        Ally_unit[num]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Atv_stats->ptr_to_unit = Ally_unit[num].get();
        unit[num] = Ally_unit[num]->Atv_stats->ptr_to_unit;
        Ally_unit[num]->stats->Ult_priority = 1;

        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());

        Ally_unit[num]->Turn_func = Turn_func_Fast_Sunday;
        Ally_unit[num]->Turn_func = Turn_func_Slow_Sunday;//*

        Ally_unit[num]->stats->Ult_func = Ult_func;
        Ally_unit[num]->stats->Char_func.Reset_func = Reset_Fast_Sunday;
        Ally_unit[num]->stats->Char_func.Before_turn_func = Before_turn;
        Ally_unit[num]->stats->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->stats->Char_func.Before_attack_func = Before_attack;
        Ally_unit[num]->stats->Char_func.Start_game_func = Start_game;
        Ally_unit[num]->stats->Char_func.Buff_func = Buff_func;


    }
    void Turn_func_Fast_Sunday(Unit *ptr){
        if(Ally_unit[ptr->Atv_stats->Character_num]->stats->Buff_check["Basic_Attack_allowed"] ==0||Robin_temp(ptr)){
            Turn_func_Slow_Sunday(ptr);
            
        }else{
            Combat_data temp;
            Skill_point(1);
            temp.num = ptr->Atv_stats->Character_num;
            temp.Turn_reset = 1;

            temp.Action_type.first = "Attack";
            temp.Action_type.second = "Basic_Attack";

            temp.Damage_element = "Imaginary";
            temp.Damage_type.push_back("Basic_Attack");

            temp.Target_type = "Single_target";
            temp.Damage_spilt.Main.push_back({100,0,0,10});
            Action_bar.push(temp);
            Increase_energy(Ally_unit[ptr->Atv_stats->Character_num]->stats.get(),20);
            Ally_unit[ptr->Atv_stats->Character_num]->stats->Buff_check["Basic_Attack_allowed"] = 0;
        }
    }
    void Turn_func_Slow_Sunday(Unit *ptr){
        Skill_point(-1);
        Increase_energy(Ally_unit[ptr->Atv_stats->Character_num]->stats.get(),30);
        Combat_data temp;
        temp.num = ptr->Atv_stats->Character_num;
        temp.Buff_type.push_back("Buff");
        temp.Target_type = "Single_target";
        temp.Action_type.first = "Buff";
        temp.Action_type.second = "Skill";
        temp.Turn_reset=true;
        if(Ally_unit[Main_dps_num]->stats->Buff_countdown["The_Sorrowing_Body"]<=Ally_unit[Main_dps_num]->Atv_stats->turn_cnt){
            Ally_unit[Main_dps_num]->Crit_rate["None"]+=20;
        }
        if(Ally_unit[Main_dps_num]->stats->Buff_countdown["Benison_of_Paper_and_Rites"]<=Ally_unit[Main_dps_num]->Atv_stats->turn_cnt){
            if(Ally_unit[Main_dps_num]->stats->Summon_ptr==nullptr){
                Ally_unit[Main_dps_num]->Dmg_bonus["None"]+=30;
            }else{
                Ally_unit[Main_dps_num]->Dmg_bonus["None"]+=50;
                
            }
            if(Ally_unit[Main_dps_num]->stats->Eidolon>=1){
                Ally_unit[Main_dps_num]->Def_shred["None"]+=16;
                Ally_unit[Main_dps_num]->Def_shred["Summon"]+=24;
            }
        }
        auto ally_ptr = dynamic_cast<Ally*>(ptr);
        
        if(ally_ptr->stats->Buff_check["Technique_use"]==0&&ally_ptr->stats->Technique==1){
            ally_ptr->stats->Buff_check["Technique_use"]= 1;
            Ally_unit[Main_dps_num]->Dmg_bonus["None"]+=50;
            Ally_unit[Main_dps_num]->stats->Buff_countdown["The_Glorious_Mysteries"] = Ally_unit[Main_dps_num]->Atv_stats->turn_cnt + 2;
        }
        Ally_unit[Main_dps_num]->stats->Buff_countdown["The_Sorrowing_Body"] = Ally_unit[Main_dps_num]->Atv_stats->turn_cnt + 3;
        Ally_unit[Main_dps_num]->stats->Buff_countdown["Benison_of_Paper_and_Rites"] = Ally_unit[Main_dps_num]->Atv_stats->turn_cnt + 2;
        
        Action_bar.push(temp);
        if(Ally_unit[Main_dps_num]->stats->Summon_ptr!=nullptr){
            Action_forward(Ally_unit[Main_dps_num]->stats->Summon_ptr->Atv_stats.get(),100);
        }
        Action_forward(Ally_unit[Main_dps_num]->Atv_stats.get(),100);
    }

    void Ult_func(Ally *ptr){
        //if(turn->Name!=Ally_unit[Main_dps_num]->Atv_stats->Name&&Driver_Type=="Swap_pull")return ;
        if(Ally_unit[Main_dps_num]->stats->Max_energy - Ally_unit[Main_dps_num]->stats->Current_energy<30&&ptr->stats->Buff_countdown["Ode_to_Caress_and_Cicatrix"] > ptr->Atv_stats->turn_cnt)return ;

        if(!Ult_use_check(ptr))return;
        Combat_data temp;
        ptr->stats->Buff_check["Basic_Attack_allowed"] = 1;
        temp.Action_type.first = "Buff";
        temp.Action_type.second = "Ultimate";
        temp.num = ptr->Atv_stats->Character_num;
        temp.Buff_type.push_back("Buff");
        temp.Target_type = "Single_target";
        Action_bar.push(temp);
        if(ptr->stats->Eidolon>=2){
            if(ptr->stats->Buff_check["Ult_first_time"]==0){
                ptr->stats->Buff_check["Ult_first_time"]=1;
                Skill_point(2);
            }
            
        }
        if(Ally_unit[Main_dps_num]->stats->Max_energy>200){
            Increase_energy(Ally_unit[Main_dps_num]->stats.get(),20,0);
        }else{
            Increase_energy(Ally_unit[Main_dps_num]->stats.get(),0,40);
        }
        if(ptr->stats->Buff_countdown["Ode_to_Caress_and_Cicatrix"] <= ptr->Atv_stats->turn_cnt ){
            if(ptr->stats->Eidolon>=2){
            Ally_unit[Main_dps_num]->Dmg_bonus["None"]+=30;
            }
            ptr->stats->Buff_note["Ode_to_Caress_and_Cicatrix"] = ptr->Crit_dam["None"]*0.3+12;
            Ally_unit[Main_dps_num]->Crit_dam["None"] += ptr->stats->Buff_note["Ode_to_Caress_and_Cicatrix"];
        }
        ptr->stats->Buff_countdown["Ode_to_Caress_and_Cicatrix"] = ptr->Atv_stats->turn_cnt + 3;
        Deal_damage();
    }
    void Before_turn(Ally *ptr){
        if(ptr->stats->Buff_countdown["Ode_to_Caress_and_Cicatrix"] > ptr->Atv_stats->turn_cnt){
            Ally_unit[Main_dps_num]->Crit_dam["None"] -= ptr->stats->Buff_note["Ode_to_Caress_and_Cicatrix"];
            ptr->stats->Buff_note["Ode_to_Caress_and_Cicatrix"] = ptr->Crit_dam["None"]*0.3+12;
            Ally_unit[Main_dps_num]->Crit_dam["None"] += ptr->stats->Buff_note["Ode_to_Caress_and_Cicatrix"];
        }
        
        if(!(ptr->Atv_stats->Character_num == turn->Character_num && turn->Side=="Ally"))return;
        if(ptr->stats->Buff_countdown["Ode_to_Caress_and_Cicatrix"] == ptr->Atv_stats->turn_cnt&&ptr->Atv_stats->turn_cnt!=0){
            Ally_unit[Main_dps_num]->Crit_dam["None"] -= ptr->stats->Buff_note["Ode_to_Caress_and_Cicatrix"];
            if(ptr->stats->Eidolon>=2){
            Ally_unit[Main_dps_num]->Dmg_bonus["None"]-=30;
            }
        }
    }
    void After_turn(Ally *ptr){
        if(!(Ally_unit[Main_dps_num]->Atv_stats->Character_num == turn->Character_num && turn->Side=="Ally"))return;
        if(Ally_unit[Main_dps_num]->stats->Buff_countdown["Benison_of_Paper_and_Rites"]==Ally_unit[Main_dps_num]->Atv_stats->turn_cnt){
            if(Ally_unit[Main_dps_num]->stats->Summon_ptr==nullptr){
                Ally_unit[Main_dps_num]->Dmg_bonus["None"]-=30;
            }else{
                Ally_unit[Main_dps_num]->Dmg_bonus["None"]-=50;
            }
            if(Ally_unit[Main_dps_num]->stats->Eidolon>=1){
                Ally_unit[Main_dps_num]->Def_shred["None"]-=16;
                Ally_unit[Main_dps_num]->Def_shred["Summon"]-=24;
            }
        }
        if(Ally_unit[Main_dps_num]->stats->Buff_countdown["The_Sorrowing_Body"]==Ally_unit[Main_dps_num]->Atv_stats->turn_cnt){
            Ally_unit[Main_dps_num]->Crit_rate["None"]-=20;
        }
        if(Ally_unit[Main_dps_num]->stats->Buff_countdown["The_Glorious_Mysteries"]==Ally_unit[Main_dps_num]->Atv_stats->turn_cnt){
            Ally_unit[Main_dps_num]->Dmg_bonus["None"]-=50;
        }
    }
    void Start_game(Ally *ptr){
        Increase_energy(ptr->stats.get(),25);
    }
    void Before_attack(Ally *ptr, Combat_data &data_){
        
        if(ptr->stats->Buff_countdown["Ode_to_Caress_and_Cicatrix"] > ptr->Atv_stats->turn_cnt){
            Ally_unit[Main_dps_num]->Crit_dam["None"] -= ptr->stats->Buff_note["Ode_to_Caress_and_Cicatrix"];
            ptr->stats->Buff_note["Ode_to_Caress_and_Cicatrix"] = ptr->Crit_dam["None"]*0.3+12;
            Ally_unit[Main_dps_num]->Crit_dam["None"] += ptr->stats->Buff_note["Ode_to_Caress_and_Cicatrix"];
        }
    }
    void Buff_func(Ally *ptr, Combat_data &data_){
        if(ptr->stats->Buff_countdown["Ode_to_Caress_and_Cicatrix"] > ptr->Atv_stats->turn_cnt&&data_.Action_type.second=="Skill"&&turn->Name=="Sunday"){
            Skill_point(1);
        }
    }
    bool Robin_temp(Unit *ptr){
        if(Robin_num!=0&&Ally_unit[Robin_num]->Atv_stats->Base_speed==-1){
            return true;
        }
        return false;
    }

}
#endif