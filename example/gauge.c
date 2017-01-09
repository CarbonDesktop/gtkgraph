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
  CadeGauge *mem = cade_gauge_new();
  CadeGauge *cpu = cade_gauge_new();

  GtkWidget *grid = gtk_grid_new();

  GtkGrid *g = GTK_GRID(grid);
  gtk_grid_set_column_spacing(g, 10);

  gtk_grid_attach(g, gtk_label_new("Processor"), 0, 0, 1, 1);
  gtk_grid_attach(g, gtk_label_new("Memory"), 1, 0, 1, 1);
  gtk_grid_attach(g, GTK_WIDGET(cpu), 0, 1, 1, 1);
  gtk_grid_attach(g, GTK_WIDGET(mem), 1, 1, 1, 1);


  g_timeout_add(10, timeout, mem);
  g_timeout_add(7, timeout, cpu);
  gtk_container_add(GTK_CONTAINER(w), grid);
  g_signal_connect_swapped(w, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show_all(w);

  gtk_main();
}
