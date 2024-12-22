
#ifndef Knight_H
#define Knight_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Relic{
    void Knight(Ally *ptr);
    void Knight(Ally *ptr){
        ptr->stats->Relic.Reset_func = [](Ally *ptr){
            ptr->Def_percent["None"]+=15;

        };
        
    }
}
#endif