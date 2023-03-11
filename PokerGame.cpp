#include "AllClass.h"
#include "Design.h"
#include "LN_REG.h"
#include "CheckHand.h"
#include "Poker.h"
using namespace std;
int main()
{

    srand(time(NULL));
    Database pokerDB;
    Deck deck;
    int num_player;
    int choice;
    int cnt = 1;
    int chip;
    int mandatoryBet;

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
        cout << " ================================================= Player " << cnt << " =================================================\n";
        cout << "Select Your Choice\n[1] Login\n[2] Register\n[3] Exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            pokerDB.loginUser();
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
    recieveSimpleInformation(chip, mandatoryBet);
    PokerGame poker(pokerDB, deck, num_player, chip, mandatoryBet); // เข้ามานั่งในเกมโป๊กเกอร์พร้อมที่จะเล่นเกม
    do
    {
        poker.beforeStart();
        poker.preflop();
        poker.flop();
        poker.turn();
        poker.river();
    } while (poker.restart);
}
