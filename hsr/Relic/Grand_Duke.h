
#ifndef Grand_Duke_H
#define Grand_Duke_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Relic{
    void Grand_Duke(Ally *ptr);
    void Grand_Duke(Ally *ptr){
        ptr->stats->Relic.Reset_func = [](Ally *ptr){
            ptr->Dmg_bonus["Fua"]+=20;

        };
        ptr->stats->Relic.Hit_func = [](Ally *ptr,Combat_data &data_,int Hit_cnt){
            bool check=0;
            if(data_.num!=ptr->Atv_stats->Character_num)return;
            for(auto e:data_.Damage_type){
                if(e == "Fua")check=1;
            }
            if(check==1){
            if(Hit_cnt>8){
                Hit_cnt = 8;
            }
            ptr->Atk_percent["None"] -= ptr->stats->Stack["Grand_Duke"]*6;
            ptr->stats->Stack["Grand_Duke"] = Hit_cnt;
            ptr->Atk_percent["None"] += ptr->stats->Stack["Grand_Duke"]*6;
            ptr->stats->Buff_countdown["Grand_Duke"] = ptr->Atv_stats->turn_cnt + 3;
            }
            
        };
        ptr->stats->Relic.After_turn_func = [](Ally *ptr){
        if(!(ptr->Atv_stats->Character_num == turn->Character_num && turn->Side=="Ally"))return;
        if(ptr->stats->Buff_countdown["Grand_Duke"] == ptr->Atv_stats->turn_cnt){
            ptr->Atk_percent["None"] -= ptr->stats->Stack["Grand_Duke"]*6;
            ptr->stats->Stack["Grand_Duke"] = 0;
        }
        };
        
    }
}
#endif