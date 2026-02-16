typedef int __attribute__((__vector_size__ (32))) V;
int a;

void
foo (V v)
{
  a--;
  v = v;
}