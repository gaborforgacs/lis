#include <iostream>
#include <vector>

namespace LIS
{
namespace internals
{
struct LISChain
{
  size_t len;
  size_t prev;

  LISChain()
    : len(1)
      , prev(0)
  {
  }
};
} // namespace internals

using IndexArray = std::vector<size_t>;

template<typename T>
IndexArray lis(std::vector<T> const &arr)
{
  using namespace internals;
  std::vector<LISChain> subSeqs(arr.size(), LISChain());

  size_t lisEndIndex = 0;
  size_t lisLen = 1;
  for(size_t i=1; i<arr.size(); ++i)
  {
    // search for the longest subsequence ending in arr[0..i-1]
    size_t longest = 1;
    size_t longestIndex = i;
    for(size_t j=0; j<i; ++j)
    {
      size_t jLen = subSeqs[j].len;
      if(arr[j] < arr[i] && jLen + 1 > longest)
      {
        longest = jLen + 1;
        longestIndex = j;
      }
    }
    subSeqs[i].len = longest;
    subSeqs[i].prev = longestIndex;

    if(longest > lisLen)
    {
      lisLen = longest;
      lisEndIndex = i;
    }
  }

  IndexArray result(lisLen);
  result[subSeqs[lisEndIndex].len - 1] = lisEndIndex;
  while(subSeqs[lisEndIndex].len > 1)
  {
    lisEndIndex = subSeqs[lisEndIndex].prev;
    result[subSeqs[lisEndIndex].len - 1] = lisEndIndex;
  };

  return result;
}
} // namespace LIS


int main()
{
  using namespace LIS;
  int n = 0;

  std::cin >> n;
  if(n < 1)
    return 1;

  std::vector<int> arr;
  arr.resize(static_cast<size_t>(n));
  for(auto &e: arr)
    std::cin >> e;

  IndexArray const lisIndexArray = lis(arr);
  std::cout << lisIndexArray[0];
  for(size_t i=1; i<lisIndexArray.size(); ++i)
    std::cout << " " << arr[i];
  std::cout << std::endl;

  return 0;
}
