#include "graph_warnet.h"
#include <limits>

int main() {
    Graph g; // Membuat objek graf
    int choice; // Variabel untuk menyimpan pilihan menu

    do {
        g.displayMenu(); // Menampilkan menu

        string input;
        cin >> input;

        try {
            choice = stoi(input); // Mengonversi input menjadi integer
        } catch (invalid_argument&) {
            cout << "Error: Input harus berupa nomor menu yang valid." << endl;
            continue;
        } catch (out_of_range&) {
            cout << "Error: Nomor menu di luar jangkauan." << endl;
            continue;
        }

        switch (choice) {
            case 1: { // Tambah Node
                string ids;
                cout << "Masukkan ID Node (misal: PC1, PC2, PC3) atau ketik 'Cancel' untuk membatalkan: ";
                cin.ignore();
                getline(cin, ids);
                if (ids == "Cancel") break;

                string type;
                cout << "Masukkan tipe untuk semua node (regular/elite) atau ketik 'Cancel' untuk membatalkan: ";
                cin >> type;
                if (type == "Cancel") break;

                size_t pos = 0;
                while ((pos = ids.find(',')) != string::npos) {
                    g.addNode(ids.substr(0, pos), type); // Menambahkan node berdasarkan ID
                    ids.erase(0, pos + 1); // Menghapus ID yang sudah diproses
                }
                g.addNode(ids, type); // Menambahkan ID terakhir
                break;
            }
            case 2: { // Tambah Edge
                string sourceId, destinationId;
                int weight;
                cout << "Masukkan koneksi (source destination weight) atau ketik 'Cancel' untuk membatalkan: ";
                cin >> sourceId;
                if (sourceId == "Cancel") break;
                cin >> destinationId;
                if (destinationId == "Cancel") break;
                cin >> weight;
                if (cin.fail()) {
                    cin.clear(); // Reset cin state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Buang input yang tidak valid
                    break;
                }
                g.addEdge(sourceId, destinationId, weight); // Menambahkan edge
                break;
            }
            case 3: { // Hitung Total Bandwidth
                int totalBandwidth = g.calculateTotalBandwidth();
                cout << "Total Bandwidth: " << totalBandwidth << " Mbps" << endl;
                break;
            }
            case 4: { // Periksa Koneksi Antar PC
                string pc_x, pc_y;
                cout << "Masukkan dua PC untuk memeriksa koneksi (misal: PC1 PC2) atau ketik 'Cancel' untuk membatalkan: ";
                cin >> pc_x;
                if (pc_x == "Cancel") break;
                cin >> pc_y;
                if (pc_y == "Cancel") break;
                if (g.canCommunicate(pc_x, pc_y)) {
                    cout << "PC " << pc_x << " dan " << pc_y << " dapat saling berkomunikasi." << endl;
                } else {
                    cout << "PC " << pc_x << " dan " << pc_y << " tidak dapat saling berkomunikasi." << endl;
                }
                break;
            }
            case 5: { // Jalankan Algoritma Dijkstra
                string startNode;
                cout << "Masukkan ID Node awal untuk Dijkstra atau ketik 'Cancel' untuk membatalkan: ";
                cin >> startNode;
                if (startNode == "Cancel") break;
                auto distances = g.dijkstra(startNode);
                cout << "Jarak terpendek dari " << startNode << " ke semua node:" << endl;
                for (const auto& pair : distances) {
                    cout << "PC " << pair.first << ": " << pair.second << " ms" << endl;
                }
                break;
            }
            case 6: { // Uji Koneksi ke PC Tertentu
                string pc;
                cout << "Masukkan ID PC untuk diuji koneksinya atau ketik 'Cancel' untuk membatalkan: ";
                cin >> pc;
                if (pc == "Cancel") break;
                g.testConnection(pc);
                break;
            }
            case 7: { // Lihat List Koneksi Warnet
                g.displayConnections(); // Menampilkan daftar koneksi
                break;
            }
            case 8: // Keluar
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }
    } while (choice != 8); // Loop hingga pengguna memilih untuk keluar

    return 0;
}
