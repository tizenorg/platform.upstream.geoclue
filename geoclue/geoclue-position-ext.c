/*
 * Geoclue
 * geoclue-position-ext.c - Client API for accessing GcIfacePosition
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
 * SECTION:geoclue-position-ext
 * @short_description: Geoclue position & velocity client API
 *
 * #GeocluePositionVelocity contains position & velocity related methods and signals.
 * It is part of the Geoclue public C client API which uses D-Bus
 * to communicate with the actual provider.
 *
 * After a #GeocluePositionExt is created with geoclue_position_ext_new() or
 * using geoclye_master_client_create_position_velocity(), the
 * geoclue_position_ext_get_position() and geoclue_position_ext_get_position_async()
 * method and the position-changed signal can be used to obtain the current position & velocity.
 */

#include <geoclue/geoclue-position-ext.h>
#include <geoclue/geoclue-marshal.h>

#include "gc-iface-position-ext-bindings.h"

typedef struct _GeocluePositionExtPrivate {
	int dummy;
} GeocluePositionExtPrivate;

enum {
	POSITION_CHANGED,
	LAST_SIGNAL
};

static guint32 signals[LAST_SIGNAL] = {0, };

#define GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GEOCLUE_TYPE_POSITION_EXT, GeocluePositionExtPrivate))

G_DEFINE_TYPE (GeocluePositionExt, geoclue_position_ext, GEOCLUE_TYPE_PROVIDER);

static void
finalize (GObject *object)
{
	G_OBJECT_CLASS (geoclue_position_ext_parent_class)->finalize (object);
}

static void
dispose (GObject *object)
{
	G_OBJECT_CLASS (geoclue_position_ext_parent_class)->dispose (object);
}

static void
position_changed (DBusGProxy      *proxy,
		  int              fields,
		  int              timestamp,
		  double           latitude,
		  double           longitude,
		  double           altitude,
		  double           speed,
		  double           direction,
		  double           velocity,
		  GeoclueAccuracy *accuracy,
		  GeocluePositionExt *position)
{
	g_signal_emit (position, signals[POSITION_CHANGED], 0, fields,
		       timestamp, latitude, longitude, altitude, speed, direction, velocity, accuracy);
}

static GObject *
constructor (GType                  type,
	     guint                  n_props,
	     GObjectConstructParam *props)
{
	GObject *object;
	GeoclueProvider *provider;

	object = G_OBJECT_CLASS (geoclue_position_ext_parent_class)->constructor
		(type, n_props, props);
	provider = GEOCLUE_PROVIDER (object);

	dbus_g_proxy_add_signal (provider->proxy, "PositionChanged",
				 G_TYPE_INT, G_TYPE_INT, G_TYPE_DOUBLE,
				 G_TYPE_DOUBLE, G_TYPE_DOUBLE,
				 G_TYPE_DOUBLE, G_TYPE_DOUBLE, G_TYPE_DOUBLE,
                                 GEOCLUE_ACCURACY_TYPE,
				 G_TYPE_INVALID);
	dbus_g_proxy_connect_signal (provider->proxy, "PositionChanged",
				     G_CALLBACK (position_changed),
				     object, NULL);

	return object;
}

static void
geoclue_position_ext_class_init (GeocluePositionExtClass *klass)
{
	GObjectClass *o_class = (GObjectClass *) klass;

	o_class->finalize = finalize;
	o_class->dispose = dispose;
	o_class->constructor = constructor;

	g_type_class_add_private (klass, sizeof (GeocluePositionExtPrivate));

	/**
	 * GeocluePosition::position--changed:
	 * @position: the #GeocluePositionExt object emitting the signal
	 * @fields: A #GeocluePositionExtFields bit field representing the validity of the position values
	 * @timestamp: Time of position measurement (Unix timestamp)
	 * @latitude: Latitude in degrees
	 * @longitude: Longitude in degrees
	 * @altitude: Altitude in meters
	 * @speed: Horizontal speed in m/s
	 * @direction: Horizontal direction in degrees
	 * @climb: Vertical speed
	 * @accuracy: Accuracy of measurement as #GeoclueAccuracy
	 *
	 * The position-changed signal is emitted each time the position changes. Clients should note
	 * that not all providers support signals.
	 */
	signals[POSITION_CHANGED] = g_signal_new ("position-changed",
						  G_TYPE_FROM_CLASS (klass),
						  G_SIGNAL_RUN_FIRST |
						  G_SIGNAL_NO_RECURSE,
						  G_STRUCT_OFFSET (GeocluePositionExtClass, position_changed),
						  NULL, NULL,
						  geoclue_marshal_VOID__INT_INT_DOUBLE_DOUBLE_DOUBLE_DOUBLE_DOUBLE_DOUBLE_BOXED,
						  G_TYPE_NONE, 9,
						  G_TYPE_INT, G_TYPE_INT,
						  G_TYPE_DOUBLE, G_TYPE_DOUBLE,
						  G_TYPE_DOUBLE, G_TYPE_DOUBLE, G_TYPE_DOUBLE,
						  G_TYPE_DOUBLE, G_TYPE_POINTER);
}

static void
geoclue_position_ext_init (GeocluePositionExt *position)
{
}

/**
 * geoclue_position_ext_new:
 * @service: D-Bus service name
 * @path: D-Bus path name
 *
 * Creates a #GeocluePositionExt with given D-Bus service name and path.
 *
 * Return value: Pointer to a new #GeocluePositionExt
 */
GeocluePositionExt *
geoclue_position_ext_new (const char *service,
		      const char *path)
{
	return g_object_new (GEOCLUE_TYPE_POSITION_EXT,
			     "service", service,
			     "path", path,
			     "interface", GEOCLUE_POSITION_EXT_INTERFACE_NAME,
			     NULL);
}

/**
 * geoclue_position_ext_get_position:
 * @position: A #GeocluePositionExt object
 * @timestamp: Pointer to returned time of position measurement (Unix timestamp) or %NULL
 * @latitude: Pointer to returned latitude in degrees or %NULL
 * @longitude: Pointer to returned longitude in degrees or %NULL
 * @altitude: Pointer to returned altitude in meters or %NULL
 * @speed: Pointer to returned horizontal speed or %NULL
 * @direction: Pointer to returned horizontal direction (bearing) or %NULL
 * @climb: Pointer to returned vertical speed or %NULL
 * @accuracy: Pointer to returned #GeoclueAccuracy or %NULL
 * @error: Pointer to returned #Gerror or %NULL
 *
 * Obtains the current position & velocity. @timestamp will contain the time of
 * the actual position & velocity measurement. @accuracy is a rough estimate of the
 * accuracy of the current position & velocity.
 *
 * If the caller is not interested in some values, the pointers can be
 * left %NULL.
 *
 * Return value: A #GeocluePositionExtFields bitfield representing the
 * validity of the position & velocity values.
 */
GeocluePositionExtFields
geoclue_position_ext_get_position (GeocluePositionExt  *position,
			       int              *timestamp,
			       double           *latitude,
			       double           *longitude,
			       double           *altitude,
			       double           *speed,
			       double           *direction,
			       double           *climb,
			       GeoclueAccuracy **accuracy,
			       GError          **error)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (position);
	double la, lo, al;
	double sp, di, cl;
	int ts, fields;
	GeoclueAccuracy *acc;
	if (!org_freedesktop_Geoclue_PositionExt_get_position (provider->proxy,
							    &fields, &ts,
							    &la, &lo, &al,
							    &sp, &di, &cl,
							    &acc, error)) {
		return GEOCLUE_POSITION_EXT_FIELDS_NONE;
	}

	if (timestamp != NULL) {
		*timestamp = ts;
	}

	if (latitude != NULL && (fields & GEOCLUE_POSITION_EXT_FIELDS_LATITUDE)) {
		*latitude = la;
	}

	if (longitude != NULL && (fields & GEOCLUE_POSITION_EXT_FIELDS_LONGITUDE)) {
		*longitude = lo;
	}

	if (altitude != NULL && (fields & GEOCLUE_POSITION_EXT_FIELDS_ALTITUDE)) {
		*altitude = al;
	}

	if (speed != NULL && (fields & GEOCLUE_POSITION_EXT_FIELDS_SPEED)) {
		*speed = sp;
	}

	if (direction != NULL && (fields & GEOCLUE_POSITION_EXT_FIELDS_DIRECTION)) {
		*direction = di;
	}

	if (climb != NULL && (fields & GEOCLUE_POSITION_EXT_FIELDS_CLIMB)) {
		*climb = cl;
	}

	if (accuracy != NULL) {
		*accuracy = acc;
	}

	return fields;
}

/**
 * geoclue_position_ext_get_last_position:
 * @position: A #GeocluePositionExt object
 * @timestamp: Pointer to returned time of position measurement (Unix timestamp) or %NULL
 * @latitude: Pointer to returned latitude in degrees or %NULL
 * @longitude: Pointer to returned longitude in degrees or %NULL
 * @altitude: Pointer to returned altitude in meters or %NULL
 * @accuracy: Pointer to returned #GeoclueAccuracy or %NULL
 * @speed: Pointer to returned horizontal speed or %NULL
 * @direction: Pointer to returned horizontal direction (bearing) or %NULL
 * @climb: Pointer to returned vertical speed or %NULL
 * @error: Pointer to returned #Gerror or %NULL
 *
 * Obtains the last position & velocity. @timestamp will contain the time of
 * the actual position measurement. @accuracy is a rough estimate of the
 * accuracy of the last position.
 *
 * If the caller is not interested in some values, the pointers can be
 * left %NULL.
 *
 * Return value: A #GeocluePositionExtFields bitfield representing the
 * validity of the position values.
 */
GeocluePositionExtFields
geoclue_position_ext_get_last_position (GeocluePositionExt  *position,
				    int              *timestamp,
				    double           *latitude,
				    double           *longitude,
				    double           *altitude,
				    double           *speed,
				    double           *direction,
				    double           *climb,
				    GeoclueAccuracy **accuracy,
				    GError          **error)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (position);
	double la, lo, al;
	double sp, di, cl;
	int ts, fields;
	GeoclueAccuracy *acc;
	if (!org_freedesktop_Geoclue_PositionExt_get_last_position (provider->proxy,
								 &fields, &ts,
								 &la, &lo, &al,
								 &sp, &di, &cl,
								 &acc, error)) {
		return GEOCLUE_POSITION_FIELDS_NONE;
	}

	if (timestamp != NULL) {
		*timestamp = ts;
	}

	if (latitude != NULL && (fields & GEOCLUE_POSITION_EXT_FIELDS_LATITUDE)) {
		*latitude = la;
	}

	if (longitude != NULL && (fields & GEOCLUE_POSITION_EXT_FIELDS_LONGITUDE)) {
		*longitude = lo;
	}

	if (altitude != NULL && (fields & GEOCLUE_POSITION_EXT_FIELDS_ALTITUDE)) {
		*altitude = al;
	}

	if (speed != NULL && (fields & GEOCLUE_POSITION_EXT_FIELDS_SPEED)) {
		*speed = sp;
	}

	if (direction != NULL && (fields & GEOCLUE_POSITION_EXT_FIELDS_DIRECTION)) {
		*direction = di;
	}

	if (climb != NULL && (fields & GEOCLUE_POSITION_EXT_FIELDS_CLIMB)) {
		*climb = cl;
	}

	if (accuracy != NULL) {
		*accuracy = acc;
	}

	return fields;
}

typedef struct _GeocluePositionExtAsyncData {
	GeocluePositionExt *position;
	GCallback callback;
	gpointer userdata;
} GeocluePositionExtAsyncData;

static void
get_position_async_callback (DBusGProxy               *proxy,
			     GeocluePositionExtFields     fields,
			     int                       timestamp,
			     double                    latitude,
			     double                    longitude,
			     double                    altitude,
			     double                    speed,
			     double                    direction,
			     double                    climb,
			     GeoclueAccuracy          *accuracy,
			     GError                   *error,
			     GeocluePositionExtAsyncData *data)
{
	(*(GeocluePositionExtCallback)data->callback) (data->position,
	                                            fields,
	                                            timestamp,
	                                            latitude,
	                                            longitude,
	                                            altitude,
	                                            speed,
	                                            direction,
	                                            climb,
	                                            accuracy,
	                                            error,
	                                            data->userdata);
	g_free (data);
}

/**
 * GeocluePositionExtCallback:
 * @position: A #GeocluePositionExt object
 * @fields: A #GeocluePositionExtFields bitfield representing the validity of the position values
 * @timestamp: Time of position measurement (Unix timestamp)
 * @latitude: Latitude in degrees
 * @longitude: Longitude in degrees
 * @altitude: Altitude in meters
 * @speed: Horizontal speed (m/s)
 * @direction: Horizontal direction in degrees
 * @climb: Vertical speed
 * @accuracy: Accuracy of measurement as #GeoclueAccuracy
 * @error: Error as #Gerror or %NULL
 * @userdata: User data pointer set in geoclue_position_velocity_get_position_velocity_async()
 *
 * Callback function for geoclue_position_ext_get_position_async().
 */

/**
 * geoclue_position_ext_get_position_async:
 * @position: A #GeocluePositionExt object
 * @callback: A #GeocluePositionExtCallback function that should be called when return values are available
 * @userdata: pointer for user specified data
 *
 * Function returns (essentially) immediately and calls @callback when current position & velocity
 * is available or when D-Bus timeouts.
 */
void
geoclue_position_ext_get_position_async (GeocluePositionExt         *position,
				     GeocluePositionExtCallback  callback,
				     gpointer                 userdata)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (position);
	GeocluePositionExtAsyncData *data;

	data = g_new (GeocluePositionExtAsyncData, 1);
	data->position = position;
	data->callback = G_CALLBACK (callback);
	data->userdata = userdata;

	org_freedesktop_Geoclue_PositionExt_get_position_async
			(provider->proxy,
			 (org_freedesktop_Geoclue_PositionExt_get_position_reply)get_position_async_callback,
			 data);
}
