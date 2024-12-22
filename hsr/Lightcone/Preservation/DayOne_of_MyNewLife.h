
#ifndef DayOne_of_MyNewLife_H
#define DayOne_of_MyNewLife_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Preservation_Lightcone{
    void DayOne_of_MyNewLife(Ally *ptr);
    void DayOne_of_MyNewLife(Ally *ptr){
        ptr->stats->Base_hp += 953;
        ptr->stats->Base_hp += 370;
        ptr->stats->Base_hp += 463;
        ptr->stats->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Def_percent["None"]+=24;
        };
       
    }
}
#endif