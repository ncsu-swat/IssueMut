struct {
    char data;
} d;

char x[(sizeof(d.data) == 8)];
char x[(sizeof(d.data) == 8)];