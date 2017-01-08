bin_PROGRAMS = gauge

gauge_SOURCES = gauge.c
gauge_LDADD = ${GTK3_LIBS} ${GObject_LIBS} $(X11_LIBS)
gauge_LDFLAGS = -lcade-graph -L=$(top_builddir)/lib/.libs/ -Wl,-rpath=$(top_builddir)/lib/.libs/
gauge_CFLAGS = ${GTK3_CFLAGS} ${GObject_CFLAGS} -std=c99 -I$(top_srcdir)/lib
