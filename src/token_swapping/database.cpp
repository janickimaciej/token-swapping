#include "token_swapping/database.hpp"

#include "token_swapping/brute_force_sort.hpp"
#include "token_swapping/stats.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

namespace TokenSwapping
{
	Database::Database(int power, int size) :
		m_power{power},
		m_size{size},
		m_fieldWidth{(int)std::log10(m_size * m_size) + 1}
	{ }

	void Database::generate()
	{
		m_oFile.open(path());
		if (!m_oFile.is_open())
		{
			error("Database::generate: Database couldn't be created");
		}
		Stats::iteratePermutations(m_power, m_size, *this);
		m_oFile.close();
	}

	int Database::optimalSolutionLength(const Instance& instance)
	{
		if (instance.power() != m_power)
		{
			error("Database::optimalSolutionLength: Incompatible instance power");
		}
		if (instance.size() != m_size)
		{
			error("Database::optimalSolutionLength: Incompatible instance size");
		}
		m_iFile.open(path());
		if (!m_iFile.is_open())
		{
			error("Database::optimalSolutionLength: Database doesn't exist");
		}
		int index = Stats::permutation2Index(instance);
		m_iFile.seekg(index * (m_fieldWidth + 2));
		std::string line;
		std::getline(m_iFile, line);
		m_iFile.close();
		return std::stoi(line);
	}

	void Database::operator()(const Instance& instance)
	{
#if 1
		for (int i = 0; i < instance.size(); ++i)
		{
			std::cout << instance[i] << " ";
		}
		std::cout << '\n';
#endif
		m_oFile << std::setw(m_fieldWidth) << BruteForceSort::getSolution(instance).size() << '\n';
	}

	std::string Database::path() const
	{
		return "database/" + std::to_string(m_power) + "_" + std::to_string(m_size) + ".txt";
	}

	void Database::error(const char* msg) const
	{
		std::cerr << std::endl << msg << std::endl;
		throw std::invalid_argument(msg);
	}
};
