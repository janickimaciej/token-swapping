#pragma once

#include <utility>
#include <vector>

namespace TokenSwapping
{
	class Instance
	{
	public:
		Instance(int power, std::vector<int> tokens);
		Instance(int power, const Instance& instance);

		int power() const;
		int size() const;
		int operator[](int index) const;
		bool isSolved() const;
		bool isSolution(const std::vector<std::pair<int, int>>& solution) const;
		bool operator==(const Instance& instance) const;

		void swap(int firstIndex, int secondIndex);
		void swap(const std::pair<int, int>& move);

	private:
		int m_power;
		std::vector<int> m_tokens;

		void error(const char* msg) const;
	};
};
