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

gboolean value_changed(GtkRange *r, GtkScrollType scroll, gdouble value, CadeGauge *gauge)
{
  cade_gauge_set_value(gauge, value);
}

int main(int argc, char **argv)
{
  gtk_init(&argc, &argv);

  GtkWidget *w = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  CadeGauge *mem = cade_gauge_new();
  CadeGauge *cpu = cade_gauge_new();
  CadeGauge *custom = cade_gauge_new();

  GtkWidget *grid = gtk_grid_new();

  GtkGrid *g = GTK_GRID(grid);
  gtk_grid_set_column_spacing(g, 10);

  gtk_grid_attach(g, gtk_label_new("Processor"), 0, 0, 1, 1);
  gtk_grid_attach(g, gtk_label_new("Memory"), 1, 0, 1, 1);
  gtk_grid_attach(g, gtk_label_new("Custom"), 2, 0, 1, 1);
  gtk_grid_attach(g, GTK_WIDGET(cpu), 0, 1, 1, 1);
  gtk_grid_attach(g, GTK_WIDGET(mem), 1, 1, 1, 1);
  gtk_grid_attach(g, GTK_WIDGET(custom), 2, 1, 1, 1);

  gtk_grid_attach(g, gtk_label_new("Change Value:"), 0, 2, 3, 1);

  GtkWidget *scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 1, 0.001);
  gtk_grid_attach(g, GTK_WIDGET(scale), 0, 3, 3, 1);
  g_signal_connect(scale, "change-value", G_CALLBACK(value_changed), custom);


  g_timeout_add(10, timeout, mem);
  g_timeout_add(7, timeout, cpu);
  gtk_container_add(GTK_CONTAINER(w), grid);
  g_signal_connect_swapped(w, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show_all(w);

  gtk_main();
}
