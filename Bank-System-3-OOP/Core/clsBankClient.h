#pragma once
#include<iostream>
#include<string>
#include"clsPerson.h"
#include"clsString.h"
#include<vector>
#include<fstream>

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObject(const string& Line,
		const string& Seperator = "#//#")
	{
		vector<string>vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1],
			vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static string _ConvertClientObjectToLine(const clsBankClient& Client,
		const string& Seperator = "#//#")
	{
		string ClientData = "";

		ClientData += Client.FirstName + Seperator;
		ClientData += Client.LastName + Seperator;
		ClientData += Client.Email + Seperator;
		ClientData += Client.Phone + Seperator;
		ClientData += Client.AccountNumber() + Seperator;
		ClientData += Client.PinCode + Seperator;
		ClientData += to_string(Client.AccountBalance);

		return ClientData;
	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				vClients.push_back(_ConvertLineToClientObject(Line));
			}

			MyFile.close();
		}

		return vClients;
	}

	static void _SaveClientsDataToFile(const vector<clsBankClient>& vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open())
		{
			string DataLine;
			for (const clsBankClient& C : vClients)
			{
				if (C.MarkedForDelete() == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	void _AddDataLineToFile(const string& DataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsBankClient> vClinets = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClinets)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(vClinets);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	string _PrepareTransferLogRecord(double Amount, const clsBankClient& DestinationClient,
		const string& UserName, const string& Seperator = "#//#")
	{
		string TransferLogRecord = "";

		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord += AccountNumber() + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLogRecord += UserName;

		return TransferLogRecord;
	}

	struct stTransferLogRecord;

	static stTransferLogRecord _ConvertTransferLogLineToRecord(const string& Line,
		const string& Seperator = "#//#")
	{
		vector <string> vTransferLogRecord = clsString::Split(Line, Seperator);

		return stTransferLogRecord{ vTransferLogRecord[0], vTransferLogRecord[1],
			vTransferLogRecord[2], stod(vTransferLogRecord[3]),stod(vTransferLogRecord[4]),
			stod(vTransferLogRecord[5]), vTransferLogRecord[6] };
	}

	void _TransferLog(double Amount, const clsBankClient& DestinationClient,
		const string& UserName)
	{
		string DataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

public:

	struct stTransferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		double Amount = 0;
		double srcBalanceAfter = 0;
		double destBalanceAfter = 0;
		string UserName;
	};

	clsBankClient(enMode Mode, const string& FirstName, const string& LastName
		, const string& Email, const string& Phone, const string& AccountNumber,
		const string& PinCode, double AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	string AccountNumber() const
	{
		return _AccountNumber;
	}

	void SetPinCode(const string& PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode() const
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	double GetAccountBalance() const
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	bool MarkedForDelete() const
	{
		return _MarkedForDelete;
	}

	bool IsEmpty() const
	{
		return (_Mode == enMode::EmptyMode);
	}

	static clsBankClient Find(const string& AccountNumber)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{

				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}

			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(const string& AccountNumber, const string& PinCode)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{

				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}

			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	enum enSaveResults
	{
		svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2
	};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:

			return enSaveResults::svFaildEmptyObject;

		case enMode::UpdateMode:

			_Update();
			return enSaveResults::svSucceeded;

		case enMode::AddNewMode:

			if (IsClientExist(AccountNumber()))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}

			_AddNew();
			_Mode = enMode::UpdateMode;
			return enSaveResults::svSucceeded;
		}

		return svFaildEmptyObject;
	}

	static bool IsClientExist(const string& AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(const string& AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		if (IsEmpty())
		{
			return false;
		}

		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C._MarkedForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		double TotalBalances = 0;

		for (const clsBankClient& Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposit(double Amount)
	{
		if (Amount <= 0)
		{
			return;
		}

		_AccountBalance += Amount;
		Save();
	}

	void Withdraw(double Amount)
	{
		if (Amount <= 0 || Amount > AccountBalance)
		{
			return;
		}

		_AccountBalance -= Amount;
		Save();
	}

	bool Transfer(double Amount, clsBankClient& DestinationClient,
		const string& UserName)
	{
		if (Amount <= 0)
		{
			return false;
		}

		if (AccountNumber() == DestinationClient.AccountNumber() || Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_TransferLog(Amount, DestinationClient, UserName);

		return true;
	}

	static vector <stTransferLogRecord> GetTransfersLogList()
	{
		vector <stTransferLogRecord> vTransferLogRecord;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			stTransferLogRecord TransferRecord;

			while (getline(MyFile, Line))
			{
				TransferRecord = _ConvertTransferLogLineToRecord(Line);
				vTransferLogRecord.push_back(TransferRecord);
			}

			MyFile.close();
		}

		return vTransferLogRecord;
	}

};

