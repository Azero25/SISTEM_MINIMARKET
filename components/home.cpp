#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <unordered_map>
#include <limits>
#include <regex>
#include <algorithm>

using namespace std;

struct Presensi {
    string nama;
    string role;
    string tanggal;
    string masuk;
    string keluar;
};

struct dataMasuk{
    int id;
    string tanggal;
    string kodeBarang;
    string namaBarang;
    int jumlahBarang;
    int hargaSupplier;
    int hargaJual;
    string namaSupplier;
    string tanggalUpdate;
};

struct dataBarang {
    string kodeBarang;
    string namaBarang;
    int jumlahBarang;
    int hargaBarang;
};

struct Barang {
    string kodeBarang;
    string namaBarang;
    int jumlah;
    int harga;
};

struct dataKeluar {
    int id;
    string tanggal;
    string kodeBarang;
    string namaBarang;
    int jumlahBarang;
    int hargaBarang;
};

struct dataReturn {
    int id;
    string tanggal_keluar;
    string kodeBarang;
    string namaBarang;
    int jumlahBarang;
    int hargaBarang;
    string tanggal_return;
};


class Home {
    private:
        vector<Presensi> presensi;
        vector<dataMasuk> masuk;
        vector<dataBarang> barang;
        vector<dataKeluar> keluar;
        vector<dataReturn> returnD;

        const string fileattend = "./databases/attendence.txt";
        const string filemasuk = "./databases/barangmasuk.txt";
        const string filebarang = "./databases/databarang.txt";
        const string filekeluar = "./databases/barangkeluar.txt";
        const string filereturn = "./databases/barangreturn.txt";

        // function load data barang masuk
        void loadBarangMasuk() {
            masuk.clear();

            ifstream file(filemasuk);
            if(!file) {
                cerr << "Error: File cannot be open." << endl;
                return; 
            }

            dataMasuk Dmasuk;
            while(file >> Dmasuk.id >> Dmasuk.tanggal >> Dmasuk.kodeBarang >> Dmasuk.namaBarang >> Dmasuk.jumlahBarang >> Dmasuk.hargaSupplier >> Dmasuk.hargaJual >> Dmasuk.namaSupplier >> Dmasuk.tanggalUpdate) {
                replace(Dmasuk.namaBarang.begin(), Dmasuk.namaBarang.end(), '_', ' ');
                replace(Dmasuk.namaSupplier.begin(), Dmasuk.namaSupplier.end(), '_', ' ');
                masuk.push_back(Dmasuk);
            }
            file.close();
        }

        // function load data barang
        void loadDataBarang() {
            barang.clear();

            ifstream file(filebarang);
            if(!file) {
                cerr << "Error: File cannot be open." << endl;
                return; 
            }

            dataBarang Dbarang;
            while(file >> Dbarang.kodeBarang >> Dbarang.namaBarang >> Dbarang.jumlahBarang >> Dbarang.hargaBarang) {
                replace(Dbarang.namaBarang.begin(), Dbarang.namaBarang.end(), '_', ' ');
                barang.push_back(Dbarang);
            }
            file.close();
        }

        // function load data barang keluar
        void loadBarangKeluar() {
            keluar.clear();

            ifstream file(filekeluar);
            if(!file) {
                cerr << "Error: File cannot be open." << endl;
                return;
            }

            dataKeluar Dkeluar;
            while(file >> Dkeluar.id >> Dkeluar.tanggal >> Dkeluar.kodeBarang >> Dkeluar.namaBarang >> Dkeluar.jumlahBarang >> Dkeluar.hargaBarang) {
                replace(Dkeluar.namaBarang.begin(), Dkeluar.namaBarang.end(), '_', ' ');
                keluar.push_back(Dkeluar);
            }
            file.close();
        }

        // function load data return barang
        void loadDataReturn() {
            returnD.clear();

            ifstream file(filereturn);
            if(!file) {
                cerr << "Error: File cannot be open." << endl;
                return;
            }
            
            dataReturn Dreturn;
            while(file >> Dreturn.id >> Dreturn.tanggal_keluar >> Dreturn.kodeBarang >> Dreturn.namaBarang >> Dreturn.jumlahBarang >> Dreturn.hargaBarang >> Dreturn.tanggal_return) {
                replace(Dreturn.namaBarang.begin(), Dreturn.namaBarang.end(), '_', ' ');
                returnD.push_back(Dreturn);
            }
            file.close();
        }

        // Function to load data presensi
        void loadPresensi() {
            presensi.clear();

            ifstream file(fileattend);
            if(!file) {
                cerr << "Error: File cannot be open." << endl;
                return;
            }

            Presensi Dpresensi;
            while(file >> Dpresensi.nama >> Dpresensi.role >> Dpresensi.tanggal >> Dpresensi.masuk >> Dpresensi.keluar) {
                replace(Dpresensi.nama.begin(), Dpresensi.nama.end(), '_', ' ');
                presensi.push_back(Dpresensi);
            }
            file.close();
        }

        // function to find index id barang masuk
        int findMasukId(const int masuk_id) {
            loadBarangMasuk();
            for(size_t i=0; i<masuk.size(); i++) {
                if(masuk[i].id == masuk_id) {
                    return i;
                }
            }
            return -1;
        }

        // Function to find index barang masuk by kodeBarang
        int findMasukIndex(const string& kode) {
            loadBarangMasuk();
            for(size_t i=0; i<masuk.size(); i++) {
                if(masuk[i].kodeBarang == kode) {
                    return i;
                }
            }
            return -1;
        }

        // Function to find index barang masuk by id
        int findMasukIndexById(const int& id) {
            loadBarangMasuk();
            for(size_t i=0; i<masuk.size(); i++) {
                if(masuk[i].id == id) {
                    return i;
                }
            }
            return -1;
        }

        // function to find index data barang by kodeBarang
        int findBarangIndex(const string& kode) {
            loadDataBarang();
            for(size_t i=0; i<barang.size(); i++) {
                if(barang[i].kodeBarang == kode) {
                    return i;
                }
            }
            return -1;
        }

        // function to find index barang keluar
        int findKeluarIndex(const string& kode, const string& tanggal) {
            loadBarangKeluar();
            for(size_t i=0; i<keluar.size(); i++) {
                if(keluar[i].kodeBarang == kode && keluar[i].tanggal == tanggal) {
                    return i;
                }
            }
            return -1;
        }

        int findKeluarId(const int& id) {
            for(size_t i=0 ; i<keluar.size(); i++) {
                if(keluar[i].id == id) {
                    return i;
                }
            }
            return -1;
        }

        // Function to find return index by kodeBarang
        int findReturnIndex(const string& kode) {
            loadDataReturn();
            for(size_t i=0; i<returnD.size(); i++) {
                if(returnD[i].kodeBarang == kode) {
                    return i;
                }
            }
            return -1;
        }

        // Function to find return index  by return_id
        int findReturnIndexById(const int& id) {
            loadDataReturn();
            for(size_t i=0; i<returnD.size(); i++) {
                if(returnD[i].id == id) {
                    return i;
                }
            }
            return -1;
        }

        // function to find presensi index by nama dan tanggal
        int findPresensiIndex(const string& nama, const string& tanggal) {
            loadPresensi();
            for(size_t i=0; i<presensi.size(); i++) {
                if(presensi[i].nama == nama && presensi[i].tanggal == tanggal) {
                    return i;
                }
            }
            return -1;
        }
        
        // function update data barang masuk
        void updateBarangMasuk() {
            ofstream file(filemasuk, ios::trunc);
            if(!file) {
                cerr << "Error: Cannot update data to file barang masuk." << endl;
                return;
            }

            for(const auto& dMasuk: masuk) {
                string tempNamaBarang = dMasuk.namaBarang;
                string tempNamaSupplier = dMasuk.namaSupplier;
                replace(tempNamaBarang.begin(), tempNamaBarang.end(), ' ', '_');
                replace(tempNamaSupplier.begin(), tempNamaSupplier.end(), ' ', '_');
                file << dMasuk.id << " " << dMasuk.tanggal << " " << dMasuk.kodeBarang << " " << tempNamaBarang << " " << dMasuk.jumlahBarang 
                << " " << dMasuk.hargaSupplier << " " << dMasuk.hargaJual << " " << tempNamaSupplier << " " << dMasuk.tanggalUpdate << endl;
            }
            file.close();
        }
        
        // function update data barang setelah menginputkan barang masuk
        void updateDataBarang() {
            ofstream file(filebarang, ios::trunc);
            if(!file) {
                cerr << "Error: Cannot update data to file data barang." << endl;
                return;
            }
            
            for(const auto& dBarang: barang) {
                string tempNamaBarang = dBarang.namaBarang;
                replace(tempNamaBarang.begin(), tempNamaBarang.end(), ' ', '_');
                file << dBarang.kodeBarang << " " << tempNamaBarang << " " << dBarang.jumlahBarang <<  " " << dBarang.hargaBarang << endl;
            }
            file.close();
        }

        // function update data barang keluar setelah transaksi
        void updateBarangKeluar() {
            ofstream file(filekeluar, ios::trunc);
            if(!file) {
                cerr << "Error: Cannot update data to file barang keluar." << endl;
                return;
            }

            for(const auto& dKeluar: keluar) {
                string tempNamaBarang = dKeluar.namaBarang;
                replace(tempNamaBarang.begin(), tempNamaBarang.end(), ' ', '_');
                file << dKeluar.id << " " << dKeluar.tanggal << " " << dKeluar.kodeBarang << " " << tempNamaBarang << " " << dKeluar.jumlahBarang << dKeluar.hargaBarang;
            }
            file.close();
        }

        // function update data return to file
        void updateDataReturn() {
            ofstream file(filereturn, ios::trunc);
            if(!file) {
                cerr << "Error: Cannot update data to file return." << endl;
                return;
            }

            for(const auto& dReturn: returnD) {
                string tempNamaBarang = dReturn.namaBarang;
                replace(tempNamaBarang.begin(), tempNamaBarang.end(), ' ', '_');
                file << dReturn.id << " " << dReturn.tanggal_keluar << " " << dReturn.kodeBarang << " " << tempNamaBarang << " " << dReturn.jumlahBarang 
                << " " << dReturn.hargaBarang << " " << dReturn.tanggal_return << endl;
            }
            file.close();
        }

        // function update data presensi to file
        void updatePresensi() {
            ofstream file(fileattend, ios::trunc);
            if(!file) {
                cerr << "Error: Cannot update data to file attend." << endl;
                return;
            }

            for(const auto& dPresensi: presensi) {
                string tempNama = dPresensi.nama;
                replace(tempNama.begin(), tempNama.end(), ' ', '_');
                file << tempNama << " " << dPresensi.role << " " << dPresensi.tanggal << " " << dPresensi.masuk << " " << dPresensi.keluar << endl;
            }
            file.close();
        }

        // function save data barang masuk
        void saveBarangMasuk(const dataMasuk& dMasuk) {
            ofstream file(filemasuk, ios::app);
            if(!file) {
                cerr << "Error: Unable save data to file barang masuk." << endl;
                return;
            }
            string tempNamaBarang = dMasuk.namaBarang;
            string tempNamaSuplier = dMasuk.namaSupplier;

            replace(tempNamaBarang.begin(), tempNamaBarang.end(), ' ', '_');
            replace(tempNamaSuplier.begin(), tempNamaSuplier.end(), ' ', '_');
            file << dMasuk.id << " " << dMasuk.tanggal << " " << dMasuk.kodeBarang << " " << tempNamaBarang << " " << dMasuk.jumlahBarang 
            << " " << dMasuk.hargaSupplier << " " << dMasuk.hargaJual << " " << tempNamaSuplier << " " << dMasuk.tanggalUpdate << endl;
            file.close();
        }

        // function save data barang
        void saveDataBarang(const dataBarang& dBarang) {
            ofstream file(filebarang, ios::app);
            if(!file) {
                cerr << "Error: Unable save data to file data barang." << endl;
                return;
            }
            string tempNamaBarang = dBarang.namaBarang;

            replace(tempNamaBarang.begin(), tempNamaBarang.end(), ' ', '_');
            file << dBarang.kodeBarang << " " << tempNamaBarang << " " << dBarang.jumlahBarang << " "  << dBarang.hargaBarang << endl;
            file.close();
        }

        // function save barang keluar
        void saveBarangKeluar(const dataKeluar& dKeluar) {
            ofstream file(filekeluar, ios::app);
            if(!file) {
                cerr << "Error: Unable save data to file barang keluar." << endl;
                return;
            }
            string tempNamaBarang = dKeluar.namaBarang;
            replace(tempNamaBarang.begin(), tempNamaBarang.end(), ' ', '_');
            file << dKeluar.id << " " << dKeluar.tanggal << " " << dKeluar.kodeBarang << " " << tempNamaBarang << " " << dKeluar.jumlahBarang << " " << dKeluar.hargaBarang << endl;
            file.close();
        }

        // function save data return
        void saveDataReturn(const dataReturn& dReturn) {
            ofstream file(filereturn, ios::app);
            if(!file) {
                cerr << "Error: Unable save data to file return." << endl;
                return;
            }
            string tempNamaBarang = dReturn.namaBarang;
            replace(tempNamaBarang.begin(), tempNamaBarang.end(), ' ', '_');
            file << dReturn.id << " " << dReturn.tanggal_keluar << " " << dReturn.kodeBarang << " " << tempNamaBarang << " " << dReturn.jumlahBarang 
            << " " << dReturn.hargaBarang << " " << dReturn.tanggal_return << endl;
            file.close(); 
        }

        // function to save data presensi
        void savePresensi(const Presensi& dPresensi) {
            ofstream file(fileattend, ios::app);
            if(!file) {
                cerr <<  "Error: Unable save data to file attend." << endl;
                return;
            }
            string tempNama = dPresensi.nama;
            replace(tempNama.begin(), tempNama.end(), ' ', '_');
            file << tempNama << " " << dPresensi.role << " " << dPresensi.tanggal << " " << dPresensi.masuk << " " << dPresensi.keluar << endl;
            file.close();
        }

        // function get date
        string getDate() {
            time_t now = time(0);
            tm *localTime = localtime(&now);
            if(!localTime) {
                cerr << "Error: Unable to get local date." << endl;
                return "";
            }

            stringstream ssDate;
            ssDate << put_time(localTime, "%d-%m-%Y");
            return ssDate.str();
        }
        
        // function get time
        string getTime() {
            time_t now = time(0);
            tm *localTime = localtime(&now);
            stringstream ssTime;
            if(!localTime) {
                cerr << "Error: Unable to get local time." << endl;
                return "";
            }

            ssTime << put_time(localTime, "%H:%M:%S");
            return ssTime.str();
        }

        // function to format ribuan
        string formatRibuan(int angka) {
            stringstream ss;
            string hasil;
            ss << angka;
            string angkaStr = ss.str();
            int len = angkaStr.length();

            for(int i=0; i<len; i++) {
                hasil += angkaStr[i];
                if((len - i - 1) % 3 == 0 && i != len - 1) {
                    hasil += ".";
                }
            }
            return hasil;
        }

        // function to convert time to second
        int timeToSeconds(const string& time) {
            int hours, minutes, seconds;
            char sep;
            
            istringstream iss(time);
            iss >> hours >> sep >> minutes >> sep >> seconds;
            return hours * 3600 + minutes * 60 + seconds;
        }

        // function to calculate range hour first attend and second attend
        double calculateHours(const string& masuk, const string& keluar) {
            int masukSeconds = timeToSeconds(masuk);
            int keluarSeconds = timeToSeconds(keluar);
            return (keluarSeconds - masukSeconds) / 3600.0; // Convert seconds to hours
        } 

    public:

        // function input data barang masuk
        void inputBarangMasuk(const string& kode, const string& namaBarang, const int jumlahBarang, const int hargaSupplier, const int hargaJual, const string& namaSupplier) {
            dataMasuk newBarangMasuk;
            dataBarang newDataBarang;

            int index = findMasukIndex(kode);
            int indexBarang = findBarangIndex(kode);

            int masuk_id = 1;
            if(!masuk.empty()) {
                masuk_id = masuk.back().id + 1;
            }
            
            string tanggal_update = "-";
            const string& currentDate = getDate();
            newBarangMasuk = {masuk_id, currentDate, kode, namaBarang, jumlahBarang, hargaSupplier, hargaJual, namaSupplier, tanggal_update};
            saveBarangMasuk(newBarangMasuk);
                
            if(indexBarang != -1) {
                barang[indexBarang].jumlahBarang += jumlahBarang;
                barang[indexBarang].hargaBarang = hargaJual;
                updateDataBarang();
            } else {
                newDataBarang = {kode, namaBarang, jumlahBarang, hargaJual};
                saveDataBarang(newDataBarang);
            }
            
            cout << "\nData barang masuk berhasil diinputkan." << endl;
        }

        void showBarangMasuk() {
            loadBarangMasuk();
            if(masuk.empty()) {
                cout << "No data barang found in file barang masuk!" << endl;
            } else {
                cout << "List Data Barang : " << endl;
                for(size_t i=0; i<masuk.size(); i++) {
                    cout << "Data ID        : " << masuk[i].id << endl;
                    cout << "Tanggal Masuk  : " << masuk[i].tanggal << endl;
                    cout << "Kode Barang    : " << masuk[i].kodeBarang << endl;
                    cout << "Nama Barang    : " << masuk[i].namaBarang << endl;
                    cout << "Jumlah Barang  : " << masuk[i].jumlahBarang << endl;
                    cout << "Harga Supplier : Rp. " << formatRibuan(masuk[i].hargaSupplier) << endl;
                    cout << "Harga Jual     : Rp. " << formatRibuan(masuk[i].hargaJual) << endl;
                    cout << "Nama Supplier  : " << masuk[i].namaSupplier << endl << endl;
                }
            }
        }

        // Function to update data barang masuk
        void updateDataBarangMasuk(const string& kode) {
            loadBarangMasuk();
            loadDataBarang();
            vector<int> matchingIndex;

            // filter data by code barang
            for(size_t i=0; i<masuk.size(); i++) {
                if(masuk[i].kodeBarang == kode) {
                    matchingIndex.push_back(i);
                    cout << "Data ID        : " << masuk[i].id << endl;
                    cout << "Tanggal Masuk  : " << masuk[i].tanggal << endl;
                    cout << "Kode Barang    : " << masuk[i].kodeBarang << endl;
                    cout << "Nama Barang    : " << masuk[i].namaBarang << endl;
                    cout << "Jumlah Barang  : " << masuk[i].jumlahBarang << endl;
                    cout << "Harga Supplier : Rp. " << formatRibuan(masuk[i].hargaSupplier) << endl;
                    cout << "Harga Jual     : Rp. " << formatRibuan(masuk[i].hargaJual) << endl;
                    cout << "Nama Supplier  : " << masuk[i].namaSupplier << endl << endl;
                }
            }

            if(matchingIndex.empty()) {
                cout << "Data barang dengan kode " << kode << " tidak ditemukan." << endl;
                return;
            }

            int nomor;
            cout << "\nMasukkan nomor data yang akan diubah : ";
            cin >> nomor;
            cin.ignore();

            auto it = find_if(matchingIndex.begin(), matchingIndex.end(), [&](int idx) { return masuk[idx].id == nomor;});

            if(it != matchingIndex.end()) {
                int indexBarang = findBarangIndex(kode);
                dataBarang newDataBarang;

                int indexNomor = *it;
                string& kodeBarang = masuk[indexNomor].kodeBarang;
                string& nama = masuk[indexNomor].namaBarang;
                int& jumlah = masuk[indexNomor].jumlahBarang;
                int& hargaSup = masuk[indexNomor].hargaSupplier;
                int& hargaJual = masuk[indexNomor].hargaJual;
                string& namaSup = masuk[indexNomor].namaSupplier;
                string& tanggalUpdate = masuk[indexNomor].tanggalUpdate;

                cout << "\nMasukkan data baru atau '-' untuk tidak mengubah : " << endl;
                cout << "Jika data yang dimasukkan angka masukkan angka saja." << endl;

                string kodeBaru;
                cout << "Masukkan kode barang : ";
                getline(cin, kodeBaru);
                if(kodeBaru != "-") {
                    kodeBarang = kodeBaru;
                }
                
                string namaBaru;
                cout << "Masukkan nama barang : ";
                getline(cin, namaBaru);
                if(namaBaru != "-") {
                    nama = namaBaru;
                }

                string jumlahBaru;
                int selisih;
                cout << "Masukkan jumlah barang : ";
                getline(cin, jumlahBaru);
                if(jumlahBaru != "-") {
                    try {
                        int newJumlah = stoi(jumlahBaru);
                        if(newJumlah > jumlah) {
                            selisih = newJumlah - jumlah;
                        } else if(newJumlah < jumlah) {
                            selisih = jumlah - newJumlah;
                        }
                        jumlah = newJumlah;
                    } catch(...) {
                        cout << "Input jumlah tidak valid, tidak ada perubahan." << endl;
                    }
                }

                string hargaSuplierBaru;
                cout << "Masukkan harga dari supplier : ";
                getline(cin, hargaSuplierBaru);
                if(hargaSuplierBaru != "-") {
                    try {
                        hargaSup = stoi(hargaSuplierBaru);
                    } catch(...) {
                        cout << "Input harga supplier tidak valid, tidak ada perubahan." << endl;
                    }
                }

                string hargaJualBaru;
                cout << "Masukkan harga jual : ";
                getline(cin, hargaJualBaru);
                if(hargaJualBaru != "-") {
                    try {
                        hargaJual = stoi(hargaJualBaru);
                    } catch(...) {
                        cout << "Input harga jual tidak valid, tidak ada perubahan." << endl;
                    }
                }

                string namaSuplierBaru;
                cout << "Masukkan nama supplier : ";
                getline(cin, namaSuplierBaru);
                if(namaSuplierBaru != "-") {
                    namaSup = namaSuplierBaru;
                }

                tanggalUpdate = getDate();

                // update data barang
                barang[indexBarang].jumlahBarang -= selisih;
                barang[indexBarang].hargaBarang = hargaJual;
                updateDataBarang();

                updateBarangMasuk();
                cout << "\nData berhasil diperbaharui!" << endl;
            } else {
                cout << "\nNomor yang dimasukkan tidak sesuai dengan data yang tersedia." << endl;
            }
        }

        // Function to delete data barang masuk
        void deleteDataBarangMasuk(const string& kode) {
            loadBarangMasuk();
            vector<int> matchingIndex;

            // filter data by code barang
            for(size_t i=0; i<masuk.size(); i++) {
                if(masuk[i].kodeBarang == kode) {
                    matchingIndex.push_back(i);
                    cout << "Data ID        : " << masuk[i].id << endl;
                    cout << "Tanggal Masuk  : " << masuk[i].tanggal << endl;
                    cout << "Kode Barang    : " << masuk[i].kodeBarang << endl;
                    cout << "Nama Barang    : " << masuk[i].namaBarang << endl;
                    cout << "Jumlah Barang  : " << masuk[i].jumlahBarang << endl;
                    cout << "Harga Supplier : Rp. " << formatRibuan(masuk[i].hargaSupplier) << endl;
                    cout << "Harga Jual     : Rp. " << formatRibuan(masuk[i].hargaJual) << endl;
                    cout << "Nama Supplier  : " << masuk[i].namaSupplier << endl << endl;
                }
            }

            if(matchingIndex.empty()) {
                cout << "Data barang dengan kode " << kode << " tidak ditemukan." << endl;
                return;
            }

            int nomor;
            cout << "\nMasukkan nomor data yang akan diubah : ";
            cin >> nomor;
            cin.ignore();

            auto it = find_if(matchingIndex.begin(), matchingIndex.end(), [&](int idx) { return masuk[idx].id == nomor;});

            if(it != matchingIndex.end()) {
                int index = findMasukIndexById(nomor);
                int indexBarang = findBarangIndex(kode);

                // // delete data barang return from vector dataReturn
                masuk.erase(masuk.begin() + index);
                barang[indexBarang].jumlahBarang -= masuk[index].jumlahBarang;
                cout << "Data masuk dengan id \"" << nomor << "\" dan kode " << kode << " berhasil dihapus.\n";

                // update data barang return in file
                updateBarangMasuk();
                updateDataBarang();
            }
        }

        // function transaction barang
        void transactionBarang() {
            loadDataBarang();
            loadBarangKeluar();
            dataKeluar newBarangKeluar;
            vector<Barang> keranjang;
            string kodeBarang;
            char pilihan;

            cout << "=== Menu Transaksi Barang ===\n";

            do {
                cout << "Masukkan kode barang yang akan dibeli (format: A1001): ";
                getline(cin, kodeBarang);

                // Validate kodeBarang format
                if (kodeBarang.empty() || !regex_match(kodeBarang, regex("^[A-Za-z][0-9]+$"))) {
                    cout << "Kode barang tidak valid. Harap masukkan kode barang dalam format huruf dan angka.\n";
                    continue;
                }

                int indexBarang = findBarangIndex(kodeBarang);
                if (indexBarang == -1) {
                    cout << "Barang dengan kode tersebut tidak ditemukan.\n";
                    continue;
                }

                const auto& barangData = barang[indexBarang];
                cout << "Nama Barang : " << barangData.namaBarang << endl;
                cout << "Jumlah Barang Tersisa : " << barangData.jumlahBarang << endl;
                cout << "Harga Satuan Barang : Rp. " << formatRibuan(barangData.hargaBarang) << endl;

                int jumlah;
                cout << "Masukkan jumlah barang yang akan dibeli: ";
                cin >> jumlah;

                if (jumlah > barangData.jumlahBarang || jumlah <= 0) {
                    cout << "Jumlah barang tidak valid.\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                // Add to keranjang
                keranjang.push_back({barangData.kodeBarang, barangData.namaBarang, jumlah, barangData.hargaBarang});
                barang[indexBarang].jumlahBarang -= jumlah;
                updateDataBarang();
                
                int keluar_id = 1;
                if(!keluar.empty()) {
                    keluar_id = keluar.back().id + 1;
                }

                string tanggal = getDate();
                newBarangKeluar = {keluar_id, tanggal, kodeBarang, barangData.namaBarang, jumlah, barangData.hargaBarang};
                saveBarangKeluar(newBarangKeluar);

                cout << "Apakah masih ada barang yang ingin dibeli [y/n]: ";
                cin >> pilihan;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            } while (tolower(pilihan) == 'y');

            // Calculate total price
            int totalHarga = 0;
            for (const auto& item : keranjang) {
                totalHarga += item.jumlah * item.harga;
            }

            // Input payment
            int pembayaran;
            cout << "\nTotal harga : Rp. " << fixed << setprecision(2) << formatRibuan(totalHarga) << endl;
            do {
                cout << "Masukkan jumlah pembayaran : Rp. ";
                cin >> pembayaran;
                if (pembayaran < totalHarga) {
                    cout << "Jumlah pembayaran kurang! Harap masukkan jumlah yang mencukupi.\n";
                }
            } while (pembayaran < totalHarga);

            int kembalian = pembayaran - totalHarga;

            // Print receipt
            system("cls");
            cout << "\n+=============================================+\n";
            cout << "|              TOKO BERKAH JAYA               |\n";
            cout << "|             Jl. Kenangan No.820             |\n";
            cout << "+=============================================+\n";
            cout << "| Tanggal transaksi : " << getDate() << "              |\n";
            cout << "+=============================================+\n";
            cout << "| Barang          Qty    Harga      Subtotal  |\n";
            cout << "+=============================================+\n";

            for (const auto& item : keranjang) {
                int subtotal = item.jumlah * item.harga;

                 // Nama barang akan ditampilkan dengan lebar tetap
                string namaBarang = item.namaBarang.length() > 12 
                                    ? item.namaBarang.substr(0, 12) + "..." 
                                    : item.namaBarang;
                
                cout << "| " << setw(12) << left << item.namaBarang
                    << setw(5) << right << item.jumlah
                    << setw(10) << right << item.harga
                    << setw(12) << right << subtotal
                    << "     |\n";
            }

            cout << "+---------------------------------------------+\n";
            cout << "|                  Total: Rp." << setw(12) << fixed << setprecision(2) << setw(8) << formatRibuan(totalHarga) << "         |\n";
            cout << "|             Pembayaran: Rp." << setw(12) << fixed << setprecision(2) << setw(8) << formatRibuan(pembayaran) << "         |\n";
            cout << "|                Kembali: Rp." << setw(12) << fixed << setprecision(2) << setw(8) << formatRibuan(kembalian) << "         |\n";
            cout << "+=============================================+\n";
            cout << "|      Terima Kasih Atas Kunjungan Anda!      |\n";
            cout << "+=============================================+\n";
        }

        // function show barang keluar
        void showBarangKeluar() {
            loadBarangKeluar();
            if(keluar.empty()) {
                cout << "No data barang found in file barang keluar!" << endl;
            } else {
                cout << "List Data Barang : " << endl;
                for(size_t i=0; i<keluar.size(); i++) {
                    cout << "ID             : " << keluar[i].id << endl;
                    cout << "Tanggal Keluar : " << keluar[i].tanggal << endl;
                    cout << "Kode Barang    : " << keluar[i].kodeBarang << endl;
                    cout << "Nama Barang    : " << keluar[i].namaBarang << endl;
                    cout << "Jumlah Barang  : " << keluar[i].jumlahBarang << endl;
                    cout << "Harga Barang   : Rp. " << formatRibuan(keluar[i].hargaBarang) << endl << endl;
                }
            }
        }

        // function input barang return
        void inputBarangReturn(const string& kode, const string& tanggal) {
            loadBarangKeluar();
            vector<int> matchingIndex;
            
            // filter data by code barang dan tanggal
            for(size_t i=0; i<keluar.size(); i++) {
                if(keluar[i].kodeBarang == kode && keluar[i].tanggal == tanggal) {
                    matchingIndex.push_back(i);
                    cout << "Keluar_ID      : " << keluar[i].id << endl;
                    cout << "Tanggal keluar : " << keluar[i].tanggal << endl;
                    cout << "Kode barang    : " << keluar[i].kodeBarang << endl;
                    cout << "Nama barang    : " << keluar[i].namaBarang << endl;
                    cout << "Jumlah barang  : " << keluar[i].jumlahBarang << endl;
                    cout << "Harga barang   : Rp. " << formatRibuan(keluar[i].hargaBarang) << endl << endl;
                }
            }

            if(matchingIndex.empty()) {
                cout << "Data barang dengan kode " << kode << " pada tanggal " << tanggal << " tidak ditemukan.\n";
                return;
            }

            int nomor;
            cout << "\nMasukkan id nomor yang akan digunakan : ";
            cin >> nomor; 

            auto it = find_if(matchingIndex.begin(), matchingIndex.end(), [&](int idx) { return keluar[idx].id == nomor;});

            if(it != matchingIndex.end()) {
                int index = findKeluarIndex(kode, tanggal);
                dataReturn newDataReturn;
                
                string& tanggal_keluar = keluar[index].tanggal;
                string& kodeBarang = keluar[index].kodeBarang;
                string& namaBarang = keluar[index].namaBarang;
                int& hargaBarang = keluar[index].hargaBarang;

                int return_id = 1;
                if(!returnD.empty()) {
                    return_id = returnD.back().id + 1;
                }
                
                // jumlahBarang retur
                int newJumlah;
                cout << "Masukkan jumlah barang retur : ";
                cin >> newJumlah;

                const string& tanggal_return = getDate();
                newDataReturn = {return_id, tanggal_keluar, kodeBarang, namaBarang, newJumlah, hargaBarang, tanggal_return};
                saveDataReturn(newDataReturn);

                cout << "\nData barang retur berhasil diinputkan.\n";
            }

        }

        // function to show from update barang return
        void updateBarangReturn(const string& kode) {
            loadDataReturn();
            vector<int> matchingIndex;
            
            // filter data return by kode barang
            for(size_t i=0; i<returnD.size(); i++) {
                if(returnD[i].kodeBarang == kode) {
                    matchingIndex.push_back(i);
                    cout << "Data id        : " << returnD[i].id << endl;
                    cout << "Tanggal keluar : " << returnD[i].tanggal_keluar << endl;
                    cout << "Kode barang    : " << returnD[i].kodeBarang << endl;
                    cout << "Nama barang    : " << returnD[i].namaBarang << endl;
                    cout << "Jumlah barang  : " << returnD[i].jumlahBarang << endl;
                    cout << "Harga barang   : Rp. " << formatRibuan(returnD[i].hargaBarang) << endl;
                    cout << "Tanggal return : " << returnD[i].tanggal_return << endl << endl;
                }
            }

            if(matchingIndex.empty()) {
                cout << "Data barang retur dengan kode " << kode << " tidak ditemukan.\n";
                return;
            }

            int nomor; 
            cout << "Masukkan nomor ID yang akan diubah : ";
            cin >> nomor;
            cin.ignore();

            auto it = find_if(matchingIndex.begin(), matchingIndex.end(), [&](int idx) { return masuk[idx].id == nomor;});

            if(it != matchingIndex.end()) {
                int index = findReturnIndex(kode);

                int indexNomor = *it;
                string& tanggal_keluar = returnD[index].tanggal_keluar;
                string& kode = returnD[index].kodeBarang;
                string& nama = returnD[index].namaBarang;
                int& jumlah = returnD[index].jumlahBarang;
                int& harga = returnD[index].hargaBarang;
                string& tanggal_return = returnD[index].tanggal_return;
                

                cout << "\nMasukkan data baru atau '-' untuk tidak mengubah : " << endl;

                string kodeBaru;
                cout << "Kode barang : ";
                getline(cin, kodeBaru);
                if(kodeBaru != "-") {
                    kode = kodeBaru;
                }

                string namaBaru;
                cout << "Nama barang : ";
                getline(cin, namaBaru);
                if(namaBaru != "-") {
                    nama = namaBaru;
                }

                string jumlahBaru;
                cout << "Jumlah barang : ";
                getline(cin, jumlahBaru);
                if(jumlahBaru != "-") {
                    try {
                        jumlah = stoi(jumlahBaru);
                    } catch(...) {
                        cout << "Input jumlah tidak valid, tidak ada perubahan" << endl;
                    }
                }

                string hargaBaru;
                cout << "Harga barang : ";
                getline(cin, hargaBaru);
                if(hargaBaru != "-") {
                    try {
                        harga = stoi(hargaBaru);
                    } catch(...) {
                        cout << "Input harga tidak valid, tidak ada perubahan" << endl;
                    }
                }
                
                string tanggalK_baru;
                cout << "Tangggal keluar : ";
                getline(cin, tanggalK_baru);
                if(tanggalK_baru != "-") {
                    tanggal_keluar = tanggalK_baru;
                }

                string tanggalR_baru;
                cout << "Tangggal return : ";
                getline(cin, tanggalR_baru);
                if(tanggalR_baru != "-") {
                    tanggal_return = tanggalR_baru;
                }

                updateDataReturn();
                cout << "\nData berhasil diperbaharui!" << endl;
            }
        }

        // Function show barang return
        void showBarangReturn() {
            loadDataReturn();
            if(returnD.empty()) {
                cout << "No data barang found in file barang return!" << endl;
            } else {
                cout << "List Data Barang Return : " << endl;
                for(size_t i=0; i<returnD.size(); i++) {
                    cout << "Data id        : " << returnD[i].id << endl;
                    cout << "Tanggal keluar : " << returnD[i].tanggal_keluar << endl;
                    cout << "Kode barang    : " << returnD[i].kodeBarang << endl;
                    cout << "Nama barang    : " << returnD[i].namaBarang << endl;
                    cout << "Jumlah barang  : " << returnD[i].jumlahBarang << endl;
                    cout << "Harga barang   : " << returnD[i].hargaBarang << endl;
                    cout << "Tanggal return : " << returnD[i].tanggal_return << endl << endl;
                }
            }
        }

        // Function delete barang return
        void deleteBarangReturn(const string& kode) {
            loadDataReturn();
            vector<int> matchingIndex;

            // filter data return by kode barang
            for(size_t i=0; i<returnD.size(); i++) {
                if(returnD[i].kodeBarang == kode) {
                    matchingIndex.push_back(i);
                    cout << "Data id        : " << returnD[i].id << endl;
                    cout << "Tanggal keluar : " << returnD[i].tanggal_keluar << endl;
                    cout << "Kode barang    : " << returnD[i].kodeBarang << endl;
                    cout << "Nama barang    : " << returnD[i].namaBarang << endl;
                    cout << "Jumlah barang  : " << returnD[i].jumlahBarang << endl;
                    cout << "Harga barang   : " << returnD[i].hargaBarang << endl;
                    cout << "Tanggal return : " << returnD[i].tanggal_return << endl << endl;
                }
            }

            if(matchingIndex.empty()) {
                cout << "Data barang retur dengan kode " << kode << " tidak ditemukan.\n";
                return;
            }

            int nomor; 
            cout << "Masukkan nomor ID yang akan diubah : ";
            cin >> nomor;
            cin.ignore();

            auto it = find_if(matchingIndex.begin(), matchingIndex.end(), [&](int idx) { return masuk[idx].id == nomor;});

            if(it != matchingIndex.end()) {
                int index = findReturnIndexById(nomor);

                // delete data barang return from vector dataReturn
                returnD.erase(returnD.begin() + index);
                cout << "Data return dengan id \"" << nomor << "\" dan kode " << kode << " berhasil dihapus.\n";

                // update data barang return in file
                updateDataReturn();
            }
        }

        // Fungsi untuk melakukan rekap pengeluaran per bulan
        void rekapPengeluaranBulanan() {
            loadBarangMasuk();
            // Map untuk menyimpan rekap berdasarkan bulan dan kode barang
            unordered_map<string, unordered_map<string, pair<string, tuple<int, int, int>>>> rekap;

            // Proses rekap
            for (const auto& item : masuk) {
                // Ambil bulan dan tahun dari tanggal
                string bulanTahun = item.tanggal.substr(3, 7);
                // Tambahkan pendapatan, jumlah barang, dan harga supplier ke rekap sesuai bulan dan kode barang
                rekap[bulanTahun][item.kodeBarang].first = item.namaBarang;
                get<0>(rekap[bulanTahun][item.kodeBarang].second) += item.jumlahBarang;
                get<1>(rekap[bulanTahun][item.kodeBarang].second) = item.hargaSupplier;
                get<2>(rekap[bulanTahun][item.kodeBarang].second) += item.jumlahBarang * item.hargaSupplier;
            }

            // Tampilkan tabel berdasarkan bulan
            for (const auto& bulan : rekap) {
                cout << "\nPengeluaran Bulanan: " << bulan.first << endl;
                cout << "+-------------+----------------------+-------------------+------------+-------------------+" << endl;
                cout << "| Kode Barang | Nama Barang          | Jumlah Barang     | Harga      | Total Pengeluaran |" << endl;
                cout << "+-------------+----------------------+-------------------+------------+-------------------+" << endl;

                int totalPendapatanBulan = 0;

                for (const auto& barang : bulan.second) {
                    const string& kodeBarang = barang.first;
                    const string& namaBarang = barang.second.first;
                    int jumlahBarang = get<0>(barang.second.second);
                    int hargaBarang = get<1>(barang.second.second);
                    int totalPendapatan = get<2>(barang.second.second);

                    cout << "| " << setw(11) << left << kodeBarang
                    << " | " << setw(20) << left << namaBarang
                    << " | " << setw(17) << left << jumlahBarang
                    << " | " << setw(5) << left << "Rp. " << formatRibuan(hargaBarang)
                    << " | " << setw(17) << left << "Rp. " + formatRibuan(totalPendapatan) << " |" << endl;

                    totalPendapatanBulan += totalPendapatan;
                }

                cout << "+-------------+----------------------+-------------------+------------+-------------------+" << endl;
                cout << "| " << setw(11) << left << "TOTAL"
                << " | " << setw(20) << left << " "
                << " | " << setw(17) << left << " "
                << " | " << setw(10) << left << " "
                << " | " << setw(17) << left << "Rp. " + formatRibuan(totalPendapatanBulan) << " |" << endl;
                cout << "+-------------+----------------------+-------------------+------------+-------------------+" << endl;
            }
        }

        // Fungsi untuk melakukan rekap pendapatan per bulan
        void rekapPendapatanBulanan() {
            loadBarangKeluar();
            // Map untuk menyimpan rekap berdasarkan bulan dan kode barang
            unordered_map<string, unordered_map<string, pair<string, tuple<int, int, int>>>> rekap;

            // Proses rekap
            for (const auto& item : keluar) {
                // Ambil bulan dan tahun dari tanggal
                string bulanTahun = item.tanggal.substr(3, 7);
                // Tambahkan pendapatan, jumlah barang, dan harga barang ke rekap sesuai bulan dan kode barang
                rekap[bulanTahun][item.kodeBarang].first = item.namaBarang;
                get<0>(rekap[bulanTahun][item.kodeBarang].second) += item.jumlahBarang;
                get<1>(rekap[bulanTahun][item.kodeBarang].second) = item.hargaBarang;
                get<2>(rekap[bulanTahun][item.kodeBarang].second) += item.jumlahBarang * item.hargaBarang;
            }

            // Tampilkan tabel berdasarkan bulan
            for (const auto& bulan : rekap) {
                cout << "\nPendapatan Bulanan: " << bulan.first << endl;
                cout << "+-------------+----------------------+-------------------+------------+-------------------+" << endl;
                cout << "| Kode Barang | Nama Barang          | Jumlah Barang     | Harga      | Total Pengeluaran |" << endl;
                cout << "+-------------+----------------------+-------------------+------------+-------------------+" << endl;

                int totalPendapatanBulan = 0;

                for (const auto& barang : bulan.second) {
                    const string& kodeBarang = barang.first;
                    const string& namaBarang = barang.second.first;
                    int jumlahBarang = get<0>(barang.second.second);
                    int hargaBarang = get<1>(barang.second.second);
                    int totalPendapatan = get<2>(barang.second.second);

                    cout << "| " << setw(11) << left << kodeBarang
                    << " | " << setw(20) << left << namaBarang
                    << " | " << setw(17) << left << jumlahBarang
                    << " | " << setw(5) << left << "Rp. " << formatRibuan(hargaBarang)
                    << " | " << setw(17) << left << "Rp. " + formatRibuan(totalPendapatan) << " |" << endl;

                    totalPendapatanBulan += totalPendapatan;
                }

                cout << "+-------------+----------------------+-------------------+------------+-------------------+" << endl;
                cout << "| " << setw(11) << left << "TOTAL"
                << " | " << setw(20) << left << " "
                << " | " << setw(17) << left << " "
                << " | " << setw(10) << left << " "
                << " | " << setw(17) << left << "Rp. " + formatRibuan(totalPendapatanBulan) << " |" << endl;
                cout << "+-------------+----------------------+-------------------+------------+-------------------+" << endl;
            }
        }

        void catatPresensi(const string& nama, const string& role) {
            char option;
            string tanggal = getDate();
            string masuk = getTime(); 
            string keluar = masuk;

            Presensi dataPresensi;
            
            while(true) {
                cout << "=== Menu Presensi Pekerja ===" << endl;
                cout << "1. Presensi Masuk" << endl;
                cout << "2. Presensi Keluar" << endl;
                cout << "Masukkan pilihan anda [1/2]: ";
                cin >> option;
                cin.ignore();
            
                int index = findPresensiIndex(nama, tanggal);

                switch(option) {
                    case '1':
                        if(index != -1) {
                            cout << "Data presensi masuk sudah ada." << endl;
                        } else {
                            dataPresensi.nama = nama;
                            dataPresensi.role = role;
                            dataPresensi.tanggal = tanggal;
                            dataPresensi.masuk = masuk;
                            dataPresensi.keluar = "belum";

                            savePresensi(dataPresensi);
                            cout << "Presensi masuk berhasil." << endl;
                        }
                        return;
                    case '2':
                        if(index != -1) {
                            presensi[index].keluar = keluar;
                            updatePresensi();
                            cout << "Presensi keluar berhasil." << endl;
                        } else {
                            cout << "Presensi masuk tidak ditemukan." << endl;
                        }
                        return;
                    default:
                        cout << "Pilihan anda salah, silahkan coba lagi" << endl;
                }
            }
        }
        
        // function to rekap total jam kerja pekerja per bulan
        void rekapPresensiBulanan() {
            loadPresensi();
            map<string, map<string, pair<string, double>>> jamKerjaPerBulan;

            for (const auto& entry : presensi) {
                string bulan = entry.tanggal.substr(3, 7); // Get month and year
                jamKerjaPerBulan[bulan][entry.nama].first = entry.role; // Set role or jabatan
                jamKerjaPerBulan[bulan][entry.nama].second += calculateHours(entry.masuk, entry.keluar);
            }

            for (const auto& [bulan, namaData] : jamKerjaPerBulan) {
                cout << "\nBulan: " << bulan << endl;
                cout << "+---------------+---------------+-----------+" << endl;
                cout << "| Nama          | Jabatan       | Jam Kerja |" << endl;
                cout << "+---------------+---------------+-----------+" << endl;

                for (const auto& [nama, info] : namaData) {
                    cout << "| " << left << setw(14) << nama
                    << "| " << setw(14) << info.first
                    << "| " << setw(9) << fixed << setprecision(2) << info.second << " |" << endl;
                }
                cout << "+---------------+---------------+-----------+" << endl;
            }
        }

};
