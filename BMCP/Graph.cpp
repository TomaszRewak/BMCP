// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include "Graph.h"

namespace BMCP
{
	Node::Node() :
		weight(0)
	{}

	Node::Node(size_t weight) :
		weight(weight)
	{}

	OneWayEdge::OneWayEdge(size_t node, size_t weight) :
		weight(weight),
		node(node)
	{}

	Edge::Edge(size_t nodeA, size_t nodeB, size_t weight) :
		weight(weight),
		nodeA(nodeA),
		nodeB(nodeB)
	{}

	Graph::Graph() :
		slots(0)
	{ }

	size_t Graph::nodesCount() { return nodes.size(); }
	size_t Graph::edgesCount() { return edges.size(); }

	std::istream& operator >> (std::istream& stream, Graph& graph)
	{
		while (!stream.eof()) {
			char command;
			stream >> command;

			if (stream.eof())
				return stream;

			switch (command)
			{
			case 'c': {
				std::string comment;
				std::getline(stream, comment);
				break;
			}
			case 'p': {
				std::string band;
				size_t nodesCount, edgesCount;
				stream >> band >> nodesCount >> edgesCount;

				graph.nodes.resize(nodesCount);
				graph.neighbours.resize(nodesCount);
				graph.edges.reserve(edgesCount);

				break;
			}
			case 'e': {
				size_t begin, end, weight;
				stream >> begin >> end >> weight;
				begin--;
				end--;

				graph.edges.push_back(Edge(begin, end, weight));
				graph.neighbours[begin].push_back(OneWayEdge(end, weight));
				graph.neighbours[end].push_back(OneWayEdge(begin, weight));

				break;
			}
			case 'n': {
				size_t node, weight;
				stream >> node >> weight;
				node--;
				graph.nodes[node] = Node(weight);
				graph.slots += weight;
			}
			default:
				break;
			}
		}

		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, Graph& graph) {
		stream << "Nodes:" << std::endl;
		for (size_t i = 0; i < graph.nodesCount(); i++) {
			Node& node = graph.nodes[i];
			stream << node.weight << std::endl;
		}

		stream << "Edges:" << std::endl;
		for (size_t i = 0; i < graph.edgesCount(); i++) {
			Edge& edge = graph.edges[i];
			stream << edge.nodeA << "-" << edge.nodeB << ": " << edge.weight << std::endl;
		}

		return stream;
	}
}