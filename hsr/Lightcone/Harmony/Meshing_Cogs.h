
#ifndef Meshing_Cogs_H
#define Meshing_Cogs_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Harmony_Lightcone{
    void Meshing_Cogs(Ally *ptr);
    void Meshing_Cogs(Ally *ptr){
        ptr->stats->Base_hp += 847;
        ptr->stats->Base_hp += 318;
        ptr->stats->Base_hp += 265;

        ptr->stats->Light_cone.After_attack_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.num == ptr->Atv_stats->Character_num){
                Increase_energy(ptr->stats.get(),8);
            }
            
        };
        ptr->stats->Light_cone.Enemy_hit_func = [](Ally *ptr,Enemy *target){
            
            
            Increase_energy(ptr->stats.get(),8);
            
            
        };
    }
}
#endif