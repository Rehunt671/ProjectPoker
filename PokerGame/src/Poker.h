#ifndef PROJECT4_H
#define PROJECT4_H
void recieveSimpleInformation(int &minChip, int &mandatoryBetRef)
{
    int choice;
    do
    {
        cout << "How much minChip do you want to set\n";
        cout << "[1]$500\n[2]$800\n[3]$1000\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            minChip = 500;
            break;
        case 2:
            minChip = 800;
            break;
        case 3:
            minChip = 1000;
            break;
        default:
            clearInput();
            cout << "Don't have input choice try again\n";
            break;
        }
    } while (choice != 1 && choice != 2 && choice != 3);
    do
    {
        cout << "How Much Mandatory do you want to play\n";
        cout << "1.10\n2.20\n3.30\n4.40\n5.50\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            mandatoryBetRef = 10;
            break;
        case 2:
            mandatoryBetRef = 20;
            break;
        case 3:
            mandatoryBetRef = 30;
            break;
        case 4:
            mandatoryBetRef = 40;
            break;
        case 5:
            mandatoryBetRef = 50;
            break;
        default:
            clearInput();
            cout << "Don't have input choice try again\n";
            break;
        }
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5);
    cout << "Okay!! Mandatory = " << mandatoryBetRef << "\n";
}
void PokerGame::createOrderTable()
{ // Collum 1-2

    od[1].emplace_back("call");
    od[1].emplace_back("check");
    od[2].emplace_back("raise");
    od[2].emplace_back("bet");
    od[3].emplace_back("cheat");
    od[3].emplace_back("cheat");
    od[4].emplace_back("all-in");
    od[4].emplace_back("all-in");
    od[5].emplace_back("fold");
    od[5].emplace_back("fold");
}

PokerGame::PokerGame(Database &pokerDB, vector<Player *> &players, Deck &deck, int minChip, int mandatoryBet) // สร้าง 1 PokerGame ต้องมีข้อมูลพื้นฐานตาม Parameterต่อไปนี้ ตำแหน่งคนจริง(&) สำรับไพ่ จำนวนคน
{
    this->pokerDB = pokerDB;
    this->deck = deck; // กำหนด *deck ให้ตรงกับสำรับไพ่ที่เราสร้างขึ้นมา
    this->players = players;
    this->num_player = players.size(); // กำหนดจำนวนคนของเกม Poker ของเรา
    this->minChip = minChip;
    this->mandatoryBet = mandatoryBet; // Chip เดิมพันขั้นต่ำที่จะเล่นกัน
    createOrderTable();
    pot = 0;         // กำหนดเงินใน Board ตั้งต้น
    highestBet = 0;  // กำหนด ว่าตอนนี้ค่าเงิน Betสูงสุดเท่าไหร่ คน Call Raise จะได้รู้
    round = 1;       // กำหนดรอบของเกม
    restart = false; // กำหนดให้เป็นNew game
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
void PokerGame::showMoneyPot() // Show ว่าเงินใน Board มีเท่าไหร่แล้ว
{
    cout << "Pot: " << pot << "\n";
}
void PokerGame::showMoneyBet() // Show ว่าเงิน Bet สูงสุดตอนนี้เท่าไหร่แล้ว
{
    cout << "Highest Bet Money: " << highestBet << "\n";
}
void PokerGame::showPlayerCards(Player *p) // Showว่าไพ่คนปัจจุบัน(ใน Parameter ) มีอะไรบ้าง
{
    cout << p->name << "'s Cards:\n";
    showUiCardHand(p->cards);
    cout << "\n";
}
void PokerGame::holecards()
{
    for (size_t i = 0; i < num_player; i++) // ใช้ size_t เนื่องจากเป็นการบอกว่าเป็น size หรือ index และใช้เพื่อ represent largest value ของ object นั้นๆ
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
        if (players[i]->action != "all-in" && players[i]->action != "fold" && players[i]->action != "dead" && cleanIncludeLastRaise) // ลบทั้งคน LastRaise แต่ไม่รวมหมอบและคนตาย เป็นการรีเซตที่มีการเปลี่ยนรอบ
            players[i]->action = "";
        else if (players[i]->action != "all-in" && players[i]->action != "fold" && players[i]->action != "dead" && i != lastRaise) // ลบแค่คนอื่นที่ไม่ใช่ LastRaise และ หมอบ และ คนตาย เป็นการรีเซตที่ยังอยู่ในรอบนั้นๆ
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
        p->handRanking.first = "";
    }
}
void PokerGame::assignRole()
{
    if (players.size() == 2)
    {
        players[0]->role = "small-blind";
        players[1]->role = "big-blind";
        dealer = 1;
    }
    else
    {
        dealer = rand() % num_player;
        players[dealer]->role = ""; // จริงๆไม่ต้องมีก็ได้
        players[(dealer + 1) % num_player]->role = "small-blind";
        players[(dealer + 2) % num_player]->role = "big-blind";
    }
}
void PokerGame::moneyForMandatoryBet(Player *s, Player *b)
{

    cout << s->name << " is Small-Blind you lost money from Mandatory-bet :" << mandatoryBet / 2 << "\n";
    s->chip -= mandatoryBet / 2;
    s->accumulateBet = mandatoryBet / 2;
    cout << b->name << " is Big-Blind you lost money from Mandatory-bet :" << mandatoryBet << "\n";
    b->chip -= mandatoryBet;
    b->accumulateBet = mandatoryBet;
    pot += (mandatoryBet + mandatoryBet / 2);
    highestBet += mandatoryBet;
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
void PokerGame::showPlayerHandRank(Player *p)
{
    string num = "1";
    string back = "";
    int rankOfcard = p->cardRanking.first;
    int temp = 0;
    cout << p->name << "'s Hand: " << p->handRanking.first << "\n";
    cout << p->name << "'s HandRanking: " << p->handRanking.second << "\n"; // 10 อันดับ ใกล้ 1 สูงสุด
    cout << p->name << "'s MainCard: " << convertToCard(p->cardRanking.first) << "\n";
    if (p->handRanking.first != "Flush" && p->handRanking.first != "Straight" && p->handRanking.first != "StraightFlush" && p->handRanking.first != "RoyalFlush")
    {
        if (p->handRanking.first == "FullHouse" || p->handRanking.first == "TwoPair")
            cout << p->name << "'s MinorCard: " << convertToCard(p->cardRanking.second) << "\n";
    }
    else
    {
        for (size_t i = 0; i < 5; i++)
        {
            switch (num.back())
            {
            case '1':
                back = "st";
                break;
            case '2':
                back = "nd";
                break;
            case '3':
                back = "rd";
                break;

            default:
                back = "th";
                break;
            }
            if (p->handRanking.first == "Flush")
                cout << "Rank of card " << num + back << ": " << convertToCard(p->flushRank[i]) << "\n";
            else if (p->handRanking.first == "Straight" || p->handRanking.first == "StraightFlush")
            {
                cout << "Rank of card " << num + back << ": " << convertToCard(rankOfcard--) << "\n";
            }
            else if (p->handRanking.first == "RoyalFlush")
            {
                for (int i = 14; i > 9; i--)
                {
                    cout << "Rank of card " << num + back << ": " << convertToCard(i) << "\n";
                }
            }
            temp = stoi(num);
            temp++;
            num = to_string(temp);
        }
    }
}
void PokerGame::showPlayerAccumulateBet(Player *p)
{
    cout << p->name << "'s AccumulateBet = " << p->accumulateBet << "\n";
}
void PokerGame::beforeStart()
{
    deck.shuffle(); // สับไพ่ในสำรับก่อน
    assignRole();   // จัด Role ให้ผู้เล่นให้ครบ ว่าเป็น dealer or small or big
    holecards();    // ทุกคนยังไม่มีไพ่บนมือดังนั้นเราจะเริ่มด้วยการแจกไพ่คนละ2ใบก่อน
    if (players.size() > 2)
    {
        current = (dealer + 3) % num_player;  //ถัดจาก big blind 
        moneyForMandatoryBet(players[(dealer + 1) % num_player], players[(dealer + 2) % num_player]); // ก่อนแจกไพ่ต้องมีการวางเดิมพันก่อนสำหรับ small and big
    }
    else
    {
        current = (dealer + 1) % num_player;  //small  blind                                                // เอา small blind เล่นก่อน
        moneyForMandatoryBet(players[(dealer + 1) % num_player], players[(dealer) % num_player]); // ก่อนแจกไพ่ต้องมีการวางเดิมพันก่อนสำหรับ small and big
    }
}
void PokerGame::preflop() // เริ่มรอบแรกของเกม
{
    showTurn();
    while (round == 1) // เริ่มรอบแรกอย่างเป็นทางการ
    {
        if (players[current]->action == "all-in" || players[current]->action == "fold" || players[current]->action == "dead")
        {
            updateRound();
            continue; // เจอคนหมอบก็ข้ามได้เลย
        }
        showBoard1();
        showPlayerCards(players[current]);
        if (players[current]->handRanking.first == "")
        {
            checkHand(players[current]);
        }
        showPlayerHandRank(players[current]);
        showActionChoice();
        recieveOrder(players[current]);
        if (findWinner())
        {
            endGameLogic();
            break;
        }
        else
        {
            updateRound();
        }
    }
}

void PokerGame::flop()
{
    showTurn();
    communityCards(3); // เปิดไพ่กองกลาง 3 ใบ
    while (round == 2) // เริ่มรอบสองอย่างเป็นทางการ
    {
        if (players[current]->action == "all-in" || players[current]->action == "fold" || players[current]->action == "dead")
        {
            updateRound();
            continue; // เจอคนหมอบก็ข้ามได้เลย
        }
        showBoard2();
        cout << players[current]->name << "'s Turn\n";
        showPlayerCards(players[current]);
        if (players[current]->handRanking.first == "")
            checkHand(players[current]);
        showPlayerHandRank(players[current]);
        showActionChoice();
        recieveOrder(players[current]);
        if (findWinner())
        {
            endGameLogic();
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
        if (players[current]->action == "all-in" || players[current]->action == "fold" || players[current]->action == "dead")
        {
            updateRound();
            continue; // เจอคนหมอบก็ข้ามได้เลย
        }
        showBoard3();
        cout << players[current]->name << "'s Turn\n";
        showPlayerCards(players[current]);
        if (players[current]->handRanking.first == "")
            checkHand(players[current]);
        showPlayerHandRank(players[current]);
        showActionChoice();
        recieveOrder(players[current]);
        if (findWinner())
        {
            endGameLogic();
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
        if (players[current]->action == "all-in" || players[current]->action == "fold" || players[current]->action == "dead")
        {
            updateRound();
            continue; // เจอคนหมอบก็ข้ามได้เลย
        }
        showBoard4();
        cout << players[current]->name << "'s Turn\n";
        showPlayerCards(players[current]);
        if (players[current]->handRanking.first == "")
            checkHand(players[current]);
        showPlayerHandRank(players[current]);
        showActionChoice();
        recieveOrder(players[current]);
        if (findWinner())
        {
            endGameLogic();
            break;
        }
        else
        {
            updateRound();
        }
    }
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
            cout << "PRESS ENTER TO CONTINUE\n";
            cin.get();
            return;
        }
    }
    resetAction(cleanIncludeLastRaise);
    resetAccumulateBet();
    resetHandRank();
    current = (dealer + 1) % num_player; // small Blind
    highestBet = 0;
    hasBetRaiseOrAllIn = false;
    round++;
}
void PokerGame::summarizeTheGame(vector<Player *> &allWinner, const int rankingRef, int mainCard, int minorCard, vector<int> &kicker, int cntWin)
{

    cout << "---------------------------------------------------------------------------------\n";
    cout << "HighestHand = " << findRankInStr(rankingRef) << "\n";
    cout << "HighestHandRanking = " << rankingRef << "\n";
    cout << "HighestMainCard: " << convertToCard(mainCard) << "\n";
    if (rankingRef == 4 || rankingRef == 8) // Fullhouse or TwoPair
    {
        cout << "HighestMinorCard: " << convertToCard(minorCard) << "\n";
    }
    else
    {
        string num = "1";
        string back = "";
        int temp = 0;
        for (size_t i = 0; i < 5; i++)
        {
            switch (num.back())
            {
            case '1':
                back = "st";
                break;
            case '2':
                back = "nd";
                break;
            case '3':
                back = "rd";
                break;

            default:
                back = "th";
                break;
            }
            if (rankingRef == 5)
                cout << "Rank of card " << num + back << ": " << convertToCard(allWinner[0]->flushRank[i]) << "\n";
            else if (rankingRef == 2 || rankingRef == 6)
            {
                cout << "Rank of card " << num + back << ": " << convertToCard(mainCard) << "\n";
                mainCard--;
            }
            else if (rankingRef == 1)
            {
                for (int i = 14; i > 9; i--)
                {
                    cout << "Rank of card " << num + back << ": " << convertToCard(i) << "\n";
                }
            }
            temp = stoi(num);
            temp++;
            num = to_string(temp);
        }
    }
    cout << "KickerCard 1st = " << convertToCard(kicker[0]) << "\n";
    cout << "KickerCard 2nd = " << convertToCard(kicker[1]) << "\n";
    cout << "-----------------------We have " << cntWin << " player win-----------------------\n";
    for (auto &p : allWinner)
    {
        riskPrize(p, cntWin);
    }
}
void PokerGame::endGameLogic()
{
    int chipToStore = 0;
    char input = '\0';
    int order;
    int suborder;
    for (int i = players.size() - 1; i >= 0; i--)
    {
        if (players[i]->action == "dead")
        {
            cout << players[i]->username << " body was taken away. . .\n";
            pokerDB.userDatabase.erase(make_pair(players[i]->username, players[i]->password)); // delete account at that key
            delete players[i];
            players.erase(players.begin() + i);
            players.shrink_to_fit();
        }
        if ((players[i]->moneyInWeb + players[i]->chip) < minChip) // มีเงินไม่มากพอ
        {
            cout << players[i]->name << " don't have enough chip to play knockout!!\n";
            delete players[i];
            players.erase(players.begin() + i);
            players.shrink_to_fit();
        } // มีเงินมากพอ
        else
        {
            cout << players[i]->name << " you want to restart with " << players.size() << " max remaining player? (Y = yes , N = no)\n";
            cin >> input;
            if (input == 'Y' || input == 'y')
            {
                if (players[i]->chip >= minChip)
                {
                    chipToStore = players[i]->chip - minChip; // เงินมากก็เก็บ
                    players[i]->chip = minChip;
                    pokerDB.userDatabase[make_pair(players[i]->username, players[i]->password)][1] = to_string(players[i]->moneyInWeb + chipToStore);
                }
                else
                {
                    players[i]->chip = minChip; // เงินน้อยก็ดึงจากเว็บ
                    pokerDB.userDatabase[make_pair(players[i]->username, players[i]->password)][1] = to_string(players[i]->moneyInWeb - (minChip - players[i]->chip));
                }
            }
            else
            {
                clearInput();
                pokerDB.userDatabase[make_pair(players[i]->username, players[i]->password)][1] = to_string(players[i]->moneyInWeb + players[i]->chip);
                delete players[i];
                players.erase(players.begin() + i);
                players.shrink_to_fit();
            }
        }
    }
    pokerDB.writeData2_txt();
    cout << "================================================Important!!!! If you want to exit this game just press [X] if not the game will continue ==================================================\n";
    cin >> input;
    if (input == 'X' || input == 'x')
        exit(0);
    else
    {
        clearInput();
        if (players.size() < 2)
        {
            cout << ". . . Players don't have enough to restart . . .\n. . . . . . . Waiting for another player . . . . . . .\n";
            do
            {
                cout << "[1] Login [2] Register\n";
                cin >> order;
                switch (order)
                {
                case 1:
                    pokerDB.loginUser(players, minChip);
                    break;
                case 2:
                    pokerDB.registerUser();
                    continue;
                    break;
                default:
                    clearInput();
                    break;
                }
                if (players.size() == 4)
                    break;
                cout << "Do you guy want to waiting for another player?\n[1] Yes [2] No\n";
                cin >> suborder;
            } while (suborder == 1 || players.size() < 2);
            restart = 1;
        }
        else
            restart = 1;
    }
}
void filterHighestRank(vector<Player *> &allWinner, const int rankingRef)
{
    for (int i = allWinner.size() - 1; i >= 0; i--)
    {

        if (allWinner[i]->handRanking.second != rankingRef)
            allWinner.erase(allWinner.begin() + i);
    }
}
void filterWinnerFlush(vector<Player *> &allWinner, int &mainCard)
{
    int cardIndex = 0; // เรารู้อยู่แล้วว่า index มันถูกเรียงจากมากไปน้อยเทียบตัวมากก่อน
    int cardMaxValue = 0;
    if (allWinner.size() == 1)
    {
        mainCard = allWinner[0]->flushRank[0];
    }
    else
    {
        while (cardIndex <= 4)
        {
            for (int i = allWinner.size() - 1; i > 0; i++)
            {
                cardMaxValue = allWinner[i]->flushRank[cardIndex]; // เอาตัวหลักเป็นด้านหลังสุดเทียบมาด้านหน้า 1 index
                if (cardMaxValue > allWinner[i - 1]->flushRank[cardIndex])
                {
                    if (cardIndex == 0)
                    {
                        mainCard = cardMaxValue;
                    }
                    else
                        mainCard = allWinner[i - 1]->flushRank[cardIndex];
                    allWinner.erase(allWinner.begin() + (i - 1)); // ถ้าตัวเรามากกว่าลบตัวหน้า
                }
                else if (cardMaxValue < allWinner[i - 1]->flushRank[cardIndex])
                    allWinner.erase(allWinner.begin() + i); // ถ้าตัวเค้ามากกว่าลบตัวเราแทน
            }
            cardIndex++;
        }
    }
}
void changeKicker(int rankingRef, vector<int> &kicker, Player *p)
{
    if (rankingRef != 1 && rankingRef != 2 && rankingRef != 4 && rankingRef != 6)
    {
        kicker[0] = p->kicker[0];
        kicker[1] = p->kicker[1];
    }
}
void checkGreaterKicker(int rankingRef, vector<int> &kicker, Player *p)
{
    if (p->kicker[0] >= kicker[0])
    {
        if (p->kicker[0] > kicker[0])
            changeKicker(rankingRef, kicker, p);
        else
        {
            if (p->kicker[1] > kicker[1])
                kicker[1] = p->kicker[1];
        }
    }
}
void filterWinnerNormal(vector<Player *> &allWinner, const int rankingRef, int &mainCard, int &minorCard, vector<int> &kicker)
{
    for (auto &p : allWinner)
    {
        if (p->cardRanking.first >= mainCard)
        {
            if (p->cardRanking.first > mainCard)
            {
                mainCard = p->cardRanking.first;
                minorCard = p->cardRanking.second;
                changeKicker(rankingRef, kicker, p);
            }
            else
            {
                if (p->cardRanking.second >= minorCard && rankingRef != 1 && rankingRef != 2 && rankingRef != 6) // คนที่มีการ์ดรองมากกว่าถึงจะมีสิทธิเปลี่ยนไพ่ kicker
                {
                    if (p->cardRanking.second > minorCard)
                    {
                        minorCard = p->cardRanking.second;
                        changeKicker(rankingRef, kicker, p);
                    }
                    else
                        checkGreaterKicker(rankingRef, kicker, p);
                }
            }
        }
    }
    for (int i = allWinner.size() - 1; i >= 0; i--)
    {

        if (allWinner[i]->cardRanking.first == mainCard && allWinner[i]->cardRanking.second == minorCard && allWinner[i]->kicker[0] == kicker[0] && allWinner[i]->kicker[1] == kicker[1])
            ;
        else
        {
            allWinner.erase(allWinner.begin() + i);
        }
    }
}
bool PokerGame::findWinner()
{
    vector<Player *> allWinner;
    int cntAllin = 0;
    int cntKnockout = 0;
    int cntWin = 0;
    int finalMoney = pot;
    for (auto &p : players)
    {
        if (p->action == "")
            return false;
    } // ยังไม่จบรอบนั้นๆ
    ////////////////////////////////////มาถึงตรงนี้ได้แปลว่ามี Action กันหมดทุกคนแล้ว
    for (auto &p : players)
    {
        if (p->action == "all-in")
            cntAllin++;
        else if (p->action == "fold" || p->action == "dead")
            cntKnockout++;
        if (p->action != "fold" && p->action != "dead")
            allWinner.emplace_back(p); // หาคนที่มีสิทธิชนะ
    }
    if (allWinner.size() == 1) // แปลว่า หมอบหนีหรือตาย จนเหลือเราคนเดียว
    {
        cntWin = 1;
        riskPrize(allWinner[0], cntWin);
        return true;
    }
    else if (round == 4 || cntAllin + cntKnockout == num_player) // รอบสี่ต้องเปิดไพ่ หรือ ทุกคน All in มาหมดก็ต้องเปิดไพ่เช่นกัน
    {
        int rankingRef = 10; // ต้องน้อยสุดเข้าใกล้  1
        int mainCard = 0;    // ต้องมากสุดเข้าใกล้ 14
        int minorCard = 0;   // ต้องมากสุดเข้าใกล้ 14
        vector<int> kicker(2, 0);
        switch (round)
        {
        case 1:
            showBoard1();
            break;
        case 2:
            showBoard2();
            break;
        case 3:
            showBoard3();
            break;
        default:
            showBoard4();
            break;
        }
        cout << "------------------------------------------------Okay!!! reveal all player hand------------------------------------------------\n";
        for (auto &p : allWinner)
        {
            showPlayerCards(p);
            showPlayerHandRank(p);
            if (p->handRanking.second < rankingRef) // เก็บ Rankของคนที่ไม่หมอบกับตาย เอาอันที่เข้าใกล้ 1 สุด
                rankingRef = p->handRanking.second;
        }
        if (cntAllin + cntKnockout == num_player)
        {
            do
            {
                if (cardsOnBoard.size() < 5)
                {
                    cout << "------------------------------------------------Draw Another Board Card!!!------------------------------------------------\n";
                    if (cardsOnBoard.size() == 0)
                        communityCards(3);
                    else
                        communityCards(1);
                    switch (cardsOnBoard.size())
                    {
                    case 3:
                        showBoard2();
                        break;
                    case 4:
                        showBoard3();
                        break;
                    default:
                        showBoard4();
                        break;
                    }
                }
                cout << "------------------------------------------------Okay!!! let's see rank of all player hand------------------------------------------------\n";
                for (auto &p : allWinner)
                {
                    showPlayerCards(p);
                    p->handRanking.first = "";
                    p->kicker[0] = 0;
                    p->kicker[1] = 0; // Set kicker ใหม่
                    checkHand(p);
                    showPlayerHandRank(p);
                    if (p->handRanking.second < rankingRef) // เก็บ Rankของคนที่ไม่หมอบกับตาย เอาอันที่เข้าใกล้ 1 สุด
                        rankingRef = p->handRanking.second;
                }
            } while (cardsOnBoard.size() < 5);
        }
        /////After Show player hand ranking
        filterHighestRank(allWinner, rankingRef);
        switch (rankingRef)
        {
        case 5:
            filterWinnerFlush(allWinner, mainCard);
            break;

        default:
            filterWinnerNormal(allWinner, rankingRef, mainCard, minorCard, kicker);
            break;
        }
        cntWin = allWinner.size();
        summarizeTheGame(allWinner, rankingRef, mainCard, minorCard, kicker, cntWin);
        return true;
    }
    return false; // ถ้ามาถึงจุดนี้ได้แปลว่า false แล้ว
}
void PokerGame::riskPrize(Player *p, const int cntWin)
{
    char c;
    int r;
    int finalPot = pot / cntWin;
    cout << "Congratulation!!!! " << p->name << " is a winner here\n";
    showprize(pot);
    cout << "Do you want to play risk prize?(Press Y = Yes , Other = No)\nWARNING !!!!! This prize is make your pot more or lower than you get now!!. " << endl;
    cin >> c;
    r = rand() % 100 + 1;
    if (c == 'y' || c == 'Y')
    {
        if (r <= 20)
            finalPot *= 0.5;
        else if (r > 20 && r <= 40)
            finalPot *= 0.8;
        else if (r > 40 && r <= 80)
            finalPot *= 1;
        else if (r > 80 && r <= 90)
            finalPot *= 1.2;
        else if (r > 90 && r <= 95)
            finalPot *= 1.5;
        else if (r > 95 && r <= 100)
            finalPot *= 2;
        if (pot > finalPot)
            cout << "Unlucky pot decresed from " << pot / cntWin << " to " << finalPot << endl;
        else if (pot == finalPot)
            cout << "your pot still remain the same\n";
        else
            cout << "You're so lucky pot increase from " << pot / cntWin << " to " << finalPot << endl;
        cout << "Press Enter to recieve money on board";
        cin.ignore();
        cin.get();
    }
    else
    {
        clearInput();
        cout << "You didn't play risk prize your pot remains the same" << endl;
        cout << "Your winner pot is = " << finalPot << endl;
    }
    p->chip += finalPot;
    cout << p->name << "'s chip = " << p->chip << "\n";
    cout << "=========================================================================================" << endl;
}
void PokerGame::updateLastBetRaiseOrAllIn(Player *p)
{
    for (size_t i = 0; i < players.size(); i++)
    {
        if (players[i]->username == p->username) // ใช้เป็น Username เพราะไม่มีทางซ้ำ
            lastRaise = i;
    }
}
void PokerGame::showActionChoice()
{
    int num = 1;
    cout << "Enter Your Action\n";
    if (round == 1)
    {
        cout << num++ << ".Call\n";
        cout << num++ << ".Raise\n";
        cout << num++ << ".Cheat\n";
        cout << num++ << ".All-In\n";
        cout << num++ << ".Fold\n";
    }
    else
    {

        if (!hasBetRaiseOrAllIn)
        {

            cout << num++ << ".Check\n";
            cout << num++ << ".Bet\n";
        }
        else
        {
            cout << num++ << ".Call\n";
            cout << num++ << ".Raise\n";
        }
        cout << num++ << ".Cheat\n";
        cout << num++ << ".All-In\n";
        cout << num++ << ".Fold\n";
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
        if (!hasBetRaiseOrAllIn && round > 1)
        {
            collum = 1;
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
        cout << "Your money isn't enough to " << testAction << " please try again\n";
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
        if (p->accumulateBet > p->chip || p->accumulateBet < highestBet || p->accumulateBet <= 0)
        {

            if (p->accumulateBet > p->chip)
                cout << "You don't have enough money to bet\n";
            else
                cout << "Bet money can't  <= highestBet value or string input\n";
            cout << "Press 1:Try Again\nPress 2:Exit\n";
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
                clearInput();
                cout << "Invalid input please input bet money again\n";
                continue;
            }
        }
    } while (p->accumulateBet > p->chip || p->accumulateBet < highestBet || p->accumulateBet == 0);
    updateLastBetRaiseOrAllIn(p);
    resetAction(!cleanIncludeLastRaise);
    pot += p->accumulateBet;
    p->chip -= p->accumulateBet;
    highestBet = p->accumulateBet;
    if (p->chip == 0)
        p->action = "all-in";
    else
        p->action = "bet";
    hasBetRaiseOrAllIn = true;
}

void PokerGame::call(Player *p)
{
    pot += (highestBet - p->accumulateBet);
    p->chip -= (highestBet - p->accumulateBet);
    p->accumulateBet = highestBet;
    if (p->chip == 0)
        p->action = "all-in";
    else
        p->action = "call";
    // highestBet เท่าเดิม
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
    if (p->chip == 0)
        p->action = "all-in";
    else
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
            p->handRanking.first = ""; // resetRankOfHand
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
void PokerGame::fold(Player *p)
{
    p->action = "fold";
}
void PokerGame::resetGame()
{
    deck.reset();
    cardsOnBoard.clear();
    cardsOnBoard.shrink_to_fit();
    num_player = players.size();
    lastRaise = 0;
    round = 1;
    pot = 0;
    highestBet = 0;
    hasBetRaiseOrAllIn = false;
    cleanIncludeLastRaise = true;

    for (auto &p : players)
    {
        p->handRanking.first = "";
        p->handRanking.second = 0;
        p->cardRanking.first = 0;
        p->cardRanking.second = 0;
        p->kicker.clear();
        p->flushRank.clear();
        p->cards.clear();
        p->kicker.shrink_to_fit();
        p->flushRank.shrink_to_fit();
        p->cards.shrink_to_fit();
        p->kicker.emplace_back(0);
        p->kicker.emplace_back(0);
        p->moneyToRaise = 0;
        p->accumulateBet = 0;
        p->action = "";
        p->role = "";
        p->order = 0;
    }
}
Player::Player(string username, string password, string name, int chip, int moneyInWeb) : username(username), password(password), name(name), chip(chip), moneyInWeb(moneyInWeb)
{
    action = "";
    role = "";
    kicker.emplace_back(0);
    kicker.emplace_back(0);
    accumulateBet = 0;
    order = 1;
}
Player::~Player()
{
    cout << "player has walk out\n";
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
Deck::~Deck()
{
    cout << "Deck class has been destroyed\n";
}
void Deck::reset()
{
    allCardsLeft.clear();
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
