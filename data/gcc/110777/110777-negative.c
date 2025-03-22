void pm_message(int);
int *findOrAddBackgroundInPalette_palette_pnm;
static void findOrAddBackgroundInPalette(unsigned *paletteSizeP,
                                         int *backgroundIndexP) {
  if (*paletteSizeP) {
    *backgroundIndexP = (*paletteSizeP)++;
    pm_message(0);
  }
  pm_message(findOrAddBackgroundInPalette_palette_pnm[*backgroundIndexP]);
}
void computeColorMap(int *backgroundIndexP) {
  unsigned paletteSize = 0;
  findOrAddBackgroundInPalette(&paletteSize, backgroundIndexP);
}
int main() {
  unsigned backgroundIndex = 0;
  findOrAddBackgroundInPalette_palette_pnm = (int *)calloc(100, sizeof(int));
  _setjmp();
  computeColorMap(&backgroundIndex);
  free(findOrAddBackgroundInPalette_palette_pnm);
  return 0;
}