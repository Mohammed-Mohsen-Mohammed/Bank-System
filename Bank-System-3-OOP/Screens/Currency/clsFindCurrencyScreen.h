#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsString.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:

	static string _ReadCurrencyCode()
	{
		string CurrencyCode;
		cout << "\nPlease Enter Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();

		return CurrencyCode;
	}

	static string _ReadCountryName()
	{
		string CountryName;
		cout << "\nPlease Enter Country Name: ";
		CountryName = clsInputValidate::ReadString();

		return CountryName;
	}

	static void _PrintCurrency(const clsCurrency& Currency)
	{

		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();
		cout << "\n_____________________________\n";

	}

	static void _ShowResults(const clsCurrency& Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Was Not Found :-(\n";
		}
	}

public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\tFind Currency Screen");

		short Choice;
		cout << "\nFind By: [1] Code or [2] Country: ";
		Choice = clsInputValidate::ReadNumberBetween<short>(1, 2);

		if (Choice == 1)
		{
			string Code = clsString::UpperAllString(_ReadCurrencyCode());
			clsCurrency Currency = clsCurrency::FindByCode(Code);
			_ShowResults(Currency);
		}
		else
		{
			string CountryName = clsString::UpperFirstLetterOfEachWord(_ReadCountryName());
			clsCurrency Currency = clsCurrency::FindByCountry(CountryName);
			_ShowResults(Currency);
		}
		
	}

};

