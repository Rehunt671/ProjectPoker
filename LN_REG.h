#ifndef PROJECT1_H
#define PROJECT1_H
#include "AllClass.h"
// สร้าง map เพื่อเก็บข้อมูลของผู้ใช้งาน
using std::cin;
map<pair<string, string>, vector<string>> userDatabase;
bool Database::checkIfNewWeb()
{
    string test;
    ifstream newWeb("DataLN&RG.txt");
    if (!getline(newWeb, test))
    {

        newWeb.close();
        return true;
    }
    newWeb.close();
    return false;
}
void Database::setDisplayName()
{ // รับ input display name
    bool state = false;
    string input;
    while (state == 0)
    {
        cout << "Enter Display name: ";
        cin.ignore();
        getline(cin, input);
        if (input.size() == 0)
        {
            cout << "Display name cannot be empty.\n";
        }
        else if (input.size() > 20)
        {
            cout << "Display name must be 1-20 characters.\n";
        }
        else
        {
            displayname = input;
            state = true;
        }
    }
}

void Database::Delete_()
{
    set<string> collet;
    string line;
    ifstream file("DataLN&RG.txt");

    if (file.is_open())
    {
        while (getline(file, line))
        {

            collet.insert(line);
        }
        file.close();
    }

    ofstream newfile("DataLN&RG.txt");
    for (auto it = collet.begin(); it != collet.end(); ++it)
    {
        newfile << *it << endl;
    }
    newfile.close();
}

void Database::writeData2_txt(const map<pair<string, string>, vector<string>> &userDatabase, const string &Datatxt)
{
    ofstream dest(Datatxt, std::ios::app);

    for (const auto &entry : userDatabase)
    {
        const auto &key = entry.first;
        const auto &value = entry.second;
        dest << key.first << " " << key.second << " ";
        for (const auto &elem : value)
        {
            dest << elem << " ";
        }
        dest << "\n";
    }
    dest.close();
}

void Database::importDatafromfile(string filename, vector<string> &un, vector<string> &pw)
{

    ifstream source(filename.c_str());
    string line;
    char format[] = "%s %s";
    char name[100];
    char pass[100];
    while (getline(source, line))
    {
        sscanf(line.c_str(), format, name, pass);

        un.push_back(name);
        pw.push_back(pass);
    }
    source.close();
}

string Database::toUpperStr(string x)
{
    string y = x;
    for (unsigned i = 0; i < x.size(); i++)
        y[i] = toupper(x[i]);
    return y;
}

// ฟังก์ชันสำหรับ Login ผู้ใช้งาน //

//**************************************************************//
//                                                             //
//             >>ระบบLogin   1000000%                         //
//                                                           //
//__________________________________________________________//

void Database::loginUser(int &num_Userlogin)
{ // ตรวจสอบว่ามีบัญชีในฐานข้อมูลหรือไม่
    string username;
    string password;
    string filename = "DataLN&RG.txt";
    vector<string> un;
    vector<string> pw;
    importDatafromfile(filename, un, pw);
    bool valid = false;
    while (!valid || num_Userlogin < 1 || num_Userlogin > 4)
    { // ฟังก์ชั่นเช็คต้องใส่ตัวเลขเท่านั้น
        cout << "How many user want to login ? :";
        cin >> num_Userlogin;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter number(2-4)!!!\n";
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
        bool n = true;
        bool m = true;
        bool checkUN = false;
        bool checkPW = false;
        while (n)
        {
            cout << "Username  : ";
            cin >> username;

            for (unsigned int i = 0; i < un.size(); i++)
            { // เช็คว่ามีชื่อในระบบไหม

                if (username == un[i])
                {
                    checkUN = true;
                    n = false;
                }
            }
            if (checkUN == false)
            {
                cout << "Couldn't find your username\n";
                cout << "Please enter your username again.\n";
            }
        }

        // ตรวจสอบว่ารหัสผ่านถูกต้องหรือไม่
        while (m)
        {
            cout << "Password : ";
            cin >> password;
            for (unsigned int i = 0; i < pw.size(); i++)
            {

                if (password == pw[i])
                {
                    checkPW = true;
                    m = false;
                    cout << "User " << username << " has logged in successfully.\n";
                    i = num_Userlogin + 10;
                }
            }

            if (checkPW == false)
            {
                cout << "Incorrect password for user " << username << ".\n";
            }
        }
    }
}

// ฟังก์ชันสำหรับ Register ผู้ใช้งาน //

//**************************************************************//
//                                                             //
//             >>ระบบRegister   %                       //
//                                                           //
//__________________________________________________________//

// ฟังก์ชันสำหรับ Register ผู้ใช้งาน  // เพิ่มข้อมูลผู้ใช้งานลงในฐานข้อมูล
void Database::registerUser()
{
    string username;
    string password;
    string passwordCF;
    int num_UserRegister;
    bool valid = false;
    while (!valid)
    { // checkต้องnum เท่านั้น
        cout << "How many user want to register ? : ";
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
        bool n = true;
        bool m = true;
        cout << "User Register\n";

        while (true)
        {
            cout << "Username : ";
            cin >> username;
            bool found = false;
            for (auto const &key_value : userDatabase)
            {
                if (key_value.first.first == username)
                {
                    found = true;
                    break;
                }
            }
            if (found)
                cout << "That username is taken. Try another\n";
            else
            {
                break;
            }
        }
        while (true)
        {
            cout << "Password : ";
            cin >> password;
            cout << "Confirm Password : ";
            cin >> passwordCF;
            if (password == passwordCF)
                break;
            else if (password != passwordCF)
            {
                cout << "Passwords didn't match. Try again.\n";
            }
        }
        moneyInWeb = "$500";
        setDisplayName();
        userDatabase[make_pair(username, password)].emplace_back(displayname);
        userDatabase[make_pair(username, password)].emplace_back(moneyInWeb);
        writeData2_txt(userDatabase, "DataLN&RG.txt");

        cout << "User " << username << " has been registered successfully." << endl;
        cout << "You recieve free credit : " << moneyInWeb << " Dollar\n";
    }
    // Delete_();
}
#endif
