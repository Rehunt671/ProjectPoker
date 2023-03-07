#ifndef PROJECT2_H
#define PROJECT2_H
// สร้าง map เพื่อเก็บข้อมูลของผู้ใช้งาน
void Database::dailyPrize(const string &un, const string &pw)
{
    cout << "\n------------------------------------------------------------\n";
    cout << "                       DAILY PRIZE\n";
    cout << "           $50 , $100 , $200 , $300 , $400 , $500\n";
    cout << "------------------------------------------------------------\n";
    cout << "            Press Enter to receive daily prize.\n";
    cout << "------------------------------------------------------------";
    cin.ignore();
    cin.get();
    int i = rand() % 6; // prob ของ แต่ละรางวัลเป็น 1/6
    string value;
    switch (i)
    {
    case 0:
        value = "50"; // +$50
        break;
    case 1:
        value = "100"; // +$100
        break;
    case 2:
        value = "200"; // +$200
        break;
    case 3:
        value = "300"; // +$300
        break;
    case 4:
        value = "400"; // +$400
        break;
    default:
        value = "500"; // +$500
        break;
    }
    userDatabase[{un, pw}][1] = to_string(stoi(userDatabase[{un, pw}][1]) + stoi(value));
    cout << "                     You got $" + value + "!\n"
         << "                    Total money: $" << userDatabase[{un, pw}][1] << endl;
    cout << "------------------------------------------------------------\n";
    cout << "                 Press Enter to continue.\n";
    userDatabase[{un, pw}][2] = "1";                       // หลังจากบวกเงินของ user แล้ว set ค่า loggedin เป็น true
    userDatabase[{un, pw}][3] = to_string(setResetTime()); // set เวลา reset ให้เป็น 00.00 น. ของวันถัดไป
    writeData2_txt();                                      // เขียนค่า loggedin กับ resetTime ลงไฟล์
}
Database::Database() : filename("DataLN&RG.txt")
{
    importDatafromfile();
}
Database::~Database()
{
    cout << "PokerGame database was deleted";
}
void Database::setDisplayName(string &dp)
{ // รับ input display name
    bool state = false;
    while (state == false)
    {
        cout << "Enter Display name: ";
        cin.ignore();
        getline(cin, dp);
        if (dp.size() == 0)
        {
            cout << "Display name cannot be empty.\n";
        }
        else if (dp.size() > 20)
        {
            cout << "Display name must be 1-20 characters.\n";
        }
        else
        {
            state = true;
        }
    }
}

void Database::Delete_()
{
    set<string> collet;
    string line;
    ifstream file(filename);

    if (file.is_open())
    {
        while (getline(file, line))
        {

            collet.insert(line);
        }
        file.close();
    }

    ofstream newfile(filename);
    for (auto it = collet.begin(); it != collet.end(); ++it)
    {
        newfile << *it << endl;
    }
    newfile.close();
}

void Database::writeData2_txt()
{
    ofstream dest(filename);
    for (const auto &pair : userDatabase)
    {
        dest << pair.first.first << " " << pair.first.second << " ";

        for (const auto &str : pair.second)
        {
            dest << str << " ";
        }

        dest << "\n";
    }

    // Close the file
    dest.close();
}

void Database::importDatafromfile() // อ่านไฟล์จากไฟล์หลักพร้อมกับเขียนMapขึ้นมา
{
    ifstream source(filename);
    string line;
    char format[] = "%s %s %s %s %d %lld";
    char name[100];
    char pass[100];
    char dp[100];
    char mn[100];
    int boolLoggedin;
    unsigned long long int rst;
    while (getline(source, line))
    {
        sscanf(line.c_str(), format, name, pass, dp, mn, &boolLoggedin, &rst);
        reset(boolLoggedin, rst); // เช็คว่าจะรีเซ็ต DailyPrize ให้คนนั้นๆไหมก่อนจะนำข้อมูลไปเก็บใน Map
        userDatabase[{name, pass}].push_back(dp);
        userDatabase[{name, pass}].push_back(mn);
        userDatabase[{name, pass}].push_back(to_string(boolLoggedin));
        userDatabase[{name, pass}].push_back(to_string(rst));
    }
    source.close();
}

// ฟังก์ชันสำหรับ Login ผู้ใช้งาน //

//**************************************************************//
//                                                             //
//             >>ระบบLogin   1000000%                         //
//                                                           //
//__________________________________________________________//

void Database::loginUser()
{ // ตรวจสอบว่ามีบัญชีในฐานข้อมูลหรือไม่
    // ตรวจสอบว่ามีชื่ออยุ่ในฐานข้อมูลไหมน้าาา
    string un; // เก็บข้อมูล
    string pw; // เก็บข้อมูล
    bool n = true;
    bool m = true;
    bool checkUN = false;
    bool checkPW = false;
    cout << "User Login\n";
    while (n)
    {
        cout << "Username  : ";
        cin >> un;

        for (const auto &element : userDatabase)
        {
            if (un == element.first.first)
            {
                checkUN = true;
                n = false;
            }
        } // เช็คว่าซ้ำไหม
        if (!checkUN)
        {
            cout << "Couldn't find your username\n";
            cout << "Please enter your username again.\n";
        }
    }
    // ตรวจสอบว่ารหัสผ่านถูกต้องหรือไม่
    while (m)
    {
        cout << "Password : ";
        cin >> pw;
        auto it = userDatabase.find({un, pw});
        if (it != userDatabase.end())
        {
            checkPW = true;
            m = false;
            cout << "User " << un << " has logged in successfully.\n";
            if (userDatabase[{un, pw}][2] == "0" && time(0) > stoi(userDatabase[{un, pw}][3]))//เวลาปัจจุบันมากกว่า รีเซต time
            {
                dailyPrize(un, pw);
            }
            loginUserName.push_back(un);
            break;
        }
        if (checkPW == false)
        {
            cout << "Incorrect password for user " << un << ".\n";
            loginUser();
            return;
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
    string displayname;
    string freeCredit = "500";
    string login = "0";
    string time = "0" ;
    // ไม่มี money เพราะ money ถูก Fix แล้ว 500 บาท
    int num_UserRegister;
    bool valid = false;
    while (true)
    {
        cout << "Username : ";
        cin >> username;
        bool found = false;
        for (const auto &element : userDatabase)
        {
            if (username == element.first.first) // ถ้าของเราไปตรง Usernameในแมพ
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
    setDisplayName(displayname);
    userDatabase[{username, password}].push_back(displayname);
    userDatabase[{username, password}].push_back(freeCredit);
    userDatabase[{username, password}].push_back(login);
    userDatabase[{username, password}].push_back(time);
    writeData2_txt();

    cout << "User " << username << " has been registered successfully." << endl;
    cout << "You recieve free credit : $" << freeCredit << " Dollar\n";
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                  ////
////                                                                                                  ////
////                                            Daily Login                                           ////
////                                                                                                  ////
////                                                                                                  ////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Database::reset(int &logedin, unsigned long long int &resetTime)
{ // reset ค่า loggedin ให้เป็น false ทุก ๆ 00.00 น.
    if (time(0) > resetTime){
        logedin = 0;
    }
}
unsigned long long int Database::setResetTime()
{

    // set เวลา reset โดยอ้างอิงเวลาของ วันที่ 01/01/23 เวลา 00.00 น.
    time_t base = 1672506000; // Thu Jan  1 00:00:00 2023
    struct tm t1 = *localtime(&base);
    time_t next = mktime(&t1);

    time_t now = time(0); // เวลาตอนนี้
    struct tm t2 = *localtime(&now);
    time_t next2 = mktime(&t2);

    int a = t2.tm_yday - t1.tm_yday;

    time_t reset = base + 86400 * (a + 1); // เวลา reset
    return reset;
}

#endif
