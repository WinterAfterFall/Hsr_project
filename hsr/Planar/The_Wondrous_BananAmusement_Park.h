
#ifndef The_Wondrous_H
#define The_Wondrous_H


#include"..\Setup.cpp"
namespace Planar{
    void The_Wondrous_BananAmusement_Park(Ally *ptr);
    void The_Wondrous_BananAmusement_Park(Ally *ptr){
        
        
        ptr->stats->Planar.Reset_func = [](Ally *ptr){
            ptr->Crit_dam["None"]+=16;
            if(ptr->stats->Summon_ptr!=nullptr){
                ptr->Crit_dam["None"]+=32;
            }
        };
       
    }
}
#endif