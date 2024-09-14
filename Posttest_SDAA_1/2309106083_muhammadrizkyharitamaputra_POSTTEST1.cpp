#include <iostream>
using namespace std;

void hanoi(int n, char asal, char tujuan, char sementara) {
    if (n > 0) {
        hanoi(n - 1, asal, sementara, tujuan);
        cout << "Pindahkan piringan " << n << " dari " << asal << " ke " << tujuan << endl;
        hanoi(n - 1, sementara, tujuan, asal);
    }
}

int main() {
    int n = 3;  
    cout << "Solusi Menara Hanoi untuk " << n << " piringan:\n";
    hanoi(n, 'A', 'C', 'B');  
    return 0;
}
