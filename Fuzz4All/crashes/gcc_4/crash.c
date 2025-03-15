#include <stdlib.h>
<fim_suffix>a structure definition */
struct element {
        int i;
        int j;
        float k;
        double n;
}e;
 
struct element x,y;
 
struct data {
        int i;
        struct element j;
};
struct data d[10];
 
struct element *iptr,*yptr;
 
enum day {MONDAY=1, TUESDAY, WEDNESDAY};
 
enum day *dayptr;        
 
  
struct list {
        int i;
        struct node *next;
}list;
  
union data {
        int i;
        float f;
}data;
  
struct time {
        int hour;
        int minute;
};
enum time_of_day {MORNING=0, AFTERNOON, EVENING};
 
struct foo {
        int i;
};
struct bar {
        char character;
        struct foo *foo;
};
 
 
struct data {
        int i;
        struct element j;
};
struct data d[10];
  
void foo(int i) {
        printf("%d\n", d[i].i);                 
         
}
 
#define print(x) printf (x)
 
void printer(struct data *array, int length) {
        int i;
        for (i=0; i < length; i++) {
                printf("%d\n", array[i].i);
                printf("%d\n", array[i].j.j);
        }
}
 
struct point mypoint = { 10, 12, 12};  
 
         
        printf("%d\n", mypoint.x);

         
         
        struct element array[20];
        array[2].j = {20,21,22,23}; 
        printf("%d\n", array[2].j.k);

         

 
void assign(struct point *c_point)
{
        c_point->x = 12;
        c_point->y = 12;
}

 
void print_struct(struct point c_point, struct point *cp_point)
{
        printf("struct : %d ; %d\n", cp_point->x, cp_point->y);
        printf("Local : %d ; %d\n", c_point.x, c_point.y);
        printf("local & struct : %p ; %p\n", &c_point, &cp_point);
}
/* You also can use a structure to define the functions that a variable
 * can use, for example if we want to change the value of a variable
 * of type point when a user calls the inc() function or assign_value(), 
 * we don
