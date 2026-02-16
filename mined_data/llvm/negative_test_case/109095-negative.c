constexpr char c[] = {'a', '\0'};
constexpr int i = c[1];
static_assert(i == c[0], "whatever");