# CT18 -- Header Diagrams

Conceptual diagrams referenced from `WeightedGraph.h`.

---

## 1. Weighted Graph
*`WeightedGraph.h` -- edges have numeric costs; enables shortest path and MST algorithms*

![Weighted Graph](svgs/weighted_graph.svg)

---

## 1b. Weighted Graph -- What Can You Query From Source A?
*What the `WeightedGraph` class alone answers (direct edge costs) vs. what needs an algorithm (multi-hop shortest paths) -- bridges into Dijkstra's*

![Weighted Graph Query](svgs/weighted_graph_query.svg)

---

## 1c. Multi-Hop Cost From Source A -- The Final Result
*What the answer table actually looks like for a single source -- shows the cheapest route to every vertex (direct or multi-hop), motivating why fewest-edges is not the same as lowest-cost*

![Weighted Graph Multi-Hop](svgs/weighted_graph_multihop.svg)

---

## 2. Dijkstra's Algorithm
*`WeightedGraph.h::dijkstra()` -- greedy shortest path using priority queue*

![Dijkstra's](svgs/dijkstra_overview.svg)

---

## 2b. Dijkstra's Algorithm — Step-by-Step Trace
*Tracing `dijkstra("A")` on the example graph, including the relaxation formula and heap pushes*

![Dijkstra's Trace](svgs/dijkstra_trace.svg)

---

## 2c. Dijkstra's Algorithm — Shortest Path Tree Result
*The resulting shortest path tree from A, path reconstructions, and key facts (V−1 edges, negative-weight limitation, greedy property)*

![Dijkstra's Result](svgs/dijkstra_result.svg)

---

## 2d. Dijkstra's vs Prim's — Comparison
*Side-by-side: same graph, same min-heap approach, different questions — shortest paths vs minimum spanning tree*

![Dijkstra's vs Prim's](svgs/dijkstra_vs_prims.svg)

---

## 2e. Dijkstra's vs Prim's — Different Trees Example
*A graph where Dijkstra's and Prim's produce different trees — Dijkstra must use the expensive A—B(10) direct edge, but Prim's skips it for the cheap D—B(1)*

![Different Trees](svgs/dijkstra_vs_prims_different.svg)

---

## 3. Prim's MST
*`WeightedGraph.h::prims_mst()` -- grow the cheapest spanning tree one edge at a time*

![Prim's MST](svgs/prims_overview.svg)

---

## 3b. Prim's MST — Step-by-Step Trace
*Tracing `prims_mst("A")` on the example graph, including heap pops, MST-set growth, and the cycle-skip rule*

![Prim's Trace](svgs/prims_trace.svg)

---

## 3c. Prim's MST — MST Result
*The resulting minimum spanning tree from A, edge list with total weight, excluded edges, and key facts (cut property, negative weights OK)*

![Prim's Result](svgs/prims_result.svg)
