#pragma once

#include "token_swapping/brute_force_sort.hpp"
#include "token_swapping/database_tree.hpp"
#include "token_swapping/instance.hpp"
#include "token_swapping/stats.hpp"
#include "token_swapping/utils.hpp"

#include <climits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace TokenSwapping
{
	template <int size>
	class Database
	{
	public:
		Database(int power);
		void generate(int from = 0, int to = INT_MAX);
		int optimalSolutionLength(const Instance& instance);
		void operator()(const Instance& instance);

	private:
		int m_power;
		int m_fieldWidth{};
		DatabaseTree<size> databaseTree;
		std::ofstream m_oFile{};
		std::ifstream m_iFile{};

		std::string path() const;
		std::string path(int from, int to) const;
		void error(const char* msg) const;
	};

	template <int size>
	Database<size>::Database(int power) :
		m_power{power},
		m_fieldWidth{(int)std::log10(size * size) + 1}
	{ }
	
	template <int size>
	void Database<size>::generate(int from, int to)
	{
		if (to != INT_MAX)
		{
			m_oFile.open(path(from, to));
		}
		else
		{
			m_oFile.open(path());
		}
		if (!m_oFile.is_open())
		{
			error("Database::generate: Database couldn't be created");
		}
		Stats::iteratePermutations(m_power, size, *this, from, to);
		m_oFile.close();
	}

	template <int size>
	int Database<size>::optimalSolutionLength(const Instance& instance)
	{
		if (instance.power() != m_power)
		{
			error("Database::optimalSolutionLength: Incompatible instance power");
		}
		if (instance.size() != size)
		{
			error("Database::optimalSolutionLength: Incompatible instance size");
		}
		m_iFile.open(path());
		if (!m_iFile.is_open())
		{
			error("Database::optimalSolutionLength: Database doesn't exist");
		}
		int index = permutation2Index(instance);
		m_iFile.seekg(index * (m_fieldWidth + 2));
		std::string line;
		std::getline(m_iFile, line);
		m_iFile.close();
		return std::stoi(line);
	}
	
	template <int size>
	void Database<size>::operator()(const Instance& instance)
	{
#if 1
		for (int i = 0; i < instance.size(); ++i)
		{
			std::cout << instance[i] << " ";
		}
		std::cout << '\n';
#endif
		m_oFile << std::setw(m_fieldWidth) <<
			BruteForceSort::getSolution(instance, databaseTree) << '\n';
	}
	
	template <int size>
	std::string Database<size>::path() const
	{
		return "database/" + std::to_string(m_power) + "_" + std::to_string(size) + ".txt";
	}
	
	template <int size>
	std::string Database<size>::path(int from, int to) const
	{
		return "database/" + std::to_string(m_power) + "_" + std::to_string(size) + "_" +
			std::to_string(from) + "_" + std::to_string(to) + ".txt";
	}

	template <int size>
	void Database<size>::error(const char* msg) const
	{
		std::cerr << std::endl << msg << std::endl;
		throw std::invalid_argument(msg);
	}
};
