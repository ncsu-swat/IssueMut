typedef unsigned long u64;

template <u64 mask> u64 test(u64 a, u64 b) { return (a & ~mask) | (b & mask); }

template u64 test<0x0000'0000'0000'00f0l>(u64, u64);
template u64 test<0x0000'0000'0000'fff0l>(u64, u64);
template u64 test<0x0000'0000'ffff'fff0l>(u64, u64);
template u64 test<0x0000'ffff'ffff'fff0l>(u64, u64);
template u64 test<0xffff'ffff'ffff'fff0l>(u64, u64);