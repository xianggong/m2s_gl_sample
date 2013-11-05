if HAVE_OPENGL

bin_PROGRAMS = $(top_builddir)/bin/native-sample-1

if HAVE_M2S_OPENGL

bin_PROGRAMS += $(top_builddir)/bin/m2s-sample-1

__top_builddir__bin_m2s_sample_1_SOURCES = sample_1.c
__top_builddir__bin_m2s_sample_1_CFLAGS = @M2S_RUNTIME_CFLAGS@
__top_builddir__bin_m2s_sample_1_LDFLAGS = -static -lm @M2S_RUNTIME_LDFLAGS@
__top_builddir__bin_m2s_sample_1_LDADD = @M2S_RUNTIME_LDADD@

endif

__top_builddir__bin_native_sample_1_SOURCES = sample_1.c
__top_builddir__bin_native_sample_1_LDFLAGS = -lm @NATIVE_OPENGL_LDFLAGS@

endif
