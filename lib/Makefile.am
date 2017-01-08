lib_LTLIBRARIES = libcade-graph.la

libcade_graph_la_SOURCES = gauge/cade-gauge.c
nobase_include_HEADERS = gauge/cade-gauge.h

libcade_graph_la_LIBADD = ${GTK3_LIBS} ${GObject_LIBS}
libcade_graph_la_CFLAGS = ${GTK3_CFLAGS} ${GObject_CFLAGS} -std=c99 -I$(top_srcdir)/lib/
