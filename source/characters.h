//©Intellectual property of Butilca Rares-Dumitru
#include<string.h>
#define ALIVE 1
#define DEAD 0
#define INJURED -1
#define AVAILABLE 1
#define BUSY 0
using namespace std;

#define CLEARSCREEN() for(int k = 0; k < 100; k++) cout<<"\n\n"
#define PAUSE() cout<<"Press enter to continue: "; cin.ignore(1000, '\n')
#define VLF(i) ch_list[i]->view_life_var()

class character
{
    private:
    string team; // mafia, town or neutral
    string role;
    int life_var; // alive, dead or injured
    int status; // available or busy

    public:
    void set_life_var(int a)
    {
        life_var = a;
    }

    void set_status(int a)
    {
        status = a;
    }

    int view_life_var()
    {
        return life_var;
    }

    int view_status()
    {
        return status;
    }

    string check_team()
    {
        return team;
    }

    string check_role()
    {
        return role;
    }

    void intro() {}
    void action(character* c) {}

    character(string team_value, string role_value)
    {
        life_var = ALIVE; status = AVAILABLE;
        team = team_value; role = role_value;
    }
};

class escort:public character
{
    public:
    void action(character *c)
    {
        c->set_status(BUSY);
    }

    void intro()
    {
        cout<<"The escort has awakened.\n";
        cout<<"This character will choose a target to divert tonight: ";
    }

    escort():character("town", "escort") {}
};

class jester:public character
{
    public:
    void intro()
    {
        cout<<"The jester has awakened.\n";
        cout<<"This character will do nothing. You may choose whether to wake them up or not.";
        if(view_life_var() == ALIVE)
        {            
            cout<<"\n";
            PAUSE();
        }
    }

    jester():character("neutral", "jester") {}
};

class officer:public character
{
    public:
    void action(character *c)
    {
        if(!c->check_team().compare("mafia"))
            cout<<"The target is a member of the mafia!\n";
        else 
            cout<<"The target is not a member of the mafia.\n";
    }

    void intro()
    {
        cout<<"The police officer has awakened.\n";
        cout<<"This character will choose a target to inspect: ";
    }

    officer():character("town", "officer") {}
};

class killer:public character
{
    public:
    void action(character *c)
    {
        c->set_life_var(INJURED);
    }

    void intro()
    {
        cout<<"The killer has awakened.\n";
        cout<<"This character will choose a target to kill: ";
    }

    killer():character("mafia", "killer") {}
};

class doctor:public character
{
    public:
    void action(character *c)
    {
        c->set_life_var(ALIVE);
    }

    void intro()
    {
        cout<<"The doctor has awakened.\n";
        cout<<"This character will choose a target to tend: ";
    }

    doctor():character("town", "doctor") {}
};
