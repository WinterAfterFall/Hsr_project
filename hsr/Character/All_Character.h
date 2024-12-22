#ifndef All_Character_H
#define All_Character_H
#include".\Abundance\All_Abundance_char.h"
#include".\Destruction\All_Destruction_char.h"
#include".\Erudition\All_Erudition_char.h"
#include".\Harmony\All_Harmony_char.h"
#include".\Nihility\All_Nihility_char.h"
#include".\Preservation\All_Preservation_char.h"
#include".\Remembrance\All_Remembrance_char.h"
#include".\The_Hunt\All_The_Hunt_char.h"
void Set_Technique(Ally *ptr,int tech){
    ptr->stats->Technique = tech;
}
void Timing_print(Ally *ptr){
    ptr->Print = 1;
}
#endif
/*
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Resetn(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Ult_func(Ally *ptr);//*
    void Before_turn(Ally *ptr);
    void After_turn(Ally *ptr);
    void Before_attack(Ally *ptr, Combat_data &data_);
    void After_attack(Ally *ptr, Combat_data &data_);
    void Start_game(Ally *ptr);
    void Start_wave(Ally *ptr);
    void Buff_func(Ally *ptr, Combat_data &data_);
    void Dot_func(Enemy *target, Ally *ptr, double Dot_ratio);
    void Toughness_break_func(Ally *ptr, Enemy *target, int num);
    void Enemy_hit_func(Ally *ptr, Enemy *target);    
    void Apply_debuff_func(Ally *ptr, Enemy *target, int total_debuff);
    void Hit_func(Ally *ptr, int Hit_cnt);
    */