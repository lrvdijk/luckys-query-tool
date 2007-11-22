## Process this file with automake to produce Makefile.in

## Created by Anjuta

gladedir = $(datadir)/luckys-query-tool/glade
glade_DATA = luckys-query-tool.glade

INCLUDES = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(LUCKYS_QUERY_TOOL_CFLAGS)

dnl AM_CFLAGS =\
dnl	 -Wall\
dnl	 -g \
dnl	 -DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\"
	 
AM_CPPFLAGS =\
	 -Wall\
	 -g \
	 -DPACKAGE_LOCALEDIR=\"${PACKAGE_LOCALEDIR}\"

bin_PROGRAMS = luckys-query-tool

luckys_query_tool_SOURCES = \
	main.cc            \
	MainWindow.cpp            \
	MainWindow.h            \
	Player.cpp            \
	Player.h            \
	Protocol.cpp            \
	Protocol.h            \
	QuakeWars.cpp            \
	QuakeWars.h            \
	Socket.cpp            \
	Socket.h            \
	stdinc.h            \
	TcpClient.cpp            \
	UdpClient.cpp            \
	utils.h            \
	Packet.h            \
	Packet.cpp

luckys_query_tool_LDFLAGS = 

luckys_query_tool_LDADD = $(LUCKYS_QUERY_TOOL_LIBS)

EXTRA_DIST = $(glade_DATA)
