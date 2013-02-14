/*
 * Geoclue
 * gc-iface-poi.h - GInterface for org.freedesktop.Poi
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

#ifndef _GC_IFACE_POI_H
#define _GC_IFACE_POI_H

#include <geoclue/geoclue-types.h>
#include <geoclue/geoclue-accuracy.h>

G_BEGIN_DECLS

#define GC_TYPE_IFACE_POI (gc_iface_poi_get_type ())
#define GC_IFACE_POI(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GC_TYPE_IFACE_POI, GcIfacePoi))
#define GC_IFACE_POI_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GC_TYPE_IFACE_POI, GcIfacePoiClass))
#define GC_IS_IFACE_POI(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GC_TYPE_IFACE_POI))
#define GC_IS_IFACE_POI_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GC_TYPE_IFACE_POI))
#define GC_IFACE_POI_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GC_TYPE_IFACE_POI, GcIfacePoiClass))

typedef struct _GcIfacePoi GcIfacePoi; /* Dummy typedef */
typedef struct _GcIfacePoiClass GcIfacePoiClass;

struct _GcIfacePoiClass {
	GTypeInterface base_iface;

	/* vtable */
	gboolean (*search_by_position) (GcIfacePoi	*gc,
					const char	*keyword,
					const char	*lang,
					const char	*country_code,
					int 		limit,
					double		left,
					double		top,
					double		right,
					double 		bottom,
					int		*count,
					GPtrArray	**landmark,
					GError         **error);
};

GType gc_iface_poi_get_type (void);

G_END_DECLS

#endif
