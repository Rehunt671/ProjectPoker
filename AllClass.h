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
    string filename = "DataLN&RG.txt";

public:
    map<pair<string, string>, vector<string>> userDatabase; //[username,password] displayname money
    vector<int> loginIndex;
    vector<string> un;
    vector<string> pw;
    vector<string> displayname;
    vector<string> money;
    void registerUser();
    void loginUser(vector<int> &);
    void writeData2_txt();     // เขียนข้อมูลจาก Map To ไฟล์หลัก ใช้ตอน REGISTER
    void importDatafromfile(); // นำข้อมูลจาก File หลักมาเก็บข้อมูลไว้ใน Vector แต่ละอัน พร้อมกับสร้าง Mapขึ้นมาทันที ใช้ตอน Login
    // ถ้าต้องการแก้ไข Concept คือ ImportDataFromfile แล้ว ไล่แก้ ข้อมูลให้ตรงกับ Index นั้นๆแล้วนำเวกเตอร์ 4 อันนำมาสร้างแมพแล้ว ส่งกลับขึ้นไปยังไฟล์หลัก
    void Delete_();
    // เพิ่มเติม
    void setDisplayName();
};
class PokerGame
{
private:
    vector<string> cardsOnBoard; // ไพ่บนBoard
    int num_player;
    int current;   // position
    int lastRaise; // position
    int dealer;    // position
    int round;
    int mandatory_bet;
    int pot;        // เงินใน Board รวม
    int highestBet; // เงินเดิมพันสูงสุด ณ ตอนนี้resetAccumulateBet
    bool restart;
    bool cleanIncludeLastRaise;
    bool hasBetRaiseOrAllIn;

public:
    PokerGame(Database &, Deck &, int, int, int);
    ~PokerGame();
    vector<Player *> players;
    Database pokerDB;
    Deck deck;
    map<int, vector<string>> od;
    void showTurn();
    void createOrderTable();
    void topboard();
    void midboard0();
    void midboard3();
    void midboard4();
    void midboard5();
    void botomtboard();

    void showBoard1();
    void showBoard2();
    void showBoard3();
    void showBoard4();
    void actionboard2();
    void actionboard3();
    void actionboard4();
    void setactionboard();
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
    void checkOrder(Player *);
    void doOrder(Player *);
    void updateLastBetRaiseOrAllIn(Player *);
    void check(Player *);
    void bet(Player *);
    void call(Player *);
    // void cheat(Player *p);
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
};
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
void clearInput()
{
    cin.clear();
    cin.ignore(10000, '\n');
}
#endif
