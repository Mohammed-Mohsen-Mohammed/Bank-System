#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
private:

	static string _ReadAccountNumber(const string& Message)
	{
		string AccountNumber = "";
		cout << Message;
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			cout << Message;
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

	static void _PrintClient(const clsBankClient& Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t    Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number To Transfer From: "));
		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number To Transfer To: "));
		_PrintClient(DestinationClient);

		if (!(SourceClient.AccountNumber() == DestinationClient.AccountNumber()))
		{
			cout << "\nEnter Transfer Amount? ";
			double Amount = clsInputValidate::ReadNumberBetween<double>(0, SourceClient.AccountBalance
				, "\nAmount Exceeds the available Balance, Enter another Amount: ");

			cout << "\nAre you sure you want to perform this transaction? [Y/N]: ";
			char Answer = 'N';
			cin >> Answer;

			if (toupper(Answer) == 'Y')
			{
				if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
				{
					cout << "\nTransfer Done Successfully :-)\n";
				}
				else
				{
					cout << "\nTransfer Faild :-(\n";
				}
			}
			else
			{
				cout << "\nOperation was cancelled.\n";
			}

			_PrintClient(SourceClient);
			_PrintClient(DestinationClient);
		}
		else
		{
			cout << "\nYou Can Not Transfer to Same Account!";
		}
	}

};

