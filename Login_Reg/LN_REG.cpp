#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
using namespace std;

// สร้าง map เพื่อเก็บข้อมูลของผู้ใช้งาน
map<string, string> userDatabase;

class Database
{
public:
    int num_player;
    string username, password;
    char name[100];
    void registerUser(string, string);
    void loginUser(string, string);
    void writeData2_txt(const map<string, string> &, const string &);
};

// ฟังก์ชั่นเขียนไฟล์ลงไปในไฟล์ DataLN&RG.txt
void Database::writeData2_txt(const map<string, string> &userDatabase, const string &Datatxt)
{
    ofstream dest(Datatxt, std::ios::app);

    for (const auto &[username, password] : userDatabase)
    {
        dest << username << " " << password << '\n';
    }
    dest.close();
}

// ฟังก์ชันสำหรับ Login ผู้ใช้งาน //

//***********************************************************//
//  >>ระบบLoginยังอ่านไฟล์ DataLN&RG ไม่ได้                      //
//      --> เพื่อcheckดูว่ามีชื่ออยุ่ในฐานข้อมูลไหม                   //
//                                                         //
//*********************************************************//

void Database::loginUser(string username, string password)
{
    // ตรวจสอบว่ามีบัญชีในฐานข้อมูลหรือไม่
    int num_Userlogin;
    bool valid = false;
    // ฟังก์ชั่นเช็คต้องใส่ตัวเลขเท่านั้น
    while (!valid)
    {
        cout << "How UserLogin ? :";
        cin >> num_Userlogin;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter number !!!\n";
        }
        else
        {
            valid = true;
        }
    }

    cout << "User Login\n";

    for (int i = 1; i <= num_Userlogin; i++)
    {
        // ตรวจสอบว่ามีชื่ออยุ่ในฐานข้อมูลไหมน้าาา
        while (true)
        {
            cout << "Username  : ";
            cin >> username;

            cout << "Couldn't find your username\n";
            cout << "Please enter your username again.\n";
        }
    }

    // ตรวจสอบว่ารหัสผ่านถูกต้องหรือไม่ เช็คจาก map
    while (true)
    {
        cout << "Password : ";
        cin >> password;
        if (userDatabase[username] == password)
        {
            cout << "User " << username << " has logged in successfully.\n";
            break;
        }
        else
        {
            cout << "Incorrect password for user " << username << ".\n";
        }
    }
}

//***************************************************************//
//                        ระบบ Register 100 %                     //
//                                                               //
//***************************************************************//

// ฟังก์ชันสำหรับ Register ผู้ใช้งาน  // เพิ่มข้อมูลผู้ใช้งานลงในฐานข้อมูล
void Database::registerUser(string username, string password)
{

    string passwordCF;
    int num_UserRegister;
    bool valid = false;
    while (!valid)
    {
        cout << "How UserRegister ? : ";
        cin >> num_UserRegister;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter number !!!\n";
        }
        else
        {
            valid = true;
        }
    }

    for (int i = 1; i <= num_UserRegister; i++)
    {
        while (true)
        {
            cout << "User Register\n";
            cout << "Username : ";
            cin >> username;
            if (userDatabase.count(username) > 0)
            {
                cout << "That username is taken. Try another";
            }
            else
            {
                break;
            }
        }
        while (true)
        {
            cout << "Password : ";
            cin >> password;
            cout << "Confirm Passwowrd : ";
            cin >> passwordCF;
            if (password == passwordCF)
                break;
            else if (password != passwordCF)
            {
                cout << "Passwords didn't match. Try again.\n";
            }
        }
        userDatabase[username] = password;
        writeData2_txt(userDatabase, "DataLN&RG.txt");

        cout << "User " << username << " has been registered successfully." << endl;
    }
}

int main()
{

    Database x;
    x.num_player = 4;
    x.registerUser(x.username, x.password);
    //   x.loginUser(x.username,x.password);
    return 0;
}
