# Bank Management System

![C++](https://img.shields.io/badge/C%2B%2B-Console%20Application-blue)
![File Handling](https://img.shields.io/badge/File%20Handling-fstream-orange)
![CRUD](https://img.shields.io/badge/Operations-CRUD-green)

A console-based C++ banking system for managing clients and performing basic banking transactions.

---

## 📌 Overview

This version focuses on the core functionality of a banking system, including client management, basic banking operations, and persistent data storage using text files.

The application provides a menu-driven interface for managing client records and performing financial transactions.

---

## ✨ Features

### 👤 Client Management

- Add new clients
- Display all clients
- Find clients by account number
- Update client information
- Delete clients

Each client record contains:

- Account Number
- PIN Code
- Name
- Phone
- Account Balance

### 💰 Banking Transactions

- Deposit money
- Withdraw money
- View total balances
- Validate transaction input and account balances

### 💾 Data Persistence

- Store client data in `Clients.txt`
- Load client records from the file
- Save changes back to the file

### 🛡️ Input Validation

- Validate menu selections
- Handle invalid numeric input
- Validate transaction input

---

## 🧰 Technologies & Concepts

| Technology / Concept | Usage |
|---|---|
| **C++** | Core programming language |
| **Structures** | Representing client data |
| **STL `vector`** | Managing client records |
| **`fstream`** | Reading and writing files |
| **Functions** | Organizing application logic |
| **File Handling** | Persistent data storage |
| **Input Validation** | Handling invalid user input |
| **Console UI** | Menu-driven interaction |

---

## 📂 Project Structure

```text
Bank-System-1/
│
├── main.cpp
├── Clients.txt
└── README.md
```
---

## 💾 Data Storage

Client records are stored in:

`Clients.txt`

Each client is converted into a text record and stored using the custom delimiter:

`#//#`

The application uses file handling to load existing clients and save modifications to persistent storage.

---

## 🧠 Learning Focus

This version was built to apply C++ fundamentals in a complete console application.

Key areas practiced:

- Structures and functions
- STL `vector`
- File input/output
- Data serialization and parsing
- Input validation
- CRUD operations
- Menu-driven application design
- Basic banking logic

---

## 👨‍💻 Author

**Mohammed Mohsen**

- GitHub: [Mohammed Mohsen](https://github.com/Mohammed-Mohsen-Mohammed)
- LinkedIn: [Mohammed Mohsen](https://www.linkedin.com/in/mohammed-mohsen-mohammed/)
