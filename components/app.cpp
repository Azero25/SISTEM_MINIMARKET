#include <iostream>
#include <string>
#include "auth.cpp"
#include "home.cpp"

using namespace std;

// Helper function to convert a string to lowercase
string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void app() {
    string nama, username, password, newPassword, newRole, getName;
    string kodeBarang, namaBarang, namaSuplier, tanggal;
    int jumlahBarang, hargaBarang, hargaJual;
    char authOption, attendOption, karyawanOption, managerOption, kasirOption, gudangOption, returnOption;
    bool authenticated = false;
    Auth myAuth;
    Home myHome;

    while (true) {
        // Authentication menu
        while (!authenticated) {
            cout << "\n+====================================+" << endl;
            cout << "| Selamat datang di Toko Berkah Jaya |" << endl;
            cout << "+====================================+" << endl;
            cout << "Login dan Register Akun\n";
            cout << "1. Register Account\n";
            cout << "2. Login Account\n";
            cout << "3. Exit/Keluar\n"; 
            cout << "Masukkan pilihan anda [1/2/3]: ";
            cin >> authOption;
            cin.ignore();

            switch (authOption) {
                case '1':
                    system("cls");
                    cout << "=== Menu Registrasi Akun === " << endl;
                    cout << "Masukkan nama anda : ";
                    getline(cin, nama);
                    cout << "Masukkan username : ";
                    getline(cin, username);
                    cout << "Masukkan password : ";
                    getline(cin, password);

                    username = toLowerCase(username); // Convert to lowercase

                    myAuth.registerAccount(nama, username, password);
                    cout << "Akun berhasil diregistrasi. " << endl;
                    cout << "Tekan enter untuk kembali ke menu login...";
                    cin.get();
                    system("cls");
                    break;

                case '2':
                    system("cls");
                    cout << "=== Menu Login Akun === " << endl;
                    cout << "Masukkan username : ";
                    getline(cin, username);
                    cout << "Masukkan password : ";
                    getline(cin, password);

                    username = toLowerCase(username); // Convert to lowercase

                    if (myAuth.loginAccount(username, password)) {
                        system("cls");
                        authenticated = true;
                        cout << "Selamat datang, " << myAuth.getAccountName(username) << "!\n";
                    } else {
                        system("cls");
                        cout << "Username atau password salah. Silakan coba lagi.\n";
                    }
                    break;

                case '3':
                    system("cls");
                    myAuth.exit();
                    return; // Exit the app

                default:
                    system("cls");
                    cin.ignore();
                    cout << "Pilihan anda salah, silahkan coba lagi";
                    cin.get();
                    system("cls");
                    break;
            }
        }

        // After authentication, navigate to the appropriate menu
        string role = myAuth.getAccountRole(username);

        if(role == "pegawai") {
            while(authenticated) {
                cout << "\n+=============================+" << endl;
                cout << "| Menu Utama Toko Berkah Jaya |" << endl;
                cout << "|           Karyawan          |" << endl;
                cout << "+=============================+" << endl;
                cout << "1. Presensi kerja" << endl;
                cout << "2. Update password account" << endl;
                cout << "3. Logout/Keluar" << endl;
                cout << "Masukkan pilihan anda [1/2/3]: ";
                cin >> karyawanOption;
                cin.ignore();

                switch (karyawanOption) {
                    case '1':
                        system("cls");
                        getName = myAuth.getAccountName(username);
                        myHome.catatPresensi(getName, role);
                        cout << "\nTekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '2':
                        system("cls");
                        cout << "=== Menu Update Password ===" << endl;
                        cout << "Masukkan username : ";
                        getline(cin, username);
                        cout << "Masukkan password lama : ";
                        getline(cin, password);
                        cout << "Masukkan password baru : ";
                        getline(cin, newPassword);
                    
                        // convert input username and password to lower case
                        username = toLowerCase(username);

                        myAuth.updatePassword(username, password, newPassword);
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '3':
                        system("cls");
                        myAuth.logout();
                        authenticated = false;
                        break;
                    default:
                        system("cls");
                        cin.ignore();
                        cout << "Pilihan anda salah, silahkan coba lagi";
                        cin.get();
                        system("cls");
                        break;
                }
            }
        } else if(role == "manager") {
            while(authenticated) {
                cout << "\n+=============================+" << endl;
                cout << "| Menu Utama Toko Berkah Jaya |" << endl;
                cout << "|           Manager           |" << endl;
                cout << "+=============================+" << endl;\
                cout << "1. Rekap pengeluaran" << endl;
                cout << "2. Rekap pendapatan" << endl;
                cout << "3. Rekap kinerja karyawan" << endl;
                cout << "4. Presensi kerja" << endl;
                cout << "5. Ganti role karyawan" << endl;
                cout << "6. Reset password karyawan" << endl;
                cout << "7. Update password account" << endl;
                cout << "8. Delete account" << endl;
                cout << "9. Logout/Keluar" << endl;
                cout << "Masukkan pilihan anda [1/2/3/dst..]: ";
                cin >> managerOption;
                cin.ignore();

                switch(managerOption) {
                    case '1':
                        system("cls");
                        myHome.rekapPengeluaranBulanan();
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '2':
                        system("cls");
                        myHome.rekapPendapatanBulanan();
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '3':
                        system("cls");
                        myHome.rekapPresensiBulanan();
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '4':
                        system("cls");
                        getName = myAuth.getAccountName(username);
                        myHome.catatPresensi(getName, role);
                        cout << "\nTekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '5':
                        system("cls");
                        cout << "=== Menu Ganti Role Karyawan ===" << endl;
                        cout << "Jenis Role : pegawai, gudang, kasir, return, manager" << endl;
                        cout << "Masukkan username : ";
                        getline(cin, username);

                        myAuth.changeRoleAccount(username);
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '6':
                        system("cls");
                        cout << "=== Menu Reset Password Karyawan ===" << endl;
                        cout << "Masukkan username karyawan : ";
                        getline(cin, username);
                        cout << "Masukkan password baru : ";
                        getline(cin, newPassword);
                    
                        // convert input username and password to lower case
                        username = toLowerCase(username);
                    
                        myAuth.resetPasswordKaryawan(username, newPassword);
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '7':
                        system("cls");
                        cout << "=== Menu Update Password ===" << endl;
                        cout << "Masukkan username : ";
                        getline(cin, username);
                        cout << "Masukkan password lama : ";
                        getline(cin, password);
                        cout << "Masukkan password baru : ";
                        getline(cin, newPassword);
                    
                        // convert input username to lower case
                        username = toLowerCase(username);

                        myAuth.updatePassword(username, password, newPassword);
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '8':
                        system("cls");
                        cout << "=== Menu Delete Account ===" << endl;
                        cout << "Masukkan username : ";
                        getline(cin, username);

                        username = toLowerCase(username);
                        myAuth.deleteAccount(username);
                        cin.ignore();
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '9':
                        system("cls");
                        myAuth.logout();
                        authenticated = false;
                        break;
                    default:
                        system("cls");
                        cin.ignore();
                        cout << "Pilihan anda salah, silahkan coba lagi";
                        cin.get();
                        system("cls");
                        break;
                }

            }
        } else if(role == "kasir") {
            while (authenticated) {
                cout << "\n+=============================+" << endl;
                cout << "| Menu Utama Toko Berkah Jaya |" << endl;
                cout << "|            Kasir            |" << endl;
                cout << "+=============================+" << endl;
                cout << "1. Transaksi penjualan barang" << endl;
                cout << "2. Presensi kerja" << endl;
                cout << "3. Update password account" << endl;
                cout << "4. Logout/Keluar" << endl;
                cout << "Masukkan pilihan anda [1/2/3/4]: ";
                cin >> kasirOption;
                cin.ignore();

                switch (kasirOption) {
                    case '1':
                        system("cls");
                        myHome.transactionBarang();
                        cin.ignore();
                        cout << "\n\nTransaksi selesai. Tekan enter untuk kembali...";
                        cin.get();
                        system("cls");
                        break;
                    case '2':
                        system("cls");
                        getName = myAuth.getAccountName(username);
                        myHome.catatPresensi(getName, role);
                        cout << "\nTekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '3':
                        system("cls");
                        cout << "=== Menu Update Password ===" << endl;
                        cout << "Masukkan password lama : ";
                        getline(cin, password);
                        cout << "Masukkan password baru : ";
                        getline(cin, newPassword);

                        password = toLowerCase(password);
                        newPassword = toLowerCase(newPassword);

                        myAuth.updatePassword(username, password, newPassword);
                        cout << "Password berhasil diperbarui. Tekan enter untuk kembali...";
                        cin.get();
                        system("cls");
                        break;
                    case '4':
                        system("cls");
                        myAuth.logout();
                        authenticated = false;
                        break;
                    default:
                        system("cls");
                        cin.ignore();
                        cout << "Pilihan anda salah, silahkan coba lagi";
                        cin.get();
                        system("cls");
                        break;
                }
            }
        } else if(role == "gudang") {
            while (authenticated) {
                cout << "\n+=============================+" << endl;
                cout << "| Menu Utama Toko Berkah Jaya |" << endl;
                cout << "|        Staf Gudang          |" << endl;
                cout << "+=============================+" << endl;
                cout << "1. Input data barang masuk" << endl;
                cout << "2. Menampilkan data barang masuk" << endl;
                cout << "3. Update data barang masuk" << endl;
                cout << "4. Delete data barang masuk" << endl;
                cout << "5. Menampilkan data barang keluar" << endl;
                cout << "6. Presensi pekerja" << endl;
                cout << "7. Update password account" << endl;
                cout << "8. Logout/Keluar" << endl;
                cout << "Masukkan pilihan anda [1/2/3/dst..]: ";
                cin >> gudangOption;
                cin.ignore();

                switch(gudangOption) {
                    case '1':
                        system("cls");
                        cout << "=== Menu Input Barang Masuk ===" << endl;
                        cout << "Masukkan kode barang : ";
                        getline(cin, kodeBarang);
                        cout << "Masukkan nama barang : ";
                        getline(cin, namaBarang);
                        cout << "Masukkan jumlah barang : ";
                        cin >> jumlahBarang;
                        cout << "Masukkan harga barang (dari supplier) : ";
                        cin >> hargaBarang;
                        cout << "Masukkan harga jual barang : ";
                        cin >> hargaJual;
                        cin.ignore();
                        cout << "Masukkan nama supplier : ";
                        getline(cin, namaSuplier);

                        myHome.inputBarangMasuk(kodeBarang, namaBarang, jumlahBarang, hargaBarang, hargaJual, namaSuplier);
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '2':
                        system("cls");
                        myHome.showBarangMasuk();
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '3':
                        system("cls");
                        cout << "=== Menu Update Barang Masuk ===" << endl;
                        cout << "Masukkan kode barang : ";
                        getline(cin, kodeBarang);

                        myHome.updateDataBarangMasuk(kodeBarang);
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '4':
                        system("cls");
                        cout << "Masukkan kode barang yang akan dicari : ";
                        getline(cin, kodeBarang);

                        myHome.deleteDataBarangMasuk(kodeBarang);
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '5':
                        system("cls");
                        myHome.showBarangKeluar();
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '6':
                        system("cls");
                        getName = myAuth.getAccountName(username);
                        myHome.catatPresensi(getName, role);
                        cout << "\nTekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '7':
                        system("cls");
                        cout << "=== Menu Update Password ===" << endl;
                        cout << "Masukkan username : ";
                        getline(cin, username);
                        cout << "Masukkan password lama : ";
                        getline(cin, password);
                        cout << "Masukkan password baru : ";
                        getline(cin, newPassword);
                    
                        // convert input username and password to lower case
                        username = toLowerCase(username);
                        password = toLowerCase(password);
                        newPassword = toLowerCase(newPassword);

                        myAuth.updatePassword(username, password, newPassword);
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '8':
                        system("cls");
                        myAuth.logout();
                        authenticated = false;
                        break;
                    default:
                        system("cls");
                        cin.ignore();
                        cout << "Pilihan anda salah, silahkan coba lagi";
                        cin.get();
                        system("cls");
                        break;
                }
            }
        } else if(role == "return") {
            while(authenticated) {
                cout << "\n+=============================+" << endl;
                cout << "| Menu Utama Toko Berkah Jaya |" << endl;
                cout << "|            Return           |" << endl;
                cout << "+=============================+" << endl;
                cout << "1. Input data barang return" << endl;
                cout << "2. Update data barang return" << endl;
                cout << "3. Menampilkan data barang return" << endl;
                cout << "4. Delete data barang return" << endl;
                cout << "5. Presensi kerja" << endl;
                cout << "6. Update password account" << endl;
                cout << "7. Logout/Keluar" << endl;
                cout << "Masukkan pilihan anda [1/2/3/dst..]: ";
                cin >> returnOption;
                cin.ignore();

                switch (returnOption) {
                    case '1':
                        system("cls");
                        cout << "=== Menu Input Data Return === " << endl;
                        cout << "Silahkan masukkan kode barang : ";
                        getline(cin, kodeBarang);
                        cout << "Silahkan masukkan tanggal pembelian barang (format=dd-mm-YY): ";
                        getline(cin, tanggal);

                        myHome.inputBarangReturn(kodeBarang, tanggal);
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '2':
                        system("cls");
                        cout << "=== Menu Update Data Return === " << endl;
                        cout << "Masukkan kode barang : ";
                        getline(cin, kodeBarang);
                        myHome.updateBarangReturn(kodeBarang);
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '3':
                        system("cls");
                        myHome.showBarangReturn();
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '4':
                        system("cls");
                        cout << "=== Menu Delete Data Return ===\n";
                        cout << "Masukkan kode barang yang akan dicari : ";
                        getline(cin, kodeBarang);
                        
                        myHome.deleteBarangReturn(kodeBarang);
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '5':
                        system("cls");
                        getName = myAuth.getAccountName(username);
                        myHome.catatPresensi(getName, role);
                        cout << "\nTekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '6':
                        system("cls");
                        cout << "==== Menu Update Password ====" << endl;
                        cout << "Masukkan username : ";
                        getline(cin, username);
                        cout << "Masukkan password lama : ";
                        getline(cin, password);
                        cout << "Masukkan password baru : ";
                        getline(cin, newPassword);

                        myAuth.updatePassword(username, password, newPassword);
                        cout << "Tekan enter untuk melanjutkan...";
                        cin.get();
                        system("cls");
                        break;
                    case '7':
                        system("cls");
                        myAuth.logout();
                        authenticated = false;
                        break;
                    default:
                        system("cls");
                        cout << "Pilihan anda salah, silahkan coba lagi";
                        cin.get();
                        system("cls");
                        break;
                }
            }
        }
    }
}