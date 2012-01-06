/*
 * Geoclue
 * geoclue-reverse-geocode.c - Client API for accessing GcIfaceReverseGeocode
 *
 * Author: Iain Holmes <iain@openedhand.com>
 * Copyright 2007 by Garmin Ltd. or its subsidiaries
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

/**
 * SECTION:geoclue-reverse-geocode
 * @short_description: Geoclue reverse geocode client API
 *
 * #GeoclueReverseGeocode contains reverse geocoding methods. 
 * It is part of the Geoclue public C client API which uses D-Bus 
 * to communicate with the actual provider.
 * 
 * After a #GeoclueReverseGeocode is created with 
 * geoclue_reverse_geocode_new(), the 
 * geoclue_reverse_geocode_position_to_address() and 
 * geoclue_reverse_geocode_position_to_address_async() method can be used to 
 * obtain the address of a known position.
 */

#include <geoclue/geoclue-reverse-geocode.h>
#include <geoclue/geoclue-marshal.h>

#include "gc-iface-reverse-geocode-bindings.h"

typedef struct _GeoclueReverseGeocodePrivate {
	int dummy;
} GeoclueReverseGeocodePrivate;

#define GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GEOCLUE_TYPE_REVERSE_GEOCODE, GeoclueReverseGeocodePrivate))

G_DEFINE_TYPE (GeoclueReverseGeocode, geoclue_reverse_geocode, GEOCLUE_TYPE_PROVIDER);

static void
finalize (GObject *object)
{
	G_OBJECT_CLASS (geoclue_reverse_geocode_parent_class)->finalize (object);
}

static void
dispose (GObject *object)
{
	G_OBJECT_CLASS (geoclue_reverse_geocode_parent_class)->dispose (object);
}

static void
geoclue_reverse_geocode_class_init (GeoclueReverseGeocodeClass *klass)
{
	GObjectClass *o_class = (GObjectClass *) klass;

	o_class->finalize = finalize;
	o_class->dispose = dispose;

	g_type_class_add_private (klass, sizeof (GeoclueReverseGeocodePrivate));
}

static void
geoclue_reverse_geocode_init (GeoclueReverseGeocode *geocode)
{
}

/**
 * geoclue_reverse_geocode_new:
 * @service: D-Bus service name
 * @path: D-Bus path name
 *
 * Creates a #GeoclueReverseGeocode with given D-Bus service name and path.
 * 
 * Return value: Pointer to a new #GeoclueReverseGeocode
 */
GeoclueReverseGeocode *
geoclue_reverse_geocode_new (const char *service,
			     const char *path)
{
	return g_object_new (GEOCLUE_TYPE_REVERSE_GEOCODE,
			     "service", service,
			     "path", path,
			     "interface", GEOCLUE_REVERSE_GEOCODE_INTERFACE_NAME,
			     NULL);
}

/**
 * geoclue_reverse_geocode_position_to_address:
 * @geocode: A #GeoclueReverseGeocode object
 * @latitude: latitude in degrees
 * @longitude: longitude in degrees
 * @position_accuracy: Accuracy of the given latitude and longitude
 * @details: Pointer to returned #GHashTable with address details or %NULL
 * @address_accuracy: Pointer to accuracy of the returned address or %NULL 
 * @error: Pointer to returned #Gerror or %NULL
 * 
 * Obtains an address for the position defined by @latitude and @longitude.
 * @details is a #GHashTable with the returned address data, see 
 * <ulink url="geoclue-types.html">geoclue-types.h</ulink> for the hashtable keys.
 * 
 * If the caller is not interested in some values, the pointers can be 
 * left %NULL. If accuracy of the position is not known, an accuracy with
 * GeoclueAccuracyLevel GEOCLUE_ACCURACY_DETAILED should be used.
 * 
 * Return value: %TRUE if there is no @error
 */
gboolean
geoclue_reverse_geocode_position_to_address (GeoclueReverseGeocode   *geocode,
					     double                   latitude,
					     double                   longitude,
					     GeoclueAccuracy         *position_accuracy,
					     GHashTable             **details,
					     GeoclueAccuracy        **address_accuracy,
					     GError                 **error)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (geocode);
	
	return org_freedesktop_Geoclue_ReverseGeocode_position_to_address 
		(provider->proxy, latitude, longitude, position_accuracy, 
		 details, address_accuracy, error);
}


typedef struct _GeoclueRevGeocodeAsyncData {
	GeoclueReverseGeocode *revgeocode;
	GCallback callback;
	gpointer userdata;
} GeoclueRevGeocodeAsyncData;

static void
position_to_address_callback (DBusGProxy                 *proxy, 
			      GHashTable                 *details,
			      GeoclueAccuracy            *accuracy,
			      GError                     *error,
			      GeoclueRevGeocodeAsyncData *data)
{
	(*(GeoclueReverseGeocodeCallback)data->callback) (data->revgeocode,
	                                                  details,
	                                                  accuracy,
	                                                  error,
	                                                  data->userdata);
	g_free (data);
}

/**
 * GeoclueReverseGeocodeCallback:
 * @revgeocode: A #GeoclueReverseGeocode object
 * @details: Address details as #GHashTable.
 * @accuracy: Accuracy of measurement as #GeoclueAccuracy
 * @error: Error as #Gerror (may be %NULL)
 * @userdata: User data pointer set in geoclue_reverse_geocode_position_to_address_async()
 * 
 * Callback function for geoclue_reverse_geocode_position_to_address_async().
 * 
 * see <ulink url="geoclue-types.html">geoclue-types.h</ulink> for the 
 * hashtable keys used in @details.
 */

/**
 * geoclue_reverse_geocode_position_to_address_async:
 * @geocode: A #GeoclueReverseGeocode object
 * @latitude: Latitude in degrees
 * @longitude: Longitude in degrees
 * @accuracy: Accuracy of the given position as #GeoclueAccuracy
 * @callback: A #GeoclueAddressCallback function that should be called when return values are available
 * @userdata: pointer for user specified data
 * 
 * Function returns (essentially) immediately and calls @callback when the reverse-geocoded 
 * address data is available or when D-Bus timeouts.
 */
void 
geoclue_reverse_geocode_position_to_address_async (GeoclueReverseGeocode        *revgeocode,
						   double                        latitude,
						   double                        longitude,
						   GeoclueAccuracy              *accuracy,
						   GeoclueReverseGeocodeCallback callback,
						   gpointer                      userdata)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (revgeocode);
	GeoclueRevGeocodeAsyncData *data;
	
	data = g_new (GeoclueRevGeocodeAsyncData, 1);
	data->revgeocode = revgeocode;
	data->callback = G_CALLBACK (callback);
	data->userdata = userdata;
	
	org_freedesktop_Geoclue_ReverseGeocode_position_to_address_async
			(provider->proxy,
			 latitude,
			 longitude,
			 accuracy,
			 (org_freedesktop_Geoclue_ReverseGeocode_position_to_address_reply)position_to_address_callback,
			 data);
}
