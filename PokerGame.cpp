#include "Poker.h"
#include "CheckHand.h"
using namespace std;

int main()
{
    int num_player = 4;
    int chipRef = 1000; // Money in game
    int mandatory_betRef = 10;
    srand(time(NULL));
    
    Deck dRef;                                                    // เตรียมสำรับไพ่ที่ยังไม่ได้สับ
    PokerGame poker(dRef, num_player, chipRef, mandatory_betRef); // เข้ามานั่งในเกมโป๊กเกอร์พร้อมที่จะเล่นเกม
    poker.beforeStart();
    poker.preflop();
    poker.flop();
    poker.turn();
    poker.river();
}