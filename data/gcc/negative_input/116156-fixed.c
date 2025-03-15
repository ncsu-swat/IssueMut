struct jpeg_compress_struct {
  int X_density;
};
void gg();
int h(const char *, const char *) __attribute((pure));
int h1(const char *) __attribute((pure));
int f1();
void real_save_jpeg(char **keys, char *values) {
  struct jpeg_compress_struct cinfo;
  int x_density = 0;
  while (*keys) {
    if (h1(*keys) == 0)
      gg();
    if (h1(*keys) == 0) {
      if (!*values)
        x_density = -1;
      if (x_density <= 0)
        gg();
    }
  }
  if (f1())
    cinfo.X_density = x_density;
}