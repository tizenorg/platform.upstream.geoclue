/*
 * Geoclue
 * geoclue-nmea.h - 
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


#ifndef _GEOCLUE_NMEA_H
#define _GEOCLUE_NMEA_H

#include <geoclue/geoclue-provider.h>
#include <geoclue/geoclue-types.h>
//#include <geoclue/geoclue-accuracy.h>

G_BEGIN_DECLS

#define GEOCLUE_TYPE_NMEA (geoclue_nmea_get_type ())
#define GEOCLUE_NMEA(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEOCLUE_TYPE_NMEA, GeoclueNmea))
#define GEOCLUE_IS_NMEA(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEOCLUE_TYPE_NMEA))

#define GEOCLUE_NMEA_INTERFACE_NAME "org.freedesktop.Geoclue.Nmea"

#define GEOCLUE_MAX_NMEA_DATA_SIZE (1500)

typedef struct _GeoclueNmea {
	GeoclueProvider provider;
} GeoclueNmea;

typedef struct _GeoclueNmeaClass {
	GeoclueProviderClass provider_class;

	void (* nmea_changed) (GeoclueNmea *nmea,
			       int          timestamp,
			       char         nmea_data[GEOCLUE_MAX_NMEA_DATA_SIZE]);
} GeoclueNmeaClass;

GType geoclue_nmea_get_type (void);

GeoclueNmea *geoclue_nmea_new (const char *service,
			       const char *path);

gboolean geoclue_nmea_get_nmea (GeoclueNmea *nmea,
				int         *timestamp,
				char       **nmea_data,
				GError     **error);

typedef void (*GeoclueNmeaCallback) (GeoclueNmea *nmea,
				     int          timestamp,
				     char        *nmea_data,
				     GError      *error,
				     gpointer     userdata);

void geoclue_nmea_get_nmea_async (GeoclueNmea         *nmea,
				  GeoclueNmeaCallback  callback,
				  gpointer             userdata);

G_END_DECLS

#endif
