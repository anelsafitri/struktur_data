#include <iostream>
#include <stack>
#include <string>

using namespace std;

class PengolahKata {
private:
    stack<string> tumpukanUndo;
    stack<string> tumpukanRedo;
    string teksSaatIni;

public:
    void ketik(const string& teks) {
        tumpukanUndo.push(teksSaatIni); // Simpan keadaan saat ini untuk undo
        teksSaatIni += teks;            // Tambahkan teks baru
        while (!tumpukanRedo.empty()) { // Kosongkan tumpukan redo
            tumpukanRedo.pop();
        }
    }

    void undo() {
        if (!tumpukanUndo.empty()) {
            tumpukanRedo.push(teksSaatIni); // Simpan keadaan saat ini untuk redo
            teksSaatIni = tumpukanUndo.top(); // Kembalikan ke keadaan terakhir
            tumpukanUndo.pop();
        } else {
            cout << "Tidak ada yang bisa di-undo." << endl;
        }
    }

    void redo() {
        if (!tumpukanRedo.empty()) {
            tumpukanUndo.push(teksSaatIni); // Simpan keadaan saat ini untuk undo
            teksSaatIni = tumpukanRedo.top(); // Kembalikan ke keadaan yang sudah di-undo
            tumpukanRedo.pop();
        } else {
            cout << "Tidak ada yang bisa di-redo." << endl;
        }
    }

    bool kosongUndo() const {
        return tumpukanUndo.empty();
    }

    bool kosongRedo() const {
        return tumpukanRedo.empty();
    }

    void cetakTeksSaatIni() const {
        cout << "Teks saat ini: " << teksSaatIni << endl;
    }
};

void tampilkanMenu() {
    cout << "\n===============================" << endl;
    cout << "       PILIHAN MENU:" << endl;
    cout << "===============================" << endl;
    cout << "  1. Ketik" << endl;
    cout << "  2. Undo" << endl;
    cout << "  3. Redo" << endl;
    cout << "  4. Cek Kosong Undo" << endl;
    cout << "  5. Cek Kosong Redo" << endl;
    cout << "  6. Keluar" << endl;
    cout << "===============================" << endl;
    cout << "Pilih (1-6): ";
}

int main() {
    PengolahKata editor;
    int pilihan;
    string teks;

    while (true) {
        tampilkanMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan teks: ";
                cin.ignore(); // Abaikan karakter newline yang tersisa di buffer input
                getline(cin, teks);
                editor.ketik(teks);
                editor.cetakTeksSaatIni();
                break;

            case 2:
                editor.undo();
                editor.cetakTeksSaatIni();
                break;

            case 3:
                editor.redo();
                editor.cetakTeksSaatIni();
                break;

            case 4:
                cout << (editor.kosongUndo() ? "Tumpukan undo kosong." : "Tumpukan undo tidak kosong.") << endl;
                break;

            case 5:
                cout << (editor.kosongRedo() ? "Tumpukan redo kosong." : "Tumpukan redo tidak kosong.") << endl;
                break;

            case 6:
                return 0;

            default:
                cout << "Pilihan tidak dikenal." << endl;
                break;
        }
    }

    return 0;
}
