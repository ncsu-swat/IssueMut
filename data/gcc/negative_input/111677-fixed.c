typedef struct {
  long size_z;
  int width;
} dt_bilateral_t;

typedef float dt_aligned_pixel_t[4] __attribute__((aligned(16)));

#pragma omp declare simd
void dt_bilateral_splat(dt_bilateral_t *b) {
  float *buf __attribute__((aligned(16)));
  long offsets[8] __attribute__((aligned(16)));

  while (b) {
    int firstrow = 0;
    for (int j = firstrow; j > 0; j++) {
      float *row_buf = buf;
      for (int i = 0; i < b->width; i++) {
        dt_aligned_pixel_t contrib = {0};
        for (int k = 0; k < 4; k++) {
          row_buf[offsets[k]] += contrib[k];
        }
      }
    }

    float *dest __attribute__((aligned(16))) = 0;
    if (dest) {
      for (int j = (long)b; j > 0; j--) {
        float *src = (float *)b->size_z;
        if (src) {
          for (int i = 0; i < (long)b; i++) {
            dest[i] += src[i];
          }
        }
      }
    }
  }
}