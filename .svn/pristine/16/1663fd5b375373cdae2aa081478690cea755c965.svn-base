AC_INIT(./)
AM_INIT_AUTOMAKE(gameone, 0.1.0)

AC_CONFIG_HEADERS(config.h)

RELEASE=0:1:0
VERSION=0:0:0

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
#AM_PROG_LIBTOOL
##########################################################################
# debug compilation support
##########################################################################

AC_MSG_CHECKING([whether to use ahtlon-tbird march])
AC_ARG_ENABLE([tbird],
    [AS_HELP_STRING([--enable-tbird],
        [enable athlon tbird optimization generation (def=no)])],
    [tbirdit="$enableval"],
    [tbirdit=no])
AC_MSG_RESULT([$debugit])

if test x"$tbirdit" = x"yes"; then
    AC_DEFINE([TBIRD],[],[Debug Mode])
    AM_CXXFLAGS="$AM_CXXFLAGS -march=athlon-tbird"
fi

##########################################################################
##########################################################################
# debug compilation support
##########################################################################

AC_MSG_CHECKING([whether to build with debug information])
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug],
        [enable debug data generation (def=no)])],
    [debugit="$enableval"],
    [debugit=no])
AC_MSG_RESULT([$debugit])

if test x"$debugit" = x"yes"; then
    AC_DEFINE([DEBUG],[],[Debug Mode])
    AM_CXXFLAGS="$AM_CXXFLAGS -g3 -Wall -Wno-uninitialized -O0"
else
    AC_DEFINE([NDEBUG],[],[No-debug Mode])
    AM_CXXFLAGS="$AM_CXXFLAGS -O3 -floop-parallelize-all -ftree-parallelize-loops=4"
fi

##########################################################################


PKG_CHECK_MODULES([OGRE], [OGRE >= 1.7])
AC_SUBST(OGRE_CFLAGS)
AC_SUBST(OGRE_LIBS)
    
PKG_CHECK_MODULES([OIS], [OIS >= 1.0])
AC_SUBST(OIS_CFLAGS)
AC_SUBST(OIS_LIBS)

PKG_CHECK_MODULES([CEGUI], [CEGUI >= 0.7])
AC_SUBST(CEGUI_CFLAGS)
AC_SUBST(CEGUI_LIBS)

AC_ARG_WITH([mysql-include-path],
	      [AS_HELP_STRING([--with-mysql-include-path],
			          [location of the MySQL headers, defaults to /usr/include/mysql])],
				    [MYSQL_CFLAGS="-I$withval"],
				      [MYSQL_CFLAGS='-I/usr/include/mysql'])
AC_SUBST([MYSQL_CFLAGS])
AC_SUBST([AM_CXXFLAGS])


AC_ARG_WITH([mysql-lib-path],
	      [AS_HELP_STRING([--with-mysql-lib-path], [location of the MySQL libraries])],
	        [MYSQL_LIBS="-L$withval -lmysqlclient"],
		  [MYSQL_LIBS='-lmysqlclient'])
AC_SUBST([MYSQL_LIBS])
AC_OUTPUT(Makefile src/Makefile)
