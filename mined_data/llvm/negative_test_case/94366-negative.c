int main() { return 0; }

int efi_main() { return 0; }

#ifdef MS
int wmain(int, wchar_t *[], wchar_t *[]);
int wWinMain(void *, void *, wchar_t *, int);
int WinMain(void *, void *, char *, int);
bool DllMain(void *, unsigned, void *);

int wmain(int, wchar_t *[], wchar_t *[]) { return 0; }

int wWinMain(void *, void *, wchar_t *, int) { return 0; }

int WinMain(void *, void *, char *, int) { return 0; }

bool DllMain(void *, unsigned, void *) { return true; }
#endif