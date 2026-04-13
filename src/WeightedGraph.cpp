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

// Provided — identical to CT17's Graph::add_vertex.
void WeightedGraph::add_vertex(const std::string& vertex) {
    if (adj_list_.find(vertex) == adj_list_.end()) {
        adj_list_[vertex] = {};
    }
}

void WeightedGraph::add_edge(const std::string& from, const std::string& to, int weight) {
    // TODO: ensure both vertices exist, then push Edge{to, weight} into
    //       from's list AND Edge{from, weight} into to's list (undirected)
}

// =============================================================================
// 3. Queries
// =============================================================================

// Provided — identical to CT17's Graph::has_vertex.
bool WeightedGraph::has_vertex(const std::string& vertex) const {
    return adj_list_.count(vertex) > 0;
}

// Provided — identical to CT17's Graph::vertex_count.
int WeightedGraph::vertex_count() const {
    return static_cast<int>(adj_list_.size());
}

// Provided — identical to CT17's Graph::edge_count.
int WeightedGraph::edge_count() const {
    int total = 0;
    for (const auto& [vertex, edges] : adj_list_) {
        total += static_cast<int>(edges.size());
    }
    return total / 2;
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
    // TODO: implement Dijkstra's — step numbers match the SVG rows
    //
    // 1. Declare dist (already done above)
    // 2. Initialize every vertex's dist to std::numeric_limits<int>::max()
    // 3. Guard: if (!has_vertex(source)) return dist;
    // 4. Seed the source: dist[source] = 0;
    // 5. Type alias: using Pair = std::pair<int, std::string>;
    // 6. Min-heap declaration:
    //      std::priority_queue<Pair, std::vector<Pair>,
    //                          std::greater<Pair>> min_heap;
    //    (std::greater flips the default max-heap to a min-heap)
    // 7. Seed the min-heap: min_heap.push({0, source})
    // 8. Main loop — while (!min_heap.empty()):
    //      pop (d, u) with min_heap.top() / min_heap.pop()
    // 9. Stale-entry skip: if (d > dist[u]) continue;
    // 10. Relax every edge in adj_list_.at(u): compute new_dist = dist[u]
    //     + edge.weight; if new_dist < dist[edge.to], update dist[edge.to]
    //     and min_heap.push({new_dist, edge.to})
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
    // TODO: implement Prim's — step numbers match the SVG rows
    //
    // 1. Put `start` in an unordered_set<string> in_mst
    // 2. Type alias:
    //      using EdgeTuple = std::tuple<int, std::string, std::string>;
    // 3. Min-heap declaration:
    //      std::priority_queue<EdgeTuple, std::vector<EdgeTuple>,
    //                          std::greater<EdgeTuple>> min_heap;
    //    (std::greater flips the default max-heap to a min-heap)
    // 4. Seed the frontier: push every edge leaving `start` as
    //    min_heap.push({edge.weight, start, edge.to})
    // 5. Cache V = vertex_count() so we can stop at the right time
    // 6. Main loop — while (!min_heap.empty() && in_mst.size() < V):
    //      pop the cheapest tuple (w, from, to)
    // 7. Cycle skip: if in_mst already contains `to`, continue;
    // 8. Accept the edge: mst_edges.push_back({from, to, w});
    //    total_weight += w; in_mst.insert(to);
    // 9. Grow the frontier: for each edge from `to`, push
    //    {edge.weight, to, edge.to} into min_heap (skip if edge.to in in_mst)
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
