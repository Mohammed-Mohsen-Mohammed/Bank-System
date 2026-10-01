#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen
{
private:
	
	static string _ReadUserName()
	{
		string UserName = "";
		cout << "\nPlease Enter UserName: ";
		UserName = clsInputValidate::ReadString();

		return UserName;
	}

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permission: ";
		User.Permissions = _ReadPermissionsToSet();
	}

	static void _PrintUser(const clsUser& User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";
	}

	static int _ReadPermissionsToSet()
	{
		int Permissions = 0;
		char Answer = 'N';

		cout << "\nDo you want to give full access? [Y/N]: ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to : \n ";

		cout << "\nShow Client List? [Y/N]: ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::ListClients;
		}

		cout << "\nAdd New Client? [Y/N]: ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::AddNewClient;
		}

		cout << "\nDelete Client? [Y/N]: ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::DeleteClient;
		}

		cout << "\nUpdate Client? [Y/N]: ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::UpdateClients;
		}

		cout << "\nFind Client? [Y/N]: ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::FindClient;
		}

		cout << "\nTransactions? [Y/N]: ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::Tranactions;
		}

		cout << "\nManage Users? [Y/N]: ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::ManageUsers;
		}
		
		cout << "\nShow Login Register Screen? [Y/N]: ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::LoginRegister;
		}
		
		cout << "\nShow Currency Exchange Screen? [Y/N]: ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::CurrencyExchange;
		}

		return Permissions;
	}

public:

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\t  Add New User Screen");

		string UserName = _ReadUserName();

		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUser with [" << UserName << "] does not exist.\n";
			UserName = _ReadUserName();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResult;

		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case  clsUser::enSaveResults::svSucceeded:
		{
			cout << "\nUser Addeded Successfully :-)\n";
			_PrintUser(NewUser);
			break;
		}
		case clsUser::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError User was not saved because it's Empty";
			break;
		}
		case clsUser::enSaveResults::svFaildUserExists:
		{
			cout << "\nError User was not saved because UserName is used!\n";
		}
		}
	}

};

