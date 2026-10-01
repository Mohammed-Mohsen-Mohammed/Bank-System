#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionsScreen : protected clsScreen
{
private:

	enum enTransactionsMenuOptions {
		Deposit = 1, Withdraw = 2,
		TotalBalance = 3, Transfer = 4, TransferLog = 5, ShowMainMenu = 6
	};

	static short ReadTransactionsMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 6, "Enter Number between 1 to 6? ");
		return Choice;
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}
	
	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _GoBackToTransactionsMenu()
	{
		cout << "\n\nPress any key to go back to Transactions Menu...";
		system("pause>0");
		ShowTransactionsMenu();
	}

	static void _PerformTransactionsMenuOption(const enTransactionsMenuOptions& TransactionsMenuOption)
	{
		switch (TransactionsMenuOption)
		{
		case enTransactionsMenuOptions::Deposit:

			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsMenuOptions::Withdraw:

			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsMenuOptions::TotalBalance:

			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsMenuOptions::Transfer:

			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenu();
			break;
		
		case enTransactionsMenuOptions::TransferLog:

			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsMenuOptions::ShowMainMenu:
		{
			//do nothing here the main screen will handle it :-) ;
		}

		}
	}

public:

	static void ShowTransactionsMenu()
	{
		if (!CheckAccessRights(clsUser::enPermissions::Tranactions))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Transactions Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[01] Deposit.\n";
		cout << setw(37) << left << "" << "\t[02] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[03] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[04] Transfer.\n";
		cout << setw(37) << left << "" << "\t[05] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[06] Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformTransactionsMenuOption((enTransactionsMenuOptions)ReadTransactionsMenuOption());
	}

};