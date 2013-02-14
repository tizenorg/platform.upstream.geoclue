/*
 * Geoclue
 * gc-iface-nmea.c - GInterface for org.freedesktop.Geoclue.Nmea
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
#include <glib.h>

#include <dbus/dbus-glib.h>
#include <geoclue/gc-iface-nmea.h>
#include <geoclue/geoclue-marshal.h>

enum {
	NMEA_CHANGED,
	LAST_SIGNAL
};

static guint signals[LAST_SIGNAL] = {0};

static gboolean
gc_iface_nmea_get_nmea (GcIfaceNmea *nmea,
			int         *timestamp,
			char       **nmea_data,
			GError     **error);

#include "gc-iface-nmea-glue.h"

static void
gc_iface_nmea_base_init (gpointer klass)
{
	static gboolean initialized = FALSE;

	if (initialized) {
		return;
	}
	initialized = TRUE;

	signals[NMEA_CHANGED] = g_signal_new ("nmea-changed",
					      G_OBJECT_CLASS_TYPE (klass),
					      G_SIGNAL_RUN_LAST, 0,
					      NULL, NULL,
					      geoclue_marshal_VOID__INT_STRING,
					      G_TYPE_NONE, 2,
					      G_TYPE_INT,
					      G_TYPE_STRING);

	dbus_g_object_type_install_info (gc_iface_nmea_get_type (),
					 &dbus_glib_gc_iface_nmea_object_info);
}

GType
gc_iface_nmea_get_type (void)
{
	static GType type = 0;

	if (!type) {
		const GTypeInfo info = {
			sizeof (GcIfaceNmeaClass),
			gc_iface_nmea_base_init,
			NULL,
		};

		type = g_type_register_static (G_TYPE_INTERFACE,
					       "GcIfaceNmea", &info, 0);
	}

	return type;
}

static gboolean
gc_iface_nmea_get_nmea (GcIfaceNmea *gc,
			int         *timestamp,
			char       **nmea_data,
			GError     **error)
{
	return GC_IFACE_NMEA_GET_CLASS (gc)->get_nmea (gc, timestamp, nmea_data, error);
}

void
gc_iface_nmea_emit_nmea_changed (GcIfaceNmea *gc,
				 int          timestamp,
				 char        *nmea_data)
{
	g_signal_emit (gc, signals[NMEA_CHANGED], 0, timestamp, nmea_data);
}
