#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{
private:

	static string _ReadUserName()
	{
		string UserName = "";
		cout << "\nPlease Enter UserName: ";
		UserName = clsInputValidate::ReadString();

		return UserName;
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

public:

	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\tDelete User Screen");

		string UserName = _ReadUserName();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser with [" << UserName << "] does not exist.\n";
			UserName = _ReadUserName();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		cout << "\nAre you sure you want to delete this User? [Y/N]: ";

		char Answer = 'N';
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (User.Delete())
			{
				cout << "\nUser Deleted Successfully :-)\n";

				_PrintUser(User);
			}
			else
			{
				cout << "\nError User Was not Deleted\n";
			}
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}

};

