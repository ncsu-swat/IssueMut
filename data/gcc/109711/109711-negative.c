void lspf2lpc();

void interpolate_lpc(int subframe_num) {
  float weight = 0.25 * subframe_num + 1;
  if (weight)
    lspf2lpc();
}

void qcelp_decode_frame() {
  int i = 0;
  for (;; i++)
    interpolate_lpc(i);
}