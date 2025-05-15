# -Bank-Management-System-in-C-
# 💼 Bank Management System in C++

A **console-based Bank Management System** built using **C++**, focusing on core concepts of **Object-Oriented Programming (OOP)** and **File Handling**. This project simulates a basic banking environment where users can manage bank accounts with essential functionalities such as account creation, deposit, withdrawal, and deletion.

> 🔧 This project is ideal for beginner to intermediate-level C++ programmers and can be used for academic purposes, resume projects, or learning OOP and file handling in C++.

---

## 📌 Table of Contents

- [Features](#-features)
- [Technologies Used](#-technologies-used)
- [Getting Started](#-getting-started)
- [Project Structure](#-project-structure)
- [How to Use](#-how-to-use)
- [Possible Improvements](#-possible-improvements)
- [Author](#-author)
- [License](#-license)

---

## 🚀 Features

🔹 Create a new bank account with a unique account number  
🔹 View account details using balance enquiry  
🔹 Deposit money into a specific account  
🔹 Withdraw money while checking for sufficient balance  
🔹 Modify existing account holder details  
🔹 Delete (close) a bank account  
🔹 View all account holders and balances  
🔹 Persistent data storage using binary file handling (`account.dat`)

---

## 💻 Technologies Used

- **C++**
- **Object-Oriented Programming**
- **File Handling (Binary I/O)**
- **Standard Template Library (STL)** (for input/output and file streams)
- Cross-platform compatible (Windows/Linux)

---

## 🛠️ Getting Started

### 🧰 Prerequisites

- C++ compiler (like **G++**, **MinGW**, or **Clang**)
- Terminal / Command Line
- Git (optional, for cloning)

### 🐧 Linux / macOS

```bash
# Clone the repository
git clone https://github.com/yourusername/Bank-Management-System.git
cd Bank-Management-System

# Compile the code
g++ bank_management.cpp -o bank

# Run the program
./bank
