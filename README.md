* How to compile
	1. Edit M2S_RUNTIME_CFLAGS and M2S_RUNTIME_LDFLAGS in configure.ac so it points to correct Multi2Sim directory
	2. libtoolize
	3. aclocal
	4. autoconf
	5. automake --add-missing
	6. ./configure
	7. make

Binaries will be generated in bin directory
