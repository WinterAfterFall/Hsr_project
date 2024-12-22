#ifndef COMBAT_H
#define COMBAT_H
#include<bits/stdc++.h>
#include"Calculate_damage.cpp"
#include"Print.h"
#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
#define K_const 10000


bool Ult_use_check(Ally *ptr){
    if(ptr->stats->Ult_cost<=ptr->stats->Current_energy){
        ptr->stats->Current_energy = ptr->stats->Current_energy - ptr->stats->Ult_cost;
        Increase_energy(ptr->stats.get(),5);
        return true;
    }
    return false;
}

void Attack(Combat_data &data_){
    int Hit_total = 0;
    for(int i=0, sz1 = data_.Damage_spilt.Main.size(),sz2 = data_.Damage_spilt.Adjacent.size(),sz3 = data_.Damage_spilt.Other.size();i<sz1;i++){
        
        if(i<sz1)++Hit_total;
        if(i<sz2 &&Total_enemy>1)++Hit_total;
        if(i<sz2 &&Total_enemy>2)++Hit_total;
        if(i<sz3 &&Total_enemy>3)++Hit_total;
        if(i<sz3 &&Total_enemy>4)++Hit_total;
        Attack_hit(data_,Hit_total);
        for(int j=1;j<=Total_enemy;j++){

            if(Enemy_unit[j]->stats->Target_type=="Main"){
            Cal_Damage(data_,Enemy_unit[j].get(),data_.Damage_spilt.Main[i]);
            Cal_Toughness_reduction(data_,Enemy_unit[j].get(),data_.Damage_spilt.Main[i].Toughness_ratio);
            }
            
            if(i<sz2 && Enemy_unit[j]->stats->Target_type=="Adjacent"){
            Cal_Damage(data_,Enemy_unit[j].get(),data_.Damage_spilt.Adjacent[i]);
            Cal_Toughness_reduction(data_,Enemy_unit[j].get(),data_.Damage_spilt.Adjacent[i].Toughness_ratio);
            }
            
            if(i<sz3 && Enemy_unit[j]->stats->Target_type=="Other"){
            Cal_Damage(data_,Enemy_unit[j].get(),data_.Damage_spilt.Other[i]);
            Cal_Toughness_reduction(data_,Enemy_unit[j].get(),data_.Damage_spilt.Other[i].Toughness_ratio);
            }
            
            
        }
        
    }
}
void Before_turn(){
    Combat_data temp;
    if(turn->Side=="Enemy"){
        Dot_trigger(100,Enemy_unit[turn->Character_num].get());
        if(Enemy_unit[turn->Character_num]->stats->Entanglement != 0){
            temp = Combat_data();
            temp.num = Enemy_unit[turn->Character_num]->stats->Entanglement;
            temp.Damage_type.push_back("Entanglement");
            temp.Damage_element = "Quantum";

            temp.Action_type.first = "Attack";
            temp.Action_type.second = "Entanglement";
            temp.Target_type = "Single_target";
            double Const = 0.6*Enemy_unit[turn->Character_num]->stats->Entanglement_stack;
            Cal_Break_damage(temp,Enemy_unit[turn->Character_num].get(),Const);
        }
        if(Enemy_unit[turn->Character_num]->stats->Freeze != 0){
            temp = Combat_data();
            temp.num = Enemy_unit[turn->Character_num]->stats->Freeze;
            temp.Damage_type.push_back("Freeze");
            temp.Damage_element = "Ice";

            temp.Action_type.first = "Attack";
            temp.Action_type.second = "Freeze";
            temp.Target_type = "Single_target";
            Cal_Freeze_damage(temp,Enemy_unit[turn->Character_num].get());
            Action_forward(Enemy_unit[turn->Character_num]->Atv_stats.get(),-50);
            Turn_Skip=1;
        }
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Char_func.Before_turn_func)
        Ally_unit[i]->stats->Char_func.Before_turn_func(Ally_unit[i].get());

        if(Ally_unit[i]->stats->Light_cone.Before_turn_func)
        Ally_unit[i]->stats->Light_cone.Before_turn_func(Ally_unit[i].get());

        if(Ally_unit[i]->stats->Relic.Before_turn_func)
        Ally_unit[i]->stats->Relic.Before_turn_func(Ally_unit[i].get());
        
        if(Ally_unit[i]->stats->Planar.Before_turn_func)
        Ally_unit[i]->stats->Planar.Before_turn_func(Ally_unit[i].get());
    }
}
void After_turn(){
    if(turn->Side=="Enemy"){
        if(Enemy_unit[turn->Character_num]->stats->Entanglement != 0){
           Enemy_unit[turn->Character_num]->stats->Entanglement = 0;
           Enemy_unit[turn->Character_num]->stats->Entanglement_stack = 0;
           --Enemy_unit[turn->Character_num]->stats->Total_debuff;
        }
        if(Enemy_unit[turn->Character_num]->stats->Freeze != 0){
            Enemy_unit[turn->Character_num]->stats->Freeze = 0;
           --Enemy_unit[turn->Character_num]->stats->Total_debuff;
        }
        if(Enemy_unit[turn->Character_num]->stats->Imprisonment != 0){
           Enemy_unit[turn->Character_num]->stats->Imprisonment = 0;
           Speed_Buff(Enemy_unit[turn->Character_num]->Atv_stats.get(),10,0);
           --Enemy_unit[turn->Character_num]->stats->Total_debuff;
        }
        if(Enemy_unit[turn->Character_num]->stats->Bleed > 0){
           Enemy_unit[turn->Character_num]->stats->Bleed--;
           if(Enemy_unit[turn->Character_num]->stats->Bleed==0){
            Enemy_unit[turn->Character_num]->stats->Bleeder = 0;
            --Enemy_unit[turn->Character_num]->stats->Total_debuff;
           }
        }
        if(Enemy_unit[turn->Character_num]->stats->Burn > 0){
           Enemy_unit[turn->Character_num]->stats->Burn--;
           if(Enemy_unit[turn->Character_num]->stats->Burn==0){
            Enemy_unit[turn->Character_num]->stats->Burner = 0;
            --Enemy_unit[turn->Character_num]->stats->Total_debuff;
           }
        }
        if(Enemy_unit[turn->Character_num]->stats->Shock > 0){
           Enemy_unit[turn->Character_num]->stats->Shock--;
           if(Enemy_unit[turn->Character_num]->stats->Shock==0){
            Enemy_unit[turn->Character_num]->stats->Shocker = 0;
            --Enemy_unit[turn->Character_num]->stats->Total_debuff;
           }
        }
        if(Enemy_unit[turn->Character_num]->stats->Wind_shear > 0){
           Enemy_unit[turn->Character_num]->stats->Wind_shear--;
           if(Enemy_unit[turn->Character_num]->stats->Wind_shear==0){
            Enemy_unit[turn->Character_num]->stats->Wind_shearer = 0;
            Enemy_unit[turn->Character_num]->stats->Wind_shear_stack = 0;
            --Enemy_unit[turn->Character_num]->stats->Total_debuff;
           }
        }
    }
    for(int i=1;i<=Total_ally;i++){
        
        if(Ally_unit[i]->stats->Char_func.After_turn_func)
        Ally_unit[i]->stats->Char_func.After_turn_func(Ally_unit[i].get());

        if(Ally_unit[i]->stats->Light_cone.After_turn_func)
        Ally_unit[i]->stats->Light_cone.After_turn_func(Ally_unit[i].get());

        if(Ally_unit[i]->stats->Relic.After_turn_func)
        Ally_unit[i]->stats->Relic.After_turn_func(Ally_unit[i].get());
        
        if(Ally_unit[i]->stats->Planar.After_turn_func)
        Ally_unit[i]->stats->Planar.After_turn_func(Ally_unit[i].get());
    }
}
void Buff(Combat_data &data_){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Char_func.Buff_func)
        Ally_unit[i]->stats->Char_func.Buff_func(Ally_unit[i].get(),data_);

        if(Ally_unit[i]->stats->Light_cone.Buff_func)
        Ally_unit[i]->stats->Light_cone.Buff_func(Ally_unit[i].get(),data_);

        if(Ally_unit[i]->stats->Relic.Buff_func)
        Ally_unit[i]->stats->Relic.Buff_func(Ally_unit[i].get(),data_);
        
        if(Ally_unit[i]->stats->Planar.Buff_func)
        Ally_unit[i]->stats->Planar.Buff_func(Ally_unit[i].get(),data_);
    }
}
void Before_attack(Combat_data &data_){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Char_func.Before_attack_func)
        Ally_unit[i]->stats->Char_func.Before_attack_func(Ally_unit[i].get(),data_);

        if(Ally_unit[i]->stats->Light_cone.Before_attack_func)
        Ally_unit[i]->stats->Light_cone.Before_attack_func(Ally_unit[i].get(),data_);

        if(Ally_unit[i]->stats->Relic.Before_attack_func)
        Ally_unit[i]->stats->Relic.Before_attack_func(Ally_unit[i].get(),data_);
        
        if(Ally_unit[i]->stats->Planar.Before_attack_func)
        Ally_unit[i]->stats->Planar.Before_attack_func(Ally_unit[i].get(),data_);
    }
}
void After_attack(Combat_data &data_){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Char_func.After_attack_func)
        Ally_unit[i]->stats->Char_func.After_attack_func(Ally_unit[i].get(),data_);

        if(Ally_unit[i]->stats->Light_cone.After_attack_func)
        Ally_unit[i]->stats->Light_cone.After_attack_func(Ally_unit[i].get(),data_);

        if(Ally_unit[i]->stats->Relic.After_attack_func)
        Ally_unit[i]->stats->Relic.After_attack_func(Ally_unit[i].get(),data_);
        
        if(Ally_unit[i]->stats->Planar.After_attack_func)
        Ally_unit[i]->stats->Planar.After_attack_func(Ally_unit[i].get(),data_);
    }
}
void When_Toughness_break(Ally *Breaker,Enemy *target){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Char_func.Toughness_break_func)
        Ally_unit[i]->stats->Char_func.Toughness_break_func(Ally_unit[i].get(),target,Breaker);

        if(Ally_unit[i]->stats->Light_cone.Toughness_break_func)
        Ally_unit[i]->stats->Light_cone.Toughness_break_func(Ally_unit[i].get(),target,Breaker);

        if(Ally_unit[i]->stats->Relic.Toughness_break_func)
        Ally_unit[i]->stats->Relic.Toughness_break_func(Ally_unit[i].get(),target,Breaker);
        
        if(Ally_unit[i]->stats->Planar.Toughness_break_func)
        Ally_unit[i]->stats->Planar.Toughness_break_func(Ally_unit[i].get(),target,Breaker);
    }
}
void Enemy_hit(double energy,Enemy *target){
    for(int i=1;i<=Total_ally;i++){
            Increase_energy(Ally_unit[i]->stats.get(),energy);
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Char_func.Enemy_hit_func)
        Ally_unit[i]->stats->Char_func.Enemy_hit_func(Ally_unit[i].get(),target);

        if(Ally_unit[i]->stats->Light_cone.Enemy_hit_func)
        Ally_unit[i]->stats->Light_cone.Enemy_hit_func(Ally_unit[i].get(),target);

        if(Ally_unit[i]->stats->Relic.Enemy_hit_func)
        Ally_unit[i]->stats->Relic.Enemy_hit_func(Ally_unit[i].get(),target);
        
        if(Ally_unit[i]->stats->Planar.Enemy_hit_func)
        Ally_unit[i]->stats->Planar.Enemy_hit_func(Ally_unit[i].get(),target);
    }
}
void Deal_damage(){
    while(!Action_bar.empty()){
        Combat_data temp = Action_bar.front();
        if(temp.Action_type.first =="Attack"){
            Before_attack(temp);
            
            Attack(temp);
            
            if(temp.Turn_reset ==1){
                atv_reset(turn);
            }
            After_attack(temp);
            


        }else if(temp.Action_type.first =="Buff"){
            if(temp.Turn_reset ==1){
                atv_reset(turn);
            }
            Buff(temp);
            
        }
        Action_bar.pop();
    }
    if(turn->Side=="Enemy"){
        atv_reset(turn);
    }
}
void Take_action(){
    
    ++(turn->turn_cnt);
    Ult_After_Turn = 0;
    After_Turn_Check = 0;
    Before_turn();
    All_ult_check();
    Print();
    if(Turn_Skip==0){
        
        turn->ptr_to_unit->Turn_func(turn->ptr_to_unit);
        
        Deal_damage();
        
    }
    Ult_After_Turn = 1;
    
    
    All_ult_check();
    After_Turn_Check = 1;
    After_turn();

}
void All_ult_check(){
    ult_priority = 0;
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Ult_priority==ult_priority)Ally_unit[i]->stats->Ult_func(Ally_unit[i].get());
    }
    ++ult_priority;
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Ult_priority==ult_priority)Ally_unit[i]->stats->Ult_func(Ally_unit[i].get());
    }
    ++ult_priority;
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Ult_priority==ult_priority)Ally_unit[i]->stats->Ult_func(Ally_unit[i].get());
    }
}
void Skill_point(int p){
    sp+=p;
    if(sp>Max_sp){
        sp = Max_sp;
    }
    return ;
}
void Attack_hit(Combat_data &data_,int Hit_cnt){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Char_func.Hit_func)
        Ally_unit[i]->stats->Char_func.Hit_func(Ally_unit[i].get(),data_,Hit_cnt);

        if(Ally_unit[i]->stats->Light_cone.Hit_func)
        Ally_unit[i]->stats->Light_cone.Hit_func(Ally_unit[i].get(),data_,Hit_cnt);

        if(Ally_unit[i]->stats->Relic.Hit_func)
        Ally_unit[i]->stats->Relic.Hit_func(Ally_unit[i].get(),data_,Hit_cnt);

        if(Ally_unit[i]->stats->Planar.Hit_func)
        Ally_unit[i]->stats->Planar.Hit_func(Ally_unit[i].get(),data_,Hit_cnt);
    }
}
void Apply_debuff(Ally *ptr,Enemy* target, int total_debuff){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Char_func.Apply_debuff_func)
        Ally_unit[i]->stats->Char_func.Apply_debuff_func(Ally_unit[i].get(),target,total_debuff);

        if(Ally_unit[i]->stats->Light_cone.Apply_debuff_func)
        Ally_unit[i]->stats->Light_cone.Apply_debuff_func(Ally_unit[i].get(),target,total_debuff);
        
        if(Ally_unit[i]->stats->Relic.Apply_debuff_func)
        Ally_unit[i]->stats->Relic.Apply_debuff_func(Ally_unit[i].get(),target,total_debuff);
        
        if(Ally_unit[i]->stats->Planar.Apply_debuff_func)
        Ally_unit[i]->stats->Planar.Apply_debuff_func(Ally_unit[i].get(),target,total_debuff);
    }
}
void Superbreak_trigger(Combat_data &data_, double Superbreak_ratio){
    Combat_data data_2;
    data_2.num = data_.num;
    data_2.Damage_type.push_back("Break_dmg");
    data_2.Damage_type.push_back("Super_break");
    data_2.Damage_element = data_.Damage_element;
    data_2.Action_type.first = "Attack";
    data_2.Action_type.second = "Super_break";
    data_2.Target_type = data_.Target_type;
    
    for(int i=1;i<=Total_enemy;i++){
        double toughness_reduce=0;
        if(Enemy_unit[i]->stats->Target_type=="Main"){
            for(int j=0,sz=data_.Damage_spilt.Main.size();i<sz;i++){
                toughness_reduce+=data_.Damage_spilt.Main[j].Toughness_ratio;
            }
            
        }
            
        if(Enemy_unit[i]->stats->Target_type=="Adjacent"){
            for(int j=0,sz=data_.Damage_spilt.Adjacent.size();i<sz;i++){
                toughness_reduce+=data_.Damage_spilt.Adjacent[j].Toughness_ratio;
            }
            
        }
            
        if(Enemy_unit[i]->stats->Target_type=="Other"){
            for(int j=0,sz=data_.Damage_spilt.Other.size();i<sz;i++){
                toughness_reduce+=data_.Damage_spilt.Other[j].Toughness_ratio;
            }
            
        }
        toughness_reduce = toughness_reduce*Ally_unit[data_.num]->stats->Toughness_reduction/100;
        if(Enemy_unit[i]->stats->Current_toughness+toughness_reduce<=0){
        Cal_Superbreak_damage(data_2,Enemy_unit[i].get(),Superbreak_ratio*toughness_reduce/10);
        }else{
        Cal_Superbreak_damage(data_2,Enemy_unit[i].get(),Superbreak_ratio*(-1)*Enemy_unit[i]->stats->Current_toughness/10);
        }
    }
}

void Dot_trigger(double Dot_ratio,Enemy *target){
    Combat_data data_;
    data_.Damage_type.push_back("Dot");
    
    data_.Action_type.first = "Attack";
    data_.Action_type.second = "Dot";
    data_.Target_type = "Single_target";
    
    if(target->stats->Bleed > 0){
        data_.num=target->stats->Bleeder;
        data_.Damage_element = "Physical";
        data_.Damage_type.push_back("Bleed");
        Cal_Dot_Toughness_break_damage(data_,target,Dot_ratio*2*(0.5+target->stats->Max_toughness/40));
    }
    if(target->stats->Burn > 0){
        data_.num=target->stats->Burner;
        data_.Damage_element = "Fire";
        data_.Damage_type.resize(0);
        data_.Damage_type.push_back("Burn");
        Cal_Dot_Toughness_break_damage(data_,target,Dot_ratio*1);
    }
    if(target->stats->Shock > 0){
        data_.num=target->stats->Shocker;
        data_.Damage_element = "Lightning";
        data_.Damage_type.resize(0);
        data_.Damage_type.push_back("Shock");
        Cal_Dot_Toughness_break_damage(data_,target,Dot_ratio*2);
    }
    if(target->stats->Wind_shear > 0){
        data_.num=target->stats->Wind_shearer;
        data_.Damage_type.resize(0);
        data_.Damage_element = "Wind";
        data_.Damage_type.push_back("Wind_shear");
        Cal_Dot_Toughness_break_damage(data_,target,Dot_ratio*1*target->stats->Wind_shear_stack);
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Char_func.Dot_func)
        Ally_unit[i]->stats->Char_func.Dot_func(target,Ally_unit[i].get(),Dot_ratio);

        if(Ally_unit[i]->stats->Light_cone.Dot_func)
        Ally_unit[i]->stats->Light_cone.Dot_func(target,Ally_unit[i].get(),Dot_ratio);

        if(Ally_unit[i]->stats->Relic.Dot_func)
        Ally_unit[i]->stats->Relic.Dot_func(target,Ally_unit[i].get(),Dot_ratio);
        
        if(Ally_unit[i]->stats->Planar.Dot_func)
        Ally_unit[i]->stats->Planar.Dot_func(target,Ally_unit[i].get(),Dot_ratio);
    }
}
void Toughness_break(Combat_data &data_,Enemy* target){
    double Constant = 0;
    Combat_data data_2;
    data_2.num = data_.num;
    data_2.Damage_type.push_back("Break_dmg");
    data_2.Damage_element = data_.Damage_element;
    ++target->stats->Total_debuff;
    Apply_debuff(Ally_unit[data_.num].get(),target,1);

    data_2.Action_type.first = "Attack";
    data_2.Action_type.second = "Break_dmg";
    data_2.Target_type = "Single_target";
    if(data_.Damage_element=="Physical"){
        Action_forward(target->Atv_stats.get(),-25);
        target->stats->Bleed = 2;
        target->stats->Bleeder =data_.num;
        Constant=2;

    }else if(data_.Damage_element=="Fire"){
        Action_forward(target->Atv_stats.get(),-25);
        target->stats->Burn = 2;
        target->stats->Burner =data_.num;
        Constant=2;

    }else if(data_.Damage_element=="Ice"){
        Action_forward(target->Atv_stats.get(),-25);
        target->stats->Freeze = data_.num;
        Constant=1;

    }else if(data_.Damage_element=="Lightning"){
        Action_forward(target->Atv_stats.get(),-25);
        target->stats->Shock = 2;
        target->stats->Shocker =data_.num;
        Constant=1;

    }else if(data_.Damage_element=="Wind"){
        Action_forward(target->Atv_stats.get(),-25);
        target->stats->Wind_shear = 2;
        target->stats->Wind_shearer =data_.num;
        if(target->stats->Wind_shear_stack>=3){
            target->stats->Wind_shear_stack=5;
        }else { target->stats->Wind_shear_stack=3;}
        Constant=1.5;

    }else if(data_.Damage_element=="Quantum"){
        Action_forward(target->Atv_stats.get(),-20*Cal_BreakEffect_multiplier(data_,target));
        target->stats->Entanglement = data_.num;
        target->stats->Entanglement_stack = 0;
        Constant=0.5;

    }else if(data_.Damage_element=="Imaginary"){
        Action_forward(target->Atv_stats.get(),-30*Cal_BreakEffect_multiplier(data_,target));
        Speed_Buff(target->Atv_stats.get(),-10,0);
        target->stats->Imprisonment = data_.num;
        Constant=0.5;
    }
        
    When_Toughness_break(Ally_unit[data_.num].get(),target);
    Cal_Break_damage(data_2,target,Constant);
    target->stats->Toughness_status=0;
    
}
#endif