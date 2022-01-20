#include <bits/stdc++.h>    //INCLUDE SEMUA STANDAR LIBRARY C++
#include <sys/stat.h>       //INCLUDE HEADER SYSYEM DIGUNAKAN UNTUK MEMBUAT FOLDER

#ifdef _WIN32    /*MACRO PREDEFINED UNTK MENGETAHUI OS YANG DIGUNAKAN SAAT COMPILING*/
    #include <windows.h>    //INCLUDE HEADER BAWAAN DARI WINDOWS 

#else 
    #include <unistd.h>     //INCLUDE HEADER BAWAAN DARI LINUX

#endif  

#define EXIT_STATUS_SUCCESS 0
#define EXIT_STATUS_FAIL 1 

using namespace std;

struct stat buffer;

struct System{

    unsigned int Select;

    void clearScr(){
        #if defined (WIN32) || defined (_WIN32) || defined (__WIN32__) || defined (__NT__)  // MACROS PREDEFINED UNTUK MENGETAHUI OS YANG DIGUNAKAN ADALAH WINDOWS
            #ifdef __WIN64__
                system("cls");
            #else
                system("cls");
            #endif
            
        #else     // MACROS PREDEFINED UNTUK MENGETAHUI OS YANG DIGUNAKAN ADALAH SELAIN WINDOWS
            system("clear");

        #endif
    }

    void sleeps(string timeSleep){
        string sleepLinux = "sleep "+timeSleep+"s";

        #ifdef __linux__
            system(sleepLinux.c_str());
        
        #else 
            Sleep(1200);

        #endif

    }

    void pauseProgram(){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max() , '\n');

        string dummy;
        cout<<"Press ENTER to continue....."; getline(cin, dummy);
    }

};

struct Database{
    const string pathDatabase = "database/";

    time_t nowTime = time(0);
    char* outputTime = ctime(&nowTime);

    unsigned int userBalance;
    string longName;

    bool checkIfExist(string dbUserLoc){
        string pathUser = "database/"+dbUserLoc;

        if(stat(pathDatabase.c_str(), &buffer) != 0){
            return false;
        }

        else{
            if(stat(pathUser.c_str(), &buffer) == 0){
                return true;
            }
            else{
                return false;
            }
        }
    }

    bool checkIfDestExist(string dbDestLoc){
        string pathChecker = "database/"+dbDestLoc;

        if(stat(pathChecker.c_str(), &buffer) != 0){
            return false;
        }
        return true;
    }

    void saveToDatabase(string dbUserLoc, string dbPassword, string longName, string userEmail, int Number[16], unsigned int Pin, unsigned int balanceUser){
        string pathUser = "database/"+dbUserLoc;

        string databaseUser = pathUser+"/userInfo.dat";
        string databaseNumber = pathUser+"/numberInfo.dat";

        string databaseBalance = pathUser+"/balanceInfo.dat";
        string databaseSelfUser = pathUser+"/selfInfo.dat";

        if(stat(pathDatabase.c_str(), &buffer) != 0){
            #ifdef __linux__
                mkdir(pathDatabase.c_str(), 0777);
                mkdir(pathUser.c_str() , 0777);
            #else 
                mkdir(pathDatabase.c_str());
                mkdir(pathUser.c_str());
            #endif

            ofstream saveDbUser(databaseUser.c_str());
            saveDbUser << dbUserLoc << endl << dbPassword;
            
            ofstream saveDbNumber(databaseNumber.c_str());
            for(int i=0; i<16; i++){
                saveDbNumber << Number[i];
            }
            saveDbNumber << Pin;

            ofstream saveDbSelf(databaseSelfUser.c_str());
            saveDbSelf << longName << endl << userEmail;

            ofstream saveDbBalance(databaseBalance.c_str());
            saveDbBalance << balanceUser;
        }

        else{
            #ifdef __linux__
                mkdir(pathUser.c_str() , 0777);
            #else
                mkdir(pathUser.c_str());
            #endif

            ofstream saveDbUser(databaseUser.c_str());
            saveDbUser << dbUserLoc << endl << dbPassword;
            
            ofstream saveDbNumber(databaseNumber.c_str());
            for(int i=0; i<16; i++){
                saveDbNumber << Number[i];
            }

            saveDbNumber << Pin;

            ofstream saveDbSelf(databaseSelfUser.c_str());
            saveDbSelf << longName << endl << userEmail;

            ofstream saveDbBalance(databaseBalance.c_str());
            saveDbBalance << balanceUser;
        }
    }

    bool balanceChecker(string dbUserLoc, unsigned int Balance){
        string pathBalance = "database/"+dbUserLoc+"/balanceInfo.dat";
        ifstream readBalance(pathBalance.c_str());

        unsigned int userBalance;
        readBalance >> userBalance;

       if(Balance >= userBalance){
           return false;
       }
       return true;
    }

    void updateTransferBalance(string dbUserLoc, string dbDestLoc, unsigned int balanceTransfer){
        string pathDestBalance = "database/"+dbDestLoc+"/balanceInfo.dat";
        string pathUserBalance = "database/"+dbUserLoc+"/balanceInfo.dat";

        unsigned int nowBalance;
        unsigned int nowUserBalance;

        ifstream readDestBalance(pathDestBalance.c_str());
        readDestBalance >> nowBalance; readDestBalance.close();

        ifstream readUserBalance(pathUserBalance.c_str());
        readUserBalance >> nowUserBalance; readUserBalance.close();

        unsigned int updateBalance = nowBalance + balanceTransfer;
        unsigned int updateUserBalance = nowUserBalance - balanceTransfer;

        ofstream updateDestBalance(pathDestBalance.c_str());
        updateDestBalance << updateBalance; updateDestBalance.close();

        ofstream updateNowBalance(pathUserBalance.c_str());
        updateNowBalance << updateUserBalance; updateNowBalance.close();
    }

    bool updateUserPassword(string dbUserLoc, string oldPassword, string newPassword){
        string pathUser = "database/"+dbUserLoc+"/userInfo.dat";
        ifstream readPassword(pathUser.c_str());

        string tempUser;
        string passwordValidator;
        
        getline(readPassword, tempUser); getline(readPassword, passwordValidator);

        if(oldPassword == passwordValidator){
            ofstream updatePassword(pathUser.c_str());
            updatePassword << tempUser << endl << newPassword;

            return true;
        }
        return false;
    }
    
    void historyTransfer(string dbUserLoc, string dbDestLoc, unsigned int balanceTransfer){
        vector<int> randomNum;
        srand(time(0));

        for(int i=0; i<8; i++){
            int x = (rand()%9); 
            randomNum.push_back(x);
        }
        
        int id = 0; int sizeOfVect = randomNum.size();
        for(int i=0; i<sizeOfVect; i++){
        	id = id + randomNum[i] * pow(10, sizeOfVect - i - 1);
		}
		string outputID = to_string(id);

        const string Date = "DATE TRANSFER : ";
        const string Balance = "BALANCE TRANSFER : Rp. ";
        const string nowBalance = "NOW BALANCE : Rp. ";
        const string Destination = "DESTINATION TRANSFER USERNAME : ";
        const string DestinationLN = "DESTINATION TRANSFER LONG NAME : ";
        const string IdTransfer = "ID TRANSFER : ";
        const string Success = "TRANSFER STATUS = SUCCESS";

        string checkPATH = "database/"+dbUserLoc+"/history";
        string pathUserBalance = "database/"+dbUserLoc+"/balanceInfo.dat";
        string pathUser = checkPATH+"/transfer-"+outputID+".dat";
        string destPATH = "database/"+dbDestLoc+"/selfInfo.dat";
        
        unsigned int userBalance;
        ifstream readUserBalance(pathUserBalance.c_str());

        readUserBalance >> userBalance;

        string Name;

        ifstream readName(destPATH.c_str());
        getline(readName , Name); readName.close();

        vector<string> nameInput;
        nameInput.push_back(Name);

        for(auto &str:nameInput){
            for(auto &ch:str){
                ch = toupper(ch);
            }
        }

        if(stat(checkPATH.c_str(), &buffer) != 0){
            #ifdef __linux__
                mkdir(checkPATH.c_str() , 0777);
            #else   
                mkdir(checkPATH.c_str());
            #endif
            
            ofstream saveHistory(pathUser.c_str());

            saveHistory << Date << outputTime << endl << Balance << balanceTransfer << endl << nowBalance << userBalance << endl << Destination << dbDestLoc << endl << DestinationLN;

            for(auto longName: nameInput){
                saveHistory << longName;
            }

            saveHistory << endl << IdTransfer;
            for(auto ID : randomNum){
                saveHistory << ID;
            }

            saveHistory << endl << Success;
        }
        else{
            ofstream saveHistory(pathUser.c_str());

            saveHistory << Date << outputTime << endl << Balance << balanceTransfer << endl << Destination << dbDestLoc << endl << DestinationLN;

            for(auto longName : nameInput){
                saveHistory << longName;
            }
            
            saveHistory << endl << IdTransfer;
            for(auto ID : randomNum){
                saveHistory << ID;
            }

            saveHistory << endl << Success;
        }

    }

    void historyDeposit(string dbUserLoc, unsigned int balanceDeposit){
        vector<int> randomNum;
        srand(time(0));

        for(int i=0; i<8; i++){
            int x = (rand()%9); 
            randomNum.push_back(x);
        }
        
        int id = 0; int sizeOfVect = randomNum.size();
        for(int i=0; i<sizeOfVect; i++){
        	id = id + randomNum[i] * pow(10, sizeOfVect - i - 1);
		}
		string outputID = to_string(id);

        string checkPath = "database/"+dbUserLoc+"/history";
        string pathHistory = checkPath+"/deposit-"+outputID+".dat";
        string pathBalance = "database/"+dbUserLoc+"/balanceInfo.dat";
        string pathLongName = "database/"+dbUserLoc+"/selfInfo.dat";

        const string Date = "DATE DEPOSIT : ";
        const string Name = "NAME : ";
        const string Deposit = "DEPOSIT BALANCE : Rp. ";
        const string nowBalance = "NOW BALANCE : Rp. ";
        const string idDeposit = "ID DEPOSIT : ";
        const string SUCCESS = "DEPOSIT STATUS : SUCCESS"; 

        ifstream readBalance(pathBalance.c_str());
        readBalance >> userBalance; readBalance.close();

        ifstream readLongName(pathLongName.c_str());
        getline(readLongName , longName); readLongName.close();

        vector <string> nameInput;
        nameInput.push_back(longName);

        for(auto &str : nameInput){
            for(auto &ch : str){
                ch = toupper(ch);
            }
        }
		
        if(stat(checkPath.c_str(), &buffer) != 0){
            #ifdef __linux__
                mkdir(checkPath.c_str() , 0777);
            #else
                mkdir(checkPath.c_str());
            #endif

            ofstream saveHistory(pathHistory.c_str());

            saveHistory << Date << outputTime << endl << Name;
            for(auto Ln : nameInput){
                saveHistory << Ln;
            } 
            
            saveHistory << endl << Deposit << balanceDeposit << endl << nowBalance << userBalance << endl << idDeposit;
            for(auto ID : randomNum){
                saveHistory << ID;
            }

            saveHistory << endl << SUCCESS;
        }
        else{
            ofstream saveHistory(pathHistory.c_str());
            
            saveHistory << Date << outputTime << endl << Name;
            for(auto Ln : nameInput){
                saveHistory << Ln;
            } 
            
            saveHistory << endl << Deposit << balanceDeposit << endl << nowBalance << userBalance << endl << idDeposit;
            for(auto ID : randomNum){
                saveHistory << ID;
            }

            saveHistory << endl << SUCCESS;
        }
    }

    void historyWithdraw(string dbUserLoc, unsigned int balanceWithdraw){
        const string Date = "DATE WITHDRAW = ";
        const string Name = "NAME = ";
        const string Withdraw = "WITHDRAW BALANCE = Rp. ";
        const string nowBalance = "NOW BALANCE = Rp. ";
        const string idWithdraw = "ID WITHDRAW = ";
        const string SUCCESS = "WITHDRAW STATUS = SUCCESS";

        vector<int> randomNum;
        srand(time(0));

        for(int i=0; i<8; i++){
            int x = (rand()%9); 
            randomNum.push_back(x);
        }
        
        int id = 0; int sizeOfVect = randomNum.size();
        for(int i=0; i<sizeOfVect; i++){
        	id = id + randomNum[i] * pow(10, sizeOfVect - i - 1);
		}
		string outputID = to_string(id);

        string checkPath = "database/"+dbUserLoc+"/history";
        string pathHistory = checkPath+"/withdraw-"+outputID+".dat";
        string pathBalance = "database/"+dbUserLoc+"/balanceInfo.dat";
        string pathLongName = "database/"+dbUserLoc+"/selfInfo.dat";

        ifstream readLongName(pathLongName.c_str());
        getline(readLongName, longName); readLongName.close();

        ifstream readUserBalance(pathBalance.c_str());
        readUserBalance >> userBalance; readUserBalance.close(); 

        vector <string> nameInput;
        nameInput.push_back(longName);

        for(auto &str : nameInput){
            for(auto &ch : str){
                ch = toupper(ch);
            }
        }     

        if(stat(checkPath.c_str(), &buffer) != 0){
            #ifdef __linux__
                mkdir(checkPath.c_str() , 0777);
            #else 
                mkdir(checkPath.c_str());
            #endif

            ofstream saveHistory(pathHistory.c_str());

            saveHistory << Date << outputTime << endl << Name; 
            for(auto LN : nameInput){
                saveHistory << LN;
            }

            saveHistory << endl << Withdraw << balanceWithdraw << endl << nowBalance << userBalance << endl << idWithdraw;
            for(auto ID : randomNum){
                saveHistory << ID;
            }

            saveHistory << endl << SUCCESS;
            saveHistory.close();
        }        
        else{
            ofstream saveHistory(pathHistory.c_str());
            saveHistory << Date << outputTime << endl << Name; 
            for(auto LN : nameInput){
                saveHistory << LN;
            }

            saveHistory << endl << Withdraw << balanceWithdraw << endl << nowBalance << userBalance << endl << idWithdraw;
            for(auto ID : randomNum){
                saveHistory << ID;
            }

            saveHistory << endl << SUCCESS;
            saveHistory.close();   
        }

    }
};

class userRegister{
    public:
        string regUsername;
        string regPassword;
        string matchingPassword;

        string longName;
        string regEmail;

        int Number[16];
        unsigned int Pin;
        unsigned int Deposit;

    void numberInfo(){
        for(int i=0; i<16; i++){
            cout<<Number[i];
        }
    }
    
    void displayLongName(string dbUserLoc){
    	string pathLongName = "database/"+dbUserLoc+"/selfInfo.dat";
    	ifstream readLongName(pathLongName.c_str());
    	
    	vector<string> upperName;
    	string longName;
    	
    	getline(readLongName, longName);
    	upperName.push_back(longName);
    	
    	for(auto &str : upperName){
    		for(auto &ch : str){
    			ch = toupper(ch);
			}
		}
		
		for(auto capital : upperName){
			cout<<capital;
		}
		
		readLongName.close();
	}
    
};

class userLogin{
    public: 
        string loginUsername;
        string loginPassword;

        string destinationUser;
        string newPassword;
        string matchingPassword;

        unsigned int Select;
        unsigned int balanceInput;

        unsigned int transferBalance;
        int userInput;
        int convertVectorInt;
    
    bool loginCheck(string dbUserLoc, string dbPassLoc){
        string pathUser = "database/"+dbUserLoc+"/userInfo.dat";
        
        string Username;
        string Password;

        ifstream readUserData(pathUser.c_str());
        getline(readUserData, Username); getline(readUserData, Password);

        if(dbUserLoc == Username and dbPassLoc == Password){
            return true;
        }
        return false;
    }
    
    void loginWelcome(string dbUserLoc){
        string pathLongName = "database/"+dbUserLoc+"/selfInfo.dat";

        ifstream readLongName(pathLongName.c_str());
        string LongName;

        getline(readLongName , LongName);
        
        vector<string> nameInput;
        nameInput.push_back(LongName);

        for(auto &str : nameInput){
            for(auto &ch : str){
                ch = toupper(ch);
            }
        }
        for(auto upperWelcome : nameInput){
            cout<<upperWelcome;
        }
    }

    void displayUserInfo(string dbDestUser){
        string pathLongName = "database/"+dbDestUser+"/selfInfo.dat";
        string LongName;

        ifstream readLongName(pathLongName.c_str());
        getline(readLongName, LongName);
        
        vector<string> nameDisplay;
        nameDisplay.push_back(LongName);

        for(auto &str : nameDisplay){
            for(auto &ch : str){
                ch = toupper(ch);
            }
        }
        for(auto upperName : nameDisplay){
            cout<<upperName;
        }
    }

    void depositBalance(string dbUserLoc , unsigned int balanceDeposit){
        string pathDeposit = "database/"+dbUserLoc+"/balanceInfo.dat";
        ifstream readBalance(pathDeposit.c_str());

        unsigned int userBalance;
        readBalance >> userBalance;
	
        unsigned int sumBalance = userBalance + balanceDeposit;
        ofstream saveBalance(pathDeposit.c_str());

        saveBalance << sumBalance;
        cout<<"Deposit Success....";
    }

    void withdrawBalance(string dbUserLoc, unsigned int balanceWithdraw){
        string pathBalance = "database/"+dbUserLoc+"/balanceInfo.dat";
        ifstream readBalance(pathBalance.c_str());

        unsigned int userBalance;
        readBalance >> userBalance;

        unsigned int minBalance = userBalance - balanceWithdraw;
        ofstream saveBalance(pathBalance.c_str());

        saveBalance << minBalance;
        cout<<"Withdraw Success...."<<endl;
    }

    void balanceInfo(string dbUserLoc){
        string pathBalance = "database/"+dbUserLoc+"/balanceInfo.dat";
        ifstream readBalance(pathBalance.c_str());

        unsigned int userBalance;
        readBalance >> userBalance;

        cout<<"Rp. "<<userBalance;
    }

    int processRandomNumber(){
        vector<int> randNUMBER;

        srand(time(0));
        for(int i=0; i<6; i++){
            int thisRandom = (rand()%9);
            randNUMBER.push_back(thisRandom);
        }

        convertVectorInt = 0; int N = randNUMBER.size();

        for(int i = 0; i < N; i++){
            convertVectorInt = convertVectorInt + randNUMBER[i] * pow(10, N-i-1);
        }

        return convertVectorInt;
    }
    
    bool checkIfNotRobot(int checkInput){
        if(checkInput == convertVectorInt){
            return true;
        }
        return false;
    }
     
};


int main(){
    System system;
    Database regDatabase, logDatabase;
    
    userRegister Register;
    userLogin Login;

    mainMenu:
        system.clearScr();
       
        cout<<"============================="<<endl;
        cout<<"||------    Menu:   ------ ||"<<endl;
        cout<<"============================="<<endl;
        cout<<"||   1. Register           ||"<<endl;
        cout<<"||   2. Login              ||"<<endl;
        cout<<"||   3. Exit               ||"<<endl;
        cout<<"============================="<<endl;
        cout<<"|||||||||||||||||||||||||||||"<<endl;
        cout<<"============================="<<endl;
        cout<<"||   Select Choice  : ";               cin>>system.Select;
        cout<<"============================="<<endl;

        if(system.Select == 1){
            registerUsername:
                cout<<"\nInput Username : "; cin>>Register.regUsername;
                
                if(!regDatabase.checkIfExist(Register.regUsername)){
                    cin.ignore();
                    cout<<"\nEnter Full Name : "; getline(cin, Register.longName);
                    cout<<"Enter your E-Mail : "; getline(cin, Register.regEmail);

                    registerPassword:
                        cout<<"\nInput Password   : "; getline(cin, Register.regPassword);
                        cout<<"Re-Type Password : "; getline(cin, Register.matchingPassword);

                        if(Register.regPassword != Register.matchingPassword){
                            cout<<"\nPassword Does not match...."<<endl;
                            cout<<"Input Again"<<endl;

                            system.pauseProgram();
                            goto registerPassword;
                        }

                        else{
                            cout<<"\nGenerating Virtual Account Number....."<<endl;
            
                            srand(time(0));
                            for(int i=0; i<16; i++){
                                Register.Number[i] = (rand() % 9);
                            }

                            cout<<"Your Virtual Account Number is: ";cout<<endl;
                            cout<<"============================="<<endl;
                            cout<<"||     ";Register.numberInfo();cout<<"    ||"<<endl;
                            cout<<"============================="<<endl;

                            cout<<"\nCreate Pin for your Virtual Account Number"<<endl;
                            cout<<"Input PIN Number :  >> "; cin>>Register.Pin;
							
							BalanceInput:
							try {
								
	                                cout<<"\nPlease Deposit First. Mimimum deposit is Rp.100.000"<<endl;
	                                cout<<"\nEnter Balance to deposit: Rp. "; cin>>Register.Deposit;
	
		                            captchaInput:
		                            system.clearScr();
		                            
	                                cout<<"============================="<<endl;
	                                cout<<"|||||||||||||||||||||||||||||"<<endl;
	                                cout<<"============================="<<endl;
	                                cout<<"||      Check Captcha      ||"<<endl;
	                                cout<<"||  Captcha Value: "<< Login.processRandomNumber() <<"  ||" << endl;
	                                cout<<"============================="<<endl;
	                                cout<<"============================="<<endl;
	                                cout<<"== >> Input Value : "; cin>>Login.userInput;  
	
	                                cout<<"============================="<<endl;
	
	                                if(Login.checkIfNotRobot(Login.userInput)){ 
	                                
	                                	if(Register.Deposit < 999999999 and Register.Deposit >= 100000){
									
		                                    regDatabase.saveToDatabase(Register.regUsername, Register.regPassword, Register.longName, Register.regEmail, Register.Number, Register.Pin, Register.Deposit);
		
		                                    regDatabase.historyDeposit(Register.regUsername, Register.Deposit);
		                                    cout<<"\nAcoount Register Succesfully...."<<endl;
		                                    cout<<endl;
		                                    
		                                    cout<<"Account Detail  : "<<endl;
		                                    cout<<"USERNAME        : "<<Register.regUsername<<endl;
											cout<<"PASSWORD        : "<<Register.regPassword<<endl;
											
											cout<<"FULL NAME       : "; Register.displayLongName(Register.regUsername); cout<<endl;
											cout<<"E-MAIL          : "<<Register.regEmail<<endl;
											
											cout<<"VIRTUAL NUMBER  : "; Register.numberInfo(); cout<<endl;
											cout<<"PIN NUMBER      : "<<Register.Pin<<endl;
											cout<<"ACCOUNT BALANCE : Rp. "<<Register.Deposit<<endl<<endl; 
											
		                                    system.pauseProgram();
		                                    goto mainMenu;
		                                }
		
		                                else{
		                                    throw(Register.Deposit);
		                                }
		                            }
	
	                                else{
	                                    cout<<"Captcha is not same! Input again..."<<endl;
	
	                                    system.pauseProgram();
	                                    goto captchaInput;
	                                }
                        	}
                        	
                        	catch(unsigned int Deposit){
                        		cout<<"Can't deposit higher than Rp. 1.000.000.000 or Lower than Rp. 100000"<<endl;
	                            cout<<"Input again"<<endl;
	                                    
	                         	system.pauseProgram();
		                    	goto BalanceInput;
							}
                		}
				}
				
                else{
                    cout<<"This Username was already taken, choose another one!"<<endl;
                    goto registerUsername;
                }
        }
        
        else if(system.Select == 2){
            loginMenu:

            system.clearScr();  

            cout<<"============================="<<endl;
            cout<<"||----   Login Menu:   ----||"<<endl;
            cout<<"============================="<<endl;
            cout<<"||   Input Username: "; cin>>Login.loginUsername;
            cout<<"||   Input Password: "; cin>>Login.loginPassword;
            cout<<"============================="<<endl;
            cout<<"|||||||||||||||||||||||||||||"<<endl;
            cout<<"============================="<<endl;
            cout<<"||      Check Captcha      ||"<<endl;
            cout<<"||  Captcha Value: "<< Login.processRandomNumber() <<"  ||" << endl;
            cout<<"============================="<<endl;
            cout<<"============================="<<endl;
            cout<<"== >> Input Value : "; cin>>Login.userInput;  

            cout<<"============================="<<endl;

            if(Login.checkIfNotRobot(Login.userInput)){ 

                if(logDatabase.checkIfExist(Login.loginUsername)){

                    if(Login.loginCheck(Login.loginUsername, Login.loginPassword)){
                        system.sleeps("1"); 
                        cout<<"||  Login Successfully...  ||"<<endl;
                        cout<<"============================="<<endl;
                        system.sleeps("2");

                        loginChoice:
                        system.clearScr();
                            cout<<"Welcome, "; Login.loginWelcome(Login.loginUsername); cout<<endl;
                            cout<<"============================="<<endl;
                            cout<<"||--   Dashboard Menu:   --||"<<endl;
                            cout<<"============================="<<endl;
                            cout<<"||    1. Deposit           ||"<<endl;
                            cout<<"||    2. Withdraw          ||"<<endl;
                            cout<<"||    3. Transfer          ||"<<endl;
                            cout<<"||    4. Check Balance     ||"<<endl;
                            cout<<"||    5. Change Passowrd   ||"<<endl;
                            cout<<"||    6. Logout            ||"<<endl;
                            cout<<"============================="<<endl;
                            cout<<"|||||||||||||||||||||||||||||"<<endl;
                            cout<<"============================="<<endl;
                            cout<<"|| Input your choice: "; cin>>Login.Select;
                            cout<<"============================="<<endl;

                            if(Login.Select == 1){
                                depositMenu:

                                system.clearScr();
                                    cout<<"Hi, ";Login.loginWelcome(Login.loginUsername); cout<<endl;
                                    
                                    try {

	                                    cout<<"============================================================="<<endl;
	                                    cout<<"||----------            Deposit Menu             ----------||"<<endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"||       Input amount of money: Rp. "; cin>>Login.balanceInput;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"||                     Check Captcha                       ||"<<endl;
	                                    cout<<"||                Captcha Value: "<< Login.processRandomNumber() <<"                    ||" << endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"=== >> Input Value : "; cin>>Login.userInput;  
	                                    cout<<"============================================================="<<endl;
	                                    
	                                    if(Login.checkIfNotRobot(Login.userInput)){
	                                    	if(Login.balanceInput < 999999999 and Login.balanceInput > 0){
	                                    		cout<<"=== >> "; Login.depositBalance(Login.loginUsername, Login.balanceInput); cout<<endl;  
		                                        logDatabase.historyDeposit(Login.loginUsername, Login.balanceInput);
		
		                                        cout<<endl;
		                                        system.pauseProgram(); goto loginChoice;
											}
										
											else{
		                                        throw(Login.balanceInput);
	                                		}
                                   		}
                                    
	                                    else{
	                                        cout<<"Captcha is not same! Input again..."<<endl;
	
	                                        system.pauseProgram();
	                                        goto loginChoice;
	                                    }
	                            	}
	                            	catch(unsigned int balanceInput){
	                            		cout<<"Can't deposit higher than Rp. 1.000.000.000 or Lower than Rp. 1"<<endl;
	                                    cout<<"Input again"<<endl;
	                                    
	                                    system.pauseProgram();
	                                    goto loginChoice;
									}
                            }
                            
                            else if(Login.Select == 2){
                                withdrawMenu:

                                system.clearScr();
                                    cout<<"Hi, "; Login.loginWelcome(Login.loginUsername); cout<<endl;
                                    
                                    try{

	                                    cout<<"============================================================="<<endl;
	                                    cout<<"||----------            Withdraw Menu            ----------||"<<endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"||       Input amount of money: Rp. "; cin>>Login.balanceInput;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"||                     Check Captcha                       ||"<<endl;
	                                    cout<<"||                Captcha Value: "<< Login.processRandomNumber() <<"                    ||" << endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"=== >> Input Value : "; cin>>Login.userInput;  
	                                    cout<<"============================================================="<<endl;
	                                    
	                                    if(Login.checkIfNotRobot(Login.userInput)){
	                                    	
	                                    	if(Login.balanceInput < 999999999 and Login.balanceInput > 0){
	                                    	
		                                        cout<<"==>> "; 
		        
		                                        if(logDatabase.balanceChecker(Login.loginUsername, Login.balanceInput)){
		                                            Login.withdrawBalance(Login.loginUsername, Login.balanceInput);
		
		                                            logDatabase.historyWithdraw(Login.loginUsername, Login.balanceInput);
		
		                                            system.pauseProgram();
		                                            goto loginChoice;
		                                        }
		                                        else{
		                                        	cout<<"You dont have enough Balance...."<<endl;
					                            	system.pauseProgram();
					
					                            	goto loginChoice;
												}
		                                	}
		                                	
		                                	else{
		                                		throw(Login.balanceInput);
		                                    }
	                                    }
	                                    else{
	                                        cout<<"Captcha is not same! Input again..."<<endl;
	
	                                        system.pauseProgram();
	                                        goto loginChoice;
	                                    }
	                            	}
	                            	catch(unsigned int balanceInput){
	                            		cout<<"Can't Withdraw higher than Rp. 1.000.000.000 or Lower than Rp. 1"<<endl;
	                                    cout<<"Input again"<<endl;
	                                    
	                                    system.pauseProgram();
	                                    goto loginChoice;
									}
                            }

                            else if(Login.Select == 3){
                                transferMenu:

                                system.clearScr();
                                    cout<<"Hi, "; Login.loginWelcome(Login.loginUsername); cout<<endl;
                                    
									try{
									
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"||----------           Transfer Menu             ----------||"<<endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"===>> Destination Username    : "; cin>>Login.destinationUser;
	                                    cout<<"===>> Amount to Transfer      : Rp. "; cin>>Login.transferBalance;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"||                     Check Captcha                       ||"<<endl;
	                                    cout<<"||                Captcha Value: "<< Login.processRandomNumber() <<"                    ||" << endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"============================================================="<<endl;
	                                    cout<<"=== >> Input Value : "; cin>>Login.userInput;  
	                                    cout<<"============================================================="<<endl;
	                                    
	                                    if(Login.checkIfNotRobot(Login.userInput)){
	
	                                        if(logDatabase.checkIfDestExist(Login.destinationUser)){
	                                        	
	                                        	if(Login.transferBalance < 999999999 and Login.transferBalance > 0){
	
		                                            if(logDatabase.balanceChecker(Login.destinationUser, Login.transferBalance)){
		                                                
		                                                cout<<"Do you really want to transfer Rp. "<<Login.transferBalance<<" to ";
		                                                Login.displayUserInfo(Login.destinationUser); cout<<endl;
		
		                                                char selectChoice;
		
		                                                cout<<"\nInput Y to proceed, or N if not ||  Choice >> : "; cin>>selectChoice;
		
		                                                if(selectChoice == 'y' or selectChoice == 'Y'){
		                                                    logDatabase.updateTransferBalance(Login.loginUsername, Login.destinationUser, Login.transferBalance);
		                                                    cout<<"\nTransfer Success...."<<endl;
		
		                                                    logDatabase.historyTransfer(Login.loginUsername, Login.destinationUser, Login.transferBalance);
		
		                                                    system.pauseProgram();
		                                                    goto loginChoice;
		                                                }
		
		                                                else if(selectChoice == 'n' or selectChoice == 'N'){
		                                                    cout<<"\nBack To Menu...."<<endl;
		                                                    system.pauseProgram();
		
		                                                    goto loginChoice;
		                                                }
		                                            }
		                                            else{
		                                                cout<<"\nYour Balance is not enough...."<<endl;
		
		                                                system.pauseProgram();
		                                                goto loginChoice;
		                                            }
		                                    	}
		                                    	
		                                    	else{
		                                    		throw(Login.transferBalance);
												}
	                                        }
	                                        else{
	                                            cout<<"\nUser not found, please check carefully"<<endl;
	
	                                            system.pauseProgram();
	                                            goto loginChoice;
	                                        }
	                                        
	                                    }
	
	                                    else{
	                                        cout<<"Captcha is not same! Input again..."<<endl;
	
	                                        system.pauseProgram();
	                                        goto loginChoice;
	                                    }
	                            	}
	                            	
	                            	catch(unsigned int transferBalance){
	                            		cout<<"Can't Transfer higher than Rp. 1.000.000.000 or Lower than Rp. 1"<<endl;
	                                    cout<<"Input again"<<endl;
	                                    
	                                    system.pauseProgram();
	                                    goto loginChoice;
									}
                            }

                            else if(Login.Select == 4){
                                system.clearScr();
                                captchaBalance: 
                                
                                    cout<<"============================================================="<<endl;
                                    cout<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
                                    cout<<"============================================================="<<endl;
                                    cout<<"||                     Check Captcha                       ||"<<endl;
                                    cout<<"||                Captcha Value: "<< Login.processRandomNumber() <<"                    ||" << endl;
                                    cout<<"============================================================="<<endl;
                                    cout<<"============================================================="<<endl;
                                    cout<<"=== >> Input Value : "; cin>>Login.userInput;  
                                    cout<<"============================================================="<<endl;
                                    
                                    if(Login.checkIfNotRobot(Login.userInput)){
                                        system.clearScr();

                                        cout<<"Hi, "; Login.loginWelcome(Login.loginUsername); cout<<endl;

                                        cout<<"============================================================="<<endl;
                                        cout<<"||----------            Balance Menu             ----------||"<<endl;
                                        cout<<"============================================================="<<endl;
                                        cout<<"============================================================="<<endl;
                                        cout<<"||                    Your Balance is :                    ||"<<endl;
                                        cout<<"|| ===>> "; Login.balanceInfo(Login.loginUsername); cout<<"                                        ||"<<endl; 
                                        cout<<"============================================================="<<endl;

                                        system.pauseProgram();
                                        goto loginChoice;
                                    }

                                    else{
                                        cout<<"Captcha is not same! Input again..."<<endl;

                                        system.pauseProgram();  
                                        goto captchaBalance;
                                    }
                            }

                            else if(Login.Select == 5){
                                passwordChange:

                                system.clearScr();
                                    cout<<"Hi, "; Login.loginWelcome(Login.loginUsername); cout<<endl;

                                    cout<<"============================================================="<<endl;
                                    cout<<"||----------           Change Password           ----------||"<<endl;
                                    cout<<"============================================================="<<endl;
                                    cout<<"============================================================="<<endl;
                                    cout<<"====>> Input old Password    : "; cin>>Login.loginPassword;
                                    cout<<endl;
                                    cout<<"====>> Input New Password    : "; cin>>Login.newPassword;
                                    cout<<"====>> Re-Type New Password  : "; cin>>Login.matchingPassword;
                                    cout<<"============================================================="<<endl;
                                    cout<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
                                    cout<<"============================================================="<<endl;
                                    cout<<"||                     Check Captcha                       ||"<<endl;
                                    cout<<"||                Captcha Value: "<< Login.processRandomNumber() <<"                    ||" << endl;
                                    cout<<"============================================================="<<endl;
                                    cout<<"============================================================="<<endl;
                                    cout<<"=== >> Input Value : "; cin>>Login.userInput;  
                                    cout<<"============================================================="<<endl;
                                    
                                    if(Login.checkIfNotRobot(Login.userInput)){

                                        if(Login.newPassword == Login.matchingPassword){

                                            if(logDatabase.updateUserPassword(Login.loginUsername, Login.loginPassword, Login.newPassword)){

                                                cout<<"\nPassword have been updated...."<<endl;
                                                cout<<"Please Login again."<<endl<<endl;

                                                system.pauseProgram();
                                                goto mainMenu;
                                            }
                                            else{
                                                cout<<"\nOld Password not match...."<<endl;
                                                cout<<"Imput Again!!"<<endl;

                                                system.pauseProgram();
                                                goto passwordChange;
                                            }
                                        }
                                        else{
                                            cout<<"\nPassword is not match"<<endl;
                                            cout<<"Input Again!!"<<endl;

                                            system.pauseProgram();
                                            goto passwordChange;
                                        }
                                        
                                    }
                                    else{
                                        cout<<"Captcha is not same! Input again..."<<endl;

                                        system.pauseProgram();
                                        goto passwordChange;
                                    }
                            }

                            else if(Login.Select == 6){
                                goto mainMenu;
                            }

                            else{
                                cout<<"Your input is not detected, Input again!!"<<endl;
                
                                system.pauseProgram();
                                goto loginChoice;
                            }
                    }

                    else {
                        cout<<"Username or Password did not record in database...."<<endl;

                        system.pauseProgram();
                        goto mainMenu;
                    }
                }
                
                else{
                    cout<<"Username or Password did not record in database...."<<endl;

                    system.pauseProgram();
                    goto mainMenu;
                }
            }

            else{
                cout<<"Captcha is not same! Input again..."<<endl;

                system.pauseProgram();
                goto loginMenu;
            }
        }

        else if(system.Select == 3){
            cout<<"Exit Success......"<<endl;
            //(2000);
            return EXIT_STATUS_SUCCESS;
        }

        else{
            cout<<"Your input is not detected, Input again!!"<<endl;
            
            system.pauseProgram();
            goto mainMenu;
        }
    
    return EXIT_STATUS_SUCCESS;
}   
