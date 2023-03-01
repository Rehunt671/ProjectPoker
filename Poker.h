#ifndef PROJECT2_H
#define PROJECT2_H
#include "AllClass.h"
#include "CheckHand.h"
using std::cout;
using namespace std;

// void changeCard(Player *p, vector<string> deck)
// {
//     int c;
//     string needcard, thiscard;
//     bool have = false;
//     cout << "What card do you change 1 or 2 ?";
//     cin >> c;
//     c = c - 1;
//     cout << "What card do you need type ex. 3\\3 = 3\3 when \\3 = Heart , \\4 = Diamond , \\5 = Club , \\6 = Spade";
//     cin >> needcard;
//     for (int i = 0; i < deck.size(); i++)
//     {
//         if (needcard == deck[i])
//         {
//             thiscard = deck[i];
//             have = true;
//         }
//         if (!have)
//         {
//             cout << "";
//         }
//     }
//     string tempcard = p->cards[c];
//     p->cards[c] = thiscard;
//     thiscard = tempcard;
//     showUiCardHand(p->cards);
// }
// void seeCheat(vector<Player *> p){
//     int num,temp,r;
//     cout << "Which player do you want to see card ";
//     cin >> num;
//     temp = num;
//     num--;
//     r = rand()%2+1;
//     cout << "\nrandom card of player "<<temp<<" is : " <<p[num]->cards[r];
// }
// void PokerGame::cheat()
// {
//     string n = "";
//     int r, p;
//     cout << "Which one do you cheat 1.changeCard 2.seeCard : ";
//     cin >> n;
//     handleString(n);
//     p = handleString(n);
//     srand(time(0));
//     r = rand() % 100 + 1;
//     if (p == 1 && r <= 80)
//     {
//         cout << "\nYou fail to cheat";
//     }
//     else if (p == 1 && r > 80)
//     {
//         changeCard(players[current], deck.allCardsLeft);
//     }
//     else if (p == 2 && r <= 80)
//     {
//         cout << "\nYou fail to cheat";
//     }
//     else if (p == 2 && r > 80)
//     {
//         seeCheat(players);
//     }
// }
int handleString(string str)
{
    istringstream iss(str);
    int num;
    if (!(iss >> num))
    {
        return 0;
    }
    else
    {
        return num;
    }
}
string convertToLower(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}
void drawPic()
{
    cout << "\n=========================================================================================================================";
    cout << "\n                               CCCCC      A        SSSSSSSSS   IIIIIIIII  NN     NN    OOOOOOOO     ";
    cout << "\n                             CC          A  A      SS             III     NN N   NN   OO      OO    ";
    cout << "\n                            CC          A    A     SSSSSSSSS      III     NN  N  NN   OO      OO    ";
    cout << "\n                             CC        AAAAAAAA           SS      III     NN   N NN   OO      OO    ";
    cout << "\n                               CCCCC  A        A   SSSSSSSSS   IIIIIIIII  NN     NN    OOOOOOOO     ";
    cout << "\n=========================================================================================================================";
    cout << "\n================================================= Welcome to Poker Game =================================================\n";
}
void recieveSimpleInformation(int &chip, int &mandatory_betRef)
{
    string inputChoice;
    int outputChoice;
    do
    {
        cout << "How much money do you want to play(1,000 - 1,000,000): ";
        cin >> chip;
        if (chip < 500 || chip > 1000 )
            cout << "Invalid money value\n";
        cin.ignore();
    } while (chip < 500 || chip > 1000 ); // ถามจะให้มีคนละกี่บาท
    cout << "How Much Mandatory do you want to play\n";
    cout << "1.10\n2.20\n3.30\n4.40\n5.50";
    getline(cin, inputChoice);
    outputChoice = handleString(inputChoice);
    if (outputChoice == 0)
        cout << "Invalid Input try again\n";
    else if (outputChoice == 1)
        cout << "Okay!! Mandatory = 10\n";
    else if (outputChoice == 2)
        cout << "Okay!! Mandatory = 20\n";
    else if (outputChoice == 3)
        cout << "Okay!! Mandatory = 30\n";
    else if (outputChoice == 4)
        cout << "Okay!! Mandatory = 40\n";
    else if (outputChoice == 4)
        cout << "Okay!! Mandatory = 50\n";
    else
        cout << "Don't hanve " << outputChoice << " choice try again\n";
}
void PokerGame::createOrderTable()
{ // Collum 1-2

    od[1].emplace_back("call");
    od[1].emplace_back("call");
    od[1].emplace_back("check");
    od[2].emplace_back("raise");
    od[2].emplace_back("raise");
    od[2].emplace_back("bet");
    od[3].emplace_back("cheat");
    od[3].emplace_back("cheat");
    od[3].emplace_back("call");
    od[4].emplace_back("fold");
    od[4].emplace_back("all-in");
    od[4].emplace_back("raise");
    od[5].emplace_back("");
    od[5].emplace_back("fold");
    od[5].emplace_back("cheat");
    od[6].emplace_back("");
    od[6].emplace_back("");
    od[6].emplace_back("all-in");
    od[7].emplace_back("");
    od[7].emplace_back("");
    od[7].emplace_back("fold");
}
PokerGame::PokerGame(Deck &dRef, int numRef, int chipRef, int mandatory_betRef) // สร้าง 1 PokerGame ต้องมีข้อมูลพื้นฐานตาม Parameterต่อไปนี้ ตำแหน่งคนจริง(&) สำรับไพ่ จำนวนคน
{
    deck = dRef;         // กำหนด *deck ให้ตรงกับสำรับไพ่ที่เราสร้างขึ้นมา
    num_player = numRef; // กำหนดจำนวนคนของเกม Poker ของเรา
    players.emplace_back(new Player("1", 0));
    players.emplace_back(new Player("2", 0));
    players.emplace_back(new Player("3", 0));
    players.emplace_back(new Player("4", 0));
    createOrderTable();
    for (auto &p : players)
    {
        p->chip = chipRef;
    }                                    // กำหนดเงินเรียงคน
    dealer = rand() % num_player;        // สุ่มคนมาเป็น Role dealer
    current = (dealer + 3) % num_player; // คนซ้าย Big blind index ได้เริ่มก่อน;
    mandatory_bet = mandatory_betRef;    // Chip เดิมพันขั้นต่ำที่จะเล่นกัน
    pot = 0;                             // กำหนดเงินใน Board ตั้งต้น
    highestBet = 0;                      // กำหนด ว่าตอนนี้ค่าเงิน Betสูงสุดเท่าไหร่ คน Call Raise จะได้รู้
    round = 1;                           // กำหนดรอบของเกม
    restart = false;                     // กำหนดให้เป็นNew game ไม่ได้ Restart อยู่
    hasBetRaiseOrAllIn = false;          // กำหนดว่ามีการ Bet || All inไปรึยัง ถ้ามีไปแล้วจะ Check ไม่ได้แล้ว แต่ Call Raise หรือ Fold ได้
}
PokerGame::~PokerGame()
{
    for (auto &p : players)
    {
        delete p;
    }
}
void showUiCardHand(vector<string> s)
{
    string x1, x2;
    bool f[2] = {false, false};
    for (unsigned int i = 0; i < s.size(); i++)
    {
        if (s[i][0] == 'T')
        {
            s[i].replace(0, 1, "10");
            f[i] = true;
        }
    }
    x1 = s[0].substr(0, s[0].length() - 1);
    x2 = s[1].substr(0, s[1].length() - 1);

    if (!f[0] && !f[1])
    {
        cout << "\n"; // 1 1
        cout << " _ _ _ _ _      _ _ _ _ _ " << endl;
        cout << "|         |    |         |" << endl;
        cout << "|    " << x1 << "    |    |    " << x2 << "    |" << endl;
        cout << "|         |    |         |" << endl;
        cout << "|    " << s[0].back() << "    |    |    " << s[1].back() << "    |" << endl;
        cout << "|         |    |         |" << endl;
        cout << "|_ _ _ _ _|    | _ _ _ _ |" << endl;
    }

    else if (f[0] && !f[1]) // 10 1 ผ่าน
    {
        cout << "\n";
        cout << " _ _ _ _ _      _ _ _ _ _ " << endl;
        cout << "|         |    |         |" << endl;
        cout << "|    " << x1 << "   |    |    " << x2 << "    |" << endl;
        cout << "|         |    |         |" << endl;
        cout << "|    " << s[0].back() << "    |    |    " << s[1].back() << "    |" << endl;
        cout << "|         |    |         |" << endl;
        cout << "|_ _ _ _ _|    | _ _ _ _ |" << endl;
    }

    else if (!f[0] && f[1]) // 1 10 ผ่าน
    {
        cout << "\n";
        cout << " _ _ _ _ _      _ _ _ _ _ " << endl;
        cout << "|         |    |         |" << endl;
        cout << "|    " << x1 << "    |    |    " << x2 << "   |" << endl;
        cout << "|         |    |         |" << endl;
        cout << "|    " << s[0].back() << "    |    |    " << s[1].back() << "    |" << endl;
        cout << "|         |    |         |" << endl;
        cout << "|_ _ _ _ _|    | _ _ _ _ |" << endl;
    }

    else if (f[0] && f[1]) // 10 10
    {
        cout << "\n";
        cout << " _ _ _ _ _      _ _ _ _ _ " << endl;
        cout << "|         |    |         |" << endl;
        cout << "|   " << x1 << "    |    |   " << x2 << "    |" << endl;
        cout << "|         |    |         |" << endl;
        cout << "|    " << s[0].back() << "    |    |    " << s[1].back() << "    |" << endl;
        cout << "|         |    |         |" << endl;
        cout << "|_ _ _ _ _|    | _ _ _ _ |" << endl;
    }
}
void PokerGame::topboard(){

    cout << "Current Board: \n"; 
    cout << setw(30) << "                                                          Dealer                                       \n\n";
    cout << setw(30) << "                               ============================================================\n";
    cout << setw(30) << "                             //                                                            \\\\" << "\n";
    cout << setw(30) << "                            //                                                              \\\\" << "\n";
    cout << setw(30) << "                           //                                                                \\\\" << "\n";
    cout << setw(30) << "                          //                                                                  \\\\" << "\n";
    cout << setw(30) << "                         //                                                                    \\\\" << "\n";
    cout << setw(30) << "                        //                                                                      \\\\" << "\n";
    cout << setw(30) << "                       //                                                                        \\\\" << "\n";
    cout << setw(30) << "                      //                                                                          \\\\" << "\n";
    cout << setw(30) << "                     //                                                                            \\\\" << "\n\n";
}
void PokerGame::midboard0(){
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||        _ _ _ _ _    _ _ _ _ _    _ _ _ _ _    _ _ _ _ _    _ _ _ _ _         ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |_ _ _ _ _|  |_ _ _ _ _|  |_ _ _ _ _|  |_ _ _ _ _|  |_ _ _ _ _|        ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n\n";
}

void PokerGame::midboard3(){
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||        _________    _________    _________    _ _ _ _ _    _ _ _ _ _         ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |    "<<cardsOnBoard[0][0]<<"    |  |    "<<cardsOnBoard[1][0]<<"    |  |    "<<cardsOnBoard[2][0]<<"    |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |    "<<cardsOnBoard[0][1]<<"    |  |    "<<cardsOnBoard[1][1]<<"    |  |    "<<cardsOnBoard[2][1]<<"    |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |_________|  |_________|  |_________|  |_ _ _ _ _|  |_ _ _ _ _|        ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n\n";
}

void PokerGame::midboard4(){
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||        _________    _________    _________    _________    _ _ _ _ _         ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |    "<<cardsOnBoard[0][0]<<"    |  |    "<<cardsOnBoard[1][0]<<"    |  |    "<<cardsOnBoard[2][0]<<"    |  |    "<<cardsOnBoard[3][0]<<"    |  |         |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |    "<<cardsOnBoard[0][1]<<"    |  |    "<<cardsOnBoard[1][1]<<"    |  |    "<<cardsOnBoard[2][1]<<"    |  |    "<<cardsOnBoard[3][1]<<"    |  |         |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |_________|  |_________|  |_________|  |_________|  |_ _ _ _ _|        ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n\n";
}

void PokerGame::midboard5(){
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||        _________    _________    _________    _________    _________         ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |    "<<cardsOnBoard[0][0]<<"    |  |    "<<cardsOnBoard[1][0]<<"    |  |    "<<cardsOnBoard[2][0]<<"    |  |    "<<cardsOnBoard[3][0]<<"    |  |    "<<cardsOnBoard[4][0]<<"    |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |    "<<cardsOnBoard[0][1]<<"    |  |    "<<cardsOnBoard[1][1]<<"    |  |    "<<cardsOnBoard[2][1]<<"    |  |    "<<cardsOnBoard[3][1]<<"    |  |    "<<cardsOnBoard[4][1]<<"    |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |_________|  |_________|  |_________|  |_________|  |_________|        ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n\n";
}

void PokerGame::botomtboard(){
    cout << setw(30) << "                     \\\\                                                                            //\n";
    cout << setw(30) << "                      \\\\                                                                          //\n";
    cout << setw(30) << "                       \\\\                                                                        //\n";
    cout << setw(30) << "                        \\\\                                                                      //\n";
    cout << setw(30) << "                         \\\\                                                                    //\n";
    cout << setw(30) << "                          \\\\                                                                  //\n";
    cout << setw(30) << "                           \\\\                                                                //\n";
    cout << setw(30) << "                            \\\\                                                              //\n";
    cout << setw(30) << "                             \\\\                                                            //\n";
    cout << setw(30) << "                               ============================================================\n";
    cout << setw(30) << "\n";
    showMoneyPot();
    showMoneyBet();
    cout << setw(30) << "\n";
}

void PokerGame::actionboard(){
    
    cout << "player1 : " << players[0] << setw(30) << "player2 : " << players[1] << setw(30) <<"player3 : " << players[2] << setw(30) << "player4 : " << players[3] << "\n";
    cout << "money : " << players[0]->chip << setw(40) << "money : " << players[1]->chip << setw(40) << "money : " << players[2]->chip << setw(40) << "money : " << players[3]->chip << "\n";
    cout << "action : " << players[0]->action << setw(45) << "action : " << players[1]->action << setw(45) << "action : " << players[2]->action << setw(45) << "action : " << players[3]->action <<  "\n";
    cout << "\n";
}

void PokerGame::showBoard1() // Show ว่า Board preflop มีไพ่ไหนบ้างตอนนี้
{
    topboard();
    midboard0();
    botomtboard();
    actionboard();
}

void PokerGame::showBoard2() // Show ว่า Board flop มีไพ่ไหนบ้างตอนนี้
{
    topboard();
    midboard3();
    botomtboard();
    actionboard();
}

void PokerGame::showBoard3() // Show ว่า Board turn มีไพ่ไหนบ้างตอนนี้
{
    topboard();
    midboard4();
    botomtboard();
    actionboard();
}

void PokerGame::showBoard4() // Show ว่า Board river มีไพ่ไหนบ้างตอนนี้
{
    topboard();
    midboard5();
    botomtboard();
    actionboard();
}
void PokerGame::showMoneyPot() // Show ว่าเงินใน Board มีเท่าไหร่แล้ว
{
    cout << "Current Board Money: " << pot << "\n";
}
void PokerGame::showMoneyBet() // Show ว่าเงิน Bet สูงสุดตอนนี้เท่าไหร่แล้ว
{
    cout << "Current Bet Money: " << highestBet << "\n";
}
void PokerGame::showPlayerMoney(Player *p) // Showว่าเงินคนปัจจุบัน(ใน Parameter ) เหลือเท่าไหร่
{
    cout << p->name << "'s Current Money: " << p->chip << "\n";
}
void PokerGame::showPlayerCards(Player *p) // Showว่าไพ่คนปัจจุบัน(ใน Parameter ) มีอะไรบ้าง
{
    cout << p->name << "'s cards: ";
    showUiCardHand(p->cards);
    cout << "\n";
}
void PokerGame::holecards()
{
    for (size_t i = 0; i < num_player; i++)
    {
        for (size_t amount = 0; amount < 2; amount++)
        {
            players[i]->cards.emplace_back(deck.allCardsLeft.back());
            deck.allCardsLeft.pop_back();
        }
    }
}
void PokerGame::communityCards(int n)
{

    for (size_t i = 0; i < n; i++)
    {
        cardsOnBoard.emplace_back(deck.allCardsLeft.back());
        deck.allCardsLeft.pop_back();
    }
}
void PokerGame::resetAction()
{

    for (size_t i = 0; i < players.size(); i++)
    {
        if (restart)
            players[i]->action = "";
        else if (players[i]->action != "fold" && i != lastRaise)
            players[i]->action = "";
    }
}
void PokerGame::resetAccumulateBet()
{

    for (auto &p : players)
    {
        p->accumulateBet = 0;
    }
}
void PokerGame::resetHandRank()
{

    for (auto &p : players)
    {
        p->rankOfHand.first = "";
    }
}
void PokerGame::assignRole()
{
    if (restart)
    {
        dealer = (dealer + 1) % num_player;
        resetAction();
    }
    players[dealer]->role = "dealer";
    players[(dealer + 1) % num_player]->role = "small-blind";
    players[(dealer + 2) % num_player]->role = "big-blind";
}
void PokerGame::moneyForMandatoryBet(Player *s, Player *b)
{

    cout << s->name << " is Small-Blind you lost money from Mandatory-bet :" << mandatory_bet / 2 << "\n";
    s->chip -= mandatory_bet / 2;
    s->accumulateBet = mandatory_bet / 2;
    cout << b->name << " is Big-Blind you lost money from Mandatory-bet :" << mandatory_bet << "\n";
    b->chip -= mandatory_bet;
    b->accumulateBet = mandatory_bet;
    pot += (mandatory_bet + mandatory_bet / 2);
    highestBet += mandatory_bet;
}
void PokerGame::showTurn()
{
    switch (round)
    {
    case 1:
        cout << "=============================================Preflop=============================================\n";
        break;
    case 2:
        cout << "==============================================Flop===============================================\n";
        break;
    case 3:
        cout << "==============================================Turn===============================================\n";
        break;
    case 4:
        cout << "==============================================River==============================================\n";
        break;
    }
}
void PokerGame::beforeStart()
{
    deck.shuffle();                                                                               // สับไพ่ในสำรับก่อน
    assignRole();                                                                                 // จัด Role ให้ผู้เล่นให้ครบ ว่าเป็น dealer or small or big
    moneyForMandatoryBet(players[(dealer + 1) % num_player], players[(dealer + 2) % num_player]); // ก่อนแจกไพ่ต้องมีการวางเดิมพันก่อนสำหรับ small and big
    holecards();                                                                                  // ทุกคนยังไม่มีไพ่บนมือดังนั้นเราจะเริ่มด้วยการแจกไพ่คนละ2ใบก่อน
}
void PokerGame::preflop() // เริ่มรอบแรกของเกม
{
    showTurn();
    while (round == 1) // เริ่มรอบแรกอย่างเป็นทางการ
    {
        if (players[current]->action == "fold")
            continue; // เจอคนหมอบก็ข้ามได้เลย
        showBoard1();
        cout << players[current]->name << "'s Turn\n";
        showPlayerCards(players[current]);
        if (players[current]->rankOfHand.first == "")
            checkHand(players[current]);
        showHandRank(players[current]);
        showPlayerMoney(players[current]);
        cout << "Enter Your Action\n";
        showChoice();
        recieveOrder(players[current]);
        if (findWinner())
            break;
        else
        {
            updateRound();
        }
    }
}
void PokerGame::showHandRank(Player *p)
{

    cout << p->name << "'s Hand: " << p->rankOfHand.first << "\n";
    cout << p->name << "'s HandRanking: " << p->rankOfHand.second.first << "\n";
    cout << p->name << "'s MainCard: " << p->rankOfHand.second.second.first << "\n";
    cout << p->name << "'s MinorCard: " << p->rankOfHand.second.second.second << "\n";
}
bool PokerGame::findWinner()
{
    int cntFold = 0;
    for (auto &p : players)
    {
        if (p->action == "fold")
            cntFold++;
    }
    if ((round == 1 || round == 2 || round == 3) && cntFold == num_player - 1)
    { // ในรอบ preflop flop turn ถ้าเหลือคนไม่หมอบเพียงคนเดียวชนะเลย
        for (auto &p : players)
        {
            if (p->action != "fold")
            {
                cout << p->name << " Win this game!!!\n";
                cout << p->chip << "+" << pot << " = " << p->chip + pot << "\n";
                p->chip += pot;
                return true;
            }
        }
    }
    else if (round == 4)
    {
        int rankingRef = 0;
        int mainCard = 0;
        int minorCard = 0;
        for (auto &p : players)
        {
            if (p->action == "")
                return false;
        } // ยังเล่นกันไม่จบ
        for (auto &p : players)
        {
            if (p->action != "fold")
            {
                if (p->rankOfHand.second.first > rankingRef)
                    rankingRef = p->rankOfHand.second.first;
                cout << p->name << "'s cards :";
                for (const auto &c : p->cards)
                {
                    cout << c << " ";
                }
                cout << p->name << " has " << p->rankOfHand.first << "\n";
                cout << "Ranking : " << p->rankOfHand.second.first << "\n"; // 10 อันดับฃ
                cout << "MainCard : " << convertToCard(p->rankOfHand.second.second.first) << "\n";
                cout << "MinorCard : " << convertToCard(p->rankOfHand.second.second.second) << "\n";
            }
        }
        for (auto &p : players)
        {
            if (p->rankOfHand.second.first == rankingRef)
            {
                if (p->rankOfHand.second.second.first > mainCard)
                {
                    mainCard = p->rankOfHand.second.second.first;
                    if (p->rankOfHand.second.second.second > minorCard)
                        minorCard = p->rankOfHand.second.second.second;
                }
            }
            int cnt = 0;
        }
        for (auto &p : players)
        {
            if (p->rankOfHand.second.first == rankingRef && p->rankOfHand.second.second.first == mainCard && p->rankOfHand.second.second.second == minorCard)
                cout << "Congratulation!!!! " << p->name << " is a winner here\n";
            cout << "Press Enter to recieve money on board\n";
            cin.get();
            p->moneyInWeb += pot;
            cout << "Your Money = " << p->moneyInWeb;
        }
        return true;
    }

    return false;
}
void PokerGame::updateRound()
{
    for (const auto &p : players)
    {
        if (p->action == "")
        {
            current = (current + 1) % num_player;
            return;
        }
    }
    resetAction();
    resetAccumulateBet();
    resetHandRank();
    hasBetRaiseOrAllIn = false;
    round++;
}
void PokerGame::flop()
{
    showTurn();
    communityCards(3); // เปิดไพ่กองกลาง 3 ใบ
    while (round == 2) // เริ่มรอบสองอย่างเป็นทางการ
    {
        if (players[current]->action == "fold")
            continue; // เจอคนหมอบก็ข้ามได้เลย
        showBoard2();
        cout << players[current]->name << "'s Turn\n";
        showPlayerCards(players[current]);
        if (players[current]->rankOfHand.first == "")
            checkHand(players[current]);
        showHandRank(players[current]);
        showPlayerMoney(players[current]);
        cout << "Enter Your Action\n";
        showChoice();
        recieveOrder(players[current]);
        if (findWinner())
            break;
        else
        {
            updateRound();
        }
    }
}
void PokerGame::turn()
{
    showTurn();
    communityCards(1); // เปิดไพ่กองกลางเพิ่ม 1 ใบ
    while (round == 3) // เริ่มรอบสองอย่างเป็นทางการ
    {
        if (players[current]->action == "fold")
            continue; // เจอคนหมอบก็ข้ามได้เลย
        showBoard3();
        cout << players[current]->name << "'s Turn\n";
        showPlayerCards(players[current]);
        if (players[current]->rankOfHand.first == "")
            checkHand(players[current]);
        showHandRank(players[current]);
        showPlayerMoney(players[current]);
        cout << "Enter Your Action\n";
        showChoice();
        recieveOrder(players[current]);
        if (findWinner())
            break;
        else
        {
            updateRound();
        }
    }
}
void PokerGame::river()
{
    showTurn();
    communityCards(1); // เปิดไพ่กองกลางเพิ่ม 1 ใบ
    while (round == 4) // เริ่มรอบสองอย่างเป็นทางการ
    {
        if (players[current]->action == "fold")
            continue; // เจอคนหมอบก็ข้ามได้เลย
        showBoard4();
        cout << players[current]->name << "'s Turn\n";
        showPlayerCards(players[current]);
        if (players[current]->rankOfHand.first == "")
            checkHand(players[current]);
        showHandRank(players[current]);
        showPlayerMoney(players[current]);
        cout << "Enter Your Action\n";
        showChoice();
        recieveOrder(players[current]);
        if (findWinner())
            break;
        else
        {
            updateRound();
        }
    }
}
void PokerGame::showChoice()
{
    int num = 1;
    if (round == 1)
    {
        cout << num++ << ".Call\n";  // 1
        cout << num++ << ".Raise\n"; // 2
        cout << num++ << ".Cheat\n"; // 3
        cout << num++ << ".Fold\n";  // 4
    }
    else
    {

        if (!hasBetRaiseOrAllIn && round > 1)
        {

            cout << num++ << ".Check\n"; //  1
            cout << num++ << ".Bet\n";   // 2
        }
        cout << num++ << ".Call\n";   // 1,3
        cout << num++ << ".Raise\n";  // 2,4
        cout << num++ << ".Cheat\n";  // 3,5
        cout << num++ << ".All-In\n"; // 4,6
        cout << num++ << ".Fold\n";   // 5,7
    }
}

void PokerGame::recieveOrder(Player *p) // รับคำสั่งมาก่อนว่าผู้เล่นต้องการทำอะไร ฟังชั่นนี้เราจะเช็คว่าเราจะทำคำสั่งนั้นได้หรือไม่ (ต้องผ่านเงื่อนไข ขั้นพื้นฐานก่อน)
{
    const int MAX_TURN_TIME = 8000; // maximum turn time in milliseconds
    int collum = 0;
    string order = "";
    bool passTurn = false;
    bool passStage = true;
    do
    {
        passStage = true;
        cout << "Input Your Choice: ";
        // while (true)
        // {
        // auto start_time = chrono::high_resolution_clock::now();
        getline(cin, order);
        // auto end_time = chrono::high_resolution_clock::now();
        // auto duration = chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        // if (duration > MAX_TURN_TIME)
        // {
        //     cout << "Player exceeded turn time limit, skipping turn...\n";
        //     passTurn = true;
        //     break;
        // }
        // else
        //     break;
        // }
        // if (passTurn)
        //     break;
        p->order = handleString(order);
        if (hasBetRaiseOrAllIn && round > 1)
        {
            collum = 1;
        }
        else if (!hasBetRaiseOrAllIn && round > 1)
        {
            collum = 2;
        }
        auto it = od.find(p->order);
        if (it == od.end() || od[p->order][collum].empty())
        {
            cout << "Invalid Input Please Try Again\n";
            passStage = false;
        }
    } while (!passStage);
    if (passTurn)
        p->action = "fold";
    else
    {
        p->action = od[p->order][collum];
        checkOrder(p);
        doOrder(p);
    }
}
void PokerGame::checkOrder(Player *p)
{
    bool canDo = true;
    if (p->action == "call" && p->chip < (highestBet - p->accumulateBet) || p->action == "bet" && p->chip < highestBet || p->action == "raise" && p->chip <= (highestBet - p->accumulateBet))
        canDo = false;
    if (!canDo)
    {
        cout << "Your money isn't enough to " << p->action << " please try again\n";
        recieveOrder(p);
        return;
    }
}
void PokerGame::doOrder(Player *p) // หลังจากทำได้เราจะเริ่มทำคำสั่งนั้นโดยแยกตาม ว่าคำสั่งที่ถูก Player คนนั้นสั่งนั้นเป็นอะไร
{
    if (p->action == "check")
        check(p);
    else if (p->action == "bet")
    {
        bet(p);
    }
    else if (p->action == "call")
        call(p);
    else if (p->action == "raise")
    {
        raise(p);
    }
    /* else if (p->action == "cheat")
    {
        cheat(p);
    } */
    else if (p->action == "all-in")
    {
        allIn(p);
    }
    else
    {
        fold(p);
    }
}

void PokerGame::check(Player *p)
{
    p->action = "check";
}
void PokerGame::bet(Player *p)
{
    string accBet = "";
    string od = "";
    int subOrder = 0;
    do
    {

        cout << "How much money do you want to bet?\n";
        getline(cin, accBet);
        p->accumulateBet = handleString(accBet);
        if (p->accumulateBet > p->chip || p->accumulateBet < highestBet)
        {
            if (p->moneyToRaise > p->chip)
                cout << "You don't have enough money to bet\n";
            else
                cout << "Bet money can't  < highestBet value or string input\n";
            cout << "Press 1:Try Again\nPress 2:Exit\n";
            getline(cin, od);
            subOrder = handleString(od);
            switch (subOrder)
            {
            case 1:
                continue;
                break;
            case 2:
                recieveOrder(p);
                return;
                break;
            default:
                cout << "Invalid input please input bet money again\n";
                break;
            }
        }
    } while (p->accumulateBet > p->chip || p->accumulateBet < highestBet || p->accumulateBet == 0);
    updateLastBetRaiseOrAllIn(p);
    resetAction();
    pot += p->accumulateBet;
    p->chip -= p->accumulateBet;
    highestBet = p->accumulateBet;
    p->action = "bet";
    hasBetRaiseOrAllIn = true;
}
void PokerGame::call(Player *p)
{
    pot += (highestBet - p->accumulateBet);
    p->chip -= (highestBet - p->accumulateBet);
    p->accumulateBet = highestBet;
    // highestBet เท่าเดิม
}
void PokerGame::updateLastBetRaiseOrAllIn(Player *p)
{
    for (size_t i = 0; i < players.size(); i++)
    {
        if (players[i]->name == p->name)
            lastRaise = i;
    }
}
void PokerGame::raise(Player *p)
{
    string moneyRaise = "";
    string od = "";
    int subOrder = 0;
    do
    {
        cout << "How much money do you want to raise?\n";
        getline(cin, moneyRaise);
        p->moneyToRaise = handleString(moneyRaise);
        if ((highestBet - p->accumulateBet) + p->moneyToRaise > p->chip || p->moneyToRaise == 0)
        {
            if ((highestBet - p->accumulateBet) + p->moneyToRaise > p->chip)
                cout << "You don't have enough money to raise\n";
            else
                cout << "Raise money can't be 0 or string input\n";
            cout << "Press 1:Input again\nPress 2:Exit\n";
            getline(cin, od);
            subOrder = handleString(od);
            switch (subOrder)
            {
            case 1:
                continue;
            case 2:
                recieveOrder(p);
                return;
            default:
                cout << "Invalid input please input raise money again\n";
                break;
            }
        }
    } while ((highestBet - p->accumulateBet) + p->moneyToRaise > p->chip || p->moneyToRaise == 0);
    updateLastBetRaiseOrAllIn(p);
    resetAction();
    pot += ((highestBet - p->accumulateBet) + p->moneyToRaise);
    p->chip -= ((highestBet - p->accumulateBet) + p->moneyToRaise);
    highestBet += p->moneyToRaise;
    p->accumulateBet = highestBet;
    p->action = "raise";
    hasBetRaiseOrAllIn = true;
}
void PokerGame::allIn(Player *p)
{
    updateLastBetRaiseOrAllIn(p);
    resetAction();
    pot += p->chip;
    highestBet = max(highestBet, p->chip);
    p->accumulateBet = p->chip;
    p->chip = 0;
    p->action = "all-in";
    hasBetRaiseOrAllIn = true;
}
void PokerGame::fold(Player *p)
{
    p->action = "fold";
}
Player::Player(string name, long long int moneyInWeb) : name(name), moneyInWeb(moneyInWeb)
{
    action = "";
    role = "";
    accumulateBet = 0;
    order = 1;
}
Deck::Deck()
{
    for (const auto &r : ranks)
    {
        for (const auto &s : suits)
        {
            allCardsLeft.emplace_back(string(1, r) + string(1, s));
        }
    }
}
void Deck::shuffle()
{
    random_shuffle(allCardsLeft.begin(), allCardsLeft.end());
}
void Deck::showcardsLeft()
{
    for (const auto &c : allCardsLeft)
    {
        cout << c << " ";
    }
    cout << "\n";
}

#endif