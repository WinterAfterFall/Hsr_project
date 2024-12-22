#ifndef Basic_Function_H
#define Basic_Function_H
#include<bits/stdc++.h>
#include"Combat.cpp"

#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
#define K_const 10000
using std::cout ;
using std::vector;
void Basic_reset();
void Setup_enemy(int num,double speed,double energy,double Toughness,string type);
void Enemy_func(Unit *ptr);
void Summon_reset();
void Countdown_reset();

void Basic_reset(){
    
    for(int i=1;i<=Total_unit;i++){
        //flat atk
        for(auto &e:unit[i]->Atk_flat){
            if(e.first=="None"&& i<=Total_ally){
                e.second = 38+352.8;
            }else{
                e.second = 0;
            }
        }
           
        //atk percent
        for(auto &e:unit[i]->Atk_percent){
            if(e.first=="None"&& i<=Total_ally){
                e.second = 100+3.888*2;
            }else{
                e.second = 0;
            }
        }
        //Hp flat
        for(auto &e:unit[i]->Hp_flat){
            if(e.first=="None"&& i<=Total_ally){
                e.second = 76+705.6;
            }else{
                e.second = 0;
            }
        }
        //Hp percent
        for(auto &e:unit[i]->Hp_percent){
            if(e.first=="None" && i<=Total_ally){
                e.second = 100 + 3.888*2;
            }else{
                e.second = 0;
            }
        }
        //Def flat
        for(auto &e:unit[i]->Def_flat){
            if(e.first=="None"&& i<=Total_ally){
                e.second = 38;
            }else{
                e.second = 0;
            }
        }
        //Def percent
        for(auto &e:unit[i]->Def_percent){
            if(e.first=="None"&& i<=Total_ally){
                e.second = 100+4.86*2;
            }else{
                e.second = 0;
            }
        }
        //dmg bonus
        for(auto &e:unit[i]->Dmg_bonus){
            if(e.first=="None"&& i<=Total_ally){
                e.second = 100;
            }else{
                e.second = 0;
            }
        }
        //dmg bonus each element
        for(auto &e:unit[i]->Dmg_bonus_each_element){
            for(auto &f:e.second){
                f.second=0;
            }
        }
        // crit rate
        for(auto &e:unit[i]->Crit_rate){
            if(e.first=="None"&& i<=Total_ally){
                e.second = 5+2.9*2;
            }else{
                e.second = 0;
            }
        }
        //crit dam
        for(auto &e:unit[i]->Crit_dam){
            if(e.first=="None"&& i<=Total_ally){
                e.second = 50+5.8*2;
            }else{
                e.second = 0;
            }
        }
        //def shred
        for(auto &e:unit[i]->Def_shred){
                
            e.second = 0;
            
        }
        //respen
        for(auto &e:unit[i]->Respen){
            if(e.first=="None"&& i<=Total_ally){
                e.second = 100;
            }else{
                e.second = 0;
            }
        }
        //respen each element
        for(auto &e:unit[i]->Respen_each_element){
            for(auto &f:e.second){
                if(i>Total_ally&&i<=Total_ally+Total_enemy&&f.first=="None"){
                    f.second =Enemy_res[e.first]*-1;
                }else{
                f.second=0;
                }
            }
        }
        //vul
        for(auto &e:unit[i]->Vul){
            if(e.first=="None"&& i<=Total_ally){
                e.second = 100;
            }else{
                e.second = 0;
            }
        }
        //break effect
        for(auto &e:unit[i]->Break_effect){
            if(e.first=="None"&& i<=Total_ally){
                e.second = 100+5.8*2;
            }else{
                e.second = 0;
            }
        }
        //speed
        unit[i]->Atv_stats->Speed_percent=0;
        if(i<=Total_ally){
            
            unit[i]->Atv_stats->Flat_speed=2.3*2;
        }else{
            unit[i]->Atv_stats->Flat_speed=0;
        }
        unit[i]->Atv_stats->turn_cnt = 0;
        unit[i]->Atv_stats->priority = 0;
        if(i<=Total_ally){
            unit[i]->Superbreak_DamageIncrease = 100;
            unit[i]->Mitigation = 100;
            unit[i]->Effect_hit_rate = 3.888*2;
            
        }else{
            unit[i]->Superbreak_DamageIncrease = 0;
            unit[i]->Mitigation = 0;
            unit[i]->Effect_hit_rate = 0;
        }
        
        //ally edit
        auto temp = dynamic_cast<Ally*>(unit[i]->Atv_stats->ptr_to_unit);
        if(temp){
            temp->stats->Energy_recharge = 100;
            temp->stats->Toughness_reduction = 100;
            temp->stats->Current_energy = temp->stats->Max_energy/2;
            for(auto &e:temp->stats->Stack){
                e.second = 0;
            }
            for(auto &e:temp->stats->Buff_countdown){
                e.second = 0;
            }
            for(auto &e:temp->stats->Buff_note){
                e.second = 0;
            }
            for(auto &e:temp->stats->Buff_check){
                e.second = 0;
            }
        }
        //enemy edit
        auto temp_enemy = dynamic_cast<Enemy*>(unit[i]->Atv_stats->ptr_to_unit);
        if(temp_enemy){
            temp_enemy->stats->Toughness_status=1;
            temp_enemy->stats->Current_toughness=temp_enemy->stats->Max_toughness;
            temp_enemy->stats->Total_debuff=0;
            for(auto &e: temp_enemy->stats->Debuff){
                e.second = 0;
            }
            for(auto &e: temp_enemy->stats->Debuff_time_count){
                e.second = 0;
            }
            temp_enemy->stats->Bleed=0;
            temp_enemy->stats->Bleeder=0;
            temp_enemy->stats->Burn=0;
            temp_enemy->stats->Burner=0;
            temp_enemy->stats->Shock=0;
            temp_enemy->stats->Shocker=0;
            temp_enemy->stats->Wind_shear=0;
            temp_enemy->stats->Wind_shear_stack=0;
            temp_enemy->stats->Wind_shearer=0;
            temp_enemy->stats->Freeze=0;
            temp_enemy->stats->Entanglement=0;
            temp_enemy->stats->Entanglement_stack=0;
            temp_enemy->stats->Imprisonment=0;
            temp_enemy->stats->Total_toughness_broken_time =0;
            temp_enemy->stats->when_toughness_broken = 0;
            
        }

    }

}
void Summon_reset(){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Summon_ptr==nullptr)continue;
        //flat atk
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Atk_flat){
            e.second = 0;
        }
           
        //atk percent
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Atk_percent){
            e.second = 0;
        }
        //Hp flat
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Hp_flat){
            e.second = 0;
        }
        //Hp percent
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Hp_percent){
            e.second = 0;
        }
        //Def flat
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Def_flat){
            e.second = 0;
        }
        //Def percent
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Def_percent){
            e.second = 0;
        }
        //dmg bonus
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Dmg_bonus){
            e.second = 0;
        }
        //dmg bonus each element
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Dmg_bonus_each_element){
            for(auto &f:e.second){
                f.second=0;
            }
        }
        // crit rate
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Crit_rate){
            e.second = 0;
        }
        //crit dam
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Crit_dam){
            e.second = 0;
        }
        //def shred
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Def_shred){
            e.second = 0;
        }
        //respen
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Respen){
            e.second = 0;
        }
        //respen each element
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Respen_each_element){
            for(auto &f:e.second){
                f.second = 0;
            }
        }
        //vul
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Vul){
            e.second = 0;
        }
        //break effect
        for(auto &e:Ally_unit[i]->stats->Summon_ptr->Break_effect){
            e.second = 0;
        }
        //speed
        Ally_unit[i]->stats->Summon_ptr->Atv_stats->Speed_percent=0;
        Ally_unit[i]->stats->Summon_ptr->Atv_stats->Flat_speed=0;
        Ally_unit[i]->stats->Summon_ptr->Atv_stats->turn_cnt = 0;
        Ally_unit[i]->stats->Summon_ptr->Atv_stats->priority = 0;
        
        Ally_unit[i]->stats->Summon_ptr->Superbreak_DamageIncrease = 0;
        Ally_unit[i]->stats->Summon_ptr->Mitigation = 0;
        Ally_unit[i]->stats->Summon_ptr->Effect_hit_rate = 0;
        
        
    }
}
void Countdown_reset(){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->stats->Countdown==nullptr)continue;
        //flat atk
        for(auto &e:Ally_unit[i]->stats->Countdown->Atk_flat){
            e.second = 0;
        }
           
        //atk percent
        for(auto &e:Ally_unit[i]->stats->Countdown->Atk_percent){
            e.second = 0;
        }
        //Hp flat
        for(auto &e:Ally_unit[i]->stats->Countdown->Hp_flat){
            e.second = 0;
        }
        //Hp percent
        for(auto &e:Ally_unit[i]->stats->Countdown->Hp_percent){
            e.second = 0;
        }
        //Def flat
        for(auto &e:Ally_unit[i]->stats->Countdown->Def_flat){
            e.second = 0;
        }
        //Def percent
        for(auto &e:Ally_unit[i]->stats->Countdown->Def_percent){
            e.second = 0;
        }
        //dmg bonus
        for(auto &e:Ally_unit[i]->stats->Countdown->Dmg_bonus){
            e.second = 0;
        }
        //dmg bonus each element
        for(auto &e:Ally_unit[i]->stats->Countdown->Dmg_bonus_each_element){
            for(auto &f:e.second){
                f.second=0;
            }
        }
        // crit rate
        for(auto &e:Ally_unit[i]->stats->Countdown->Crit_rate){
            e.second = 0;
        }
        //crit dam
        for(auto &e:Ally_unit[i]->stats->Countdown->Crit_dam){
            e.second = 0;
        }
        //def shred
        for(auto &e:Ally_unit[i]->stats->Countdown->Def_shred){
            e.second = 0;
        }
        //respen
        for(auto &e:Ally_unit[i]->stats->Countdown->Respen){
            e.second = 0;
        }
        //respen each element
        for(auto &e:Ally_unit[i]->stats->Countdown->Respen_each_element){
            for(auto &f:e.second){
                f.second = 0;
            }
        }
        //vul
        for(auto &e:Ally_unit[i]->stats->Countdown->Vul){
            e.second = 0;
        }
        //break effect
        for(auto &e:Ally_unit[i]->stats->Countdown->Break_effect){
            e.second = 0;
        }
        //speed
        Ally_unit[i]->stats->Countdown->Atv_stats->Speed_percent=0;
        Ally_unit[i]->stats->Countdown->Atv_stats->Flat_speed=0;
        Ally_unit[i]->stats->Countdown->Atv_stats->turn_cnt = 0;
        Ally_unit[i]->stats->Countdown->Atv_stats->priority = 0;
        
        Ally_unit[i]->stats->Countdown->Superbreak_DamageIncrease = 0;
        Ally_unit[i]->stats->Countdown->Mitigation = 0;
        Ally_unit[i]->stats->Countdown->Effect_hit_rate = 0;
        
        
    }
}
void Enemy_func(Unit *ptr){
    auto target = dynamic_cast<Enemy*>(ptr);
    if(target){
    if(target->stats->Toughness_status==0){
        target->stats->Toughness_status = 1;
        target->stats->Current_toughness =  target->stats->Max_toughness;
        target->stats->Total_toughness_broken_time+=(Current_atv - target->stats->when_toughness_broken);
    }
    }
    ++target->stats->Debuff["Attack_cnt"];
    if(target->stats->Debuff["Attack_cnt"]%3==2){

        
        if(target){
        Enemy_hit(target->stats->Energy_gen,target);
        }else{
            cout<<"error from Enemy_func";
            exit(0);
        }
    }
}
void Setup_enemy(int num,double speed,double energy,double Toughness,string type){
    if(num ==0){
        cout<<"setup enemy error";
        exit(0);
    }
    Enemy_unit[num] = make_unique<Enemy>();

        Enemy_unit[num]->Atv_stats->Base_speed = speed;
        Enemy_unit[num]->stats->Energy_gen = energy;
        Enemy_unit[num]->stats->Max_toughness = Toughness;
        Enemy_unit[num]->stats->Target_type = type;
        if(type == "Main"){
            Main_Enemy_num = num;
        }

        Enemy_unit[num]->Turn_func = Enemy_func;



        for(auto &e:Enemy_weak){
                Enemy_unit[num]->stats->Weakness_type[e.first] = e.second;
        }
        for(auto &e:Enemy_res){
                Enemy_unit[num]->Respen_each_element[e.first]["None"] = e.second;
        }
        
        Enemy_unit[num]->Atv_stats->Character_num = num;
        Enemy_unit[num]->Atv_stats->Name = "Enemy_";
        Enemy_unit[num]->Atv_stats->Name += type;
        Enemy_unit[num]->Atv_stats->Side = "Enemy";
        Enemy_unit[num]->Atv_stats->ptr_to_unit = Enemy_unit[num].get();
        unit[Total_ally + num] = Enemy_unit[num]->Atv_stats->ptr_to_unit;
}

#endif