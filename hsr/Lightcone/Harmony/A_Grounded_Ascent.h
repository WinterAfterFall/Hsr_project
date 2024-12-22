
#ifndef A_Grounded_Ascent_H
#define A_Grounded_Ascent_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Harmony_Lightcone{
    void A_Grounded_Ascent(Ally *ptr);
    void A_Grounded_Ascent(Ally *ptr){
        ptr->stats->Base_hp += 1164;
        ptr->stats->Base_hp += 476;
        ptr->stats->Base_hp += 529;
        ptr->stats->Light_cone.Buff_func = [](Ally *ptr,Combat_data &data_){
            if(data_.num == ptr->Atv_stats->Character_num && data_.Buff_type.size()!=0 && data_.Target_type == "Single_target"){
                Increase_energy(ptr->stats.get(),6);
                Ally_unit[Main_dps_num]->stats->Buff_countdown["Hymn"] =Ally_unit[Main_dps_num]->Atv_stats->turn_cnt+3 ;
                if(Ally_unit[Main_dps_num]->stats->Stack["Hymn"]<6){
                ++Ally_unit[Main_dps_num]->stats->Stack["Hymn"];
                Ally_unit[Main_dps_num]->Dmg_bonus["None"]+=15;
                }

                ++ptr->stats->Stack["Hymn_cnt"];
                if(ptr->stats->Stack["Hymn_cnt"]==2){
                    Skill_point(1);
                    ptr->stats->Stack["Hymn_cnt"] = 0;
                }
            }
        };
        ptr->stats->Light_cone.After_turn_func = [](Ally *ptr){
        if(!(Ally_unit[Main_dps_num]->Atv_stats->Character_num == turn->Character_num && turn->Side=="Ally"))return;
            if(Ally_unit[Main_dps_num]->stats->Buff_countdown["Hymn"] ==Ally_unit[Main_dps_num]->Atv_stats->turn_cnt){
                Ally_unit[Main_dps_num]->Dmg_bonus["None"]-=15*Ally_unit[Main_dps_num]->stats->Stack["Hymn"];
                Ally_unit[Main_dps_num]->stats->Stack["Hymn"]=0;
            }
        };
    }
}
#endif