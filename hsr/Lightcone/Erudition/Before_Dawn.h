
#ifndef Before_Dawn_H
#define Before_Dawn_H

#include"..\..\Setup.cpp"
namespace Erudition_Lightcone{
    void Before_Dawn(Ally *ptr);
    void Before_Dawn(Ally *ptr){
        ptr->stats->Base_hp += 1058;
        ptr->stats->Base_atk += 582;
        ptr->stats->Base_def += 463;
        ptr->stats->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Crit_dam["None"]+=36;
            ptr->Dmg_bonus["Skill"]+=18;
            ptr->Dmg_bonus["Ultimate"]+=18;
        };
        ptr->stats->Light_cone.Before_attack_func = [](Ally *ptr,Combat_data &data_){
            if(turn->Character_num==ptr->Atv_stats->Character_num&&ptr->stats->Stack["Somnus_Corpus"]==1){
                for(auto e:data_.Damage_type){
                if(e =="Fua"){
                    ptr->Dmg_bonus["Fua"]+=48;
                    break;
                }
            }
            }
        };
        ptr->stats->Light_cone.After_attack_func = [](Ally *ptr,Combat_data &data_){
            if(data_.num != ptr->Atv_stats->Character_num)return;
            for(auto e:data_.Damage_type){
                if(e =="Skill"||e =="Ultimate"){
                    ptr->stats->Stack["Somnus_Corpus"]=1;
                    break;
                }
            }
            if(turn->Character_num==ptr->Atv_stats->Character_num&&ptr->stats->Stack["Somnus_Corpus"]==1){
                for(auto e:data_.Damage_type){
                if(e =="Fua"){
                    ptr->Dmg_bonus["Fua"]-=48;
                    ptr->stats->Stack["Somnus_Corpus"]=0;
                    break;
                }
            }
            }
        };
        
    }
}
#endif