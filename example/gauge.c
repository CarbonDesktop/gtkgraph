#include <gtk/gtk.h>
#include "gauge/cade-gauge.h"

int main(int argc, char **argv)
{
  gtk_init(&argc, &argv);

  GtkWidget *w = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  CadeGauge *gauge = cade_gauge_new();
  gtk_container_add(GTK_CONTAINER(w), GTK_WIDGET(gauge));

  gtk_widget_show_all(w);

  gtk_main();
}
