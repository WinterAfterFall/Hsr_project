
#ifndef Multiplication_H
#define Multiplication_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Abundance_Lightcone{
    void Multiplication(Ally *ptr);
    void Multiplication(Ally *ptr){
        ptr->stats->Base_hp += 953;
        ptr->stats->Base_hp += 318;
        ptr->stats->Base_hp += 198;

        ptr->stats->Light_cone.After_attack_func = [](Ally *ptr, Combat_data &data_){
            
            if(turn->Name == ptr->Atv_stats->Name && data_.Action_type.second=="Basic_Attack"){
                Action_forward(turn,20);
            }
            
        };
        ptr->stats->Light_cone.Buff_func = [](Ally *ptr, Combat_data &data_){
            
            if(turn->Name == ptr->Atv_stats->Name && data_.Action_type.second=="Basic_Attack"){
                Action_forward(turn,20);
            }
        };
    }
}
#endif