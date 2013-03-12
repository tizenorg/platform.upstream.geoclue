/*
 * Geoclue
 * gc-iface-poi.c - GInterface for org.freedesktop.Poi
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

/* This is a GInterface for implementing Geoclue Poi providers */

#include <glib.h>

#include <dbus/dbus-glib.h>

#include <geoclue/geoclue-accuracy.h>
#include <geoclue/gc-iface-poi.h>

static gboolean
gc_iface_poi_search_by_position (GcIfacePoi   *gc,
	     const char *keyword,
	     const char *lang,
	     const char *country_code,
	     int limit,
	     double left,
	     double top,
	     double right,
	     double bottom,
	     int	*count,
	     GPtrArray 	**landmark,
	     GError          **error);

#include "gc-iface-poi-glue.h"

static void
gc_iface_poi_base_init (gpointer klass)
{
	static gboolean initialized = FALSE;

	if (initialized) {
		return;
	}
	initialized = TRUE;

	dbus_g_object_type_install_info (gc_iface_poi_get_type (),
					 &dbus_glib_gc_iface_poi_object_info);
}

GType
gc_iface_poi_get_type (void)
{
	static GType type = 0;

	if (!type) {
		const GTypeInfo info = {
			sizeof (GcIfacePoiClass),
			gc_iface_poi_base_init,
			NULL,
		};

		type = g_type_register_static (G_TYPE_INTERFACE,
					       "GcIfacePoi", &info, 0);
	}

	return type;
}

static gboolean
gc_iface_poi_search_by_position (GcIfacePoi		*gc,
				const char		*keyword,
				const char		*lang,
				const char 		*country_code,
				int 			limit,
				double			left,
				double			top,
				double			right,
				double    		bottom,
				int			*count,
				GPtrArray 		**landmark,
				GError			**error)
{
	return GC_IFACE_POI_GET_CLASS (gc)->search_by_position
		(gc, keyword, lang, country_code, limit, left, top, right, bottom, count, landmark, error);
}
