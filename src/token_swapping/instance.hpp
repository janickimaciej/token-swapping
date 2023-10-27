#pragma once

#include <vector>

namespace TokenSwapping
{
	class Instance
	{
	public:
		Instance(int power, std::vector<int> tokens);

		int get(int index) const;
		bool swap(int firstIndex, int secondIndex);
		bool isSolved() const;

	private:
		int m_power;
		std::vector<int> m_tokens;

		void error(const char* msg) const;
	};
};
