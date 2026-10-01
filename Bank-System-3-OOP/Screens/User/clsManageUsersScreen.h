#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen
{
private:

	enum enManageUsersMenuOptions {
		ListUsers = 1, AddNewUser = 2, DeleteUser = 3,
		UpdateUser = 4, FindUser = 5, MainMenu = 6
	};

	static short _ReadManageUsersMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 6, "Enter Number between 1 to 6? ");
		return Choice;
	}

	static void _GoBackToManageUsersMenu()
	{
		cout << "\n\nPress any key to go back to Manage Users Menu...";
		system("pause>0");
		ShowManageUsersMenue();
	}

	static void _ShowListUsersScreen()
	{
		clsUsersListScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUsersMenueOption(const enManageUsersMenuOptions& ManageUsersMenuOption)
	{
		switch (ManageUsersMenuOption)
		{
		case enManageUsersMenuOptions::ListUsers:
		{
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUsersMenu();
			break;
		}

		case enManageUsersMenuOptions::AddNewUser:
		{
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}

		case enManageUsersMenuOptions::DeleteUser:
		{
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}

		case enManageUsersMenuOptions::UpdateUser:
		{
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}

		case enManageUsersMenuOptions::FindUser:
		{
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}

		case enManageUsersMenuOptions::MainMenu:
		{
			//do nothing here the main screen will handle it :-) ;
		}
		}
	}

public:

	static void ShowManageUsersMenue()
	{
		if (!CheckAccessRights(clsUser::enPermissions::ManageUsers))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\t Manage Users Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Manage Users Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[01] List Users.\n";
		cout << setw(37) << left << "" << "\t[02] Add New User.\n";
		cout << setw(37) << left << "" << "\t[03] Delete User.\n";
		cout << setw(37) << left << "" << "\t[04] Update User.\n";
		cout << setw(37) << left << "" << "\t[05] Find User.\n";
		cout << setw(37) << left << "" << "\t[06] Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformManageUsersMenueOption((enManageUsersMenuOptions)_ReadManageUsersMenuOption());
	}

};