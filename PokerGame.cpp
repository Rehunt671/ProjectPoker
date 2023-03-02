#include "AllClass.h"
#include "LN_REG.h"
#include "CheckHand.h"
#include "Poker.h"
using namespace std;
int main()
{
    srand(time(NULL));
    Database pokerDB;
    Deck deck; // เตรียมสำรับไพ่ที่ยังไม่ได้สับ
    string inChoice;
    int outChoice;
    int num_player;
    int cnt = 1;
    int moneyInGame; // Money in game
    int mandatory_betRef;

    cout << "Welcome to Poker Game\n";
    do
    {
        cout << "Enter number of player(2-4)\n";
        getline(cin, inChoice);
        outChoice = handleString(inChoice);
    } while (outChoice < 2 || outChoice > 4);
    num_player = outChoice;
    while (cnt <= num_player)
    {
        cout << "Player " << cnt << "\nSelect Your Choice\n1.Login\n2.Register\n3.Exit\n";
        getline(cin, inChoice);
        outChoice = handleString(inChoice);
        switch (outChoice)
        {
        case 1:
            pokerDB.loginUser(pokerDB.loginIndex);
            break;
        case 2:
            pokerDB.registerUser();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "Invalid input try again\n";
            break;
        }
        if (outChoice == 1)
            cnt++;
    }
    recieveSimpleInformation(moneyInGame, mandatory_betRef);
    PokerGame poker(pokerDB, deck, num_player, moneyInGame, mandatory_betRef); // เข้ามานั่งในเกมโป๊กเกอร์พร้อมที่จะเล่นเกม
    poker.beforeStart();
    poker.preflop();
    poker.flop();
    poker.turn();
    poker.river();
}
