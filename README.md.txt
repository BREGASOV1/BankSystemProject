# Bank System (OOP) 🔐

A secure C++ banking system with user management, transactions, and currency conversion.

---

## 🚀 Quick Start
1. **First Login**  
   - Username: `Admin`  
   - Password: `222` *(stored as 444 in Users.txt)*

2. Run in Visual Studio:  
   - Open `Bank-System-OOP.sln` → Press **F5**

---

## 🔑 Key Features
- **User/Client Management**  
  Add, delete, update, search, and view all data.  
  *(Passwords shown decrypted in the system)*

- **Transactions**  
  Deposit, withdraw, transfer funds, view balances.
  All Transfers you make will be saved in txt file, so you can review it.

- **Currency Conversion**  
  Search currencies, calculate exchange rates.

- **Security**  
  - manual-logout  
  - 3 failed attempts , the program will close then you have to run it again  
  - Encrypted passwords in files:  
    - Users: Key `2` (e.g., `222` → `444`)  
    - Clients: Key `15`  
    - LoginRegister File: Key `25`(where all Logins attemps will be saved, so you can review it)

---

## 📁 File Structure

BankSystemProject/
├── RequiredFiles/ # Encrypted data storage
│ ├── Users.txt
│ ├── Currencies.txt
│ ├── TransferLog.txt
│ └── LoginRegister.txt
├── include/ # Header files (.h)
├── src/ # Source files (.cpp)
├── Bank-System-OOP.sln # Visual Studio solution
├── LICENSE # MIT License terms
└── README.md # Project documentation

## ⚙️ Customization

-You can change what you want in the code, like encryption keys (manualy in the code).
-it is well organized code, everything has its class so any change you apply on a section,
 it will be applied in all sections where this section is used.
-If you decided to change encryption keys, first be sure to store orginal ones
 in a file, then store them again in "Users.txt" file encrypted with new key
 then you are good and no mistakes will be there.

⚠️ Important Notes

🔄 Backup files before making changes

🔐 Change default admin password immediately

💾 Encryption keys affect existing data - modify carefully


## 📜 License  
[MIT License](LICENSE)
