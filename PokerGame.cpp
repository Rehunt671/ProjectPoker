#include "LN_REG.h"
#include "Poker.h"
#include "CheckHand.h"
using namespace std;

int main()
{
    srand(time(NULL));
    Database PK;
    Deck dRef; // เตรียมสำรับไพ่ที่ยังไม่ได้สับ
    string inputChoice;
    int outputChoice;
    int num_player;
    int chipRef; // Money in game
    int mandatory_betRef;
    if (PK.checkIfNewWeb())
    {
        cout << "Welcome this is new poker game all people please register\n";
        PK.registerUser();
        goto Start;
    }
    else
    {
        cout << "Welcome to Poker Game\n";
    Start:
        do
        {
            cout << "Enter Your Choice\n1.Login\n2.Register\n3.Exit\n";
            getline(cin, inputChoice);
            outputChoice = handleString(inputChoice);
            if (outputChoice == 0)
                cout << "Invalid input please try again\n";
            else if (outputChoice == 1)
                PK.loginUser(num_player);
            else if (outputChoice == 2)
                PK.registerUser();
            else
                exit(0);
        } while (outputChoice == 0);
    }
    recieveSimpleInformation(chipRef, mandatory_betRef);
    PokerGame poker(dRef, num_player, chipRef, mandatory_betRef); // เข้ามานั่งในเกมโป๊กเกอร์พร้อมที่จะเล่นเกม
    poker.beforeStart();
    poker.preflop();
    poker.flop();
    poker.turn();
    poker.river();
}