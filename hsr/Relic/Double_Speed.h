
#ifndef Double_Speed_H
#define Double_Speed_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Relic{
    void Double_Speed(Ally *ptr);
    void Double_Speed(Ally *ptr){
        ptr->stats->Relic.Reset_func = [](Ally *ptr){
            ptr->Atv_stats->Speed_percent+=12;

        };
        
    }
}
#endif