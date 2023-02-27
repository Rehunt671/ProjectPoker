#ifndef PROJECT1_H
#define PROJECT1_H
#include <vector>
#include <utility>
#include <unordered_map>
#include "Project.h"
using namespace std;
bool findFreq(vector<std::pair<int, char>> hand, int &maxVar, int &max2ndPairVar, int num)
{
    // Reset ค่าออกให้หมดก่อน
    maxVar = 0;
    max2ndPairVar = 0;
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
        if (pair.second >= num && maxVar == 0)
        {
            maxVar = pair.first;
            found = true;
        }
        else if (pair.second >= 2) // ต้องเป็นคู่ 2 เท่านั้น && ทำจนได้ค่ารอบเดียวพอ && ต้อง != maxVar เนื่องจาก ถ้า TwoPair เจอ TwoPair ให้ค่าหลักไปอยู่ที่ MaxVar
        {
            max2ndPairVar = pair.first;
        }
    }
    if (found)
        return true;
    return false;
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
    }
    for (size_t i = 0; i < combined.size(); i++)
    {
        split[i].first = stoi(combined[i].substr(0, combined[i].length() - 1));
        split[i].second = combined[i].back();
    }
    for (size_t i = 0; i < combined.size(); i++)
    {
        cout << split[i].first << split[i].second << "\n";
    }
}

bool hasRoyalFlush(vector<std::pair<int, char>> hand)
{
}
bool hasStraight(vector<std::pair<int, char>> hand, int &maxVar, char &flushSuit, bool &StraightFlush)
{
    int i = hand.size();
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
            maxVar = hand[i].first;
            if (hand[i].second != flushSuit || hand[i - 1].second != flushSuit || hand[i - 2].second != flushSuit || hand[i - 3].second != flushSuit || hand[i - 4].second != flushSuit)
                StraightFlush = false;
            return true;
        }
    }
    return false;
}
bool hasFlush(vector<std::pair<int, char>> hand, int &maxVar, char &flushSuit)
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
        if (hand[i].second == flushSuit && hand[i].first > maxVar)
        {
            maxVar = hand[i].first;
        }
    }
    return true;
}
bool hasStraightFlush(vector<std::pair<int, char>> hand, int &maxVar, char &flushSuit, bool &StraightFlush)
{
    return hasStraight(hand, maxVar, flushSuit, StraightFlush) && hasFlush(hand, maxVar, flushSuit) && StraightFlush;
}

bool hasFourOfKind(vector<std::pair<int, char>> hand, int &maxVar, int &max2ndPairVar)
{
    return findFreq(hand, maxVar, max2ndPairVar, 4);
}
bool hasTreeOfKind(vector<std::pair<int, char>> hand, int &maxVar, int &max2ndPairVar)
{

    return findFreq(hand, maxVar, max2ndPairVar, 3);
}
bool hasTwoPair(vector<std::pair<int, char>> hand, int &maxVar, int &max2ndPairVar)
{

    return (findFreq(hand, maxVar, max2ndPairVar, 2) && max2ndPairVar != 0); // ต้องมีไพ่คู่รองด้วย(max2ndPairVar) ด้วยถ้ามัน == 0 แปลว่าไม่มีไพ่คู่รอง
}
bool hasPair(vector<std::pair<int, char>> hand, int &maxVar, int &max2ndPairVar)
{

    return findFreq(hand, maxVar, max2ndPairVar, 2);
}
bool hasFullHouse(vector<std::pair<int, char>> hand, int &maxVar, int &max2ndPairVar)
{
    return (hasTreeOfKind(hand, maxVar, max2ndPairVar) && max2ndPairVar != 0);
}

void hasHighcards(vector<std::pair<int, char>> hand, int &maxVar)
{
    maxVar = hand.back().first;
}
void PokerGame::checkHand(Player *p)
{ // Check กรณีดังต่อไปนี้ 2 5 6 7 ใบ
    vector<std::pair<int, char>> split;
    char flushSuit = '\0';
    bool StraightFlush = true;
    int maxVar = 0;
    int max2ndPairVar = 0;
    vector<string> combined(p->cards.begin(), p->cards.end());
    combined.insert(combined.end(), cardsOnBoard.begin(), cardsOnBoard.end());
    sort(combined.begin(), combined.end(), [](const string &a, const string &b)
         {
        string ranks = "23456789TJQKA";
        return ranks.find(a[0]) < ranks.find(b[0]); });
    convertToPairVector(split, combined);
    if (split.size() >= 5)
    {
        // if (hasRoyalFlush(split))
        //     cout << "RoyalFlush!!";
        if (hasStraightFlush(split, maxVar, flushSuit, StraightFlush))
            cout << "StraightFlush";
        else if (hasFourOfKind(split, maxVar, max2ndPairVar))
            cout << "FourOfkind";
        else if (hasFullHouse(split, maxVar, max2ndPairVar))
            cout << "FullHouse";
        else if (hasFlush(split, maxVar, flushSuit))
            cout << "Flush";
        else if (hasStraight(split, maxVar, flushSuit, StraightFlush))
            cout << "hasStraight";
        else if (hasTreeOfKind(split, maxVar, max2ndPairVar))
            cout << "ThreeOfKind";
        else if (hasTwoPair(split, maxVar, max2ndPairVar))
            cout << "TwoPair";
    }
    if (p->rankOfHand.first == "")
    {
        if (hasPair(split, maxVar, max2ndPairVar))
            cout << "Pair";
        else
        {
            hasHighcards(split, maxVar);
            cout << "Highcards";
        }
    }
    cout << "\nMaxVar = " << maxVar;
    cout << "\nMax2nd = " << max2ndPairVar;
}
#endif