#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsUser.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{
private:

	static bool _Login()
	{
		bool LoginFaild = false;
		short FaildLoginCounter = 3;

		string Username, Password;

		do
		{

			if (LoginFaild)
			{
				FaildLoginCounter--;

				cout << "\nInvalid Username/Password!\n";
				cout << "You have " << FaildLoginCounter << " Trial(s) to login.\n\n";
			}

			if (FaildLoginCounter == 0)
			{
				cout << "\nYour are locked after 3 faild trials.\n\n";
				return false;
			}

			cout << "Enter Username? ";
			cin >> Username;

			cout << "Enter Password? ";
			cin >> Password;

			CurrentUser = clsUser::Find(Username, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenu();

		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t     Login Screen");
		return _Login();
	}

};

