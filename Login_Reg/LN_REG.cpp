#include <iostream>
#include <string>
#include <map>
<<<<<<< HEAD
#include <fstream>
#include <vector>
=======
#include<fstream>
#include<vector>
#include<cstdlib>
#include<set>
>>>>>>> 6825746765c9565f9714b04cfb59318304ad6f2c
using namespace std;

// สร้าง map เพื่อเก็บข้อมูลของผู้ใช้งาน
map<string, string> userDatabase;

<<<<<<< HEAD
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
=======


class Database{
    public:
string username,password;

string toUpperStr(string);
void registerUser(string,string);
void loginUser(string,string);
void writeData2_txt(const map<string,string>&, const string&);
void importDatafromfile(string,vector<string> &,vector<string> &);
void Delete_();
};

void Database::Delete_(){
    set<string> collet;
    string line;
    ifstream file("DataLN&RG.txt");
    
    if(file.is_open()){
        while(getline(file,line)){
            collet.insert(line);
        }
        file.close();
    }
    
    ofstream newfile("DataLN&RG.txt");
    for(auto it = collet.begin();it != collet.end();++it){
        
        newfile << *it<<endl;
    }
newfile.close();



}

void Database::writeData2_txt(const map<string,string>&userDatabase, const string&Datatxt){
    ofstream dest(Datatxt,std::ios::app);
    
    for(const auto& [username,password]:userDatabase){
        dest<<username << " "<<password<<'\n';
>>>>>>> 6825746765c9565f9714b04cfb59318304ad6f2c
    }
    dest.close();
}

<<<<<<< HEAD
// ฟังก์ชันสำหรับ Login ผู้ใช้งาน //
=======
void Database::importDatafromfile(string filename ,vector<string> &un,vector<string> &pw){

    ifstream source(filename.c_str());
    string line;
    char format[] = "%s %s";
    char name[100];
    char pass[100];
    while(getline(source,line)){
        sscanf(line.c_str(),format,name,pass);

        un.push_back(name);
        pw.push_back(pass);
    }
source.close();

}

string Database::toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}



              // ฟังก์ชันสำหรับ Login ผู้ใช้งาน //
>>>>>>> 6825746765c9565f9714b04cfb59318304ad6f2c

//**************************************************************//
//                                                             //
//             >>ระบบLogin   1000000%                         //
//                                                           //
//__________________________________________________________//

<<<<<<< HEAD
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
=======

void Database::loginUser(string username, string password){   // ตรวจสอบว่ามีบัญชีในฐานข้อมูลหรือไม่
vector<string> un;
vector<string> pw;            
int num_Userlogin;
bool valid = false; 
            while(!valid){                               //ฟังก์ชั่นเช็คต้องใส่ตัวเลขเท่านั้น
            cout<<"How UserLogin ? :";
            cin>>num_Userlogin;

                if(cin.fail()){
                    cin.clear();
                    cin.ignore(10000,'\n');
                    cout<<"Please enter number !!!\n";
                }else{
                    valid = true;
                }
                  }
                  

>>>>>>> 6825746765c9565f9714b04cfb59318304ad6f2c

    cout << "User Login\n";

<<<<<<< HEAD
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
=======

 for(int i=1;i<=num_Userlogin;i++){   
                                                         //ตรวจสอบว่ามีชื่ออยุ่ในฐานข้อมูลไหมน้าาา
    bool n = true;
    bool m = true;
    bool checkUN = false; 
    bool checkPW = false;
while(n){
    cout<<"Username  : ";
    cin>>username;

    for(unsigned int i=0;i<un.size();i++){               //เช็คว่ามีชื่อในระบบไหม

            if(username == un[i]){
                checkUN = true;
                n = false;
            }
    }  
    if(checkUN == false){
        cout<<"Couldn't find your username\n";
        cout<<"Please enter your username again.\n";
    }
}   
     
                                                 // ตรวจสอบว่ารหัสผ่านถูกต้องหรือไม่
    while(m){
        cout<<"Password : ";
        cin>>password;
    for(unsigned int i =0;i<pw.size(); i++) {

        if(password == pw[i]){
                checkPW = true;
                m = false;
              cout << "User " << username << " has logged in successfully.\n";  
                i = num_Userlogin+10;
            }  
    }

    if(checkPW == false){
            cout << "Incorrect password for user " << username << ".\n";
        } 
}
}

}






                    // ฟังก์ชันสำหรับ Register ผู้ใช้งาน //

//**************************************************************//
//                                                             //
//             >>ระบบRegister   %                              //
//   ** reg ครั้งต่อมาใส่ชื่อซ้ำได้    **เช็ค ตัวเล็กใหญ่ยังไม่ได้          //
//__________________________________________________________//
>>>>>>> 6825746765c9565f9714b04cfb59318304ad6f2c

// ฟังก์ชันสำหรับ Register ผู้ใช้งาน  // เพิ่มข้อมูลผู้ใช้งานลงในฐานข้อมูล
<<<<<<< HEAD
void Database::registerUser(string username, string password)
{

    string passwordCF;
    int num_UserRegister;
    bool valid = false;
    while (!valid)
    {
        cout << "How UserRegister ? : ";
        cin >> num_UserRegister;
=======
void Database::registerUser(string username, string password){
   
   
    string passwordCF;
    int num_UserRegister;
    bool valid = false;
    while(!valid){                                                  //checkต้องnum เท่านั้น
        cout<<"How UserRegister ? : ";
        cin>>num_UserRegister;
>>>>>>> 6825746765c9565f9714b04cfb59318304ad6f2c

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
<<<<<<< HEAD
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
=======
}   


cout<<"User Register\n";

    for(int i=1;i<=num_UserRegister;i++ ){
    bool n = true;
    bool m = true;
    bool checkUN = false; 
    bool checkPW = false;
    
    
     while(true){
    cout<<"Username : ";
    cin>>username;
     if(userDatabase.count(username)>0 ){
        cout<<"That username is taken. Try another\n";

     }else if(username == toUpperStr(username)){
        cout<<"That username is taken. Try another\n";
    
    }else{
        break;
    }

    }
    while(true){
    cout<<"Password : ";
    cin>>password;
    cout<<"Confirm Passwowrd : ";
    cin>>passwordCF;
    if(password == passwordCF) break;
   else if(password != passwordCF){
    cout<<"Passwords didn't match. Try again.\n";
   }
    }
    userDatabase[username] = password;                                                 //  จัดลำดับให้ตรง user-> pass
    writeData2_txt(userDatabase,"DataLN&RG.txt");                                      //เขียนinput ลงไปในไฟล์
    Delete_();                                                                        //ไว้ลบตัวซ้ำ
    
    cout << "User " << username << " has been registered successfully." << endl;
    
}
    
>>>>>>> 6825746765c9565f9714b04cfb59318304ad6f2c
}

int main()
{

<<<<<<< HEAD
    Database x;
    x.num_player = 4;
    x.registerUser(x.username, x.password);
    //   x.loginUser(x.username,x.password);
=======
int main() {
    
Database x;
   
    x.registerUser(x.username, x.password);
   // x.loginUser(x.username,x.password);
>>>>>>> 6825746765c9565f9714b04cfb59318304ad6f2c
    return 0;
}
