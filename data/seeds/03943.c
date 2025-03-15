/* Test combinations of UTF-8 in various parts of identifiers.  */
/* { dg-do run } */
/* { dg-xfail-if "" { "powerpc-ibm-aix*" } } */
/* { dg-skip-if "" { ! ucn } } */
/* { dg-options "-std=c99" } */

extern void abort(void);

int π = 3;
int π² = 9;
int πp1 = 4;
int twoπ = 6;
int four_plus_π_ = 7;
int 😀ÀÁÂÃÄÅßàáâãäaåbæçèéêcëìígîïð7ñ9__òóô4õöÆ3ÇÈÉÊËabcÌÍÎÏÐÑÒÓÔÕÖ😄😅🤣😂_ÿ = 2;
int π\u03C0 = 9;

int main() {
  if (π != 3)
    abort();

  if (π² != 9)
    abort();

  if (πp1 != 4)
    abort();

  if (twoπ != 6)
    abort();

  if (four_plus_π_ != 7)
    abort();

  if (😀ÀÁÂÃÄÅßàáâãäaåbæçèéêcëìígîïð7ñ9__òóô4õöÆ3ÇÈÉÊËabcÌÍÎÏÐÑÒÓÔÕÖ😄😅🤣😂_ÿ != 2)
    abort();

  if (ππ != π²)
    abort();
}
