#ifndef INCLUDE_FIND_BRIDGES_HPP_
#define INCLUDE_FIND_BRIDGES_HPP_

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace graph {

template <typename Graph>
class FindBridgesAlgorithm {
 private:
  size_t timer;
  std::unordered_set<size_t> used;
  std::unordered_map<size_t, size_t> tin;
  std::unordered_map<size_t, size_t> fup;
  std::vector<std::pair<size_t, size_t>> bridges;

  void Dfs(size_t v, size_t p, bool has_parent, const Graph& graph) {
    used.insert(v);
    tin[v] = fup[v] = timer++;
    for (size_t to : graph.IncomingEdges(v)) {
      if (has_parent && to == p) {
        continue;
      }
      if (used.find(to) != used.end()) {
        fup[v] = std::min(fup[v], tin[to]);
      } else {
        Dfs(to, v, true, graph);
        fup[v] = std::min(fup[v], fup[to]);
        if (fup[to] > tin[v]) {
          bridges.push_back({std::min(v, to), std::max(v, to)});
        }
      }
    }
  }

 public:
  std::vector<std::pair<size_t, size_t>> FindBridges(const Graph& graph) {
    timer = 0;
    used.clear();
    tin.clear();
    fup.clear();
    bridges.clear();

    for (size_t i : graph.Vertices()) {
      if (used.find(i) == used.end()) {
        Dfs(i, 0, false, graph);
      }
    }
    return bridges;
  }
};

}  // namespace graph

#endif  // INCLUDE_FIND_BRIDGES_HPP_
