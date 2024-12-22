
#ifndef Double_Atk_H
#define Double_Atk_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Relic{
    void Double_Atk(Ally *ptr);
    void Double_Atk(Ally *ptr){
        ptr->stats->Relic.Reset_func = [](Ally *ptr){
            ptr->Atk_percent["None"]+=24;

        };
        
    }
}
#endif