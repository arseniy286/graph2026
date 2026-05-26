#include <utility>
#include <vector>

#include <nlohmann/json.hpp>

#include "methods.hpp"
#include "../include/find_bridges.hpp"
#include "../include/graph.hpp"

namespace graph {

int FindBridgesMethod(const nlohmann::json& input, nlohmann::json* output) {
  if (!input.contains("graph") || !input["graph"].is_array()) {
    (*output)["error"] = "Invalid input format: missing graph array";
    return -1;
  }

  Graph graph_data;
  std::vector<std::vector<size_t>> json_graph =
      input["graph"].get<std::vector<std::vector<size_t>>>();

  for (size_t i = 0; i < json_graph.size(); ++i) {
    graph_data.AddVertex(i);
    for (size_t neighbor : json_graph[i]) {
      graph_data.AddVertex(neighbor);
      graph_data.AddEdge(i, neighbor);
    }
  }

  FindBridgesAlgorithm<Graph> algorithm;
  std::vector<std::pair<size_t, size_t>> bridges =
      algorithm.FindBridges(graph_data);

  (*output)["bridges"] = bridges;
  return 0;
}

}  // namespace graph
