enum foo
{
  BAR = 0,
  BAZ = 1,
  QUZ = 2,
  QUX = 3
};

struct bitt
{
  enum foo f : 3;
} bitty;