AC_INIT([m2s_gl_sample], [0.0])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([nostdinc])
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CXX
AC_PROG_INSTALL

# Libtool
LT_INIT
AC_PROG_LIBTOOL

# Silent rules if supported
ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

##################
# Test flag '-m32'
##################

saved_flags="$CFLAGS"
CFLAGS="-m32"
AC_MSG_CHECKING([for -m32 compiler flag])
have_m32_flag="no"
AC_LINK_IFELSE(
	[
		AC_LANG_PROGRAM(
			[[#include <stdio.h>]],
			[[ printf("hello world\n"); ]]
		)
	],
	[
		have_m32_flag="yes"
	]
)
AC_MSG_RESULT($have_m32_flag)
CFLAGS="$saved_flags"

# Show warning
if test "x$have_m32_flag" = "xno"
then
	AC_MSG_WARN([

	Your compiler does not support 32-bit compilation using the '-m32' flag.
	This mode is needed to compile the this OpenGL sample package

	If you want to support this feature, please install the 32-bit gcc
	libraries. For example, this can be done in Ubuntu 12.04 by running
	command:

		sudo apt-get install lib32gcc1 gcc-multilib]
	)
fi

# Conditional for Makefile.am
AM_CONDITIONAL(HAVE_M32_FLAG, test x$have_m32_flag = xyes)

###############
# Test for libm
###############

AC_CHECK_HEADER([math.h], [], [AC_MSG_ERROR([cannot find header math.h])])
AC_MSG_CHECKING([for -lm])

# Use new LDFLAGS
saved_libs="$LIBS"
LIBS="-lm"

# Try program
AC_LINK_IFELSE(
	[
		AC_LANG_PROGRAM([[#include <math.h>]], [[return sin(1.0);]])
	],
	[
		AC_MSG_RESULT(yes)
	],
	[
		AC_MSG_RESULT(no)
		AC_MSG_ERROR([
	
	The math library (libmath) is not present in your system. Please make
	sure that your linker supports the -lm flag.]
		)
	]
)

# Restore original LDFLAGS
LIBS="$saved_libs"

#############
# Test OpenGL
#############

# Assume that we have OpenGL
have_opengl=yes

# Check headers
AC_CHECK_HEADER([GL/glut.h], [], [have_opengl=no])
AC_CHECK_HEADER([GL/gl.h], [], [have_opengl=no])
AC_CHECK_HEADER([GL/glu.h], [], [have_opengl=no])
AC_CHECK_HEADER([GL/glew.h], [], [have_opengl=no])

# Linker flags for OpenGL
NATIVE_OPENGL_LDFLAGS="-lGL -lGLU -lGLEW -lglut"
AC_SUBST([NATIVE_OPENGL_LDFLAGS])

# Export temporary LDFLAGS
saved_libs="$LIBS"
LIBS="$NATIVE_OPENGL_LDFLAGS"

# Try link
AC_MSG_CHECKING([for $NATIVE_OPENGL_LDFLAGS])
AC_LINK_IFELSE(
	[
		AC_LANG_PROGRAM(
			[[
				#include <GL/glut.h>
				#include <GL/gl.h>
				#include <GL/glu.h>
			]],
			[[
				glutInit(NULL, NULL);
				glBegin(0);
				gluOrtho2D(0.0, 0.0, 0.0, 0.0);
			]]
		)
	],
	[
		AC_MSG_RESULT(yes)
	],
	[
		AC_MSG_RESULT(no)
		have_opengl=no
	]
)

# Restore original LIBS
LIBS="$saved_libs"

# Message if not present
if test "x$have_opengl" = "xno"
then
	AC_MSG_WARN([

Your system lacks at least one of the graphics libraries required to
compile this OpenGL sample packege. These libraries are OpenGL, GLU,
GLUT, and GLEW. Please make sure that your linker supports flags

	$NATIVE_OPENGL_LDFLAGS

In Ubuntu, the following command is suggested to install the missing
libraries:

	sudo apt-get install freeglut3-dev libglew-dev]
)

fi

# Define macro for Automake and gcc
AM_CONDITIONAL(HAVE_OPENGL, test x$have_opengl = xyes)
if test x$have_opengl == xyes
then
	AC_DEFINE(HAVE_OPENGL, [1])
fi


##################
# M2S Headers/Libs
##################

# Assume that we have Multi2sim OpenGL runtime libraries
have_m2s_opengl=yes

# Check if M2S_ROOT environment variable is set
if test "x$M2S_ROOT" = "xno"
then
	have_m2s_opengl=no
fi

# Linker flags for OpenGL
M2S_RUNTIME_LDFLAGS="-lm2s-glut -lm2s-glew -lm2s-glu -lm2s-opengl"
AC_SUBST([M2S_RUNTIME_LDFLAGS])

# Export temporary flags
saved_libs="$LIBS"
saved_cflags="$CFLAGS"
saved_ldflags="$LDFLAGS"

LIBS="$M2S_RUNTIME_LDFLAGS"
CFLAGS="-I$M2S_ROOT/runtime/include"
LDFLAGS="-L$M2S_ROOT/lib/.libs/"

# Try link
AC_MSG_CHECKING([for $M2S_RUNTIME_LDFLAGS])
AC_LINK_IFELSE(
	[
		AC_LANG_PROGRAM(
			[[
				#include <GL/glut.h>
				#include <GL/gl.h>
				#include <GL/glu.h>
			]],
			[[
				glutInit(NULL, NULL);
				glBegin(0);
				gluOrtho2D(0.0, 0.0, 0.0, 0.0);
			]]
		)
	],
	[
		AC_MSG_RESULT(yes)
	],
	[
		AC_MSG_RESULT(no)
		have_m2s_opengl=no
	]
)

# Restore original 
LIBS="$saved_libs"
CFLAGS="$saved_cflags"
LD_FLAGS="$saved_ldflags"

# Message if not present
if test "x$have_m2s_opengl" == "xno"
then
	AC_MSG_WARN([

Your system lacks at least one of the graphics libraries required to
compile this OpenGL sample package. Please make sure that your linker
supports flags

	$M2S_RUNTIME_LDFLAGS

You need to compile Multi2Sim and set M2S_ROOT environment variable

	export M2S_ROOT=PATH_TO_MULTI2SIM

])
fi

# Define macro for Automake and gcc
AM_CONDITIONAL(HAVE_M2S_OPENGL, test x$have_m2s_opengl == xyes)
if test x$have_m2s_opengl = xyes
then
	AC_DEFINE(HAVE_M2S_OPENGL, [1])
	M2S_RUNTIME_CFLAGS="-I$M2S_ROOT/runtime/include/GL"
	M2S_RUNTIME_LDFLAGS="-L$M2S_ROOT/lib/.libs"
	M2S_RUNTIME_LDADD="-static -lm2s-glut -lm2s-glew -lm2s-glu -lm2s-opengl"

	AC_SUBST([M2S_RUNTIME_CFLAGS])
	AC_SUBST([M2S_RUNTIME_LDFLAGS])
	AC_SUBST([M2S_RUNTIME_LDADD])
fi

###########
# Makefiles
###########

AC_CONFIG_FILES([
Makefile
src/Makefile
src/sample_0/Makefile
src/sample_1/Makefile
])

AC_OUTPUT
