#ifndef Define_H
#define Define_H
#include <bits/stdc++.h>

#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
using std::cout ;
using std::vector;
using std::string;
using std::unordered_map;
using std::queue;
using std::pair;
using std::function;
using std::unique_ptr;
using std::make_unique;
// Stats
class Unit;
class Ally_stats;
class Enemy_stats;
class Action_value_stats;
class Func;
class Ally;
class Enemy;
class Combat_data;
class Ratio_data;
class Hit_spilt;

typedef unordered_map<string,double> Common_stats; 
/*  None 
    Basic_Attack
    Skill
    Ultimate 
    Dot 
    Fua 
    Summon 
    Break_dmg 
    Super_break 
*/
typedef unordered_map<string,Common_stats> Common_stats_each_element;

//cal
double Cal_Atk_multiplier(Combat_data &data_,Enemy *target);
double Cal_Hp_multiplier(Combat_data &data_,Enemy *target);
double Cal_Def_multiplier(Combat_data &data_,Enemy *target);
double Cal_Bonus_dmg_multiplier(Combat_data &data_,Enemy *target);
double Cal_Crit_multiplier(Combat_data &data_,Enemy *target);
double Cal_Def_shred_multiplier(Combat_data &data_,Enemy *target);
double Cal_Respen_multiplier(Combat_data &data_,Enemy *target);
double Cal_Vul_multiplier(Combat_data &data_,Enemy *target);
double Cal_BreakEffect_multiplier(Combat_data &data_,Enemy *target);
double Cal_Toughness_multiplier(Combat_data &data_,Enemy *target);
double Cal_Superbreak_DamageIncrease_multiplier(Combat_data &data_,Enemy *target);
double Cal_Mitigation_multiplier(Combat_data &data_,Enemy *target);


void Cal_Toughness_reduction(Combat_data &data_,Enemy* target,double Toughness_reduce);
void Cal_Damage(Combat_data &data_,Enemy *target,Ratio_data Skill_mtpr);
void Cal_Additional_damage(Combat_data &data_,Enemy *target,Ratio_data Skill_mtpr);
void Cal_Break_damage(Combat_data &data_,Enemy *target,double &Constant);
void Cal_Freeze_damage(Combat_data &data_,Enemy *target);
void Cal_Superbreak_damage(Combat_data &data_,Enemy *target,double Superbreak_ratio);
void Cal_Dot_damage(Combat_data &data_,Enemy *target,double Dot_ratio);
void Cal_Dot_Toughness_break_damage(Combat_data &data_,Enemy *target,double Dot_ratio);
double Cal_Average(Enemy *target);
//atv
void Update_Max_atv(Action_value_stats *ptr);
void atv_reset(Action_value_stats *ptr);
void Action_forward(Action_value_stats *ptr,double fwd);
void All_Action_forward(double fwd,int Start,int End);
void All_atv_reset();

void Speed_Buff(Action_value_stats *ptr,double spd_percent ,double flat_spd );
void Increase_energy(Ally_stats *stats_ptr,double Energy);
void Increase_energy(Ally_stats *stats_ptr,double Energy_percent,double Flat_energy);
void Find_turn();
void Atv_fix(double Atv_reduce);
//combat
void Toughness_break(Combat_data &data_,Enemy* target);
void Deal_damage();
void All_ult_check();
void Take_action();
void Buff(Combat_data &data_);
void Before_turn();
void After_turn();
void Before_attack(Combat_data &data_);
void After_attack(Combat_data &data_);
void When_Toughness_break(int num,Enemy *target);
void Attack(Combat_data &data_);
bool Ult_use_check(Ally *ptr);
void Dot_trigger(double Dot_ratio,Enemy *target);
void Attack_hit(Combat_data &data_,int Hit_cnt);
void Enemy_hit(double energy,Enemy *target);
void Superbreak_trigger(Combat_data &data_, double Superbreak_ratio);
void Apply_debuff(Ally *ptr,Enemy* target, int total_debuff);
void Skill_point(int p);
#endif
