#ifndef __CADE_GAUGE_H__
#define __CADE_GAUGE_H__

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CADE_TYPE_GAUGE            (cade_gauge_get_type ())
#define CADE_GAUGE(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_GAUGE, CadeGauge))
#define CADE_IS_GAUGE(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_GAUGE))
#define CADE_GAUGE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_GAUGE, CadeGaugeClass))
#define CADE_IS_GAUGE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_GAUGE))
#define CADE_GAUGE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_GAUGE, CadeGaugeClass))

typedef struct _CadeGauge        CadeGauge;
typedef struct _CadeGaugeClass   CadeGaugeClass;

GType      cade_gauge_get_type (void) G_GNUC_CONST;
CadeGauge *cade_gauge_new (void);

G_END_DECLS

#endif /* __CADE_GAUGE_H__ */
