# CT18 -- Implementation Diagrams

Code-block diagrams referenced from `WeightedGraph.cpp`.

---

## 1. add_edge() — Weighted Undirected Edge
*`WeightedGraph.cpp::add_edge()` -- push `Edge{to, weight}` into both neighbor lists*

![add_edge](svgs/add_edge_impl.svg)

---

## 2. dijkstra() — Min-Heap Shortest Path
*`WeightedGraph.cpp::dijkstra()` -- init distances, relax edges through a min-heap until empty*

**Part 1: Setup** — declare `dist`, initialize to infinity, guard, seed source, build min-heap, seed heap.

![Dijkstra Setup](svgs/dijkstra_impl_setup.svg)

**Part 2: Main Loop** — pop closest vertex, skip stale entries, walk every outgoing edge and relax it step by step.

![Dijkstra Main Loop](svgs/dijkstra_impl_loop.svg)

---

## 2a. dijkstra() — Stale Entry Skip Breakdown
*`WeightedGraph.cpp::dijkstra()` -- why `if (d > dist[u]) continue;` is needed and what a "stale" heap entry looks like*

![Dijkstra Stale Skip](svgs/dijkstra_stale_skip.svg)

---

## 2b. dijkstra() — Code Execution Trace
*`WeightedGraph.cpp::dijkstra()` -- tracing dijkstra("A") step by step: heap pops, relaxation checks, dist updates*

![Dijkstra Code Trace](svgs/dijkstra_code_trace.svg)

---

## 3. prims_mst() — Min-Heap MST Growth
*`WeightedGraph.cpp::prims_mst()` -- grow MST one vertex at a time by popping the cheapest crossing edge*

**Part 1: Setup** — seed the MST set with `start`, build the min-heap of edge tuples, seed the frontier with every edge leaving `start`.

![Prim's Setup](svgs/prims_impl_setup.svg)

**Part 2: Main Loop** — pop cheapest edge, skip cycles, accept the edge (record + total + mark), grow the frontier.

![Prim's Main Loop](svgs/prims_impl_loop.svg)

---

## 3b. prims_mst() — Code Execution Trace
*`WeightedGraph.cpp::prims_mst()` -- tracing prims_mst("A") step by step: heap pops, cycle-skips, MST growth*

![Prim's Code Trace](svgs/prims_code_trace.svg)
