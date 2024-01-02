#include "token_swapping/reverse/criteria/criteria.hpp"

namespace TokenSwapping
{
	const std::vector<std::unique_ptr<Criterion>>& Criteria::getVector() const
	{
		return m_criteria;
	}
};
