
#ifndef Before_the_Tutorial_Mission_Starts_H
#define Before_the_Tutorial_Mission_Starts_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Nihility_Lightcone{
    void Before_the_Tutorial(Ally *ptr);
    void Before_the_Tutorial(Ally *ptr){
        ptr->stats->Base_hp += 953;
        ptr->stats->Base_hp += 476;
        ptr->stats->Base_hp += 331;
        
        ptr->stats->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Effect_hit_rate+=40;
        };

        ptr->stats->Light_cone.After_attack_func = [](Ally *ptr, Combat_data &data_){
            if(data_.num!=ptr->Atv_stats->Character_num)return;
            int sz2 = data_.Damage_spilt.Adjacent.size();
            int sz3 = data_.Damage_spilt.Other.size();
            for(int i=1;i<=Total_enemy;i++){

            if(Enemy_unit[i]->stats->Target_type=="Main"){
                if(Enemy_unit[i]->Def_shred["None"]>0){
                    Increase_energy(ptr->stats.get(),8);
                    return;
                }
            }
            
            if(0<sz2 && Enemy_unit[i]->stats->Target_type=="Adjacent"){
                if(Enemy_unit[i]->Def_shred["None"]>0){
                    Increase_energy(ptr->stats.get(),8);
                    return;
                }
            }
            
            if(0<sz3 && Enemy_unit[i]->stats->Target_type=="Other"){
                if(Enemy_unit[i]->Def_shred["None"]>0){
                    Increase_energy(ptr->stats.get(),8);
                    return;
                }
            }
            
            
        }
            
        };


    }
}
#endif