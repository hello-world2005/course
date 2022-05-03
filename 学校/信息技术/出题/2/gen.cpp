#include "testlib.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  std::vector<std::string> v;
  std::unordered_map<int, int> NumberToSuit;
  std::unordered_map<int, int> SuitToNumber;
  std::unordered_map<int, int> NumberToPip;
  std::unordered_map<int, int> PipToNumber;
  NumberToSuit.insert(std::make_pair('S', 1));
  SuitToNumber.insert(std::make_pair(1, 'S'));
  NumberToSuit.insert(std::make_pair('H', 2));
  SuitToNumber.insert(std::make_pair(2, 'H'));
  NumberToSuit.insert(std::make_pair('D', 3));
  SuitToNumber.insert(std::make_pair(3, 'D'));
  NumberToSuit.insert(std::make_pair('C', 4));
  SuitToNumber.insert(std::make_pair(4, 'C'));
  NumberToPip.insert(std::make_pair('A', 14));
  PipToNumber.insert(std::make_pair(14, 'A'));
  NumberToPip.insert(std::make_pair('K', 13));
  PipToNumber.insert(std::make_pair(13, 'K'));
  NumberToPip.insert(std::make_pair('Q', 12));
  PipToNumber.insert(std::make_pair(12, 'Q'));
  NumberToPip.insert(std::make_pair('J', 11));
  PipToNumber.insert(std::make_pair(11, 'J'));
  NumberToPip.insert(std::make_pair('T', 10));
  PipToNumber.insert(std::make_pair(10, 'T'));
  for (char i = '2'; i <= '9'; ++i) {
    NumberToPip.insert(std::make_pair(i, i - '1' + 1));
    PipToNumber.insert(std::make_pair(i - '1' + 1, i));
  }
  for (int i = 1; i <= 52; ++i) {
    std::string s = "  ";
    s[0] = char(SuitToNumber[i % 13 == 0 ? i / 13 : i / 13 + 1]);
    s[1] = char(PipToNumber[i % 13 + 1 == 1 ? 14 : i % 13 + 1]);
    v.push_back(s);
  }
  shuffle(v.begin(), v.end());
  std::cout << v[0] << ' ' << v[1] << std::endl;
  std::cout << v[2] << ' ' << v[3] << std::endl;
  std::cout << v[4] << ' ' << v[5] << ' ' << v[6] << std::endl;
  return 0;
}
