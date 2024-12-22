
#ifndef Lushaka_H
#define Lushaka_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Planar{
    void Lushaka(Ally *ptr);
    void Lushaka(Ally *ptr){
        
        
        ptr->stats->Planar.Reset_func = [](Ally *ptr){
            ptr->stats->Energy_recharge += 5;
            if(ptr->Atv_stats->Character_num!=Main_dps_num){
            Ally_unit[Main_dps_num]->Atk_percent["None"]+=12;
            }
        };
       
    }
}
#endif