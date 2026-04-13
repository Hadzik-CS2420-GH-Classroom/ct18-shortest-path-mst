#include <gtest/gtest.h>
#include "WeightedGraph.h"
#include <unordered_set>

// =============================================================================
// Helper: build the standard test graph
// =============================================================================
//     A ---4--- B
//     |  \      |
//     6   3     5
//     |    \    |
//     C ---2--- D
//
static WeightedGraph build_test_graph() {
    WeightedGraph g;
    g.add_edge("A", "B", 4);
    g.add_edge("A", "C", 6);
    g.add_edge("A", "D", 3);
    g.add_edge("B", "D", 5);
    g.add_edge("C", "D", 2);
    return g;
}

// =============================================================================
// Constructor / add
// =============================================================================

TEST(WGraphConstructor, Empty) {
    WeightedGraph g;
    EXPECT_EQ(g.vertex_count(), 0);
    EXPECT_EQ(g.edge_count(), 0);
}

TEST(WGraphAdd, EdgeCreatesVertices) {
    WeightedGraph g;
    g.add_edge("X", "Y", 10);
    EXPECT_TRUE(g.has_vertex("X"));
    EXPECT_TRUE(g.has_vertex("Y"));
    EXPECT_EQ(g.vertex_count(), 2);
    EXPECT_EQ(g.edge_count(), 1);
}

TEST(WGraphAdd, FullGraph) {
    WeightedGraph g = build_test_graph();
    EXPECT_EQ(g.vertex_count(), 4);
    EXPECT_EQ(g.edge_count(), 5);
}

// =============================================================================
// Dijkstra's
// =============================================================================

TEST(Dijkstra, SourceDistanceZero) {
    WeightedGraph g = build_test_graph();
    auto dist = g.dijkstra("A");
    EXPECT_EQ(dist["A"], 0);
}

TEST(Dijkstra, DirectEdge) {
    WeightedGraph g = build_test_graph();
    auto dist = g.dijkstra("A");
    // A->B direct = 4, A->D direct = 3
    EXPECT_EQ(dist["B"], 4);
    EXPECT_EQ(dist["D"], 3);
}

TEST(Dijkstra, ShortestViaShorterPath) {
    WeightedGraph g = build_test_graph();
    auto dist = g.dijkstra("A");
    // A->C direct = 6, but A->D->C = 3+2 = 5 (shorter!)
    EXPECT_EQ(dist["C"], 5);
}

TEST(Dijkstra, AllVerticesReachable) {
    WeightedGraph g = build_test_graph();
    auto dist = g.dijkstra("A");
    EXPECT_EQ(dist.size(), 4);
}

TEST(Dijkstra, SingleVertex) {
    WeightedGraph g;
    g.add_vertex("X");
    auto dist = g.dijkstra("X");
    EXPECT_EQ(dist.size(), 1);
    EXPECT_EQ(dist["X"], 0);
}

// =============================================================================
// Prim's MST
// =============================================================================

TEST(PrimsMST, CorrectEdgeCount) {
    WeightedGraph g = build_test_graph();
    auto [edges, total] = g.prims_mst("A");
    // MST has V-1 = 3 edges
    EXPECT_EQ(edges.size(), 3);
}

TEST(PrimsMST, MinimumTotalWeight) {
    WeightedGraph g = build_test_graph();
    auto [edges, total] = g.prims_mst("A");
    // Cheapest spanning tree: A-D(3) + D-C(2) + A-B(4) = 9
    EXPECT_EQ(total, 9);
}

TEST(PrimsMST, AllVerticesConnected) {
    WeightedGraph g = build_test_graph();
    auto [edges, total] = g.prims_mst("A");
    std::unordered_set<std::string> vertices;
    for (const auto& [from, to, w] : edges) {
        vertices.insert(from);
        vertices.insert(to);
    }
    EXPECT_EQ(vertices.size(), 4);
}

TEST(PrimsMST, SingleVertex) {
    WeightedGraph g;
    g.add_vertex("X");
    auto [edges, total] = g.prims_mst("X");
    EXPECT_EQ(edges.size(), 0);
    EXPECT_EQ(total, 0);
}
