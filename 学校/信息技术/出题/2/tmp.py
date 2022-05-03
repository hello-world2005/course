class Card:
  def __init__(self, pip = 0, suit = 0) -> None:
    self.pip = pip
    self.suit = suit
  
  def __lt__(self, rhs):
    if (self.pip != rhs.pip):
      return self.pip < rhs.pip
    return self.suit < rhs.suit
  
  def __gt__(self, rhs):
    if (self.pip != rhs.pip):
      return self.pip < rhs.pip
    return self.suit < rhs.suit
  
  def __eq__(self, rhs):
    return self.pip == rhs.pip and self.suit == rhs.suit
  
  def __hash__(self) -> int:
    return (self.suit - 1) * 13 + self.pip - 2

  def Pip(self) -> int: return self.pip
  def Suit(self) -> int: return self.suit

def HandType(player):
  c = player.copy()
  c.sort()
  def IsStraight(c):
    res1 = (c[0].Pip() == c[1].Pip() - 1 and c[1].Pip() == c[2].Pip() - 1 and 
            c[2].Pip() == c[3].Pip() - 1 and c[3].Pip() == c[4].Pip() - 1)
    if (res1):
      return True
    if (c[4].Pip() != 14):
      return res1
    if (c[0].Pip() == 2 and c[1].Pip() == 3 and c[2].Pip() == 4 and c[3].Pip() == 5):
      return True
    return False
  def IsFlush(c):
    return (c[0].Suit() == c[1].Suit() and c[1].Suit() == c[2].Suit() and
            c[2].Suit() == c[3].Suit() and c[3].Suit() == c[4].Suit())
  def FourOfAKind(c):
    return ((c[0].Pip() == c[1].Pip() and c[1].Pip() == c[2].Pip() and
            c[2].Pip() == c[3].Pip()) or
           (c[1].Pip() == c[2].Pip() and c[2].Pip() == c[3].Pip() and
            c[3].Pip() == c[4].Pip()))
  def FullHouse(c):
    return ((c[0].Pip() == c[1].Pip() and c[1].Pip() == c[2].Pip() and
            c[3].Pip() == c[4].Pip()) or
           (c[0].Pip() == c[1].Pip() and c[2].Pip() == c[3].Pip() and
            c[3].Pip() == c[4].Pip()))
  def ThreeAKind(c):
    return ((c[0].Pip() == c[1].Pip() and c[1].Pip() == c[2].Pip()) or
           (c[1].Pip() == c[2].Pip() and c[2].Pip() == c[3].Pip()) or
           (c[2].Pip() == c[3].Pip() and c[3].Pip() == c[4].Pip()))
  def TwoPairs(c):
    return ((c[0].Pip() == c[1].Pip() and c[2].Pip() == c[3].Pip()) or
           (c[0].Pip() == c[1].Pip() and c[3].Pip() == c[4].Pip()) or
           (c[1].Pip() == c[2].Pip() and c[3].Pip() == c[4].Pip()))
  def Pairs(c):
    return (c[0].Pip() == c[1].Pip() or c[1].Pip() == c[2].Pip() or
           c[2].Pip() == c[3].Pip() or c[3].Pip() == c[4].Pip())
  
  if (IsStraight(c) and IsFlush(c)):
    if (c[0].Pip() == 10 and c[1].Pip() == 11 and c[2].Pip() == 12 and
        c[3].Pip() == 13 and c[4].Pip() == 14):
      return 1
    return 2
  if (FourOfAKind(c)):
    return 3
  if (FullHouse(c)):
    return 4
  if (IsFlush(c)):
    return 5
  if (IsStraight(c)):
    return 6
  if (ThreeAKind(c)):
    return 7
  if (TwoPairs(c)):
    return 8
  if (Pairs(c)):
    return 9
  return 10

def Win(pl1, pl2):
  handtype_pl1 = HandType(pl1)
  handtype_pl2 = HandType(pl2)
  if (handtype_pl1 < handtype_pl2):
    return True
  if (handtype_pl1 > handtype_pl2):
    return False
  c1 = pl1.copy()
  c2 = pl2.copy()
  c1.sort()
  c2.sort()

  if (handtype_pl1 == 1):
    return False
  elif (handtype_pl1 == 2):
    if (c1[4].Pip() == 14 and c1[0].Pip() == 2):
      c1[4].pip = 1
      c1[0], c1[1], c1[2], c1[3], c1[4] = c1[4], c1[0], c1[1], c1[2], c1[3]
    if (c2[4].Pip() == 14 and c2[0].Pip() == 2):
      c2[4].pip = 1
      c2[0], c2[1], c2[2], c2[3], c2[4] = c2[4], c2[0], c2[1], c2[2], c2[3]
    return c1[0].Pip() > c2[0].Pip()
  elif (handtype_pl1 == 3):
    if (c1[1].Pip() == c1[2].Pip() and c1[2].Pip() == c1[3].Pip() and
        c1[3].Pip() == c1[4].Pip()):
      c1[0], c1[4] = c1[4], c1[0]
    if (c2[1].Pip() == c2[2].Pip() and c2[2].Pip() == c2[3].Pip() and
        c2[3].Pip() == c2[4].Pip()):
      c2[0], c2[4] = c2[4], c2[0]
    if (c1[0].Pip() != c2[0].Pip()):
      return c1[0].Pip() > c2[0].Pip()
    return c1[4].Pip() > c2[4].Pip()
  elif (handtype_pl1 == 4):
    if (c1[2].Pip() == c1[3].Pip() and c1[3].Pip() == c1[4].Pip() and
        c1[0].Pip() == c1[1].Pip()):
      c1[0], c1[3], c1[1], c1[4] = c1[3], c1[0], c1[4], c1[1]
    if (c2[2].Pip() == c2[3].Pip() and c2[3].Pip() == c2[4].Pip() and
        c2[0].Pip() == c2[1].Pip()):
      c2[0], c2[3], c2[1], c2[4] = c2[3], c2[0], c2[4], c2[1]
    if (c1[0].Pip() != c2[0].Pip()):
      return c1[0].Pip() > c2[0].Pip()
    return c1[3].Pip() > c2[3].Pip()
  elif (handtype_pl1 == 5):
    for i in range(4, -1, -1):
      if (c1[i].Pip() != c2[i].Pip()):
        return c1[i].Pip() > c2[i].Pip()
    return False
  elif (handtype_pl1 == 6):
    if (c1[4].Pip() == 14 and c1[0].Pip() == 2):
      c1[4].pip = 1
      c1[0], c1[1], c1[2], c1[3], c1[4] = c1[4], c1[0], c1[1], c1[2], c1[3]
    if (c2[4].Pip() == 14 and c2[0].Pip() == 2):
      c2[4].pip = 1
      c2[0], c2[1], c2[2], c2[3], c2[4] = c2[4], c2[0], c2[1], c2[2], c2[3]
    return c1[0].Pip() > c2[0].Pip()
  elif (handtype_pl1 == 7):
    if (c1[0].Pip() != c1[1].Pip() and c1[1].Pip() != c1[2].Pip()):
      c1[1], c1[2], c1[3], c1[4] = c1[2], c1[3], c1[4], c1[1]
      c1[0], c1[1], c1[2], c1[3] = c1[1], c1[2], c1[3], c1[0]
    elif (c1[0].Pip() != c1[1].Pip() and c1[3].Pip() != c1[4].Pip()):
      c1[0], c1[1], c1[2], c1[3] = c1[1], c1[2], c1[3], c1[0]
    if (c2[0].Pip() != c2[1].Pip() and c2[1].Pip() != c2[2].Pip()):
      c2[1], c2[2], c2[3], c2[4] = c2[2], c2[3], c2[4], c2[1]
      c2[0], c2[1], c2[2], c2[3] = c2[1], c2[2], c2[3], c2[0]
    elif (c2[0].Pip() != c2[1].Pip() and c2[3].Pip() != c2[4].Pip()):
      c2[0], c2[1], c2[2], c2[3] = c2[1], c2[2], c2[3], c2[0]
    if (c1[0].Pip() != c2[0].Pip()):
      return c1[0].Pip() > c2[0].Pip()
    if (c1[4].Pip() != c2[4].Pip()):
      return c1[4].Pip() > c2[4].Pip()
    return c1[3].Pip() > c2[3].Pip()
  elif (handtype_pl1 == 8):
    if (c1[0].Pip() == c1[1].Pip() and c1[3].Pip() == c1[4].Pip()):
      c1[2], c1[3], c1[4] = c1[3], c1[4], c1[2]
    elif (c1[1].Pip() == c1[2].Pip() and c1[3].Pip() and c1[4].Pip()):
      c1[0], c1[1], c1[2], c1[3], c1[4] = c1[1], c1[2], c1[3], c1[4], c1[0]
    if (c2[0].Pip() == c2[1].Pip() and c2[3].Pip() == c2[4].Pip()):
      c2[2], c2[3], c2[4] = c2[3], c2[4], c2[2]
    elif (c2[1].Pip() == c2[2].Pip() and c2[3].Pip() and c2[4].Pip()):
      c2[0], c2[1], c2[2], c2[3], c2[4] = c2[1], c2[2], c2[3], c2[4], c2[0]
    if (c1[2].Pip() != c2[2].Pip()):
      return c1[2].Pip() > c2[2].Pip()
    if (c1[0].Pip() != c2[0].Pip()):
      return c1[0].Pip() > c2[0].Pip()
    return c1[4].Pip() > c2[4].Pip()
  elif (handtype_pl1 == 9):
    if (c1[1].Pip() == c1[2].Pip()):
      c1[0], c1[1], c1[2] = c1[1], c1[2], c1[0]
    elif (c1[2].Pip() == c1[3].Pip()):
      c1[2], c1[1], c1[0] = c1[1], c1[0], c1[2]
      c1[3], c1[2], c1[1] = c1[2], c1[1], c1[3]
    elif (c1[3].Pip() == c1[4].Pip()):
      c1[3], c1[2], c1[1], c1[0] = c1[2], c1[1], c1[0], c1[3]
      c1[4], c1[3], c1[2], c1[1] = c1[3], c1[2], c1[1], c1[4]
    if (c2[1].Pip() == c2[2].Pip()):
      c2[0], c2[1], c2[2] = c2[1], c2[2], c2[0]
    elif (c2[2].Pip() == c2[3].Pip()):
      c2[2], c2[1], c2[0] = c2[1], c2[0], c2[2]
      c2[3], c2[2], c2[1] = c2[2], c2[1], c2[3]
    elif (c2[3].Pip() == c2[4].Pip()):
      c2[3], c2[2], c2[1], c2[0] = c2[2], c2[1], c2[0], c2[3]
      c2[4], c2[3], c2[2], c2[1] = c2[3], c2[2], c2[1], c2[4]
    if (c1[0].Pip() != c2[0].Pip()):
      return c1[0].Pip() > c2[0].Pip()
    for i in range(4, 1, -1):
      if (c1[i].Pip() != c2[i].Pip()):
        return c1[i].Pip() > c2[i].Pip()
    return False
  else:
    for i in range(4, -1, -1):
      if (c1[i].Pip() != c2[i].Pip()):
        return c1[i].Pip() > c2[i].Pip()
    return False

# print(Win([Card(13, 4), Card(13, 2), Card(14, 1), Card(14, 2), Card(8, 2)], [Card(4, 1), Card(4, 2), Card(14, 1), Card(14, 2), Card(8, 2)]))

# print(HandType([Card(13, 4), Card(13, 2), Card(2, 4), Card(2, 3), Card(14, 1)]),
#       HandType([Card(3, 3), Card(14, 3), Card(14, 1), Card(3, 4), Card(13, 2)]))

# print(Win([Card(13, 4), Card(13, 2), Card(2, 4), Card(2, 3), Card(14, 1)], [Card(3, 3), Card(14, 3), Card(14, 1), Card(3, 4), Card(13, 2)]))

def FindBest(pl):
  pos = 0
  for i in range(1, len(pl)):
    if (Win(pl[i], pl[pos])):
      pos = i
  return pl[pos]

def Enumerate(c1, c2, c3, c4, c5, c6, c7):
  return FindBest([[c1, c2, c3, c4, c5],
                   [c1, c2, c3, c4, c6],
                   [c1, c2, c3, c4, c7],
                   [c1, c2, c3, c5, c6],
                   [c1, c2, c3, c5, c7],
                   [c1, c2, c3, c6, c7],
                   [c1, c2, c4, c5, c6],
                   [c1, c2, c4, c5, c7],
                   [c1, c2, c4, c6, c7],
                   [c1, c2, c5, c6, c7],
                   [c1, c3, c4, c5, c6],
                   [c1, c3, c4, c5, c7],
                   [c1, c3, c4, c6, c7],
                   [c1, c3, c5, c6, c7],
                   [c1, c4, c5, c6, c7],
                   [c2, c3, c4, c5, c6],
                   [c2, c3, c4, c5, c7],
                   [c2, c3, c4, c6, c7],
                   [c2, c3, c5, c6, c7],
                   [c2, c4, c5, c6, c7],
                   [c3, c4, c5, c6, c7]])

def Gen(c1, c2, c3, c4, c5, c6, c7):
  return [[c1, c2, c3, c4, c5],
          [c1, c2, c3, c4, c6],
          [c1, c2, c3, c4, c7],
          [c1, c2, c3, c5, c6],
          [c1, c2, c3, c5, c7],
          [c1, c2, c3, c6, c7],
          [c1, c2, c4, c5, c6],
          [c1, c2, c4, c5, c7],
          [c1, c2, c4, c6, c7],
          [c1, c2, c5, c6, c7],
          [c1, c3, c4, c5, c6],
          [c1, c3, c4, c5, c7],
          [c1, c3, c4, c6, c7],
          [c1, c3, c5, c6, c7],
          [c1, c4, c5, c6, c7],
          [c2, c3, c4, c5, c6],
          [c2, c3, c4, c5, c7],
          [c2, c3, c4, c6, c7],
          [c2, c3, c5, c6, c7],
          [c2, c4, c5, c6, c7],
          [c3, c4, c5, c6, c7]]

def Print(l):
  for i in l:
    print(i.pip, i.suit)

print(Win(Enumerate(Card(13, 4), Card(2, 4), Card(13, 2), Card(2, 3), Card(3, 4), Card(14, 1), Card(4, 1))
, Enumerate(Card(3, 3), Card(14, 3), Card(13, 2), Card(2, 3), Card(3, 4), Card(14, 1), Card(4, 1))))

Print(FindBest(Gen(Card(3, 3), Card(14, 3), Card(13, 2), Card(2, 3), Card(3, 4), Card(14, 1), Card(4, 1))))

print(Win([Card(13, 4), Card(2, 4), Card(13, 2), Card(2, 3), Card(14, 1)], [Card(3, 3), Card(13, 2), Card(3, 4), Card(14, 1), Card(4, 1)]))
