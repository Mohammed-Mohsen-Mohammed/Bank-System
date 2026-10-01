#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

struct stUser
{
	string Username;
	string Password;
	int Permissions;
	bool MarkForDelete = false;
};

enum enMainMenuOptions
{
	ShowClients = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4
	, FindClient = 5, Transactions = 6, ManageUsers = 7, Logout = 8
};

enum enTransactionsMenuOptions
{
	Deposit = 1, Withdraw = 2, TotalBalances = 3, ShowMainMenue = 4
};

enum enManageUsersMenuOptions
{
	ListUsers = 1, AddUser = 2, DeleteUser = 3,
	UpdateUser = 4, FindUser = 5, MainMenue = 6
};

enum enMainMenuPermissions
{
	pAll = -1, pShowClients = 1, pAddClient = 2, pDeleteClient = 4, pUpdateClient = 8
	, pFindClient = 16, pTransactions = 32, pManageUsers = 64
};

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
stUser CurrentUser;

void ShowMainMenu();
void ShowTransactionsMenu();
void ShowManageUsersMenu();
void Login();

vector<string> SplitString(string S, string Delim)
{
	vector<string> vString;
	short Pos = 0;
	string Word = "";

	while ((Pos = S.find(Delim)) != std::string::npos)
	{
		Word = S.substr(0, Pos);
		if (Word != "")
		{
			vString.push_back(Word);
		}
		S.erase(0, Pos + Delim.length());
	}
	if (S != "")
	{
		vString.push_back(S);
	}

	return vString;
}

stClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
	stClient Client;
	vector<string> vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

stUser ConvertUserLineToRecord(string Line, string Seperator = "#//#")
{
	stUser User;
	vector<string> vUserData = SplitString(Line, Seperator);

	User.Username = vUserData[0];
	User.Password = vUserData[1];
	User.Permissions = stoi(vUserData[2]);

	return User;
}

string ConvertRecordToLine(const stClient& Client, string Seperator = "#//#")
{
	string ClientData = "";

	ClientData += Client.AccountNumber + Seperator;
	ClientData += Client.PinCode + Seperator;
	ClientData += Client.Name + Seperator;
	ClientData += Client.Phone + Seperator;
	ClientData += to_string(Client.AccountBalance);

	return ClientData;
}

string ConvertUserRecordToLine(const stUser& User, string Seperator = "#//#")
{
	string UserData = "";

	UserData += User.Username + Seperator;
	UserData += User.Password + Seperator;
	UserData += to_string(User.Permissions);

	return UserData;
}

vector<stClient> LoadClientsDataFromFile(string FileName)
{
	vector<stClient> vClients;
	fstream MyFile;

	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		while (getline(MyFile, Line))
		{
			vClients.push_back(ConvertLineToRecord(Line));
		}
		MyFile.close();
	}

	return vClients;
}

vector<stUser> LoadUsersDataFromFile(string FileName)
{
	vector<stUser> vUsers;
	fstream MyFile;

	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		while (getline(MyFile, Line))
		{
			vUsers.push_back(ConvertUserLineToRecord(Line));
		}
		MyFile.close();
	}

	return vUsers;
}

void SaveClientsDataToFile(string FileName, vector<stClient>& vclients)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		string DataLine;
		for (stClient& Client : vclients)
		{
			if (Client.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(Client);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
}

void SaveUsersDataToFile(string FileName, vector<stUser>& vUsers)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		string DataLine;
		for (stUser& User : vUsers)
		{
			if (User.MarkForDelete == false)
			{
				DataLine = ConvertUserRecordToLine(User);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
}

void ShowAccessDeniedMessage()
{
	cout << "\n------------------------------------\n";
	cout << "Access Denied, \nYou dont Have Permission To Dothis, \nPlease Conact Your Admin.";
	cout << "\n------------------------------------\n";
}

int ReadPermissionsToSet()
{
	char Answer = 'N';

	cout << "\nDo you want to give full access? [Y/N] ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		return -1;
	}

	int Permissions = 0;
	cout << "\nDo you want to give access to : \n ";

	cout << "\nShow Client List? [Y/N] ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permissions += enMainMenuPermissions::pShowClients;
	}

	cout << "\nAdd New Client? [Y/N] ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permissions += enMainMenuPermissions::pAddClient;
	}

	cout << "\nDelete Client? [Y/N] ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permissions += enMainMenuPermissions::pDeleteClient;
	}

	cout << "\nUpdate Client? [Y/N] ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permissions += enMainMenuPermissions::pUpdateClient;
	}

	cout << "\nfind Client? [Y/N] ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permissions += enMainMenuPermissions::pFindClient;
	}

	cout << "\nTransactions? [Y/N] ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permissions += enMainMenuPermissions::pTransactions;
	}

	cout << "\nManage Users? [Y/N] ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permissions += enMainMenuPermissions::pManageUsers;
	}

	return Permissions;
}

bool CheckAccessPermission(enMainMenuPermissions Permission)
{
	if (CurrentUser.Permissions == enMainMenuPermissions::pAll)
		return true;

	if ((Permission & CurrentUser.Permissions) == Permission)
		return true;
	else
		return false;
}

void PrintClientRecord(const stClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintUserRecord(const stUser& User)
{
	cout << "| " << setw(15) << left << User.Username;
	cout << "| " << setw(10) << left << User.Password;
	cout << "| " << setw(40) << left << User.Permissions;
}

void PrintAllClientsData()
{
	if (!CheckAccessPermission(enMainMenuPermissions::pShowClients))
	{
		ShowAccessDeniedMessage();
		return;
	}

	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tClients List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (stClient& Client : vClients)
		{
			PrintClientRecord(Client);
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void PrintAllUsersData()
{
	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permissions";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vUsers.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (stUser& User : vUsers)
		{
			PrintUserRecord(User);
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;

	return AccountNumber;
}

string ReadUsername()
{
	string Username = "";
	cout << "\nPlease enter Username? ";
	cin >> Username;

	return Username;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	fstream MyFile;

	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		stClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
		}
		MyFile.close();
	}
	return false;
}

bool UserExistsByUserName(string Username, string FileName)
{
	fstream MyFile;

	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		stUser User;
		while (getline(MyFile, Line))
		{
			User = ConvertUserLineToRecord(Line);
			if (User.Username == Username)
			{
				MyFile.close();
				return true;
			}
		}
		MyFile.close();
	}
	return false;
}

stClient ReadNewClient()
{
	stClient Client;

	cout << "Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with [" << Client.AccountNumber <<
			"] already exists, Enter another Account Number ? ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "\nEnter PinCode? ";
	getline(cin, Client.PinCode);
	cout << "\nEnter Name? ";
	getline(cin, Client.Name);
	cout << "\nEnter Phone? ";
	getline(cin, Client.Phone);
	cout << "\nEnter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

stUser ReadNewUser()
{
	stUser User;

	cout << "Enter Username? ";
	getline(cin >> ws, User.Username);

	while (UserExistsByUserName(User.Username, UsersFileName))
	{
		cout << "\nUser with [" << User.Username <<
			"] already exists, Enter another Username ? ";
		getline(cin >> ws, User.Username);
	}

	cout << "\nEnter Password? ";
	getline(cin, User.Password);
	User.Permissions = ReadPermissionsToSet();

	return User;
}

void AddClientToFile(string FileName, string DataLine)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << DataLine << endl;
		MyFile.close();
	}
}

void AddUserToFile(string FileName, string DataLine)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << DataLine << endl;
		MyFile.close();
	}
}

void AddNewClient()
{
	stClient Client = ReadNewClient();
	AddClientToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewUser()
{
	stUser User = ReadNewUser();
	AddUserToFile(UsersFileName, ConvertUserRecordToLine(User));
}

void AddNewClients()
{
	if (!CheckAccessPermission(enMainMenuPermissions::pAddClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	char AddMore = 'Y';
	while (toupper(AddMore) == 'Y')
	{
		/*system("cls");*/
		cout << "Adding New Client:\n\n";
		AddNewClient();
		cout << "\n\nClient Added Successfully, do you want to add more clients ? [Y / N] ";
		cin >> AddMore;
	}
}

void AddNewUsers()
{
	char AddMore = 'Y';
	while (toupper(AddMore) == 'Y')
	{
		/*system("cls");*/
		cout << "Adding New User:\n\n";
		AddNewUser();
		cout << "\n\nUser Added Successfully, do you want to add more Users ? [Y / N] ";
		cin >> AddMore;
	}
}

void ShowAddNewClientsScreen()
{
	if (!CheckAccessPermission(enMainMenuPermissions::pAddClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n------------------------------------\n\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "\n------------------------------------\n\n";
	AddNewClients();
}

void ShowAddNewUsersScreen()
{
	cout << "\n------------------------------------\n\n";
	cout << "\tAdd New Users Screen\n";
	cout << "\n------------------------------------\n\n";
	AddNewUsers();
}

void PrintClientCard(const stClient& Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "-----------------------------------";
	cout << "\nAccount Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n-----------------------------------\n";
}

void PrintUserCard(const stUser& User)
{
	cout << "\nThe following are the User details:\n";
	cout << "-----------------------------------";
	cout << "\nUsername    : " << User.Username;
	cout << "\nPassword    : " << User.Password;
	cout << "\nPermissions : " << User.Permissions;
	cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<stClient>& vClients,
	stClient& Client)
{
	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool FindUserByUsername(string Username, vector<stUser>& vUsers, stUser& User)
{
	for (stUser& U : vUsers)
	{
		if (U.Username == Username)
		{
			User = U;
			return true;
		}
	}
	return false;
}

void MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{
	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return;
		}
	}
}

void MarkUserForDeleteByUsername(string Username, vector<stUser>& vUsers)
{
	for (stUser& U : vUsers)
	{
		if (U.Username == Username)
		{
			U.MarkForDelete = true;
			return;
		}
	}
}

void DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{
	stClient Client;
	char Sure = 'N';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want to Delete this client? [Y/N] ";
		cin >> Sure;

		if (toupper(Sure) == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Deleted Successfully.\n";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber <<
			") is Not Found!\n";
	}
}

void DeleteUserByUsername(string Username, vector<stUser>& vUsers)
{
	stUser User;
	char Sure = 'N';

	if (FindUserByUsername(Username, vUsers, User))
	{
		PrintUserCard(User);
		cout << "\n\nAre you sure you want to Delete this User? [Y/N] ";
		cin >> Sure;

		if (toupper(Sure) == 'Y')
		{
			MarkUserForDeleteByUsername(Username, vUsers);
			SaveUsersDataToFile(UsersFileName, vUsers);
			cout << "\n\nUser Deleted Successfully.\n";
		}
	}
	else
	{
		cout << "\nUser with Username (" << Username << ") is Not Found!\n";
	}
}

void ShowDeleteClientScreen()
{
	if (!CheckAccessPermission(enMainMenuPermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n------------------------------------\n\n";
	cout << "\tDelete Client Screen\n";
	cout << "\n------------------------------------\n\n";

	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowDeleteUserScreen()
{
	cout << "\n------------------------------------\n\n";
	cout << "\tDelete User Screen\n";
	cout << "\n------------------------------------\n\n";

	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string Username = ReadUsername();

	if (Username == "Admin")
	{
		cout << "\n\nYou cannot delete this user.";
		return;
	}
	DeleteUserByUsername(Username, vUsers);
}

stClient UpdateClientData(string AccountNumber)
{
	stClient ClientData;

	ClientData.AccountNumber = AccountNumber;
	cout << "\nEnter PinCode? ";
	getline(cin >> ws, ClientData.PinCode);
	cout << "\nEnter Name? ";
	getline(cin, ClientData.Name);
	cout << "\nEnter Phone? ";
	getline(cin, ClientData.Phone);
	cout << "\nEnter AccountBalance? ";
	cin >> ClientData.AccountBalance;

	return ClientData;
}

stUser UpdateUserData(string Username)
{
	stUser UserData;

	UserData.Username = Username;
	cout << "\nEnter Password? ";
	getline(cin >> ws, UserData.Password);
	UserData.Permissions = ReadPermissionsToSet();

	return UserData;
}

void UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{
	stClient Client;
	char Sure = 'Y';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want to update this client? [Y/N] ";
		cin >> Sure;

		if (toupper(Sure) == 'Y')
		{
			for (stClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = UpdateClientData(AccountNumber);
					break;
				}
			}
			SaveClientsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Updated Successfully.\n";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber <<
			") is Not Found!\n";
	}
}

void UpdateUserByUsername(string Username, vector<stUser>& vUsers)
{
	stUser User;
	char Sure = 'Y';

	if (FindUserByUsername(Username, vUsers, User))
	{
		PrintUserCard(User);
		cout << "\n\nAre you sure you want to update this User? [Y/N] ";
		cin >> Sure;

		if (toupper(Sure) == 'Y')
		{
			for (stUser& U : vUsers)
			{
				if (U.Username == Username)
				{
					U = UpdateUserData(Username);
					break;
				}
			}
			SaveUsersDataToFile(UsersFileName, vUsers);
			cout << "\n\nUser Updated Successfully.\n";
		}
	}
	else
	{
		cout << "\nUser with Username (" << Username << ") is Not Found!\n";
	}
}

void ShowUpdateClientScreen()
{
	if (!CheckAccessPermission(enMainMenuPermissions::pUpdateClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n------------------------------------\n\n";
	cout << "\tUpdate Client Info Screen\n";
	cout << "\n------------------------------------\n\n";

	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateUserScreen()
{
	cout << "\n------------------------------------\n\n";
	cout << "\tUpdate User Info Screen\n";
	cout << "\n------------------------------------\n\n";

	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string Username = ReadUsername();

	UpdateUserByUsername(Username, vUsers);
}

void ShowFindClientScreen()
{
	if (!CheckAccessPermission(enMainMenuPermissions::pFindClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n------------------------------------\n\n";
	cout << "\tFind Client Screen\n";
	cout << "\n------------------------------------\n\n";

	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	stClient Client;

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber <<
			") is Not Found!\n";
	}
}

void ShowFindUserScreen()
{
	cout << "\n------------------------------------\n\n";
	cout << "\tFind User Screen\n";
	cout << "\n------------------------------------\n\n";

	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string Username = ReadUsername();
	stUser User;

	if (FindUserByUsername(Username, vUsers, User))
	{
		PrintUserCard(User);
	}
	else
	{
		cout << "\nUser with Username (" << Username <<
			") is Not Found!\n";
	}
}

void AddDepositToClient(string AccountNumber, double Amount, vector<stClient>& vClients)
{
	char Sure = 'n';

	cout << "\n\nAre you sure you want perfrom this transaction? [y / n] ";
	cin >> Sure;
	if (toupper(Sure) == 'Y')
	{
		for (stClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveClientsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New balance is: "
					<< C.AccountBalance;
				break;
			}
		}
	}
}

void ShowDepositScreen()
{
	cout << "\n------------------------------------\n\n";
	cout << "\tDeposit Screen\n";
	cout << "\n------------------------------------\n\n";

	stClient Client;
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);
	double Amount = 0;
	while (Amount <= 0)
	{
		cout << "\n\nPlease enter deposit amount? ";
		cin >> Amount;
	}

	AddDepositToClient(AccountNumber, Amount, vClients);
}

void ShowWithdrawtScreen()
{
	cout << "\n------------------------------------\n\n";
	cout << "\tWithdraw Screen\n";
	cout << "\n------------------------------------\n\n";

	stClient Client;
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);
	double Amount = 0;

	while (Amount <= 0)
	{
		cout << "\n\nPlease enter withdraw amount? ";
		cin >> Amount;
	}

	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw upto : " << Client.AccountBalance << endl;
		do
		{
			cout << "Please enter another amount? ";
			cin >> Amount;
		} while (Amount <= 0);
	}

	AddDepositToClient(AccountNumber, -1 * Amount, vClients);
}

void PrintClientRecordBalanceLine(const stClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowTotalBalancesScreen()
{
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	double TotalBalances = 0;

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (stClient& Client : vClients)
		{
			PrintClientRecordBalanceLine(Client);
			TotalBalances += Client.AccountBalance;
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t Total Balances = " << TotalBalances;
}

void GoBackToMainMenu()
{
	cout << "\n\nPress any key to go back to Main Menue... ";
	system("pause>0");
	ShowMainMenu();
}

void GoBackToTransactionsMenu()
{
	cout << "\n\nPress any key to go back to Transactions Menue... ";
	system("pause>0");
	ShowTransactionsMenu();
}

void GoBackToManageUsersMenu()
{
	cout << "\n\nPress any key to go back to Manage Users Menue... ";
	system("pause>0");
	ShowManageUsersMenu();
}

short ReadTransactionsMenuOption()
{
	short Choice = 0;
	do
	{
		cout << "Choose what do you want to do? [1 to 4]? ";
		cin >> Choice;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid choise, Enter a valid one:" << endl;
			cin >> Choice;
		}

	} while (Choice <= 0 || Choice > 4);

	return Choice;
}

void PerfromTransactionsMenuOption(enTransactionsMenuOptions TransactionsMenue)
{
	switch (TransactionsMenue)
	{
	case enTransactionsMenuOptions::Deposit:
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenu();
		break;
	case enTransactionsMenuOptions::Withdraw:
		system("cls");
		ShowWithdrawtScreen();
		GoBackToTransactionsMenu();
		break;
	case enTransactionsMenuOptions::TotalBalances:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionsMenu();
		break;
	case enTransactionsMenuOptions::ShowMainMenue:
		ShowMainMenu();
	}
}

void ShowTransactionsMenu()
{
	if (!CheckAccessPermission(enMainMenuPermissions::pTransactions))
	{
		ShowAccessDeniedMessage();
		return;
	}

	system("cls");
	cout << "===========================================\n";
	cout << "\t\tTransactions Menu Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "===========================================\n";

	PerfromTransactionsMenuOption((enTransactionsMenuOptions)ReadTransactionsMenuOption());
}

short ReadManageUsersMenuOption()
{
	short Choice = 0;
	do
	{
		cout << "Choose what do you want to do? [1 to 6]? ";
		cin >> Choice;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid choise, Enter a valid one:" << endl;
			cin >> Choice;
		}

	} while (Choice <= 0 || Choice > 6);

	return Choice;
}

void PerfromManageUsersMenuOption(enManageUsersMenuOptions ManageUsersMenueOptoins)
{
	switch (ManageUsersMenueOptoins)
	{
	case enManageUsersMenuOptions::ListUsers:
		system("cls");
		PrintAllUsersData();
		GoBackToManageUsersMenu();
		break;
	case enManageUsersMenuOptions::AddUser:
		system("cls");
		ShowAddNewUsersScreen();
		GoBackToManageUsersMenu();
		break;
	case enManageUsersMenuOptions::DeleteUser:
		system("cls");
		ShowDeleteUserScreen();
		GoBackToManageUsersMenu();
		break;
	case enManageUsersMenuOptions::UpdateUser:
		system("cls");
		ShowUpdateUserScreen();
		GoBackToManageUsersMenu();
		break;
	case enManageUsersMenuOptions::FindUser:
		system("cls");
		ShowFindUserScreen();
		GoBackToManageUsersMenu();
		break;
	case enManageUsersMenuOptions::MainMenue:
		ShowMainMenu();
	}
}

void ShowManageUsersMenu()
{
	if (!CheckAccessPermission(enMainMenuPermissions::pManageUsers))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}

	system("cls");
	cout << "===========================================\n";
	cout << "\tManage Users Menu Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "===========================================\n";

	PerfromManageUsersMenuOption((enManageUsersMenuOptions)
		ReadManageUsersMenuOption());
}

short ReadMainMenuOption()
{
	short Choice = 0;
	do
	{
		cout << "Choose what do you want to do? [1 to 8]? ";
		cin >> Choice;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid choise, Enter a valid one:" << endl;
			cin >> Choice;
		}

	} while (Choice <= 0 || Choice > 8);

	return Choice;
}

void PerfromMainMenuOption(enMainMenuOptions MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenuOptions::ShowClients:
		system("cls");
		PrintAllClientsData();
		GoBackToMainMenu();
		break;
	case enMainMenuOptions::AddClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOptions::DeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOptions::UpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOptions::FindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOptions::Transactions:
		system("cls");
		ShowTransactionsMenu();
		break;
	case enMainMenuOptions::ManageUsers:
		system("cls");
		ShowManageUsersMenu();
		break;
	case enMainMenuOptions::Logout:
		system("cls");
		Login();
	}
}

void ShowMainMenu()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "===========================================\n";

	PerfromMainMenuOption((enMainMenuOptions)ReadMainMenuOption());
}

bool FindUserByUsernameAndPassword(string Username, string Password, stUser& User)
{
	vector<stUser>vUsers = LoadUsersDataFromFile(UsersFileName);

	for (stUser& U : vUsers)
	{
		if (U.Username == Username && U.Password == Password)
		{
			User = U;
			return true;
		}
	}

	return false;
}

bool LoadUserInfo(string Username, string Password)
{
	if (FindUserByUsernameAndPassword(Username, Password, CurrentUser))
		return true;
	else
		return false;
}

void Login()
{
	bool LoginFailed = false;
	string Username, Password;

	do
	{
		system("cls");

		cout << "===========================================\n";
		cout << "\t\tLogin Screen\n";
		cout << "===========================================\n";

		if (LoginFailed)
		{
			cout << "Invalid Username/Password!\n";
		}

		cout << "Enter Username? ";
		cin >> Username;
		cout << "Enter Password? ";
		cin >> Password;

		LoginFailed = !LoadUserInfo(Username, Password);

	} while (LoginFailed);

	ShowMainMenu();
}

int main()
{
	Login();

	return 0;
}