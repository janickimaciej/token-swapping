#pragma once

#include "token_swapping/reverse/criteria/criterion.hpp"

#include <memory>
#include <vector>

namespace TokenSwapping
{
	class Criteria
	{
	public:
		template <typename CriterionType>
		void add();

		const std::vector<std::unique_ptr<Criterion>>& getVector() const;

	private:
		std::vector<std::unique_ptr<Criterion>> m_criteria;
	};

	template <typename CriterionType>
	void Criteria::add()
	{
		m_criteria.push_back(std::make_unique<CriterionType>());
	}
};
