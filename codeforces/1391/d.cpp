#include <algorithm>
#include <cstdio>
#include <vector>

const char _22[8][2][3] = {{"00", "01"}, {"00", "10"}, {"01", "00"}, {"01", "11"}, {"10", "00"}, {"10", "11"}, {"11", "01"}, {"11", "10"}};
const char _23[16][2][4] = {{"000", "010"}, {"000", "101"}, {"001", "011"}, {"001", "100"}, {"010", "000"}, {"010", "111"}, {"011", "001"}, {"011", "110"}, {"100", "001"}, {"100", "110"}, {"101", "000"}, {"101", "111"}, {"110", "011"}, {"110", "100"}, {"111", "010"}, {"111", "101"}};
const char _24[32][2][5] = {{"0000", "0101"}, {"0000", "1010"}, {"0001", "0100"}, {"0001", "1011"}, {"0010", "0111"}, {"0010", "1000"}, {"0011", "0110"}, {"0011", "1001"}, {"0100", "0001"}, {"0100", "1110"}, {"0101", "0000"}, {"0101", "1111"}, {"0110", "0011"}, {"0110", "1100"}, {"0111", "0010"}, {"0111", "1101"}, {"1000", "0010"}, {"1000", "1101"}, {"1001", "0011"}, {"1001", "1100"}, {"1010", "0000"}, {"1010", "1111"}, {"1011", "0001"}, {"1011", "1110"}, {"1100", "0110"}, {"1100", "1001"}, {"1101", "0111"}, {"1101", "1000"}, {"1110", "0100"}, {"1110", "1011"}, {"1111", "0101"}, {"1111", "1010"}};
const char _32[16][3][3] = {{"00", "01", "00"}, {"00", "01", "11"}, {"00", "10", "00"}, {"00", "10", "11"}, {"01", "00", "01"}, {"01", "00", "10"}, {"01", "11", "01"}, {"01", "11", "10"}, {"10", "00", "01"}, {"10", "00", "10"}, {"10", "11", "01"}, {"10", "11", "10"}, {"11", "01", "00"}, {"11", "01", "11"}, {"11", "10", "00"}, {"11", "10", "11"}};
const char _33[32][3][4] = {{"000", "010", "000"}, {"000", "010", "111"}, {"000", "101", "000"}, {"000", "101", "111"}, {"001", "011", "001"}, {"001", "011", "110"}, {"001", "100", "001"}, {"001", "100", "110"}, {"010", "000", "010"}, {"010", "000", "101"}, {"010", "111", "010"}, {"010", "111", "101"}, {"011", "001", "011"}, {"011", "001", "100"}, {"011", "110", "011"}, {"011", "110", "100"}, {"100", "001", "011"}, {"100", "001", "100"}, {"100", "110", "011"}, {"100", "110", "100"}, {"101", "000", "010"}, {"101", "000", "101"}, {"101", "111", "010"}, {"101", "111", "101"}, {"110", "011", "001"}, {"110", "011", "110"}, {"110", "100", "001"}, {"110", "100", "110"}, {"111", "010", "000"}, {"111", "010", "111"}, {"111", "101", "000"}, {"111", "101", "111"}};
const char _34[64][3][5] = {{"0000", "0101", "0000"}, {"0000", "0101", "1111"}, {"0000", "1010", "0000"}, {"0000", "1010", "1111"}, {"0001", "0100", "0001"}, {"0001", "0100", "1110"}, {"0001", "1011", "0001"}, {"0001", "1011", "1110"}, {"0010", "0111", "0010"}, {"0010", "0111", "1101"}, {"0010", "1000", "0010"}, {"0010", "1000", "1101"}, {"0011", "0110", "0011"}, {"0011", "0110", "1100"}, {"0011", "1001", "0011"}, {"0011", "1001", "1100"}, {"0100", "0001", "0100"}, {"0100", "0001", "1011"}, {"0100", "1110", "0100"}, {"0100", "1110", "1011"}, {"0101", "0000", "0101"}, {"0101", "0000", "1010"}, {"0101", "1111", "0101"}, {"0101", "1111", "1010"}, {"0110", "0011", "0110"}, {"0110", "0011", "1001"}, {"0110", "1100", "0110"}, {"0110", "1100", "1001"}, {"0111", "0010", "0111"}, {"0111", "0010", "1000"}, {"0111", "1101", "0111"}, {"0111", "1101", "1000"}, {"1000", "0010", "0111"}, {"1000", "0010", "1000"}, {"1000", "1101", "0111"}, {"1000", "1101", "1000"}, {"1001", "0011", "0110"}, {"1001", "0011", "1001"}, {"1001", "1100", "0110"}, {"1001", "1100", "1001"}, {"1010", "0000", "0101"}, {"1010", "0000", "1010"}, {"1010", "1111", "0101"}, {"1010", "1111", "1010"}, {"1011", "0001", "0100"}, {"1011", "0001", "1011"}, {"1011", "1110", "0100"}, {"1011", "1110", "1011"}, {"1100", "0110", "0011"}, {"1100", "0110", "1100"}, {"1100", "1001", "0011"}, {"1100", "1001", "1100"}, {"1101", "0111", "0010"}, {"1101", "0111", "1101"}, {"1101", "1000", "0010"}, {"1101", "1000", "1101"}, {"1110", "0100", "0001"}, {"1110", "0100", "1110"}, {"1110", "1011", "0001"}, {"1110", "1011", "1110"}, {"1111", "0101", "0000"}, {"1111", "0101", "1111"}, {"1111", "1010", "0000"}, {"1111", "1010", "1111"}};
const char _42[32][4][3] = {{"00", "01", "00", "01"}, {"00", "01", "00", "10"}, {"00", "01", "11", "01"}, {"00", "01", "11", "10"}, {"00", "10", "00", "01"}, {"00", "10", "00", "10"}, {"00", "10", "11", "01"}, {"00", "10", "11", "10"}, {"01", "00", "01", "00"}, {"01", "00", "01", "11"}, {"01", "00", "10", "00"}, {"01", "00", "10", "11"}, {"01", "11", "01", "00"}, {"01", "11", "01", "11"}, {"01", "11", "10", "00"}, {"01", "11", "10", "11"}, {"10", "00", "01", "00"}, {"10", "00", "01", "11"}, {"10", "00", "10", "00"}, {"10", "00", "10", "11"}, {"10", "11", "01", "00"}, {"10", "11", "01", "11"}, {"10", "11", "10", "00"}, {"10", "11", "10", "11"}, {"11", "01", "00", "01"}, {"11", "01", "00", "10"}, {"11", "01", "11", "01"}, {"11", "01", "11", "10"}, {"11", "10", "00", "01"}, {"11", "10", "00", "10"}, {"11", "10", "11", "01"}, {"11", "10", "11", "10"}};
const char _43[64][4][4] = {{"000", "010", "000", "010"}, {"000", "010", "000", "101"}, {"000", "010", "111", "010"}, {"000", "010", "111", "101"}, {"000", "101", "000", "010"}, {"000", "101", "000", "101"}, {"000", "101", "111", "010"}, {"000", "101", "111", "101"}, {"001", "011", "001", "011"}, {"001", "011", "001", "100"}, {"001", "011", "110", "011"}, {"001", "011", "110", "100"}, {"001", "100", "001", "011"}, {"001", "100", "001", "100"}, {"001", "100", "110", "011"}, {"001", "100", "110", "100"}, {"010", "000", "010", "000"}, {"010", "000", "010", "111"}, {"010", "000", "101", "000"}, {"010", "000", "101", "111"}, {"010", "111", "010", "000"}, {"010", "111", "010", "111"}, {"010", "111", "101", "000"}, {"010", "111", "101", "111"}, {"011", "001", "011", "001"}, {"011", "001", "011", "110"}, {"011", "001", "100", "001"}, {"011", "001", "100", "110"}, {"011", "110", "011", "001"}, {"011", "110", "011", "110"}, {"011", "110", "100", "001"}, {"011", "110", "100", "110"}, {"100", "001", "011", "001"}, {"100", "001", "011", "110"}, {"100", "001", "100", "001"}, {"100", "001", "100", "110"}, {"100", "110", "011", "001"}, {"100", "110", "011", "110"}, {"100", "110", "100", "001"}, {"100", "110", "100", "110"}, {"101", "000", "010", "000"}, {"101", "000", "010", "111"}, {"101", "000", "101", "000"}, {"101", "000", "101", "111"}, {"101", "111", "010", "000"}, {"101", "111", "010", "111"}, {"101", "111", "101", "000"}, {"101", "111", "101", "111"}, {"110", "011", "001", "011"}, {"110", "011", "001", "100"}, {"110", "011", "110", "011"}, {"110", "011", "110", "100"}, {"110", "100", "001", "011"}, {"110", "100", "001", "100"}, {"110", "100", "110", "011"}, {"110", "100", "110", "100"}, {"111", "010", "000", "010"}, {"111", "010", "000", "101"}, {"111", "010", "111", "010"}, {"111", "010", "111", "101"}, {"111", "101", "000", "010"}, {"111", "101", "000", "101"}, {"111", "101", "111", "010"}, {"111", "101", "111", "101"}};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<std::vector<int> > a(n + 1), b(n + 1);
  for (int i = 1; i <= n; ++i)
    a[i].resize(m + 1), b[i].resize(m + 1);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%1d", &a[i][j]);
  if (n >= 4 && m >= 4) {
    printf("-1\n");
  } else if (n == 1 || m == 1) {
    printf("0\n");
  } else if (n == 2 && m == 2) {
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < 8; ++i) {
      int now = 0;
      for (int j = 1; j <= 2; ++j)
        for (int k = 1; k <= 2; ++k)
          if (a[j][k] != (bool)(_22[i][j - 1][k - 1] - '0'))
            ++now;
      ans = std::min(ans, now);
    }
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
  } else if (n == 2 && m == 3) {
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < 16; ++i) {
      int now = 0;
      for (int j = 1; j <= 2; ++j)
        for (int k = 1; k <= 3; ++k)
          if (a[j][k] != (bool)(_23[i][j - 1][k - 1] - '0'))
            ++now;
      ans = std::min(ans, now);
    }
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
  } else if (n == 2 && m == 4) {
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < 32; ++i) {
      int now = 0;
      for (int j = 1; j <= 2; ++j)
        for (int k = 1; k <= 4; ++k)
          if (a[j][k] != (bool)(_24[i][j - 1][k - 1] - '0'))
            ++now;
      ans = std::min(ans, now);
    }
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
  } else if (n == 3 && m == 2) {
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < 16; ++i) {
      int now = 0;
      for (int j = 1; j <= 3; ++j)
        for (int k = 1; k <= 2; ++k)
          if (a[j][k] != (bool)(_32[i][j - 1][k - 1] - '0'))
            ++now;
      ans = std::min(ans, now);
    }
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
  } else if (n == 3 && m == 3) {
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < 32; ++i) {
      int now = 0;
      for (int j = 1; j <= 3; ++j)
        for (int k = 1; k <= 3; ++k)
          if (a[j][k] != (bool)(_33[i][j - 1][k - 1] - '0'))
            ++now;
      ans = std::min(ans, now);
    }
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
  } else if (n == 3 && m == 4) {
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < 64; ++i) {
      int now = 0;
      for (int j = 1; j <= 3; ++j)
        for (int k = 1; k <= 4; ++k)
          if (a[j][k] != (bool)(_34[i][j - 1][k - 1] - '0'))
            ++now;
      ans = std::min(ans, now);
    }
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
  } else if (n == 4 && m == 2) {
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < 32; ++i) {
      int now = 0;
      for (int j = 1; j <= 4; ++j)
        for (int k = 1; k <= 2; ++k)
          if (a[j][k] != (bool)(_42[i][j - 1][k - 1] - '0'))
            ++now;
      ans = std::min(ans, now);
    }
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
  } else if (n == 4 && m == 3) {
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < 64; ++i) {
      int now = 0;
      for (int j = 1; j <= 4; ++j)
        for (int k = 1; k <= 3; ++k)
          if (a[j][k] != (bool)(_43[i][j - 1][k - 1] - '0'))
            ++now;
      ans = std::min(ans, now);
    }
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
  }
  return 0;
}
