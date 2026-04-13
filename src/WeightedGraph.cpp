// =============================================================================
// CT18: Shortest Path & MST — Implementation
// =============================================================================

#include "WeightedGraph.h"
#include <iostream>
#include <tuple>
#include <limits>

// =============================================================================
// 1. Constructor
// =============================================================================

WeightedGraph::WeightedGraph() {}

// =============================================================================
// 2. add_vertex / add_edge
// =============================================================================
//
// ? SEE DIAGRAM: images/cpp_diagrams.md #1 — add_edge weighted undirected edge
//
// ! DISCUSSION: add_edge is the only change from CT17's Graph.
//   - CT17 pushed just the neighbor string into a vector<string>
//   - CT18 pushes an Edge struct carrying BOTH the destination and the cost
//   - everything else (add_vertex, has_vertex, counts) is identical
//

void WeightedGraph::add_vertex(const std::string& vertex) {
    // TODO: insert vertex with empty edge list if not present
}

void WeightedGraph::add_edge(const std::string& from, const std::string& to, int weight) {
    // TODO: ensure both vertices exist, then push Edge{to, weight} into
    //       from's list AND Edge{from, weight} into to's list (undirected)
}

// =============================================================================
// 3. Queries
// =============================================================================

bool WeightedGraph::has_vertex(const std::string& vertex) const {
    // TODO
    return false;
}

int WeightedGraph::vertex_count() const {
    // TODO
    return 0;
}

int WeightedGraph::edge_count() const {
    // TODO: sum sizes of all edge lists, divide by 2 (undirected)
    return 0;
}

// =============================================================================
// 4. Dijkstra's Algorithm
// =============================================================================
//
// ? SEE DIAGRAM: images/cpp_diagrams.md #2  — dijkstra implementation
// ? SEE DIAGRAM: images/cpp_diagrams.md #2a — stale-entry skip breakdown
// ? SEE DIAGRAM: images/cpp_diagrams.md #2b — code execution trace
//
// ! DISCUSSION: The relaxation step.
//   - for each neighbor v of the current vertex u:
//     if dist[u] + edge_weight < dist[v]:
//       update dist[v] and push to priority queue
//   - "relax" means: we found a shorter path, so update our records
//
// ! DISCUSSION: Priority queue stores {distance, vertex}.
//   - we use std::greater so the smallest distance is at the top (min-heap)
//   - when we pop a vertex with d > dist[u], it's a stale entry — skip it
//   - stale entries happen because std::priority_queue has no decrease-key
//

std::unordered_map<std::string, int>
WeightedGraph::dijkstra(const std::string& source) const {
    std::unordered_map<std::string, int> dist;
    // TODO: implement Dijkstra's using a priority queue
    //
    // 1. Initialize all distances to std::numeric_limits<int>::max()
    //    dist[source] = 0
    // 2. Declare a min-heap of (distance, vertex) pairs using std::greater
    // 3. Push {0, source}
    // 4. While the heap is not empty:
    //    a. Pop the smallest (d, u)
    //    b. If d > dist[u], `continue;` (stale entry)
    //    c. For each edge {v, w} in adj_list_.at(u):
    //         if dist[u] + w < dist[v], update dist[v] and push {dist[v], v}
    return dist;
}

// =============================================================================
// 5. Prim's Algorithm — MST
// =============================================================================
//
// ? SEE DIAGRAM: images/cpp_diagrams.md #3  — prims implementation
// ? SEE DIAGRAM: images/cpp_diagrams.md #3b — code execution trace
//
// ! DISCUSSION: Prim's grows the MST one edge at a time.
//   - start with one vertex in the MST
//   - repeatedly add the cheapest edge that connects an MST vertex to a non-MST vertex
//   - stop when all vertices are in the MST (V-1 edges)
//
// ! DISCUSSION: Tuple is (weight, from, to) — 3 fields, not 2.
//   - weight first so the min-heap orders by it
//   - we need 'from' as well as 'to' to record the MST edge in the output
//   - skip rule: if 'to' is already in the MST, adding it would create a cycle
//

std::pair<std::vector<std::tuple<std::string, std::string, int>>, int>
WeightedGraph::prims_mst(const std::string& start) const {
    std::vector<std::tuple<std::string, std::string, int>> mst_edges;
    int total_weight = 0;
    // TODO: implement Prim's using a priority queue
    //
    // 1. Put `start` in an unordered_set<string> in_mst
    // 2. Declare a min-heap of (weight, from, to) tuples using std::greater
    // 3. Seed the heap with every edge leaving `start`: pq.push({w, start, v})
    // 4. While pq not empty AND in_mst.size() < V:
    //    a. Pop the cheapest tuple (w, from, to)
    //    b. If in_mst already contains `to`, `continue;` (would form a cycle)
    //    c. Append {from, to, w} to mst_edges; add w to total_weight
    //    d. Insert `to` into in_mst
    //    e. For each edge {v, nw} in adj_list_.at(to):
    //         if v is NOT in in_mst, pq.push({nw, to, v})
    return {mst_edges, total_weight};
}

// =============================================================================
// 6. print
// =============================================================================

void WeightedGraph::print() const {
    for (const auto& [vertex, edges] : adj_list_) {
        std::cout << vertex << ": ";
        for (size_t i = 0; i < edges.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << edges[i].to << "(" << edges[i].weight << ")";
        }
        std::cout << std::endl;
    }
}
