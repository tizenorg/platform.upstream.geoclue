/*
 * Geoclue
 * geoclue-poi.c - Client API for accessing GcIfacePoi
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
 * SECTION:geoclue-poi
 * @short_description: Geoclue poi client API
 *
 * #GeocluePoi contains geocoding methods.
 * It is part of the Geoclue public C client API which uses D-Bus
 * to communicate with the actual provider.
 *
 * After a #GeocluePoi is created with geoclue_poi_new(), the
 * geoclue_poi_address_to_position(),
 * geoclue_poi_freeform_address_to_position() methods and their
 * asynchronous counterparts can be used to obtain the position (coordinates)
 * of the given address.
 *
 * Address #GHashTable keys are defined in
 * <ulink url="geoclue-types.html">geoclue-types.h</ulink>. See also
 * convenience functions in
 * <ulink url="geoclue-address-details.html">geoclue-address-details.h</ulink>.
 */

#include <geoclue/geoclue-poi.h>
#include <geoclue/geoclue-marshal.h>
#include <geoclue/geoclue-landmark.h>

#include "gc-iface-poi-bindings.h"

typedef struct _GeocluePoiPrivate {
	int dummy;
} GeocluePoiPrivate;

#define GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GEOCLUE_TYPE_POI, GeocluePoiPrivate))

G_DEFINE_TYPE (GeocluePoi, geoclue_poi, GEOCLUE_TYPE_PROVIDER);

static void
finalize (GObject *object)
{
	G_OBJECT_CLASS (geoclue_poi_parent_class)->finalize (object);
}

static void
dispose (GObject *object)
{
	G_OBJECT_CLASS (geoclue_poi_parent_class)->dispose (object);
}

static void
geoclue_poi_class_init (GeocluePoiClass *klass)
{
	GObjectClass *o_class = (GObjectClass *) klass;

	o_class->finalize = finalize;
	o_class->dispose = dispose;

	g_type_class_add_private (klass, sizeof (GeocluePoiPrivate));
}

static void
geoclue_poi_init (GeocluePoi *poi)
{
}

/**
 * geoclue_poi_new:
 * @service: D-Bus service name
 * @path: D-Bus path name
 *
 * Creates a #GeocluePoi with given D-Bus service name and path.
 *
 * Return value: Pointer to a new #GeocluePoi
 */
GeocluePoi *
geoclue_poi_new (const char *service,
		     const char *path)
{
	return g_object_new (GEOCLUE_TYPE_POI,
			     "service", service,
			     "path", path,
			     "interface", GEOCLUE_POI_INTERFACE_NAME,
			     NULL);
}

/**
 * geoclue_poi_address_to_position:
 * @poi: A #GeocluePoi object
 * @details: Hashtable with address data
 * @latitude: Pointer to returned latitude in degrees or %NULL
 * @longitude: Pointer to returned longitude in degrees or %NULL
 * @altitude: Pointer to returned altitude in meters or %NULL
 * @accuracy: Pointer to returned #GeoclueAccuracy or %NULL
 * @error: Pointer to returned #Gerror or %NULL
 *
 * Pois given address to coordinates (@latitude, @longitude, @altitude).
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
gboolean
geoclue_poi_search_by_position (GeocluePoi  		*poi,
								 const char 		*keyword,
								 const char 		*lang,
								 const char 		*country_code,
								 int 				limit,
								 double			left,
								 double			top,
								 double			right,
								 double			bottom,
								 int			*count,
								 GPtrArray		**landmark,
								 GError          	**error)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (poi);
	if (!org_freedesktop_Geoclue_Poi_search_by_position (provider->proxy,
								  keyword, lang, country_code, limit, left, top, right, bottom, count,
								  landmark, error)){
		return FALSE;
	}

	return TRUE;
}

typedef struct _GeocluePoiAsyncData {
	GeocluePoi *poi;
	GCallback callback;
	gpointer userdata;
} GeocluePoiAsyncData;

static void
_geoclue_poi_callback (DBusGProxy             	*proxy,
				 int			count,
				  GPtrArray				*landmark,
			      GError               				    *error,
			      GeocluePoiAsyncData 					*data)
{

	(*(GeocluePoiCallback)data->callback) (data->poi, count, landmark, error, data->userdata);
	g_free (data);
}

/**
 * GeocluePoiCallback:
 * @poi: A #GeocluePoi object
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
 * geoclue_poi_address_to_position_async:
 * @poi: A #GeocluePoi object
 * @details: A #GHashTable with address data
 * @callback: A #GeoclueAddressCallback function that should be called when return values are available
 * @userdata: pointer for user specified data
 *
 * Function returns (essentially) immediately and calls @callback when the poid
 * position data is available or when D-Bus timeouts.
 *
 * see <ulink url="geoclue-types.html">geoclue-types.h</ulink> for the
 * hashtable keys usable in @details.
 *
 */
void
geoclue_poi_search_by_position_async (GeocluePoi        *poi,
				const char 		*keyword,
				const char 		*lang,
				const char 		*country_code,
				int 			limit,
				double			left,
				double 			top,
				double			right,
				double			bottom,
				GeocluePoiCallback	callback,
				gpointer		userdata)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (poi);
	GeocluePoiAsyncData *data;

	data = g_new (GeocluePoiAsyncData, 1);
	data->poi = poi;
	data->callback = G_CALLBACK (callback);
	data->userdata = userdata;

	org_freedesktop_Geoclue_Poi_search_by_position_async
			(provider->proxy,
			 keyword, lang, country_code, limit, left, top, right, bottom,
			 (org_freedesktop_Geoclue_Poi_search_by_position_reply)_geoclue_poi_callback,
			 data);
}
