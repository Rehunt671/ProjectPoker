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
    Player(string, long long int);
    pair<std::string, std::vector<int>> rankOfHand; // ประกอบไปด้วย (ชนิดของไพ่บนมือ,{ไพ่สูงสุด,ไพ่รองคู่สูงสุด})
    string name;                                    // ชื่อคนเล่น
    long long int moneyInWeb;                       // เงินในระบบ
    int chip;                                       // เงินในเกม
    int moneyToRaise;                               // เงินที่ Raise เพิ่มจาก Bet สูงสุด ณ ตอนนั้น
    int accumulateBet;                              // เงินที่เราลงเดิมพันไปแล้ว
    vector<string> cards;                           // การ์ดบนมือเรา มี 2 ใบ
    string action;                                  // การกระทำของเรา ณ ตอนนั้น Call Raise Bet Fold Cheat etc.
    string role;                                    // ตำแหน่งของเรา dealer ,Small Blind, Big Blind
    int order;                                      // คำสั่งของเรา
};
class PokerGame
{
private:
    vector<string> cardsOnBoard = {"A\4","Q\4","K\4","J\4","T\4"}; // ไพ่บนBoard
    int num_player;
    int current;   // position
    int lastRaise; // position
    int dealer;    // position
    int round;
    int mandatory_bet;
    int pot;        // เงินใน Board รวม
    int highestBet; // เงินเดิมพันสูงสุด ณ ตอนนี้resetAccumulateBet
    bool restart;
    bool hasBetRaiseOrAllIn;

public:
    PokerGame(Deck &, int, int, int);
    ~PokerGame();
    vector<Player *> players;
    Deck deck;
    map<int, vector<string>> od;
    void showTurn();
    void createOrderTable();
    void showBoard();
    void showMoneyPot();
    void showMoneyBet();
    void showPlayerMoney(Player *);
    void showPlayerCards(Player *);
    void showHandRank(Player *p);
    void holecards();
    void communityCards(int);
    void checkHand(Player *p);
    void showChoice();
    void recieveOrder(Player *);
    void checkOrder(Player *);
    void doOrder(Player *);
    void updateLastBetRaiseOrAllIn(Player *p);
    void check(Player *);
    void bet(Player *);
    void call(Player *);
    void raise(Player *);
    void allIn(Player *);
    void fold(Player *);
    void assignRole();
    void resetAction();
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
};
#endif