#ifndef PROJECT3_H
#define PROJECT3_H
bool findFreq(vector<std::pair<int, char>> hand, int &mainCardValue, int &minorCardValue, int num)
{
    // Reset ค่าออกให้หมดก่อน
    mainCardValue = 0;
    minorCardValue = 0;
    reverse(hand.begin(), hand.end()); // เปลี่ยนจากเรียงจากน้อยไปมาก ไปเป็น มากไปน้อย
    unordered_map<int, int> freqRank;
    bool found = false;
    for (const auto &cards : hand)
    {
        if (freqRank.find(cards.first) == freqRank.end())
        {
            freqRank[cards.first] = 1;
        }
        else
        {
            freqRank[cards.first]++;
        }
    }
    for (const auto &pair : freqRank) // เรียงจากมากไปน้อย
    {
        if (pair.second >= num && mainCardValue == 0)
        {
            mainCardValue = pair.first;
            found = true;
        }
        else if (pair.second >= 2 && mainCardValue == 0)
        {
            minorCardValue = pair.first;
        }
    }
    if (found)
        return true;
    return false;
}
vector<int> findKicker(vector<string> cards, const int mainCardValue, const int minorCardValue, const bool twopair) /////หาไพ่ใบรองจาก main ในมือเราถ้าไม่มี ก็คือเสมอเลย
{
    vector<int> kicker(2, 0);
    int cardVar = 0;
    convertFrontToNumber(cards);
    for (size_t i = 0; i < cards.size(); i++)
    {
        cardVar = stoi(cards[i].substr(0, cards[i].length() - 1));
        if (twopair)
        {
            if (cardVar > kicker[i] && cardVar != mainCardValue && cardVar != minorCardValue)
                kicker[i] = cardVar;
        }
        else
        {
            if (cardVar > kicker[i] && cardVar != mainCardValue)
                kicker[i] = cardVar;
        }
    }
    sort(kicker.begin(), kicker.end(), greater<int>());
    cout << "Kicker 0 ========== " << kicker[0] << "\n";
    cout << "Kicker 1 ========== " << kicker[1] << "\n";
    return kicker;
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
int findRankInNumber(string strRank)
{
    map<string, int> ranking;
    ranking["RoyalFlush"] = 1;
    ranking["StraightFlush"] = 2;
    ranking["FourOfKind"] = 3;
    ranking["FullHouse"] = 4;
    ranking["Flush"] = 5;
    ranking["Straight"] = 6;
    ranking["ThreeOfKind"] = 7;
    ranking["TwoPair"] = 8;
    ranking["Pair"] = 9;
    ranking["HighCard"] = 10;
    if (ranking.count(strRank) > 0) // กัน return bad behavior
        return ranking[strRank];
    return 0;
}
string findRankInStr(int intRank)
{
    map<int, string> ranking;
    ranking[1] = "RoyalFlush";
    ranking[2] = "StraightFlush";
    ranking[3] = "FourOfKind";
    ranking[4] = "FullHouse";
    ranking[5] = "Flush";
    ranking[6] = "Straight";
    ranking[7] = "ThreeOfKind";
    ranking[8] = "TwoPair";
    ranking[9] = "Pair";
    ranking[10] = "HighCard";
    if (ranking.count(intRank) > 0)
        return ranking[intRank];
    return 0;
}
void convertFrontToNumber(vector<string> &v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i][0] == 'A')
        {
            v[i].replace(0, 1, "14");
        }
        else if (v[i][0] == 'K')
        {
            v[i].replace(0, 1, "13");
        }
        else if (v[i][0] == 'Q')
        {
            v[i].replace(0, 1, "12");
        }
        else if (v[i][0] == 'J')
        {
            v[i].replace(0, 1, "11");
        }
        else if (v[i][0] == 'T')
        {
            v[i].replace(0, 1, "10");
        }
    }
}
void convertToPairVector(vector<std::pair<int, char>> &split, vector<string> &combined)
{
    split.resize(combined.size());
    convertFrontToNumber(combined);
    for (size_t i = 0; i < combined.size(); i++)
    {
        split[i].first = stoi(combined[i].substr(0, combined[i].length() - 1));
        split[i].second = combined[i].back();
    }
}

bool hasRoyalFlush(vector<std::pair<int, char>> hand, char &flushSuit)
{
    int i = hand.size() - 1;
    while (i > 0)
    {
        if (hand[i].first - hand[i - 1].first == 0)
            hand.erase(hand.begin() + i);
        i--;
    }
    i = hand.size() - 1;
    if (
        hand[i].first == 14 && hand[i].second == flushSuit && hand[i - 1].first == 13 && hand[i - 1].second == flushSuit && hand[i - 2].first == 12 && hand[i - 2].second == flushSuit && hand[i - 3].first == 11 && hand[i - 3].second == flushSuit && hand[i - 4].first == 10 && hand[i - 4].second == flushSuit)
    {
        return true;
    }

    return false;
}
bool hasStraight(vector<std::pair<int, char>> hand, int &mainCardValue, char &flushSuit, bool &StraightFlush)
{
    int i = hand.size() - 1;
    while (i > 0)
    {
        if (hand[i].first - hand[i - 1].first == 0)
            hand.erase(hand.begin() + i);
        i--;
    } // ลบซ้ำ
    for (size_t i = hand.size() - 1; i > 0; i--)
    {
        if (i - 4 >= 0 && hand[i].first - hand[i - 1].first == 1 && hand[i].first - hand[i - 2].first == 2 && hand[i].first - hand[i - 3].first == 3 && hand[i].first - hand[i - 4].first == 4)
        {
            mainCardValue = hand[i].first;
            if (hand[i].second != flushSuit || hand[i - 1].second != flushSuit || hand[i - 2].second != flushSuit || hand[i - 3].second != flushSuit || hand[i - 4].second != flushSuit)
                StraightFlush = false;
            return true;
        }
    }
    return false;
}
bool findFlushSuit(vector<std::pair<int, char>> hand, char &flushSuit)
{
    unordered_map<char, int> suitCounts;
    for (auto &p : hand)
    {
        suitCounts[p.second]++;
    }

    for (auto &sc : suitCounts)
    {
        if (sc.second >= 5)
        {
            flushSuit = sc.first;
            break;
        }
    }

    if (flushSuit == '\0')
    {
        return false; // no flush
    }
    return true;
}
bool hasFlush(vector<std::pair<int, char>> hand, vector<int> &flushRank, const char flushSuit)
{
    if (flushSuit != '\0')
    {
        flushRank.clear();
        for (int i = 0; i < hand.size(); i++)
        {
            if (hand[i].second == flushSuit)
            {
                flushRank.emplace_back(hand[i].first);
            }
        }
        sort(flushRank.begin(), flushRank.end(), greater<int>());
        return true;
    }
    return false;
}
bool hasStraightFlush(vector<std::pair<int, char>> hand, int &mainCardValue, char &flushSuit, bool &StraightFlush)
{
    return hasStraight(hand, mainCardValue, flushSuit, StraightFlush) && StraightFlush; // ต้องมี Straight ก่อนแล้วต้องเป็น StraightFlush ด้วย
}

bool hasFourOfKind(vector<std::pair<int, char>> hand, int &mainCardValue, int &minorCardValue)
{
    return findFreq(hand, mainCardValue, minorCardValue, 4);
}
bool hasTreeOfKind(vector<std::pair<int, char>> hand, int &mainCardValue, int &minorCardValue)
{

    return findFreq(hand, mainCardValue, minorCardValue, 3);
}
bool hasTwoPair(vector<std::pair<int, char>> hand, int &mainCardValue, int &minorCardValue)
{

    return (findFreq(hand, mainCardValue, minorCardValue, 2) && minorCardValue != 0); // ต้องมีไพ่คู่รองด้วย(minorCardValue) ด้วยถ้ามัน == 0 แปลว่าไม่มีไพ่คู่รอง
}
bool hasPair(vector<std::pair<int, char>> hand, int &mainCardValue, int &minorCardValue)
{

    return findFreq(hand, mainCardValue, minorCardValue, 2);
}
bool hasFullHouse(vector<std::pair<int, char>> hand, int &mainCardValue, int &minorCardValue)
{
    return (hasTreeOfKind(hand, mainCardValue, minorCardValue) && minorCardValue != 0);
}

void hasHighcards(vector<std::pair<int, char>> hand, int &mainCardValue)
{
    mainCardValue = hand.back().first;
}
void PokerGame::checkHand(Player *p)
{ // Check กรณีดังต่อไปนี้ 2 5 6 7 ใบ
    vector<std::pair<int, char>> split;
    char flushSuit = '\0';
    bool StraightFlush = true;
    int mainCardValue = 0;
    int minorCardValue = 0;
    vector<string> combined(p->cards.begin(), p->cards.end());
    combined.insert(combined.end(), cardsOnBoard.begin(), cardsOnBoard.end());
    sort(combined.begin(), combined.end(), [](const string &a, const string &b)
         {
        string ranks = "23456789TJQKA";
        return ranks.find(a[0]) < ranks.find(b[0]); });                            // เรียกจากค่าไพ่น้อยไปมาก 2-A
    convertToPairVector(split, combined); // แยกหน้าไพ่กับ Rank ไพ่
    if (split.size() >= 5)
    {

        findFlushSuit(split, flushSuit);     // เริ่มแรกมาเช็คหน้าไพ่ก่อนเลยว่ามีซ้ำครบ 5 ใบไหม
        if (hasRoyalFlush(split, flushSuit)) // ต้องมี Flush และตรงกับ Rank A K Q J 10 กรณีเช็คยากสุดเทียบ mainCard X
            p->handRanking.first = "RoyalFlush";
        else if (hasStraightFlush(split, mainCardValue, flushSuit, StraightFlush)) // ต้องมีทั้ง Flush กับ Straight ที่ตรงกัน กรณีเช็คยากสุดเทียบ mainCard X
            p->handRanking.first = "StraightFlush";
        else if (hasFourOfKind(split, mainCardValue, minorCardValue)) // ต้องมีไพ่ 4 ใบ Rank เดียวกัน กรณีเช็คยากสุด เทียบไพ่ใบที่ 5 ที่เรียกว่า Kicker บนมือผู้เล่น
            p->handRanking.first = "FourOfKind";
        else if (hasFullHouse(split, mainCardValue, minorCardValue)) // ต้องมีไพ่ ตอง 1 และ คู่ 1 คู่ กรณีเช็คยากสุด เทียบ main แล้ว minor X
            p->handRanking.first = "FullHouse";
        else if (hasFlush(split, p->flushRank, flushSuit)) // 5 ใบหน้าตรงกัน กรณีเช็คยากสุด เทียบเรียงใบ 5 ใบ
            p->handRanking.first = "Flush";
        else if (hasStraight(split, mainCardValue, flushSuit, StraightFlush)) // 5 ใบเรียง กรณีเช็คยากสุดเทียบ mainCard X
            p->handRanking.first = "Straight";
        else if (hasTreeOfKind(split, mainCardValue, minorCardValue))
            p->handRanking.first = "ThreeOfKind";                  // 1ต้อง   กรณีเช็คยากสุดเทียบ Kicker บนมือผู้เล่น
        else if (hasTwoPair(split, mainCardValue, minorCardValue)) // 2 คู่  กรณีเช็คยากสุด เทียบ main แล้ว minor แล้วไป kicker
            p->handRanking.first = "TwoPair";
    }
    if (p->handRanking.first == "")
    {
        if (hasPair(split, mainCardValue, minorCardValue)) // 1 คู่  กรณีเช็คยากสุดเทียบ kicker
            p->handRanking.first = "Pair";
        else
        {
            hasHighcards(split, mainCardValue); // เดี่ยว กรณีเช็คยากสุดเทียบ kicker
            p->handRanking.first = "HighCard";
        }
    }
    if (p->handRanking.first == "FourOfKind" || p->handRanking.first == "ThreeOfKind" ||
        p->handRanking.first == "TwoPair" || p->handRanking.first == "Pair")
    {
        bool twopair = false;
        if (p->handRanking.first == "TwoPair")
            twopair = true;
        p->kicker = findKicker(p->cards, mainCardValue, minorCardValue, twopair);
    }
    p->handRanking.second = findRankInNumber(p->handRanking.first);
    p->cardRanking.first = mainCardValue;
    p->cardRanking.second = minorCardValue;
}

#endif
