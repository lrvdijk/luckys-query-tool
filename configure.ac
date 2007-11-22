dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(luckys-query-tool, 0.1)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_CONFIG_HEADER(config.h)
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CXX
AM_PROG_CC_STDC
AC_HEADER_STDC




dnl ***************************************************************************
dnl Internatinalization
dnl ***************************************************************************
GETTEXT_PACKAGE=luckys-query-tool
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])

PACKAGE_LOCALEDIR=[${datadir}/locale]
AC_SUBST(PACKAGE_LOCALEDIR)



AM_PROG_LIBTOOL



PKG_CHECK_MODULES(LUCKYS_QUERY_TOOL, [gtkmm-2.4 >= 2.8 libglademm-2.4 >= 2.6    ])
AC_SUBST(LUCKYS_QUERY_TOOL_CFLAGS)
AC_SUBST(LUCKYS_QUERY_TOOL_LIBS)




AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
])
