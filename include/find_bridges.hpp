#ifndef INCLUDE_FIND_BRIDGES_HPP_
#define INCLUDE_FIND_BRIDGES_HPP_

#include <algorithm>
#include <utility>
#include <vector>

template <typename Graph>
class FindBridgesAlgorithm {
 private:
  int timer;
  std::vector<bool> used;
  std::vector<int> tin;
  std::vector<int> fup;
  std::vector<std::pair<int, int>> bridges;

  void Dfs(int v, int p, const Graph& graph) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (int to : graph[v]) {
      if (to == p) {
        continue;
      }
      if (used[to]) {
        fup[v] = std::min(fup[v], tin[to]);
      } else {
        Dfs(to, v, graph);
        fup[v] = std::min(fup[v], fup[to]);
        if (fup[to] > tin[v]) {
          bridges.push_back({std::min(v, to), std::max(v, to)});
        }
      }
    }
  }

 public:
  std::vector<std::pair<int, int>> FindBridges(const Graph& graph) {
    int n = graph.size();
    timer = 0;
    used.assign(n, false);
    tin.assign(n, -1);
    fup.assign(n, -1);
    bridges.clear();

    for (int i = 0; i < n; ++i) {
      if (!used[i]) {
        Dfs(i, -1, graph);
      }
    }
    return bridges;
  }
};

#endif  // INCLUDE_FIND_BRIDGES_HPP_
