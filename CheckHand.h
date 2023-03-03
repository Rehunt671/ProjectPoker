#ifndef PROJECT2_H
#define PROJECT2_H
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
bool findFreq(vector<std::pair<int, char>> hand, int &mainCardValue, int &minorCardValue, int num)
{
    // Reset ค่าออกให้หมดก่อน
    mainCardValue = 0;
    minorCardValue = 0;
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

    for (const auto &pair : freqRank)
    {
        if (pair.second >= num && mainCardValue == 0)
        {
            mainCardValue = pair.first;
            found = true;
        }
        else if (pair.second >= 2) // ต้องเป็นคู่ 2 เท่านั้น && ทำจนได้ค่ารอบเดียวพอ && ต้อง != mainCardValue เนื่องจาก ถ้า TwoPair เจอ TwoPair ให้ค่าหลักไปอยู่ที่ mainCardValue
        {
            minorCardValue = pair.first;
        }
    }
    if (found)
        return true;
    return false;
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

void convertToPairVector(vector<std::pair<int, char>> &split, vector<string> &combined)
{
    split.resize(combined.size());
    for (size_t i = 0; i < combined.size(); i++)
    {
        if (combined[i][0] == 'A')
        {
            combined[i].replace(0, 1, "14");
        }
        else if (combined[i][0] == 'K')
        {
            combined[i].replace(0, 1, "13");
        }
        else if (combined[i][0] == 'Q')
        {
            combined[i].replace(0, 1, "12");
        }
        else if (combined[i][0] == 'J')
        {
            combined[i].replace(0, 1, "11");
        }
        else if (combined[i][0] == 'T')
        {
            combined[i].replace(0, 1, "10");
        }
    }
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
    }
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
bool hasFlush(vector<std::pair<int, char>> hand, int &mainCardValue, char &flushSuit)
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

    for (int i = 0; i < hand.size(); i++)
    {
        if (hand[i].second == flushSuit && hand[i].first > mainCardValue)
        {
            mainCardValue = hand[i].first;
        }
    }
    return true;
}
bool hasStraightFlush(vector<std::pair<int, char>> hand, int &mainCardValue, char &flushSuit, bool &StraightFlush)
{
    return hasStraight(hand, mainCardValue, flushSuit, StraightFlush) && flushSuit != '\0' && StraightFlush;
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
        return ranks.find(a[0]) < ranks.find(b[0]); });
    convertToPairVector(split, combined);
    if (split.size() >= 5)
    {
        hasFlush(split, mainCardValue, flushSuit); // เริ่มแรกมาเช็คหน้าไพ่ก่อนเลยว่ามีซ้ำครบ 5 ใบไหม
        if (hasRoyalFlush(split, flushSuit))       // ต้องมี Flush และตรงกับ Rank A K Q J 10
            p->rankOfHand.first = "RoyalFlush";
        else if (hasStraightFlush(split, mainCardValue, flushSuit, StraightFlush)) // ต้องมีทั้ง Flush กับ Straight ที่ตรงกัน
            p->rankOfHand.first = "StraightFlush";
        else if (hasFourOfKind(split, mainCardValue, minorCardValue)) // ต้องมีไพ่ 4 ใบ Rank เดียวกัน
            p->rankOfHand.first = "FourOfKind";
        else if (hasFullHouse(split, mainCardValue, minorCardValue)) // ต้องมีไพ่ ตอง 1 และ คู่ 1 คู่
            p->rankOfHand.first = "FullHouse";
        else if (flushSuit != '\0') // ขอแค่มี flushSuit ก็แปลว่ามีไพ่หน้าเดียวกัน 5 ใบแล้ว
            p->rankOfHand.first = "Flush";
        else if (hasStraight(split, mainCardValue, flushSuit, StraightFlush))
            p->rankOfHand.first = "Straight";
        else if (hasTreeOfKind(split, mainCardValue, minorCardValue))
            p->rankOfHand.first = "ThreeOfKind";
        else if (hasTwoPair(split, mainCardValue, minorCardValue))
            p->rankOfHand.first = "TwoPair";
    }
    if (p->rankOfHand.first == "")
    {
        if (hasPair(split, mainCardValue, minorCardValue))
            p->rankOfHand.first = "Pair";
        else
        {
            hasHighcards(split, mainCardValue);
            p->rankOfHand.first = "HighCard";
        }
    }
    p->rankOfHand.second.first = findRankInNumber(p->rankOfHand.first);
    p->rankOfHand.second.second.first = mainCardValue;
    p->rankOfHand.second.second.second = minorCardValue;

}

#endif
