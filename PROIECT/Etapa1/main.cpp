#include <string.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cmath>
#include <Windows.h >
using namespace std;


char mobnume[100]={"monster"};
// player class ////////////////////////////////////////////////////////////////////////

class Player
{
    public:
        Player();
        // ~player();

        // getters  setters

        inline char* getName() const { return this->name; }
        inline int getLevel() const { return this->level; }
        inline int getExpNext() const { return this->expNext; }
        inline int getHP() const { return this->hp; }
        inline int getHPMax() const { return this->hpMax; }
        inline int getDmg() const { return this->dmg; }
        inline int getDef() const { return this->def; }
        inline int getHPot() const { return this->hPot; }
        inline bool getBossFight() const { return this->bossFight; }
        inline const int getLevelMax() const { return this->levelMax; }

        inline void setHP(int a) {this->hp += a;}
        inline void setHPMax(int a) {this->hpMax += a;}
        inline void setExp(int a) {this->exp += a;}
        inline void setExpNext(int a) {this->expNext = a;}
        inline void setDmg(int a) {this->dmg += a;}
        inline void setDef(int a) {this->def += a;}
        inline void setHPPot(int a) {this->hPot += a;}
        inline void setBossFight(bool a) {this->bossFight = a;}
        void setDmgArr(int* a)
        {
            if (this->dmgArr != nullptr)
                delete[] this->dmgArr;

            int b = 3;

            this->dmgArr = new int[b];
            for(int i=0;i<b;i++)
                this->dmgArr[i] = a[i];
        }

        // functions

        void player_lvlUP(Player &obj);
        void exp_checker(Player &obj);
        void player_block(Player &obj);
        void player_run (void);
        void player_pot(Player &obj);
        void last_level(Player &obj);

        //operator
        friend ostream& operator<<(ostream &, Player&);
        friend istream& operator>>(istream& in, Player& obj);
        Player operator++();
        Player operator++(int);

        Player operator+(int);
        bool operator== (int);
        bool operator> (int);
        Player& operator =(const Player& cvObj)
        {
            this->hpMax = cvObj.hpMax;
        }
        int operator [](int index)
        {
            return this->dmgArr[index];
        }
        explicit operator int()
        {
            return (int) this->exp;
        }

    private:
        int level;
        const int levelMax = 9;
        float exp;
        int expNext;
        int hp;
        int hpMax;
        int dmg;
        int def;
        bool bossFight;
        int hPot;
        char* name;
        int* dmgArr;

    protected:

};

//constructor player
Player::Player()
{
    //this->name = name;
    this->level = 1;
    this->exp = 0;
    this->expNext = 100;
    this->hp = 100;
    this->hpMax = 100;
    this->dmg= 15;
    this->def = 1;
    this->bossFight = false;
    this->hPot = 2;

}
//operatori player

istream& operator>>(istream& in, Player&obj)
{
    char aux[100];
    cout<<"Type your characters name: ";
    in>>aux;
    //obj.name = (char*)malloc(256&sizeof(char));
    obj.name = new char[strlen(aux)+1];
    strcpy(obj.name,aux);
}
ostream& operator<<(ostream& out, Player& obj)
{
    out<<" Name: "<<obj.getName()<<"\t"<<" Health: "<<obj.getHP()<<" / "<<obj.getHPMax()<<
        "\tDamage: "<<obj.getDmg()<<"\n Level: "<<obj.getLevel()<<
        "\tExp :"<<(int)obj<<" / "<<obj.getExpNext()<<"\tDefense: "<<obj.getDef()<<"\n\n";
    return out;
}
Player Player::operator++()
{
    this->level++;
    return *this;
}
Player Player::operator++(int dummy)
{
    this->def+=this->getLevel();
    this->dmg+=this->getLevel();
    return *this;
}
Player Player::operator+(int a)
{
    Player *rez = new Player(*this) ;
    rez->hpMax+=10;



    return *rez;
}
bool Player::operator==(int a)
{
    return exp == a;
}
bool Player::operator>(int a)
{
    return exp > a;
}
//functii player

void Player::player_block(Player &obj)
{
    system("cls");

    int d = (int)(0.2*obj.getDmg());
    cout<<" You blocked the attack and healed for "<<d<<" HP.\n\n";
    obj.setHP(d);
    if(obj.getHP()>obj.getHPMax())
        obj.setHP(obj.getHPMax()-obj.getHP());
    system("pause");
    system("cls");
}

void Player::player_pot(Player&obj)
{
    system("cls");
    if (obj.getHPot()>0)
    {
        obj.setHPPot(-1);

        cout<<"\n You used 1 health potion.\n\n You healed for ";
        cout<<(int)(0.3*obj.getHPMax())<<" .\n\n ";
        system("pause");
        system("cls");
        obj.setHP((int)(0.3*obj.getHPMax()));
        if(obj.getHP()>obj.getHPMax())
            obj.setHP(obj.getHPMax()-obj.getHP());
    }

    else
        cout<<"\n You don't have any potions!";

}
void Player::player_run(void)
{
    system("cls");
    cout<<"run";
}

void Player::last_level(Player &obj)
{
    system("cls");
    cout<<"gz";
}
void Player::player_lvlUP(Player &obj)
{
    if (obj.getLevel()==obj.getLevelMax())
        obj.last_level(obj);
    else
    {
        ++obj;
        cout<<"\n Gz u leveled up!\n\n";

        obj.setExp(-(int)obj);
        obj.setExpNext(2*obj.getExpNext());
        obj++;
        obj=obj+10;
    }
}

void Player::exp_checker(Player &obj)
{
    if (obj > obj.getExpNext())
    {
        obj.setExp(obj.getExpNext()-(int)obj);
    }
    if(obj == obj.getExpNext())
        obj.setBossFight(true);
}

// monster1 class ////////////////////////////////////////////////////////////////

class Monster1
{
public:
    Monster1();
    //constructor cu parametrii
    Monster1(Player obj,char* nume);
    Monster1(const Monster1&mob);

    // ~monster();

    //getters setter

    inline const int getLevel() const { return this->mobLevel; }
    inline const int getHP() const { return this->mobHP; }
    inline const int getHPMax() const { return this->mobHPMax; }
    inline const int getDamage() const { return this->mobDamage; }
    inline const int getDefense() const { return this->mobDefense; }
    inline const bool getDoubleExp() const {return this->doubleExp;}
    inline const int getLevelMax() const { return this->mobLevelMax; }
    inline const int getMobCounter() const { return this->mobCounter; }
    inline const char* getMobTitle() const { return this->mobTitle;}

    char* getName()
    {
        strcpy(this->mobName,mobnume);
        return this->mobName;
    }

    inline void setHP(int a) {this->mobHP =a;}
    inline void setExp(int a) {this->mobExp = a;}
    inline void setMobLevel (int a) {this->mobLevel=a;}
    inline void setMobCounter () {this->mobCounter++;}

    //functions

    void player_attack(Player &obj,Monster1 &mob);

    //operatori
    friend ostream& operator<<(ostream &, Monster1&);
    friend istream& operator>>(istream& in, Monster1& mob);
    Monster1 operator++();
    Monster1 operator++(int);
    Monster1 operator--(int);
    Monster1 operator+(Player);
    bool operator== (Monster1&);
    bool operator< (Monster1&);
    Monster1& operator =(const Monster1& cvMob)
    {
        this->mobHP = cvMob.mobHP;
    }
    int operator [](int index)
    {
        return this->dmgArr[index];
    }
    void setDmgArr(int* a)
    {
        if (this->dmgArr != nullptr)
            delete[] this->dmgArr;

        int b = 3;

        this->dmgArr = new int[b];
        for(int i=0;i<b;i++)
            this->dmgArr[i] = a[i];
    }
    explicit operator int()
    {
        return (int) this->mobExp;
    }

private:
    int mobLevel;
    const int mobLevelMax = 9;
    bool doubleExp;
    char* mobName;
    int* dmgArr;
    int mobDamage;
    int mobHP;
    int mobHPMax;
    float mobExp;
    int mobDefense;
    static double mobCounter;
    static char mobTitle[100];

};

double Monster1::mobCounter = 0;
char Monster1::mobTitle[100]={""};

Monster1::Monster1()
{

}

Monster1::Monster1(Player obj,char* nume)
{
    srand((int)time(0));
    int r = (rand() % 3) ;

    this->mobLevel = obj.getLevel() + r;

    this->mobDamage = obj.getDmg()-5+2*this->mobLevel;
    this->mobHPMax = obj.getHPMax()-10 + 2*this->mobLevel;
    this->mobHP =this->mobHPMax ;
    this->mobDefense = obj.getDef();
    this->mobExp = 20+this->mobLevel*2;
    this->doubleExp = false;
    this->mobName = new char[strlen(nume)+1];
    strcpy(this->mobName,nume);


}
int c=0;
Monster1::Monster1(const Monster1 &mob)
{
    srand((int)time(0));
    int p;
    c++;
    if(c%2==0)
        p=1;
    else p=0;

    this->mobLevel = mob.mobLevel-p;
    this->mobName = mob.mobName;
    this->mobDamage = mob.mobDamage;
    this->mobHPMax = mob.mobHPMax;
    this->mobHP =mob.mobHP;
    this->mobDefense = mob.mobDefense;
    this->mobExp = mob.mobExp;
    this->doubleExp = mob.doubleExp;
}

//supraincarcari

istream& operator>>(istream& in, Monster1&mob)
{
    char aux[100];
    cout<<"Change monster title: ";
    in>>aux;
    strcpy(mob.mobTitle,aux);
}
ostream& operator<<(ostream& out,Monster1 &mob)
{
    out<<"\n\t You defeated the "<<mob.getName()<<"!! \n\n You got "<<(int)mob<<" EXP!\n " ;
    return out;
}

Monster1 Monster1::operator++()
{
    this->mobCounter++;
    return *this;
}


Monster1 Monster1::operator++(int dummy)
{
    this->doubleExp = true;
    return *this;
}

Monster1 Monster1::operator--(int dummy)
{
    this->doubleExp = false;
    return *this;
}

Monster1 Monster1::operator+(Player obj)
{
    Monster1 *rez = new Monster1(*this);

    srand((int)time(0));
    int k1 = (rand() % 3);

    int mobHP = this->mobHP;
    int playerDMG = obj[k1] - this->getDefense();

    mobHP -= playerDMG;

    rez->mobHP= mobHP;

    return *rez;
}

bool Monster1::operator==(Monster1& mob)
{
    return mobLevel == mob.getLevel();
}
bool Monster1::operator<(Monster1& mob)
{
    return mobLevel < mob.getLevel();
}
void Monster1::player_attack(Player &obj,Monster1 &mob)
{
    mob++;
    int playerHP = obj.getHP();

    srand((int)time(0));
    int k1 = (rand() % 3);
    int k2 = (rand() % 3);

    int playerDMG = obj[k1] - mob.getDefense();
    int mobDMG = mob[k2] - obj.getDef();

    playerHP -=mobDMG;

    obj.setHP(-mobDMG);
    //mob.setHP(mobHP);
    mob = mob+obj;
    system("cls");
    cout<<"You did "<<playerDMG<<" DMG to the "<<mob.getName()<<".\n\n";
    cout<<"You took "<<mobDMG<<" DMG.\n\n";
    system("pause");
    system("cls");
};

// monster2 the loot class ////////////////////////////////////////////////////////////////

class Monster2
{
public:
    Monster2();
    //constructor cu parametrii
    Monster2(Player obj,char* nume);
    Monster2(const Monster2&mob);

    // ~monster();

    //getters setter

    inline const int getLevel() const { return this->mobLevel; }
    inline const int getHP() const { return this->mobHP; }
    inline const int getHPMax() const { return this->mobHPMax; }
    inline const int getDamage() const { return this->mobDamage; }
    inline const int getDefense() const { return this->mobDefense; }
    inline const bool getDoubleExp() const {return this->doubleExp;}
    inline const int getLevelMax() const { return this->mobLevelMax; }
    inline const int getMobCounter() const { return this->mobCounter; }
    inline const char* getMobTitle() const { return this->mobTitle;}

    char* getName()
    {
        strcpy(this->mobName,mobnume);
        return this->mobName;
    }

    inline void setHP(int a) {this->mobHP =a;}
    inline void setExp(int a) {this->mobExp = a;}
    inline void setMobLevel (int a) {this->mobLevel=a;}
    inline void setMobCounter () {this->mobCounter++;}
    void setFighturi(int a);

    //functions

    void player_attack(Player &obj,Monster2 &mob);
    explicit operator int()
    {
        return (int) this->mobExp;
    }
    //operatori
    friend ostream& operator<<(ostream &, Monster2&);
    friend istream& operator>>(istream& in, Monster2& mob);
    Monster2 operator++();
    Monster2 operator++(int);
    Monster2 operator--(int);
    Monster2 operator+(Player);
    bool operator== (Monster2&);
    bool operator< (Monster2&);
    Monster2& operator =(const Monster2& cvMob)
    {
        this->mobHP = cvMob.mobHP;
    }
    int operator [](int index)
    {
        return this->dmgArr[index];
    }
    void setDmgArr(int* a)
    {
        if (this->dmgArr != nullptr)
            delete[] this->dmgArr;

        int b = 3;

        this->dmgArr = new int[b];
        for(int i=0;i<b;i++)
            this->dmgArr[i] = a[i];
    }

private:
    int mobLevel;
    const int mobLevelMax = 9;
    bool doubleExp;
    char* mobName;
    int* dmgArr;
    int mobDamage;
    int mobHP;
    int mobHPMax;
    float mobExp;
    int mobDefense;
    static double mobCounter;
    static char mobTitle[100];

};

double Monster2::mobCounter = 0;
char Monster2::mobTitle[100]={""};

Monster2::Monster2()
{

}

Monster2::Monster2(Player obj,char* nume)
{
    srand((int)time(0));
    int r = (rand() % 3) ;

    this->mobLevel = obj.getLevel() + r;

    this->mobDamage = obj.getDmg()-5+2*this->mobLevel;
    this->mobHPMax = obj.getHPMax()-10 + 2*this->mobLevel;
    this->mobHP =this->mobHPMax ;
    this->mobDefense = obj.getDef();
    this->mobExp = 5+this->mobLevel*2;
    this->doubleExp = false;
    this->mobName = new char[strlen(nume)+1];
    strcpy(this->mobName,nume);


}
int c1=0;
Monster2::Monster2(const Monster2 &mob)
{
    srand((int)time(0));
    int p;
    c1++;
    if(c1%2==0)
        p=1;
    else p=0;

    this->mobLevel = mob.mobLevel-p;
    this->mobName = mob.mobName;
    this->mobDamage = mob.mobDamage;
    this->mobHPMax = mob.mobHPMax;
    this->mobHP =mob.mobHP;
    this->mobDefense = mob.mobDefense;
    this->mobExp = mob.mobExp;
    this->doubleExp = mob.doubleExp;
}

//supraincarcari

istream& operator>>(istream& in, Monster2&mob)
{
    char aux[100];
    cout<<"Change monster title: ";
    in>>aux;
    strcpy(mob.mobTitle,aux);
}
ostream& operator<<(ostream& out,Monster2 &mob)
{
    out<<"\n\t You defeated the "<<mob.getName()<<"!! \n\n You got "<<(int)mob<<" EXP!\n " ;
    return out;
}

Monster2 Monster2::operator++()
{
    this->mobCounter++;
    return *this;
}


Monster2 Monster2::operator++(int dummy)
{
    this->doubleExp = true;
    return *this;
}

Monster2 Monster2::operator--(int dummy)
{
    this->doubleExp = false;
    return *this;
}

Monster2 Monster2::operator+(Player obj)
{
    Monster2 *rez = new Monster2(*this);

    int mobHP = this->mobHP;
    int mobDMG = this->mobDamage - obj.getDef();
    int playerHP = obj.getHP();
    int playerDMG = obj.getDmg() - this->mobDefense;

    mobHP -= playerDMG;
    playerHP -=mobDMG;

    rez->mobHP= mobHP;

    return *rez;
}

bool Monster2::operator==(Monster2& mob)
{
    return mobLevel == mob.getLevel();
}
bool Monster2::operator<(Monster2& mob)
{
    return mobLevel < mob.getLevel();
}
void Monster2::player_attack(Player &obj,Monster2 &mob)
{
    mob++;
    int mobHP = mob.getHP();
    int playerHP = obj.getHP();

    srand((int)time(0));
    int k1 = (rand() % 3);
    int k2 = (rand() % 3);

    int playerDMG = obj[k1] - mob.getDefense();
    int mobDMG = mob[k2] - obj.getDef();

    mobHP -= playerDMG;
    playerHP -=mobDMG;

    obj.setHP(-mobDMG);
    //mob.setHP(mobHP);
    mob = mob+obj;
    system("cls");
    cout<<"You did "<<playerDMG<<" DMG to the "<<mob.getName()<<".\n\n";
    cout<<"You took "<<mobDMG<<" DMG.\n\n";
    system("pause");
    system("cls");
};

//loot class ////////////////////////////////////////////////////////////////

class loot
{
    public:
        loot(Player &obj);
        loot(Player &obj,int r);
        ~loot();
        inline string const getLoot_type(int a) {return this->loot_type[a];}
    private:

        const string loot_type[3] = {"Weapon","Armor","Health Potion"};

};
loot::loot(Player &obj)
{
    srand((int)time(0));

    int r = (rand() % 4);

    switch(r)
        {
        case 0:
            cout<<"\nYou found a weapon.  You get +"<<obj.getLevel()<<" permanent attack damage.\n\n";
            obj.setDmg(obj.getLevel());
            break;
        case 1:
            cout<<"\nYou found an armor.  You get +"<<obj.getLevel()<<" permanent defense.\n\n";
            obj.setDef(obj.getLevel());
            break;
        case 2:
            cout<<"\nYou found a health potion!";
            obj.setHPPot(1);
            cout<<"\n\nYou have "<<obj.getHPot()<<" health potions in total.\n\n";
            break;
        default:
            cout<<"\nYou did not find anything.\n";
            break;
        }
}
loot::loot(Player &obj,int r)
{

    switch(r)
        {
        case 0:
            cout<<"\nYou found a weapon.  You get +"<<obj.getLevel()<<" permanent attack damage.\n\n";
            obj.setDmg(obj.getLevel());
            break;
        case 1:
            cout<<"\nYou found an armor.  You get +"<<obj.getLevel()<<" permanent defense.\n\n";
            obj.setDef(obj.getLevel());
            break;
        case 2:
            cout<<"\nYou found a health potion!";
            obj.setHPPot(1);
            cout<<"\n\nYou have "<<obj.getHPot()<<" health potions in total.\n\n";
            break;
        default:
            cout<<"\nYou did not find anything.\n";
            break;
        }
}
loot::~loot()
{
    //cout<<"\nYou added the new item to you gear.\n\n";
}
//Boss class/////////////////////////////////////////////////////////////////////

class Boss
{
    public:
        Boss(Player obj);

        inline const int getLevel() const { return this->bossLevel; }
        inline const int getHP() const { return this->bossHP; }
        inline const int getHPMax() const { return this->bossHPMax; }
        inline const int getDamage() const { return this->bossDamage; }
        inline const int getDefense() const { return this->bossDefense; }
        inline const string getBoss(Player obj) {return this->bosses[obj.getLevel()-1]; }
        inline const int getLevelMax() const { return this->bossLevelMax; }

        inline void setHP(int a) {this->bossHP =a;}

        void player_attack(Player &obj,Boss &mob);

        //supraincarcari
        friend ostream& operator<<(ostream &, Boss&);
        Boss operator+(Player);
        Boss& operator =(const Boss& cvBoss)
        {
            this->bossHP = cvBoss.bossHP;
            cout<<cvBoss.bossHP;
        }

    private:
        int bossLevel;
        const int bossLevelMax = 9;
        int bossDamage;
        int bossHP;
        int bossHPMax;
        int bossDefense;
        static string bosses[10];

};

string Boss::bosses[10] = {"boss1","boss2","boss3","boss4","boss5","boss6","boss7","boss8","boss9","boss10"};

Boss::Boss(Player obj)
{
    this->bossDamage = obj.getDmg()-obj.getLevel();
    this->bossHPMax = (obj.getLevel()+1)*100;
    this->bossHP =this->bossHPMax ;
    this->bossDefense = obj.getLevel()*obj.getLevel() +1;
};

void Boss::player_attack(Player &obj,Boss &boss)
{
    int bossHP = boss.getHP();
    int bossDMG = boss.getDamage() - obj.getDef();
    int playerHP = obj.getHP();

    srand((int)time(0));
    int k = (rand() % 3);

    int playerDMG = obj[k] - boss.getDefense();

    bossHP -= playerDMG;
    playerHP -=bossDMG;

    obj.setHP(-bossDMG);

    boss = boss + obj;

    system("cls");
    cout<<"You did "<<playerDMG<<" DMG to the "<<boss.getBoss(obj)<<".\n\n";
    cout<<"You took "<<bossDMG<<" DMG.\n\n";
    system("pause");
    system("cls");
};
//supraincarcari boss

ostream& operator<<(ostream& out, Boss& boss)
{
    out<<"\n\t You defeated the boss from this zone: ";
    return out;
}

Boss Boss::operator+(Player obj)
{
    Boss *rez = new Boss(*this);

    int bossHP = this->bossHP;
    int bossDMG = this->bossDamage - obj.getDef();
    int playerHP = obj.getHP();
    int playerDMG = obj.getDmg() - this->getDefense();

    bossHP -= playerDMG;
    playerHP -=bossDMG;

    rez->bossHP= bossHP;

    return *rez;
}

//Game class

class Game
{
    public:
        Game();
        //~Game();
        //Functions

        void main_menu(Player &obj);
        void explore(Player &obj,bool monster);
        void monster1_pop(Player &obj);
        void monster2_pop(Player &obj);
        void loot_pop(Player &obj);
        void rest(Player &obj);
        void boss_fight(Player &obj);

        //Getters_Setters

        inline bool get_playing() const{ return this->playing;}

    private:
        int choice;
        bool playing;
};

Game::Game()
        {
            choice = 0;
            playing = true;
        }

// functii game

void Game::boss_fight(Player &obj)
{
    system("cls");
    //cout<<"bossuuu\n\n";
    Boss boss(obj);
    int pdmg[3] = {obj.getDmg()-1,obj.getDmg(),obj.getDmg()+1};
    obj.setDmgArr(pdmg);
    bool action2 = true;
    int r;
    while(action2)
    {

        int i;
        int proc = (int)(boss.getHPMax()/100);
        for (i=0;i<=boss.getHPMax()/2;i+=proc)
            cout<<" ";
        cout<<"~"<<boss.getBoss(obj)<<"~";

        cout<<"\n\n>";
        for (i=0;i<=boss.getHP();i+=proc)
            cout<<"@";
        for (i=boss.getHP()+1;i<=boss.getHPMax();i+=proc)
            cout<<"-";
        cout<<"<\n\n";
        for (i=0;i<=boss.getHP()/2-5;i+=proc)
            cout<<" ";
        cout<<"HP:"<<boss.getHP()<<"/"<<boss.getHPMax();
        for (i=0;i<=boss.getHP()/2-5;i+=proc)
            cout<<" ";
        cout<<"\n~The Elite from Zone "<<obj.getLevel()<<"\n~ATK:"<<boss.getDamage()<<"\n~DEF:"<<boss.getDefense()<<"\n";

        cout<<"\n LVL"<<obj.getLevel()<<" Player name: "<<obj.getName()<<"\n\n Player stats:  | HP:"<<obj.getHP()<<"/"<<
            obj.getHPMax()<<"  | EXP:"<<(int)obj<<"/"<<obj.getExpNext()<<" |\n\t\t| ATK:"<<obj.getDmg()<<"      | DEF:"<<obj.getDef()<<"     |\n\n";

        cout<<"\n Chose your action:\n";
        cout<<"\t1) Attack!\n\t2) Block!\n\t3) Use Health Potion!\n\t";
        cin>>r;
        switch(r)
        {
            case 1:
                system("cls");
                boss.player_attack(obj,boss);
                if (obj.getHP()<=0)
                {
                    action2 = false;
                    cout<<"\n\t YOU DIED and went back to 0 EXP.\n\n";
                    obj.setExp(-(int)obj);
                    obj.setHP(obj.getHPMax()-obj.getHP());
                    obj.setBossFight(false);
                    system("pause");
                }
                else if (boss.getHP()<=0)
                {
                    action2 = false;
                    cout<<boss;
                    cout<<boss.getBoss(obj)<<"\n\n";

                    obj.setBossFight(false);
                    int hp_missing = 0.6*(obj.getHPMax() - obj.getHP());
                    obj.setHP((int)(hp_missing));
                    obj.player_lvlUP(obj);
                    system("pause");
                }
                break;
            case 2:
                system("cls");
                obj.player_block(obj);
                break;
            case 3:
                system("cls");
                obj.player_pot(obj);
                break;
            default:
                system("cls");
                cout<<"problema";
                break;
        }
    }


}

void Game::monster1_pop(Player &obj)
{
    int twoMobs=0;

    Monster1 mob(obj,mobnume);
    int pdmg[] = {obj.getDmg()-1,obj.getDmg(),obj.getDmg()+1};
    obj.setDmgArr(pdmg);

    int mdmg[] = {mob.getDamage()-1,mob.getDamage(),mob.getDamage()+1};
    mob.setDmgArr(mdmg);


    system("cls");

    if (mob.getLevel() == obj.getLevel() + 2  && mob.getMobCounter()%2==0)
        {mob++;
        twoMobs =1;
        }
    else mob--;

    if (mob.getLevel()>mob.getLevelMax())
        mob.setMobLevel(mob.getLevelMax());

    Monster1 mobSec=mob;

    int msdmg[] = {mobSec.getDamage()-1,mobSec.getDamage(),mobSec.getDamage()+1};

    cout<<"\t\t You encountered a monster:"<<mob.getName()<<"\n"; //rase mai tz
    cout<<"\n Monster counter :"<<mob.getMobCounter()<<"\n\n";

    bool action = true;
    bool fighting =true;

    while(action == true)
    {

        cout<<" LVL"<<obj.getLevel()<<" Player name: "<<obj.getName()<<"\n\n Player stats:  | HP:"<<obj.getHP()<<"/"<<
            obj.getHPMax()<<"  | EXP:"<<(int)obj<<"/"<<obj.getExpNext()<<" |\n\t\t| ATK:"<<obj.getDmg()<<"      | DEF:"<<obj.getDef()<<"     |\n\n";
        if(fighting==true) cout<<" LVL "<<mob.getLevel()<<" "<<mob.getMobTitle()<<" "<<mob.getName()<<" stats:  | HP:"<<mob.getHP()<<"/"<<mob.getHPMax()<<" |\n\t\t| ATK:"<<mob.getDamage()<<"      | DEF:"<<mob.getDefense()<<"     |\n\n";

        if(twoMobs==1 &&fighting ==false) cout<<" sec LVL"<<mobSec.getLevel()<<" "<<mobSec.getMobTitle()<<" "<<mobSec.getName()<<" stats:  | HP:"<<mobSec.getHP()<<"/"<<mobSec.getHPMax()<<" |\n\t\t| ATK:"<<mobSec.getDamage()<<"      | DEF:"<<mobSec.getDefense()<<"     |\n\n";

        cout<<"\n Chose your action:\n";
        cout<<"\t1) Attack!\n\t2) Block!\n\t3) Run!\n\t";

        int r;
        cin>>r;
        switch(r)
        {
        case 1:
            system("cls");
            if(fighting==true) mob.player_attack(obj,mob);
            else {mobSec.setDmgArr(msdmg);mobSec.player_attack(obj,mobSec);}

            if (obj.getHP()<=0)
                {
                    action = false;
                    cout<<"\n\t YOU DIED and went back to 0 EXP.\n\n";
                    obj.setHP(obj.getHPMax()-obj.getHP());
                    obj.setExp(-1*(int)obj);
                }
            else if (mob.getHP()<=0 && fighting==true)
                {
                    if (twoMobs==0)
                        action = false;
                    fighting =false;

                    if (mob.getDoubleExp()==true)
                        mob.setExp(2*(int)mob);

                    cout<<mob;

                    ++mob;
                    obj.setExp((int)mob);
                    obj.exp_checker(obj);
                    cout<<"\n You have "<<(int)obj<<"/"<<obj.getExpNext()<<" EXP.\n\n";
                    int hp_missing = 0.6*(obj.getHPMax() - obj.getHP());
                    obj.setHP((int)(hp_missing));

                    if(twoMobs ==1)
                    {
                        system("pause");
                        system("cls");
                        cout<<"\n Another monster ambushed you!\n\n ";
                        system("pause");
                        system("cls");
                    }

                }
            else if(fighting == false && mobSec.getHP()<=0)
            {
                fighting =false;

                if (mob.getDoubleExp()==true)
                    mob.setExp(2*(int)mob);

                cout<<mobSec;

                obj.setExp((int)mobSec);
                obj.exp_checker(obj);
                cout<<"\n You have "<<(int)obj<<"/"<<obj.getExpNext()<<" EXP.\n\n";
                if(mob==mobSec)
                    cout<<" These 2 monsters were brothers.\n\n";
                else if(mobSec<mob)
                    cout<<" These 2 monsters were not brothers.\n\n";
                int hp_missing = 0.6*(obj.getHPMax() - obj.getHP());
                obj.setHP((int)(hp_missing));
                twoMobs = 0;
                action=false;
                system("pause");
                system("cls");
                loot item(obj,mob.getMobCounter()%3);
            }

            break;
        case 2:
            system("cls");
            obj.player_block(obj);
            break;
        case 3:
            system("cls");
            cout<<"\n You ran away from the monster\n\n";
            action = false;
            break;
        default:
            system("cls");
            cout<<"\n Unknown command.\n\n";
            system("pause");
            system("cls");
            break;

        }
    }
}
void Game::monster2_pop(Player &obj)
{
    int twoMobs=0;

    Monster2 mob(obj,mobnume);
    int pdmg[3] = {obj.getDmg()-1,obj.getDmg(),obj.getDmg()+1};
    obj.setDmgArr(pdmg);

    int mdmg[3] = {mob.getDamage()-1,mob.getDamage(),mob.getDamage()+1};
    mob.setDmgArr(mdmg);

    system("cls");

    if (mob.getLevel() == obj.getLevel() + 2  && mob.getMobCounter()%2==0)
        {mob++;
        twoMobs =1;
        }
    else mob--;

    if (mob.getLevel()>mob.getLevelMax())
        mob.setMobLevel(mob.getLevelMax());

    Monster2 mobSec=mob;

    int msdmg[3] = {mobSec.getDamage()-1,mobSec.getDamage(),mobSec.getDamage()+1};


    cout<<"\t\t You encountered a monster:"<<mob.getName()<<"\n"; //rase mai tz
    cout<<"\n Monster counter :"<<mob.getMobCounter()<<"\n\n";

    bool action = true;
    bool fighting =true;

    while(action == true)
    {

        cout<<" LVL"<<obj.getLevel()<<" Player name: "<<obj.getName()<<"\n\n Player stats:  | HP:"<<obj.getHP()<<"/"<<
            obj.getHPMax()<<"  | EXP:"<<(int)obj<<"/"<<obj.getExpNext()<<" |\n\t\t| ATK:"<<obj.getDmg()<<"      | DEF:"<<obj.getDef()<<"     |\n\n";
        if(fighting==true) cout<<" LVL "<<mob.getLevel()<<" "<<mob.getMobTitle()<<" "<<mob.getName()<<" stats:  | HP:"<<mob.getHP()<<"/"<<mob.getHPMax()<<" |\n\t\t| ATK:"<<mob.getDamage()<<"      | DEF:"<<mob.getDefense()<<"     |\n\n";

        if(twoMobs==1 &&fighting ==false) cout<<" sec LVL"<<mobSec.getLevel()<<" "<<mobSec.getMobTitle()<<" "<<mobSec.getName()<<" stats:  | HP:"<<mobSec.getHP()<<"/"<<mobSec.getHPMax()<<" |\n\t\t| ATK:"<<mobSec.getDamage()<<"      | DEF:"<<mobSec.getDefense()<<"     |\n\n";

        cout<<"\n Chose your action:\n";
        cout<<"\t1) Attack!\n\t2) Block!\n\t3) Run!\n\t";

        int r;
        cin>>r;
        switch(r)
        {
        case 1:
            system("cls");
            if(fighting==true) mob.player_attack(obj,mob);
            else {mobSec.setDmgArr(msdmg); mobSec.player_attack(obj,mobSec);}

            if (obj.getHP()<=0)
                {
                    action = false;
                    cout<<"\n\t YOU DIED and went back to 0 EXP.\n\n";
                    obj.setHP(obj.getHPMax()-obj.getHP());
                    obj.setExp(-1*(int)obj);
                }
            else if (mob.getHP()<=0 && fighting==true)
                {
                    if (twoMobs==0)
                        action = false;
                    fighting =false;

                    if (mob.getDoubleExp()==true)
                        mob.setExp(2*(int)mob);

                    cout<<mob;

                    ++mob;
                    obj.setExp((int)mob);
                    obj.exp_checker(obj);
                    cout<<"\n You have "<<(int)obj<<"/"<<obj.getExpNext()<<" EXP.\n\n";
                    int hp_missing = 0.6*(obj.getHPMax() - obj.getHP());
                    obj.setHP((int)(hp_missing));

                    loot item(obj,mob.getMobCounter()%3);

                    if(twoMobs ==1)
                    {
                        system("pause");
                        system("cls");
                        cout<<"\n Another monster ambushed you!\n\n ";
                        system("pause");
                        system("cls");
                    }
                }
            else if(fighting == false && mobSec.getHP()<=0)
            {
                fighting =false;

                if (mob.getDoubleExp()==true)
                    mob.setExp(2*(int)mob);

                cout<<mobSec;

                obj.setExp((int)mobSec);
                obj.exp_checker(obj);
                cout<<"\n You have "<<(int)obj<<"/"<<obj.getExpNext()<<" EXP.\n\n";
                if(mob==mobSec)
                    cout<<" These 2 monsters were brothers.\n\n";
                else if(mobSec<mob)
                    cout<<" These 2 monsters were not brothers.\n\n";
                int hp_missing = 0.6*(obj.getHPMax() - obj.getHP());
                obj.setHP((int)(hp_missing));
                twoMobs = 0;
                action=false;
                system("pause");
                system("cls");
                loot item(obj,mob.getMobCounter()%3);
            }

            break;
        case 2:
            system("cls");
            obj.player_block(obj);
            break;
        case 3:
            system("cls");
            cout<<"\n You ran away from the monster\n\n";
            action = false;
            break;
        default:
            system("cls");
            cout<<"\n Unknown command.\n\n";
            system("pause");
            system("cls");
            break;

        }
    }
}

void Game::explore(Player &obj,bool monster )
{
    system("cls");
    Sleep(500);

    srand((int)time(0));
    int r = (rand() % 10) + 1;

    if (monster == 1 && r!=-1)
        monster1_pop(obj);
    else if(monster == 0)
        monster2_pop(obj);

    else
    {
        system("cls");
        cout<<"You did not find anything.\n\n";
    }

    system("pause");
}

void Game::rest(Player &obj)
{
    system("cls");
    cout<<"...";
    Sleep(1000);
    system("cls");
    cout<<"\nYou've made a bonfire and rested for a few hours!\n\n";
    //va trb random
    int hp_missing = obj.getHPMax() - obj.getHP();

    cout<<"You've healed from "<<obj.getHP() <<" HP to "<<obj.getHPMax()<<" HP\n\n";
    obj.setHP(hp_missing);
    system("pause");
}

void Game::main_menu(Player &obj)
{
    Sleep(500);

    system("cls");
    cout<<obj;
    cout << "\tWhat do you want to do?\n";

    if (obj.getBossFight()==true)
        cout << "\t0: Boss Fight!\n";

    cout << "\t1: Hunt Exp Monsters\n";
    cout << "\t2: Hunt Loot Monsters\n";
    cout << "\t3: Rest\n";
    cout << "\t4: Close game\n";
    cout << "\t5: Change mob name\n";
    cout << "\t6: Help\n";
    cout <<"\n\tChoice: ";
    cin >>choice;
    switch (choice)
    {
        case 0:
            boss_fight(obj);
            break;
        case 4:
            playing = false;
            break;
        case 1:
            explore(obj,1);
            break;
        case 2:
            explore(obj,0);
            break;
        case 3:
            rest(obj);
            break;
        case 5:
            {system("cls");
            cout<<"Change monsters name: ";
            cin>>mobnume;
            Monster1 mob;
            cin>>mob;
            cout<<"\nThe monsters are now:"<<mobnume<<" ";
            cout<<mob.getMobTitle()<<"\n\n";
            system("pause");
            system("cls");
            break;}
        case 6:
            {system("cls");
            cout<<"\t\t A few tips.\n\n";
            cout<<"\n\t - You can either kill monsters for exp or for loot. \n";
            cout<<"\n\t - Once you get to max exp you can fight the boss. \n";
            cout<<"\n\t - The only way to level up is to defeat the boss when at max exp. \n";
            cout<<"\n\t - It is not recommended to fight the boss right after it is available. \n";
            cout<<"\n\t - You should farm items (damage items, defense items and health potions) \n\tfrom the loot monsters before going to the boss.\n";
            cout<<"\n\t - There's a monster counter (it counts the fights actually), every time you get a monster \n\tthat's 2 levels bigger than you  and the counter is even you get double exp from it \n\tand you get ambushed by another monster that will drop an item.   \n";
            cout<<"\n\t - When fighting a monster you can either attack, block (you'll block the monsters attack \n\tand heal for a small ammount of hp), or run if you think the monster is too dangerouse.\n";
            cout<<"\n\t - You can change the monsters name and title in the main menu.\n";
            system("pause");
            break;}

    }

}

// int main

int main()
{

    Player obj;
    cin>>obj;

    Game game;

    while(game.get_playing())
    {
        game.main_menu(obj);
    }

    return 0;
}
