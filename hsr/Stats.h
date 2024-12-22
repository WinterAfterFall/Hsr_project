#ifndef STATS_H
#define STATS_H
#include <bits/stdc++.h>
#include "Declaration.h"
using namespace std;
#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12







class Func{
    public:
    string Name;
    function<void(Ally *ptr)> Before_turn_func ;
    function<void(Ally *ptr)> After_turn_func ;
    function<void(Ally *ptr,Combat_data &data_)> Before_attack_func ;
    function<void(Ally *ptr,Combat_data &data_)> After_attack_func ;
    function<void(Ally *ptr,Combat_data &data_)> Buff_func ;
    function<void(Enemy* target,Ally *ptr,double Dot_ratio)> Dot_func ;
    function<void(Ally *ptr,Enemy *target,Ally *Breaker)> Toughness_break_func ;
    function<void(Ally *ptr,Enemy *target)> Enemy_hit_func ;
    function<void(Ally *ptr)> Start_game_func ;
    function<void(Ally *ptr)> Start_wave_func ;
    function<void(Ally *ptr,Enemy* target, int total_debuff)> Apply_debuff_func ;
    function<void(Ally *ptr)> Reset_func ;
    function<void(Ally *ptr,Combat_data &data_,int Hit_cnt)> Hit_func ;
};
// Action value stats for a unit (atv)
class Action_value_stats {
public:
    double Base_speed = 0.01;//*
    double Flat_speed = 0;
    double Speed_percent = 0;
    double atv ;//*
    double Max_atv;//*
    int turn_cnt = 0;
    int Character_num = 0;//*
    string Side;//*
    int priority = 0;
    string Name;
    Unit* ptr_to_unit = nullptr; //* // This will be set to point back to the unit (Ally or Enemy)
};
// Base Unit class
class Unit {
public:
    unique_ptr<Action_value_stats> Atv_stats;  // Moved Atv_stats here to be shared by both Ally and Enemy
    function<void(Unit *ptr)> Turn_func ;
    // Constructor to initialize Atv_stats and set ptr_to_unit to 'this'
    Unit() {
        Atv_stats = make_unique<Action_value_stats>();  // Create Atv_stats in Unit
        Atv_stats->ptr_to_unit = this;  // Set ptr_to_unit to this object (Unit, Ally, or Enemy)
    }
    Common_stats Atk_percent;
    Common_stats Atk_flat;
    Common_stats Hp_percent;
    Common_stats Hp_flat;
    Common_stats Def_percent;
    Common_stats Def_flat;
    Common_stats Dmg_bonus;
    Common_stats_each_element Dmg_bonus_each_element;
    Common_stats Crit_rate;
    Common_stats Crit_dam;
    Common_stats Def_shred;
    Common_stats Respen;
    Common_stats_each_element Respen_each_element;
    Common_stats Vul;
    Common_stats Break_effect;
    double Superbreak_DamageIncrease = 0;
    double Mitigation = 0;
    double Effect_hit_rate=0;
    bool Print =0;
    
    virtual ~Unit() {}  // Virtual destructor to ensure proper cleanup of derived classes
};

// Common stats for all units
// Common stats for elements



// Ally stats
class Ally_stats {
public:
    double Base_atk;//*
    double Base_hp;//*
    double Base_def;//*
    
    double Toughness_reduction = 100;
    double Max_energy = -1;//*
    double Current_energy = -1;
    double Energy_recharge = 100;
    double Ult_cost = -1;//*
    Func Light_cone;//*
    Func Char_func;//*
    Func Relic;//*
    Func Planar;//*
    int Eidolon;//*
    unordered_map<string,int> Stack;
    unordered_map<string,double> Buff_note;
    unordered_map<string,int> Buff_countdown;
    unordered_map<string,bool> Buff_check;

    vector<double> Normal_Damage;//*
    vector<double> Dot_damage;//*
    vector<double> Break_damage;//*
    vector<double> Superbreak_damage;//*
    vector<double> Max_Damage;//*
    vector<double> Max_Dot_damage;//*
    vector<double> Max_Break_damage;//*
    vector<double> Max_Superbreak_damage;//*
    double Total_damage;
    double Max = 0;
    
    vector<pair<string,int>> Substats;//*
    vector<int> Max_damage_Substats;//*
    bool Reroll_check=0;
    bool Stop_reroll=1;
    int Total_substats = 20;
    int Separate_sub = 20;
    int Current_spilt = 0;
    int Current_sub_choose =0;

    string Element_type = "";//*
    string Path = "";//*
    function<void(Ally *ptr)> Ult_func ;//*
    unique_ptr<Unit> Summon_ptr;  // 
    unique_ptr<Unit> Countdown;  // 
    int Technique = 1;
    int Ult_priority = 0;
    double Sub_effect_hit_rate_use = 0;
    double Sub_Speed_use = 0;
    function<void(Ally *ptr)> Tune_stats_func ;


};

// Enemy stats
class Enemy_stats {
public:
    
    bool Toughness_status = 1;
    double Max_toughness;   //*
    double Current_toughness;
    int Total_debuff = 0;
    unordered_map<string,int> Debuff;
    unordered_map<string,int> Debuff_time_count;
    string Target_type = "";//*
    int Bleed = 0,Bleeder = 0;
    int Burn = 0,Burner = 0;
    int Shock = 0,Shocker = 0;
    int Wind_shear = 0,Wind_shearer = 0;
    int  Wind_shear_stack = 0;
    int Freeze = 0;
    int Entanglement= 0,Entanglement_stack = 0;
    int Imprisonment = 0;
    unordered_map<string,bool> Weakness_type;
    double Energy_gen;
    double Total_toughness_broken_time =0;
    double when_toughness_broken;
};

// Ally class, derived from Unit
class Ally : public Unit {
public:
    unique_ptr<Ally_stats> stats;

    // Constructor now calls the base class constructor to initialize Atv_stats and set ptr_to_unit
    Ally() : Unit() {  // Call Unit constructor to initialize Atv_stats and set ptr_to_unit
        stats = make_unique<Ally_stats>();  // Using unique_ptr for stats
    }

    ~Ally() {}
};

// Enemy class, derived from Unit
class Enemy : public Unit {
public:
    unique_ptr<Enemy_stats> stats;

    // Constructor now calls the base class constructor to initialize Atv_stats and set ptr_to_unit
    Enemy() : Unit() {  // Call Unit constructor to initialize Atv_stats and set ptr_to_unit
        stats = make_unique<Enemy_stats>();  // Using unique_ptr for stats
    }

    ~Enemy() {}
};
#endif