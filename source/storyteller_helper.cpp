//©Intellectual property of Butilca Rares-Dumitru
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<ctime>
#include"characters.h"
using namespace std;

//Player setup
void setup(character* ch_list[6], character* p_list[6])
{
    int number;
    string input;

	cout<<"ALL INPUTS ARE TO BE NUMBERS INTRODUCED FROM KEYBOARD FOLLOWED BY ENTER KEY\n\n\n";
	cout<<"How are the players going to be assigned their roles, manually(1) or automatically(2): ";

    do
    {
        getline(cin, input);

	    if(input == "1")
	    {
    	    cout<<"\nPlayers will be counted from 1 to 5.\n\n";

    	    for(int j = 1; j < 6; j++)
    	    {
    	        switch(j)
    	        {
    	            case 1: cout<<"The escort"; break;
    	            case 2: cout<<"The jester"; break;
    	            case 3: cout<<"The police officer"; break;
    	            case 4: cout<<"The killer"; break;
    	            case 5: cout<<"The doctor"; break;
    	        }

    	        cout<<" will be assigned the number: ";

    	        while(1)
    	        {
    	            getline(cin, input);

    	            if(input.size() == 1)
    	            {
    	                number = input[0] - '0';

    	                if(number >= 1 && number <= 5)
    	                {
                            if(!p_list[number])
                            {
    	                        p_list[number] = ch_list[j];
    	                        break;
                            }
                            else
                                cout<<"Player already assigned to a role, try again: ";
    	                }
                        else
                            cout<<"Wrong input, try again: ";
    	            }
                    else
                        cout<<"Wrong input, try again: ";
    	        }

    	        cout<<endl;
    	    }

    	    PAUSE();
    	    CLEARSCREEN();
            break;
	    }
	    else if(input == "2")
        {
			//algorithm that randomly assigns roles without repeating them
		    for(int i = 1; i < 6; i++)
		    {
				//the number of players without roles is reduced after every iteration
			    number = clock() % (5 - i + 1) + 1;

				//look up for the number-th player that has not been assigned a role to yet
                int position = 1;
                while(number)
                {
                    if(!p_list[position])
                    { 
                        number--;
                        if(!number)
                            p_list[position] = ch_list[i];
                    }

                    position++;
                }
	        }

            for(int i = 1; i < 6; i++)
            {
                cout<<"\nPlayer "<<i<<" will be assigned the role: "<<p_list[i]->check_role()<<"\n";
            }

            cout<<"\nThis intelligence is confidential,";
            cout<<"so make sure each player only knows which their role is.\n\n";
    	    PAUSE();
    	    CLEARSCREEN();
            break;
        }
        else
        {
            cout<<"Wrong input, try again: ";
        }
    }
    while(1);
}	

void night_phase (character* ch_list[6], character* p_list[6], int &on)
{
    int pick;
    string input;

	cout<<"ALL INPUTS ARE TO BE NUMBERS INTRODUCED FROM KEYBOARD FOLLOWED BY ENTER KEY\n\n\n";

    for(int i = 1; i < 6; i++)
    {
        cout<<"player "<<i<<"("<<p_list[i]->check_role()<<")->";
        if(p_list[i]->view_life_var() == ALIVE)
            cout<<" alive\n";
        else
            cout<<" dead\n";
    }

    cout<<"-------------------------\n\n";
    cout<<"The night has come! Everyone will go to sleep.\n\n";

    for(int j = 1; j < 6; j++)
    {

        switch(j)
        {
            case 1: ((escort*)ch_list[j])->intro(); break;
            case 2: ((jester*)ch_list[j])->intro(); break;
            case 3: ((officer*)ch_list[j])->intro(); break;
            case 4: ((killer*)ch_list[j])->intro(); break;
            case 5: ((doctor*)ch_list[j])->intro(); break;
        }
        

        if(ch_list[j]->view_life_var() == DEAD)
        {
            cout<<"\nThis character is dead. ";
            cout<<"It will be called to wake up just to create confusion, ";
			cout<<"but the player will do nothing.\n";
            PAUSE();
            cout<<"\n";
        }
        else
        {
            //Don't attempt to choose a target if the character is the jester
            while(j != 2)
            {
                getline(cin, input);

                if(input.size() == 1)
                {
                    pick = input[0] - '0';

                    if(pick >= 1 && pick <= 5)
                    {
                        if(p_list[pick]->view_life_var() != DEAD)
                        {
                            if(ch_list[j] != p_list[pick])
                                break;
                            else
                                cout<<"A player cannot pick themselves, try again: ";
                        }
                        else
                            cout<<"This target is dead, try again: ";

                    }
                    else
                        cout<<"Wrong input, try again: ";
                }
                else
                    cout<<"Wrong input, try again: ";
            }

            if(ch_list[j]->view_status())
            {
                switch(j)
                {
                    case 1: ((escort*)ch_list[j])->action(p_list[pick]); break;
                    case 2: ((jester*)ch_list[j])->action(p_list[pick]); break;
                    case 3: ((officer*)ch_list[j])->action(p_list[pick]); break;
                    case 4: ((killer*)ch_list[j])->action(p_list[pick]); break;
                    case 5: ((doctor*)ch_list[j])->action(p_list[pick]); break;
                }
            }
            //The officer has to be announced that they can't use their skill this night
            else if(j == 3)
            {
                cout<<"The officer is being kept busy by the escort.\n";
            }
            
            cout<<endl;
            ch_list[j]->set_status(AVAILABLE);
        }
    }

    PAUSE();
    CLEARSCREEN();
}

void day_phase(character* ch_list[6], character* p_list[6], int &on)
{
    int pick;
    string input;

	cout<<"ALL INPUTS ARE TO BE NUMBERS INTRODUCED FROM KEYBOARD FOLLOWED BY ENTER KEY\n\n\n";

    for(int i = 1; i < 6; i++)
    {
        cout<<"player "<<i<<"("<<p_list[i]->check_role()<<")->";
        if(p_list[i]->view_life_var() == ALIVE)
            cout<<" alive\n";
        else
            cout<<" dead\n";
    }

    cout<<"-------------------------\n\n";
    cout<<"The morning has come! Everyone will wake up.\n\n";
    
    for(int i = 1; i < 6; i++)
        if(p_list[i]->view_life_var() == INJURED)
        {
            cout<<"The player bearing the number "<<i<<" has died."<<endl;
            p_list[i]->set_life_var(DEAD);
        }
    
	//Only mafia can win right after the night phase
    if(VLF(1) + VLF(2) + VLF(3) + VLF(5) <= 1)
    {
        cout<<"Mafia has won the game!\n\n";
        on = 0;
        return;
    }

    cout<<"The rest of the players left alive will decide who to condemn to death by trial.";
    cout<<"If the consensus is reached, introduce the number of the condemned player.";
    cout<<"Otherwise, introduce anything other than the number of a living player: ";
    getline(cin, input);
    cout<<endl;

    if(input.size() == 1)
    {
        pick = input[0] - '0';

        if(pick >= 1 && pick <= 5 && p_list[pick]->view_life_var() == ALIVE)
        {    
            p_list[pick]->set_life_var(DEAD);

			//If the jester is killed during the day phase he wins alone and the others lose
            if(p_list[pick] == ch_list[2]) 
            {
                cout<<"The jester has won the game!\n\n";
                on = 0;
                return;
            }

			//If the killer is hanged, the town wins
            if(p_list[pick] == ch_list[4])
            {
                cout<<"The town has won!\n\n";
                on = 0;
                return;
            }
        }
    }

	//Only if the jester isn't the one to be hanged, the mafia can win
    if(VLF(1) + VLF(2) + VLF(3) + VLF(5) <= 1)
    {
        cout<<"Mafia has won!\n\n";
        on = 0;
        return;
    }

    CLEARSCREEN();
}

//Eliminates the objects that were dynamically allocated
void delete_residuals(character* ch_list[6])
{
    for(int i = 1; i < 6; i++)
    {
        delete ch_list[i];
    }
}

int main()
{
    string input;
    do
    {	
		cout<<"ALL INPUTS ARE TO BE NUMBERS INTRODUCED FROM KEYBOARD FOLLOWED BY ENTER KEY\n\n\n";
        cout<<"Welcome to the storyteller helper!\n";
        cout<<"\tMENU\n";
        cout<<"   Start game(1)\n      Help(2)\n    Exit(other)\n";
        cout<<"Introduce your option: ";
        getline(cin, input);
        cout<<endl;
        CLEARSCREEN();

        if(!input.compare("1"))
        {
            //Character list
            character* ch_list[6];
            //Players list
            character* p_list[6];
            for(int i = 1; i < 6; i++)
                p_list[i] = NULL;
            // Variable that registers whether the game is still on or if it is over
            int on = 1;

            ch_list[1] = new escort;
            ch_list[2] = new jester;
            ch_list[3] = new officer;
            ch_list[4] = new killer;
            ch_list[5] = new doctor;
    
            setup(ch_list, p_list);
    
            while(on)
            {
                night_phase(ch_list, p_list, on);
                if(!on)
                    break;
                day_phase(ch_list, p_list, on);
            }

            PAUSE();
            CLEARSCREEN();
            delete_residuals(ch_list);
        }
        else if(!input.compare("2"))
        {
            ifstream f("tool text files/help.txt");
            string line;

            while(getline(f, line))
            {
                cout<<line<<endl;
            }

            f.close();

            cout<<"\n";
            PAUSE();
            CLEARSCREEN();
        }
    }
    while(!input.compare("1") || !input.compare("2"));

    return 0;
}
