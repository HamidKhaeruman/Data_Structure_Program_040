#ifndef GRAPH_WARNET_H
#define GRAPH_WARNET_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <set>

using namespace std;

// Struktur Node untuk merepresentasikan PC
struct Node {
    string id; // Menggunakan string sebagai ID
    string type; // "regular" atau "elite"
};

// Struktur Edge untuk merepresentasikan koneksi antara PC
struct Edge {
    Node* destination; // Node tujuan
    int weight; // Bobot dari koneksi (bandwidth)
};

// Struktur Graph untuk merepresentasikan graf
class Graph {
public:
    vector<Node> nodes; // Daftar node (PC)
    unordered_map<string, vector<Edge>> adjacencyList; // Daftar adjacency untuk edge

    void addNode(const string& id, const string& type); // Menambahkan node
    void addEdge(const string& sourceId, const string& destinationId, int weight); // Menambahkan edge
    int calculateTotalBandwidth(); // Menghitung total bandwidth
    bool canCommunicate(const string& pc_x, const string& pc_y); // Memeriksa koneksi antar PC
    unordered_map<string, int> dijkstra(const string& startNode); // Algoritma Dijkstra
    void displayMenu(); // Menampilkan menu
    void testConnection(const string& pc); // Menguji koneksi ke PC tertentu
    void displayConnections(); // Menampilkan daftar koneksi warnet
};

#endif // GRAPH_WARNET_H
