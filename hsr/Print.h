#include<bits/stdc++.h>


#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
using std::cout ;
using std::vector;
//#include"Setup.cpp"
#include"Calculate_damage.cpp"
#include".\Character\All_Character.h"
#include".\Lightcone\All_Lighcone.h"
#include".\Planar\All_Planar.h"
#include".\Relic\All_Relic.h"
void Print();
void Print_damage();
void Print(){
    //return;
    cout<<Current_atv<<" ";
    cout<<turn->Name<<" ";
    cout<<"Turn = "<<turn->turn_cnt<<" ";
    //cout<<"last sp = "<<Ally_unit[3]->stats->Buff_note["Last_sp"]<<" ";
    //cout<<"defshred = "<<Ally_unit[1]->Def_shred["None"]<<" ";
    cout<<"Atk = "<<Ally_unit[1]->Atk_percent["None"]<<" ";
    cout<<"dmg = "<<Ally_unit[1]->Dmg_bonus["None"]<<" ";
    //cout<<"crit = "<<Ally_unit[1]->Crit_dam["None"]<<" ";

    cout<<Ally_unit[3]->stats->Current_energy<<" ";
    cout<<sp<<" ";
    // for(int i=1;i<=Total_enemy;i++){
    //     cout<<Enemy_unit[i]->Def_shred["None"]<<" ";
    // }
    
    
    cout<<endl;
}
void Print_damage(){
    
    for(int j=1;j<=Total_ally;j++){
    double temp = 0;
    cout<<Ally_unit[j]->Atv_stats->Name<<" ";
    //cout<<Ally_unit[j]->stats->Normal_Damage[1]<<" ";
    // for(int i=1;i<=Total_enemy;i++){
    //     temp+=Ally_unit[j]->stats->Total_Damage[i];
        
    // }
    // cout<<static_cast<long long>(temp)<<" ";
    // for(int i=1;i<=Total_enemy;i++){
    //     temp+=Ally_unit[j]->stats->Total_Break_damage[i];
        
    // }
    // cout<<static_cast<long long>(temp)<<" ";
    // for(int i=1;i<=Total_enemy;i++){
    //     temp+=Ally_unit[j]->stats->Total_Dot_damage[i];
        
    // }
    // cout<<static_cast<long long>(temp)<<" ";
    // for(int i=1;i<=Total_enemy;i++){
    //     temp+=Ally_unit[j]->stats->Total_Superbreak_damage[i];
        
    // }
    cout<<static_cast<long long>(Ally_unit[j]->stats->Max)<<" ";
    cout<<Ally_unit[j]->Atv_stats->turn_cnt<<" ";
    cout<<endl;
    }
}