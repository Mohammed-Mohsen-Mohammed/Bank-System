#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
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

	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\t  Find User Screen");

		string UserName = _ReadUserName();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser with [" << UserName << "] does not exist.\n";
			UserName = _ReadUserName();
		}

		clsUser User = clsUser::Find(UserName);

		if (!User.IsEmpty())
			cout << "\nUser Found :-)\n";
		else
			cout << "\nUser Wasn't Found :-(\n";

		_PrintUser(User);
	}

};

