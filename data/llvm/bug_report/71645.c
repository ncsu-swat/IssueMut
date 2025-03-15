extern char **environ;

int main() { __builtin_printf("%10s\n", environ[0]); }