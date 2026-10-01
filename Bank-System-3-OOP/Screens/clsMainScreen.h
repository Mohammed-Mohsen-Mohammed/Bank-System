#pragma once
#include <iostream>
#include <iomanip>
#include "Global.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"

class clsMainScreen : protected clsScreen
{
private:

	enum enMainMenuOptions {
		ListClients = 1, AddNewClient = 2, DeleteClient = 3,
		UpdateClient = 4, FindClient = 5, Transactions = 6,
		ManageUsers = 7, LoginRegister = 8, CurrencyExchange = 9, Exit = 10
	};

	static short _ReadMainMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 10, "Enter Number between 1 to 10? ");
		return Choice;
	}

	static  void _GoBackToMainMenu()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menu...\n";

		system("pause>0");
		ShowMainMenu();
	}

	static void _ShowAllClientsScreen()
	{
		clsClientsListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientsScreen()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenu()
	{
		clsTransactionsScreen::ShowTransactionsMenu();
	}

	static void _ShowManageUsersMenu()
	{
		clsManageUsersScreen::ShowManageUsersMenue();
	}

	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}
	
	static void _ShowCurrencyExchangeMainScreen()
	{
		clsCurrencyExchangeMainScreen::ShowCurrenciesMenu();
	}

	static void _ShowLogout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static void _PerfromMainMenuOption(const enMainMenuOptions& MainMenuOption)
	{
		switch (MainMenuOption)
		{
		case enMainMenuOptions::ListClients:
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::AddNewClient:
			system("cls");
			_ShowAddNewClientsScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::DeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::UpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::FindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::Transactions:
			system("cls");
			_ShowTransactionsMenu();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::ManageUsers:
			system("cls");
			_ShowManageUsersMenu();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::LoginRegister:
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenu();
			break;
		
		case enMainMenuOptions::CurrencyExchange:
			system("cls");
			_ShowCurrencyExchangeMainScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::Exit:
			system("cls");
			_ShowLogout();
			//Login();
		}
	}

public:

	static void ShowMainMenu()
	{
		system("cls");
		_DrawScreenHeader("\t     Main Screen");

		cout << setw(37) << left << "" << "==========================================\n";
		cout << setw(37) << left << "" << "\t\t     Main Menu\n";
		cout << setw(37) << left << "" << "==========================================\n";
		cout << setw(37) << left << "" << "\t[01] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[02] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[03] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[04] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[05] Find Client.\n";
		cout << setw(37) << left << "" << "\t[06] Transactions.\n";
		cout << setw(37) << left << "" << "\t[07] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[08] Login Register.\n";
		cout << setw(37) << left << "" << "\t[09] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "==========================================\n";

		_PerfromMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
	}

};

