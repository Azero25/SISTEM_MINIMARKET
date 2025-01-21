#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct authData {
    string name;
    string user;
    string pass;
    string role;
};

class Auth {
    private:
        vector<authData> accounts;
        const string userfile = "./databases/users.txt";

        // Function to load accounts from the user file
        void loadAccount() {
            accounts.clear();
            ifstream file(userfile);
            if(!file) {
                cerr << "Unable to open account file." << endl;
                return;
            }

            authData account;
            while(file >> account.name >> account.user >> account.pass >> account.role) {
                replace(account.name.begin(), account.name.end(), '_', ' ');
                accounts.push_back(account);
            }
            file.close();
        }

        // Function untuk mencari akun by username
        int findUserIndex(const string& username) {
            loadAccount();
            for(size_t i=0; i<accounts.size(); i++) {
                if(accounts[i].user == username) {
                    return i;
                }
            }
            return -1;
        }

        // Function to check akunnya ada / tidak
        bool isAccountAvailable(const string& username) {
            return findUserIndex(username) != -1;
        }

        // Function update data account
        void updateDataAccount() {
            ofstream file(userfile, ios::trunc);
            if(!file) { 
                cerr << "Error: Unable to update accounts file." << endl;
                return;
            }

            for(const auto& account: accounts) {
                string tempName = account.name;
                replace(tempName.begin(), tempName.end(), ' ', '_'); // Replace spaces with underscores
                file << tempName << " " << account.user << " " << account.pass << " " << account.role << endl;
            }
            file.close();
        }

        // Function untuk save data
        void saveAccount(const authData& account) {
            ofstream file(userfile, ios::app);
            if(!file) {
                cerr << "Error: Unable to save account to file!" << endl;
                return;
            }
            string tempName = account.name;
            replace(tempName.begin(), tempName.end(), ' ', '_'); // Replace spaces with underscores
            file << tempName << " " << account.user << " " << account.pass << " " << account.role << endl;
            file.close();
        }

    public:
        // Function untuk register
        void registerAccount(const string& nama, const string& username, const string& password) {
            if (isAccountAvailable(username)) {
                cout << "Error: Akun sudah ada, silakan buat lagi!" << endl;
                return;
            }
    
            const string& role = "pegawai";
            authData newAccount = {nama, username, password, role};
            saveAccount(newAccount);
        }

        // Function to log in
        bool loginAccount(const string& username, const string& password) {
            loadAccount();
            int index = findUserIndex(username);
            if (index != -1 && accounts[index].pass == password) {
                return true;
            }
            return false;
        }

        // function to get role account
        string getAccountRole(const string& username) {
            loadAccount();
            int index = findUserIndex(username);
            if(index != -1) {
                return accounts[index].role;
            }
            return "";
        }

        // function to get name account
        string getAccountName(const string& username) {
            loadAccount();
            int index = findUserIndex(username);
            if(index != -1) {
                return accounts[index].name;
            }
            return "";
        }

        // Function to change role account
        void changeRoleAccount(const string& username) {
            loadAccount();
            int index = findUserIndex(username);
            if(index != -1) {
                cout << "Akun ditemukan : \n";
                cout << "Nama       : " << accounts[index].name << endl;
                cout << "Username   : " << accounts[index].user << endl;
                cout << "Role       : " << accounts[index].role << endl;

                string newRole;
                cout << "\nMasukkan jenis role ganti : ";
                getline(cin, newRole);

                accounts[index].role = newRole;
                updateDataAccount();
                cout << "\nGanti role akun berhasil!" << endl;
            } else {
                cout << "\nError: Username tidak ditemukan!" << endl;
            }
        }

        // Function to reset password (Manager)
        void resetPasswordKaryawan(const string& username, const string& newPassword) {
            loadAccount();
            int index = findUserIndex(username);
            if (index != -1) {
                accounts[index].pass = newPassword;
                updateDataAccount();
                cout << "Reset password berhasil!" << endl;
            } else {
                cout << "Error: Username tidak ditemukan!" << endl;
            }
        }

        // Function to update password after login
        void updatePassword(const string& username, const string& oldPassword, const string& newPassword) {
            loadAccount();
            int index = findUserIndex(username);
            if (index != -1 && accounts[index].pass == oldPassword) {
                accounts[index].pass = newPassword;
                updateDataAccount();
                cout << "Password berhasil diperbaharui!" << endl;
            } else {
                cout << "Error: Username dan password salah!" << endl;
            }
        }

        // Function to delete account
        void deleteAccount(const string& username) {
            loadAccount();

            int index = findUserIndex(username);
            if(index != -1) {
                cout << "Akun ditemukan : \n";
                cout << "Nama       : " << accounts[index].name << endl;
                cout << "Username   : " << accounts[index].user << endl;
                cout << "Role       : " << accounts[index].role << endl;

                char option;
                cout << "\nApakah anda ingin menghapus akun ini? [y/n] : ";
                cin >> option;

                if(option == 'y' || option == 'Y') {
                    // Delete account from vector accounts
                    accounts.erase(accounts.begin() + index);
                    cout << "Akun dengan username \"" << username << "\" berhasil dihapus." << endl;

                    // update data account in userfile
                    updateDataAccount();
                } else {
                    cout << "Akun dengan username \"" << username << "\" tidak jadi dihapus." << endl;
                }

            } else {
                cout << "Akun dengan username \"" << username << "\" tidak ditemukan." << endl;
                return;
            }
        }

        // function to print logout message
        void logout() {
            cout << "Anda telah logout. Kembali ke menu utama...\n";
        }

        // Function to print an exit message
        void exit() {
            cout << "Terima kasih telah menggunakan aplikasi kami." << endl;
        }
};
