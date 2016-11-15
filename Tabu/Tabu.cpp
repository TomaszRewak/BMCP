// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include <algorithm>

#include "Tabu.h"

namespace TabuSearch {

	TabuElementNode::TabuElementNode() :
		value(INT_MIN),
		generation(0)
	{}

	TabuElementNode::TabuElementNode(int color, int previous, int parent, long long generation) :
		value(color),
		previous(previous),
		parent(parent),
		generation(generation)
	{}


	Tabu::Tabu(int maxSize, int maxDiff) :
		maxSize(maxSize),
		maxDiff(maxDiff)
	{
		bufferedElements = std::make_shared<std::vector<TabuElementNode>>();
		bufferedElements->reserve(maxSize);
		bufferedElements->push_back(TabuElementNode());
		bufferedElements->push_back(TabuElementNode());
	}

	bool Tabu::isUnique(std::vector<int> &element, int elemIndex, int tabuIndex, int diff)
	{
		if (diff > maxDiff)
			return true;

		if (elemIndex >= element.size())
			return false;

		if (!tabuIndex)
			throw "Tabu buffer error";

		for (; tabuIndex; tabuIndex = bufferedElements->at(tabuIndex).next)
			if (!isUnique(element, elemIndex + 1, bufferedElements->at(tabuIndex).child, diff + std::abs(element[elemIndex] - bufferedElements->at(tabuIndex).value)))
				return false;

		return true;
	}

	bool Tabu::isUnique(std::vector<int> &element)
	{
		int first = bufferedElements->at(1).next;

		if (!first || isUnique(element, 0, first, 0))
			return true;
		else
			return false;
	}

	void Tabu::insert(std::vector<int> &element, long long generation)
	{
		std::vector<TabuElementNode>& buffer = *bufferedElements;

		while (buffer.size() + element.size() > maxSize)
			removeTheOldest();

		int nodeIndex = 1;

		bool unique = false;

		for (auto value : element) {
			if (unique) {
				buffer[nodeIndex].child = buffer.size();
				buffer.push_back(TabuElementNode(value, 0, nodeIndex, generation));
				nodeIndex = buffer.size() - 1;
			}
			else {
				while (buffer[nodeIndex].value != value && buffer[nodeIndex].next)
					nodeIndex = buffer[nodeIndex].next;

				if (buffer[nodeIndex].value != value) {
					buffer[nodeIndex].next = buffer.size();
					buffer.push_back(TabuElementNode(value, nodeIndex, 0, generation));
					nodeIndex = buffer.size() - 1;
					unique = true;
				}
				else {
					nodeIndex = buffer[nodeIndex].child;
				}
			}
		}
	}

	void Tabu::removeTheOldest()
	{
		std::vector<TabuElementNode>& buffer = *bufferedElements;

		long long oldestGeneration = LLONG_MAX;

		for (int i = 1; i; i = buffer[i].next)
			oldestGeneration = std::min(oldestGeneration, buffer[i].generation);

		int nodeIndex = 1;

		while (buffer[nodeIndex].generation != oldestGeneration || buffer[nodeIndex].generation == oldestGeneration && buffer[nodeIndex].child)
		{
			if (buffer[nodeIndex].generation != oldestGeneration)
				nodeIndex = buffer[nodeIndex].next;
			else
				nodeIndex = buffer[nodeIndex].child;
		}

		bool remove = true;

		while (nodeIndex)
		{
			if (remove)
			{
				if (buffer[nodeIndex].previous || buffer[nodeIndex].next)
					remove = false;

				int nextNodeIndex = nodeIndex;
				while (buffer[nextNodeIndex].previous)
					nextNodeIndex = buffer[nextNodeIndex].previous;
				nextNodeIndex = buffer[nextNodeIndex].parent;

				nodeIndex = removeNode(nodeIndex, nextNodeIndex);
			}
			else
			{
				oldestGeneration = LLONG_MAX;

				for (int i = buffer[nodeIndex].child; i; i = buffer[i].next)
					oldestGeneration = std::min(oldestGeneration, buffer[i].generation);

				buffer[nodeIndex].generation = oldestGeneration;

				while (buffer[nodeIndex].previous)
					nodeIndex = buffer[nodeIndex].previous;
				nodeIndex = buffer[nodeIndex].parent;
			}
		}
	}

	int Tabu::removeNode(int nodeIndex, int newIndex)
	{
		std::vector<TabuElementNode>& buffer = *bufferedElements;

		if (buffer[nodeIndex].previous)
			buffer[buffer[nodeIndex].previous].next = buffer[nodeIndex].next;
		if (buffer[nodeIndex].next)
			buffer[buffer[nodeIndex].next].previous = buffer[nodeIndex].previous;
		if (buffer[nodeIndex].parent)
		{
			buffer[buffer[nodeIndex].parent].child = buffer[nodeIndex].next;
			buffer[buffer[nodeIndex].next].parent = buffer[nodeIndex].parent;
		}

		if (nodeIndex != buffer.size() - 1)
		{
			buffer[nodeIndex] = buffer[buffer.size() - 1];

			if (buffer[nodeIndex].previous)
				buffer[buffer[nodeIndex].previous].next = nodeIndex;
			if (buffer[nodeIndex].next)
				buffer[buffer[nodeIndex].next].previous = nodeIndex;
			if (buffer[nodeIndex].parent)
				buffer[buffer[nodeIndex].parent].child = nodeIndex;
			if (buffer[nodeIndex].child)
				buffer[buffer[nodeIndex].child].parent = nodeIndex;
		}

		buffer.resize(buffer.size() - 1);

		return newIndex == buffer.size() ? nodeIndex : newIndex;
	}
}