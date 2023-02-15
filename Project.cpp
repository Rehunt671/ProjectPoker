#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include "Project.h"
using namespace std;
void drawPic()
{
    cout << "\n===============================================================================================";
    cout << "\n   CCCCC      A        SSSSSSSSS   IIIIIIIII  NN     NN    OOOOOOOO     ";
    cout << "\n CC          A  A      SS             III     NN N   NN   OO      OO    ";
    cout << "\nCC          A    A     SSSSSSSSS      III     NN  N  NN   OO      OO    ";
    cout << "\n CC        AAAAAAAA           SS      III     NN   N NN   OO      OO    ";
    cout << "\n   CCCCC  A        A   SSSSSSSSS   IIIIIIIII  NN     NN    OOOOOOOO     ";
    cout << "\n===============================================================================================";
    cout << "\n======================== Welcome to Poker Game=================================================\n";
}
void recieveSimpleInformation(int &num, long long int &money)
{
    do
    {
        cout << "Enter Number Of Player(2-4 People): ";
        cin >> num;
        if (num < 2 || num > 4)
            cout << "Invalid number of player\n";
        cin.ignore();
    } while (num < 2 || num > 4); // ถามว่ามากี่คน
    do
    {
        cout << "How much money do you want to play(1,000 - 1,000,000): ";
        cin >> money;
        if (money < 1000 || money > 1000000)
            cout << "Invalid money value\n";
        cin.ignore();
    } while (money < 1000 || money > 1000000);//ถามจะให้มีคนละกี่บาท
}
PokerGame::PokerGame(Player *&pRef, Deck &dRef, int numRef, long long int moneyRef) // สร้าง 1 PokerGame ต้องมีข้อมูลพื้นฐานตาม Parameterต่อไปนี้ ตำแหน่งคนจริง(&) สำรับไพ่ จำนวนคน
{
    player = pRef;    // กำหนด *player ของ Class Pokergame ชี้ไปยังคนแรก
    deck = dRef;      // กำหนดสำรับไพ่ ให้ตรงกับสำรับไพ่ที่เราสร้างขึ้นมา
    num_player = numRef; // กำหนดจำนวนคนของเกม Poker ของเรา
    for (int i = 0; i < numRef; i++)
    {
        (player + i)->money = moneyRef;
    }// กำหนดเงินเรียงคน
    round = 1;//กำหนดรอบของเกม
    turn = 0;//กำหนดเทิร์นว่าเทิร์นใคร
    boardMoney = 0;//กำหนดเงินใน Board ตั้งต้น
    betMoney = 0;//กำหนด ว่าตอนนี้ค่าเงิน Betสูงสุดเท่าไหร่ คน Call Raise จะได้รู้
    haveBetOrAllIn = false;//กำหนดว่ามีการ Bet || All inไปรึยัง ถ้ามีไปแล้วจะ Check ไม่ได้แล้ว แต่ Call Raise หรือ Fold ได้
}
PokerGame::~PokerGame()
{
    delete[] player;
}//Destructor ถูกเรียกใช้หลัง Function Main() กัน Memory Leak
void PokerGame::showBoard()//Show ว่า Board มีไพ่ไหนบ้างตอนนี้
{
    cout << "Current Board: ";
    for (int i = 0; i < boardSize; i++)
    {
        cout << board[i] << " ";
    }
    cout << "\n";
}
void PokerGame::showMoneyBoard()//Show ว่าเงินใน Board มีเท่าไหร่แล้ว
{
    cout << "Current Board Money: " << boardMoney << "\n";
}
void PokerGame::showMoneyBet()//Show ว่าเงิน Bet สูงสุดตอนนี้เท่าไหร่แล้ว
{
    cout << "Current Bet Money: " << betMoney << "\n";
}
void PokerGame::showPlayerCard(Player *p)// Showว่าไพ่คนปัจจุบัน(ใน Parameter ) มีอะไรบ้าง
{
    cout << p->name << "'s Cards: ";
    for (int i = 0; i < p->card.size(); i++)
    {
        cout << p->card[i] << " ";
    }
    cout << "\n";
}
void PokerGame::showPlayerMoney(Player *p)// Showว่าเงินคนปัจจุบัน(ใน Parameter ) เหลือเท่าไหร่ 
{
    cout << p->name << "'s Current Money: " << p->money << "\n";
}
void PokerGame::round1()// เริ่มรอบแรกของเกม
{
    deck.shuffle(); // สับไพ่ในสำรับก่อน
    for (int i = 0; i < num_player; i++)
    {
        player[i].drawCard(deck, 2);
    } // ทุกคนยังไม่มีไพ่บนมือดังนั้นเราจะเริ่มด้วยการแจกไพ่คนละ2ใบก่อน
    while (round == 1)//เริ่มรอบแรกอย่างเป็นทางการ
    {

        Player *currentPlayer = player + turn;//เลื่อน Pointer ชี้ไปยังคนเล่นคนปัจจุบันแปรผันตาม ตัวแปร จำนวนเทิร์น
        if (currentPlayer->status == "fold") continue;// ถ้าถึงตาคนหมอบไปแล้วก็ข้ามได้เลย
        showBoard();
        showMoneyBoard();
        showMoneyBet();
        cout << currentPlayer->name << "'s Turn\n";
        showPlayerCard(currentPlayer);
        showPlayerMoney(currentPlayer);
        cout << "Enter Your Action\n";
        if (!haveBetOrAllIn)//ถ้าไม่มี Bet หรือ All in Choices ทั้งหมดที่เป็นไปได้จะมี 1.Check 2.Bet เพิ่ม 3. ALL-In 4. Fold
            cout << "1.Check\n2.Bet\n";
        else         //ถ้ามี Bet หรือ All in ไปแล้ว Choices ทั้งหมดที่เป็นไปได้จะมี 1.Call ตาม 2.Raise เพิ่มไปอีก 3. ALL-In 4. Fold
        {
            cout << "1.Call\n2.Raise\n";
        }
        cout << "3.All-In\n4.Fold\n";
        recieveOd(currentPlayer);
        if (cntCheck == num_player)
        {
            cntCheck = 0;
            turn = 0;
            haveBetOrAllIn = false;
            round++;
        }
    }
}
void PokerGame::recieveOd(Player *p)//รับคำสั่งมาก่อนว่าผู้เล่นต้องการทำอะไร ฟังชั่นนี้เราจะเช็คว่าเราจะทำคำสั่งนั้นได้หรือไม่ (ต้องผ่านเงื่อนไข ขั้นพื้นฐานก่อน)
{
    do
    {
        cout << "Input Your Choice: ";
        cin >> p->order;
        if (p->order < 1 || p->order > 4)
            cout << "Invalid Order Try Again\n";
        else if (haveBetOrAllIn && p->order == 1 && (p->money - betMoney) < 0)
            cout << "You don't have enough money to call";
        else if (haveBetOrAllIn && p->order == 2 && (p->money - betMoney) <= 0)
            cout << "You don't have enough money to raise";
    } while (p->order < 1 || p->order > 4);
    doOrder(p);
}
void PokerGame::doOrder(Player *p)//หลังจากทำได้เราจะเริ่มทำคำสั่งนั้นโดยแยกตาม ว่าคำสั่งที่ถูก Player คนนั้นสั่งนั้นเป็นอะไร
{
    if (!haveBetOrAllIn)
    {
        switch (p->order)
        {
        case 1:
            check(p);
            break;
        case 2:
            bet(p);
            break;
        case 3:
            allIn(p);
            break;
        default:
            p->status = "fold";
            break;
        }
    }
    else
    {
        switch (p->order)
        {
        case 1:
            p->status = "call";
            break;
        case 2:
            raise(p);
            break;
        case 3:
            allIn(p);
            break;
        default:
            p->status = "fold";
            break;
        }
    }
}
void PokerGame::check(Player *p){
    cntCheck++;
    p->status = "check";
}
void PokerGame::bet(Player *p)
{
    do
    {
        int od = 0;
        cout << "How much money do you want to bet?\n";
        cin >> betMoney;
        if (betMoney > p->money)
        {
            cout << "You don't have enough money\nPress 1:Try Again\nPress 2:Exit\n";
            cin >> od;
        }
        if (od == 1)
            continue;
        else if (od == 2)
        {
            recieveOd(p);
            return;
        }
        else
            cout << "Invalid Input Try Again";
    } while (betMoney > p->money);
    p->status = "bet";
    boardMoney += betMoney;
    haveBetOrAllIn = true;
    p->money -= betMoney;
}
void PokerGame::call(Player *p){
    boardMoney += p->money;
    betMoney += p->money;
    p->status = "call";
}
void PokerGame::raise(Player *p)
{
    do
    {
        cout << "How much money do you want to raise? ( > ) " << betMoney << "\n";
        cin >> betMoney;
        if (betMoney > p->money)
            cout << "You don't have enough money please try again\n";
    } while (betMoney > p->money);
    p->status = "raise";
}
void PokerGame::allIn(Player *p){
    boardMoney += p->money;
    betMoney += p->money;
    p->money = 0 ;
    p->status = "all_in";
}
void PokerGame::fold(Player *p){
    cntCheck++;
    p->status = "fold";
}
Player::Player()
{
    cout << "Enter Your name\n";
    getline(cin, name);
}
void Player::drawCard(Deck &deck, int N)
{
    for (int i = 0; i < N; i++)
    {
        card.push_back(deck.allCardLeft.back());
        deck.allCardLeft.pop_back();
        deck.cardLeft = deck.allCardLeft.size(); // change number of card left in deck
    }
}
Deck::Deck()
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            allCardLeft.push_back(ranks[i] + suits[j]);
        }
    }
}
void Deck::shuffle()
{
    random_shuffle(allCardLeft.begin(), allCardLeft.end());
}
void Deck::showCardLeft()
{
    for (int i = 0; i < cardLeft; i++)
    {
        cout << allCardLeft[i] << " ";
    }
    cout << "\n";
}
int main()
{
    int num_player = 0;
    long long int moneyRef = 0;
    drawPic();                                         // เดินเข้ามาในร้านเห็นป้ายหน้าร้าน
    recieveSimpleInformation(num_player, moneyRef);    // ถามข้อมูลพื้นฐานก่อนนำไปสร้าง BoardGame
    Player *pRef = new Player[num_player];             // สร้างผู้เล่นให้เท่ากับจำนวนคนจริงๆ // เอา Pointer ที่เก็บตัวแปร ประเภท Class มาเก็บที่อยู่ตัวแรกของ Array ที่เราได้จากการ Return ของ Dynamic Allocation แบบ Array
    Deck dRef;                                         // เตรียมสำรับไพ่ที่ยังไม่ได้สับ
    PokerGame poker(pRef, dRef, num_player, moneyRef); // เข้ามานั่งในเกมโป๊กเกอร์พร้อมที่จะเล่นเกม
    poker.round1();
}