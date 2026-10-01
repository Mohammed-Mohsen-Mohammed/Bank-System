#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
{
private:

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";
		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		return AccountNumber;
	}

	static double _ReadAmount()
	{
		double Amount = 0;
		cout << "\nPlease enter deposit amount? ";
		Amount = clsInputValidate::ReadNumber<double>();
		while (Amount <= 0)
		{
			cout << "\nPlease enter Positive Number: ";
			Amount = clsInputValidate::ReadNumber<double>();
		}

		return Amount;
	}

	static void _Print(const clsBankClient& Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

public:

	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t    Withdraw Screen");

		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_Print(Client);

		double Amount = _ReadAmount();

		while (Amount > Client.AccountBalance)
		{
			cout << "\nAmount Exceeds the balance, you can withdraw upto : " << Client.AccountBalance << endl;
			do
			{
				cout << "Please enter another amount? ";
				cin >> Amount;
			} while (Amount <= 0);
		}

		cout << "\nAre you sure you want to perform this transaction? [Y/N]: ";

		char Answer = 'N';
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Client.Withdraw(Amount);
			cout << "\nAmount Withdraw Successfully.\n";
			cout << "\nNew Balance Is: " << Client.AccountBalance;
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}

};

