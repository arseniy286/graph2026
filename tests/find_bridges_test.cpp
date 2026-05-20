#include <cassert>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

#include "test.hpp"
#include "../include/find_bridges.hpp"

void TestFindBridges() {
  FindBridgesAlgorithm<std::vector<std::vector<int>>> algorithm;

  std::vector<std::vector<int>> graph1 = {
    {1, 2}, {0, 2}, {0, 1, 3}, {2, 4, 5}, {3, 5}, {3, 4}
  };
  std::vector<std::pair<int, int>> bridges1 = algorithm.FindBridges(graph1);
  assert(bridges1.size() == 1);
  assert(bridges1[0].first == 2 && bridges1[0].second == 3);

  int n = 10 + std::rand() % 90;
  std::vector<std::vector<int>> graph2(n);
  for (int i = 1; i < n; ++i) {
    int parent = std::rand() % i;
    graph2[i].push_back(parent);
    graph2[parent].push_back(i);
  }
  std::vector<std::pair<int, int>> bridges2 = algorithm.FindBridges(graph2);
  assert(bridges2.size() == static_cast<size_t>(n - 1));

  std::cout << "FindBridges tests passed.\n";
}
