#ifndef PROJECT_H
#define PROJECT_H
#include <iostream>
#include <iomanip> //design
#include <fstream> //read and write data
#include <string>
#include <algorithm>     //sort
#include <vector>        //vector
#include <utility>       //vector pair
#include <set>           //not include same element
#include <unordered_map> //mapscards
#include <map>           //map
#include <chrono> //time
#include <thread> //time
using namespace std;
using namespace std::chrono;
using std::cin;
using std::cout;
class Deck
{
private:
    char ranks[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    char suits[4] = {'\3', '\4', '\5', '\6'};

public:
    Deck();
    ~Deck();
    vector<string> allCardsLeft; // ไพ่ใน Deck ที่เหลือ ณ ตอนนั้น
    void reset();
    void shuffle();       // สับไพ่
    void showcardsLeft(); // Show cards ที่เหลือ
};
class Player
{
public:
    Player(string, string, string, int,int);
    ~Player();
    pair<string, int> handRanking;
    pair<int, int> cardRanking;
    vector<int> kicker;
    vector<int> flushRank;
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
};
class Database
{
private:
    string filename;

public:
    Database();
    ~Database();
    map<pair<string, string>, vector<string>> userDatabase; //[username,password] displayname money
    unsigned long long int resetTime;                       // เพิ่มใน Database
    void registerUser();
    void setDisplayName(string &); // ใช้ตอนสมัครเท่านั้น
    void loginUser(vector<Player *> &, int &);
    void writeData2_txt(); // เขียนข้อมูลจาก Map To ไฟล์หลัก ใช้ตอน REGISTER
    void fixData2_txt(pair<string, string>, string, string, string, string);
    void appendData2_txt(pair<string, string>, string, string, string, string);
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
    vector<string> cardsOnBoard; // ไพ่บนBoard
    int num_player;
    int current;   // position
    int lastRaise; // position
    int dealer;    // position
    int round;
    int minChip;
    int mandatoryBet;
    int pot;        // เงินใน Board รวม
    int highestBet; // เงินเดิมพันสูงสุด ณ ตอนนี้resetAccumulateBet
    bool cleanIncludeLastRaise;
    bool hasBetRaiseOrAllIn;

public:
    PokerGame(Database &, vector<Player *> &, Deck &, int, int);
    ~PokerGame();
    map<int, vector<string>> od;
    void createPlayer(const int);
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
    // AfterDesign
    void assignRole();
    void showMoneyPot();
    void showMoneyBet();
    void showActionChoice();
    void showPlayerCards(Player *);
    void showPlayerHandRank(Player *);
    void showPlayerAccumulateBet(Player *);
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
    void summarizeTheGame(vector<Player *> &, const int, int, int, vector<int> &, int);
    void riskPrize(Player *p, const int);
    void resetGame();
    void endGameLogic();
    bool restart;
};

// Declaration
void recieveSimpleInformation(int &, int &);
string convertToCard(int);
void showUiCardHand(vector<string>);
void changeCard(Player *p, vector<string> &deck);
void seeCheat(Player *p, vector<Player *> players);
void convertFrontToNumber(vector<string> &v);
void showprize();
void clearInput();
int handleString(string);
/// Definition
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input
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
#endif
