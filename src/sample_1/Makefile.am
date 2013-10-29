if HAVE_OPENGL

bin_PROGRAMS = $(top_builddir)/bin/native-sample-1 $(top_builddir)/bin/m2s-sample-1

__top_builddir__bin_native_sample_1_SOURCES = sample_1.c
__top_builddir__bin_native_sample_1_LDFLAGS = -static @NATIVE_OPENGL_LDFLAGS@ -lm

__top_builddir__bin_m2s_sample_1_SOURCES = sample_1.c
__top_builddir__bin_m2s_sample_1_CFLAGS = @M2S_RUNTIME_CFLAGS@
__top_builddir__bin_m2s_sample_1_LDFLAGS = -static @M2S_RUNTIME_LDFLAGS@ -lm
__top_builddir__bin_m2s_sample_1_LDADD = @M2S_RUNTIME_LDADD@

else

bin_PROGRAMS = $(top_builddir)/bin/m2s-sample-1

__top_builddir__bin_m2s_sample_1_SOURCES = sample_1.c
__top_builddir__bin_m2s_sample_1_CFLAGS = @M2S_RUNTIME_CFLAGS@
__top_builddir__bin_m2s_sample_1_LDFLAGS = -static @M2S_RUNTIME_LDFLAGS@ -lm
__top_builddir__bin_m2s_sample_1_LDADD = @M2S_RUNTIME_LDADD@

endif
