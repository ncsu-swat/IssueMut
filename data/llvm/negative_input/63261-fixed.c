#include <assert.h>
#include <inttypes.h>
#include <omp-tools.h>
#include <omp.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>



void skip() {
  
  sleep(1);
}

void nest_work(omp_nest_lock_t *lck) {
  omp_set_nest_lock(lck);
  sleep(1);
  omp_unset_nest_lock(lck);
}

int main() {
  
  omp_lock_t lck;
  omp_init_lock(&lck);

#pragma omp parallel shared(lck) num_threads(2)
  {
    while (!omp_test_lock(&lck)) {
      skip();
    }
    sleep(1);
    omp_unset_lock(&lck);
  }

  omp_destroy_lock(&lck);

  
  omp_nest_lock_t nest_lck;
  omp_init_nest_lock(&nest_lck);

#pragma omp parallel shared(nest_lck) num_threads(2)
  {
    while (!omp_test_nest_lock(&nest_lck)) {
      skip();
    }
    nest_work(&nest_lck);
    omp_unset_nest_lock(&nest_lck);
  }

  omp_destroy_nest_lock(&nest_lck);

  return 0;
}



int32_t ompt_mutex_test_lock_kind_encountered = 0;
_Thread_local int32_t ompt_tool_tid =
    -1; 

static const char *mutex2string(ompt_mutex_t t) {
  switch (t) {
  case ompt_mutex_lock:
    return "lock";
  case ompt_mutex_test_lock:
    return "test_lock";
  case ompt_mutex_nest_lock:
    return "nest_lock";
  case ompt_mutex_test_nest_lock:
    return "test_nest_lock";
  case ompt_mutex_critical:
    return "critical";
  case ompt_mutex_atomic:
    return "atomic";
  case ompt_mutex_ordered:
    return "ordered";
  }
  assert(false);
  return "";
}

static const char *scope_endpoint2string(ompt_scope_endpoint_t t) {
  switch (t) {
  case ompt_scope_begin:
    return "begin";
  case ompt_scope_end:
    return "end";
  case ompt_scope_beginend:
    return "beginend";
  }
  assert(false);
  return "";
}

void thread_begin_cb(ompt_thread_t thread_type, ompt_data_t *thread_data) {
  assert(ompt_tool_tid == -1);
  static atomic_int_least32_t thread_counter = 1; 
  ompt_tool_tid = atomic_fetch_add(&thread_counter, 1);
  thread_data->value = ompt_tool_tid;
}

void lock_init_cb(ompt_mutex_t kind, unsigned int hint, unsigned int impl,
                  ompt_wait_id_t wait_id, const void *codeptr_ra) {
  printf("[%s] tid = %" PRId32 " | kind = %s | wait_id = %" PRIu64
         " | codep `ompt_callback_mutetr_ra = %p\n",
         __FUNCTION__, ompt_tool_tid, mutex2string(kind), wait_id, codeptr_ra);
}

void lock_destroy_cb(ompt_mutex_t kind, ompt_wait_id_t wait_id,
                     const void *codeptr_ra) {
  printf("[%s] tid = %" PRId32 " | kind = %s | wait_id = %" PRIu64
         " | codeptr_ra = %p\n",
         __FUNCTION__, ompt_tool_tid, mutex2string(kind), wait_id, codeptr_ra);
}

void mutex_acquire_cb(ompt_mutex_t kind, unsigned int hint, unsigned int impl,
                      ompt_wait_id_t wait_id, const void *codeptr_ra) {
  printf("[%s] tid = %" PRId32 " | kind = %s | wait_id = %" PRIu64
         " | codeptr_ra = %p\n",
         __FUNCTION__, ompt_tool_tid, mutex2string(kind), wait_id, codeptr_ra);
  if( kind == ompt_mutex_test_lock || kind == ompt_mutex_lock ||
      kind == ompt_mutex_test_nest_lock || kind == ompt_mutex_nest_lock ) {
    ompt_mutex_test_lock_kind_encountered = 1;
  }
}

void mutex_acquired_cb(ompt_mutex_t kind, ompt_wait_id_t wait_id,
                       const void *codeptr_ra) {
  printf("[%s] tid = %" PRId32 " | kind = %s | wait_id = %" PRIu64
         " | codeptr_ra = %p\n",
         __FUNCTION__, ompt_tool_tid, mutex2string(kind), wait_id, codeptr_ra);
  if( kind == ompt_mutex_test_lock || kind == ompt_mutex_lock ||
      kind == ompt_mutex_test_nest_lock || kind == ompt_mutex_nest_lock ) {
    ompt_mutex_test_lock_kind_encountered = 1;
  }
}

void mutex_released_cb(ompt_mutex_t kind, ompt_wait_id_t wait_id,
                       const void *codeptr_ra) {
  printf("[%s] tid = %" PRId32 " | kind = %s | wait_id = %" PRIu64
         " | codeptr_ra = %p\n",
         __FUNCTION__, ompt_tool_tid, mutex2string(kind), wait_id, codeptr_ra);
}

static int my_initialize_tool(ompt_function_lookup_t lookup,
                              int initial_device_num, ompt_data_t *tool_data) {
  printf("[%s] tid = %" PRId32 " | initial_device_num %d\n", __FUNCTION__,
         ompt_tool_tid, initial_device_num);
  ompt_set_callback_t set_callback =
      (ompt_set_callback_t)lookup("ompt_set_callback");

  set_callback(ompt_callback_thread_begin, (ompt_callback_t)&thread_begin_cb);
  set_callback(ompt_callback_lock_init, (ompt_callback_t)&lock_init_cb);
  set_callback(ompt_callback_lock_destroy, (ompt_callback_t)&lock_destroy_cb);
  set_callback(ompt_callback_mutex_acquire, (ompt_callback_t)&mutex_acquire_cb);
  set_callback(ompt_callback_mutex_acquired,
               (ompt_callback_t)&mutex_acquired_cb);
  set_callback(ompt_callback_mutex_released,
               (ompt_callback_t)&mutex_released_cb);

  return 1; 
}

static void my_finalize_tool(ompt_data_t *tool_data) {
  printf("[%s] tid = %" PRId32 "\n", __FUNCTION__, ompt_tool_tid);
  assert( ompt_mutex_test_lock_kind_encountered == 1 );
}

ompt_start_tool_result_t *ompt_start_tool(unsigned int omp_version,
                                          const char *runtime_version) {
  setbuf(stdout, NULL);
  printf("[%s] tid = %" PRId32 " | omp_version %d | runtime_version = \'%s\'\n",
         __FUNCTION__, ompt_tool_tid, omp_version, runtime_version);
  static ompt_start_tool_result_t tool = {&my_initialize_tool,
                                          &my_finalize_tool, ompt_data_none};
  return &tool;
}