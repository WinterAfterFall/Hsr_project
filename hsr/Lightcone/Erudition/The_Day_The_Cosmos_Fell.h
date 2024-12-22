
#ifndef The_Day_The_Cosmos_Fell_H
#define The_Day_The_Cosmos_Fell_H

#include"..\..\Setup.cpp"
namespace Erudition_Lightcone{
    void Cosmos_Fell(Ally *ptr);
    void Cosmos_Fell(Ally *ptr){
        ptr->stats->Base_hp += 953  ;
        ptr->stats->Base_atk += 476;
        ptr->stats->Base_def += 331;
        ptr->stats->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Crit_dam["None"]+=40;
            ptr->Atk_percent["None"]+=24;

        };
        
        
    }
}
#endif