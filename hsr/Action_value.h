#ifndef ATV_H
#define ATV_H
#include<bits/stdc++.h>
#include"Control_panel.h"
#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
#define K_const 10000



void Update_Max_atv(Action_value_stats *ptr) {
    if(ptr->Base_speed<=0){
        ptr->Max_atv = 1e6;
        return;
    }
    ptr->Max_atv = K_const / (ptr->Base_speed + ptr->Base_speed * ptr->Speed_percent/100 + ptr->Flat_speed);
    
}
void atv_reset(Action_value_stats *ptr) {

    ptr->atv = ptr->Max_atv;
    
}
void All_atv_reset() {
    for(int i=1;i<=Total_unit;i++){
        Update_Max_atv(unit[i]->Atv_stats.get());
        atv_reset(unit[i]->Atv_stats.get());
     }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Summon_ptr==nullptr)continue;
        Update_Max_atv(Ally_unit[i]->stats->Summon_ptr->Atv_stats.get());
        atv_reset(Ally_unit[i]->stats->Summon_ptr->Atv_stats.get());
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Countdown==nullptr)continue;
        Update_Max_atv(Ally_unit[i]->stats->Countdown->Atv_stats.get());
        atv_reset(Ally_unit[i]->stats->Countdown->Atv_stats.get());
    }
    
}
void Action_forward(Action_value_stats *ptr,double fwd) {
    if(ptr->Base_speed<=0)return;
    if(ptr->Character_num==0){
        return ;
    }
    if (ptr->atv <= ptr->Max_atv*fwd/100 ) {
        ptr->atv = 0;
        ptr->priority = ++Turn_priority;
        return ;
    } else {
        ptr->atv = ptr->atv - ptr->Max_atv*fwd/100;
        return ;
    }
}
void All_Action_forward(double fwd,int Start,int End){
    bool chk[Total_ally+1];
    if(End>Total_ally){
        cout<<"All actionForward error";
        exit(0);
    }
    for(int i=Start;i<=End;i++){
        chk[i]=0;
    }
    for(int i=Start;i<=End;i++){
        int mx =-1;
        int Choose = 0;
        for(int j=Start;j<=End;j++){
        if(chk[j]==1)continue;
        if(Ally_unit[j]->Atv_stats->atv>mx){
            mx = Ally_unit[j]->Atv_stats->atv;
            Choose = j;
        }
        }
        chk[Choose] = 1;
        Action_forward(Ally_unit[Choose]->Atv_stats.get(),fwd);
    }
}


void Speed_Buff(Action_value_stats *ptr,double spd_percent ,double flat_spd ) {
    double x = ptr->Max_atv;
    ptr->Flat_speed += flat_spd;
    ptr->Speed_percent += spd_percent;
    Update_Max_atv(ptr);
    ptr->atv=ptr->atv/x*ptr->Max_atv;
}

void Increase_energy(Ally_stats *stats_ptr,double Energy ){
    if(stats_ptr->Current_energy+Energy*stats_ptr->Energy_recharge/100 > stats_ptr->Max_energy){
        stats_ptr->Current_energy = stats_ptr->Max_energy;
    }else{
         stats_ptr->Current_energy +=  Energy*stats_ptr->Energy_recharge/100;
    }
    return ;
}
void Increase_energy(Ally_stats *stats_ptr,double Energy_percent,double Flat_energy){
    if(stats_ptr->Current_energy+Flat_energy+Energy_percent/100*stats_ptr->Max_energy > stats_ptr->Max_energy){
        stats_ptr->Current_energy = stats_ptr->Max_energy;
    }else{
         stats_ptr->Current_energy += Flat_energy+Energy_percent/100*stats_ptr->Max_energy;
    }
    return ;
}
void Find_turn(){
    pair<double,int> mx;
    turn = nullptr;
    mx.first = 1e9;
    mx.second = 0;
    for(int i=1;i<=Total_unit;i++){
        if(mx.first > unit[i]->Atv_stats->atv){
            mx.first = unit[i]->Atv_stats->atv;
            mx.second = unit[i]->Atv_stats->priority;
            turn = unit[i]->Atv_stats.get();
            continue;
        }
        if(mx.first == unit[i]->Atv_stats->atv){
            if(mx.second<unit[i]->Atv_stats->priority){
                mx.second = unit[i]->Atv_stats->priority;
            turn = unit[i]->Atv_stats.get();
            }
        }
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Summon_ptr==nullptr)continue;
        if(mx.first >Ally_unit[i]->stats->Summon_ptr->Atv_stats->atv){
            mx.first = Ally_unit[i]->stats->Summon_ptr->Atv_stats->atv;
            mx.second = Ally_unit[i]->stats->Summon_ptr->Atv_stats->priority;
            turn = Ally_unit[i]->stats->Summon_ptr->Atv_stats.get();
            continue;
        }
        if(mx.first == Ally_unit[i]->stats->Summon_ptr->Atv_stats->atv){
            if(mx.second<Ally_unit[i]->stats->Summon_ptr->Atv_stats->priority){
                mx.second = Ally_unit[i]->stats->Summon_ptr->Atv_stats->priority;
            turn = Ally_unit[i]->stats->Summon_ptr->Atv_stats.get();
            }
        }
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Countdown==nullptr)continue;
        if(mx.first > Ally_unit[i]->stats->Countdown->Atv_stats->atv){
            mx.first = Ally_unit[i]->stats->Countdown->Atv_stats->atv;
            mx.second = Ally_unit[i]->stats->Countdown->Atv_stats->priority;
            turn = Ally_unit[i]->stats->Countdown->Atv_stats.get();
            continue;
        }
        if(mx.first == Ally_unit[i]->stats->Countdown->Atv_stats->atv){
            if(mx.second<Ally_unit[i]->stats->Countdown->Atv_stats->priority){
                mx.second = Ally_unit[i]->stats->Countdown->Atv_stats->priority;
            turn = Ally_unit[i]->stats->Countdown->Atv_stats.get();
            }
        }
    }
}
void Atv_fix(double Atv_reduce){
    for(int i=1;i<=Total_unit;i++){
        unit[i]->Atv_stats->atv -= Atv_reduce;
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Summon_ptr==nullptr)continue;
        Ally_unit[i]->stats->Summon_ptr->Atv_stats->atv -= Atv_reduce;
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Countdown==nullptr)continue;
        Ally_unit[i]->stats->Countdown->Atv_stats->atv -= Atv_reduce;
    }
    Current_atv+=Atv_reduce;
}
#endif