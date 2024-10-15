#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <conio.h>
#include <iomanip>
#include <algorithm>
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

struct StackNode {
    SepedaMotor motor;
    StackNode* next;
};

struct QueueNode {
    SepedaMotor motor;
    QueueNode* next;
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

void pushStack(StackNode*& top) {
    StackNode* newNode = new StackNode;
    cout << "Masukkan nama sepeda motor (Stack): ";
    cin.ignore();
    getline(cin, newNode->motor.nama);
    cout << "Masukkan jenis sepeda motor: ";
    getline(cin, newNode->motor.jenis);
    cout << "Masukkan stok sepeda motor: ";
    cin >> newNode->motor.stok;
    cout << "Masukkan harga sepeda motor: ";
    cin >> newNode->motor.harga;
    newNode->next = top;
    top = newNode;
    cout << "Sepeda motor berhasil ditambahkan ke Stack." << endl;
}

void popStack(StackNode*& top) {
    if (top == nullptr) {
        cerr << "Stack kosong!" << endl;
        return;
    }
    StackNode* temp = top;
    top = top->next;
    cout << "Sepeda motor " << temp->motor.nama << " berhasil dihapus dari Stack." << endl;
    delete temp;
}

void tampilkanStack(StackNode* top) {
    if (top == nullptr) {
        cout << "Stack kosong!" << endl;
        return;
    }

    cout << "=== DAFTAR SEPEDA MOTOR DI STACK ===" << endl;

    cout << left << setw(5)  << "ID"
         << setw(20) << "Nama"
         << setw(15) << "Jenis"
         << setw(10) << "Stok"
         << setw(15) << "Harga" << endl;
    cout << "--------------------------------------------------------------" << endl;

    int id = 1;
    StackNode* temp = top;
    while (temp != nullptr) {
        cout << left << setw(5)  << id++
             << setw(20) << temp->motor.nama
             << setw(15) << temp->motor.jenis
             << setw(10) << temp->motor.stok
             << setw(15) << fixed << setprecision(2) << temp->motor.harga << endl;
        temp = temp->next;
    }
}

void enqueue(QueueNode*& front, QueueNode*& rear) {
    QueueNode* newNode = new QueueNode;
    cout << "Masukkan nama sepeda motor (Queue): ";
    cin.ignore();
    getline(cin, newNode->motor.nama);
    cout << "Masukkan jenis sepeda motor: ";
    getline(cin, newNode->motor.jenis);
    cout << "Masukkan stok sepeda motor: ";
    cin >> newNode->motor.stok;
    cout << "Masukkan harga sepeda motor: ";
    cin >> newNode->motor.harga;
    newNode->next = nullptr;

    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    cout << "Sepeda motor berhasil ditambahkan ke Queue." << endl;
}

void dequeue(QueueNode*& front, QueueNode*& rear) {
    if (front == nullptr) {
        cerr << "Queue kosong!" << endl;
        return;
    }
    QueueNode* temp = front;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    cout << "Sepeda motor " << temp->motor.nama << " berhasil dihapus dari Queue." << endl;
    delete temp;
}

void tampilkanQueue(QueueNode* front) {
    if (front == nullptr) {
        cout << "Queue kosong!" << endl;
        return;
    }

    cout << "=== DAFTAR SEPEDA MOTOR DI QUEUE ===" << endl;

    cout << left << setw(5)  << "ID"
         << setw(20) << "Nama"
         << setw(15) << "Jenis"
         << setw(10) << "Stok"
         << setw(15) << "Harga" << endl;
    cout << "--------------------------------------------------------------" << endl;

    int id = 1;
    QueueNode* temp = front;
    while (temp != nullptr) {
        cout << left << setw(5)  << id++
             << setw(20) << temp->motor.nama
             << setw(15) << temp->motor.jenis
             << setw(10) << temp->motor.stok
             << setw(15) << fixed << setprecision(2) << temp->motor.harga << endl;
        temp = temp->next;
    }
}

int partitionAscending(vector<SepedaMotor>& arr, int low, int high) {
    double pivot = arr[high].harga;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].harga < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortAscending(vector<SepedaMotor>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionAscending(arr, low, high);
        quickSortAscending(arr, low, pi - 1);
        quickSortAscending(arr, pi + 1, high);
    }
}

void mergeDescending(vector<SepedaMotor>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<SepedaMotor> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].harga >= R[j].harga) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortDescending(vector<SepedaMotor>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortDescending(arr, left, mid);
        mergeSortDescending(arr, mid + 1, right);
        mergeDescending(arr, left, mid, right);
    }
}

vector<SepedaMotor> linkedListToVector(Node* head) {
    vector<SepedaMotor> vec;
    Node* temp = head;
    while (temp != nullptr) {
        vec.push_back(temp->motor);
        temp = temp->next;
    }
    return vec;
}


void vectorToLinkedList(vector<SepedaMotor>& vec, Node*& head) {
    head = nullptr;
    Node* tail = nullptr;
    for (const auto& motor : vec) {
        Node* newNode = new Node{motor, nullptr};
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
}

void sortMotorAscending(Node*& head) {
    vector<SepedaMotor> vec = linkedListToVector(head);
    quickSortAscending(vec, 0, vec.size() - 1);
    vectorToLinkedList(vec, head);
    cout << "Daftar sepeda motor berhasil diurutkan secara ascending berdasarkan harga." << endl;
}

void sortMotorDescending(Node*& head) {
    vector<SepedaMotor> vec = linkedListToVector(head);
    mergeSortDescending(vec, 0, vec.size() - 1);
    vectorToLinkedList(vec, head);
    cout << "Daftar sepeda motor berhasil diurutkan secara descending berdasarkan harga." << endl;
}



void tampilkanMenu() {
    cout << "===== MENU UTAMA =====" << endl;
    cout << "1. Registrasi" << endl;
    cout << "2. Login" << endl;
    cout << "3. Keluar" << endl;
}

void tampilkanMenuMotor() {
    cout << "===== MENU SEPEDA MOTOR =====" << endl;
    cout << "1. Tambah Sepeda Motor" << endl;
    cout << "2. Lihat Daftar Sepeda Motor" << endl;
    cout << "3. Update Nama, Stok, dan Harga Sepeda Motor" << endl;
    cout << "4. Hapus Sepeda Motor" << endl;
    cout << "5. Kelola Sepeda Motor dengan Stack" << endl;
    cout << "6. Kelola Sepeda Motor dengan Queue" << endl;
    cout << "7. Urutkan Sepeda Motor (Ascending)" << endl;
    cout << "8. Urutkan Sepeda Motor (Descending)" << endl;
    cout << "9. Keluar" << endl;
}


void tampilkanMenuStack() {
    cout << "===== MENU STACK =====" << endl;
    cout << "1. Push (Tambah Motor)" << endl;
    cout << "2. Pop (Hapus Motor)" << endl;
    cout << "3. Tampilkan Isi Stack" << endl;
    cout << "4. Kembali ke Menu Utama" << endl;
}

void tampilkanMenuQueue() {
    cout << "===== MENU QUEUE =====" << endl;
    cout << "1. Enqueue (Tambah Motor)" << endl;
    cout << "2. Dequeue (Hapus Motor)" << endl;
    cout << "3. Tampilkan Isi Queue" << endl;
    cout << "4. Kembali ke Menu Utama" << endl;
}

void registrasiPengguna(vector<Pengguna>& pengguna) {
    Pengguna p;
    cout << "Masukkan nama: ";
    getline(cin, p.nama);
    cout << "Masukkan NIM: ";
    getline(cin, p.nim);
    pengguna.push_back(p);
    cout << "Registrasi berhasil." << endl;
}

bool cekLogin(const vector<Pengguna>& pengguna) {
    string nama, nim;
    cout << "Masukkan nama: ";
    getline(cin, nama);
    cout << "Masukkan NIM: ";
    getline(cin, nim);

    for (const auto& p : pengguna) {
        if (p.nama == nama && p.nim == nim) {
            cout << "Login berhasil." << endl;
            return true;
        }
    }
    cerr << "Login gagal. Nama atau NIM tidak cocok." << endl;
    return false;
}

int main() {
    Node* daftarMotor = nullptr;
    vector<Pengguna> pengguna;
    StackNode* topStack = nullptr; 
    QueueNode* frontQueue = nullptr, * rearQueue = nullptr; 

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
                                system("cls");
                                while (true) {
                                    tampilkanMenuStack();
                                    int pilihanStack;
                                    cout << "Pilihan: ";
                                    cin >> pilihanStack;

                                    if (pilihanStack == 1) {
                                        pushStack(topStack);
                                        system("cls");
                                    } else if (pilihanStack == 2) {
                                        popStack(topStack);
                                       
                                    } else if (pilihanStack == 3) {
                                        system("cls");
                                        tampilkanStack(topStack);
                                    } else if (pilihanStack == 4) {
                                        system("cls");
                                        break;
                                    } else {
                                        cout << "Pilihan tidak valid!" << endl;
                                    }
                                }
                                break;
                            case 6:
                                system("cls");
                                while (true) {
                                    tampilkanMenuQueue();
                                    int pilihanQueue;
                                    cout << "Pilihan: ";
                                    cin >> pilihanQueue;

                                    if (pilihanQueue == 1) {
                                        enqueue(frontQueue, rearQueue);
                                        system("cls");
                                    } else if (pilihanQueue == 2) {
                                        dequeue(frontQueue, rearQueue);
                                        
                                    } else if (pilihanQueue == 3) {
                                        system("cls");
                                        tampilkanQueue(frontQueue);
                                    } else if (pilihanQueue == 4) {
                                        system("cls");
                                        break;
                                    } else {
                                        cout << "Pilihan tidak valid!" << endl;
                                    }
                                }
                                break;
                           case 7:
                                system("cls");
                                sortMotorAscending(daftarMotor);
                                break;
                            case 8:
                                system("cls");
                                sortMotorDescending(daftarMotor);
                                break;
                            case 9:
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
