#include <assert.h>
#include <omp-tools.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static int no_schedule = 1;

void callback_ompt_work(ompt_work_t work_type, ompt_scope_endpoint_t endpoint,
                        ompt_data_t *parallel_data, ompt_data_t *task_data,
                        uint64_t count, const void *codeptr_ra) {
  switch (work_type) {
  case ompt_work_loop:
    printf("ompt_work_loop detected\n");
    break;
  case ompt_work_loop_static:
  case ompt_work_loop_dynamic:
  case ompt_work_loop_guided:
  case ompt_work_loop_other:
    no_schedule = 0;
    break;
  default:
    break;
  }
}

static int ompt_initialize(ompt_function_lookup_t lookup,
                           int initial_device_num, ompt_data_t *tool_data) {
  ompt_set_callback_t set_cb = (ompt_set_callback_t)lookup("ompt_set_callback");
  set_cb(ompt_callback_work, (ompt_callback_t)&callback_ompt_work);
  return 1; /* non-zero indicates success for OMPT runtime. */
}

static void ompt_finalize(ompt_data_t *tool_data) { assert(no_schedule == 0); }

ompt_start_tool_result_t *ompt_start_tool(unsigned int omp_version,
                                          const char *runtime_version) {
  static ompt_start_tool_result_t ompt_start_tool_result = {
      &ompt_initialize, &ompt_finalize, ompt_data_none};
  return &ompt_start_tool_result;
}

int main(void) {
#pragma omp parallel for schedule(static)
  for (unsigned i = 0; i < 100; ++i) {
  }

#pragma omp parallel for schedule(dynamic)
  for (unsigned i = 0; i < 100; ++i) {
  }

#pragma omp parallel for schedule(guided)
  for (unsigned i = 0; i < 100; ++i) {
  }

  return 0;
}