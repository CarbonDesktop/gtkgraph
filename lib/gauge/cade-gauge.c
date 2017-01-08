#include "cade-gauge.h"

struct _CadeGauge {
  GtkWidget parent_instance;
};

struct _CadeGaugeClass {
  GtkWidgetClass parent_class;
};

G_DEFINE_TYPE (CadeGauge, cade_gauge, GTK_TYPE_WIDGET)

static void
cade_gauge_class_init (CadeGaugeClass *klass)
{
}

static void
cade_gauge_init (CadeGauge *self)
{
}

CadeGauge *
cade_gauge_new (void)
{
  return g_object_new (CADE_TYPE_GAUGE, NULL);
}
