#ifndef PROJECT1_H
#define PROJECT1_H
// สร้าง map เพื่อเก็บข้อมูลของผู้ใช้งาน
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
            displayname.push_back(input);
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
    ofstream dest(filename, std::ios::app);

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

void Database::importDatafromfile() // อ่านไฟล์จากไฟล์หลักพร้อมกับเขียนMapขึ้นมา
{
    un.clear();
    pw.clear();
    displayname.clear();
    money.clear();
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

        un.push_back(name);
        pw.push_back(pass);
        displayname.push_back(dp);
        money.push_back(mn);
        userDatabase[make_pair(name, pass)].push_back(displayname.back());
        userDatabase[make_pair(name, pass)].push_back(mn);
    }
    source.close();
}

// ฟังก์ชันสำหรับ Login ผู้ใช้งาน //

//**************************************************************//
//                                                             //
//             >>ระบบLogin   1000000%                         //
//                                                           //
//__________________________________________________________//

void Database::loginUser(vector<int> &loginIndex)
{ // ตรวจสอบว่ามีบัญชีในฐานข้อมูลหรือไม่
    importDatafromfile();
    string userN;    // แค่ไว้เช็ค
    string password; // แค่ไว้เช็ค
    bool valid = false;

    cout << "User Login\n";
    // ตรวจสอบว่ามีชื่ออยุ่ในฐานข้อมูลไหมน้าาา
    bool n = true;
    bool m = true;
    bool checkUN = false;
    bool checkPW = false;
    while (n)
    {
        cout << "Username  : ";
        cin >> userN;

        for (unsigned int i = 0; i < un.size(); i++)
        { // เช็คว่ามีชื่อในระบบไหม

            if (userN == un[i])
            {
                loginIndex.push_back(i);
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
        if (password == pw[loginIndex.back()])
        {
            checkPW = true;
            m = false;
            cout << "User " << userN << " has logged in successfully.\n";
            break;
        }
        if (checkPW == false)
        {
            loginIndex.pop_back();
            cout << "Incorrect password for user " << userN << ".\n";
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
    string freeCredit = "500";
    string username;
    string password;
    string passwordCF;
    int num_UserRegister;
    bool valid = false;
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
    setDisplayName();
    userDatabase[make_pair(username, password)].emplace_back(displayname.back());
    userDatabase[make_pair(username, password)].emplace_back(freeCredit);
    writeData2_txt();

    cout << "User " << username << " has been registered successfully." << endl;
    cout << "You recieve free credit : $" << freeCredit << " Dollar\n";
    Delete_();
} // แปลว่าตอนเอาเงินไปอัพเดทจำเป็นต้องเขียน
#endif
