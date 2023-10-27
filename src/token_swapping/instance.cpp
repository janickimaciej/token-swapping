#include "token_swapping/instance.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace TokenSwapping
{
	Instance::Instance(int power, std::vector<int> tokens) :
		m_power{power},
		m_tokens{tokens}
	{
		if (power <= 0 || power >= tokens.size())
		{
			error("Instance::Instance: Invalid power");
		}
		std::sort(tokens.begin(), tokens.end());
		for (int i = 0; i < tokens.size(); i++)
		{
			if (tokens[i] != i)
			{
				error("Instance::Instance: Invalid instance");
			}
		}
	}

	int Instance::size() const
	{
		return m_tokens.size();
	}

	int Instance::operator[](int index) const
	{
		if (index < 0 || index >= m_tokens.size())
		{
			error("Instance::get: Index out of bounds");
		}

		return m_tokens[index];
	}

	bool Instance::isSolved() const
	{
		for (int i = 0; i < m_tokens.size(); i++)
		{
			if (m_tokens[i] != i)
			{
				return false;
			}
		}
		return true;
	}

	bool Instance::swap(int firstIndex, int secondIndex)
	{
		if (firstIndex < 0 || secondIndex < 0 || firstIndex >= m_tokens.size() ||
			secondIndex >= m_tokens.size())
		{
			error("Instance::swap: Index out of bounds");
		}
		if (firstIndex == secondIndex)
		{
			error("Instance::swap: Indices are equal");
		}
		if (std::abs(firstIndex - secondIndex) > m_power)
		{
			error("Instance::swap: Vertices are too far from each other");
		}

		int tmp = m_tokens[firstIndex];
		m_tokens[firstIndex] = m_tokens[secondIndex];
		m_tokens[secondIndex] = tmp;
		return true;
	}

	void Instance::error(const char* msg) const
	{
		std::cerr << std::endl << msg << std::endl;
		throw std::invalid_argument(msg);
	}
};
