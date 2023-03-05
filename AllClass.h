#ifndef PROJECT_H
#define PROJECT_H
#include <iostream>
#include <iomanip> //design
#include <fstream> //read and write data
#include <string>
#include <cstring>       //convert string to c string
#include <algorithm>     //sort
#include <vector>        //vector
#include <utility>       //vector pair
#include <set>           //not include same element
#include <unordered_map> //mapscards
#include <map>           //map
#include <chrono>        //time
#include <thread>        //time
using namespace std;
using namespace std::chrono;
using std::cout;
struct Deck
{
private:
    char ranks[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    char suits[4] = {'\3', '\4', '\5', '\6'};

public:
    Deck();
    vector<string> allCardsLeft; // ไพ่ใน Deck ที่เหลือ ณ ตอนนั้น
    void shuffle();              // สับไพ่
    void showcardsLeft();        // Show cards ที่เหลือ
};
struct Player
{
public:
    Player(string, string, string, int);
    pair<string, pair<int, pair<int, int>>> rankOfHand; // ประกอบไปด้วย (Rankไพ่บนมือ(String),{Rank(int1-10),{ไพ่สูงสุดMainCard,ไพ่รองคู่สูงสุดMinorCard}})
    // vector<int> allOfFlushCards;
    string username;
    string password; //
    string name;     // ชื่อคนเล่น
    int moneyInWeb;
    int chip;             // เงินในเกม
    int moneyToRaise;     // เงินที่ Raise เพิ่มจาก Bet สูงสุด ณ ตอนนั้น
    int accumulateBet;    // เงินที่เราลงเดิมพันไปแล้ว
    vector<string> cards; // การ์ดบนมือเรา มี 2 ใบ
    string action;        // การกระทำของเรา ณ ตอนนั้น Call Raise Bet Fold Cheat etc.
    string role;          // ตำแหน่งของเรา dealer ,Small Blind, Big Blind
    int order;            // คำสั่งของเรา
    bool operator<(const Player *other) const
    {
        return rankOfHand.second.first < other->rankOfHand.second.first;
    }
};
class Database
{
private:
    string filename;

public:
    Database();
    ~Database();
    map<pair<string, string>, vector<string>> userDatabase; //[username,password] displayname money
    vector<string> loginUserName;                           // [username,password]
    unsigned long long int resetTime;                       // เพิ่มใน Database
    void registerUser();
    void setDisplayName(string &); // ใช้ตอนสมัครเท่านั้น
    void loginUser();
    void writeData2_txt();     // เขียนข้อมูลจาก Map To ไฟล์หลัก ใช้ตอน REGISTER
    void importDatafromfile(); // นำข้อมูลจาก File หลักมาเก็บข้อมูลไว้ใน Vector แต่ละอัน พร้อมกับสร้าง Mapขึ้นมาทันที ใช้ตอน Login
    void Delete_();
    // time
    void dailyPrize(const string &, const string &);
    void reset(int &, unsigned long long int &);
    unsigned long long int setResetTime();
};
class PokerGame
{
private:
    vector<Player *> players;
    Database pokerDB;
    Deck deck;
    vector<string> cardsOnBoard ; // ไพ่บนBoard
    int num_player;
    int current;   // position
    int lastRaise; // position
    int dealer;    // position
    int round;
    int mandatory_bet;
    int pot;        // เงินใน Board รวม
    int highestBet; // เงินเดิมพันสูงสุด ณ ตอนนี้resetAccumulateBet
    bool cleanIncludeLastRaise;
    bool hasBetRaiseOrAllIn;

public:
    PokerGame(Database &, Deck &, int, int, int);
    ~PokerGame();
    map<int, vector<string>> od;
    void createPlayer();
    void createOrderTable();
    void showTurn();
    void topboard();
    void midboard0();
    void midboard3();
    void midboard4();
    void midboard5();
    void botomboard();
    void showBoard1();
    void showBoard2();
    void showBoard3();
    void showBoard4();
    void actionboard2();
    void actionboard3();
    void actionboard4();
    void setActionboard();
    void showMoneyPot();
    void showMoneyBet();
    void showPlayerAccumulateBet(Player *);
    void showPlayerMoney(Player *);
    void showPlayerCards(Player *);
    void showHandRank(Player *);
    void showActionChoice();
    void holecards();
    void communityCards(int);
    void checkHand(Player *);
    void recieveOrder(Player *);
    bool checkOrder(Player *, string);
    void doOrder(Player *);
    void updateLastBetRaiseOrAllIn(Player *);
    void check(Player *);
    void bet(Player *);
    void call(Player *);
    void cheat(Player *p);
    void raise(Player *);
    void allIn(Player *);
    void fold(Player *);
    void assignRole();
    void resetAction(bool);
    void resetHandRank();
    void resetAccumulateBet();
    void moneyForMandatoryBet(Player *, Player *);
    bool findWinner();
    void updateRound();
    void beforeStart();
    void preflop();
    void flop();
    void turn();
    void river();
    void updateLastestChip(string);
    bool restart;
};
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input
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

        cout << " _ _ _ _ _      _ _ _ _ _ " << endl;
        cout << "|         |    |         |" << endl;
        cout << "|   " << x1 << "    |    |   " << x2 << "    |" << endl;
        cout << "|         |    |         |" << endl;
        cout << "|    " << s[0].back() << "    |    |    " << s[1].back() << "    |" << endl;
        cout << "|         |    |         |" << endl;
        cout << "|_ _ _ _ _|    | _ _ _ _ |" << endl;
    }
}
void changeCard(Player *p, vector<string> &deck)
{
    int c;
    string needcard;
    bool have = false;
    do
    {
        cout << "What card do you change 1 or 2 ?\n";
        cin >> c;
        if (c != 1 && c != 2)
            clearInput();
    } while (c != 1 && c != 2);
    c -= 1;
    cout << "What card do you need (Press Alt+3,4,5,6 to type Symbol \3 \4 \5 \6) Ex. K\3,3\6,A\4 \n";
    cin >> needcard;
    for (int i = 0; i < deck.size(); i++)
    {
        if (needcard == deck[i])
        {
            have = true;
            string tempcard = p->cards[c];
            p->cards[c] = needcard;
            deck[i] = tempcard;
            cout << "This is your hand now:\n";
            showUiCardHand(p->cards);
            p->rankOfHand.first = ""; // resetRankOfHand
            break;
        }
        if (i == deck.size() - 1 && !have)
        {
            cout << "Unlucky Y^Y you select card that don't exist in deck\n";
            return;
        }
    }
}
void seeCheat(Player *p, vector<Player *> players)
{
    int num, r;
    do
    {
        cout << "Which player do you want to see card [1],[2],[3],[4]\n";
        cin >> num;
        if (num >= 1 && num <= 4 && players[num - 1]->username == p->username)
            cout << "Can't watch yourself card!!\n";
        else if (num < 1 || num > players.size() - 1 || cin.fail())
        {
            clearInput();
            cout << "Invalid index of player try again\n";
        }
    } while (players[num - 1]->username == p->username || num < 1 || num > players.size() - 1 || cin.fail());
    num--;
    r = rand() % 2;
    cout << "\nrandom card of player " << num + 1 << " is : " << players[num]->cards[r] << "\n";
}
string convertToCard(int max)
{
    map<int, string> maxVar;
    maxVar[14] = "A";
    maxVar[13] = "K";
    maxVar[12] = "Q";
    maxVar[11] = "J";
    maxVar[10] = "10";
    for (int i = 9; i > 1; i--)
    {
        maxVar[i] = to_string(i);
    }
    maxVar[0] = "";
    if (maxVar.count(max) > 0) // กัน return bad behavior
        return maxVar[max];
    return 0;
}
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

/// /////////////////////////////////////////////////////////////////Design/////////////////////////////////////////////////////////////////////////////////////
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
void PokerGame::topboard()
{

    cout << "Current Board: \n";
    cout << setw(30) << "                                                          Dealer                                       \n\n";
    cout << setw(30) << "                               ============================================================\n";
    cout << setw(30) << "                             //                                                            \\\\"
         << "\n";
    cout << setw(30) << "                            //                                                              \\\\"
         << "\n";
    cout << setw(30) << "                           //                                                                \\\\"
         << "\n";
    cout << setw(30) << "                          //                                                                  \\\\"
         << "\n";
    cout << setw(30) << "                         //                                                                    \\\\"
         << "\n";
    cout << setw(30) << "                        //                                                                      \\\\"
         << "\n";
    cout << setw(30) << "                       //                                                                        \\\\"
         << "\n";
    cout << setw(30) << "                      //                                                                          \\\\"
         << "\n";
    cout << setw(30) << "                     //                                                                            \\\\"
         << "\n\n";
}
void PokerGame::midboard0()
{
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

void PokerGame::midboard3()
{
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||        _________    _________    _________    _ _ _ _ _    _ _ _ _ _         ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |    " << cardsOnBoard[0][0] << "    |  |    " << cardsOnBoard[1][0] << "    |  |    " << cardsOnBoard[2][0] << "    |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |    " << cardsOnBoard[0][1] << "    |  |    " << cardsOnBoard[1][1] << "    |  |    " << cardsOnBoard[2][1] << "    |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |_________|  |_________|  |_________|  |_ _ _ _ _|  |_ _ _ _ _|        ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n\n";
}

void PokerGame::midboard4()
{
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||        _________    _________    _________    _________    _ _ _ _ _         ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |    " << cardsOnBoard[0][0] << "    |  |    " << cardsOnBoard[1][0] << "    |  |    " << cardsOnBoard[2][0] << "    |  |    " << cardsOnBoard[3][0] << "    |  |         |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |    " << cardsOnBoard[0][1] << "    |  |    " << cardsOnBoard[1][1] << "    |  |    " << cardsOnBoard[2][1] << "    |  |    " << cardsOnBoard[3][1] << "    |  |         |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |_________|  |_________|  |_________|  |_________|  |_ _ _ _ _|        ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n\n";
}

void PokerGame::midboard5()
{
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||        _________    _________    _________    _________    _________         ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |    " << cardsOnBoard[0][0] << "    |  |    " << cardsOnBoard[1][0] << "    |  |    " << cardsOnBoard[2][0] << "    |  |    " << cardsOnBoard[3][0] << "    |  |    " << cardsOnBoard[4][0] << "    |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |    " << cardsOnBoard[0][1] << "    |  |    " << cardsOnBoard[1][1] << "    |  |    " << cardsOnBoard[2][1] << "    |  |    " << cardsOnBoard[3][1] << "    |  |    " << cardsOnBoard[4][1] << "    |        ||\n";
    cout << setw(30) << "                    ||       |         |  |         |  |         |  |         |  |         |        ||\n";
    cout << setw(30) << "                    ||       |_________|  |_________|  |_________|  |_________|  |_________|        ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n";
    cout << setw(30) << "                    ||                                                                              ||\n\n";
}

void PokerGame::botomboard()
{
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
    cout << "\n";
    showMoneyPot();
    showMoneyBet();
    cout << "\n";
}
void PokerGame::actionboard2()
{

    cout << left << "player1 : ";
    cout.width(23);
    cout << players[0]->name;
    cout << left << "player2 : ";
    cout.width(23);
    cout << players[1]->name << "\n";
    cout << left << "money : ";
    cout.width(25);
    cout << players[0]->chip;
    cout << left << "money : ";
    cout.width(25);
    cout << players[1]->chip << "\n";
    cout << left << "action : ";
    cout.width(24);
    cout << players[0]->action;
    cout << left << "action : ";
    cout.width(24);
    cout << players[1]->action << "\n";
    cout << "\n";
}

void PokerGame::actionboard3()
{

    cout << left << "player1 : ";
    cout.width(23);
    cout << players[0]->name;
    cout << left << "player2 : ";
    cout.width(23);
    cout << players[1]->name;
    cout << left << "player3 : ";
    cout.width(23);
    cout << players[2]->name << "\n";
    cout << left << "money : ";
    cout.width(25);
    cout << players[0]->chip;
    cout << left << "money : ";
    cout.width(25);
    cout << players[1]->chip;
    cout << left << "money : ";
    cout.width(25);
    cout << players[2]->chip << "\n";
    cout << left << "action : ";
    cout.width(24);
    cout << players[0]->action;
    cout << left << "action : ";
    cout.width(24);
    cout << players[1]->action;
    cout << left << "action : ";
    cout.width(24);
    cout << players[2]->action << "\n";
    cout << "\n";
}

void PokerGame::actionboard4()
{

    cout << left << "player1 : ";
    cout.width(23);
    cout << players[0]->name;
    cout << left << "player2 : ";
    cout.width(23);
    cout << players[1]->name;
    cout << left << "player3 : ";
    cout.width(23);
    cout << players[2]->name;
    cout << left << "player4 : ";
    cout.width(24);
    cout << players[3]->name << "\n";
    cout << left << "money : ";
    cout.width(25);
    cout << players[0]->chip;
    cout << left << "money : ";
    cout.width(25);
    cout << players[1]->chip;
    cout << left << "money : ";
    cout.width(25);
    cout << players[2]->chip;
    cout << left << "money : ";
    cout.width(20);
    cout << players[3]->chip << "\n";
    cout << left << "action : ";
    cout.width(24);
    cout << players[0]->action;
    cout << left << "action : ";
    cout.width(24);
    cout << players[1]->action;
    cout << left << "action : ";
    cout.width(24);
    cout << players[2]->action;
    cout << left << "action : ";
    cout.width(19);
    cout << players[3]->action << "\n";
    cout << "\n";
}

void PokerGame::setActionboard()
{
    if (num_player == 2)
        actionboard2();
    else if (num_player == 3)
        actionboard3();
    else if (num_player == 4)
        actionboard4();
}

void PokerGame::showBoard1() // Show ว่า Board preflop มีไพ่ไหนบ้างตอนนี้
{
    topboard();
    midboard0();
    botomboard();
    setActionboard();
}

void PokerGame::showBoard2() // Show ว่า Board flop มีไพ่ไหนบ้างตอนนี้
{
    topboard();
    midboard3();
    botomboard();
    setActionboard();
}

void PokerGame::showBoard3() // Show ว่า Board turn มีไพ่ไหนบ้างตอนนี้
{
    topboard();
    midboard4();
    botomboard();
    setActionboard();
}

void PokerGame::showBoard4() // Show ว่า Board river มีไพ่ไหนบ้างตอนนี้
{
    topboard();
    midboard5();
    botomboard();
    setActionboard();
}

#endif
