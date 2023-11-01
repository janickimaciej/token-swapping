#pragma once

#include <vector>

namespace TokenSwapping
{
	class Instance
	{
	public:
		Instance(int power, std::vector<int> tokens);

		int power() const;
		int size() const;
		int operator[](int index) const;
		bool isSolved() const;
		bool operator==(const Instance& instance) const;

		bool swap(int firstIndex, int secondIndex);

	private:
		int m_power;
		std::vector<int> m_tokens;

		void error(const char* msg) const;
	};
};
