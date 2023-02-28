#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int money = 1000;

class check {
public:
    bool loggedin;
    void setBoolLoggedin(bool);
    void resetBoolLoggedin();
};

void check::setBoolLoggedin(bool ln) {
    loggedin = ln;
}

void check::resetBoolLoggedin() {
    time_t now = time(0);
    struct tm* t1 = localtime(&now);
    t1->tm_mday += 1;
    t1->tm_hour = 0;
    t1->tm_min = 0;
    t1->tm_sec = 0;
    time_t resetTime = mktime(t1); 
    cout << now << " : " << ctime(&now) << endl;
    cout << resetTime << " : " << ctime(&resetTime) << endl;
    if (now >= resetTime) {
        loggedin = false;
    }
}

void dailyPrize(check& user) {
    user.resetBoolLoggedin(); 
    if (user.loggedin == false) {
        cout << "\n------------------------------------------------------------\n";
        cout << "                       DAILY PRIZE\n";
        cout << "            100 , 200 , 300 , 500 , 750, 1000\n";
        cout << "------------------------------------------------------------\n";
        cout << "           Press enter to receive daily prize\n";
        cout << "------------------------------------------------------------";
        cin.get();
        srand(time(0));
        int i = rand() % 6;
        int value;
        switch (i) {
        case 0:
            value = 100;
            break;
        case 1:
            value = 200;
            break;
        case 2:
            value = 300;
            break;
        case 3:
            value = 500;
            break;
        case 4:
            value = 750;
            break;
        default:
            value = 1000;
            break;
        }
        money += value;
        cout << "               You got $" << value << "!\n" << "               Total money: $" << money << endl;
        cout << "\n------------------------------------------------------------\n";
        user.setBoolLoggedin(true);
    }
}

int main() {
    check z;
    dailyPrize(z);
    dailyPrize(z);
    return 0;
}
