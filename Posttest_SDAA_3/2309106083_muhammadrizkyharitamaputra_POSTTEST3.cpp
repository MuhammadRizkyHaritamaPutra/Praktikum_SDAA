#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <conio.h>
#include <iomanip>  
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

struct Node {
    SepedaMotor motor;
    Node* next;
};


void tambahMotor(Node*& head) {
    Node* newNode = new Node;
    cout << "Masukkan nama sepeda motor: ";
    cin.ignore();
    getline(cin, newNode->motor.nama);
    cout << "Masukkan jenis sepeda motor: ";
    getline(cin, newNode->motor.jenis);
    cout << "Masukkan stok sepeda motor: ";
    cin >> newNode->motor.stok;
    cout << "Masukkan harga sepeda motor: ";
    cin >> newNode->motor.harga;
    newNode->next = nullptr;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        delete newNode;
        cerr << "Input stok atau harga tidak valid. Masukkan angka." << endl;
        return;
    }

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    system("cls");
    cout << "Sepeda motor berhasil ditambahkan." << endl;
}


void lihatDaftarMotor(Node* head) {
    if (head == nullptr) {
        cout << "Daftar sepeda motor kosong!" << endl;
        return;
    }

    Node* temp = head;
    cout << "=== DAFTAR SEPEDA MOTOR ===" << endl;

    cout << left << setw(5)  << "ID"
         << setw(20) << "Nama"
         << setw(15) << "Jenis"
         << setw(10) << "Stok"
         << setw(15) << "Harga" << endl;
    cout << "--------------------------------------------------------------" << endl;

    int id = 1;
    while (temp != nullptr) {
        cout << left << setw(5)  << id++
             << setw(20) << temp->motor.nama
             << setw(15) << temp->motor.jenis
             << setw(10) << temp->motor.stok
             << setw(15) << fixed << setprecision(2) << temp->motor.harga << endl;
        temp = temp->next;
    }
}


void updateNamaStokDanHargaMotor(Node* head) {
    if (head == nullptr) {
        cerr << "Daftar sepeda motor kosong!" << endl;
        return;
    }

    lihatDaftarMotor(head);

    int indeks;
    cout << "Masukkan nomor sepeda motor yang ingin diupdate: ";
    cin >> indeks;

    if (cin.fail() || indeks < 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Nomor sepeda motor tidak valid!" << endl;
        return;
    }

    Node* temp = head;
    for (int i = 1; i < indeks && temp != nullptr; i++) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cerr << "Nomor sepeda motor tidak ditemukan!" << endl;
        return;
    }

    cout << "Masukkan nama baru: ";
    cin.ignore();
    getline(cin, temp->motor.nama);
    cout << "Masukkan stok baru: ";
    cin >> temp->motor.stok;
    cout << "Masukkan harga baru: ";
    cin >> temp->motor.harga;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Input stok atau harga tidak valid." << endl;
    } else {
        cout << "Informasi sepeda motor berhasil diperbarui." << endl;
    }
}

void hapusMotor(Node*& head) {
    if (head == nullptr) {
        cerr << "Daftar sepeda motor kosong!" << endl;
        return;
    }

    lihatDaftarMotor(head);

    int indeks;
    cout << "Masukkan nomor sepeda motor yang ingin dihapus: ";
    cin >> indeks;

    if (cin.fail() || indeks < 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Nomor sepeda motor tidak valid!" << endl;
        return;
    }

    if (indeks == 1) {
        Node* temp = head;
        head = head->next;
        delete temp;
    } else {
        Node* temp = head;
        for (int i = 1; i < indeks - 1 && temp != nullptr; i++) {
            temp = temp->next;
        }

        if (temp == nullptr || temp->next == nullptr) {
            cerr << "Nomor sepeda motor tidak ditemukan!" << endl;
            return;
        }

        Node* delNode = temp->next;
        temp->next = delNode->next;
        delete delNode;
    }

    cout << "Sepeda motor berhasil dihapus." << endl;
}


void tampilkanMenuMotor() {
    cout << "\n=== M E N U M O T O R ===" << endl;
    cout << "1. Tambah Sepeda Motor" << endl;
    cout << "2. Lihat Daftar Sepeda Motor" << endl;
    cout << "3. Update Nama, Stok, dan Harga Sepeda Motor" << endl;
    cout << "4. Hapus Sepeda Motor" << endl;
    cout << "5. Keluar" << endl;
}


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

int main() {
    Node* daftarMotor = nullptr;
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
                        int pilihanMotor;
                        cout << "Pilihan: ";
                        if (!(cin >> pilihanMotor)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            system("cls");
                            cout << "Input tidak valid. Silakan masukkan nomor pilihan." << endl;
                            continue;
                        }

                        switch (pilihanMotor) {
                            case 1:
                                system("cls");
                                tambahMotor(daftarMotor);
                                break;
                            case 2:
                                system("cls");
                                lihatDaftarMotor(daftarMotor);
                                break;
                            case 3:
                                system("cls");
                                updateNamaStokDanHargaMotor(daftarMotor);
                                break;
                            case 4:
                                system("cls");
                                hapusMotor(daftarMotor);
                                break;
                            case 5:
                                cout << "Keluar dari program. Terima kasih." << endl;
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
                cout << "Keluar dari program. Terima kasih." << endl;
                return 0;
            default:
                system("cls");
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }
    }

    return 0;
}

