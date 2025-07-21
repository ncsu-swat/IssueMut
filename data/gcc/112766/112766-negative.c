void *operator new[](__SIZE_TYPE__, void *__p);

class Result {
public:
  Result();
  ~Result();
};

void *foo(long nElements, void *p) {
  if (p)
    return new ((int *)p) Result[nElements];
  else
    return new Result[nElements];
}