#ifndef Setup_H
#define Setup_H
#include<bits/stdc++.h>
#include"Basic_function.cpp"

#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
#define K_const 10000
//Defination
void Setup();

void Start_game();
void Start_wave();
void Reset();
bool Reroll_substats(Ally *ptr);



void Setup(){
    for(int i=1;i<=Total_ally;i++){
        Ally_unit[i]->Atk_flat["None"] = 0;
        Ally_unit[i]->Atk_percent["None"] = 0;
        Ally_unit[i]->Hp_flat["None"] = 0;
        Ally_unit[i]->Hp_percent["None"] = 0;
        Ally_unit[i]->Def_flat["None"] = 0;
        Ally_unit[i]->Def_percent["None"] = 0;
        Ally_unit[i]->Dmg_bonus["None"] = 0;
        Ally_unit[i]->Crit_rate["None"] = 0;
        Ally_unit[i]->Crit_dam["None"] = 0;
        Ally_unit[i]->Def_shred["None"] = 0;
        Ally_unit[i]->Respen["None"] = 0;
        Ally_unit[i]->Vul["None"] = 0;
        Ally_unit[i]->Break_effect["None"] = 0;
        Ally_unit[i]->stats->Normal_Damage.resize(Total_enemy+1);
        Ally_unit[i]->stats->Dot_damage.resize(Total_enemy+1);
        Ally_unit[i]->stats->Break_damage.resize(Total_enemy+1);
        Ally_unit[i]->stats->Superbreak_damage.resize(Total_enemy+1);
        
        cout<<endl;
        Ally_unit[i]->stats->Max_Damage.resize(Total_enemy+1);
        Ally_unit[i]->stats->Max_Dot_damage.resize(Total_enemy+1);
        Ally_unit[i]->stats->Max_Break_damage.resize(Total_enemy+1);
        Ally_unit[i]->stats->Max_Superbreak_damage.resize(Total_enemy+1);




    }
}

void Reset(){
    sp =3;
    Basic_reset();
    Summon_reset();
    Countdown_reset();
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Char_func.Reset_func)
        Ally_unit[i]->stats->Char_func.Reset_func(Ally_unit[i].get());

        if(Ally_unit[i]->stats->Light_cone.Reset_func)
        Ally_unit[i]->stats->Light_cone.Reset_func(Ally_unit[i].get());

        if(Ally_unit[i]->stats->Relic.Reset_func)
        Ally_unit[i]->stats->Relic.Reset_func(Ally_unit[i].get());
        
        if(Ally_unit[i]->stats->Planar.Reset_func)
        Ally_unit[i]->stats->Planar.Reset_func(Ally_unit[i].get());
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Tune_stats_func)
        Ally_unit[i]->stats->Tune_stats_func(Ally_unit[i].get());
    }
    
}

void Start_game(){
    All_atv_reset();
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Char_func.Start_game_func)
        Ally_unit[i]->stats->Char_func.Start_game_func(Ally_unit[i].get());

        if(Ally_unit[i]->stats->Light_cone.Start_game_func)
        Ally_unit[i]->stats->Light_cone.Start_game_func(Ally_unit[i].get());

        if(Ally_unit[i]->stats->Relic.Start_game_func)
        Ally_unit[i]->stats->Relic.Start_game_func(Ally_unit[i].get());
        
        if(Ally_unit[i]->stats->Planar.Start_game_func)
        Ally_unit[i]->stats->Planar.Start_game_func(Ally_unit[i].get());
    }
}
void EndWave(double Total_atv){
    
    double temp = 0;
    for(int i=1;i<=Total_enemy;i++){
        for(int j=1;j<=Total_ally;j++){
            Ally_unit[j]->stats->Normal_Damage[i] *= Cal_Average(Enemy_unit[i].get(),Total_atv);
            Ally_unit[j]->stats->Dot_damage[i]*= Cal_Average(Enemy_unit[i].get(),Total_atv);
            Ally_unit[j]->stats->Total_damage+=(Ally_unit[j]->stats->Dot_damage[i]+Ally_unit[j]->stats->Normal_Damage[i]+Ally_unit[j]->stats->Superbreak_damage[i] +Ally_unit[j]->stats->Break_damage[i]);
            
            
        }
    }
   
    cout<<endl;
    
}
void Start_wave(){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Char_func.Start_wave_func)
        Ally_unit[i]->stats->Char_func.Start_wave_func(Ally_unit[i].get());

        if(Ally_unit[i]->stats->Light_cone.Start_wave_func)
        Ally_unit[i]->stats->Light_cone.Start_wave_func(Ally_unit[i].get());

        if(Ally_unit[i]->stats->Relic.Start_wave_func)
        Ally_unit[i]->stats->Relic.Start_wave_func(Ally_unit[i].get());
        
        if(Ally_unit[i]->stats->Planar.Start_wave_func)
        Ally_unit[i]->stats->Planar.Start_wave_func(Ally_unit[i].get());
    }
    All_atv_reset();
    for(int i =1;i<=Total_enemy;i++){
        Enemy_unit[i]->stats->Toughness_status=1;
        Enemy_unit[i]->stats->Current_toughness=Enemy_unit[i]->stats->Max_toughness;
        Enemy_unit[i]->stats->when_toughness_broken = 0;
        Enemy_unit[i]->stats->Total_toughness_broken_time = 0;
    }
}
bool Reroll_substats(Ally *ptr){
    if(0 == ptr->stats->Reroll_check){
        double Temp_mx=0;
        for(int i=1;i<=Total_enemy;i++){    
            Temp_mx+=ptr->stats->Normal_Damage[i];
            ptr->stats->Normal_Damage[i] = 0;
        }
        for(int i=1;i<=Total_enemy;i++){
            Temp_mx+=ptr->stats->Break_damage[i];
            ptr->stats->Break_damage[i] = 0;
        }
        for(int i=1;i<=Total_enemy;i++){
            Temp_mx+=ptr->stats->Dot_damage[i];
            ptr->stats->Dot_damage[i] = 0;
        }
        for(int i=1;i<=Total_enemy;i++){
            Temp_mx+=ptr->stats->Superbreak_damage[i];
            ptr->stats->Superbreak_damage[i] = 0;
        }
        ptr->stats->Max =Temp_mx;
        for(int i=0,sz = ptr->stats->Substats.size();i<sz;i++){
        if(ptr->stats->Substats[i].first=="Crit_rate"){
            ptr->Crit_rate["None"]+=2.9*ptr->stats->Substats[i].second;

        }else if(ptr->stats->Substats[i].first=="Crit_dam"){
            ptr->Crit_dam["None"]+=5.8*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Atk_percent"){
            ptr->Atk_percent["None"]+=3.888*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Hp_percent"){
            ptr->Hp_percent["None"]+=3.888*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Def_percent"){
            ptr->Def_percent["None"]+=4.86*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Speed"){
            ptr->Atv_stats->Flat_speed+=2.3*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Break_effect"){
            ptr->Break_effect["None"]+=5.8*ptr->stats->Substats[i].second;
            
        }
    }
        return 0;
    }

    if(ptr->stats->Current_spilt==0){
        ptr->stats->Current_spilt = 1;
        for(int i=0,sz = ptr->stats->Substats.size();i<sz;i++){
        if(ptr->stats->Substats[i].first=="Crit_rate"){
            ptr->Crit_rate["None"]+=2.9*ptr->stats->Substats[i].second;

        }else if(ptr->stats->Substats[i].first=="Crit_dam"){
            ptr->Crit_dam["None"]+=5.8*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Atk_percent"){
            ptr->Atk_percent["None"]+=3.888*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Hp_percent"){
            ptr->Hp_percent["None"]+=3.888*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Def_percent"){
            ptr->Def_percent["None"]+=4.86*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Speed"){
            ptr->Atv_stats->Flat_speed+=2.3*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Break_effect"){
            ptr->Break_effect["None"]+=5.8*ptr->stats->Substats[i].second;
            
        }
    }
        return 1;
    }
  
    if(ptr->stats->Total_damage>ptr->stats->Max){
        ptr->stats->Max = ptr->stats->Total_damage;
        for(int i=0,sz = ptr->stats->Max_damage_Substats.size();i<sz;i++){
            ptr->stats->Max_damage_Substats[i] = ptr->stats->Substats[i].second;
            ptr->stats->Stop_reroll = 0;
        }
    }
    ptr->stats->Total_damage = 0;
    for(int i=1;i<=Total_enemy;i++){
        ptr->stats->Normal_Damage[i] = 0;
    }
    for(int i=1;i<=Total_enemy;i++){
        ptr->stats->Break_damage[i] = 0;
    }
    for(int i=1;i<=Total_enemy;i++){
        ptr->stats->Dot_damage[i] = 0;
    }
    for(int i=1;i<=Total_enemy;i++){
        ptr->stats->Superbreak_damage[i] = 0;
    }
    
    if(ptr->stats->Current_sub_choose+1==ptr->stats->Current_spilt){
        if(1 == ptr->stats->Stop_reroll||ptr->stats->Separate_sub==0){
            ptr->stats->Current_spilt++;
            if(ptr->stats->Current_spilt==ptr->stats->Substats.size()){
                ptr->stats->Reroll_check=0;
                return 0;
            }
            ptr->stats->Separate_sub = ptr->stats->Total_substats-1;
            ptr->stats->Current_sub_choose = 0;
            ptr->stats->Stop_reroll = 1;

            ptr->stats->Substats[0].second = ptr->stats->Max_damage_Substats[0]-1;
            for(int i=1;i<ptr->stats->Current_spilt;i++){
                ptr->stats->Substats[i].second = ptr->stats->Max_damage_Substats[i];
            }
            ptr->stats->Substats[ptr->stats->Current_spilt].second = ptr->stats->Max_damage_Substats[ptr->stats->Current_spilt]+1;
        
            
        }else{
            --ptr->stats->Separate_sub;
        ptr->stats->Current_sub_choose = 0;
        ptr->stats->Stop_reroll = 1;
        ptr->stats->Substats[0].second = ptr->stats->Max_damage_Substats[0]-1;
        for(int i=1;i<ptr->stats->Current_spilt;i++){
            ptr->stats->Substats[i].second = ptr->stats->Max_damage_Substats[i];
        }
        ptr->stats->Substats[ptr->stats->Current_spilt].second = ptr->stats->Max_damage_Substats[ptr->stats->Current_spilt]+1;
        }
    }else{
        ptr->stats->Substats[ptr->stats->Current_sub_choose].second++;
        ++ptr->stats->Current_sub_choose;
        ptr->stats->Substats[ptr->stats->Current_sub_choose].second--;

    }
    for(int i=0,sz = ptr->stats->Substats.size();i<sz;i++){
        if(ptr->stats->Substats[i].first=="Crit_rate"){
            ptr->Crit_rate["None"]+=2.9*ptr->stats->Substats[i].second;

        }else if(ptr->stats->Substats[i].first=="Crit_dam"){
            ptr->Crit_dam["None"]+=5.8*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Atk_percent"){
            ptr->Atk_percent["None"]+=3.888*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Hp_percent"){
            ptr->Hp_percent["None"]+=3.888*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Def_percent"){
            ptr->Def_percent["None"]+=4.86*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Speed"){
            ptr->Atv_stats->Flat_speed+=2.3*ptr->stats->Substats[i].second;
            
        }else if(ptr->stats->Substats[i].first=="Break_effect"){
            ptr->Break_effect["None"]+=5.8*ptr->stats->Substats[i].second;
            
        }
    }
    return 1;

}
#endif