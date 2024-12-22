
#ifndef For_Tomorrow_Journey_H
#define For_Tomorrow_Journey_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Harmony_Lightcone{
    void For_Tomorrow_Journey(Ally *ptr);
    void For_Tomorrow_Journey(Ally *ptr){
        ptr->stats->Base_hp += 953;
        ptr->stats->Base_hp += 476;
        ptr->stats->Base_hp += 331;
        ptr->stats->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Atk_percent["None"]+=32;
        };
        ptr->stats->Light_cone.After_attack_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.num == ptr->Atv_stats->Character_num && data_.Action_type.second=="Ultimate"){
                
                if(ptr->stats->Buff_check["For_Tomorrow_Journey_Buff"] ==0){
                    ptr->stats->Buff_check["For_Tomorrow_Journey_Buff"] = 1;
                    ptr->Dmg_bonus["None"]+=30;
                }
                ptr->stats->Buff_countdown["For_Tomorrow_Journey_Buff"] = ptr->Atv_stats->turn_cnt+1;
            }
            
        };
        ptr->stats->Light_cone.Buff_func = [](Ally *ptr, Combat_data &data_){
            
            
            if(data_.num == ptr->Atv_stats->Character_num && data_.Action_type.second=="Ultimate"){
                if(ptr->stats->Buff_check["For_Tomorrow_Journey_Buff"] ==0){
                    ptr->stats->Buff_check["For_Tomorrow_Journey_Buff"] = 1;
                    ptr->Dmg_bonus["None"]+=30;
                }
                ptr->stats->Buff_countdown["For_Tomorrow_Journey_Buff"] = ptr->Atv_stats->turn_cnt+1;
            }
        };
        ptr->stats->Light_cone.After_turn_func = [](Ally *ptr){
            
            if(ptr->stats->Buff_countdown["For_Tomorrow_Journey_Buff"] <= ptr->Atv_stats->turn_cnt&&ptr->stats->Buff_check["For_Tomorrow_Journey_Buff"] == 1){
                ptr->Dmg_bonus["None"]-=30;
                ptr->stats->Buff_check["For_Tomorrow_Journey_Buff"] = 0;
            }
        };
    }
}
#endif