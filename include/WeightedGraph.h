#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits>

// =============================================================================
// CT18: Shortest Path & Minimum Spanning Tree
// =============================================================================
//
// A weighted graph assigns a numeric cost (weight) to each edge.
// This enables two fundamental algorithms:
//   - Dijkstra's: find the shortest path from one vertex to all others
//   - Prim's: find the minimum spanning tree (cheapest way to connect all vertices)
//
// ? SEE DIAGRAM: images/header_diagrams.md #1 — weighted graph example
//
// ! DISCUSSION: Weighted vs unweighted graphs.
//   - CT17 used unweighted graphs (every edge has the same cost)
//   - BFS finds shortest path in unweighted graphs (fewest edges)
//   - Dijkstra's finds shortest path in weighted graphs (lowest total cost)
//   - you can't just use BFS on a weighted graph — fewer edges != lower cost
//

/// Edge struct: stores destination vertex and weight.
struct Edge {
    std::string to;
    int weight;
};

class WeightedGraph {
public:
    // -------------------------------------------------------------------------
    // Constructor
    // -------------------------------------------------------------------------

    /// Constructs an empty weighted undirected graph.
    WeightedGraph();

    // -------------------------------------------------------------------------
    // Modifiers
    // -------------------------------------------------------------------------

    /// Adds a vertex to the graph. Ignored if vertex already exists.
    void add_vertex(const std::string& vertex);

    /// Adds a weighted undirected edge between two vertices.
    /// Creates vertices if they don't exist.
    void add_edge(const std::string& from, const std::string& to, int weight);

    // -------------------------------------------------------------------------
    // Queries
    // -------------------------------------------------------------------------

    bool has_vertex(const std::string& vertex) const;
    int vertex_count() const;
    int edge_count() const;

    // -------------------------------------------------------------------------
    // Dijkstra's Algorithm — Shortest Path
    // -------------------------------------------------------------------------
    //
    // ? SEE DIAGRAM: images/header_diagrams.md #2 — Dijkstra's step-by-step
    //
    // ! DISCUSSION: Dijkstra's algorithm.
    //   - finds the shortest path from a source vertex to ALL other vertices
    //   - uses a priority queue (min-heap) to always process the closest vertex
    //   - greedy: once a vertex is finalized, its shortest distance is known
    //   - does NOT work with negative edge weights
    //
    // ! DISCUSSION: Time complexity.
    //   - O((V + E) log V) with a binary heap priority queue
    //   - each vertex is extracted from the heap once: O(V log V)
    //   - each edge is relaxed once: O(E log V)
    //

    /// Returns shortest distances from source to all reachable vertices.
    std::unordered_map<std::string, int> dijkstra(const std::string& source) const;

    // -------------------------------------------------------------------------
    // Prim's Algorithm — Minimum Spanning Tree
    // -------------------------------------------------------------------------
    //
    // ? SEE DIAGRAM: images/header_diagrams.md #3 — Prim's MST step-by-step
    //
    // ! DISCUSSION: Prim's algorithm (CCD 2.12 — lecture only).
    //   - finds the minimum spanning tree: connects ALL vertices with minimum total weight
    //   - a spanning tree has exactly V-1 edges and no cycles
    //   - greedy: always pick the cheapest edge that connects a new vertex
    //   - uses a priority queue to efficiently find the cheapest crossing edge
    //
    // ! DISCUSSION: Prim's vs Dijkstra's.
    //   - Dijkstra's minimizes total distance from SOURCE to each vertex
    //   - Prim's minimizes total weight of all edges in the tree
    //   - same data structure (priority queue), different goal
    //

    /// Returns the edges in the MST and the total weight.
    /// pair.first = vector of (from, to, weight) tuples
    /// pair.second = total MST weight
    std::pair<std::vector<std::tuple<std::string, std::string, int>>, int>
    prims_mst(const std::string& start) const;

    // -------------------------------------------------------------------------
    // Display
    // -------------------------------------------------------------------------

    void print() const;

private:
    std::unordered_map<std::string, std::vector<Edge>> adj_list_;
};
