/*
 * Geoclue
 * geoclue-poi.h -
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

#ifndef _GEOCLUE_POI_H
#define _GEOCLUE_POI_H

#include <geoclue/geoclue-provider.h>
#include <geoclue/geoclue-types.h>
#include <geoclue/geoclue-accuracy.h>
#include <geoclue/geoclue-address-details.h>

G_BEGIN_DECLS

#define GEOCLUE_TYPE_POI (geoclue_poi_get_type ())
#define GEOCLUE_POI(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEOCLUE_TYPE_POI, GeocluePoi))
#define GEOCLUE_IS_POI(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEOCLUE_TYPE_POI))

#define GEOCLUE_POI_INTERFACE_NAME "org.freedesktop.Geoclue.Poi"

typedef struct _GeocluePoi {
	GeoclueProvider provider;
} GeocluePoi;

typedef struct _GeocluePoiClass {
	GeoclueProviderClass provider_class;
} GeocluePoiClass;

GType geoclue_poi_get_type (void);

GeocluePoi *geoclue_poi_new (const char *service,
				     const char *path);

gboolean
geoclue_poi_search_by_position (GeocluePoi	*poi,
				const char	*keyword,
				const char 	*lang,
				const char 	*country_code,
				int		limit,
				double 		left,
				double    	top,
				double 		right,
				double    	bottom,
				int		*count,
				GPtrArray 	**landmark,
				GError          **error);

typedef void (*GeocluePoiCallback) (GeocluePoi       	*poi,
				int				count,
				GPtrArray				*landmark,
				GError               	*error,
				gpointer              	userdata);

void
geoclue_poi_search_by_position_async (GeocluePoi        *poi,
				const char 		*keyword,
				const char 		*lang,
				const char 		*country_code,
				int 			limit,
				double			left,
				double			top,
				double 			right,
				double    		bottom,
				GeocluePoiCallback  	callback,
				gpointer		userdata);

G_END_DECLS

#endif
