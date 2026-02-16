struct build_id_note {
  char pad[16];
  char hash[20];
};

const struct build_id_note *build_id_note = (const struct build_id_note *)0x5000000;

__attribute__((noinline)) char get_build_id() { return build_id_note->hash[0]; }

int main() {
  get_build_id();
  return 0;
}