
#ifndef Sacerdos_H
#define Sacerdos_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Relic{
    void Sacerdos_Relived_Ordeal(Ally *ptr);
    void Sacerdos_Relived_Ordeal(Ally *ptr){
        ptr->stats->Relic.Reset_func = [](Ally *ptr){
            ptr->Atv_stats->Speed_percent += 6;
        };
        ptr->stats->Relic.Buff_func =[](Ally *ptr, Combat_data &data_){
             if(data_.num == ptr->Atv_stats->Character_num && data_.Target_type == "Single_target"){
                Ally_unit[Main_dps_num]->stats->Buff_countdown["Sacerdos"] =Ally_unit[Main_dps_num]->Atv_stats->turn_cnt+2 ;
                if(Ally_unit[Main_dps_num]->stats->Stack["Sacerdos"]<2){
                Ally_unit[Main_dps_num]->Crit_dam["None"]+=18;
                ++Ally_unit[Main_dps_num]->stats->Stack["Sacerdos"]; 
                }
             }
        };
        ptr->stats->Relic.After_turn_func =[](Ally *ptr){
        if(!(Ally_unit[Main_dps_num]->Atv_stats->Character_num == turn->Character_num && turn->Side=="Ally"))return;
        if(Ally_unit[Main_dps_num]->stats->Buff_countdown["Sacerdos"] ==Ally_unit[Main_dps_num]->Atv_stats->turn_cnt){
            Ally_unit[Main_dps_num]->Crit_dam["None"]-=18*Ally_unit[Main_dps_num]->stats->Stack["Sacerdos"];
            Ally_unit[Main_dps_num]->stats->Stack["Sacerdos"] = 0;
        }
        };
    }
}
#endif