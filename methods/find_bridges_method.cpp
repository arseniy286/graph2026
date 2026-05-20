#include <utility>
#include <vector>

#include <nlohmann/json.hpp>

#include "methods.hpp"
#include "../include/find_bridges.hpp"

namespace graph {

int FindBridgesMethod(const nlohmann::json& input, nlohmann::json* output) {
  if (!input.contains("graph") || !input["graph"].is_array()) {
    (*output)["error"] = "Invalid input format: missing graph array";
    return -1;
  }

  std::vector<std::vector<int>> graph_data =
      input["graph"].get<std::vector<std::vector<int>>>();

  FindBridgesAlgorithm<std::vector<std::vector<int>>> algorithm;
  std::vector<std::pair<int, int>> bridges = algorithm.FindBridges(graph_data);

  (*output)["bridges"] = bridges;
  return 0;
}

}  // namespace graph
