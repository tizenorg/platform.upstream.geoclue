/*
 * Geoclue
 * gc-iface-nmea.h - GInterface for org.freedesktop.Geoclue.Nmea
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

#ifndef _GC_IFACE_NMEA_H
#define _GC_IFACE_NMEA_H

#include <geoclue/geoclue-types.h>

G_BEGIN_DECLS

#define GC_TYPE_IFACE_NMEA (gc_iface_nmea_get_type ())
#define GC_IFACE_NMEA(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GC_TYPE_IFACE_NMEA, GcIfaceNmea))
#define GC_IFACE_NMEA_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GC_TYPE_IFACE_NMEA, GcIfaceNmeaClass))
#define GC_IS_IFACE_NMEA(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GC_TYPE_IFACE_NMEA))
#define GC_IS_IFACE_NMEA_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GC_TYPE_IFACE_NMEA))
#define GC_IFACE_NMEA_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GC_TYPE_IFACE_NMEA, GcIfaceNmeaClass))

typedef struct _GcIfaceNmea GcIfaceNmea; /* Dummy typedef */

typedef struct _GcIfaceNmeaClass {
        GTypeInterface base_iface;

	/* signals */
	void (* nmea_changed) (GcIfaceNmea *gc,
			       int          timestamp,
			       char        *nmea_data);

	/* vtable */
	gboolean (* get_nmea) (GcIfaceNmea *gc,
			       int         *timestamp,
			       char       **nmea_data,
			       GError     **error);
} GcIfaceNmeaClass;

GType gc_iface_nmea_get_type (void);

void gc_iface_nmea_emit_nmea_changed (GcIfaceNmea *gc,
				      int timestamp,
				      char *nmea_data);

G_END_DECLS

#endif
