#include "cade-gauge.h"
#include <string.h>

struct _CadeGauge {
  GtkWidget parent_instance;
  float value;
};

struct _CadeGaugeClass {
  GtkWidgetClass parent_class;
};

G_DEFINE_TYPE (CadeGauge, cade_gauge, GTK_TYPE_WIDGET)

static GtkSizeRequestMode cade_gauge_get_request_mode(GtkWidget *w)
{
  return GTK_SIZE_REQUEST_CONSTANT_SIZE;
}

/* Size Functions */

static void cade_gauge_get_preferred_height(GtkWidget *w, gint *min, gint *natural)
{
  *min = 75;
  *natural = 75;
}

static void cade_gauge_get_preferred_width(GtkWidget *w, gint *min, gint *natural)
{
  *min = 150;
  *natural = 150;
}

static void cade_gauge_get_preferred_width_for_height(GtkWidget *w, gint height, gint *min, gint *natural)
{
  *min = 2* height;
  *natural = 2* height;
}

static void cade_gauge_get_preferred_heigth_for_width(GtkWidget *w, gint width, gint *min, gint *natural)
{
  *min = 0.5 * width;
  *natural = 0.5 * width;
}

/* Allocation Functions */

static void cade_gauge_allocate_size(GtkWidget *w, GtkAllocation *alloc)
{
  gtk_widget_set_allocation(w, alloc);
  if(gtk_widget_get_has_window(w))
  {
    GdkWindow *window = gtk_widget_get_window(w);
    if(window)
      gdk_window_move_resize(window, alloc->x, alloc->y, alloc->width, alloc->height);
  }
}

static void cade_gauge_realize(GtkWidget *w)
{
  gtk_widget_set_realized(w,TRUE);
  if(!gtk_widget_get_has_window(w))
  {
    GdkWindow *window = gtk_widget_get_parent_window(w);
    g_object_ref(window);
    gtk_widget_set_window(w, window);
  }
  else
  {
    GdkWindowAttr attributes;
    memset(&attributes, 0, sizeof(attributes));

    GtkAllocation alloc;
    gtk_widget_get_allocation(w, &alloc);
    attributes.x = alloc.x;
    attributes.y = alloc.y;
    attributes.width = alloc.width;
    attributes.height = alloc.height;

    attributes.event_mask = gtk_widget_get_events(w) | GDK_EXPOSURE_MASK;
    attributes.window_type = GDK_WINDOW_CHILD;
    attributes.wclass = GDK_INPUT_OUTPUT;

    GdkWindow *window = gdk_window_new(gtk_widget_get_parent_window(w), &attributes, GDK_WA_X | GDK_WA_Y);

    gtk_widget_set_window(w, window);
    gdk_window_set_user_data(window, G_OBJECT(w));
  }
}

/* Render */

static gboolean cade_gauge_draw(GtkWidget *w, cairo_t *cr)
{
  GtkAllocation alloc;
  gtk_widget_get_allocation(w, &alloc);


  GtkStyleContext *style = gtk_widget_get_style_context(w);

  gtk_render_background(style, cr, 0, 0, alloc.width, alloc.height);

  CadeGauge *gauge = CADE_GAUGE(w);

  cairo_set_source_rgb(cr, 0, 0.5, 1);

  cairo_set_line_width(cr, 50);

  int radius = alloc.height - 25;
  if(alloc.width / 2 < alloc.height)
  {
    radius = alloc.width / 2 - 25;
  }

  cairo_arc(cr,alloc.width/2, alloc.height, radius, 3.141, (gauge->value+1) * 3.141);
  cairo_stroke(cr);

  cairo_set_line_width(cr, 2);

  cairo_arc(cr,alloc.width/2, alloc.height, radius-24, 3.141, 2 * 3.141);
  cairo_stroke(cr);
  cairo_arc(cr,alloc.width/2, alloc.height, radius+24, 3.141, 2 * 3.141);
  cairo_stroke(cr);

  cairo_move_to(cr, 0, alloc.height -1);
  cairo_line_to(cr, 50, alloc.height -1);
  cairo_stroke(cr);

  cairo_move_to(cr, alloc.width - 50, alloc.height -1);
  cairo_line_to(cr, alloc.width, alloc.height -1);
  cairo_stroke(cr);

  gchar *text = g_strdup_printf("%d %%", (int) (gauge->value * 100) );

  cairo_text_extents_t extents;
  cairo_text_extents(cr, text, &extents);
  double x = (alloc.width / 2) - (extents.width/2) + extents.x_bearing;
  double y = alloc.height - extents.height - extents.y_bearing;

  cairo_move_to(cr,x,y);
  cairo_show_text(cr, text);

  g_free(text);
  return TRUE;
}

static void
cade_gauge_class_init (CadeGaugeClass *klass)
{
  GtkWidgetClass *wc = GTK_WIDGET_CLASS(klass);
  wc->get_request_mode = cade_gauge_get_request_mode;
  wc->get_preferred_width = cade_gauge_get_preferred_width;
  wc->get_preferred_height = cade_gauge_get_preferred_height;
  wc->get_preferred_height_for_width = cade_gauge_get_preferred_heigth_for_width;
  wc->get_preferred_width_for_height = cade_gauge_get_preferred_width_for_height;
  wc->size_allocate = cade_gauge_allocate_size;
  wc->realize = cade_gauge_realize;
  wc->draw = cade_gauge_draw;
}

static void
cade_gauge_init (CadeGauge *self)
{
  self->value = 0;
}

CadeGauge *
cade_gauge_new (void)
{
  return g_object_new (CADE_TYPE_GAUGE, NULL);
}

float cade_gauge_get_value(CadeGauge *gauge)
{
  if(gauge)
    return gauge->value;

  return 0;
}

void cade_gauge_set_value(CadeGauge *gauge, float value)
{
  gauge->value = value;
  gtk_widget_queue_draw(GTK_WIDGET(gauge));
}
