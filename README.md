# CT18 -- Shortest Path & Minimum Spanning Tree

## Overview

An in-class code-together activity extending the adjacency-list graph from CT17 to **weighted** graphs, then implementing **Dijkstra's algorithm** for shortest paths. Students store edges as `Edge` structs (destination + weight), implement `add_edge` for the weighted undirected case, and then build Dijkstra's step by step: distance map, min-heap priority queue, stale-entry skip, and edge relaxation. Prim's MST algorithm is provided as an instructor-led walkthrough (CCD 2.12 is lecture-only) so students see the same priority-queue pattern solving a different problem.

## Learning Objectives

- Explain why **BFS doesn't work** on weighted graphs and why weighted shortest path needs a different algorithm
- Implement `add_edge` for a **weighted undirected** adjacency list (push `Edge{to, weight}` on both sides)
- Implement **Dijkstra's algorithm** using a `std::priority_queue` as a min-heap via `std::greater<Pair>`
- Explain the **relaxation step** -- when `dist[u] + edge.weight < dist[v]`, update `dist[v]` and push a new heap entry
- Explain why **stale heap entries** occur (no decrease-key) and why `if (d > dist[u]) continue;` is the standard fix
- Read Prim's MST walkthrough and explain how the **same priority-queue pattern** minimizes total edge weight instead of source distance

## Project Structure

```
ct18-shortest-path-mst/
├── CMakeLists.txt
├── assignment.json
├── README.md
├── include/
│   └── WeightedGraph.h         # Edge struct + class declaration
├── src/
│   ├── WeightedGraph.cpp       # add_edge and dijkstra are TODOs; prims_mst is provided
│   └── main.cpp                # Demo: city map, Dijkstra from SLC, Prim's MST from SLC
├── tests/
│   └── ct18_test.cpp           # Google Test suite (30 points; Dijkstra = 21)
└── images/
    ├── header_diagrams.md      # Concept diagrams referenced from WeightedGraph.h
    ├── cpp_diagrams.md         # Implementation diagrams referenced from WeightedGraph.cpp
    └── svgs/                   # All SVGs (weighted graph, dijkstra, prims)
```

## What You'll Do

Open `WeightedGraph.cpp`. The constructor, queries, and `add_vertex` are already implemented -- identical to CT17's `Graph`. Your three tasks are `add_edge` (Section 2), `dijkstra` (Section 4), and reading through the provided `prims_mst` (Section 5) while the instructor walks it in class. After each TODO, run `main.cpp` to verify the city-map demo output, then re-run the test suite to watch the Dijkstra points come in.

## Files

| File | Focus | TODOs |
|---|---|---|
| `WeightedGraph.cpp` | add_edge and dijkstra | 2 (add_edge body, dijkstra body) |
| `main.cpp` | Demo: city map, Dijkstra from SLC, Prim's MST | 0 (run as-is to verify output) |

## Teaching Order

### 1. `WeightedGraph.h` -- Review the weighted interface

Walk through the header. Highlight the `Edge` struct (destination + weight) and contrast `adj_list_` -- it's now `unordered_map<string, vector<Edge>>` instead of CT17's `vector<string>`. Point out the two new method signatures: `dijkstra` returns a distance map and `prims_mst` returns a tuple vector + total weight.

### 2. `WeightedGraph.cpp` -- Two student TODOs + one provided walkthrough

1. **Section 2: add_edge** -- ensure both vertices exist, push `Edge{to, weight}` into `from`'s list and `Edge{from, weight}` into `to`'s list (undirected)
2. **Section 4: dijkstra** -- full 10-step implementation: dist map, guard, source seed, type alias, min-heap with `std::greater`, main loop, stale-entry skip, relaxation
3. **Section 5: prims_mst** (provided) -- instructor walks the tuple-based min-heap, cycle skip, and frontier growth using the Prim's SVGs; students read but don't type

### 3. `main.cpp` -- City map demo (3 sections)

1. **Section 1: Build weighted graph** -- SLC, Ogden, Provo, Logan with 5 edges; `print()` shows the adjacency list with weights
2. **Section 2: Dijkstra from SLC** -- verify `SLC=0, Ogden=4, Logan=3, Provo=5` (SLC->Logan->Provo = 3+2 beats direct SLC->Provo = 6)
3. **Section 3: Prim's MST from SLC** -- verify SLC-Logan(3), Logan-Provo(2), SLC-Ogden(4), total weight 9

## Diagrams

| File | Description |
|---|---|
| `images/svgs/weighted_graph.svg` | Weighted adjacency list with Edge{to, weight} pairs |
| `images/svgs/dijkstra_overview.svg` | Step-by-step Dijkstra trace from source on the city map |
| `images/svgs/dijkstra_impl_setup.svg` | dijkstra() implementation: dist map, guard, source seed, min-heap declaration |
| `images/svgs/dijkstra_impl_loop.svg` | dijkstra() main loop: pop, stale skip, relaxation, push |
| `images/svgs/dijkstra_stale_skip.svg` | Why `if (d > dist[u]) continue;` -- a stale heap entry example |
| `images/svgs/dijkstra_code_trace.svg` | Full trace of dijkstra("A") on a 5-vertex graph: heap pops, relaxation checks, dist updates |
| `images/svgs/prims_impl_setup.svg` | prims_mst() setup: in_mst seed, tuple min-heap, frontier seeding |
| `images/svgs/prims_impl_loop.svg` | prims_mst() main loop: pop cheapest, cycle skip, accept, grow frontier |
| `images/svgs/dijkstra_vs_prims.svg` | Side-by-side comparison: same priority-queue pattern, different goals |

## Grading (30 points)

| Category | Points | What is tested |
|---|---|---|
| Build | 0 | Project must compile (tests won't run otherwise) |
| Constructor | 2 | Empty graph has zero vertices and zero edges |
| add_edge | 7 | Creates both endpoints; full graph has correct vertex and edge counts |
| Dijkstra -- source distance | 3 | `dist[source] == 0` |
| Dijkstra -- direct edge | 4 | Direct neighbors get their edge weight as distance |
| Dijkstra -- relaxation | 6 | Shorter multi-hop path replaces longer direct edge |
| Dijkstra -- reachability | 4 | All reachable vertices appear in the result map |
| Dijkstra -- single vertex | 4 | Isolated vertex returns `{source: 0}` with no crash |
