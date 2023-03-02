#include "AllClass.h"
#include "LN_REG.h"
#include "CheckHand.h"
#include "Poker.h"
using namespace std;
int main()
{
    srand(time(NULL));
    Database pokerDB;
    Deck deck;                      // เตรียมสำรับไพ่ที่ยังไม่ได้สับ
    pokerDB.importDatafromfile();   // อ่านลง Vector 4 ตัว มี Username Password Displayname money ใน Class pokerDB
    int num_player;
    int choice;
    int cnt = 1;
    int moneyInGame; // Money in game
    int mandatory_betRef;

    cout << "Welcome to Poker Game\n";
    do
    {
        cout << "Enter number of player(2-4)\n";
        cin >> num_player;
        if (num_player < 2 || num_player > 4)
        {
            clearInput();
        }
    } while (num_player < 2 || num_player > 4);
    while (cnt <= num_player)
    {
        cout << " ================================================= Player " << cnt << " =================================================\n" ;   
        cout << "Select Your Choice\n1.Login\n2.Register\n3.Exit\n";
        cin >> choice;
        switch (choice)
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
            clearInput();
            cout << "Invalid input try again\n";
            break;
        }
        if (choice == 1)
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
