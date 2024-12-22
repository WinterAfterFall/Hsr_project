
#ifndef DDD_H
#define DDD_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Harmony_Lightcone{
    void DDD(Ally *ptr);
    void DDD(Ally *ptr){
        ptr->stats->Base_hp += 953;
        ptr->stats->Base_hp += 423;
        ptr->stats->Base_hp += 397;

        ptr->stats->Light_cone.After_attack_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.num == ptr->Atv_stats->Character_num && data_.Action_type.second=="Ultimate"){
                All_Action_forward(24,1,Total_ally);
            }
            
        };
        ptr->stats->Light_cone.Buff_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.num == ptr->Atv_stats->Character_num && data_.Action_type.second=="Ultimate"){
                All_Action_forward(24,1,Total_ally);
            }
        };
    }
}
#endif