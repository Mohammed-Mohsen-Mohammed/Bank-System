#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "clsString.h"

class clsCurrency
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };

	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(const string& Line,
		const string& Seperator = "#//#")
	{
		vector <string> vCurrencyData = clsString::Split(Line, Seperator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1],
			vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static string _ConvertCurrencyObjectToLine(const clsCurrency& Currency,
		const string& Seperator = "#//#")
	{
		string CurrencyData = "";

		CurrencyData += Currency.Country() + Seperator;
		CurrencyData += Currency.CurrencyCode() + Seperator;
		CurrencyData += Currency.CurrencyName() + Seperator;
		CurrencyData += to_string(Currency.Rate());

		return CurrencyData;
	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile()
	{
		vector <clsCurrency> vCurrencies;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				vCurrencies.push_back(_ConvertLineToCurrencyObject(Line));
			}

			MyFile.close();
		}

		return vCurrencies;
	}

	static void _SaveCurrenciesDataToFile(const vector<clsCurrency>& vCurrencies)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		if (MyFile.is_open())
		{
			string DataLine;
			for (const clsCurrency& C : vCurrencies)
			{
				DataLine = _ConvertCurrencyObjectToLine(C);
				MyFile << DataLine << endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& C : vCurrencies)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}

		_SaveCurrenciesDataToFile(vCurrencies);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode, const string& Country, const string& CurrencyCode
		, const string& CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty() const
	{
		return (_Mode == enMode::EmptyMode);
	}

	string Country() const
	{
		return _Country;
	}

	string CurrencyCode() const
	{
		return _CurrencyCode;
	}

	string CurrencyName() const
	{
		return _CurrencyName;
	}

	void UpdateRate(float NewRate)
	{
		if (NewRate <= 0)
		{
			return;
		}

		_Rate = NewRate;
		_Update();
	}

	float Rate() const
	{
		return _Rate;
	}

	static clsCurrency FindByCode(const string& CurrencyCode)
	{
		string Code = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.CurrencyCode() == Code)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();

		}

		return _GetEmptyCurrencyObject();

	}

	static clsCurrency FindByCountry(const string& Country)
	{
		string CountryName = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country()) == CountryName)
				{
					MyFile.close();
					return Currency;
				}

			}

			MyFile.close();

		}

		return _GetEmptyCurrencyObject();

	}

	static bool IsCurrencyExist(const string& CurrencyCode)
	{

		clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);

		return (!C1.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float Amount) const
	{
		return (Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, const clsCurrency& Currency2) const
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (AmountInUSD * Currency2.Rate());
	}

};

