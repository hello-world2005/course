#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <unordered_map>
#include <vector>

std::unordered_map<char, int> NumberToSuit;
std::unordered_map<char, int> SuitToNumber;
std::unordered_map<char, int> NumberToPip;
std::unordered_map<char, int> PipToNumber;

struct Card {
  int pip;   // A,K,Q,J,10,9,8,7,6,5,4,3,2
  int suit;  // diamonds, clubs, hearts and spades

  Card() : pip(0), suit(0) {}
  Card(int _pip, int _suit) : pip(_pip), suit(_suit) {}

  bool operator<(const Card& rhs) const {
    return pip != rhs.pip ? pip < rhs.pip : suit < rhs.suit;
  }

  int Pip() { return pip; }
  int Suit() { return suit; }
  bool PipEqual(const Card& rhs) const { return pip == rhs.pip; }
  bool SuitEqual(const Card& rhs) const { return suit == rhs.suit; }
  bool Equal(const Card& rhs) const { return PipEqual(rhs) && SuitEqual(rhs); }

  void Read() {
    auto IsSuit = [&](char c) {
      return NumberToSuit.find(c) != NumberToSuit.end();
    };
    auto Suit = [&](char c) { return NumberToSuit[c]; };
    auto Pip = [&](char c) { return NumberToPip[c]; };

    char c = getchar();
    while (!IsSuit(c))
      c = getchar();
    suit = Suit(c);
    c = getchar();
    pip = Pip(c);
  }
};

Card player1[2], player2[2], community[5];
std::set<Card> initial;

void Input() {
  initial.clear();
  player1[0].Read(), player1[1].Read(), player2[0].Read(), player2[1].Read(),
      community[0].Read(), community[1].Read(), community[2].Read();
  initial.insert(player1[0]), initial.insert(player1[1]),
      initial.insert(player2[0]), initial.insert(player2[1]);
  initial.insert(community[0]), initial.insert(community[1]),
      initial.insert(community[2]);
  // printf("%d %d\n", player1[0].pip, player1[0].suit);
  // printf("%d %d\n", player1[1].pip, player1[1].suit);
  // printf("%d %d\n", player2[0].pip, player2[0].suit);
  // printf("%d %d\n", player2[1].pip, player2[1].suit);
  // printf("%d %d\n", community[0].pip, community[0].suit);
  // printf("%d %d\n", community[1].pip, community[1].suit);
  // printf("%d %d\n", community[2].pip, community[2].suit);
}

struct Situation {
  std::vector<Card> c;

  Situation() { c.clear(); }
  Situation(std::vector<Card> _c) { c = _c; }
};

int HandType(Situation player) {
  std::vector<Card> c(player.c);
  std::sort(c.begin(), c.end());

  auto IsStraight = [=](std::vector<Card> c) {
    bool res1 = (c[0].Pip() == c[1].Pip() - 1 && c[1].Pip() == c[2].Pip() - 1 &&
                 c[2].Pip() == c[3].Pip() - 1 && c[3].Pip() == c[4].Pip() - 1);
    if (res1)
      return true;
    if (c[4].Pip() != 14)
      return res1;
    if (c[0].Pip() == 2 && c[1].Pip() == 3 && c[2].Pip() == 4 &&
        c[3].Pip() == 5)
      return true;
    return false;
  };
  auto IsFlush = [&](std::vector<Card> c) {
    return (c[0].Suit() == c[1].Suit() && c[1].Suit() == c[2].Suit() &&
            c[2].Suit() == c[3].Suit() && c[3].Suit() == c[4].Suit());
  };
  auto FourOfAKind = [&](std::vector<Card> c) {
    return (c[0].Pip() == c[1].Pip() && c[1].Pip() == c[2].Pip() &&
            c[2].Pip() == c[3].Pip()) ||
           (c[1].Pip() == c[2].Pip() && c[2].Pip() == c[3].Pip() &&
            c[3].Pip() == c[4].Pip());
  };
  auto FullHouse = [&](std::vector<Card> c) {
    return (c[0].Pip() == c[1].Pip() && c[1].Pip() == c[2].Pip() &&
            c[3].Pip() == c[4].Pip()) ||
           (c[0].Pip() == c[1].Pip() && c[2].Pip() == c[3].Pip() &&
            c[3].Pip() == c[4].Pip());
  };
  auto ThreeAKind = [&](std::vector<Card> c) {
    return (c[0].Pip() == c[1].Pip() && c[1].Pip() == c[2].Pip()) ||
           (c[1].Pip() == c[2].Pip() && c[2].Pip() == c[3].Pip()) ||
           (c[2].Pip() == c[3].Pip() && c[3].Pip() == c[4].Pip());
  };
  auto TwoPairs = [&](std::vector<Card> c) {
    return (c[0].Pip() == c[1].Pip() && c[2].Pip() == c[3].Pip()) ||
           (c[0].Pip() == c[1].Pip() && c[3].Pip() == c[4].Pip()) ||
           (c[1].Pip() == c[2].Pip() && c[3].Pip() == c[4].Pip());
  };
  auto Pairs = [&](std::vector<Card> c) {
    return c[0].Pip() == c[1].Pip() || c[1].Pip() == c[2].Pip() ||
           c[2].Pip() == c[3].Pip() || c[3].Pip() == c[4].Pip();
  };

  if (IsStraight(c) && IsFlush(c)) {
    if (c[0].Pip() == 10 && c[1].Pip() == 11 && c[2].Pip() == 12 &&
        c[3].Pip() == 13 && c[4].Pip() == 14)
      return 1;
    return 2;
  };
  if (FourOfAKind(c))
    return 3;
  if (FullHouse(c))
    return 4;
  if (IsFlush(c))
    return 5;
  if (IsStraight(c))
    return 6;
  if (ThreeAKind(c))
    return 7;
  if (TwoPairs(c))
    return 8;
  if (Pairs(c))
    return 9;
  return 10;
}

bool Win(Situation pl1, Situation pl2) {
  int handtype_pl1 = HandType(pl1), handtype_pl2 = HandType(pl2);
  if (handtype_pl1 < handtype_pl2)
    return true;
  if (handtype_pl1 > handtype_pl2)
    return false;
  std::vector<Card> c1(pl1.c), c2(pl2.c);
  std::sort(c1.begin(), c1.end());
  std::sort(c2.begin(), c2.end());

  if (handtype_pl1 == 1) {
    return false;
  } else if (handtype_pl1 == 2) {
    if (c1[4].Pip() == 14 && c1[0].Pip() == 2)
      c1[4].pip = 1, std::swap(c1[4], c1[3]), std::swap(c1[3], c1[2]),
      std::swap(c1[2], c1[1]), std::swap(c1[1], c1[0]);
    if (c2[4].Pip() == 14 && c2[0].Pip() == 2)
      c2[4].pip = 1, std::swap(c2[4], c2[3]), std::swap(c2[3], c2[2]),
      std::swap(c2[2], c2[1]), std::swap(c2[1], c2[0]);
    return c1[0].Pip() > c2[0].Pip();
  } else if (handtype_pl1 == 3) {
    if (c1[1].Pip() == c1[2].Pip() && c1[2].Pip() == c1[3].Pip() &&
        c1[3].Pip() == c1[4].Pip())
      std::swap(c1[0], c1[4]);
    if (c2[1].Pip() == c2[2].Pip() && c2[2].Pip() == c2[3].Pip() &&
        c2[3].Pip() == c2[4].Pip())
      std::swap(c2[0], c2[4]);
    return c1[0].Pip() != c2[0].Pip() ? c1[0].Pip() > c2[0].Pip()
                                      : c1[4].Pip() > c2[4].Pip();
  } else if (handtype_pl1 == 4) {
    if (c1[2].Pip() == c1[3].Pip() && c1[3].Pip() == c1[4].Pip() &&
        c1[0].Pip() == c1[1].Pip())
      std::swap(c1[0], c1[3]), std::swap(c1[1], c1[4]);
    if (c2[2].Pip() == c2[3].Pip() && c2[3].Pip() == c2[4].Pip() &&
        c2[0].Pip() == c2[1].Pip())
      std::swap(c2[0], c2[3]), std::swap(c2[1], c2[4]);
    return c1[0].Pip() != c2[0].Pip() ? c1[0].Pip() > c2[0].Pip()
                                      : c1[3].Pip() > c2[3].Pip();
  } else if (handtype_pl1 == 5) {
    for (int i = 4; i >= 0; --i)
      if (c1[i].Pip() != c2[i].Pip())
        return c1[i].Pip() > c2[i].Pip();
    return false;
  } else if (handtype_pl1 == 6) {
    if (c1[4].Pip() == 14 && c1[0].Pip() == 2)
      c1[4].pip = 1, std::swap(c1[4], c1[3]), std::swap(c1[3], c1[2]),
      std::swap(c1[2], c1[1]), std::swap(c1[1], c1[0]);
    if (c2[4].Pip() == 14 && c2[0].Pip() == 2)
      c2[4].pip = 1, std::swap(c2[4], c2[3]), std::swap(c2[3], c2[2]),
      std::swap(c2[2], c2[1]), std::swap(c2[1], c2[0]);
    return c1[0].Pip() > c2[0].Pip();
  } else if (handtype_pl1 == 7) {
    if (c1[0].Pip() != c1[1].Pip() && c1[1].Pip() != c1[2].Pip())
      std::swap(c1[1], c1[2]), std::swap(c1[2], c1[3]), std::swap(c1[3], c1[4]),
          std::swap(c1[0], c1[1]), std::swap(c1[1], c1[2]),
          std::swap(c1[2], c1[3]);
    else if (c1[0].Pip() != c1[1].Pip() && c1[3].Pip() != c1[4].Pip())
      std::swap(c1[0], c1[1]), std::swap(c1[1], c1[2]), std::swap(c1[2], c1[3]);
    if (c2[0].Pip() != c2[1].Pip() && c2[1].Pip() != c2[2].Pip())
      std::swap(c2[1], c2[2]), std::swap(c2[2], c2[3]), std::swap(c2[3], c2[4]),
          std::swap(c2[0], c2[1]), std::swap(c2[1], c2[2]),
          std::swap(c2[2], c2[3]);
    else if (c2[0].Pip() != c2[1].Pip() && c2[3].Pip() != c2[4].Pip())
      std::swap(c2[0], c2[1]), std::swap(c2[1], c2[2]), std::swap(c2[2], c2[3]);
    return c1[0].Pip() != c2[0].Pip()
               ? c1[0].Pip() > c2[0].Pip()
               : (c1[4].Pip() != c2[4].Pip() ? c1[4].Pip() > c2[4].Pip()
                                             : c1[3].Pip() > c2[3].Pip());
  } else if (handtype_pl1 == 8) {
    if (c1[0].Pip() == c1[1].Pip() && c1[3].Pip() == c1[4].Pip())
      std::swap(c1[2], c1[3]), std::swap(c1[3], c1[4]);
    else if (c1[1].Pip() == c1[2].Pip() && c1[3].Pip() && c1[4].Pip())
      std::swap(c1[0], c1[1]), std::swap(c1[1], c1[2]), std::swap(c1[2], c1[3]),
          std::swap(c1[3], c1[4]);
    if (c2[0].Pip() == c2[1].Pip() && c2[3].Pip() == c2[4].Pip())
      std::swap(c2[2], c2[3]), std::swap(c2[3], c2[4]);
    else if (c2[1].Pip() == c2[2].Pip() && c2[3].Pip() && c2[4].Pip())
      std::swap(c2[0], c2[1]), std::swap(c2[1], c2[2]), std::swap(c2[2], c2[3]),
          std::swap(c2[3], c2[4]);
    return c1[2].Pip() != c2[2].Pip()
               ? c1[2].Pip() > c2[2].Pip()
               : (c1[0].Pip() != c2[0].Pip() ? c1[0].Pip() > c2[0].Pip()
                                             : c1[4].Pip() > c2[4].Pip());
  } else if (handtype_pl1 == 9) {
    if (c1[1].Pip() == c1[2].Pip())
      std::swap(c1[0], c1[1]), std::swap(c1[1], c1[2]);
    else if (c1[2].Pip() == c1[3].Pip())
      std::swap(c1[2], c1[1]), std::swap(c1[1], c1[0]), std::swap(c1[3], c1[2]),
          std::swap(c1[2], c1[1]);
    else if (c1[3].Pip() == c1[4].Pip())
      std::swap(c1[3], c1[2]), std::swap(c1[2], c1[1]), std::swap(c1[1], c1[0]),
          std::swap(c1[4], c1[3]), std::swap(c1[3], c1[2]),
          std::swap(c1[2], c1[1]);
    if (c2[1].Pip() == c2[2].Pip())
      std::swap(c2[0], c2[1]), std::swap(c2[1], c2[2]);
    else if (c2[2].Pip() == c2[3].Pip())
      std::swap(c2[2], c2[1]), std::swap(c2[1], c2[0]), std::swap(c2[3], c2[2]),
          std::swap(c2[2], c2[1]);
    else if (c2[3].Pip() == c2[4].Pip())
      std::swap(c2[3], c2[2]), std::swap(c2[2], c2[1]), std::swap(c2[1], c2[0]),
          std::swap(c2[4], c2[3]), std::swap(c2[3], c2[2]),
          std::swap(c2[2], c2[1]);
    if (c1[0].Pip() != c2[0].Pip())
      return c1[0].Pip() > c2[0].Pip();
    for (int i = 4; i >= 2; --i)
      if (c1[i].Pip() != c2[i].Pip())
        return c1[i].Pip() > c2[i].Pip();
    return false;
  } else {
    for (int i = 4; i >= 0; --i)
      if (c1[i].Pip() != c2[i].Pip())
        return c1[i].Pip() > c2[i].Pip();
    return false;
  }
  return false;
}

Situation FindBest(std::vector<Situation> pl) {
  int minn = HandType(pl[0]), pos = 0;
  for (int i = 1; i < (int)pl.size(); ++i) {
    int hand_type = HandType(pl[i]);
    if (hand_type <= minn) {
      if (hand_type < minn)
        minn = hand_type, pos = i;
      else if (Win(pl[i], pl[pos]))
        minn = hand_type, pos = i;
    }
  }
  return pl[pos];
}

std::pair<int, int> Calc(Situation pl1, Situation pl2) {
  // if (!Win(pl1, pl2)) {
  //   printf("%d %d\n", HandType(pl1), HandType(pl2));
  //   auto b = pl1.c;
  //   for (auto i : b)
  //     printf("%d %d\n", i.suit, i.pip);
  //   printf("\n");
  //   b = pl2.c;
  //   for (auto i : b)
  //     printf("%d %d\n", i.suit, i.pip);
  //   printf("\n==========\n");
  // }
  return std::make_pair(Win(pl1, pl2), 1);
}

Card NumToCard(const int& x) {
  int suit = x / 13 + 1, pip = x % 13 + 2;
  return Card(pip, suit);
}

Situation Enumerate(const Card& c1,
                    const Card& c2,
                    const Card& c3,
                    const Card& c4,
                    const Card& c5,
                    const Card& c6,
                    const Card& c7) {
  std::vector<Situation> res;

  auto FiveCardToSituation = [&](const Card c1, const Card c2, const Card c3,
                                 const Card c4, const Card c5) {
    std::vector<Card> c(5);
    c[0] = c1, c[1] = c2, c[2] = c3, c[3] = c4, c[4] = c5;
    return Situation(c);
  };

  res.push_back(FiveCardToSituation(c1, c2, c3, c4, c5));
  res.push_back(FiveCardToSituation(c1, c2, c3, c4, c6));
  res.push_back(FiveCardToSituation(c1, c2, c3, c4, c7));
  res.push_back(FiveCardToSituation(c1, c2, c3, c5, c6));
  res.push_back(FiveCardToSituation(c1, c2, c3, c5, c7));
  res.push_back(FiveCardToSituation(c1, c2, c3, c6, c7));
  res.push_back(FiveCardToSituation(c1, c2, c4, c5, c6));
  res.push_back(FiveCardToSituation(c1, c2, c4, c5, c7));
  res.push_back(FiveCardToSituation(c1, c2, c4, c6, c7));
  res.push_back(FiveCardToSituation(c1, c2, c5, c6, c7));
  res.push_back(FiveCardToSituation(c1, c3, c4, c5, c6));
  res.push_back(FiveCardToSituation(c1, c3, c4, c5, c7));
  res.push_back(FiveCardToSituation(c1, c3, c4, c6, c7));
  res.push_back(FiveCardToSituation(c1, c3, c5, c6, c7));
  res.push_back(FiveCardToSituation(c1, c4, c5, c6, c7));
  res.push_back(FiveCardToSituation(c2, c3, c4, c5, c6));
  res.push_back(FiveCardToSituation(c2, c3, c4, c5, c7));
  res.push_back(FiveCardToSituation(c2, c3, c4, c6, c7));
  res.push_back(FiveCardToSituation(c2, c3, c5, c6, c7));
  res.push_back(FiveCardToSituation(c2, c4, c5, c6, c7));
  res.push_back(FiveCardToSituation(c3, c4, c5, c6, c7));

  return FindBest(res);
}

std::pair<int, int> Solve() {
  int cnt[20], ans = 0, tot = 0;
  memset(cnt, 0, sizeof(cnt));
  ++cnt[player1[0].Pip()], ++cnt[player1[1].Pip()];
  ++cnt[player2[0].Pip()], ++cnt[player2[1].Pip()];
  ++cnt[community[0].Pip()], ++cnt[community[1].Pip()],
      ++cnt[community[2].Pip()];
  int qwq = 0;
  for (int i = 0; i < 52; ++i) {
    community[3] = NumToCard(i);
    if (initial.find(community[3]) != initial.end())
      continue;
    ++cnt[community[3].Pip()];
    for (int j = 0; j < i; ++j) {
      community[4] = NumToCard(j);
      if (initial.find(community[4]) != initial.end())
        continue;
      ++cnt[community[4].Pip()];
      auto now =
          Calc(Enumerate(player1[0], player1[1], community[0], community[1],
                         community[2], community[3], community[4]),
               Enumerate(player2[0], player2[1], community[0], community[1],
                         community[2], community[3], community[4]));
      ans += now.first, tot += now.second;
      --cnt[community[4].Pip()];
    }
    --cnt[community[3].Pip()];
  }
  return std::make_pair(ans, tot);
}

void Output(std::pair<int, int> ans) {
  auto Gcd = [=](int a, int b) {
    while (b ^= a ^= b ^= a %= b)
      ;
    return a;
  };

  // printf("%d %d\n", ans.first, ans.second);
  int gcd = Gcd(ans.first, ans.second);
  printf("%d/%d\n", ans.first / gcd, ans.second / gcd);
}

void Main() {
  Input();
  Output(Solve());
}

void Init() {
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
}

int main() {
  int T;
  scanf("%d", &T);
  Init();
  while (T--)
    Main();
  return 0;
}
