// =============================================================================
// CT18: Shortest Path & MST — Demo Driver
// =============================================================================
//
// Builds a weighted city map and demonstrates Dijkstra's and Prim's.
//
//     SLC ---4--- Ogden
//      |  \         |
//      6   3        5
//      |    \       |
//    Provo---2---Logan
//

#include "WeightedGraph.h"
#include <iostream>

int main() {

    std::cout << "=== Build Weighted Graph ===" << std::endl;

    WeightedGraph g;
    g.add_edge("SLC", "Ogden", 4);
    g.add_edge("SLC", "Provo", 6);
    g.add_edge("SLC", "Logan", 3);
    g.add_edge("Ogden", "Logan", 5);
    g.add_edge("Provo", "Logan", 2);

    g.print();
    std::cout << std::endl;

    // =============================================================================
    // Dijkstra's — Shortest paths from SLC
    // =============================================================================
    std::cout << "=== Dijkstra's from SLC ===" << std::endl;

    auto distances = g.dijkstra("SLC");
    for (const auto& [city, dist] : distances) {
        std::cout << "  SLC -> " << city << ": " << dist << std::endl;
    }
    // Expected: SLC=0, Ogden=4, Logan=3, Provo=5 (SLC->Logan->Provo = 3+2)
    std::cout << std::endl;

    // =============================================================================
    // Prim's MST
    // =============================================================================
    std::cout << "=== Prim's MST from SLC ===" << std::endl;

    auto [mst_edges, total] = g.prims_mst("SLC");
    for (const auto& [from, to, weight] : mst_edges) {
        std::cout << "  " << from << " --- " << to << " (weight " << weight << ")" << std::endl;
    }
    std::cout << "Total MST weight: " << total << std::endl;
    // Expected edges: SLC-Logan(3), Logan-Provo(2), SLC-Ogden(4) = total 9

    return 0;
}
