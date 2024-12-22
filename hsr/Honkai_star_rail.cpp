/*
b แทนค่าว่าอัลติพร้อมไหม
*/
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12

int formula_check = 0;//check สมการ
int Action_check  = 0;//check ลำดับตัวละคร
int break_multilplier_average_mode = 2;
int Swap_After_break=0;//1 = สมจริง 2 คือจำลอง
int Target_check = 1; //1 5 6
int sp=3,max_wave=1;//1450
double wave[3]={1506.85,450,450};

int mem = 4,Enemy_mem = 2 , Enemy_total = 2 , Other_mem=5;
int Total_mem = mem + Enemy_mem + Other_mem;

double Res_enemy[7]={100,100,100,100,100,100,100};
bool Weakness_element[7]={1,1,1,1,1,1,1};
int Speed_Substats[4]={3,8,8,8};
int Technique_check[4]={1,0,0,0};

int crit_overload=0;//crit ล้น
//just parameter
int j=0; //set wave แรกที่ 1 || ปล 0 คือ 1
int turn = 0,turn_check=0;
double current = 0;
int Swap_check=0;
double k = 10000.0 ;
double Total_break_dmg=0;
double Total_Dot_dmg=0;
double Level_multiplier = 3767.5533;

// stats ตัวละคร


int relic_check=0;
int crit_rate_sub = 3;
int crit_dam_sub = 0;
int speed_sub = 2; 
int ult_after = 0;
double Max_toughness = 160;
double Max_toughness_multiplier = 4.5;


int Robin_num=0, LC_Robin_check = 0 , LC_Robin_0_stack = 0 , Robin_ult_time = 0 , Robin_ult_atkbuff=1186,Robin_tech_check=1,Robin_ult_hit=0;//1350
int Seele_num=0;
int Topaz_num=0 , Numby_num=0;
int Aventurine_num=0;
int Sw_num=0;
int Fuxuan_num=0;
int Hanabi_num=0;
int Gallagher_num=4; bool Gallagher_normal_atk_buff = 0;
int Ruan_mei_num = 0,Ruan_mei_ult_time=0;
int Firefly_num = 1 ,Firefly_ult_num = 7;
int MC_img_num=3,MC_img_ult_time=0;
int Asta_num=0;
int Pela_num = 2;

// main character
int Main_enemy_num=5,Second_enemy_num=6;

int Main_dps_num =Firefly_num; //dps หลัก

int Spector_num=Gallagher_num; //ตัวที่เราพิจารณา

int Force_break=1;

// flatatk atk flathp hp flatdef def critrate critdam  defres vun be 
// normal skill ult fua dot Break SuperBreak Talent
double dmg[7][9][DMG_CAL];
double Respen[7][9][8];
double Dmg_bonus[7][9][8];
vector<struct chr> unt(Total_mem+1);
vector<struct Ally_status> unt_Ally(mem+1);
vector<struct Enemy_status> unt_Enemy(Enemy_mem+1);
//phy fire ice lightning wind qt img
//setting
struct chr {
    int num;
    double  spd = 0.01, atv;
    pair<double,double> buffspd;
    int cnt;
    
    
};
struct Combat {
    pair<double,double> Atk_ratio;
    pair<double,double> Hp_ratio;
    pair<double,double> Def_ratio;
    pair<double,double> toughness_reduction;
    int Dmg_type;
    
    int num;
};
struct Ally_status {
    int base_atk;
    int base_hp;
    int base_def;
    double A2 ,A4, A6;
    double E1,E2,E4,E6;
    double   en, mxen,er;
    int break_cnt;
    int element;
    
    int Asta_ult_time;

    int Attack_en;
    int Toughness_reduction_check;
    pair<int,int> LC_check; 
    double toughness_dmg_multiplier = 1;
    
};
struct Enemy_status {
    double  toughness;
    int debuff;
    int Turn_count;
    int Enemy_call_amount;
    
    int sw_skill_debuff_time , sw_ult_time , sw_talent_stack;
    int aventurine_ult_time;
    int Topaz_talent_check;

    int Ruan_mei_ult_debuff;

    int Gallagher_ult_debuff;
    

    //BREAK
    int toughness_break_check;
    double atv_at_break,all_toughness_break_time;
    pair<int,int> pyhsical_dot,wind_dot,lightning_dot,fire_dot;
    int wind_dot_stack;
    int ice_break;
    int Quantum_break,Quantum_stack;
    int Img_break;
};

struct ChrCompare {
    bool operator()(const chr &l, const chr &r) const {

        return l.atv > r.atv;
    }
};
priority_queue<chr, vector<chr>, ChrCompare> pq;

queue<Combat> Action_queue;

void st(struct chr &a) {
    
    a.atv = k / (a.spd + a.spd * a.buffspd.F + a.buffspd.S);
    
}
int mx_atv(struct chr &a) {
    return (k / (a.spd + a.spd * a.buffspd.F + a.buffspd.S));    
}
void energy(int a,double b){
    unt_Ally[a].en += b * unt_Ally[a].er;
    return ;
}
int Use_ult(int a){
    int c=0;

    if(unt_Ally[a].en>=unt_Ally[a].mxen){
        unt_Ally[a].en=5*unt_Ally[a].er;
        c=1;

    }
    return c;


}
double forward(struct chr &a,double fwd) {
    double speed = a.spd + a.spd * a.buffspd.F + a.buffspd.S;
    if(a.num==0){
        a.atv=1e6;
        return 1e6;
    }
    if (a.atv <= k / speed * fwd) {
        a.atv = 0;
        return 0;
    } else {
        a.atv = a.atv - (k / speed * fwd);
        return a.atv - (k / speed * fwd);
    }
}

double Speed_Buff(struct chr &a,double buff1 ,double buff2 ) {
    double ans = a.atv / (k / (a.spd + a.spd * a.buffspd.F + a.buffspd.S)) * (k / (a.spd + a.spd * (a.buffspd.F + buff1) + (a.buffspd.S + buff2)));
    a.buffspd.F = a.buffspd.F + buff1;
    a.buffspd.S = a.buffspd.S + buff2;
    a.atv=ans;
    return ans;
}
//stats
void stats(int a,int LC_star,int LC_chocie,double Energy_recharge){
    if(a==0)return;
    //relic sub stats;
    dmg[a][0][1]+=19*2;
    dmg[a][0][2]+=3.888*2;
    dmg[a][0][7]+=2.9*2;
    dmg[a][0][8]+=5.8*2;
    dmg[a][0][11]+=5.8*2;
    dmg[a][0][3]+=38*2;
    dmg[a][0][4]+=3.8*2;
    dmg[a][0][5]+=19*2;
    dmg[a][0][6]+=4.8*2;
    unt[a].buffspd.S+=2.3*2;
    unt_Ally[a].er = Energy_recharge;
    unt_Ally[a].en = unt_Ally[a].mxen/2; 
    if(Weakness_element[unt_Ally[a].element-1]==1){
        unt_Ally[a].Toughness_reduction_check = 1;
    }

    unt[a].num=a;
    unt_Ally[a].LC_check.F = LC_star;
    unt_Ally[a].LC_check.S = LC_chocie;

    if(a==Firefly_num){
        unt_Ally[a].base_atk = 524;
        unt_Ally[a].base_hp = 815;
        unt_Ally[a].base_def = 776;

        //base stats
        dmg[a][0][7]+=5;
        dmg[a][0][8]+=50;
        //trace
        dmg[a][0][11]+=37.3;
        unt[Firefly_num].buffspd.S+=5;
        
        //relic stats
        //head
        dmg[a][0][3]+=705;
        //hand
        dmg[a][0][1]+=352;
        //body
        dmg[a][0][2]+=43.2;
        //boot
        unt[Firefly_num].buffspd.S+=25;
        //orb;
        dmg[a][0][2]+=43.2;
        //rope
        dmg[a][0][11]+=64.8;

        //relic set
        dmg[a][0][11]+=16;
        dmg[a][6][9]+=10;
        dmg[a][7][9]+=15;

        //planar
        unt[a].buffspd.F+=0.06;
        dmg[a][0][11]+=40;
        //Substats    
        unt[Firefly_num].buffspd.S+=2.3*Speed_Substats[a-1];
        dmg[a][0][11]+=(20-Speed_Substats[a-1])*5.8;
        if(LC_star==5){
            if(LC_chocie==0){
               unt_Ally[a].base_atk += 476;
                unt_Ally[a].base_hp += 1164;
                unt_Ally[a].base_def += 529;
                dmg[a][0][11]+=60;
                dmg[a][6][10]+=24;
            }
            if(LC_chocie==1){
                unt_Ally[a].base_atk += 529;
                unt_Ally[a].base_hp += 1058;
                unt_Ally[a].base_def += 397; 
                dmg[a][0][2]+=64;
            }

        }
        if(LC_star==4){
            
        }
    }
    if(a==Ruan_mei_num){
        unt_Ally[a].base_atk = 659;
        unt_Ally[a].base_hp = 1086;
        unt_Ally[a].base_def = 485;

        //base stats
        dmg[a][0][7]+=5;
        dmg[a][0][8]+=50;
        //trace
        dmg[a][0][11]+=37.3;
        unt[a].buffspd.S+=5;
        dmg[a][0][6]+=22.5;
        
        //relic stats
        //head
        dmg[a][0][3]+=705;
        //hand
        dmg[a][0][1]+=352;
        //body
        dmg[a][0][4]+=43.2;
        //boot
        unt[a].buffspd.S+=25;
        //orb;
        dmg[a][0][6]+=54;
        //rope

        //relic set
        dmg[a][0][11]+=32;

        //planar
        
        //Substats    
        unt[a].buffspd.S+=2.3*Speed_Substats[a-1];
        dmg[a][0][11]+=(20-Speed_Substats[a-1])*5.8;
        if(LC_star==5){
            
        }
        if(LC_star==4){
            if(LC_chocie==0){
                dmg[a][0][11]+=56;
                unt_Ally[a].Attack_en+=8;
                unt_Ally[a].base_atk += 423;
                unt_Ally[a].base_hp += 953;
                unt_Ally[a].base_def += 397; 
            }
        }
    }
    if(a==Gallagher_num){
        unt_Ally[a].base_atk = 529;
        unt_Ally[a].base_hp = 1305;
        unt_Ally[a].base_def = 441; 

        //base stats
        dmg[a][0][7]+=5;
        dmg[a][0][8]+=50;
        //trace
        dmg[a][0][11]+=13.3;
        dmg[a][0][4]+=18;
        // extra trace and eidolon
        dmg[a][0][11]+=20;
        unt_Ally[a].toughness_dmg_multiplier+=0.2;
        //relic stats
        //head
        dmg[a][0][3]+=705;
        //hand
        dmg[a][0][1]+=352;
        //body

        //boot
        unt[a].buffspd.S+=25;
        //orb;
        dmg[a][0][4]+=43.2;
        //rope

        //relic set
        dmg[a][0][11]+=32;

        //planar
        dmg[a][0][11]+=36;
        
        //Substats    
        unt[a].buffspd.S+=2.3*Speed_Substats[a-1];
        dmg[a][0][11]+=(20-Speed_Substats[a-1])*5.8;
        if(LC_star==5){
            
        }
        if(LC_star==4){
            if(LC_chocie==0){
                dmg[a][0][11]+=48;
                unt_Ally[a].base_atk += 423;
                unt_Ally[a].base_hp += 1058;
                unt_Ally[a].base_def += 331; 
            }
        }
    }
    if(a==MC_img_num){
        unt_Ally[a].base_atk = 446;
        unt_Ally[a].base_hp = 1087;
        unt_Ally[a].base_def = 679; 

        //base stats
        dmg[a][0][7]+=5;
        dmg[a][0][8]+=50;
        //trace
        dmg[a][0][11]+=37.3;
        Dmg_bonus[a][0][7]+=14.4;
        // extra trace and eidolon
        
        //relic stats
        //head
        dmg[a][0][3]+=705;
        //hand
        dmg[a][0][1]+=352;
        //body
        dmg[a][0][4]+=43.2;
        //boot
        unt[a].buffspd.S+=25;
        //orb;
        dmg[a][0][4]+=43.2;
        //rope

        //relic set
        dmg[a][0][11]+=16;
        dmg[a][6][9]+=10;
        dmg[a][7][9]+=15;

        //planar
        dmg[a][0][11]+=36;
        
        //Substats    
        unt[a].buffspd.S+=2.3*Speed_Substats[a-1];
        dmg[a][0][11]+=(20-Speed_Substats[a-1])*5.8;
        if(LC_star==5){
            
        }
        if(LC_star==4){
            if(LC_chocie==0){
                dmg[a][0][11]+=56;
                unt_Ally[a].Attack_en+=8;
                unt_Ally[a].base_atk += 423;
                unt_Ally[a].base_hp += 953;
                unt_Ally[a].base_def += 397; 
            }
        }
    }
    

}
void Before_turn(){
    if(turn==Ruan_mei_num){
        energy(Ruan_mei_num,5);
    }
}
void After_turn(){
    if(turn==Firefly_num && unt[Firefly_ult_num].spd!=70){
        forward(unt[Firefly_num], 0.25);
    }
}
//function character
//phy fire ice lightning wind qt img
void Break_dmg(int a,double Const_K,int Target){
    double def_multi,res_multi,vun_multi,break_effect_multi;
    double K_weakness=0;
    if(unt_Enemy[Target-4].toughness>0){
        K_weakness=0.9;
    }else{
        K_weakness=1;
    }
    if(dmg[a][0][9] + dmg[a][6][9] + dmg[Target][0][9] + dmg[Target][6][9]>=100){
        def_multi=100;
    }else{def_multi=dmg[a][0][9] + dmg[a][6][9] + dmg[Target][0][9] + dmg[Target][6][9];}
    def_multi = ((100-def_multi)/100*1150)/((100-def_multi)/100*1150+1000);
    res_multi = Respen[a][0][0] + Respen[a][6][0] + Respen[Target][0][0] + Respen[Target][6][0];
    res_multi += Respen[a][0][unt_Ally[a].element] + Respen[a][6][unt_Ally[a].element] + Respen[Target][0][unt_Ally[a].element] + Respen[Target][6][unt_Ally[a].element];
    vun_multi = dmg[a][0][10] + dmg[a][6][10] + dmg[Target][0][10] + dmg[Target][6][10];
    break_effect_multi = dmg[a][0][11] + dmg[a][6][11] + dmg[Target][0][11] + dmg[Target][6][11];

    if(a == Spector_num && Action_check == 0 && break_multilplier_average_mode!=1 &&(Target_check==1||Target_check==Target)){
        printf("%lf*%lf*%lf*%lf*(%lf+Res_substats)/100*(100+%lf+Vun_substats)/100*(100+%lf+Break_effect_substats)/100*%lf+",Const_K,Max_toughness_multiplier,Level_multiplier,1-def_multi,res_multi,vun_multi,break_effect_multi,K_weakness);
        if(formula_check==1){
            printf("\n");
        }
    }
}
void Toughness_Break(int a,int b){
    if(Force_break!=0){
        a=Force_break;
    }
    
    unt_Ally[a].break_cnt++;
    unt_Enemy[b-4].atv_at_break = current;
    Swap_check=1;
    double K_multiplier=0;

    double def_multi,res_multi,vun_multi,break_effect_multi;
    if(dmg[a][0][6] + dmg[a][6][6] + dmg[b][0][6] + dmg[b][6][6]>=100){
        def_multi=100;
    }else{def_multi=dmg[a][0][6] + dmg[a][6][6] + dmg[b][0][6] + dmg[b][6][6];}
    def_multi = ((100-def_multi)/100*1150)/((100-def_multi)/100*1150+1000);
    res_multi = dmg[a][0][7] + dmg[a][6][7] + dmg[b][0][7] + dmg[b][6][7];
    vun_multi = dmg[a][0][8] + dmg[a][6][8] + dmg[b][0][8] + dmg[b][6][8];
    break_effect_multi = dmg[a][0][9] + dmg[a][6][9] + dmg[b][0][9] + dmg[b][6][9];

    if(unt_Ally[a].element==1){
        forward(unt[b],-0.25);
        unt_Enemy[b-4].pyhsical_dot.F=a;
        unt_Enemy[b-4].pyhsical_dot.S=2;
        K_multiplier=2;

    }else if(unt_Ally[a].element==2){
        forward(unt[b],-0.25);
        unt_Enemy[b-4].fire_dot.F=a;
        unt_Enemy[b-4].fire_dot.S=2;
        K_multiplier=2;

    }else if(unt_Ally[a].element==3){
        forward(unt[b],-0.25);
        unt_Enemy[b-4].ice_break=a;
        K_multiplier=1;

    }else if(unt_Ally[a].element==4){
        forward(unt[b],-0.25);
        unt_Enemy[b-4].lightning_dot.F=a;
        unt_Enemy[b-4].lightning_dot.S=2;
        K_multiplier=1;

    }else if(unt_Ally[a].element==5){
        forward(unt[b],-0.25);
        unt_Enemy[b-4].wind_dot.F=a;
        unt_Enemy[b-4].wind_dot.S=2;
        if(unt_Enemy[b-4].wind_dot_stack==3){
            unt_Enemy[b-4].wind_dot_stack=5;
        }else {unt_Enemy[b-4].wind_dot_stack=3;}
        K_multiplier=1.5;
        
    }else if(unt_Ally[a].element==6){
        forward(unt[b],-0.2*(100+break_effect_multi)/100);
        unt_Enemy[b-4].Quantum_break=a;
        K_multiplier=0.5;

    }else if(unt_Ally[a].element==7){
        forward(unt[b],-0.3*(100+break_effect_multi)/100);
        Speed_Buff(unt[b] , -0.1 , 0);
        unt_Enemy[b-4].Img_break=a;
        K_multiplier=0.5;

    }
    if(a==Spector_num && Action_check==0 && break_multilplier_average_mode!=1 &&(Target_check==1||Target_check==b)){
        printf("%lf*%lf*%lf*%lf*(100+%lf+Res_substats)/100*(100+%lf+Vun_substats)/100*(100+%lf+Break_effect_substats)/100*0.9+",K_multiplier,Max_toughness_multiplier,Level_multiplier,1-def_multi,res_multi,vun_multi,break_effect_multi);
        if(formula_check==1){
            printf("\n");
        }
    }
    if(MC_img_num!=0){
        forward(unt[b],-0.3);
        energy(MC_img_num,11);
    }
    if(Ruan_mei_num!=0){
        Break_dmg(Ruan_mei_num,1.2,b);
        if(Ruan_mei_ult_time>unt[Ruan_mei_num].cnt){
            unt_Enemy[b-4].Ruan_mei_ult_debuff=1;
           }
        }
}

void Robin_ult(){
    Robin_ult_time=1;
    dmg[0][0][1]+=Robin_ult_atkbuff;
    dmg[0][4][5]+=25;
    if(Action_check==0 && formula_check==1){printf("         Robin ult start \n");
        }
        if(Action_check==1){cout<<"         Robin ult start "<<endl;}

    for(int i=1;i<=4;i++){
        if(i==Robin_num)continue;
        if(unt[i].num==0)continue;
        pq.push(unt[i]);
    }
    unt[Robin_num].atv=10000/90;


}
void All_ult(){
    
    if(Firefly_num!=0 && unt[Firefly_num].atv>0&& Use_ult(Firefly_num)==1){
        unt[Firefly_ult_num].spd = 70;
        st(unt[Firefly_ult_num]);
        unt_Ally[Firefly_num].toughness_dmg_multiplier += 0.5;
        Speed_Buff(unt[Firefly_num],0,60);
        dmg[Firefly_num][6][8]+=20;
        forward(unt[Firefly_num],1);
    }
    if(Ruan_mei_num!=0 && unt[Ruan_mei_num].atv>unt[Main_dps_num].atv&& Use_ult(Ruan_mei_num)==1){
        for(int i=1;i<=4;i++){
            dmg[i][0][7]+=25;
        }
        Ruan_mei_ult_time=unt[Ruan_mei_num].cnt+2;
        
    }
    if(Gallagher_num!=0 &&turn==Gallagher_num&&ult_after==1&& Use_ult(Gallagher_num)==1){
    forward(unt[Gallagher_num], 1);
    for(int i=1;i<=Enemy_mem;i++){
        if(unt_Enemy[i].Gallagher_ult_debuff<=unt[i+4].cnt){
        dmg[i+4][6][8]+=13.2;
        }
        unt_Enemy[i].Gallagher_ult_debuff = unt[i+4].cnt+3;
    }
    Action_queue.push({{165,165},{0,0},{0,0},{20,20},3,Gallagher_num});
    }
    if(MC_img_num!=0 && Use_ult(MC_img_num)==1){
        MC_img_ult_time = 3;
        for(int i=1;i<=4;i++){
            dmg[i][0][9]+=33;
        }
    }
    
}
void Super_Break(int a,double Const_K,int Target){
    Const_K=Level_multiplier*Const_K;
    double K_weakness=0;
    double dmg_multi,def_multi,res_multi,vun_multi,break_effect_multi;
    
    if(unt_Enemy[Target-4].toughness>0){
        K_weakness=0.9;
    }else{
        K_weakness=1;
    }

    if(dmg[a][0][6] + dmg[a][6][6] + dmg[Target][0][6] + dmg[Target][6][6] + dmg[a][7][6] + dmg[Target][7][6]>=100){
        def_multi=100;
    }else{def_multi=dmg[a][0][6] + dmg[a][6][6] + dmg[Target][0][6] + dmg[Target][6][6] + dmg[a][7][6] + dmg[Target][7][6];}

    dmg_multi = dmg[a][6][3] + dmg[Target][6][3] + dmg[a][7][3] + dmg[Target][7][3];
    def_multi = ((100-def_multi)/100*1150)/((100-def_multi)/100*1150+1000);
    res_multi = dmg[a][0][7] + dmg[a][6][7] + dmg[Target][0][7] + dmg[Target][6][7] + dmg[a][7][7] + dmg[Target][7][7];
    vun_multi = dmg[a][0][8] + dmg[a][6][8] + dmg[Target][0][8] + dmg[Target][6][8] + dmg[a][7][8] + dmg[Target][7][8];
    break_effect_multi = dmg[a][0][9] + dmg[a][6][9] + dmg[Target][0][9] + dmg[Target][6][9] + dmg[a][7][9] + dmg[Target][7][9];

    if(a==Spector_num && Action_check==0 && break_multilplier_average_mode!=1 &&(Target_check==1||Target_check==Target)){
        printf("(%lf+Super_break_substats)*(%lf+100)/100*%lf*(100+%lf+Res_substats)/100*(100+%lf+Vun_substats)/100*(100+%lf+Break_effect_substats)/100*%lf+",Const_K,dmg_multi,1-def_multi,res_multi,vun_multi,break_effect_multi,K_weakness);
        if(formula_check==1){
            printf("\n");
        }
    }
}
void Break_side_effect_damage_cal(int a,double Const_K){
    
    int Target;
    double K_weakness=0;
    double def_multi,res_multi,vun_multi,break_effect_multi;
    if(turn!=Main_enemy_num && turn!= Second_enemy_num){
        Target = Main_enemy_num;
    }else{
        Target = turn;
    }
    
    if(unt_Enemy[Target-4].toughness>0){
        K_weakness=0.9;
    }else{
        K_weakness=1;
    }

    if(dmg[a][0][6] + dmg[a][6][6] + dmg[Target][0][6] + dmg[Target][6][6]>=100){
        def_multi=100;
    }else{def_multi=dmg[a][0][6] + dmg[a][6][6] + dmg[Target][0][6] + dmg[Target][6][6];}
    def_multi = ((100-def_multi)/100*1150)/((100-def_multi)/100*1150+1000);
    res_multi = dmg[a][0][7] + dmg[a][6][7] + dmg[Target][0][7] + dmg[Target][6][7];
    vun_multi = dmg[a][0][8] + dmg[a][6][8] + dmg[Target][0][8] + dmg[Target][6][8];
    break_effect_multi = dmg[a][0][9] + dmg[a][6][9] + dmg[Target][0][9] + dmg[Target][6][9];
    
    if(a==Spector_num && Action_check==0 && break_multilplier_average_mode!=1 &&(Target_check==1||Target_check==Target)){
        printf("%lf*%lf*(100+%lf+Res_substats)/100*(100+%lf+Vun_substats)/100*(100+%lf+Break_effect_substats)/100*%lf+",Const_K,1-def_multi,res_multi,vun_multi,break_effect_multi,K_weakness);
        if(formula_check==1){
            printf("\n");
        }
    }
}
void Dot(double Dot_ratio){
    int Target;
    
    if(turn!=Main_enemy_num && turn!= Second_enemy_num){
        Target = Main_enemy_num;
    }else{
        Target = turn;
    }
    if(unt_Enemy[Target-4].pyhsical_dot.S != 0 && unt_Enemy[Target-4].pyhsical_dot.F == Spector_num){

        Break_side_effect_damage_cal(unt_Enemy[Target-4].pyhsical_dot.F,2*Level_multiplier*Max_toughness_multiplier*Dot_ratio);
    }
    if(unt_Enemy[Target-4].fire_dot.S != 0 && unt_Enemy[Target-4].fire_dot.F == Spector_num){
        
        Break_side_effect_damage_cal(unt_Enemy[Target-4].fire_dot.F,Level_multiplier*Dot_ratio);
    }
    if(unt_Enemy[Target-4].wind_dot.S != 0 && unt_Enemy[Target-4].wind_dot.F == Spector_num){
        
        Break_side_effect_damage_cal(unt_Enemy[Target-4].wind_dot.F,2*Level_multiplier*unt_Enemy[Target-4].wind_dot_stack*Dot_ratio);
    }
    if(unt_Enemy[Target-4].lightning_dot.S != 0 && unt_Enemy[Target-4].lightning_dot.F == Spector_num){
        
        Break_side_effect_damage_cal(unt_Enemy[Target-4].wind_dot.F,2*Level_multiplier*Dot_ratio);
    }
}
int Start_enemy_turn(){
    bool Return_num=0;
    
    //Turn Skip           
    if(unt_Enemy[turn-4].ice_break != 0){
        unt_Enemy[turn-4].ice_break=0;
        Break_side_effect_damage_cal(unt_Enemy[turn-4].wind_dot.S,Level_multiplier);
        forward(unt[turn],-0.5);
        Return_num=1;
    }else if(unt_Enemy[turn-4].Ruan_mei_ult_debuff != 0){
        unt_Enemy[turn-4].Ruan_mei_ult_debuff=0;
        forward(unt[turn],-0.1-(0.2*(dmg[Ruan_mei_num][0][9]+dmg[turn][0][9])));
        Break_dmg(Ruan_mei_num,0.5,turn);
        Return_num=1;
        //return 1; 
    }

    if(unt_Enemy[turn-4].Quantum_break != 0 && unt_Enemy[turn-4].Quantum_break == Spector_num){
        
        Break_side_effect_damage_cal(unt_Enemy[turn-4].Quantum_break,3*Level_multiplier*Max_toughness_multiplier);
    }
    
    //effect
            
    if(unt_Enemy[turn-4].pyhsical_dot.S != 0){
        unt_Enemy[turn-4].pyhsical_dot.S--;
    }
    if(unt_Enemy[turn-4].fire_dot.S != 0){
        unt_Enemy[turn-4].fire_dot.S--;
    }
    if(unt_Enemy[turn-4].wind_dot.S != 0){
        unt_Enemy[turn-4].wind_dot.S--;
    }
    if(unt_Enemy[turn-4].lightning_dot.S != 0){
        unt_Enemy[turn-4].lightning_dot.S--;
    }
    if(unt_Enemy[turn-4].Quantum_break != 0){
        unt_Enemy[turn-4].Quantum_break =0;
    }
    if(unt_Enemy[turn-4].Img_break != 0){
        unt_Enemy[turn-4].Img_break=0;
        Speed_Buff(unt[turn] , 0.1 , 0);
    }
    
    
    return Return_num;
}
void Before_Attack(pair<double,double> &Atk_ratio,pair<double,double> &Hp_ratio,pair<double,double> &Def_ratio,pair<double,double> &toughness_dmg,int dmg_type,int a){
    if(MC_img_num!=0){
        for(int i=1;i<=4;i++){
            dmg[i][0][9]-=unt_Ally[MC_img_num].E4;
        }
        unt_Ally[MC_img_num].E4=dmg[MC_img_num][0][9]*0.15;
        for(int i=1;i<=4;i++){
            dmg[i][0][9]+=unt_Ally[MC_img_num].E4;
        }
    }
    if(a==Firefly_num){
        dmg[Firefly_num][0][9] -= unt_Ally[Firefly_num].A6*0.8;
        unt_Ally[Firefly_num].A6 = (int)(((unt_Ally[Firefly_num].base_atk*(100+dmg[Firefly_num][0][2]+dmg[Firefly_num][2][2])/100+dmg[Firefly_num][0][1]+dmg[Firefly_num][2][1])-1800)/10);
        dmg[Firefly_num][0][9] += unt_Ally[Firefly_num].A6*0.8;
    }
    if(a==Firefly_num && dmg[Firefly_num][0][9]+dmg[Firefly_num][2][9]>=360){
        unt_Ally[Firefly_num].A4 = 0.5;
    }else if(a==Firefly_num && dmg[Firefly_num][0][9]+dmg[Firefly_num][2][9]>=200){
        unt_Ally[Firefly_num].A4 = 0.35;
    }
    if(a==Firefly_num && unt[Firefly_ult_num].spd == 70){
        Atk_ratio.F+=(dmg[Firefly_num][0][9]+dmg[Firefly_num][2][9])*0.2;
        Atk_ratio.S+=(dmg[Firefly_num][0][9]+dmg[Firefly_num][2][9])*0.1;
    }
}
void Attack(pair<double,double> &Atk_ratio,pair<double,double> &Hp_ratio,pair<double,double> &Def_ratio,pair<double,double> &toughness_dmg,int dmg_type,int a){
    
    if(Spector_num==a&&Action_check==0&&(Target_check==Main_enemy_num||Target_check==1)&&break_multilplier_average_mode!=2){
    int multiplier_number=2;
    double def_multi;
    //atk
    printf("( (%d*(100+%lf+Atk_substats)/(100)+%lf)",unt_Ally[a].base_atk, dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Main_enemy_num][0][multiplier_number] + dmg[Main_enemy_num][dmg_type][multiplier_number] , dmg[a][0][1] + dmg[a][dmg_type][1] + dmg[Main_enemy_num][0][1] + dmg[Main_enemy_num][dmg_type][1]);

    //skill
    printf("*((%lf+Atk_ratio_substats)/(100))",Atk_ratio.F);

    //hp
    printf("+(%d*(100+%lf+Hp_substats)/(100)+%lf)",unt_Ally[a].base_hp, dmg[a][0][11] + dmg[a][dmg_type][11] + dmg[Main_enemy_num][0][11] + dmg[Main_enemy_num][dmg_type][11] , dmg[a][0][10] + dmg[a][dmg_type][10] + dmg[Main_enemy_num][0][10] + dmg[Main_enemy_num][dmg_type][10]);

    //skill hp
    printf("*((%lf+Hp_ratio_substats)/(100))",Hp_ratio.F);

    //def 
    printf("+(%d*(100+%lf+Def_substats)/(100)+%lf)",unt_Ally[a].base_def, dmg[a][0][13] + dmg[a][dmg_type][13] + dmg[Main_enemy_num][0][13] + dmg[Main_enemy_num][dmg_type][13] , dmg[a][0][12] + dmg[a][dmg_type][12] + dmg[Main_enemy_num][0][12] + dmg[Main_enemy_num][dmg_type][12]);

    //skill def
    printf("*((%lf+Def_ratio_substats)/(100)) )",Def_ratio.F);

    //dmg
    multiplier_number++;
    printf("*(100+Dmg_substats+%lf)/(100)", dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Main_enemy_num][0][multiplier_number] + dmg[Main_enemy_num][dmg_type][multiplier_number] );

    if(crit_overload==0){

    //crit rate
    multiplier_number++; 
    printf("*( 1+(%lf+(Crit_rate_substats))/(100)", dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Main_enemy_num][0][multiplier_number] + dmg[Main_enemy_num][dmg_type][multiplier_number] );
    //crit dam
    multiplier_number++;
    printf("*(%lf+(Crit_dam_substats))/(100) )", dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Main_enemy_num][0][multiplier_number] + dmg[Main_enemy_num][dmg_type][multiplier_number] );

    }else{

    //crit rate
    multiplier_number++;
    printf("*( 1+(%lf)/(100)", dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Main_enemy_num][0][multiplier_number] + dmg[Main_enemy_num][dmg_type][multiplier_number] );
    //crit dam
    multiplier_number++;
    printf("*(%lf+(Crit_dam_substats))/(100) )", dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Main_enemy_num][0][multiplier_number] + dmg[Main_enemy_num][dmg_type][multiplier_number] );

    }
    //def
    multiplier_number++;
    if(dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Main_enemy_num][0][multiplier_number] + dmg[Main_enemy_num][dmg_type][multiplier_number]>=100){
        def_multi=100;
    }else{def_multi=dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Main_enemy_num][0][multiplier_number] + dmg[Main_enemy_num][dmg_type][multiplier_number];}
    printf("*(1-%lf)", ((100-def_multi)/100*1150)/((100-def_multi)/100*1150+1000) );

    //res
    multiplier_number++;
    printf("*(%lf+%lf+Res_substats)/(100)",Res_enemy[unt_Ally[a].element-1],dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Main_enemy_num][0][multiplier_number] + dmg[Main_enemy_num][dmg_type][multiplier_number] );

    //vun
    multiplier_number++;
    printf("*(100+%lf+Vun_substats)/(100)", dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Main_enemy_num][0][multiplier_number] + dmg[Main_enemy_num][dmg_type][multiplier_number] );

    
    //weakness
    if(unt_Enemy[Main_enemy_num-4].toughness>0 && break_multilplier_average_mode==0){
        printf("*(0.9)");
    }
    printf("+");
    if(formula_check==1){
    printf("\n");}
    }

    if(unt_Ally[a].Toughness_reduction_check==1){
        unt_Enemy[Main_enemy_num-4].toughness-=toughness_dmg.F*unt_Ally[a].toughness_dmg_multiplier;
        if(unt_Enemy[Main_enemy_num-4].toughness<=0 && unt_Enemy[Main_enemy_num-4].toughness_break_check==0){
            unt_Enemy[Main_enemy_num-4].toughness_break_check=1;
            Toughness_Break(a,Main_enemy_num);
        }
    }

    //เป้ารอง
    if(Spector_num==a && Action_check == 0 && toughness_dmg.S!=0&&(Target_check==Second_enemy_num||Target_check==1)&&break_multilplier_average_mode!=2){
    int multiplier_number=2;
    double def_multi;
    //atk
    printf("( (%d*(100+%lf+Atk_substats)/(100)+%lf)",unt_Ally[a].base_atk, dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Second_enemy_num][0][multiplier_number] + dmg[Second_enemy_num][dmg_type][multiplier_number] , dmg[a][0][1] + dmg[a][dmg_type][1] + dmg[Second_enemy_num][0][1] + dmg[Second_enemy_num][dmg_type][1]);

    //skill
    printf("*((%lf+Atk_ratio_substats)/(100))",Atk_ratio.S);

    //hp
    printf("+(%d*(100+%lf+Hp_substats)/(100)+%lf)",unt_Ally[a].base_hp, dmg[a][0][11] + dmg[a][dmg_type][11] + dmg[Second_enemy_num][0][11] + dmg[Second_enemy_num][dmg_type][11] , dmg[a][0][10] + dmg[a][dmg_type][10] + dmg[Second_enemy_num][0][10] + dmg[Second_enemy_num][dmg_type][10]);

    //skill hp
    printf("*((%lf+Hp_ratio_substats)/(100))",Hp_ratio.S);

    //def 
    printf("+(%d*(100+%lf+Def_substats)/(100)+%lf)",unt_Ally[a].base_def, dmg[a][0][13] + dmg[a][dmg_type][13] + dmg[Second_enemy_num][0][13] + dmg[Second_enemy_num][dmg_type][13] , dmg[a][0][12] + dmg[a][dmg_type][12] + dmg[Second_enemy_num][0][12] + dmg[Second_enemy_num][dmg_type][12]);

    //skill def
    printf("*((%lf+Def_ratio_substats)/(100)) )",Def_ratio.S);

    //dmg
    multiplier_number++;
    printf("*(100+Dmg_substats+%lf)/(100)", dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Second_enemy_num][0][multiplier_number] + dmg[Second_enemy_num][dmg_type][multiplier_number] );

    if(crit_overload==0){

    //crit rate
    multiplier_number++; 
    printf("*( 1+(%lf+(Crit_rate_substats))/(100)", dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Second_enemy_num][0][multiplier_number] + dmg[Second_enemy_num][dmg_type][multiplier_number] );
    //crit dam
    multiplier_number++;
    printf("*(%lf+(Crit_dam_substats))/(100) )", dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Second_enemy_num][0][multiplier_number] + dmg[Second_enemy_num][dmg_type][multiplier_number] );

    }else{

    //crit rate
    multiplier_number++;
    printf("*( 1+(%lf)/(100)", dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Second_enemy_num][0][multiplier_number] + dmg[Second_enemy_num][dmg_type][multiplier_number] );
    //crit dam
    multiplier_number++;
    printf("*(%lf+(Crit_dam_substats))/(100) )", dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Second_enemy_num][0][multiplier_number] + dmg[Second_enemy_num][dmg_type][multiplier_number] );

    }
    //def
    multiplier_number++;
    if(dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Second_enemy_num][0][multiplier_number] + dmg[Second_enemy_num][dmg_type][multiplier_number]>=100){
        def_multi=100;
    }else{def_multi=dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Second_enemy_num][0][multiplier_number] + dmg[Second_enemy_num][dmg_type][multiplier_number];}
    printf("*(1-%lf)", ((100-def_multi)/100*1150)/((100-def_multi)/100*1150+1000) );

    //res
    multiplier_number++;
    printf("*(%lf+%lf+Res_substats)/(100)",Res_enemy[unt_Ally[a].element-1],dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Second_enemy_num][0][multiplier_number] + dmg[Second_enemy_num][dmg_type][multiplier_number] );

    //vun
    multiplier_number++;
    printf("*(100+%lf+Vun_substats)/(100)", dmg[a][0][multiplier_number] + dmg[a][dmg_type][multiplier_number] + dmg[Second_enemy_num][0][multiplier_number] + dmg[Second_enemy_num][dmg_type][multiplier_number] );

    
    //weakness
    if(unt_Enemy[Second_enemy_num-4].toughness>0 && break_multilplier_average_mode==0){
        printf("*(0.9)");
    }
    printf("+");
    if(formula_check==1){
    printf("\n");}
    }

    if(unt_Ally[a].Toughness_reduction_check==1&&toughness_dmg.S!=0){
        unt_Enemy[Second_enemy_num-4].toughness-=toughness_dmg.S*unt_Ally[a].toughness_dmg_multiplier;
        if(unt_Enemy[Second_enemy_num-4].toughness<=0 && unt_Enemy[Second_enemy_num-4].toughness_break_check==0){
            unt_Enemy[Second_enemy_num-4].toughness_break_check=1;
            Toughness_Break(a,Second_enemy_num);
        }
    }
}
void After_Attack(pair<double,double> &Atk_ratio,pair<double,double> &Hp_ratio,pair<double,double> &Def_ratio,pair<double,double> &toughness_dmg,int dmg_type,int a){
    double Super_break_K_main=0,Super_break_K_second=0;
    if(a==Firefly_num &&Firefly_num!=0 && unt[Firefly_ult_num].spd==70){
        
        if(unt_Enemy[Main_enemy_num-4].toughness<=0){
            if(unt_Enemy[Main_enemy_num-4].toughness+toughness_dmg.F*unt_Ally[Firefly_num].toughness_dmg_multiplier<=0){
                Super_break_K_main = toughness_dmg.F*unt_Ally[Firefly_num].toughness_dmg_multiplier/10;
            }else{
                Super_break_K_main = (-1*unt_Enemy[Main_enemy_num-4].toughness/10);
            }
            Super_Break(a,unt_Ally[Firefly_num].A4*Super_break_K_main,Main_enemy_num);
        }
        if(unt_Enemy[Second_enemy_num-4].toughness<=0){
            if(unt_Enemy[Second_enemy_num-4].toughness+toughness_dmg.S*unt_Ally[Firefly_num].toughness_dmg_multiplier<=0){
                Super_break_K_second = toughness_dmg.S*unt_Ally[Firefly_num].toughness_dmg_multiplier/10;
            }else{
                Super_break_K_second = (-1*unt_Enemy[Second_enemy_num-4].toughness/10);
            }
            Super_Break(a,unt_Ally[Firefly_num].A4*Super_break_K_second,Second_enemy_num);
        }
    }
    if(MC_img_num!=0&&MC_img_ult_time > 0){
        if(unt_Enemy[Main_enemy_num-4].toughness<=0){
            if(unt_Enemy[Main_enemy_num-4].toughness+toughness_dmg.F*unt_Ally[a].toughness_dmg_multiplier<=0){
                Super_break_K_main = toughness_dmg.F*unt_Ally[a].toughness_dmg_multiplier/10;
            }else{
                Super_break_K_main = (-1*unt_Enemy[Main_enemy_num-4].toughness/10);
            }
            Super_Break(a,1.5*Super_break_K_main,Main_enemy_num);
        }
        if(unt_Enemy[Second_enemy_num-4].toughness<=0){
            if(unt_Enemy[Second_enemy_num-4].toughness+toughness_dmg.S*unt_Ally[a].toughness_dmg_multiplier<=0){
                Super_break_K_second = toughness_dmg.S*unt_Ally[a].toughness_dmg_multiplier/10;
            }else{
                Super_break_K_second = (-1*unt_Enemy[Second_enemy_num-4].toughness/10);
            }
            Super_Break(a,1.2*Super_break_K_second,Second_enemy_num);
        }
    }
     //Action_queue.push({{-1,-1},-1,{-1,-1},unt[Robin_num]});
    
}
void Deal_damage(){
    
    
    while(!Action_queue.empty()){
        if(Action_queue.front().toughness_reduction.F==-1){
            All_ult();
        }else{
        if(Action_queue.front().toughness_reduction.F!=0){
            Before_Attack(Action_queue.front().Atk_ratio,Action_queue.front().Hp_ratio,Action_queue.front().Def_ratio,Action_queue.front().toughness_reduction,Action_queue.front().Dmg_type,Action_queue.front().num);
        }
            Attack(Action_queue.front().Atk_ratio,Action_queue.front().Hp_ratio,Action_queue.front().Def_ratio,Action_queue.front().toughness_reduction,Action_queue.front().Dmg_type,Action_queue.front().num);
        if(Action_queue.front().toughness_reduction.F!=0){
            After_Attack(Action_queue.front().Atk_ratio,Action_queue.front().Hp_ratio,Action_queue.front().Def_ratio,Action_queue.front().toughness_reduction,Action_queue.front().Dmg_type,Action_queue.front().num);
        }
        }
        if(Action_queue.front().Dmg_type==1||Action_queue.front().Dmg_type==2){
            st(unt[turn]);
            turn_check=1;
            After_turn();
        }
        Action_queue.pop();

    }
    if(turn_check==0){
        turn_check=1;
        st(unt[turn]);
        After_turn();
    }
    if(Swap_check==1){
        if(Swap_After_break==1){
            swap(Main_enemy_num,Second_enemy_num);
        }
        if(Swap_After_break==2){
            
            swap(unt_Enemy[Main_enemy_num-4].toughness,unt_Enemy[Second_enemy_num-4].toughness);
            swap(unt[Main_enemy_num].atv,unt[Second_enemy_num].atv);
            swap(unt_Enemy[Main_enemy_num-4].toughness_break_check,unt_Enemy[Second_enemy_num-4].toughness_break_check);
            
        }    

        Swap_check=0;
    }
}    
void Robin(int a){

}

void Ruanmei(int a){
    if(unt[a].cnt==Ruan_mei_ult_time){
        for(int i=1;i<=4;i++){
            dmg[i][0][7]-=25;
        }
    }
    if(unt[a].cnt%3==0){
        sp--;
        energy(Ruan_mei_num,30);
    }else{
        sp++;
        Action_queue.push({{100,0},{0,0},{0,0},{10,0},2,Ruan_mei_num});
        energy(Ruan_mei_num,20+unt_Ally[Ruan_mei_num].Attack_en);
    }


}
void Firefly(int a){
    sp--;
    if(unt[Firefly_ult_num].spd==70){
        Action_queue.push({{200,100},{0,0},{0,0},{20,10},2,Firefly_num});
    }else{
        Action_queue.push({{200,0},{0,0},{0,0},{20,0},2,Firefly_num});
        unt_Ally[Firefly_num].en+=unt_Ally[Firefly_num].mxen*0.6;
    }
    

}
void MC_img(int a){
    MC_img_ult_time--;
    if(MC_img_ult_time==0){
        for(int i=1;i<=4;i++){
            dmg[i][0][9]-=33;
        }
        if(Action_check==1){
            cout<<"-------------------------------- Ult MC img end"<<endl;
        }
    }
    if(sp>=2){
        sp--;
        if(unt_Ally[a].A4==0){
            Action_queue.push({{55*4,55*3},{0,0},{0,0},{35,15},2,a});
            sp++;
        }else{
            Action_queue.push({{55*4,55*3},{0,0},{0,0},{25,15},2,a});
        }
        energy(a,30+unt_Ally[a].Attack_en);
    }else{
        sp++;
        Action_queue.push({{110,0},{0,0},{0,0},{10,0},1,a});
        energy(a,20+unt_Ally[a].Attack_en);
    }
}

void Gallagher(int a){

    if(unt[a].cnt%4==1&&unt[a].cnt!=1){
        sp--;
        energy(Gallagher_num,30);
    }else{
        sp++;
        if(Gallagher_normal_atk_buff==1){
            Gallagher_normal_atk_buff=0;
            Action_queue.push({{275,0},{0,0},{0,0},{10,0},1,Gallagher_num});
        }else{
            Action_queue.push({{110,0},{0,0},{0,0},{10,0},1,Gallagher_num});
        }
        
        energy(Gallagher_num,20+unt_Ally[Gallagher_num].Attack_en);
    }

}
void Enemy_Call(int a){
    if(Enemy_total+a>=5){
        Enemy_total=5;
    }else{
        Enemy_total+=3;
    }
}
void Enemy(int a){
    Dot(1);
    Start_enemy_turn();
    bool Turn_skip;
    Turn_skip=Start_enemy_turn();
    if(Turn_skip==1){
        return;
    }
    if(unt_Enemy[turn-4].toughness<=0){
        unt_Enemy[turn-4].toughness=Max_toughness;
        unt_Enemy[turn-4].toughness_break_check=0;
        unt_Enemy[turn-4].all_toughness_break_time+=current-unt_Enemy[turn-4].atv_at_break;
    }
    unt_Enemy[turn-4].Turn_count++;

    if(unt_Enemy[turn-4].Turn_count%3==0){
        for(int i=1;i<=4;i++){
            unt_Ally[i].en+=unt_Ally[i].er*5;
        }
    }
    if(unt_Enemy[turn-4].Turn_count%3==1){
        Enemy_Call(unt_Enemy[turn-4].Enemy_call_amount);
    }         
}

void Start_Battle(){
    if(Ruan_mei_num!=0){
        energy(Ruan_mei_num,30);
        for(int i=1;i<=4;i++){
            dmg[i][0][3]+=68;
            dmg[i][0][9]+=20;
            unt_Ally[i].toughness_dmg_multiplier+=0.5;
            
            if(i!=Ruan_mei_num){
                Speed_Buff(unt[i],0.1,0);
            }
        }
    }
    if(MC_img_num!=0){
        unt_Ally[MC_img_num].er+=0.25;
    }
    
}
void Start_wave(){

}

void Buff_check(){
    if(turn==5||turn==6){
        return ;
    }
    if(unt[MC_img_num].cnt==3&&turn==MC_img_num){
        unt_Ally[MC_img_num].er-=0.25;
    }
}
void Debuff_check(){
    if(ult_after==1){
        ult_after=0;
    } 
    if(turn!=5||turn!=6){
        return ;
    }
    if(unt_Enemy[turn-4].Gallagher_ult_debuff==unt[turn].cnt){
    for(int i=1;i<=Enemy_mem;i++){
        dmg[i+4][6][8]-=13.2;
    }
    }
    
}

void Func_char(){
    turn_check=0;

        if(turn == Robin_num){
            Robin(turn);
        }
        if(turn == Ruan_mei_num){
            Ruanmei(turn);
        }
        if(turn == Firefly_num){
            Firefly(turn);
        }
        if(turn == Firefly_ult_num){
            unt[Firefly_ult_num].spd=0.01;
            st(unt[Firefly_ult_num]);
            unt_Ally[Firefly_num].toughness_dmg_multiplier -=0.5;
            dmg[Firefly_num][6][8]-=20;
            Speed_Buff(unt[Firefly_num],0,-60);
        }

        if(turn == MC_img_num){
            MC_img(turn);
        }

        if(turn == Gallagher_num){
            Gallagher(turn);
        }

        if(turn==Main_enemy_num||turn==Second_enemy_num){
            Enemy(turn);
        }

        ult_after=1;
}

void standby(){
    //spd setting
    if(Ruan_mei_num!=0){
        unt[Ruan_mei_num].spd = 104;
        unt_Ally[Ruan_mei_num].mxen = 130;
        unt_Ally[Ruan_mei_num].element = 3;
        stats(Ruan_mei_num,4,0,1.244);
    }
    if(Firefly_num!=0){
        unt[Firefly_num].spd = 104;
        unt_Ally[Firefly_num].mxen = 240;
        unt_Ally[Firefly_num].element = 2;
        stats(Firefly_num,5,1,1);
    }
    if(Firefly_ult_num!=0){
        unt[Firefly_ult_num].spd = 0.01;
    }
    if(MC_img_num!=0){
        unt[MC_img_num].spd = 105;
        unt_Ally[MC_img_num].mxen = 140;
        unt_Ally[MC_img_num].element = 7;
        stats(MC_img_num,4,0,1.244);
    }

    if(Gallagher_num!=0){
        unt[Gallagher_num].spd = 98;
        unt_Ally[Gallagher_num].mxen = 110;
        unt_Ally[Gallagher_num].element = 2;
        stats(Gallagher_num,4,0,1.244);
    }
    //unit number spd en er ตรงธาตุ ธาตุไร


    //enemy spd setting
    if(Main_enemy_num!=0){
    unt[Main_enemy_num].num=Main_enemy_num;
    unt[Main_enemy_num].spd = 158;
    unt_Enemy[Main_enemy_num-4].toughness = Max_toughness;

    }
    if(Second_enemy_num!=0){
    unt[Second_enemy_num].num=Second_enemy_num;
    unt[Second_enemy_num].spd = 158;
    unt_Enemy[Second_enemy_num-4].toughness = Max_toughness;
    }
    
    //other
    for(int i =1;i<=Total_mem;i++){
        st(unt[i]);
    }
    for(int i = 5;i<=6;i++){
    }
    Start_Battle();
    Start_wave();
}
void Out_put(){
    if(Action_check==1){
        cout<<current<<" ";
        cout<<turn<<" ";
        cout<<unt_Enemy[Main_enemy_num-4].toughness<<" ";
        cout<<unt_Enemy[Second_enemy_num-4].toughness<<" ";
        cout<<unt_Ally[Firefly_num].A6<<" ";
        cout<<endl;
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    double mns = 1e9;
    standby();
    
    



    //loop

    while (current < wave[j]) {
         mns = 1e9;
        //turn = 0;
        if(Robin_ult_time==1){
            for (int i = 1; i <= Total_mem; i++) {
                if(unt[i].atv==0){
                    turn =i;
                    unt[turn].cnt++;
                    Before_turn();
                    All_ult();
                    Deal_damage();

                    Func_char();
                    Deal_damage();
                     
                     
                    Out_put();
                    All_ult();
                    Deal_damage();

                    Debuff_check();
                    Buff_check();
                }
            }
            while(!pq.empty()){
            turn=pq.top().num;

            pq.pop();
            unt[turn].cnt++;
            Before_turn();
            All_ult();
            Deal_damage();
            
            Func_char();
            Deal_damage();
            
            
            Out_put();
            All_ult();
            Deal_damage();

            Debuff_check();
            Buff_check();

        }
        }

        for (int i = 1; i <= Total_mem; i++) {
            if (unt[i].atv < mns) {
                mns = unt[i].atv;
                turn = i;
            }
        }

        for (int i = 1; i <= Total_mem; i++) {

            if (i == turn) {
            }else unt[i].atv -= mns;
        }

        current+=mns;
        if(j<max_wave-1&&current >= wave[j]){
            j++;
            current=0;
            for(int i =1;i<=Total_mem;i++){
            st(unt[i]);

    }
    if(Robin_ult_time==1){
        unt[Robin_num].atv=10000/90;
    }
    Robin_tech_check=1;
    if(Action_check==1){cout<<"             new wave"<<endl;}
    else printf("new wave \n");
    continue;
        }
        if(current >= wave[j]){
            break;
        }
        unt[turn].cnt++;
        Before_turn();
        All_ult();
        Deal_damage();

        Func_char();
        Deal_damage();

        if(Robin_ult_time==1&&turn==Robin_num){
        unt[Robin_num].atv=10000/90;
        }
        
        Out_put();
        All_ult();
        Deal_damage();

        Debuff_check();
        Buff_check();
        }


    cout<<endl;
       for(int i =1;i<=Total_mem;i++){
        cout<<unt[i].cnt<<" ";

    }
    cout<<endl;
       for(int i =1;i<=4;i++){
        cout<<unt_Ally[i].break_cnt<<" ";

    }
    cout<<endl;
    
    for(int i = 1;i<=2;i++){
        if(unt_Enemy[i].toughness_break_check==1){
        unt_Enemy[i].all_toughness_break_time+=wave[j]-unt_Enemy[i].atv_at_break;
        }
    }
    cout<<unt_Enemy [Main_enemy_num-4].all_toughness_break_time<<" "<<unt_Enemy[Second_enemy_num-4].all_toughness_break_time;


    return 0;
}