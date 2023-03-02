#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

int money = 500; // สมมติให้เงินของใน user ใน database เป็น $500

class check {
        string filename;
    public:
        check();
        bool loggedin;      // เพิ่มใน Database
        int resetTime;      // เพิ่มใน Database
        void setBoolLoggedin(bool);
        void setResetTime();
        void reset();
        void read();
        void write(bool,int);
};

check::check(){
    filename = "check.txt";        // จำลองไฟล์ DataLN&RG.txt
}

void check::setBoolLoggedin(bool ln) {    // set ค่า loggedin
    loggedin = ln;
}

void check::reset() {                     // reset ค่า loggedin ให้เป็น false ทุก ๆ 00.00 น.
    if (time(0) > resetTime) {
        setBoolLoggedin(false);
    }
}

void check::write(bool ln,int rst){           // จำลอง writeData2_txt() เขียนค่า loggedin และ resetTime ลงไฟล์
    ofstream write(filename);
    write << ln << " " << rst << endl;
    write.close();
}

void check::read(){                      // จำลอง importDatafromfile() อ่านค่า loggedin และ resetTime จากไฟล์
    ifstream read(filename);
    string line;
    char format[] = "%s %s";
    char boolLoggedin[1];
    char reset[100];
    while(getline(read,line)){
        sscanf(line.c_str(), format, boolLoggedin, reset);
        if(strcmp(boolLoggedin, "0") == 0) setBoolLoggedin(false);
        else if(strcmp(boolLoggedin, "1") == 0) setBoolLoggedin(true);
        resetTime = atoi(reset);
    }
    read.close();
}

void check::setResetTime(){         // set เวลา reset โดยอ้างอิงเวลาของ วันที่ 01/01/23 เวลา 00.00 น.
    time_t base = 1672506000;       // Thu Jan  1 00:00:00 2023
    struct tm t1 = *localtime(&base);
    time_t next = mktime(&t1);

    time_t now = time(0);           // เวลาตอนนี้
    struct tm t2= *localtime(&now);
    time_t next2 = mktime(&t2);

    int a = t2.tm_yday - t1.tm_yday;

    time_t rs = base+86400*(a+1);  // เวลา reset
    resetTime = rs;
}

void dailyPrize(check& user) {  // fn dailyPrize รับ parameter เป็น class 
    user.read();    // อ่านค่า loggedin และ resetTime จากไฟล์
    user.reset();   // เช็คว่าตอนนี้ถึงเวลาที่จะต้อง reset หรือยัง ถ้าถึงเวลาแล้ว loggedin จะถูก reset ให้เป็น false
    if (user.loggedin == 0 && time(0) > user.resetTime) {      // ถ้า loggedin เป็น false และเวลาตอนนี้เลยเวลา reset มาแล้ว
        cout << "\n------------------------------------------------------------\n";
        cout << "                       DAILY PRIZE\n";
        cout << "            50 , 100, 200 , 300 , 400, 500\n";                   
        cout << "------------------------------------------------------------\n";
        cout << "           Press enter to receive daily prize\n";
        cout << "------------------------------------------------------------";
        cin.get();
        srand(time(0));
        int i = rand() % 6;  // prob ของ แต่ละรางวัลเป็น 1/6
        int value;
        switch (i) {
        case 0:
            value = 50;     // +$50
            break;
        case 1:
            value = 100;    // +$100
            break;
        case 2:
            value = 200;    // +$200
            break;
        case 3:
            value = 300;    // +$300
            break;
        case 4:
            value = 400;    // +$400
            break;
        default:
            value = 500;    // +$500
            break;
        }
        money += value;  
        cout << "               You got $" << value << "!\n" << "               Total money: $" << money << endl;
        cout << "------------------------------------------------------------\n";
        user.setBoolLoggedin(true);                   // หลังจากบวกเงินของ user แล้ว set ค่า loggedin เป็น true
        user.setResetTime();                          // set เวลา reset ให้เป็น 00.00 น. ของวันถัดไป
        user.write(user.loggedin,user.resetTime);     // เขียนค่า loggedin กับ resetTime ลงไฟล์
    }
}

int main() {
    check z;  
    dailyPrize(z);
    return 0;
}
