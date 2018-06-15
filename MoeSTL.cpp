#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> vec(std::istream_iterator<int>(std::cin), (std::istream_iterator<int>()));
    std::sort(vec.begin(), vec.end());
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout));
    return 0;
}