long XXH3_len_4to8_64b_len, XXH3_len_0to16_64b___trans_tmp_3, XXH3_mix2Accs_acc,
    XXH3_64bits_internal___trans_tmp_8;
typedef unsigned long (*XXH3_hashLong64_f)(void *, unsigned long);
void *XXH3_64bits_internal_input;
int XXH3_64bits_internal___trans_tmp_1;
long XXH3_mul128_fold64(long, long);

static void XXH3_mergeAccs(unsigned long param) {
  for (;;) {
    long result = XXH3_mul128_fold64(XXH3_mix2Accs_acc, 0);
    if (result)
      break;
  }
}

static unsigned long XXH3_hashLong_64b_default(void *input, unsigned long len) {
  XXH3_mergeAccs(len * 7);
  return len;
}

long XXH3_64bits_internal(unsigned long len, XXH3_hashLong64_f f_hashLong) {
  if (len <= 16) {
    long keyed =
        XXH3_64bits_internal___trans_tmp_1 ^ XXH3_len_0to16_64b___trans_tmp_3;
    return XXH3_mul128_fold64(keyed, XXH3_len_4to8_64b_len);
  }
  return f_hashLong(XXH3_64bits_internal_input, len);
}

static void XXH_INLINE_XXH3_64bits(unsigned long len) {
  XXH3_64bits_internal(len, XXH3_hashLong_64b_default);
}

void __cmplog_rtn_hook(void) { XXH_INLINE_XXH3_64bits(sizeof(long)); }