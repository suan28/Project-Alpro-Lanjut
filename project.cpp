#include <iostream>
#include <fstream>
using namespace std;

const int MAX = 100;
const int MAX_PC = 10;

struct Member {
    int id;
    string nama;
    int jam;
    int harga;
    int aktif;
    int pc;
};

Member data[MAX];
bool pcTerpakai[MAX_PC];
int jumlah = 0;

int hitungHarga(int jam) {
    return 5000 * jam; 
}


void simpanKeFile() {
    ofstream file("data_member.txt");
    for (int i = 0; i < jumlah; i++) {
        if (data[i].aktif == 1) {
            file << data[i].id << " "
                 << data[i].jam << " "
                 << data[i].harga << " "
                 << data[i].aktif << " "
                 << data[i].pc << " "
                 << data[i].nama << "\n"; 
        }
    }
    file.close();
}


void bacaDariFile() {
    ifstream file("data_member.txt");
    jumlah = 0;
    while (file >> data[jumlah].id 
                >> data[jumlah].jam 
                >> data[jumlah].harga 
                >> data[jumlah].aktif 
                >> data[jumlah].pc) 
    {
        file.ignore(); 
        getline(file, data[jumlah].nama); 

        if (data[jumlah].aktif == 1 && data[jumlah].pc >= 1 && data[jumlah].pc <= MAX_PC) {
            pcTerpakai[data[jumlah].pc - 1] = true;
        }
        jumlah++;
        if (jumlah >= MAX) break;
    }
    file.close();
}

// 1. Buat Member
void buatMember() {
    if (jumlah >= MAX) {
        cout << "Data penuh!\n";
        return;
    }

    int idInput;
    cout << "Masukkan ID Member: ";
    cin >> idInput;

    bool sudahAda = false;
    int indexAda = -1;
    for (int i = 0; i < jumlah; i++) {
        if (data[i].id == idInput && data[i].aktif == 1) {
            sudahAda = true;
            indexAda = i;
            break;
        }
    }

    if (sudahAda) {
        cout << "ID sudah terdaftar atas nama: " << data[indexAda].nama << endl;
        cout << "\n=== PRICE LIST ===\n";
        for (int i = 1; i <= 5; i++) {
            cout << i << " jam = Rp" << hitungHarga(i) << endl;
        }

        int tambahanJam;
        cout << "Durasi tambahan (jam): ";
        cin >> tambahanJam;

        data[indexAda].jam += tambahanJam;
        data[indexAda].harga = hitungHarga(data[indexAda].jam);

        simpanKeFile();
        cout << "Durasi diperbarui! Total jam: " << data[indexAda].jam 
             << " jam, Total harga: Rp" << data[indexAda].harga << endl;
        return;
    }

    Member m;
    m.id = idInput;
    cin.ignore();
    cout << "Masukkan Nama: ";
    getline(cin, m.nama);

    // pilih PC kosong
    int pilihPC;
    while (true) {
        cout << "Pilih PC (1-10): ";
        cin >> pilihPC;
        if (pilihPC >= 1 && pilihPC <= MAX_PC && !pcTerpakai[pilihPC-1]) {
            m.pc = pilihPC;
            pcTerpakai[pilihPC-1] = true;
            break;
        } else {
            cout << "PC tidak tersedia, silakan pilih lagi.\n";
        }
    }

    cout << "\n=== PRICE LIST ===\n";
    for (int i = 1; i <= 5; i++) {
        cout << i << " jam = Rp" << hitungHarga(i) << endl;
    }

    cout << "Durasi (jam): ";
    cin >> m.jam;

    m.harga = hitungHarga(m.jam);
    m.aktif = 1;
    data[jumlah++] = m;

    simpanKeFile();
    cout << "Member baru berhasil dibuat dengan harga Rp" << m.harga 
         << " di PC " << m.pc << endl;
}

// 2. Cari ID Member
void cariMember() {
    int id;
    cout << "Masukkan ID yang dicari: ";
    cin >> id;
    bool ketemu = false;
    for (int i = 0; i < jumlah; i++) {
        if (data[i].id == id && data[i].aktif == 1) {
            cout << "Data ditemukan!\n";
            cout << "Nama: " << data[i].nama 
                 << ", Durasi total: " << data[i].jam 
                 << " jam, Harga total: Rp" << data[i].harga
                 << ", PC: " << data[i].pc << endl;
            ketemu = true;
            break;
        }
    }
    if (!ketemu) cout << "Data tidak ditemukan.\n";
}

// 3. Lihat Data Member
void lihatDataMember() {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (data[j].id > data[j+1].id) {
                Member tmp = data[j];
                data[j] = data[j+1];
                data[j+1] = tmp;
            }
        }
    }

    cout << "\n=== Data Member Terurut (ID) ===\n";
    for (int i = 0; i < jumlah; i++) {
        if (data[i].aktif == 1) {
            cout << "ID: " << data[i].id 
                 << ", Nama: " << data[i].nama 
                 << ", Durasi total: " << data[i].jam 
                 << " jam, Harga total: Rp" << data[i].harga
                 << ", PC: " << data[i].pc << endl;
        }
    }
}

// 4. Lihat PC Kosong
void lihatPCKosong() {
    cout << "\n=== Status PC ===\n";
    for (int i = 0; i < MAX_PC; i++) {
        cout << "PC " << i+1 << ": " << (pcTerpakai[i] ? "Terpakai" : "Kosong") << endl;
    }
}

int main() {
    bacaDariFile();
    int pilihan;
    do {
        cout << "\n=== Sistem Manajemen Member Warnet ===\n";
        cout << "1. Buat Member\n";
        cout << "2. Cari ID Member\n";
        cout << "3. Lihat Data Member\n";
        cout << "4. Lihat PC Kosong\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: buatMember(); break;
            case 2: cariMember(); break;
            case 3: lihatDataMember(); break;
            case 4: lihatPCKosong(); break;
            case 5: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    return 0;
}
