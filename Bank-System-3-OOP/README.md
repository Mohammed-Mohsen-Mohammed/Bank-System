# Bank Management System — Version 3

![C++](https://img.shields.io/badge/C%2B%2B-Console%20Application-blue)
![OOP](https://img.shields.io/badge/Design-Object--Oriented-green)
![Authentication](https://img.shields.io/badge/Authentication-Login-orange)
![Authorization](https://img.shields.io/badge/Authorization-Permissions-purple)
![File Handling](https://img.shields.io/badge/File%20Handling-fstream-orange)

A console-based C++ banking system redesigned using Object-Oriented Programming and extended with money transfers, transaction logging, login registration, and currency exchange.

---

## 📌 Overview

This version represents a major evolution of the previous Bank Management System.

The application was redesigned using Object-Oriented Programming, with separate classes for core entities, screens, and reusable utilities.

Alongside the existing client, transaction, authentication, and authorization features, this version introduces money transfers, transfer history, login registration, and currency exchange.

---

## ✨ Features

### 👤 Client Management

The system provides:

- Add new clients
- Display all clients
- Find clients by account number
- Update client information
- Delete clients

Client information includes:

- Account Number
- PIN Code
- Name
- Phone
- Email
- Account Balance

### 💰 Banking Transactions

The transaction module supports:

- Deposit
- Withdraw
- View total balances

### 🔄 Money Transfers

Clients can transfer money between accounts.

The transfer operation validates:

- Transfer amount
- Available balance
- Source and destination accounts
- Prevents transfers to the same account

After a successful transfer, the updated balances are displayed.

### 📋 Transfer Log

Successful transfers are recorded in:

```text
TransferLog.txt
```

Each transfer record contains information such as:

- Date and time
- Source account
- Destination account
- Transfer amount
- Source balance after transfer
- Destination balance after transfer
- Username who performed the transfer

### 👥 User Management

Authorized users can manage system users through:

- Add new users
- Display users
- Find users
- Update users
- Delete users

Users contain personal information along with:

- Username
- Password
- Permissions

### 🔐 Authentication & Authorization

Users must log in before accessing the main application.

The system uses permission-based authorization to control access to different operations.

Available permissions include:

- List Clients
- Add New Client
- Delete Client
- Update Clients
- Find Client
- Transactions
- Manage Users
- Login Register
- Currency Exchange

Permissions can be combined using bitwise flags.

### 📝 Login Register

Successful logins are recorded in:

LoginRegister.txt

Users with the appropriate permission can view the login register through the application.

### 💱 Currency Exchange

The system includes a currency management and exchange module.

It provides:

- List currencies
- Find currencies
- Update currency rates
- Currency calculator

Currency information includes:

- Country
- Currency Code
- Currency Name
- Exchange Rate

The calculator performs conversions through USD.

Currency data is stored in:

Currencies.txt

---

## 🏗️ OOP Design

The application was redesigned around reusable classes with separate responsibilities.

### `clsPerson`

A base class that contains common personal information:

- First Name
- Last Name
- Email
- Phone
- Full Name

### `clsBankClient`

Inherits from `clsPerson` and manages...

- Client management
- Deposits
- Withdrawals
- Transfers
- Client lookup
- Balance calculations

### `clsUser`

Inherits from clsPerson and handles:

- User management
- Authentication
- Permissions
- Login registration

### `clsCurrency`

Responsible for:

- Currency data
- Currency lookup
- Exchange rates
- Currency conversion
- Currency persistence

### `clsScreen`

A base class for application screens that provides common screen functionality and access-rights checking for screens that use the shared access-control mechanism.

---

## 🧰 Utility Classes

The project also contains reusable utility classes.

| Class              | Purpose                                                          |
| ------------------ | ---------------------------------------------------------------- |
| `clsDate`          | Date, time, and calendar operations                              |
| `clsString`        | String manipulation and processing                               |
| `clsUtil`          | General utilities, random generation, encryption, and formatting |
| `clsInputValidate` | Numeric, date, and string input validation                       |

---

## 🧰 Technologies & Concepts

| Technology / Concept     | Usage                                             |
| ------------------------ | ------------------------------------------------- |
| **C++**                  | Core programming language                         |
| **OOP**                  | Organizing the application into reusable classes  |
| **Inheritance**          | Sharing common functionality through base classes |
| **Encapsulation**        | Managing data and operations within classes       |
| **STL `vector`**         | Managing collections                              |
| **Templates**            | Reusable input-validation functions               |
| **`fstream`**            | Reading and writing persistent data               |
| **File Handling**        | Text-file data persistence                        |
| **Authentication**       | User login                                        |
| **Authorization**        | Permission-based access control                   |
| **Bitwise Operators**    | Combining and checking permissions                |
| **String Processing**    | Parsing and manipulating text data                |
| **Date & Time Handling** | Managing application dates and logs               |
| **Console UI**           | Menu-driven interaction                           |

---

## 📂 Project Structure

The application is organized into three main components: core classes, reusable utility classes, and application screens.

```text
Bank-System-3-OOP/
│
├── Core/
│   ├── clsBankClient.h
│   ├── clsCurrency.h
│   ├── clsPerson.h
│   └── clsUser.h
│
├── Lib/
│   ├── clsDate.h
│   ├── clsInputValidate.h
│   ├── clsString.h
│   └── clsUtil.h
│
├── Screens/
│   ├── Client/
│   │   ├── clsAddNewClientScreen.h
│   │   ├── clsClientsListScreen.h
│   │   ├── clsDeleteClientScreen.h
│   │   ├── clsDepositScreen.h
│   │   ├── clsFindClientScreen.h
│   │   ├── clsTotalBalancesScreen.h
│   │   ├── clsTransactionsScreen.h
│   │   ├── clsTransferLogScreen.h
│   │   ├── clsTransferScreen.h
│   │   ├── clsUpdateClientScreen.h
│   │   └── clsWithdrawScreen.h
│   │
│   ├── Currency/
│   │   ├── clsCurrenciesListScreen.h
│   │   ├── clsCurrencyCalculatorScreen.h
│   │   ├── clsCurrencyExchangeMainScreen.h
│   │   ├── clsFindCurrencyScreen.h
│   │   └── clsUpdateCurrencyRateScreen.h
│   │
│   ├── User/
│   │   ├── clsAddNewUserScreen.h
│   │   ├── clsDeleteUserScreen.h
│   │   ├── clsFindUserScreen.h
│   │   ├── clsLoginRegisterScreen.h
│   │   ├── clsLoginScreen.h
│   │   ├── clsManageUsersScreen.h
│   │   ├── clsUpdateUserScreen.h
│   │   └── clsUsersListScreen.h
│   │
│   ├── clsMainScreen.h
│   └── clsScreen.h
│
├── Global.h
├── main.cpp
└── README.md
```

---

## 💾 Data Storage

The application uses text files for persistent storage:

| File                | Purpose                    |
| ------------------- | -------------------------- |
| `Clients.txt`       | Client records             |
| `Users.txt`         | User records               |
| `Currencies.txt`    | Currency records           |
| `TransferLog.txt`   | Transfer history           |
| `LoginRegister.txt` | Login registration records |

---

## 🧠 Learning Focus

This version focuses on applying Object-Oriented Programming to a larger console application.

Key areas practiced:

- Designing classes around specific responsibilities
- Inheritance and reusable base classes
- Encapsulation
- Separating application screens from core logic
- Building reusable utility classes
- Implementing authentication and authorization
- Managing permission-based access
- Working with persistent data
- Handling dates and strings
- Extending an existing application with new modules
- Refactoring a procedural system into an OOP-based design

---

## 👨‍💻 Author

**Mohammed Mohsen**

- GitHub: [Mohammed Mohsen](https://github.com/Mohammed-Mohsen-Mohammed)
- LinkedIn: [Mohammed Mohsen](https://www.linkedin.com/in/mohammed-mohsen-mohammed/)
