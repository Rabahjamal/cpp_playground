#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <queue>
#include <map>

namespace Dijkstra
{
template <class T>
using Queue = std::priority_queue<std::pair<int, T>,
                                  std::vector<std::pair<int, T>>,
                                  std::greater<std::pair<int, T>>>;

template <typename T>
void initialize_all_nodes(const std::map<T, std::vector<std::pair<T, int>>>& graph,
                          std::map<T, int>& shortest_distance,
                          T start_node)
{
    shortest_distance[start_node] = 0;
    for(const auto& node : graph)
    {
        if(node.first != start_node)
        {
            shortest_distance[node.first] = std::numeric_limits<int>::max();
        }
    }
}

template <typename T>
int
find_shortest_path(const std::map<T, std::vector<std::pair<T, int>>>& graph,
                   T start_node,
                   T end_node)
{
    Queue<T> q;

    std::map<T, int> shortest_distance;
    std::map<T, T> prv_nodes;

    initialize_all_nodes(graph, shortest_distance, start_node);

    q.push({0, start_node});

    while(!q.empty())
    {
        auto top = q.top();
        q.pop();

        int current_distance = top.first;
        T current_node = top.second;

        for(const auto& neighbour : graph.at(current_node))
        {
            T node_val = neighbour.first;
            int edge_val = neighbour.second;
            int new_distance = current_distance + edge_val;

            if(new_distance< shortest_distance[node_val])
            {
                shortest_distance[node_val] = new_distance;
                prv_nodes[node_val] = current_node;
                q.push({new_distance, node_val});
            }
        }
    }


    return shortest_distance[end_node];

}

}

#endif // DIJKSTRA_H
