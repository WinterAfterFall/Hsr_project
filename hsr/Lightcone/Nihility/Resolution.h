
#ifndef Resolution_H
#define Resolution_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Nihility_Lightcone{
    void Resolution(Ally *ptr);
    void Resolution(Ally *ptr){
        ptr->stats->Base_hp += 953;
        ptr->stats->Base_hp += 476;
        ptr->stats->Base_hp += 331;

        ptr->stats->Light_cone.After_attack_func = [](Ally *ptr, Combat_data &data_){
            if(data_.num!=ptr->Atv_stats->Character_num)return;
            int sz2 = data_.Damage_spilt.Adjacent.size();
            int sz3 = data_.Damage_spilt.Other.size();
            for(int i=1;i<=Total_enemy;i++){

            if(Enemy_unit[i]->stats->Target_type=="Main"){
                if(Enemy_unit[i]->stats->Debuff["Ensnared"]==1)continue;
                Enemy_unit[i]->Def_shred["None"]+=16;
                Enemy_unit[i]->stats->Debuff["Ensnared"]=1;
                Enemy_unit[i]->stats->Debuff_time_count["Ensnared"]= 1 + Enemy_unit[i]->Atv_stats->turn_cnt;
                Apply_debuff(ptr,Enemy_unit[i].get(),1);
                ++Enemy_unit[i]->stats->Total_debuff;
            }
            
            if(0<sz2 && Enemy_unit[i]->stats->Target_type=="Adjacent"){
                if(Enemy_unit[i]->stats->Debuff["Ensnared"]==1)continue;
                Enemy_unit[i]->Def_shred["None"]+=16;
                Enemy_unit[i]->stats->Debuff["Ensnared"]=1;
                Enemy_unit[i]->stats->Debuff_time_count["Ensnared"]= 1 + Enemy_unit[i]->Atv_stats->turn_cnt;
                Apply_debuff(ptr,Enemy_unit[i].get(),1);
                ++Enemy_unit[i]->stats->Total_debuff;
            }
            
            if(0<sz3 && Enemy_unit[i]->stats->Target_type=="Other"){
                if(Enemy_unit[i]->stats->Debuff["Ensnared"]==1)continue;
                Enemy_unit[i]->Def_shred["None"]+=16;
                Enemy_unit[i]->stats->Debuff["Ensnared"]=1;
                Enemy_unit[i]->stats->Debuff_time_count["Ensnared"]= 1 + Enemy_unit[i]->Atv_stats->turn_cnt;
                Apply_debuff(ptr,Enemy_unit[i].get(),1);
                ++Enemy_unit[i]->stats->Total_debuff;
            }
            
            
        }
            
        };
        ptr->stats->Light_cone.After_turn_func = [](Ally *ptr){
            if(turn->Side=="Enemy"){
                if(Enemy_unit[turn->Character_num]->stats->Debuff_time_count["Ensnared"]==Enemy_unit[turn->Character_num]->Atv_stats->turn_cnt){
                    Enemy_unit[turn->Character_num]->Def_shred["None"]-=16;
                Enemy_unit[turn->Character_num]->stats->Debuff["Ensnared"]=0;
                --Enemy_unit[turn->Character_num]->stats->Total_debuff;
                }
            }
        
        
        };

    }
}
#endif