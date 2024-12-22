
#ifndef Robin_H
#define Robin_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Robin{
    void Setup_Fast_Robin(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset_Fast_Robin(Ally *ptr);
    void Turn_func_Fast_Robin(Unit *ptr);
    void Ult_func(Ally *ptr);//*
    void Before_turn(Ally *ptr);
    void After_turn(Ally *ptr);
    void Before_attack(Ally *ptr, Combat_data &data_);
    void After_attack(Ally *ptr, Combat_data &data_);
    void Start_game(Ally *ptr);
    void Start_wave(Ally *ptr);
    void Buff_func(Ally *ptr, Combat_data &data_);
    void Dot_func(Enemy *target, Ally *ptr, double Dot_ratio);
    void Toughness_break_func(Ally *ptr, Enemy *target, int num);
    void Enemy_hit_func(Ally *ptr, Enemy *target);    
    void Apply_debuff_func(Ally *ptr, Enemy *target, int total_debuff);
    void Hit_func(Ally *ptr, int Hit_cnt);
    bool Temp_Turn_Condition(Unit *ptr);

    void Setup_Fast_Robin(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->stats->Base_hp = 1280;
        Ally_unit[num]->stats->Base_atk = 640;
        Ally_unit[num]->stats->Base_def = 485;
        Ally_unit[num]->Atv_stats->Base_speed = 102;
        Ally_unit[num]->stats->Max_energy = 160;
        Ally_unit[num]->stats->Ult_cost = 160;
        Ally_unit[num]->stats->Eidolon = E;
        Ally_unit[num]->stats->Element_type = "Physical";
        Ally_unit[num]->stats->Path = "Harmony";
        Ally_unit[num]->Atv_stats->Character_num = num;
        Ally_unit[num]->Atv_stats->Name = "Robin";
        Ally_unit[num]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Atv_stats->ptr_to_unit = Ally_unit[num].get();
        unit[num] = Ally_unit[num]->Atv_stats->ptr_to_unit;
        Robin_num = num;
        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());

        Ally_unit[num]->Turn_func = Turn_func_Fast_Robin;
        Ally_unit[num]->stats->Ult_func = Ult_func;
        Ally_unit[num]->stats->Char_func.Reset_func = Reset_Fast_Robin;
        Ally_unit[num]->stats->Char_func.Before_turn_func = Before_turn;
        Ally_unit[num]->stats->Char_func.After_attack_func = After_attack;
        Ally_unit[num]->stats->Char_func.Before_attack_func = Before_attack;
        Ally_unit[num]->stats->Char_func.Start_wave_func = Start_wave;
        Ally_unit[num]->stats->Char_func.Start_game_func = Start_game;

        //countdown
        Ally_unit[num]->stats->Countdown =  make_unique<Unit>();
        Ally_unit[num]->stats->Countdown->Atv_stats->Base_speed = -1;
        Ally_unit[num]->stats->Countdown->Atv_stats->Character_num = num;
        Ally_unit[num]->stats->Countdown->Atv_stats->Name = "Concerto_state";
        Ally_unit[num]->stats->Countdown->Atv_stats->Side = "Countdown";
        Ally_unit[num]->stats->Countdown->Atv_stats->ptr_to_unit = Ally_unit[num]->stats->Countdown.get();
        Ally_unit[num]->stats->Countdown->Turn_func = [](Unit *x){

            auto ptr = Ally_unit[x->Atv_stats->Character_num].get();

            if( ptr->stats->Countdown->Atv_stats->Base_speed == 90){
                ptr->stats->Countdown->Atv_stats->Base_speed = -1;
                ptr->Atv_stats->Base_speed = 102;
                Update_Max_atv(ptr->Atv_stats.get());
                Update_Max_atv(ptr->stats->Countdown->Atv_stats.get());
                atv_reset(ptr->Atv_stats.get());
                atv_reset(ptr->stats->Countdown->Atv_stats.get());

                for(int i=1;i<=Total_ally;i++){
                    Ally_unit[i]->Atk_flat["None"]-=ptr->stats->Buff_note["Concerto_state"];
                    Ally_unit[i]->Crit_dam["Fua"]-=25;
                    if(ptr->stats->Eidolon>=1){
                        Ally_unit[i]->Respen["None"]-=24;
                    }
                    if(ptr->stats->Eidolon>=2){
                        Speed_Buff(Ally_unit[i]->Atv_stats.get(),-16,0);
                    }
                }
                Action_forward(ptr->Atv_stats.get(),100);
                if(ptr->Print){
                    cout<<"-----------------------Robin Ult End at "<<Current_atv<<endl;
                }
            }
        };
        
    }
    void Reset_Fast_Robin(Ally *ptr){
        ptr->Atk_percent["None"]+=28;
        ptr->Hp_percent["None"]+=18;
        ptr->Atv_stats->Flat_speed+=5;
        

        //relic
        ptr->Atk_percent["None"]+=43.2;
        ptr->Atv_stats->Flat_speed+=25;
        ptr->Atk_percent["None"]+=43.2;
        ptr->stats->Energy_recharge+=19.4;

        //substats
        ptr->Atk_percent["None"]+=54.432; //14
        ptr->Atv_stats->Flat_speed+=13.8; //5
        for(int i=1;i<=Total_ally;i++){
            Ally_unit[i]->Crit_dam["None"]+=20;
        }
        ptr->stats->Countdown->Atv_stats->Base_speed = -1;
        ptr->Atv_stats->Base_speed = 102;
        return;
    }
    void Turn_func_Fast_Robin(Unit *ptr){
        Combat_data temp;
        auto ally_ptr = dynamic_cast<Ally*>(ptr);
        
        Skill_point(-1);
        
        temp.num = ptr->Atv_stats->Character_num;
        temp.Turn_reset = 1;

        temp.Action_type.first = "Buff";
        temp.Action_type.second = "Skill";

        temp.Buff_type.push_back("Buff");

        temp.Target_type = "Aoe";
        Increase_energy(Ally_unit[ptr->Atv_stats->Character_num]->stats.get(),35);

        if(ally_ptr->stats->Buff_countdown["Pinion'sAria"]<=ptr->Atv_stats->turn_cnt){
            for(int i=1;i<=Total_ally;i++){
            Ally_unit[i]->Dmg_bonus["None"]+=50;
        }
        ally_ptr->stats->Buff_countdown["Pinion'sAria"]=ptr->Atv_stats->turn_cnt + 3;
        }else{
            
            Skill_point(1);
            temp.num = ptr->Atv_stats->Character_num;
            temp.Turn_reset = 1;

            temp.Action_type.first = "Attack";
            temp.Action_type.second = "Basic_Attack";

            temp.Damage_element = "Physical";
            temp.Damage_type.push_back("Basic_Attack");

            temp.Target_type = "Single_target";
            temp.Damage_spilt.Main.push_back({100,0,0,10});
            
            Increase_energy(Ally_unit[ptr->Atv_stats->Character_num]->stats.get(),20);
        }
        Action_bar.push(temp);
        return;
    }
    void Ult_func(Ally *ptr){
        if(Driver_Type=="Double_turn"){
            if((Ally_unit[Driver_num]->Atv_stats->atv<30||Ally_unit[Main_dps_num]->Atv_stats->atv<30))return;
            if((Ally_unit[Main_dps_num]->Atv_stats->turn_cnt <4||(Ally_unit[Main_dps_num]->Atv_stats->turn_cnt==4&&Ult_After_Turn==0)))return;

        }else if(Driver_Type=="Swap_pull"){
            if(Ally_unit[Driver_num]->Atv_stats->atv <= Ally_unit[Main_dps_num]->Atv_stats->atv &&Ally_unit[Main_dps_num]->stats->Summon_ptr==nullptr)return;
            
        }else if(Driver_Type=="Always_pull"){
            if(Ally_unit[Driver_num]->Atv_stats->atv <= Ally_unit[Main_dps_num]->Atv_stats->atv &&(Ally_unit[Main_dps_num]->stats->Summon_ptr==nullptr||Ally_unit[Driver_num]->Atv_stats->Name=="Hanabi"))return;
            if(Ally_unit[Main_dps_num]->stats->Summon_ptr!=nullptr&&(Ally_unit[Main_dps_num]->Atv_stats->turn_cnt <2||(Ally_unit[Main_dps_num]->Atv_stats->turn_cnt==2&&Ult_After_Turn==0)))return;
            if(Ally_unit[Main_dps_num]->stats->Summon_ptr!=nullptr&&(Ally_unit[Driver_num]->Atv_stats->atv <=Ally_unit[Driver_num]->Atv_stats->Max_atv*0.5 ))return;
        }
        if( (Ally_unit[Main_dps_num]->stats->Summon_ptr==nullptr||Ally_unit[Main_dps_num]->stats->Summon_ptr->Atv_stats->atv!=0)&&ptr->stats->Countdown->Atv_stats->Base_speed != 90&&ptr->stats->Buff_countdown["Pinion'sAria"]>ptr->Atv_stats->turn_cnt&&Ult_use_check(ptr)){
            ptr->stats->Countdown->Atv_stats->Base_speed = 90;
            
            ptr->Atv_stats->Base_speed = -1;
            Update_Max_atv(ptr->Atv_stats.get());
            Update_Max_atv(ptr->stats->Countdown->Atv_stats.get());
            atv_reset(ptr->Atv_stats.get());
            atv_reset(ptr->stats->Countdown->Atv_stats.get());
            ptr->stats->Buff_note["Concerto_state"] = ((ptr->Atk_percent["None"]/100*ptr->stats->Base_atk)+ptr->Atk_flat["None"])*0.228+200;
            for(int i=1;i<=Total_ally;i++){
            Ally_unit[i]->Atk_flat["None"]+=ptr->stats->Buff_note["Concerto_state"];
            Ally_unit[i]->Crit_dam["Fua"]+=25;
            if(ptr->stats->Eidolon>=1){
                Ally_unit[i]->Respen["None"]+=24;
            }
            if(ptr->stats->Eidolon>=2){
                Speed_Buff(Ally_unit[i]->Atv_stats.get(),16,0);
            }
        }
        All_Action_forward(100,1,Total_ally);
        Combat_data temp;
        temp.num = ptr->Atv_stats->Character_num;

        temp.Action_type.first = "Buff";
        temp.Action_type.second = "Ultimate";

        temp.Buff_type.push_back("Buff");

        temp.Target_type = "Aoe";
        Action_bar.push(temp);
        if(ptr->Print){
            cout<<Ally_unit[Main_dps_num]->stats->Summon_ptr->Atv_stats->atv<<" ";
            cout<<"-----------------------Robin Ult at "<<Current_atv<<endl;
            
        }
        }
        Deal_damage();
        return;
    }
    void Before_turn(Ally *ptr){
        if(turn->Character_num==ptr->Atv_stats->Character_num&&turn->Side=="Ally"){
            if(ptr->stats->Buff_countdown["Pinion'sAria"]==ptr->Atv_stats->turn_cnt){
                for(int i=1;i<=Total_ally;i++){
                Ally_unit[i]->Dmg_bonus["None"]-=50;
                }
            }
        }
        if( ptr->stats->Countdown->Atv_stats->Base_speed == 90){
            for(int i=1;i<=Total_ally;i++){
            Ally_unit[i]->Atk_flat["None"]-=ptr->stats->Buff_note["Concerto_state"];
            }
            ptr->stats->Buff_note["Concerto_state"] = ((ptr->Atk_percent["None"]/100*ptr->stats->Base_atk)+ptr->Atk_flat["None"])*0.228+200;
            for(int i=1;i<=Total_ally;i++){
            Ally_unit[i]->Atk_flat["None"]+=ptr->stats->Buff_note["Concerto_state"];
            }
        }
    }
    void After_turn(Ally *ptr){
        if( ptr->stats->Countdown->Atv_stats->Base_speed == 90){
            for(int i=1;i<=Total_ally;i++){
            Ally_unit[i]->Atk_flat["None"]-=ptr->stats->Buff_note["Concerto_state"];
            }
            ptr->stats->Buff_note["Concerto_state"] = ((ptr->Atk_percent["None"]/100*ptr->stats->Base_atk)+ptr->Atk_flat["None"])*0.228+200;
            for(int i=1;i<=Total_ally;i++){
            Ally_unit[i]->Atk_flat["None"]+=ptr->stats->Buff_note["Concerto_state"];
            }
        }
    }
    void Before_attack(Ally *ptr, Combat_data &data_){
        if( ptr->stats->Countdown->Atv_stats->Base_speed == 90){
            for(int i=1;i<=Total_ally;i++){
            Ally_unit[i]->Atk_flat["None"]-=ptr->stats->Buff_note["Concerto_state"];
            }
            ptr->stats->Buff_note["Concerto_state"] = ((ptr->Atk_percent["None"]/100*ptr->stats->Base_atk)+ptr->Atk_flat["None"])*0.228+200;
            for(int i=1;i<=Total_ally;i++){
            Ally_unit[i]->Atk_flat["None"]+=ptr->stats->Buff_note["Concerto_state"];
            }
        }
    }
    
    void After_attack(Ally *ptr, Combat_data &data_){
        if( ptr->stats->Countdown->Atv_stats->Base_speed == 90){

        Combat_data temp;
        double x1=0,x2=0;
        temp.num = ptr->Atv_stats->Character_num;

        temp.Action_type.first = "Attack";
        temp.Action_type.second = "Additional";

        temp.Damage_element = "Physical";
        temp.Damage_type.push_back("Additional");

        temp.Target_type = "Single_target";

        ptr->Crit_rate["None"]+=100;
        x1 = ptr->Crit_dam["None"];
        x2 = Enemy_unit[Main_Enemy_num]->Crit_dam["None"];
        ptr->Crit_dam["None"] = 150;
        Enemy_unit[Main_Enemy_num]->Crit_dam["None"]= 0;
        
        Cal_Additional_damage(temp,Enemy_unit[Main_Enemy_num].get(),{120,0,0,0});
        
        ptr->Crit_rate["None"]-=100;
        ptr->Crit_dam["None"] = x1;
        Enemy_unit[Main_Enemy_num]->Crit_dam["None"] = x2;


        }
        Increase_energy(ptr->stats.get(),2);
        if(ptr->stats->Eidolon>=2){
            Increase_energy(ptr->stats.get(),1);
        }
    }
    void Start_wave(Ally *ptr){
        if(ptr->stats->Technique==1){
            Increase_energy(ptr->stats.get(),5);
        }
    }
    void Start_game(Ally *ptr){
        Action_forward(ptr->Atv_stats.get(),25);
    }
    bool Temp_Turn_Condition(Unit *ptr){
        return true;
    }
}
    
#endif
