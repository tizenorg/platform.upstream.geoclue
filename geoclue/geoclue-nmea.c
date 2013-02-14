/*
 * Geoclue
 * geoclue-nmea.c - Client API for accessing GcIfaceNmea
 *
 * Author: Tae-Hwan Kim <the81.kim@samsung.com>, Youngae Kang <youngae.kang@samsung.com>,
 *         Yunhan Kim <yhan.kim@samsung.com>, Genie Kim <daejins.kim@samsung.com>
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd. All rights reserved.
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
 * SECTION:geoclue-nmea
 * @short_description: Geoclue nmea client API
 *
 * #GeoclueNmea contains nmea-related methods and signals.
 * It is part of the Geoclue public C client API which uses D-Bus
 * to communicate with the actual provider.
 *
 * After a #GeoclueNmea is created with geoclue_nmea_new() or
 * using geoclye_master_client_create_nmea(), the
 * geoclue_nmea_get_nmea() and geoclue_nmea_get_nmea_async()
 * method and the nmea-changed signal can be used to obtain the current nmea.
 */

#include <geoclue/geoclue-nmea.h>
#include <geoclue/geoclue-marshal.h>

#include "gc-iface-nmea-bindings.h"

//#include <glib.h>
#include <string.h>

typedef struct _GeoclueNmeaPrivate {
	int dummy;
} GeoclueNmeaPrivate;

enum {
	NMEA_CHANGED,
	LAST_SIGNAL
};

static guint32 signals[LAST_SIGNAL] = {0, };

#define GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GEOCLUE_TYPE_NMEA, GeoclueNmeaPrivate))

G_DEFINE_TYPE (GeoclueNmea, geoclue_nmea, GEOCLUE_TYPE_PROVIDER);

static void
finalize (GObject *object)
{
	G_OBJECT_CLASS (geoclue_nmea_parent_class)->finalize (object);
}

static void
dispose (GObject *object)
{
	G_OBJECT_CLASS (geoclue_nmea_parent_class)->dispose (object);
}

static void
nmea_changed (DBusGProxy      *proxy,
	      int              timestamp,
	      char             *nmea_data,
	      GeoclueNmea *nmea)
{
	g_signal_emit (nmea, signals[NMEA_CHANGED], 0,
		       timestamp, nmea_data);
}

static GObject *
constructor (GType                  type,
	     guint                  n_props,
	     GObjectConstructParam *props)
{
	GObject *object;
	GeoclueProvider *provider;

	object = G_OBJECT_CLASS (geoclue_nmea_parent_class)->constructor (type, n_props, props);
	provider = GEOCLUE_PROVIDER (object);

	dbus_g_proxy_add_signal (provider->proxy, "NmeaChanged",
				 G_TYPE_INT,
				 G_TYPE_STRING,
				 G_TYPE_INVALID);
	dbus_g_proxy_connect_signal (provider->proxy, "NmeaChanged",
				     G_CALLBACK (nmea_changed),
				     object, NULL);

	return object;
}

static void
geoclue_nmea_class_init (GeoclueNmeaClass *klass)
{
	GObjectClass *o_class = (GObjectClass *) klass;

	o_class->finalize = finalize;
	o_class->dispose = dispose;
	o_class->constructor = constructor;

	g_type_class_add_private (klass, sizeof (GeoclueNmeaPrivate));

	signals[NMEA_CHANGED] = g_signal_new ("nmea-changed",
					      G_TYPE_FROM_CLASS (klass),
					      G_SIGNAL_RUN_FIRST |
					      G_SIGNAL_NO_RECURSE,
					      G_STRUCT_OFFSET (GeoclueNmeaClass, nmea_changed),
					      NULL, NULL,
					      geoclue_marshal_VOID__INT_STRING,
					      G_TYPE_NONE, 2,
					      G_TYPE_INT,
					      G_TYPE_STRING);
}

static void
geoclue_nmea_init (GeoclueNmea *nmea)
{
}

/**
 * geoclue_nmea_new:
 * @service: D-Bus service name
 * @path: D-Bus path name
 *
 * Creates a #GeoclueNmea with given D-Bus service name and path.
 *
 * Return value: Pointer to a new #GeoclueNmea
 */
GeoclueNmea *
geoclue_nmea_new (const char *service,
		      const char *path)
{
	return g_object_new (GEOCLUE_TYPE_NMEA,
			     "service", service,
			     "path", path,
			     "interface", GEOCLUE_NMEA_INTERFACE_NAME,
			     NULL);
}

gboolean
geoclue_nmea_get_nmea (GeoclueNmea  *nmea,
		       int          *timestamp,
		       char        **nmea_data,
		       GError      **error)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (nmea);

	if (!org_freedesktop_Geoclue_Nmea_get_nmea (provider->proxy,
						    timestamp,
						    nmea_data,
						    error)) {
		return FALSE;
	}
	return TRUE;
}


typedef struct _GeoclueNmeaAsyncData {
	GeoclueNmea *nmea;
	GCallback callback;
	gpointer userdata;
} GeoclueNmeaAsyncData;

static void
get_nmea_async_callback (DBusGProxy           *proxy,
			 int                   timestamp,
			 char                 *nmea_data,
			 GError               *error,
			 GeoclueNmeaAsyncData *data)
{
	(*(GeoclueNmeaCallback)data->callback) (data->nmea,
						timestamp,
						nmea_data,
						error,
						data->userdata);
	g_free (data);
}

void
geoclue_nmea_get_nmea_async (GeoclueNmea         *nmea,
			     GeoclueNmeaCallback  callback,
			     gpointer             userdata)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (nmea);
	GeoclueNmeaAsyncData *data;

	data = g_new (GeoclueNmeaAsyncData, 1);
	data->nmea = nmea;
	data->callback = G_CALLBACK (callback);
	data->userdata = userdata;

	org_freedesktop_Geoclue_Nmea_get_nmea_async (
			provider->proxy,
			(org_freedesktop_Geoclue_Nmea_get_nmea_reply)get_nmea_async_callback,
			data);
}
