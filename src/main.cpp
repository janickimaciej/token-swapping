#include "token_swapping/instance.hpp"

#include <iostream>

int main()
{
	TokenSwapping::Instance instance(1, std::vector<int>{0, 2, 3, 1});
	instance.swap(2, 3);
	instance.swap(1, 2);
	std::cout << instance.isSolved() << std::endl;
	return 0;
}
