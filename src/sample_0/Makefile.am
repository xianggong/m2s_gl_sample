if HAVE_OPENGL

bin_PROGRAMS = $(top_builddir)/bin/native-sample-0 $(top_builddir)/bin/m2s-sample-0

__top_builddir__bin_native_sample_0_SOURCES = sample_0.c
__top_builddir__bin_native_sample_0_LDFLAGS = -static @NATIVE_OPENGL_LDFLAGS@

__top_builddir__bin_m2s_sample_0_SOURCES = sample_0.c
__top_builddir__bin_m2s_sample_0_CFLAGS = @M2S_RUNTIME_CFLAGS@
__top_builddir__bin_m2s_sample_0_LDFLAGS = -static @M2S_RUNTIME_LDFLAGS@
__top_builddir__bin_m2s_sample_0_LDADD = @M2S_RUNTIME_LDADD@

else

bin_PROGRAMS = $(top_builddir)/bin/m2s-sample-0

__top_builddir__bin_m2s_sample_0_SOURCES = sample_0.c
__top_builddir__bin_m2s_sample_0_CFLAGS = @M2S_RUNTIME_CFLAGS@
__top_builddir__bin_m2s_sample_0_LDFLAGS = -static @M2S_RUNTIME_LDFLAGS@
__top_builddir__bin_m2s_sample_0_LDADD = @M2S_RUNTIME_LDADD@

endif
