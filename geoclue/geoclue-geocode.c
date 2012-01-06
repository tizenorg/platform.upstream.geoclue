/*
 * Geoclue
 * geoclue-geocode.c - Client API for accessing GcIfaceGeocode
 *
 * Authors: Iain Holmes <iain@openedhand.com>
 *          Jussi Kukkonen <jku@linux.intel.com>
 * Copyright 2007 by Garmin Ltd. or its subsidiaries
 *           2010 Intel Corporation
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
 * SECTION:geoclue-geocode
 * @short_description: Geoclue geocode client API
 *
 * #GeoclueGeocode contains geocoding methods. 
 * It is part of the Geoclue public C client API which uses D-Bus 
 * to communicate with the actual provider.
 * 
 * After a #GeoclueGeocode is created with geoclue_geocode_new(), the 
 * geoclue_geocode_address_to_position(),
 * geoclue_geocode_freeform_address_to_position() methods and their
 * asynchronous counterparts can be used to obtain the position (coordinates)
 * of the given address.
 * 
 * Address #GHashTable keys are defined in 
 * <ulink url="geoclue-types.html">geoclue-types.h</ulink>. See also 
 * convenience functions in 
 * <ulink url="geoclue-address-details.html">geoclue-address-details.h</ulink>.
 */

#include <geoclue/geoclue-geocode.h>
#include <geoclue/geoclue-marshal.h>

#include "gc-iface-geocode-bindings.h"

typedef struct _GeoclueGeocodePrivate {
	int dummy;
} GeoclueGeocodePrivate;

#define GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GEOCLUE_TYPE_GEOCODE, GeoclueGeocodePrivate))

G_DEFINE_TYPE (GeoclueGeocode, geoclue_geocode, GEOCLUE_TYPE_PROVIDER);

static void
finalize (GObject *object)
{
	G_OBJECT_CLASS (geoclue_geocode_parent_class)->finalize (object);
}

static void
dispose (GObject *object)
{
	G_OBJECT_CLASS (geoclue_geocode_parent_class)->dispose (object);
}

static void
geoclue_geocode_class_init (GeoclueGeocodeClass *klass)
{
	GObjectClass *o_class = (GObjectClass *) klass;

	o_class->finalize = finalize;
	o_class->dispose = dispose;

	g_type_class_add_private (klass, sizeof (GeoclueGeocodePrivate));
}

static void
geoclue_geocode_init (GeoclueGeocode *geocode)
{
}

/**
 * geoclue_geocode_new:
 * @service: D-Bus service name
 * @path: D-Bus path name
 *
 * Creates a #GeoclueGeocode with given D-Bus service name and path.
 * 
 * Return value: Pointer to a new #GeoclueGeocode
 */
GeoclueGeocode *
geoclue_geocode_new (const char *service,
		     const char *path)
{
	return g_object_new (GEOCLUE_TYPE_GEOCODE,
			     "service", service,
			     "path", path,
			     "interface", GEOCLUE_GEOCODE_INTERFACE_NAME,
			     NULL);
}

/**
 * geoclue_geocode_address_to_position:
 * @geocode: A #GeoclueGeocode object
 * @details: Hashtable with address data
 * @latitude: Pointer to returned latitude in degrees or %NULL
 * @longitude: Pointer to returned longitude in degrees or %NULL
 * @altitude: Pointer to returned altitude in meters or %NULL
 * @accuracy: Pointer to returned #GeoclueAccuracy or %NULL
 * @error: Pointer to returned #Gerror or %NULL
 * 
 * Geocodes given address to coordinates (@latitude, @longitude, @altitude). 
 * see <ulink url="geoclue-types.html">geoclue-types.h</ulink> for the 
 * hashtable keys usable in @details. @accuracy is a rough estimate of 
 * the accuracy of the returned position.
 * 
 * If the caller is not interested in some values, the pointers can be 
 * left %NULL.
 * 
 * Return value: A #GeocluePositionFields bitfield representing the 
 * validity of the returned coordinates.
 */
GeocluePositionFields
geoclue_geocode_address_to_position (GeoclueGeocode   *geocode,
				     GHashTable       *details,
				     double           *latitude,
				     double           *longitude,
				     double           *altitude,
				     GeoclueAccuracy **accuracy,
				     GError          **error)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (geocode);
	int fields;
	double la, lo, al;
	GeoclueAccuracy *acc;
	
	if (!org_freedesktop_Geoclue_Geocode_address_to_position (provider->proxy,
								  details, &fields,
								  &la, &lo, &al,
								  &acc, error)){
		return GEOCLUE_POSITION_FIELDS_NONE;
	}

	if (latitude != NULL && (fields & GEOCLUE_POSITION_FIELDS_LATITUDE)) {
		*latitude = la;
	}

	if (longitude != NULL && (fields & GEOCLUE_POSITION_FIELDS_LONGITUDE)) {
		*longitude = lo;
	}

	if (altitude != NULL && (fields & GEOCLUE_POSITION_FIELDS_ALTITUDE)) {
		*altitude = al;
	}

	if (accuracy != NULL) {
		*accuracy = acc;
	}

	return fields;
}

typedef struct _GeoclueGeocodeAsyncData {
	GeoclueGeocode *geocode;
	GCallback callback;
	gpointer userdata;
} GeoclueGeocodeAsyncData;

static void
address_to_position_callback (DBusGProxy              *proxy, 
			      GeocluePositionFields    fields,
			      double                   latitude,
			      double                   longitude,
			      double                   altitude,
			      GeoclueAccuracy         *accuracy,
			      GError                  *error,
			      GeoclueGeocodeAsyncData *data)
{
	(*(GeoclueGeocodeCallback)data->callback) (data->geocode,
	                                           fields,
	                                           latitude,
	                                           longitude,
	                                           altitude,
	                                           accuracy,
	                                           error,
	                                           data->userdata);
	g_free (data);
}

/**
 * GeoclueGeocodeCallback:
 * @geocode: A #GeoclueGeocode object
 * @fields: A #GeocluePositionFields bitfield representing the validity of the position values
 * @latitude: Latitude in degrees
 * @longitude: Longitude in degrees
 * @altitude: Altitude in meters
 * @accuracy: Accuracy of measurement as #GeoclueAccuracy
 * @error: Error as #Gerror or %NULL
 * @userdata: User data pointer
 * 
 * Callback function for the asynchronous methods.
 */

/**
 * geoclue_geocode_address_to_position_async:
 * @geocode: A #Geocluegeocode object
 * @details: A #GHashTable with address data
 * @callback: A #GeoclueAddressCallback function that should be called when return values are available
 * @userdata: pointer for user specified data
 * 
 * Function returns (essentially) immediately and calls @callback when the geocoded 
 * position data is available or when D-Bus timeouts.
 * 
 * see <ulink url="geoclue-types.html">geoclue-types.h</ulink> for the 
 * hashtable keys usable in @details.
 * 
 */
void 
geoclue_geocode_address_to_position_async (GeoclueGeocode         *geocode,
					   GHashTable             *details,
					   GeoclueGeocodeCallback  callback,
					   gpointer                userdata)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (geocode);
	GeoclueGeocodeAsyncData *data;
	
	data = g_new (GeoclueGeocodeAsyncData, 1);
	data->geocode = geocode;
	data->callback = G_CALLBACK (callback);
	data->userdata = userdata;
	
	org_freedesktop_Geoclue_Geocode_address_to_position_async
			(provider->proxy,
			 details,
			 (org_freedesktop_Geoclue_Geocode_address_to_position_reply)address_to_position_callback,
			 data);
}

/**
 * geoclue_geocode_freeform_address_to_position:
 * @geocode: A #GeoclueGeocode object
 * @address: freeform address
 * @latitude: Pointer to returned latitude in degrees or %NULL
 * @longitude: Pointer to returned longitude in degrees or %NULL
 * @altitude: Pointer to returned altitude in meters or %NULL
 * @accuracy: Pointer to returned #GeoclueAccuracy or %NULL
 * @error: Pointer to returned #Gerror or %NULL
 *
 * Geocodes given address to coordinates (@latitude, @longitude, @altitude).
 * @accuracy is a rough estimate of the accuracy of the returned position.
 *
 * If the caller is not interested in some values, the pointers can be
 * left %NULL.
 *
 * Return value: A #GeocluePositionFields bitfield representing the
 * validity of the returned coordinates.
 */
GeocluePositionFields
geoclue_geocode_freeform_address_to_position (GeoclueGeocode   *geocode,
                                              const char       *address,
                                              double           *latitude,
                                              double           *longitude,
                                              double           *altitude,
                                              GeoclueAccuracy **accuracy,
                                              GError          **error)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (geocode);
	int fields;
	double la, lo, al;
	GeoclueAccuracy *acc;

	if (!org_freedesktop_Geoclue_Geocode_freeform_address_to_position
			(provider->proxy,
			 address, &fields,
			 &la, &lo, &al,
			 &acc, error)) {
		return GEOCLUE_POSITION_FIELDS_NONE;
	}

	if (latitude != NULL && (fields & GEOCLUE_POSITION_FIELDS_LATITUDE)) {
		*latitude = la;
	}

	if (longitude != NULL && (fields & GEOCLUE_POSITION_FIELDS_LONGITUDE)) {
		*longitude = lo;
	}

	if (altitude != NULL && (fields & GEOCLUE_POSITION_FIELDS_ALTITUDE)) {
		*altitude = al;
	}

	if (accuracy != NULL) {
		*accuracy = acc;
	}

	return fields;
}

/**
 * geoclue_geocode_freeform_address_to_position_async:
 * @geocode: A #Geocluegeocode object
 * @address: freeform address
 * @callback: A #GeoclueAddressCallback function that should be called when return values are available
 * @userdata: pointer for user specified data
 *
 * Function returns (essentially) immediately and calls @callback when the geocoded 
 * position data is available or when D-Bus timeouts.
 */
void
geoclue_geocode_freeform_address_to_position_async (GeoclueGeocode         *geocode,
                                                    const char             *address,
                                                    GeoclueGeocodeCallback  callback,
                                                    gpointer                userdata)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (geocode);
	GeoclueGeocodeAsyncData *data;

	data = g_new (GeoclueGeocodeAsyncData, 1);
	data->geocode = geocode;
	data->callback = G_CALLBACK (callback);
	data->userdata = userdata;

	org_freedesktop_Geoclue_Geocode_freeform_address_to_position_async
			(provider->proxy,
			 address,
			 (org_freedesktop_Geoclue_Geocode_address_to_position_reply)address_to_position_callback,
			 data);
}

