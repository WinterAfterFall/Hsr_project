#include<bits/stdc++.h>


#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
using std::cout ;
using std::vector;
#include"Setup.cpp"

#include".\Character\All_Character.h"
#include".\Lightcone\All_Lighcone.h"
#include".\Planar\All_Planar.h"
#include".\Relic\All_Relic.h"
bool first_time=1;
int main(){ 
    Formula_check_mode =0;



    Jingyuan::Setup_Jingyuan(1,0,Erudition_Lightcone::Cosmos_Fell,Relic::Grand_Duke,Planar::The_Wondrous_BananAmusement_Park);

    Sunday::Setup_Slow_Sunday(2,0,Harmony_Lightcone::A_Grounded_Ascent,Relic::Sacerdos_Relived_Ordeal,Planar::Lushaka); 
    //Robin::Setup_Fast_Robin(3,0,Harmony_Lightcone::For_Tomorrow_Journey,Relic::Double_Atk,Planar::Lushaka);
    //Hanabi::Setup(3,0,Harmony_Lightcone::But_the_Battle_Isnt_Over,Relic::Sacerdos_Relived_Ordeal,Planar::Lushaka);
    Tingyun::Setup(3,6,Harmony_Lightcone::DDD,Relic::Double_Speed,Planar::Lushaka);
    //Pela::Setup(3,6,Nihility_Lightcone::Resolution,Relic::Double_Speed,Planar::Lushaka);

    //Aventurine::Set_up(4,0,Preservation_Lightcone::DayOne_of_MyNewLife,Relic::Knight,Planar::Lushaka);
    Luocha::Setup(4,0,Abundance_Lightcone::Multiplication,Relic::Double_Speed,Planar::Lushaka);

    //Jingyuan::Fix_Slow_Jingyuan(Ally_unit[1].get());
    Timing_print(Ally_unit[3].get());
    //Set_Technique(Ally_unit[2].get(),0);




    Setup_enemy(1,158,15,160,"Main");
    Setup_enemy(2,158,10,160,"Adjacent");
    Setup();
    
    while(1){
        cout<<" ---------------------------------------------------------- ";
        cout<<endl;
        bool endgame =1;
        bool skip = 0;
        Reset();
        
        for(int i=1;i<=Total_ally;i++){
            if(Reroll_substats(Ally_unit[i].get()))endgame = 0;
        }
        if(endgame==1&&first_time==0)break;
        
        Start_game();
        for(auto &e:Ally_unit[1]->stats->Substats){
        cout<<e.second<<" ";
        if(e.second<0){
            skip =1;
        }
        }
        cout<<endl;
        if(skip)continue;

    for(int i=0;i<Total_wave;i++){
        
        Current_atv=0;
        Start_wave();
        while(1){
            Turn_Skip=0;
            Find_turn();
            Atv_fix(turn->atv);
            if(Current_atv>Wave[i]){
                EndWave(Wave[i]);
                break;
            }
            
            Take_action();
        }
    }
    Print_damage();
    //exit(0);
    first_time = 0;
    
    }
    
    
    return 0;
}
