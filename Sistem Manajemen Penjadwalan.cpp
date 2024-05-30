#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

class Schedule {
public:
    Schedule(const string& tanggal, const string& waktu, const string& deskripsi)
        : tanggal(tanggal), waktu(waktu), deskripsi(deskripsi), sudahSelesai(false) {}

    void tandaiSelesai() {
        sudahSelesai = true;
    }

    void perbaruiJadwal(const string& tanggalBaru, const string& waktuBaru, const string& deskripsiBaru) {
        tanggal = tanggalBaru;
        waktu = waktuBaru;
        deskripsi = deskripsiBaru;
    }

    void cetakJadwal() const {
        cout << "Tanggal: " << tanggal << endl;
        cout << "Waktu: " << waktu << endl;
        cout << "Deskripsi: " << deskripsi << endl;
        cout << (sudahSelesai ? "Selesai" : "Belum selesai") << endl;
        cout << endl;
    }

    string getTanggal() const {
        return tanggal;
    }

    string getWaktu() const {
        return waktu;
    }

    bool operator<=(const Schedule &j2) const {
        return getTanggal() < j2.getTanggal() || (getTanggal() == j2.getTanggal() && getWaktu() < j2.getWaktu());
    }

private:
    string tanggal;
    string waktu;
    string deskripsi;
    bool sudahSelesai;
};

int partition(vector<Schedule*>& arr, int low, int high) {
    Schedule* pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (*arr[j] <= *pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<Schedule*>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void tambahJadwal(vector<Schedule*>& jadwal) {
    string tanggal, waktu, deskripsi;
    queue<string> q;

    cout << "Masukkan tanggal (dd/mm/yyyy): ";
    cin >> tanggal;
    q.push(tanggal);

    cout << "Masukkan waktu: ";
    cin >> waktu;
    q.push(waktu);

    cout << "Masukkan deskripsi: ";
    cin.ignore();
    getline(cin, deskripsi);
    q.push(deskripsi);

    tanggal = q.front();
    q.pop();
    waktu = q.front();
    q.pop();
    deskripsi = q.front();
    q.pop();

    jadwal.push_back(new Schedule(tanggal, waktu, deskripsi));

    cout << "Jadwal berhasil ditambahkan!" << endl;
}

void hapusJadwal(vector<Schedule*>& jadwal) {
    string tanggal, waktu;

    cout << "Masukkan tanggal jadwal yang akan dihapus: ";
    cin >> tanggal;

    cout << "Masukkan waktu jadwal yang akan dihapus: ";
    cin >> waktu;

    auto it = find_if(jadwal.begin(), jadwal.end(),
        [tanggal, waktu](const Schedule* jadwal) {
            return (jadwal->getTanggal() == tanggal) && (jadwal->getWaktu() == waktu);
        });

    if (it != jadwal.end()) {
        delete *it;
        jadwal.erase(it);
        cout << "Jadwal berhasil dihapus!" << endl;
    }
    else {
        cout << "Jadwal tidak ditemukan!" << endl;
    }
}

void tandaiJadwalSelesai(vector<Schedule*>& jadwal) {
    string tanggal, waktu;

    cout << "Masukkan tanggal jadwal yang akan ditandai selesai: ";
    cin >> tanggal;

    cout << "Masukkan waktu jadwal yang akan ditandai selesai: ";
    cin >> waktu;

    auto it = find_if(jadwal.begin(), jadwal.end(),
        [tanggal, waktu](const Schedule* jadwal) {
            return (jadwal->getTanggal() == tanggal) && (jadwal->getWaktu() == waktu);
        });

    if (it != jadwal.end()) {
        (*it)->tandaiSelesai();
        cout << "Jadwal berhasil ditandai selesai!" << endl;
    }
    else {
        cout << "Jadwal tidak ditemukan!" << endl;
    }
}

void perbaruiJadwal(vector<Schedule*>& jadwal) {
    string tanggal, waktu;
    cout << "Masukkan tanggal jadwal yang akan diperbarui: ";
    cin >> tanggal;

    cout << "Masukkan waktu jadwal yang akan diperbarui: ";
    cin >> waktu;

    auto it = find_if(jadwal.begin(), jadwal.end(),
        [tanggal, waktu](const Schedule* jadwal) {
            return (jadwal->getTanggal() == tanggal) && (jadwal->getWaktu() == waktu);
        });

    if (it != jadwal.end()) {
        string tanggalBaru, waktuBaru, deskripsiBaru;

        cout << "Masukkan tanggal baru (dd/mm/yyyy): ";
        cin >> tanggalBaru;

        cout << "Masukkan waktu baru: ";
        cin >> waktuBaru;

        cout << "Masukkan deskripsi baru: ";
        cin.ignore();
        getline(cin, deskripsiBaru);

        (*it)->perbaruiJadwal(tanggalBaru, waktuBaru, deskripsiBaru);

        cout << "Jadwal berhasil diperbarui!" << endl;
    }
    else {
        cout << "Jadwal tidak ditemukan!" << endl;
    }
}

void cetakJadwal(const vector<Schedule*>& jadwal) {
    if (jadwal.empty()) {
        cout << "Tidak ada jadwal yang ditemukan!" << endl;
        return;
    }

    for (const Schedule* jadwal : jadwal) {
        jadwal->cetakJadwal();
    }
}

void cetakJadwalTerbalik(const vector<Schedule*>& jadwal) {
    if (jadwal.empty()) {
        cout << "Tidak ada jadwal yang ditemukan!" << endl;
        return;
    }

    for (auto it = jadwal.rbegin(); it != jadwal.rend(); ++it) {
        (*it)->cetakJadwal();
    }
}

void cetakJadwalTerurut(vector<Schedule*>& jadwal) {
    if (jadwal.empty()) {
        cout << "Tidak ada jadwal yang ditemukan!" << endl;
        return;
    }

    quickSort(jadwal, 0, jadwal.size() - 1);

    cetakJadwal(jadwal);
}

void cetakJadwalTerurutMenurun(vector<Schedule*>& jadwal) {
    if (jadwal.empty()) {
        cout << "Tidak ada jadwal yang ditemukan!" << endl;
        return;
    }

    sort(jadwal.begin(), jadwal.end(), [](const Schedule* j1, const Schedule* j2) {
        return j1->getTanggal() > j2->getTanggal() || (j1->getTanggal() == j2->getTanggal() && j1->getWaktu() > j2->getWaktu());
    });

    cetakJadwal(jadwal);
}

int main() {
    vector<Schedule*> jadwal;
    int pilihan;

    do {
        cout << "============================================" << endl;
        cout << "|              SELAMAT DATANG              |" << endl;
        cout << "|       Sistem Manajemen Penjadwalan       |" << endl;
        cout << "|==========================================|" << endl;
        cout << "| 1. Tambah Jadwal                         |" << endl;
        cout << "| 2. Hapus Jadwal                          |" << endl;
        cout << "| 3. Tandai Jadwal sebagai Selesai         |" << endl;
        cout << "| 4. Perbarui Jadwal                       |" << endl;
        cout << "| 5. Cetak Jadwal                          |" << endl;
        cout << "| 6. Cetak Jadwal Terbalik                 |" << endl;
        cout << "| 7. Cetak Jadwal Terurut                  |" << endl;
        cout << "| 8. Cetak Jadwal Terurut Menurun          |" << endl;
        cout << "| 9. Keluar                                |" << endl;
        cout << "============================================" << endl;
        cout << " Masukkan pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahJadwal(jadwal);
            break;
        case 2:
            hapusJadwal(jadwal);
            break;
        case 3:
            tandaiJadwalSelesai(jadwal);
            break;
        case 4:
            perbaruiJadwal(jadwal);
            break;
        case 5:
            cetakJadwal(jadwal);
            break;
        case 6:
            cetakJadwalTerbalik(jadwal);
            break;
        case 7:
            cetakJadwalTerurut(jadwal);
            break;
        case 8:
            cetakJadwalTerurutMenurun(jadwal);
            break;
        case 9:
            cout << "Keluar dari program..." << endl;
            cout << "======================" << endl;
            cout << "     TERIMAKASIH    " << endl;
            cout << "======================" << endl;
            break;
        default:
            cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
        }

        cout << endl;

    } while (pilihan != 9);

    for (Schedule* jadwal : jadwal) {
        delete jadwal;
    }

    return 0;
}
