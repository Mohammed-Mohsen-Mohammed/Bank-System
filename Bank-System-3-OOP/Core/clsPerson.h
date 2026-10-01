#pragma once
#include<iostream>
using namespace std;

class clsPerson
{
private:

	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:

	clsPerson(const string& FirstName, const string& LastName, const string& Email,
		const string& Phone)
	{
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	void SetFirstName(const string& FirstName)
	{
		_FirstName = FirstName;
	}

	string GetFirstName() const
	{
		return _FirstName;
	}
	__declspec(property(get = GetFirstName, put = SetFirstName))string FirstName;

	void SetLastName(const string& LastName)
	{
		_LastName = LastName;
	}

	string GetLastName() const
	{
		return _LastName;
	}
	__declspec(property(get = GetLastName, put = SetLastName))string LastName;

	void SetEmail(const string& Email)
	{
		_Email = Email;
	}

	string GetEmail() const
	{
		return _Email;
	}
	__declspec(property(get = GetEmail, put = SetEmail))string Email;

	void SetPhone(const string& Phone)
	{
		_Phone = Phone;
	}

	string GetPhone() const
	{
		return _Phone;
	}
	__declspec(property(get = GetPhone, put = SetPhone))string Phone;

	string FullName() const
	{
		return _FirstName + " " + _LastName;
	}

};