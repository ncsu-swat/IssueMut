typedef long mpfr_prec_t;
typedef long mpfr_exp_t;
typedef struct {
  mpfr_prec_t _mpfr_prec;
} __mpfr_struct;
typedef __mpfr_struct mpfr_t[1];
extern _Thread_local mpfr_exp_t __gmpfr_emax;
static _Thread_local mpfr_exp_t previous_emax;
static _Thread_local mpfr_t bound_emax;
extern const mpfr_t __gmpfr_const_log2_RNDD;
extern const mpfr_t __gmpfr_const_log2_RNDU;

typedef enum {
  MPFR_RNDN = 0,
  MPFR_RNDZ,
  MPFR_RNDU,
  MPFR_RNDD,
  MPFR_RNDA,
  MPFR_RNDF,
  MPFR_RNDNA = -1
} mpfr_rnd_t;
typedef __mpfr_struct *mpfr_ptr;
typedef const __mpfr_struct *mpfr_srcptr;
void mpfr_mul(mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);

void foo(void) {
  mpfr_exp_t saved_emax;
  mpfr_exp_t current_emax = __gmpfr_emax;
  mpfr_exp_t prev_emax = previous_emax;

  if (current_emax != prev_emax) {
    saved_emax = current_emax;

    bound_emax->_mpfr_prec = 32;

    mpfr_mul(bound_emax,
             saved_emax < 0 ? __gmpfr_const_log2_RNDD : __gmpfr_const_log2_RNDU,
             MPFR_RNDU);
    previous_emax = saved_emax;
    __gmpfr_emax = saved_emax;
  }
}