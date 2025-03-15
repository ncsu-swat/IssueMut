#include <stdlib.h>

typedef unsigned char uint8_t;
#define SIZE 256

int main(void)
{
uint8_t tab[SIZE];
int fd;
uint8_t bit;
char * filename;
int i;
char * f_name = "bit-set.bin";
int fd = 0;
int size = sizeof(tab);
static const int O_CREAT = 1;
static const int O_RDWR = 2;

for (i = 0; i < 64; i++)
{
filename = f_name;
fd = open(filename, O_CREAT | O_RDWR);
if (fd < 0)
perror("open");
for (bit = 0; bit < SIZE; bit++)
{
tab[bit] = 0;
write(fd, tab[bit]);
}
close(fd);
}
return (0);
}
<fim_middle>#include <assert.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
int main(void)
{
assert(!!5 || assert(4 || assert(3 || 1)));
return (0);
}
 
#include <stdio.h>
#include <stdlib.h>

typedef struct        s_block
{
struct s_block *prev;
struct s_block *next;
int id;
char data[BLOCK_SIZE];

} t_block;

t_block *ft_lstlast(t_block *lst)
{
if (!lst)
return (NULL);
while (lst->next)
lst = lst->next;
return (lst);
}

 
#include <stdio.h>
#include <stdlib.h>

typedef struct        s_block
{
struct s_block *prev;
struct s_block *next;
int id;
char data[BLOCK_SIZE];

} t_block;

t_block *ft_lstnew(void *content)
{
t_block *new;

if (!(new = (t_block *)malloc(sizeof(t_block))))
exit(1);
new->data = content;
new->next = NULL;
new->prev = NULL;
return (new);
}

 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
