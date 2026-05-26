#include <cassert>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

#include "test.hpp"
#include "../include/find_bridges.hpp"
#include "../include/graph.hpp"

void TestFindBridges() {
  graph::FindBridgesAlgorithm<graph::Graph> algorithm;

  graph::Graph graph1;
  for (size_t i = 0; i < 6; ++i) {
    graph1.AddVertex(i);
  }
  graph1.AddEdge(0, 1);
  graph1.AddEdge(0, 2);
  graph1.AddEdge(1, 2);
  graph1.AddEdge(2, 3);
  graph1.AddEdge(3, 4);
  graph1.AddEdge(3, 5);
  graph1.AddEdge(4, 5);

  std::vector<std::pair<size_t, size_t>> bridges1 =
      algorithm.FindBridges(graph1);
  assert(bridges1.size() == 1);
  assert((bridges1[0].first == 2 && bridges1[0].second == 3) ||
         (bridges1[0].first == 3 && bridges1[0].second == 2));

  graph::Graph graph2;
  int n = 10 + std::rand() % 90;
  std::vector<size_t> vertices;
  for (int i = 0; i < n; ++i) {
    size_t v_id = static_cast<size_t>(std::rand() % 1000000);
    graph2.AddVertex(v_id);
    vertices.push_back(v_id);
  }

  for (int i = 1; i < n; ++i) {
    int parent = std::rand() % i;
    graph2.AddEdge(vertices[i], vertices[parent]);
  }

  std::vector<std::pair<size_t, size_t>> bridges2 =
      algorithm.FindBridges(graph2);
  assert(bridges2.size() == static_cast<size_t>(n - 1));

  std::cout << "FindBridges tests passed.\n";
}
