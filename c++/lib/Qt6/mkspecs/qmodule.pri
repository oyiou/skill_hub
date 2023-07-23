QT_CPU_FEATURES.x86_64 = mmx sse sse2
QT.global_private.enabled_features = gc_binaries reduce_exports sse2 sse3 ssse3 sse4_1 sse4_2 aesni rdrnd rdseed shani alloca_malloc_h alloca system-zlib zstd dbus gui network printsupport sql testlib widgets xml largefile precompile_header sse2 sse3 ssse3 sse4_1 sse4_2 aesni rdrnd rdseed shani simdAlways
QT.global_private.disabled_features = use_bfd_linker use_gold_linker use_lld_linker use_mold_linker android-style-assets private_tests debug reduce_relocations avx f16c avx2 avx512f avx512er avx512cd avx512pf avx512dq avx512bw avx512vl avx512ifma avx512vbmi mips_dsp mips_dspr2 neon arm_crc32 arm_crypto posix_fallocate alloca_h stack-protector-strong dbus-linked libudev dlopen relocatable intelcet
CONFIG += largefile precompile_header sse2 sse3 ssse3 sse4_1 sse4_2 aesni rdrnd rdseed shani simdAlways
QT_COORD_TYPE = double
QT_BUILD_PARTS = libs tools

QMAKE_LIBS_ZLIB = -lz
QMAKE_LIBS_ZSTD = -lzstd
