
#ifndef Battle_Isnt_Over_H
#define Battle_Isnt_Over_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Harmony_Lightcone{
    void But_the_Battle_Isnt_Over(Ally *ptr);
    void But_the_Battle_Isnt_Over(Ally *ptr){
        ptr->stats->Base_hp += 1164;
        ptr->stats->Base_hp += 529;
        ptr->stats->Base_hp += 463;

        ptr->stats->Light_cone.Reset_func = [](Ally *ptr){
            ptr->stats->Energy_recharge+=10;
                
        };
        ptr->stats->Light_cone.After_attack_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.num == ptr->Atv_stats->Character_num && data_.Action_type.second=="Skill"){
                ptr->stats->Buff_check["Battle_Isnt_Over_buff"] =1;
            }
            if(data_.num == ptr->Atv_stats->Character_num && data_.Action_type.second=="Ultimate"){
                if(ptr->stats->Buff_check["Battle_Isnt_Over_cnt"]==0){
                ptr->stats->Buff_check["Battle_Isnt_Over_cnt"] = true;
                Skill_point(1);
                }else{
                    ptr->stats->Buff_check["Battle_Isnt_Over_cnt"] = false;
                }
            }
        };
        ptr->stats->Light_cone.Buff_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.num == ptr->Atv_stats->Character_num && data_.Action_type.second=="Skill"){
                ptr->stats->Buff_check["Battle_Isnt_Over_buff"] =1;
            }
            if(data_.num == ptr->Atv_stats->Character_num && data_.Action_type.second=="Ultimate"){
                if(ptr->stats->Buff_check["Battle_Isnt_Over_cnt"]==0){
                ptr->stats->Buff_check["Battle_Isnt_Over_cnt"] = true;
                Skill_point(1);
                }else{
                    ptr->stats->Buff_check["Battle_Isnt_Over_cnt"] = false;
                }
            }
        };
        ptr->stats->Light_cone.Before_turn_func = [](Ally *ptr){
            
            if(turn->Side=="Ally" && ptr->stats->Buff_check["Battle_Isnt_Over_buff"] ==1){
                
                auto ally_ptr = dynamic_cast<Ally*>(turn->ptr_to_unit);
                ally_ptr->Dmg_bonus["None"]+=30;
            }
        };
        ptr->stats->Light_cone.After_turn_func = [](Ally *ptr){
            
            if(turn->Side=="Ally" && ptr->stats->Buff_check["Battle_Isnt_Over_buff"] ==1&&turn->Name!=ptr->Atv_stats->Name){
                auto ally_ptr = dynamic_cast<Ally*>(turn->ptr_to_unit);
                ally_ptr->Dmg_bonus["None"]-=30;
                ptr->stats->Buff_check["Battle_Isnt_Over_buff"] = 0;
            }
        };
    }
    
}
#endif