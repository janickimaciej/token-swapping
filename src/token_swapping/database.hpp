#pragma once

#include "token_swapping/instance.hpp"

#include <fstream>
#include <string>

namespace TokenSwapping
{
	class Database
	{
	public:
		Database(int power, int size);
		void generate();
		int optimalSolutionLength(const Instance& instance);
		void operator()(const Instance& instance);

	private:
		int m_power;
		int m_size;
		int m_fieldWidth{};
		std::ofstream m_oFile{};
		std::ifstream m_iFile{};

		std::string path() const;
		void error(const char* msg) const;
	};
};
