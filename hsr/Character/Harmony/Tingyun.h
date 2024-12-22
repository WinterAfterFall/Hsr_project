
#ifndef Tingyun_H
#define Tingyun_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Tingyun{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Ult_func(Ally *ptr);//*
    void Before_turn(Ally *ptr);
    void After_turn(Ally *ptr);
    void After_attack(Ally *ptr, Combat_data &data_);
    void Start_game(Ally *ptr);
    
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->stats->Base_hp = 847;
        Ally_unit[num]->stats->Base_atk = 529;
        Ally_unit[num]->stats->Base_def = 397;
        Ally_unit[num]->Atv_stats->Base_speed = 112;
        Ally_unit[num]->stats->Max_energy = 130;
        Ally_unit[num]->stats->Ult_cost = 130;
        Ally_unit[num]->stats->Eidolon = E;
        Ally_unit[num]->stats->Element_type = "Lightning";
        Ally_unit[num]->stats->Path = "Harmony";
        Ally_unit[num]->Atv_stats->Character_num = num;
        Ally_unit[num]->Atv_stats->Name = "Tingyun";
        Ally_unit[num]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Atv_stats->ptr_to_unit = Ally_unit[num].get();
        unit[num] = Ally_unit[num]->Atv_stats->ptr_to_unit;
        Ally_unit[num]->stats->Technique = 2;

        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        
        Ally_unit[num]->Turn_func = Turn_func;
        Ally_unit[num]->stats->Ult_func = Ult_func;
        Ally_unit[num]->stats->Char_func.Reset_func = Reset;
        Ally_unit[num]->stats->Char_func.Before_turn_func = Before_turn;
        Ally_unit[num]->stats->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->stats->Char_func.After_attack_func = After_attack;
        Ally_unit[num]->stats->Char_func.Start_game_func = Start_game;


    }
    void Reset(Ally *ptr){
        ptr->Dmg_bonus_each_element["Lightning"]["None"]+=8;
        ptr->Atk_percent["None"]+=28;
        ptr->Def_percent["None"]+=22.5;


        //relic
        ptr->Atk_percent["None"]+=43.2;
        ptr->Atv_stats->Flat_speed+=25;
        ptr->Atk_percent["None"]+=43.2;
        ptr->stats->Energy_recharge+=19.4;

        //substats
        ptr->Atk_percent["None"]+=77.76;
        ptr->Dmg_bonus["Basic_Attack"]+=40;
    }
    void Turn_func(Unit *ptr){
        Combat_data data_;
        if(Ally_unit[Main_dps_num]->stats->Buff_countdown["Benediction"]<=Ally_unit[Main_dps_num]->Atv_stats->turn_cnt){
            Skill_point(-1);
            if(ptr->Print){
            cout<<"-----------------------tingyun skill at "<<Current_atv<<endl;
            
        }
            data_.num = ptr->Atv_stats->Character_num;
            data_.Turn_reset = 1;

            data_.Action_type.first="Buff";
            data_.Action_type.second = "Skill";

            data_.Buff_type.push_back("Buff");

            data_.Target_type="Single_target";
            Action_bar.push(data_);
            auto ally_ptr = dynamic_cast<Ally*>(ptr);
            Increase_energy(ally_ptr->stats.get(),30);
            Ally_unit[Main_dps_num]->stats->Buff_countdown["Benediction"]= 3 + Ally_unit[Main_dps_num]->Atv_stats->turn_cnt;
            Ally_unit[Main_dps_num]->Atk_percent["None"]+=55;
            return;
        }
        Skill_point(1);
        
        data_.num = ptr->Atv_stats->Character_num;
        data_.Turn_reset = 1;

        data_.Action_type.first="Attack";
        data_.Action_type.second = "Basic_Attack";

        data_.Damage_element="Lightning";
        data_.Damage_type.push_back("Basic_Attack");

        data_.Target_type="Single_target";
        data_.Damage_spilt.Main.push_back({33,0,0,3});
        data_.Damage_spilt.Main.push_back({77,0,0,7});
        Action_bar.push(data_);
        auto ally_ptr = dynamic_cast<Ally*>(ptr);
        Increase_energy(ally_ptr->stats.get(),20);
        return;
    }
    void Ult_func(Ally *ptr){
        if(Ally_unit[Main_dps_num]->stats->Max_energy - Ally_unit[Main_dps_num]->stats->Current_energy<=30)return ;

        if(!Ult_use_check(ptr))return;
        Combat_data data_;
        data_.num = ptr->Atv_stats->Character_num;

        data_.Action_type.first="Buff";
        data_.Action_type.second = "Ultimate";

        data_.Buff_type.push_back("Buff");

        data_.Target_type="Single_target";
        Action_bar.push(data_);
        Increase_energy(Ally_unit[Main_dps_num]->stats.get(),0,50);
        if(ptr->stats->Eidolon>=6){
            Increase_energy(Ally_unit[Main_dps_num]->stats.get(),0,10);
        }
        if(ptr->stats->Eidolon>=1){
            Speed_Buff(Ally_unit[Main_dps_num]->Atv_stats.get(),20,0);
            Ally_unit[Main_dps_num]->stats->Buff_countdown["Windfall_of_Lucky_Springs"]=1;
        }
        if(Ally_unit[Main_dps_num]->stats->Buff_countdown["Rejoicing_Clouds"]<=0){
             Ally_unit[Main_dps_num]->Dmg_bonus["None"]+=56;
        }
        Ally_unit[Main_dps_num]->stats->Buff_countdown["Rejoicing_Clouds"] = 2;
        Deal_damage();
    }
    void Before_turn(Ally *ptr){
        if(turn->Name!="Tingyun")return;
        Increase_energy(ptr->stats.get(),5);
    }
    void After_turn(Ally *ptr){
        if(turn->Name=="Tingyun"){
            if(ptr->stats->Buff_countdown["Nourished_Joviality"]==1){
            Speed_Buff(ptr->Atv_stats.get(),-20,0);
            ptr->stats->Buff_countdown["Nourished_Joviality"]=0;
            return;
        }
        }
        if(turn->Character_num!=Main_dps_num||turn->Side!="Ally")return;
        --Ally_unit[Main_dps_num]->stats->Buff_countdown["Rejoicing_Clouds"];
        --Ally_unit[Main_dps_num]->stats->Buff_countdown["Windfall_of_Lucky_Springs"];
        if(Ally_unit[Main_dps_num]->stats->Buff_countdown["Benediction"]==Ally_unit[Main_dps_num]->Atv_stats->turn_cnt){
            Ally_unit[Main_dps_num]->Atk_percent["None"]-=55;
        }
        if(Ally_unit[Main_dps_num]->stats->Buff_countdown["Windfall_of_Lucky_Springs"]==0){
             Speed_Buff(Ally_unit[Main_dps_num]->Atv_stats.get(),-20,0);
        }
        if(Ally_unit[Main_dps_num]->stats->Buff_countdown["Rejoicing_Clouds"]==0){
             Ally_unit[Main_dps_num]->Dmg_bonus["None"]-=56;
        }
    }
    void After_attack(Ally *ptr, Combat_data &data_){
        if(Ally_unit[Main_dps_num]->stats->Buff_countdown["Benediction"]>Ally_unit[Main_dps_num]->Atv_stats->turn_cnt||(Ally_unit[Main_dps_num]->stats->Buff_countdown["Benediction"]==Ally_unit[Main_dps_num]->Atv_stats->turn_cnt&&After_Turn_Check==0)){
        if(data_.num==ptr->Atv_stats->Character_num){
                Combat_data temp = Combat_data();
                temp.num = Main_dps_num;

                temp.Action_type.first = "Attack";
                temp.Action_type.second = "Additional";

                temp.Damage_element = "Lightning";
                temp.Damage_type.push_back("Additional");

                temp.Target_type = "Single_target";
                    Cal_Additional_damage(temp,Enemy_unit[Main_Enemy_num].get(),{66,0,0,0});
                
        }else if(data_.num==Main_dps_num){
                Combat_data temp = Combat_data();
                temp.num = Main_dps_num;

                temp.Action_type.first = "Attack";
                temp.Action_type.second = "Additional";

                temp.Damage_element = "Lightning";
                temp.Damage_type.push_back("Additional");

                temp.Target_type = "Single_target";
        
                if(ptr->stats->Eidolon>=4){
                    Cal_Additional_damage(temp,Enemy_unit[Main_Enemy_num].get(),{64,0,0,0});
                }else{
                    Cal_Additional_damage(temp,Enemy_unit[Main_Enemy_num].get(),{44,0,0,0});
                }
        }
        }
        if(data_.Action_type.second=="Skill"&&data_.num==ptr->Atv_stats->Character_num){
            Speed_Buff(ptr->Atv_stats.get(),20,0);
            ptr->stats->Buff_countdown["Nourished_Joviality"]==1;
        }
    }
    void Start_game(Ally *ptr){
        Increase_energy(ptr->stats.get(),0,50*ptr->stats->Technique);
    }
    

    

    
}
#endif
