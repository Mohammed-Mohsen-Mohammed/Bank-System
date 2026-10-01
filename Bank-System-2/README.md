# Bank Management System — Version 2

![C++](https://img.shields.io/badge/C%2B%2B-Console%20Application-blue)
![Authentication](https://img.shields.io/badge/Authentication-Login-orange)
![Authorization](https://img.shields.io/badge/Authorization-Permissions-green)
![File Handling](https://img.shields.io/badge/File%20Handling-fstream-orange)

A console-based C++ banking system enhanced with user authentication, permission-based authorization, and user management.

---

## 📌 Overview

This version builds on the core banking functionality introduced in **Bank-System-1** and introduces a user management system with authentication and authorization.

Users must log in before accessing the application, and different permissions can be assigned to control access to specific operations.

---

## ✨ Features

### 👤 Client Management

The system continues to provide:

- Add new clients
- Display all clients
- Find clients by account number
- Update client information
- Delete clients

### 💰 Banking Transactions

The system supports:

- Deposit money
- Withdraw money
- View total balances

### 👥 User Management

Authorized users can manage system users through:

- Add new users
- Display users
- Find users
- Update users
- Delete users

Each user contains information such as:

- Username
- Password
- Permissions

### 🔐 Authentication

Users must log in using:

- Username
- Password

before accessing the main application.

The system validates the entered credentials and loads the corresponding user information.

### 🛡️ Authorization

Access to system operations is controlled using user permissions.

Available permissions include:

- Show Clients
- Add Client
- Delete Client
- Update Client
- Find Client
- Transactions
- Manage Users

Users can receive full access or a selected set of permissions.

### ⚙️ Permission Management

Permissions are represented using **bitwise flags**, allowing multiple permissions to be combined into a single permissions value.

Before protected operations are performed, the system checks whether the current user has the required permission.

---

## 🧰 Technologies & Concepts

| Technology / Concept | Usage |
|---|---|
| **C++** | Core programming language |
| **Structures** | Representing clients and users |
| **STL `vector`** | Managing records |
| **`fstream`** | Reading and writing files |
| **Functions** | Organizing application logic |
| **File Handling** | Persistent data storage |
| **Authentication** | User login and credential validation |
| **Authorization** | Controlling access to operations |
| **Bitwise Operators** | Combining and checking permissions |
| **Input Validation** | Handling invalid user input |
| **Console UI** | Menu-driven interaction |

---

## 📂 Project Structure

```text
Bank-System-2/
│
├── main.cpp
├── Clients.txt
├── Users.txt
└── README.md
```

---

## 💾 Data Storage

### Client Data

Client records are stored in:

`Clients.txt`

### User Data

User records are stored in:

`Users.txt`

Both files are used as persistent storage for the application.

Records are converted between structured data and text using a custom delimiter:

`#//#`

---

## 🔄 Application Flow

```text
Login
  ↓
Validate Username & Password
  ↓
Load Current User
  ↓
Main Menu
  ↓
Check Required Permission
  ↓
Perform Operation

This allows different users to access different parts of the system according to their assigned permissions.
```

---

## 🧠 Learning Focus

This version focuses on extending an existing C++ application with authentication and authorization.

Key areas practiced:

- User management
- Authentication
- Authorization
- Permission-based access control
- Bitwise permission flags
- File-based persistence
- Managing multiple data files
- Input validation
- Extending an existing application with authentication, authorization, and user management

---

## 👨‍💻 Author

**Mohammed Mohsen**

- GitHub: [Mohammed Mohsen](https://github.com/Mohammed-Mohsen-Mohammed)
- LinkedIn: [Mohammed Mohsen](https://www.linkedin.com/in/mohammed-mohsen-mohammed/)
