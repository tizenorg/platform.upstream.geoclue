/*
 * Geoclue
 * geoclue-nominatim.h - A Geocode/ReverseGeocode provider for nominatim.openstreetmap.org
 *
 * Author: Jussi Kukkonen <jku@linux.intel.com>
 */

#ifndef _GEOCLUE_NOMINATIM
#define _GEOCLUE_NOMINATIM

#include <glib-object.h>
#include <geoclue/gc-web-service.h>

G_BEGIN_DECLS


#define GEOCLUE_TYPE_NOMINATIM (geoclue_nominatim_get_type ())

#define GEOCLUE_NOMINATIM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEOCLUE_TYPE_NOMINATIM, GeoclueNominatim))
#define GEOCLUE_NOMINATIM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GEOCLUE_TYPE_NOMINATIM, GeoclueNominatimClass))
#define GEOCLUE_IS_NOMINATIM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEOCLUE_TYPE_NOMINATIM))
#define GEOCLUE_IS_NOMINATIM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GEOCLUE_TYPE_NOMINATIM))

typedef struct _GeoclueNominatim {
	GcProvider parent;
	GMainLoop *loop;

	GcWebService *geocoder;
	GcWebService *rev_geocoder;
	GcWebService *poi;
} GeoclueNominatim;

typedef struct _GeoclueNominatimClass {
	GcProviderClass parent_class;
} GeoclueNominatimClass;

typedef struct _GeocluePOIData {
	gint id;
	gint rank;
	gdouble lat;
	gdouble lon;
	gdouble boundary_left;
	gdouble boundary_top;
	gdouble boudnary_right;
	gdouble boundary_bottom;
	gchar *name;
	gchar *icon;
	gchar *house;
	gchar *road;
	gchar *village;
	gchar *suburb;
	gchar *city;
	gchar *county;
	gchar *country;
	gchar *country_code;
} GeocluePOIData;

GType geoclue_nominatim_get_type (void);

G_END_DECLS

#endif
