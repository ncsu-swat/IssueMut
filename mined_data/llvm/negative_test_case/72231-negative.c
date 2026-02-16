#include "callback.h"
#include <omp.h>

__attribute__ ((noinline)) 
void print_task_info_at(int ancestor_level, int id)
{
#pragma omp critical
  {
    int task_type;
char buffer[2048];
ompt_data_t *parallel_data;
ompt_data_t *task_data;
int thread_num;
ompt_get_task_info(ancestor_level, &task_type, &task_data, NULL, &parallel_data,
                   &thread_num);
format_task_type(task_type, buffer);
printf("%" PRIu64 ": ancestor_level=%d id=%d task_type=%s=%d "
       "parallel_id=%" PRIu64 " task_id=%" PRIu64 " thread_num=%d\n",
       ompt_get_thread_data()->value, ancestor_level, id, buffer, task_type,
       parallel_data->value, task_data->value, thread_num);
}
}
;

int main() {

#pragma omp parallel num_threads(2)
  {
#pragma omp barrier
    if (omp_get_thread_num() == 1) {
      
      
      
#pragma omp task if (0)
      {
        
        print_task_info_at(0, 1);
        print_task_info_at(1, 0);
      };
    }
  }

  
  
  
  
  

  
  

  
  
  
  

  
  
  
  
  

  return 0;
}