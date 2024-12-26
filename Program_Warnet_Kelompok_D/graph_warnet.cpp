#include "graph_warnet.h"

// Menambahkan Node ke Graph
void Graph::addNode(const string& id, const string& type) {
    Node newNode = {id, type}; // Membuat node baru
    nodes.push_back(newNode); // Menambahkan node ke dalam daftar
}

// Menambahkan Edge ke Graph
void Graph::addEdge(const string& sourceId, const string& destinationId, int weight) {
    Node* destinationNode = nullptr; // Pointer untuk node tujuan
    for (auto& node : nodes) {
        if (node.id == destinationId) {
            destinationNode = &node; // Mencari node tujuan
            break;
        }
    }
    // Jika node tujuan ditemukan, tambahkan edge
    if (destinationNode) {
        adjacencyList[sourceId].push_back({destinationNode, weight}); // Menambahkan edge dari source ke destination
        adjacencyList[destinationId].push_back({&nodes[0], weight}); // Menambahkan koneksi balik ke server
    }
}

// Menghitung Total Bandwidth
int Graph::calculateTotalBandwidth() {
    int totalBandwidth = 0; // Variabel untuk total bandwidth
    for (const auto& node : nodes) {
        // Menambahkan bandwidth berdasarkan tipe node
        if (node.type == "regular") {
            totalBandwidth += 100; // 100 Mbps untuk paket regular
        } else if (node.type == "elite") {
            totalBandwidth += 200; // 200 Mbps untuk paket elite
        }
    }
    return totalBandwidth; // Mengembalikan total bandwidth
}

// Memeriksa Koneksi Antar PC
bool Graph::canCommunicate(const string& pc_x, const string& pc_y) {
    queue<string> q; // Antrian untuk BFS
    set<string> visited; // Set untuk menyimpan node yang sudah dikunjungi

    q.push(pc_x); // Menambahkan node awal ke antrian
    visited.insert(pc_x); // Menandai node awal sebagai dikunjungi

    while (!q.empty()) {
        string current = q.front(); // Mengambil node dari antrian
        q.pop();

        if (current == pc_y) {
            return true; // Jika menemukan node tujuan
        }

        // Mencari semua neighbor dari node saat ini
        for (const auto& edge : adjacencyList[current]) {
            string neighbor = edge.destination->id; // Mendapatkan ID neighbor
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor); // Menandai neighbor sebagai dikunjungi
                q.push(neighbor); // Menambahkan neighbor ke antrian
            }
        }
    }
    return false; // Tidak ada jalur komunikasi
}

// Algoritma Dijkstra
unordered_map<string, int> Graph::dijkstra(const string& startNode) {
    unordered_map<string, int> distances; // Peta untuk menyimpan jarak
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq; // Antrian prioritas

    // Inisialisasi jarak untuk semua node
    for (const auto& node : nodes) {
        distances[node.id] = numeric_limits<int>::max(); // Set jarak awal ke tak terhingga
    }
    distances[startNode] = 0; // Jarak dari startNode ke dirinya sendiri adalah 0

    pq.push({0, startNode}); // Menambahkan node awal ke antrian prioritas

    while (!pq.empty()) {
        string current = pq.top().second; // Mendapatkan node saat ini
        int currentDistance = pq.top().first; // Mendapatkan jarak saat ini
        pq.pop();

        // Mencari semua edge dari node saat ini
        for (const auto& edge : adjacencyList[current]) {
            int newDistance = currentDistance + edge.weight; // Menghitung jarak baru

            // Jika jarak baru lebih kecil dari jarak yang sudah ada
            if (newDistance < distances[edge.destination->id]) {
                distances[edge.destination->id] = newDistance; // Update jarak
                pq.push({newDistance, edge.destination->id}); // Tambahkan ke antrian prioritas
            }
        }
    }

    return distances; // Mengembalikan jarak terpendek dari startNode ke semua node
}

// Menampilkan Menu
void Graph::displayMenu() {
    cout << "\n=== Menu ===\n";
    cout << "1. Tambah Node\n";
    cout << "2. Tambah Edge\n";
    cout << "3. Hitung Total Bandwidth\n";
    cout << "4. Periksa Koneksi Antar PC\n";
    cout << "5. Jalankan Algoritma Dijkstra\n";
    cout << "6. Uji Koneksi ke PC Tertentu\n";
    cout << "7. Lihat List Koneksi Warnet\n"; // Opsi baru untuk melihat koneksi
    cout << "8. Keluar\n";
    cout << "Pilih opsi: ";
}

// Menguji Koneksi ke PC tertentu
void Graph::testConnection(const string& pc) {
    if (adjacencyList.find(pc) != adjacencyList.end()) {
        int speed = (nodes[0].type == "elite") ? 200 : 100; // Kecepatan berdasarkan tipe node
        cout << "Menghubungi " << pc << " ... " << endl;
        cout << "Koneksi berhasil dengan kecepatan: " << speed << " Mbps" << endl;
    } else {
        cout << "PC " << pc << " tidak ditemukan." << endl;
    }
}

// Menampilkan daftar koneksi
void Graph::displayConnections() {
    cout << "\n=== List Koneksi Warnet ===\n";
    for (const auto& node : nodes) {
        cout << node.id << " : "; // Menampilkan ID PC
        // Menampilkan koneksi dari node ini
        for (const auto& edge : adjacencyList[node.id]) {
            cout << edge.destination->id << " - "; // Menampilkan ID koneksi
        }
        cout << "\b\b \n"; // Menghapus tanda '-' terakhir
    }
}
