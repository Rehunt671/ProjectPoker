#include<iostream>
#include<string>
#include<conio.h>
#include<stdlib.h>
#include<cstdlib>
#include<vector>
using namespace std;

class reg{                           // ข้อมูลของแต่ละคน: username, display name, password, เงิน
        string username;
        string displayname;
        char password[19];
        long long int money;
    public:
        reg();
        void setUsername();
        void setDisplayName();
        void setPassword();
};

class allUsers{                      // เก็บข้อมูลของ user แต่ละคน (class reg) ไปใส่ใน vector all
        vector<reg> all;
    public:
        void addUserInfo(reg); 
};

void allUsers::addUserInfo(reg user){
    all.emplace_back(user);
};

void reg::setUsername(){            // รับ input username
    int state = 0;
    string input;
    while(state == 0){
        cout << "Enter Username: ";
        getline(cin,input);
        if(input.size() == 0){
            cout << "Username cannot be empty.\n";
        }else if(input.size() < 6 || input.size() > 30){
            cout << "Username must be 6-30 characters.\n";
        }else{
            username = input; 
            state = 1;
        }
    }
};

void reg::setDisplayName(){           // รับ input display name          
    int state = 0;
    string input;
    while(state == 0){
        cout << "Enter Display name: ";
        getline(cin,input);
        if(input.size() == 0){
            cout << "Display name cannot be empty.\n";
        }else if(input.size() > 20){
            cout << "Display name must be 1-20 characters.\n";
        }else{
            displayname = input; 
            state = 1;
        }
    }
}

void reg::setPassword(){             // รับ input password
    START:
    int i = 0,state = 0;
    char c,pwd[19];
    cout << "Enter Password: ";
    for(i=0;;){ 
        c = getch();
        if(c >= 33 || c <= 126){
            pwd[i] = c;
            ++i;
            cout << "*";
        }
        if(c == '\b' && i >= 1){ //8
            cout << "\b \b";
            --i;
        }
        if(c == '\r'){
            cout << "\b \b";
            --i;
            pwd[i] = '\0';
            break;          
        }else{

        }           
    }  
    if(i == 0){
        cout << "\nPassword cannot be empty.\n";
        goto START;
    }else if(i < 6 || i > 18){
        cout << "\nPassword must be 6-18 characters.\n";
        goto START;
    }else{
        for(int j = 0; j < i+1; j++) password[j] = pwd[j];
    }
};

reg::reg(){               
    setUsername();
    setDisplayName();
    setPassword();

};
int main(){
    reg r1;
}