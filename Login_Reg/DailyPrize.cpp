#include<iostream>
#include<cstdlib>
#include<ctime>

void getLoggeginTime(){
    ofstream write("time.txt");
    ifstream read("time.txt");
    time_t  t = time(0); 
    write << t << endl;
    string strtime;
    getline(read,strtime);
    const int a = stoi(strtime);
    cout << a;
    remove("time.txt");
}

void dailyPrize(string name, int loggedinTime){
    long long int allowedtime = loggedinTime+86400;
    cout << "------------------------------------------------------------\n";
    cout << "                       DAILY PRIZE\n";
    if(time(0) < allowedtime){
        cout << "You are aleready login today. Please try again tomorrow.";
        cout << "------------------------------------------------------------\n";
    }else{
        cout << "            100 , 200 , 300 , 500 , 750, 1000\n";
        cout << "------------------------------------------------------------\n";
        cout << "Press enter to recieve daily prize";
        cin.get();
        srand(time(0));
        int i = rand()%6;
        switch(i){
            case 0:
                // บวกเงิน 10
                break;
            case 1:
                // บวกเงิน 20,000
                break;
            case 2:
                // บวกเงิน 30,000
                break;
            case 3:
                // บวกเงิน 50,000
                break;
            case 4:
                // บวกเงิน 75,000
                break;
            default:
                // บวกเงิน 100,000
                break;
        }
    }
}
