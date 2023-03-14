#ifndef PROJECT1_H
#define PROJECT1_H
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

    cout << left;
    cout.width(33);
    cout << players[0]->role;
    cout << left;
    cout.width(33);
    cout << players[1]->role << "\n";
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
    cout << left << "accomulate bet : ";
    cout.width(16);
    cout << players[0]->accumulateBet;
    cout << left << "accomulate bet : ";
    cout.width(16);
    cout << players[1]->accumulateBet << "\n";
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
    cout << left;
    cout.width(33);
    cout << players[0]->role;
    cout << left;
    cout.width(33);
    cout << players[1]->role;
    cout << left;
    cout.width(33);
    cout << players[2]->role << "\n";
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
    cout << left << "accomulate bet : ";
    cout.width(16);
    cout << players[0]->accumulateBet;
    cout << left << "accomulate bet : ";
    cout.width(16);
    cout << players[1]->accumulateBet;
    cout << left << "accomulate bet : ";
    cout.width(16);
    cout << players[2]->accumulateBet << "\n";
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
    cout << left;
    cout.width(33);
    cout << players[0]->role;
    cout << left;
    cout.width(33);
    cout << players[1]->role;
    cout << left;
    cout.width(33);
    cout << players[2]->role;
    cout << left;
    cout.width(33);
    cout << players[3]->role << "\n";
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
    cout << left << "accomulate bet : ";
    cout.width(16);
    cout << players[0]->accumulateBet;
    cout << left << "accomulate bet : ";
    cout.width(16);
    cout << players[1]->accumulateBet;
    cout << left << "accomulate bet : ";
    cout.width(16);
    cout << players[2]->accumulateBet;
    cout << left << "accomulate bet : ";
    cout.width(16);
    cout << players[3]->accumulateBet << "\n";
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
void showprize()
{
    cout << "\n=========================================================================================";
    cout << "==                       PPPPP    RRRRR    IIIII  ZZZZZZ  EEEEEE                       ==" << endl;
    cout << "==                       P    P   R    R     I        Z   E                            ==" << endl;
    cout << "==                       PPPPP    RRRRR      I       Z    EEEEEE                       ==" << endl;
    cout << "==                       P        R   R      I     Z      E                            ==" << endl;
    cout << "==                       P        R    R   IIIII  ZZZZZZ  EEEEEE                       ==" << endl;
    cout << "=========================================================================================" << endl;
    cout << "=========================================================================================" << endl;
    cout << "=                                    This is pot*......                                  " << endl;
    cout << "=            *0.5 in 20 percent      *0.8 in 20 percent      *1.0 in 40 percent          " << endl;
    cout << "=                       *1.2 in 10 percent      *1.5 in 5 percent                        " << endl;
    cout << "                                                                                         " << endl;
    cout << "                        !!!! And the big win *2 in 5 percent !!!!                        " << endl;
    cout << "=========================================================================================" << endl;
}
#endif
