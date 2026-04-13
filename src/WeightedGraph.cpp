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
    if (adj_list_.find(vertex) == adj_list_.end()) {
        adj_list_[vertex] = {};
    }
}

void WeightedGraph::add_edge(const std::string& from, const std::string& to, int weight) {
    add_vertex(from);
    add_vertex(to);
    adj_list_[from].push_back({to, weight});
    adj_list_[to].push_back({from, weight});
}

// =============================================================================
// 3. Queries
// =============================================================================

bool WeightedGraph::has_vertex(const std::string& vertex) const {
    return adj_list_.count(vertex) > 0;
}

int WeightedGraph::vertex_count() const {
    return static_cast<int>(adj_list_.size());
}

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

    // 1. Initialize all distances to "infinity"
    for (const auto& [vertex, edges] : adj_list_) {
        dist[vertex] = std::numeric_limits<int>::max();
    }
    if (!has_vertex(source)) return dist;
    dist[source] = 0;

    // 2. Min-heap of (distance, vertex) pairs
    using Pair = std::pair<int, std::string>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    pq.push({0, source});

    // 3. Main loop: pop closest unfinalized vertex, relax its edges
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;  // stale entry, skip

        for (const auto& edge : adj_list_.at(u)) {
            const int new_dist = dist[u] + edge.weight;
            if (new_dist < dist[edge.to]) {
                dist[edge.to] = new_dist;
                pq.push({new_dist, edge.to});
            }
        }
    }
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

    if (!has_vertex(start)) return {mst_edges, total_weight};

    // 1. Start with 'start' in the MST set
    std::unordered_set<std::string> in_mst;
    in_mst.insert(start);

    // 2. Min-heap of (weight, from, to) tuples
    using EdgeTuple = std::tuple<int, std::string, std::string>;
    std::priority_queue<EdgeTuple, std::vector<EdgeTuple>, std::greater<EdgeTuple>> pq;

    // 3. Seed the frontier with every edge leaving 'start'
    for (const auto& edge : adj_list_.at(start)) {
        pq.push({edge.weight, start, edge.to});
    }

    const int V = vertex_count();

    // 4. Grow the MST until it contains every vertex
    while (!pq.empty() && static_cast<int>(in_mst.size()) < V) {
        auto [w, from, to] = pq.top();
        pq.pop();

        if (in_mst.count(to)) continue;  // cycle — to is already in the tree

        mst_edges.push_back({from, to, w});
        total_weight += w;
        in_mst.insert(to);

        // push every crossing edge from the newly added vertex
        for (const auto& edge : adj_list_.at(to)) {
            if (!in_mst.count(edge.to)) {
                pq.push({edge.weight, to, edge.to});
            }
        }
    }

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
