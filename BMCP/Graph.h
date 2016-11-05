// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include <vector>
#include <istream>
#include <ostream>
#include <string>

namespace BMCP
{
	class Node {
	public:
		int weight;

		Node();
		Node(size_t weight);
	};

	class OneWayEdge {
	public:
		int weight;
		int node;

		OneWayEdge(size_t node, size_t weight);
	};

	class Edge {
	public:
		int weight;
		int nodeA, nodeB;

		Edge(size_t nodeA, size_t nodeB, size_t weight);
	};

	class Graph {
	public:
		int slots;

		std::vector<Node> nodes;
		std::vector<Edge> edges;
		std::vector<std::vector<OneWayEdge>> neighbours;

		size_t nodesCount();
		size_t edgesCount();

		Graph();

		friend std::istream& operator>>(std::istream& stream, Graph& graph);
		friend std::ostream& operator<<(std::ostream& stream, Graph& graph);
	};

	std::istream& operator>>(std::istream& stream, Graph& graph);
	std::ostream& operator<<(std::ostream& stream, Graph& graph);
}