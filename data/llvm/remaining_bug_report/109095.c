constexpr char c[] = {'a'};
constexpr int i = c[1];
static_assert(i == c[0], "whatever");