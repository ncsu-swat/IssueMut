bool foo(bool a, bool b, bool c, bool d, bool e) {
  if (a || b)
    return c && d;
  else
    return e;
}