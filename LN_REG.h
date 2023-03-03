#ifndef PROJECT1_H
#define PROJECT1_H
// สร้าง map เพื่อเก็บข้อมูลของผู้ใช้งาน
Database::Database()
{
    importDatafromfile();
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
    char format[] = "%s %s %s %s ";
    char name[100];
    char pass[100];
    char dp[100];
    char mn[100];
    while (getline(source, line))
    {
        sscanf(line.c_str(), format, name, pass, dp, mn);
        userDatabase[{name, pass}].push_back(dp);
        userDatabase[{name, pass}].push_back(mn);
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
    cin.ignore();
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
    writeData2_txt();

    cout << "User " << username << " has been registered successfully." << endl;
    cout << "You recieve free credit : $" << freeCredit << " Dollar\n";
}
#endif
