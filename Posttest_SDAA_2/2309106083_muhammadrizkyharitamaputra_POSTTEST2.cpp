#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <conio.h>
using namespace std;

struct Pengguna {
    string nama;
    string nim;
};

struct SepedaMotor {
    string nama;
    string jenis;
    int stok;
    double harga;
};

void tampilkanMenu() {
    cout << "\n=== M E N U ===" << endl;
    cout << "1. Registrasi" << endl;
    cout << "2. Login" << endl;
    cout << "3. Keluar" << endl;
}

bool registrasiPengguna(vector<Pengguna>& pengguna) {
    Pengguna user;
    cout << "Masukkan Nama: ";
    getline(cin, user.nama);
    cout << "Masukkan NIM: ";
    getline(cin, user.nim);
    pengguna.push_back(user);
    cout << "Registrasi berhasil." << endl;
    cout << "Tekan enter untuk melanjutkan...";
    getch();
    system("cls");
    return true;
}

bool cekLogin(const vector<Pengguna>& pengguna) {
    if (pengguna.empty()) {
        cout << "Belum ada pengguna terdaftar. Silakan registrasi terlebih dahulu." << endl;
        return false;
    } else {
        int percobaan = 0;
        while (percobaan < 3) {
            string nama, nim;
            cout << "Masukkan Nama: ";
            getline(cin, nama);
            cout << "Masukkan NIM: ";
            getline(cin, nim);

            for (const auto& user : pengguna) {
                if (user.nama == nama && user.nim == nim) {
                    cout << "Login berhasil." << endl;
                    cout << "Tekan enter untuk melanjutkan...";
                    getch();
                    system("cls");
                    return true;
                }
            }

            percobaan++;
            if (percobaan < 3)
                cout << "Login gagal. Anda memiliki " << 3 - percobaan << " percobaan lagi." << endl;
        }
        cout << "Anda telah salah login sebanyak 3 kali. Program berhenti." << endl;
        exit(1);
    }
}

void tampilkanMenuMotor() {
    cout << "\n=== M E N U M O T O R ===" << endl;
    cout << "1. Tambah Sepeda Motor" << endl;
    cout << "2. Lihat Daftar Sepeda Motor" << endl;
    cout << "3. Update Nama, Stok, dan Harga Sepeda Motor" << endl;
    cout << "4. Hapus Sepeda Motor" << endl;
    cout << "5. Keluar" << endl;
}

void tambahMotor(SepedaMotor* daftarMotor, int& jumlahMotor, const int MAX_MOTOR) {
    bool validInput = false;
    while (!validInput) {
        try {
            if (jumlahMotor < MAX_MOTOR) {
                cout << "Masukkan nama sepeda motor: ";
                cin.ignore();
                getline(cin, (daftarMotor + jumlahMotor)->nama);
                cout << "Masukkan jenis sepeda motor: ";
                getline(cin, (daftarMotor + jumlahMotor)->jenis);
                cout << "Masukkan stok sepeda motor: ";
                cin >> (daftarMotor + jumlahMotor)->stok;
                cout << "Masukkan harga sepeda motor: ";
                cin >> (daftarMotor + jumlahMotor)->harga;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                if (cin.fail()) {
                    cin.clear();
                    throw "Input stok atau harga tidak valid. Masukkan angka.";
                }
                jumlahMotor++;
                validInput = true;
            } else {
                throw "Daftar sepeda motor penuh!";
            }
        } catch (const char* errorMsg) {
            cerr << "Terjadi kesalahan: " << errorMsg << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void lihatDaftarMotor(const SepedaMotor* daftarMotor, const int jumlahMotor) {
    if (jumlahMotor > 0) {
        cout << "=== DAFTAR SEPEDA MOTOR ===" << endl;
        cout << "ID\tNama\tJenis\tStok\tHarga" << endl;
        for (int i = 0; i < jumlahMotor; i++) {
            cout << i + 1 << "\t";
            cout << (daftarMotor + i)->nama << "\t";
            cout << (daftarMotor + i)->jenis << "\t";
            cout << (daftarMotor + i)->stok << "\t";
            cout << (daftarMotor + i)->harga << endl;
        }
    } else {
        cout << "Daftar sepeda motor kosong!" << endl;
    }
}

void updateNamaStokDanHargaMotor(SepedaMotor* daftarMotor, const int jumlahMotor) {
    try {
        if (jumlahMotor > 0) {
            int indeks;
            cout << "Masukkan nomor sepeda motor yang ingin diupdate: ";
            cin >> indeks;
            if (cin.fail() || indeks < 1 || indeks > jumlahMotor) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                lihatDaftarMotor(daftarMotor, jumlahMotor);
                throw "Nomor sepeda motor tidak valid!";
            }
            cout << "Masukkan nama baru: ";
            cin.ignore();
            getline(cin, (daftarMotor + indeks - 1)->nama);
            cout << "Masukkan stok baru: ";
            cin >> (daftarMotor + indeks - 1)->stok;
            cout << "Masukkan harga baru: ";
            cin >> (daftarMotor + indeks - 1)->harga;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                throw "Input stok atau harga tidak valid. Masukkan angka.";
            }
            cout << "Informasi sepeda motor berhasil diperbarui." << endl;
        } else {
            throw "Daftar sepeda motor kosong!";
        }
    } catch (const char* errorMsg) {
        cerr << "Terjadi kesalahan: " << errorMsg << endl;
        if (jumlahMotor == 0)
            return;
        updateNamaStokDanHargaMotor(daftarMotor, jumlahMotor);
    }
}

void hapusMotor(SepedaMotor* daftarMotor, int& jumlahMotor) {
    bool motorDitambahkan = (jumlahMotor > 0);
    try {
        if (jumlahMotor > 0) {
            int indeks;
            cout << "Masukkan nomor sepeda motor yang ingin dihapus: ";
            cin >> indeks;
            if (cin.fail() || indeks < 1 || indeks > jumlahMotor) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                lihatDaftarMotor(daftarMotor, jumlahMotor);
                throw "Nomor sepeda motor tidak valid!";
            }
            for (int i = indeks - 1; i < jumlahMotor - 1; i++) {
                *(daftarMotor + i) = *(daftarMotor + i + 1);
            }
            jumlahMotor--;
            cout << "Sepeda motor berhasil dihapus." << endl;
        } else {
            throw "Daftar sepeda motor kosong!";
        }
    } catch (const char* errorMsg) {
        cerr << "Terjadi kesalahan: " << errorMsg << endl;
        if (!motorDitambahkan) {
            return;
        }
        hapusMotor(daftarMotor, jumlahMotor);
    }
}


int main() {
    const int MAX_MOTOR = 100;
    SepedaMotor daftarMotor[MAX_MOTOR];
    int jumlahMotor = 0;

    vector<Pengguna> pengguna;

    while (true) {
        tampilkanMenu();
        int pilihan;
        cout << "Pilihan: ";
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Input tidak valid. Silakan masukkan nomor pilihan." << endl;
            continue;
        }
        cin.ignore();
        system("cls");

        switch (pilihan) {
            case 1:
                registrasiPengguna(pengguna);
                break;
            case 2:
                if (cekLogin(pengguna)) {
                    system("cls");
                    while (true) {
                        tampilkanMenuMotor();
                        int pilihan;
                        cout << "Pilihan: ";
                        if (!(cin >> pilihan)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            system("cls");
                            cout << "Input tidak valid. Silakan masukkan nomor pilihan." << endl;
                            continue;
                        }

                        switch (pilihan) {
                            case 1:
                                system("cls");
                                tambahMotor(daftarMotor, jumlahMotor, MAX_MOTOR);
                                break;
                            case 2:
                                system("cls");
                                lihatDaftarMotor(daftarMotor, jumlahMotor);
                                break;
                            case 3:
                                system("cls");
                                lihatDaftarMotor(daftarMotor, jumlahMotor);
                                updateNamaStokDanHargaMotor(daftarMotor, jumlahMotor);
                                break;
                            case 4:
                                system("cls");
                                lihatDaftarMotor(daftarMotor, jumlahMotor);
                                hapusMotor(daftarMotor, jumlahMotor);
                                break;
                            case 5:
                                cout << "Keluar dari program, Terima kasih telah menggunakan program kami." << endl;
                                return 0;
                            default:
                                system("cls");
                                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                                break;
                        }
                    }
                }
                break;
            case 3:
                cout << "Keluar dari program, Terima kasih telah menggunakan program kami." << endl;
                return 0;
            default:
                system("cls");
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }
    }

    return 0;
}
