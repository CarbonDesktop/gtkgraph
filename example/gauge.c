#include <gtk/gtk.h>
#include "gauge/cade-gauge.h"

gboolean timeout(gpointer data)
{
  CadeGauge *gauge = CADE_GAUGE(data);
  float value = cade_gauge_get_value(gauge);
  if(value < 1)
    value += 0.002;
  else
    value = 0;

  cade_gauge_set_value(gauge, value);
  return G_SOURCE_CONTINUE;
}

int main(int argc, char **argv)
{
  gtk_init(&argc, &argv);

  GtkWidget *w = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

  CadeGauge *gauge = cade_gauge_new();

  gtk_box_pack_end(GTK_BOX(box), GTK_WIDGET(gauge), TRUE, TRUE, 0);

  gtk_container_add(GTK_CONTAINER(w), GTK_WIDGET(box));

  g_timeout_add(10, timeout, gauge);

  gtk_widget_show_all(w);

  gtk_main();
}
