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
    vector<Player *> players;
    int num_player;
    int minChip;
    int mandatoryBet;
    int choice;
    int cnt = 1;
    drawPic();
    do
    {
        cout << "Enter number of player(2-4)\n";
        cin >> num_player;
        if (num_player < 2 || num_player > 4)
        {
            clearInput();
        }
    } while (num_player < 2 || num_player > 4);
    recieveSimpleInformation(minChip, mandatoryBet);
    while (cnt <= num_player)
    {
        cout << " ================================================= Player " << cnt << " =================================================\n";
        cout << "Select Your Choice\n[1] Login\n[2] Register\n[3] Exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            pokerDB.loginUser(players, minChip);
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
    PokerGame poker(pokerDB, players, deck, minChip, mandatoryBet); // เข้าม   านั่งในเกมโป๊กเกอร์พร้อมที่จะเล่นเกม
    do
    {
        if (poker.restart)
        {
            poker.restart = false;
            poker.resetGame();
        }
        poker.beforeStart();
        poker.preflop();
        if (poker.restart)
            continue;
        poker.flop();
        if (poker.restart)
            continue;
        poker.turn();
        if (poker.restart)
            continue;
        poker.river();
    } while (poker.restart);
}
