#ifndef PROJECT3_H
#define PROJECT3_H
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
            break;
        }
        if (i == deck.size() - 1 && !have)
        {
            cout << "Unlucky Y^Y you select card that don't exist in deck\n";
            return;
        }
    }
    string tempcard = p->cards[c];
    p->cards[c] = needcard;
    needcard = tempcard;
    cout << "This is your hand now:\n";
    showUiCardHand(p->cards);
    p->rankOfHand.first == ""; // resetRankOfHand
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

void recieveSimpleInformation(int &moneyInGame, int &mandatory_betRef)
{
    int choice;
    do
    {
        cout << "How much money do you want to play(500 - 1,000): ";
        cin >> moneyInGame;
        if (moneyInGame < 500 || moneyInGame > 1000)
        {
            clearInput();
            cout << "Invalid money value\n";
        }
    } while (moneyInGame < 500 || moneyInGame > 1000); // ถามจะให้มีคนละกี่บาท
    cout << "How Much Mandatory do you want to play\n";
    cout << "1.10\n2.20\n3.30\n4.40\n5.50\n";
    cin >> choice;
    switch (choice)
    {
    case 1:
        mandatory_betRef = 10;
        break;
    case 2:
        mandatory_betRef = 20;
        break;
    case 3:
        mandatory_betRef = 30;
        break;
    case 4:
        mandatory_betRef = 40;
        break;
    case 5:
        mandatory_betRef = 50;
        break;
    default:
        clearInput();
        cout << "Don't have input choice try again\n";
        break;
    }
    cout << "Okay!! Mandatory = " << mandatory_betRef << "\n";
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
PokerGame::PokerGame(Database &dbRef, Deck &dRef, int numRef, int chipRef, int mandatory_betRef) // สร้าง 1 PokerGame ต้องมีข้อมูลพื้นฐานตาม Parameterต่อไปนี้ ตำแหน่งคนจริง(&) สำรับไพ่ จำนวนคน
{
    pokerDB = dbRef;
    deck = dRef;         // กำหนด *deck ให้ตรงกับสำรับไพ่ที่เราสร้างขึ้นมา
    num_player = numRef; // กำหนดจำนวนคนของเกม Poker ของเรา
    createPlayer();
    createOrderTable();
    for (auto &p : players)
    {
        p->chip = chipRef;
    }                                    // กำหนดเงินเรียงคน
    mandatory_bet = mandatory_betRef;    // Chip เดิมพันขั้นต่ำที่จะเล่นกัน
    current = (dealer + 3) % num_player; // คนซ้าย Big blind index ได้เริ่มก่อน;
    dealer = rand() % num_player;        // สุ่มคนมาเป็น Role dealer
    pot = 0;                             // กำหนดเงินใน Board ตั้งต้น
    highestBet = 0;                      // กำหนด ว่าตอนนี้ค่าเงิน Betสูงสุดเท่าไหร่ คน Call Raise จะได้รู้
    round = 1;                           // กำหนดรอบของเกม
    restart = false;                     // กำหนดให้เป็นNew game
    cleanIncludeLastRaise = true;
    hasBetRaiseOrAllIn = false; // กำหนดว่ามีการ Bet || All inไปรึยัง ถ้ามีไปแล้วจะ Check ไม่ได้แล้ว แต่ Call Raise หรือ Fold ได้
}
PokerGame::~PokerGame()
{
    for (auto &p : players)
    {
        delete p;
    }
}

void PokerGame::createPlayer()
{
    string pw;      // ไม่จำเป็นต้องเอาตัวแปรมารับก็ได้แต่ ทำไว้เผื่อทวน
    string dp;      // ไม่จำเป็นต้องเอาตัวแปรมารับก็ได้แต่ ทำไว้เผื่อทวน
    int moneyInWeb; // ไม่จำเป็นต้องเอาตัวแปรมารับก็ได้แต่ ทำไว้เผื่อทวน
    for (auto &user : pokerDB.loginUserName)
    {
        for (const auto &element : pokerDB.userDatabase) //[username,password]
        {
            if (user == element.first.first)
            {
                pw = element.first.second;
                dp = element.second[0];
                moneyInWeb = stoi(element.second[1]);
                players.emplace_back(new Player(user, pw, dp, moneyInWeb));
            }
        } // เช็คว่าซ้ำไหม
    }
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
void PokerGame::showMoneyPot() // Show ว่าเงินใน Board มีเท่าไหร่แล้ว
{
    cout << "Pot: " << pot << "\n";
}
void PokerGame::showMoneyBet() // Show ว่าเงิน Bet สูงสุดตอนนี้เท่าไหร่แล้ว
{
    cout << "Highest Bet Money: " << highestBet << "\n";
}
void PokerGame::showPlayerMoney(Player *p) // Showว่าเงินคนปัจจุบัน(ใน Parameter ) เหลือเท่าไหร่
{
    cout << p->name << "'s Current Money: " << p->chip << "\n";
}
void PokerGame::showPlayerCards(Player *p) // Showว่าไพ่คนปัจจุบัน(ใน Parameter ) มีอะไรบ้าง
{
    cout << p->name << "'s Cards:\n";
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
void PokerGame::resetAction(bool cleanIncludeLastRaise)
{

    for (size_t i = 0; i < players.size(); i++)
    {
        if (restart) // ลบหมดลบทั้งหมอบด้วย
            players[i]->action = "";
        else if (players[i]->action != "fold" && players[i]->action != "dead" && cleanIncludeLastRaise) // ลบทั้งคน LastRaise แต่ไม่รวมหมอบและคนตาย เป็นการรีเซตที่มีการเปลี่ยนรอบ
            players[i]->action = "";
        else if (players[i]->action != "fold" && players[i]->action != "dead" && i != lastRaise) // ลบแค่คนอื่นที่ไม่ใช่ LastRaise และ หมอบ และ คนตาย เป็นการรีเซตที่ยังอยู่ในรอบนั้นๆ
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
        resetAction(cleanIncludeLastRaise);
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
void PokerGame::showPlayerAccumulateBet(Player *p)
{
    cout << p->name << "'s AccumulateBet = " << p->accumulateBet << "\n";
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
        if (players[current]->action == "fold" || players[current]->action == "dead")
        {
            updateRound();
            continue; // เจอคนหมอบหรือคนตายก็ข้ามได้เลย
        }
        showBoard1();
        cout << players[current]->name << "'s Turn\n";
        showPlayerCards(players[current]);
        if (players[current]->rankOfHand.first == "")
            checkHand(players[current]);
        showHandRank(players[current]);
        showPlayerMoney(players[current]);
        showPlayerAccumulateBet(players[current]);
        showActionChoice();
        recieveOrder(players[current]);
        if (findWinner())
        {
            exit(0);
            break;
        }
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
    cout << p->name << "'s MainCard: " << convertToCard(p->rankOfHand.second.second.first) << "\n";
    cout << p->name << "'s MinorCard: " << convertToCard(p->rankOfHand.second.second.second) << "\n";
}
bool PokerGame::findWinner()
{
    int cntFold = 0;
    for (auto &p : players)
    {
        if (p->action == "fold" || p->action == "dead")
            cntFold++;
    }
    if ((round == 1 || round == 2 || round == 3) && cntFold == num_player - 1)
    { // ในรอบ preflop flop turn ถ้าเหลือคนไม่หมอบเพียงคนเดียวชนะเลย
        for (auto &p : players)
        {
            if (p->action != "fold" && p->action != "dead")
            {
                cout << p->name << " Win this game!!!\n";
                cout << p->chip << " + " << pot << " = " << p->chip + pot << "$\n";
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
        } // ยังไม่จบรอบนั้นๆ
        for (auto &p : players)
        {
            if (p->action != "fold" && p->action != "dead")
            {
                if (p->rankOfHand.second.first > rankingRef)
                    rankingRef = p->rankOfHand.second.first; // หา Ranking ไพ่สูงสุด 1-10ว่าคนที่ไม่หมอบคนไหนสูงสุด
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
        } // หาเรียบร้อยแล้วว่าคนไหนที่ไม่หมอบมี อันดับสูงสุด
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
            p->chip += pot;
            cout << "Your Money = " << p->chip;
        }
        return true;
    }

    return false;
}
void PokerGame::updateRound()
{
    if (players[current]->action == "cheat")
        return;                   // ถ้าคนปัจจุบันเลือก choice cheat ก็ยังต้องเล่นอีกรอบ
    for (const auto &p : players) // ถ้ามีคนยังไม่ได้เล่นก็ให้เล่นต่อไป
    {
        if (p->action == "")
        {
            current = (current + 1) % num_player;
            return;
        }
    }
    resetAction(cleanIncludeLastRaise);
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
        if (players[current]->action == "fold" || players[current]->action == "dead")
        {
            updateRound();
            continue; // เจอคนหมอบก็ข้ามได้เลย
        }
        showBoard2();
        cout << players[current]->name << "'s Turn\n";
        showPlayerCards(players[current]);
        if (players[current]->rankOfHand.first == "")
            if (players[current]->action == "fold")
            {
                updateRound();
                continue; // เจอคนหมอบก็ข้ามได้เลย
            }
        checkHand(players[current]);
        showHandRank(players[current]);
        showPlayerMoney(players[current]);
        showPlayerAccumulateBet(players[current]);
        showActionChoice();
        recieveOrder(players[current]);
        if (findWinner())
        {
            exit(0);
            break;
        }
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
        if (players[current]->action == "fold" || players[current]->action == "dead")
        {
            updateRound();
            continue; // เจอคนหมอบก็ข้ามได้เลย
        }
        showBoard3();
        cout << players[current]->name << "'s Turn\n";
        showPlayerCards(players[current]);
        if (players[current]->rankOfHand.first == "")
            checkHand(players[current]);
        showHandRank(players[current]);
        showPlayerMoney(players[current]);
        showPlayerAccumulateBet(players[current]);
        showActionChoice();
        recieveOrder(players[current]);
        if (findWinner())
        {
            exit(0);
            break;
        }
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
        if (players[current]->action == "fold" || players[current]->action == "dead")
        {
            updateRound();
            continue; // เจอคนหมอบก็ข้ามได้เลย
        }
        showBoard4();
        cout << players[current]->name << "'s Turn\n";
        showPlayerCards(players[current]);
        if (players[current]->rankOfHand.first == "")
            checkHand(players[current]);
        showHandRank(players[current]);
        showPlayerMoney(players[current]);
        showPlayerAccumulateBet(players[current]);
        showActionChoice();
        recieveOrder(players[current]);
        if (findWinner())
        {
            exit(0);
            break;
        }
        else
        {
            updateRound();
        }
    }
}
void PokerGame::showActionChoice()
{
    int num = 1;
    cout << "Enter Your Action\n";
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
    const int MAX_TURN_TIME = 100000; // maximum turn time in milliseconds
    string testAction;
    int collum = 0;
    int order = 0;
    bool forceFold = false;
    bool passStage = true;
    do
    {
        passStage = true;
        while (true)
        {
            cout << "Input Your Choice\n";
            auto start_time = chrono::high_resolution_clock::now();
            cin >> order;
            cin.ignore(100, '\n'); // เอาที่เหลือจากเว้นวรรคแรกลบออกหมดจนกว่าจะเจอ'\n'
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
            if (duration > MAX_TURN_TIME)
            {
                cout << "Player exceeded turn time limit, skipping turn...\n";
                p->action = "fold";
                forceFold = true;
                return;
            }
            else if (!cin.fail())
            {
                p->order = order;
                break;
            }
            else
            {
                clearInput();
            }
        }
        if (hasBetRaiseOrAllIn && round > 1)
        {
            collum = 1;
        }
        else if (!hasBetRaiseOrAllIn && round > 1)
        {
            collum = 2;
        }
        auto it = od.find(p->order);
        if (it == od.end() || od[p->order][collum].empty()) // ไม่มี or หาไม่เจอ
        {
            cout << "Invalid Input Please Try Again\n";
            passStage = false;
        }
    } while (!passStage);
    testAction = od[p->order][collum];
    if (checkOrder(p, testAction))
    {
        p->action = testAction;
        doOrder(p);
    }
}
bool PokerGame::checkOrder(Player *p, string testAction)
{

    if (testAction == "call" && p->chip < (highestBet - p->accumulateBet) || testAction == "bet" && p->chip < highestBet || testAction == "raise" && p->chip <= (highestBet - p->accumulateBet))

    {
        cout << "Your money isn't enough to " << p->action << " please try again\n";
        recieveOrder(p);
        return false;
    }
    else if (p->action == "cheat" && testAction == "cheat")
    {
        cout << "You're already cheat try again next turn\n";
        recieveOrder(p);
        return false;
    }
    return true;
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
    else if (p->action == "cheat")
    {
        cheat(p);
    }
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
                clearInput();
                cout << "Invalid input please input bet money again\n";
                break;
            }
        }
    } while (p->accumulateBet > p->chip || p->accumulateBet < highestBet || p->accumulateBet == 0);
    updateLastBetRaiseOrAllIn(p);
    resetAction(!cleanIncludeLastRaise);
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
    p->action = "call";
    // highestBet เท่าเดิม
}
void PokerGame::updateLastBetRaiseOrAllIn(Player *p)
{
    for (size_t i = 0; i < players.size(); i++)
    {
        if (players[i]->username == p->username) // ใช้เป็น Username เพราะไม่มีทางซ้ำ
            lastRaise = i;
    }
}
void PokerGame::raise(Player *p)
{
    string moneyRaise;
    string od = "";
    int subOrder = 0;
    do
    {
        cout << "How much money do you want to raise?\n";
        getline(cin, moneyRaise);
        p->moneyToRaise = handleString(moneyRaise);
        cout << p->moneyToRaise;
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
                break;
            case 2:
                recieveOrder(p);
                return;
            default:
                clearInput();
                cout << "Invalid input please input raise money again\n";
                break;
            }
        }
    } while ((highestBet - p->accumulateBet) + p->moneyToRaise > p->chip || p->moneyToRaise == 0);
    updateLastBetRaiseOrAllIn(p);
    resetAction(!cleanIncludeLastRaise);
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
    resetAction(!cleanIncludeLastRaise);
    pot += p->chip;
    highestBet = max(highestBet, p->chip);
    p->accumulateBet = p->chip;
    p->chip = 0;
    p->action = "all-in";
    hasBetRaiseOrAllIn = true;
}
void PokerGame::cheat(Player *p)
{
    int r = rand() % 100, deadRate, choice;
    do
    {
        cout << "Which one do you want to cheat\n1.Change card in hand\n2.See other player's card\n";
        cin >> choice;
        if ((choice == 1 || choice == 2) && r < 50)
        {
            cout << "You fail to cheat\n";
            p->action = "cheat";
            deadRate = rand() % 100;
            if (deadRate < 50)
            {
                cout << "Other player notice you cheat!!!\n";
                cout << "Bang!! Bang!! Bang!!\n";
                cout << "You're Dead\n";
                p->action = "dead";
            }
        }
        else if (choice == 1)
        {
            changeCard(p, deck.allCardsLeft);
            p->action = "cheat";
        }
        else if (choice == 2)
        {
            seeCheat(p, players);
            p->action = "cheat";
        }
        else
        {
            clearInput();
        }
    } while (choice != 1 && choice != 2);
}
void PokerGame::fold(Player *p)
{
    p->action = "fold";
}
Player::Player(string username, string password, string name, int moneyInWeb) : username(username), password(password), name(name), moneyInWeb(moneyInWeb)
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
