// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include <memory>
#include <vector>

namespace TabuSearch {
	class TabuElementNode {
	public:
		int next = 0;
		int child = 0;

		int previous = 0;
		int parent = 0;

		int value;
		long long generation;

		TabuElementNode();

		TabuElementNode(int color, int previous, int parent, long long generation);
	};

	class Tabu {
	private:
		int maxSize;
		std::shared_ptr<std::vector<TabuElementNode>> bufferedElements;

	public:
		int maxDiff;

		int attempts = 0;
		int failures = 0;

		Tabu(int maxSize, int maxDiff);

		void insert(std::vector<int> &element, long long generation);
		bool isUnique(std::vector<int> &element);

	private:
		bool isUnique(std::vector<int> &element, int elemIndex, int tabuIndex, int diff);

		void removeTheOldest();
		int removeNode(int nodeIndex, int newIndex);
	};
}