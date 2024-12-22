#ifndef Cal_damage_H
#define Cal_damage_H
#include<bits/stdc++.h>
#include"Action_value.h"

#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
#define K_const 10000



queue<Combat_data> Action_bar;

class Ratio_data{
    public:
    double Atk_ratio;
    double Hp_ratio;
    double Def_ratio;
    double Toughness_ratio;
};
class Hit_spilt{
    public:
    vector<Ratio_data> Main;
    vector<Ratio_data> Adjacent;
    vector<Ratio_data> Other;
};
class Combat_data{
    public:
    int num=0;
    bool Turn_reset = 0;
    bool Dont_care_weakness =0;
    Hit_spilt Damage_spilt;
    
    pair<string,string> Action_type;//Attack Buff//Skill Basic_Attack Ultimate

    vector<string> Buff_type;//Buff Heal Shield 
    vector<string> Damage_type;//  None Basic_Attack Skill Ultimate  Dot  Fua  Summon  Break_dmg  Super_break Additional
    string Damage_element;//Physical Fire Ice Lightning Wind Quantum Imaginary

    string Target_type = "";// Aoe Single_target Bounce
    
    
    

};
double Cal_Atk_multiplier(Combat_data &data_,Enemy *target){
    double ans=Ally_unit[data_.num]->stats->Base_atk;
    double Atk_percent_mtpr = Ally_unit[data_.num]->Atk_percent["None"] + target->Atk_percent["None"];
    double Flat_atk_mtpr = Ally_unit[data_.num]->Atk_flat["None"] + target->Atk_flat["None"];
    for(int i=0,sz=data_.Damage_type.size();i<sz;i++){
            Atk_percent_mtpr+= Ally_unit[data_.num]->Atk_percent[data_.Damage_type[i]];
            Atk_percent_mtpr+= target->Atk_percent[data_.Damage_type[i]];

            Flat_atk_mtpr += Ally_unit[data_.num]->Atk_flat[data_.Damage_type[i]];
            Flat_atk_mtpr += target->Atk_flat[data_.Damage_type[i]];
    }

    ans = (ans * Atk_percent_mtpr/100) + Flat_atk_mtpr;
    return ans;
}
double Cal_Hp_multiplier(Combat_data &data_,Enemy *target){
    double ans=Ally_unit[data_.num]->stats->Base_hp;
    double Hp_percent_mtpr = Ally_unit[data_.num]->Hp_percent["None"] + target->Hp_percent["None"];
    double Flat_hp_mtpr = Ally_unit[data_.num]->Hp_flat["None"] + target->Hp_flat["None"];
    for(int i=0,sz=data_.Damage_type.size();i<sz;i++){
            Hp_percent_mtpr+= Ally_unit[data_.num]->Hp_percent[data_.Damage_type[i]];
            Hp_percent_mtpr+= target->Hp_percent[data_.Damage_type[i]];

            Flat_hp_mtpr += Ally_unit[data_.num]->Hp_flat[data_.Damage_type[i]];
            Flat_hp_mtpr += target->Hp_flat[data_.Damage_type[i]];
    }
    ans = (ans * Hp_percent_mtpr/100) + Flat_hp_mtpr;
    return ans;
}

double Cal_Def_multiplier(Combat_data &data_,Enemy *target){
    double ans=Ally_unit[data_.num]->stats->Base_def;
    double Def_percent_mtpr = Ally_unit[data_.num]->Def_percent["None"] + target->Def_percent["None"];
    double Flat_def_mtpr = Ally_unit[data_.num]->Def_flat["None"] + target->Def_flat["None"];
    for(int i=0,sz=data_.Damage_type.size();i<sz;i++){
            Def_percent_mtpr+= Ally_unit[data_.num]->Def_percent[data_.Damage_type[i]];
            Def_percent_mtpr+= target->Def_percent[data_.Damage_type[i]];

            Flat_def_mtpr += Ally_unit[data_.num]->Def_flat[data_.Damage_type[i]];
            Flat_def_mtpr += target->Def_flat[data_.Damage_type[i]];
    }
    ans = (ans *Def_percent_mtpr/100) + Flat_def_mtpr;
    return ans;
}
double Cal_Bonus_dmg_multiplier(Combat_data &data_,Enemy *target){
    double Bonus_dmg_mtpr = Ally_unit[data_.num]->Dmg_bonus["None"] + target->Dmg_bonus["None"] + Ally_unit[data_.num]->Dmg_bonus_each_element[data_.Damage_element]["None"] +target->Dmg_bonus_each_element[data_.Damage_element]["None"] ;

    for(int i=0,sz=data_.Damage_type.size();i<sz;i++){
            Bonus_dmg_mtpr += Ally_unit[data_.num]->Dmg_bonus[data_.Damage_type[i]] + Ally_unit[data_.num]->Dmg_bonus_each_element[data_.Damage_element][data_.Damage_type[i]] ;
            Bonus_dmg_mtpr += target->Dmg_bonus[data_.Damage_type[i]]+target->Dmg_bonus_each_element[data_.Damage_element][data_.Damage_type[i]];
    }
    return Bonus_dmg_mtpr/100;
}
double Cal_Crit_multiplier(Combat_data &data_,Enemy *target){

    double Crit_rate_mtpr = Ally_unit[data_.num]->Crit_rate["None"] + target->Crit_rate["None"];
    double Crit_dam_mtpr = Ally_unit[data_.num]->Crit_dam["None"] + target->Crit_dam["None"];
    for(int i=0,sz=data_.Damage_type.size();i<sz;i++){
            Crit_rate_mtpr += Ally_unit[data_.num]->Crit_rate[data_.Damage_type[i]] + target->Crit_rate[data_.Damage_type[i]];
            Crit_dam_mtpr += Ally_unit[data_.num]->Crit_dam[data_.Damage_type[i]] + target->Crit_dam[data_.Damage_type[i]];
    }
    if(Crit_rate_mtpr>=100){
        Crit_rate_mtpr = 100;
    }
    return (1+(Crit_rate_mtpr/100 * Crit_dam_mtpr/100));

}
double Cal_Def_shred_multiplier(Combat_data &data_,Enemy *target){
    double Def_shred_mtpr = Ally_unit[data_.num]->Def_shred["None"] + target->Def_shred["None"];

    for(int i=0,sz=data_.Damage_type.size();i<sz;i++){
            Def_shred_mtpr += Ally_unit[data_.num]->Def_shred[data_.Damage_type[i]] + target->Def_shred[data_.Damage_type[i]];
    }
    if(Def_shred_mtpr>=100){
        Def_shred_mtpr = 100;
    }
    return 100/(100 + 115*(1-1*Def_shred_mtpr/100));
}
double Cal_Respen_multiplier(Combat_data &data_,Enemy *target){
    double Respen_mtpr = Ally_unit[data_.num]->Respen["None"] + target->Respen["None"] + Ally_unit[data_.num]->Respen_each_element[data_.Damage_element]["None"] +target->Respen_each_element[data_.Damage_element]["None"] ;
    for(int i=0,sz=data_.Damage_type.size();i<sz;i++){
            Respen_mtpr += Ally_unit[data_.num]->Respen[data_.Damage_type[i]] + Ally_unit[data_.num]->Respen_each_element[data_.Damage_element][data_.Damage_type[i]] ;
            Respen_mtpr += target->Respen[data_.Damage_type[i]]+target->Respen_each_element[data_.Damage_element][data_.Damage_type[i]];
    }
    return Respen_mtpr/100;
}
double Cal_Vul_multiplier(Combat_data &data_,Enemy *target){
    double Vul_mtpr = Ally_unit[data_.num]->Vul["None"] + target->Vul["None"];
    for(int i=0,sz=data_.Damage_type.size();i<sz;i++){
            Vul_mtpr += Ally_unit[data_.num]->Vul[data_.Damage_type[i]] + target->Vul[data_.Damage_type[i]];

        }
    return Vul_mtpr/100;
}
double Cal_BreakEffect_multiplier(Combat_data &data_,Enemy *target){
    double BreakEffect_mtpr = Ally_unit[data_.num]->Break_effect["None"] + target->Break_effect["None"];
    for(int i=0,sz=data_.Damage_type.size();i<sz;i++){
            BreakEffect_mtpr += Ally_unit[data_.num]->Break_effect[data_.Damage_type[i]] + target->Break_effect[data_.Damage_type[i]];
        }
    return BreakEffect_mtpr/100;
}
double Cal_Toughness_multiplier(Combat_data &data_,Enemy *target){
    if(Avg_damage_Mode||target->stats->Toughness_status==0){
        return 1;
    }else{
        return 0.9;
    }
}
double Cal_Superbreak_DamageIncrease_multiplier(Combat_data &data_,Enemy *target){
    double Spb_dmg_mtpr = Ally_unit[data_.num]->Superbreak_DamageIncrease + target->Superbreak_DamageIncrease;
    return Spb_dmg_mtpr/100;
}
double Cal_Mitigation_multiplier(Combat_data &data_,Enemy *target){
    double Mitigation_mtpr = Ally_unit[data_.num]->Mitigation + target->Mitigation;
    return Mitigation_mtpr/100;
}

void Cal_Damage(Combat_data &data_,Enemy *target,Ratio_data Skill_mtpr){
    double Total_dmg = 0;
    if(Formula_check_mode==1){
        printf("( ( %f * %f ) + ( %f * %f ) + ( %f * %f ) *%f * %f * %f *%f *%f * %f \n)",Cal_Atk_multiplier(data_,target),Skill_mtpr.Atk_ratio/100,Cal_Hp_multiplier(data_,target),Skill_mtpr.Hp_ratio/100
        ,Cal_Def_multiplier(data_,target),Skill_mtpr.Def_ratio/100,Cal_Bonus_dmg_multiplier(data_,target),Cal_Crit_multiplier(data_,target)
        ,Cal_Def_shred_multiplier(data_,target),Cal_Respen_multiplier(data_,target),Cal_Vul_multiplier(data_,target),Cal_Toughness_multiplier(data_,target));
    }
    Total_dmg += Cal_Atk_multiplier(data_,target)*Skill_mtpr.Atk_ratio/100;
    Total_dmg += Cal_Hp_multiplier(data_,target)*Skill_mtpr.Hp_ratio/100;
    Total_dmg += Cal_Def_multiplier(data_,target)*Skill_mtpr.Def_ratio/100;
    Total_dmg = Total_dmg*Cal_Bonus_dmg_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Crit_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Def_shred_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Respen_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Vul_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Toughness_multiplier(data_,target);
    
    Ally_unit[data_.num]->stats->Normal_Damage[target->Atv_stats->Character_num] +=Total_dmg;
    // if(turn->Name=="LL"&&data_.Action_type.second=="Fua"){
    //     // cout<<Cal_Atk_multiplier(data_,target)<<" ";
    //     // cout<<Cal_Bonus_dmg_multiplier(data_,target)<<" ";
    //     // cout<<Cal_Crit_multiplier(data_,target)<<" ";
    //     cout<<Total_dmg<<" ";
    //     cout<<endl;
    // }
    

}
void Cal_Toughness_reduction(Combat_data &data_,Enemy* target,double Toughness_reduce){
    if(target->stats->Weakness_type[data_.Damage_element]==0&& 0 == data_.Dont_care_weakness)return ;
    target->stats->Current_toughness-=Ally_unit[data_.num]->stats->Toughness_reduction/100*Toughness_reduce;
    if(target->stats->Current_toughness<=0&&target->stats->Toughness_status==1){
        if(Force_break!=0){
            int temp1 = data_.num;
            string temp2 = data_.Damage_element;
            data_.num = Force_break;
            data_.Damage_element = Ally_unit[Force_break]->stats->Element_type;
            Toughness_break(data_,target);
            data_.num = temp1;
            data_.Damage_element = temp2;

        }else{
            Toughness_break(data_,target);
        }
        
        target->stats->when_toughness_broken = Current_atv;
    }
}

void Cal_Break_damage(Combat_data &data_,Enemy *target,double &Constant){
    double Total_dmg = Constant *Level_multiplier;
    
    Total_dmg = Total_dmg*(0.5+target->stats->Max_toughness/40);
    Total_dmg = Total_dmg*Cal_BreakEffect_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Def_shred_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Respen_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Vul_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Mitigation_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Toughness_multiplier(data_,target);
    Ally_unit[data_.num]->stats->Break_damage[target->Atv_stats->Character_num] +=Total_dmg;
    
}
void Cal_Freeze_damage(Combat_data &data_,Enemy *target){
    double Total_dmg = Level_multiplier;
    
    Total_dmg = Total_dmg*Cal_BreakEffect_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Def_shred_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Respen_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Vul_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Mitigation_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Toughness_multiplier(data_,target);
    Ally_unit[data_.num]->stats->Break_damage[target->Atv_stats->Character_num] +=Total_dmg;
    
}

void Cal_Dot_damage(Combat_data &data_,Enemy *target,double Dot_ratio){
    double Total_dmg = 0;
    Total_dmg += Cal_Atk_multiplier(data_,target)*data_.Damage_spilt.Main[0].Atk_ratio/100;
    Total_dmg += Cal_Hp_multiplier(data_,target)*data_.Damage_spilt.Main[0].Hp_ratio/100;
    Total_dmg += Cal_Def_multiplier(data_,target)*data_.Damage_spilt.Main[0].Def_ratio/100;
    Total_dmg = Total_dmg*Cal_Bonus_dmg_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Def_shred_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Respen_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Vul_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Toughness_multiplier(data_,target);
    
    Ally_unit[data_.num]->stats->Dot_damage[target->Atv_stats->Character_num] +=Total_dmg*Dot_ratio/100;
}
void Cal_Dot_Toughness_break_damage(Combat_data &data_,Enemy *target,double Dot_ratio){
    double Total_dmg = Level_multiplier*Dot_ratio/100;
        
    Total_dmg = Total_dmg*Cal_BreakEffect_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Def_shred_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Respen_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Vul_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Mitigation_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Toughness_multiplier(data_,target);
    Ally_unit[data_.num]->stats->Break_damage[target->Atv_stats->Character_num] +=Total_dmg;
}
void Cal_Superbreak_damage(Combat_data &data_,Enemy *target,double Superbreak_ratio){
    double Total_dmg = Level_multiplier*Superbreak_ratio/100;
    
    Total_dmg = Total_dmg*Cal_BreakEffect_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Superbreak_DamageIncrease_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Def_shred_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Respen_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Vul_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Mitigation_multiplier(data_,target);
    Ally_unit[data_.num]->stats->Superbreak_damage[target->Atv_stats->Character_num] +=Total_dmg;
}
void Cal_Additional_damage(Combat_data &data_,Enemy *target,Ratio_data Skill_mtpr){
    double Total_dmg = 0;
    if(Formula_check_mode==1){
        printf("( ( %f * %f ) + ( %f * %f ) + ( %f * %f ) *%f * %f * %f *%f *%f * %f \n)",Cal_Atk_multiplier(data_,target),Skill_mtpr.Atk_ratio/100,Cal_Hp_multiplier(data_,target),Skill_mtpr.Hp_ratio/100
        ,Cal_Def_multiplier(data_,target),Skill_mtpr.Def_ratio/100,Cal_Bonus_dmg_multiplier(data_,target),Cal_Crit_multiplier(data_,target)
        ,Cal_Def_shred_multiplier(data_,target),Cal_Respen_multiplier(data_,target),Cal_Vul_multiplier(data_,target),Cal_Toughness_multiplier(data_,target));
    }
    Total_dmg += Cal_Atk_multiplier(data_,target)*Skill_mtpr.Atk_ratio/100;
    Total_dmg += Cal_Hp_multiplier(data_,target)*Skill_mtpr.Hp_ratio/100;
    Total_dmg += Cal_Def_multiplier(data_,target)*Skill_mtpr.Def_ratio/100;
    Total_dmg = Total_dmg*Cal_Bonus_dmg_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Crit_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Def_shred_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Respen_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Vul_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Toughness_multiplier(data_,target);
    
    Ally_unit[data_.num]->stats->Normal_Damage[target->Atv_stats->Character_num] +=Total_dmg;
    // if(1){
    //     //cout<<Cal_Atk_multiplier(data_,target)<<" ";
    //     //cout<<Cal_Bonus_dmg_multiplier(data_,target)<<" ";
    //     //cout<<Cal_Crit_multiplier(data_,target)<<" ";
    //     cout<<Total_dmg<<" ";
    //     cout<<endl;
    // }
}
double Cal_Average(Enemy *target,double Total_atv){
    double temp=0;
    temp = (1*(target->stats->Total_toughness_broken_time) + 0.9*(Total_atv-target->stats->Total_toughness_broken_time))/Total_atv; 
    return temp;
}
void Cal_effect_hit_rate(Ally *ptr,double Base_chance){
    double temp=100/(Base_chance/100)/((100 - Enemy_effect_res)/100);
    temp = temp-100;
    temp-=ptr->Effect_hit_rate;
    if(temp<=0)return ;
    ptr->stats->Sub_effect_hit_rate_use = ceil(temp/3.888);
    ptr->stats->Total_substats-=ptr->stats->Sub_effect_hit_rate_use;
    ptr->stats->Separate_sub-=ptr->stats->Sub_effect_hit_rate_use;
    ptr->stats->Substats[0].second -= ptr->stats->Sub_effect_hit_rate_use;
    ptr->stats->Sub_effect_hit_rate_use *= 3.888;
    ptr->Effect_hit_rate+=ptr->stats->Sub_effect_hit_rate_use;
    return ;
}
void Cal_Speed_Needed(Ally *ptr,double Speed_Need){
    double temp = ptr->Atv_stats->Base_speed+ptr->Atv_stats->Base_speed*ptr->Atv_stats->Speed_percent/100 + ptr->Atv_stats->Flat_speed;
    temp = Speed_Need - temp;
    if(temp<=0)return;
    ptr->stats->Sub_Speed_use = ceil(temp/2.3);
    ptr->stats->Total_substats-=ptr->stats->Sub_Speed_use;
    ptr->stats->Separate_sub-=ptr->stats->Sub_Speed_use;
    ptr->stats->Substats[0].second -= ptr->stats->Sub_Speed_use;
    ptr->stats->Sub_Speed_use *= 2.3;
    ptr->Atv_stats->Flat_speed += ptr->stats->Sub_Speed_use;
    return;
}
#endif