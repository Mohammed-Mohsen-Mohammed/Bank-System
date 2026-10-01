#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;
const string FileName = "Clients.txt";

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

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

sClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> vClientData = SplitString(Line, Seperator);	

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	string ClientData = "";

	ClientData += Client.AccountNumber + Seperator;
	ClientData += Client.PinCode + Seperator;
	ClientData += Client.Name + Seperator;
	ClientData += Client.Phone + Seperator;
	ClientData += to_string(Client.AccountBalance);

	return ClientData;
}

vector<sClient> LoadClientsDataFromFile(string FileName)
{
	vector<sClient> vClients;
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

void SaveClientsDataToFile(string FileName, vector<sClient>& vclients)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		string DataLine;
		for (sClient& Client : vclients)
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

void PrintClientRecord(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData()
{
	vector <sClient> vClients = LoadClientsDataFromFile(FileName);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
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
		for (sClient& Client : vClients)
		{
			PrintClientRecord(Client);
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

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	fstream MyFile;

	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
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

sClient ReadNewClient()
{
	sClient Client;

	cout << "Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, FileName))
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

void AddNewClient()
{
	sClient Client = ReadNewClient();
	AddClientToFile(FileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
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

void ShowAddNewClientsScreen()
{
	cout << "\n------------------------------------\n\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "\n------------------------------------\n\n";
	AddNewClients();
}

void PrintClientCard(sClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccount Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient>& vClients,
	sClient& Client)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

void MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return;
		}
	}
}

void DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Sure = 'Y';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want to Delete this client? [Y/N] ";
		cin >> Sure;

		if (toupper(Sure) == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataToFile(FileName, vClients);
			cout << "\n\nClient Deleted Successfully.\n";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber <<
			") is Not Found!\n";
	}
}

void ShowDeleteClientScreen()
{
	cout << "\n------------------------------------\n\n";
	cout << "\tDelete Client Screen\n";
	cout << "\n------------------------------------\n\n";

	vector<sClient> vClients = LoadClientsDataFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();

	DeleteClientByAccountNumber(AccountNumber, vClients);
}

sClient UpdateClientData(string AccountNumber)
{
	sClient ClientData;

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

void UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Sure = 'Y';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want to update this client? [Y/N] ";
		cin >> Sure;

		if (toupper(Sure) == 'Y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = UpdateClientData(AccountNumber);
					break;
				}
			}
			SaveClientsDataToFile(FileName, vClients);
			cout << "\n\nClient Updated Successfully.\n";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber <<
			") is Not Found!\n";
	}
}

void ShowUpdateClientScreen()
{
	cout << "\n------------------------------------\n\n";
	cout << "\tUpdate Client Info Screen\n";
	cout << "\n------------------------------------\n\n";

	vector<sClient> vClients = LoadClientsDataFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();

	UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen()
{
	cout << "\n------------------------------------\n\n";
	cout << "\tFind Client Screen\n";
	cout << "\n------------------------------------\n\n";

	vector<sClient> vClients = LoadClientsDataFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();
	sClient Client;

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

void ShowEndScreen()
{
	cout << "\n-----------------------------------\n\n";
	cout << "\tProgram Ends :-)\n";
	cout << "\n-----------------------------------\n\n";
}

enum enMainMenueOptions
{
	ShowClients = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4
	, FindClient = 5, Transactions = 6, Exit = 7
};

enum enTransactionsMenueOptions
{
	Deposit = 1, Withdraw = 2,
	TotalBalances = 3, MainMenue = 4
};

void AddDepositToClient(string AccountNumber, double Amount, vector<sClient>& vClients)
{
	char Sure = 'n';

	cout << "\n\nAre you sure you want perfrom this transaction? [y / n] ";
	cin >> Sure;
	if (toupper(Sure) == 'Y')
	{
		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveClientsDataToFile(FileName, vClients);
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

	sClient Client;
	vector <sClient> vClients = LoadClientsDataFromFile(FileName);
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

	AddDepositToClient(AccountNumber, Amount,vClients);
}

void ShowWithdrawtScreen()
{
	cout << "\n------------------------------------\n\n";
	cout << "\tWithdraw Screen\n";
	cout << "\n------------------------------------\n\n";

	sClient Client;
	vector <sClient> vClients = LoadClientsDataFromFile(FileName);
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

void PrintClientRecordBalanceLine(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowTotalBalancesScreen()
{
	vector <sClient> vClients = LoadClientsDataFromFile(FileName);
	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
	cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	double TotalBalances = 0;

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (sClient Client : vClients)
		{
			PrintClientRecordBalanceLine(Client);
			TotalBalances += Client.AccountBalance;
			cout << endl;
		}

	cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t Total Balances = " << TotalBalances;
}

void ShowMainMenue();

void ShowTransactionsMenue();

void GoBackToTransactionsMenue()
{
	cout << "\n\nPress any key to go back to transactions menue... ";
	system("pause>0");
	ShowTransactionsMenue();
}

short ReadTransactionsMenueOption()
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

void PerfromTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenue)
{
	switch (TransactionsMenue)
	{
	case Deposit:
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenue();
		break;
	case Withdraw:
		system("cls");
		ShowWithdrawtScreen();
		GoBackToTransactionsMenue();
		break;
	case TotalBalances:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionsMenue();
		break;
	case MainMenue:
		system("cls");
		ShowMainMenue();
		break;
	}
}

void ShowTransactionsMenue()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "===========================================\n";

	PerfromTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to main menue... ";
	system("pause>0");
	ShowMainMenue();
}

short ReadMainMenueOption()
{
	short Choice = 0;
	do
	{
		cout << "Choose what do you want to do? [1 to 7]? ";
		cin >> Choice;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid choise, Enter a valid one:" << endl;
			cin >> Choice;
		}

	} while (Choice <= 0 || Choice > 7);

	return Choice;
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOptions::ShowClients:
		system("cls");
		PrintAllClientsData();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::AddClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::DeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::UpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::FindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::Transactions:
		system("cls");
		ShowTransactionsMenue();
		break;
	case enMainMenueOptions::Exit:
		system("cls");
		ShowEndScreen();
		break;
	}
}

void ShowMainMenue()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "===========================================\n";

	PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

int main()
{
	ShowMainMenue();

	return 0;
}
