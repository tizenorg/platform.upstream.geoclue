/*
 * Geoclue
 * geoclue-position-ext.h
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

#ifndef _GEOCLUE_POSITION_EXT_H
#define _GEOCLUE_POSITION_EXT_H

#include <geoclue/geoclue-provider.h>
#include <geoclue/geoclue-types.h>
#include <geoclue/geoclue-accuracy.h>

G_BEGIN_DECLS

#define GEOCLUE_TYPE_POSITION_EXT (geoclue_position_ext_get_type ())
#define GEOCLUE_POSITION_EXT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEOCLUE_TYPE_POSITION_EXT, GeocluePositionExt))
#define GEOCLUE_IS_POSITION_EXT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEOCLUE_TYPE_POSITION_EXT))

#define GEOCLUE_POSITION_EXT_INTERFACE_NAME "org.freedesktop.Geoclue.PositionExt"

typedef struct _GeocluePositionExt {
	GeoclueProvider provider;
} GeocluePositionExt;

typedef struct _GeocluePositionExtClass {
	GeoclueProviderClass provider_class;

	void (* position_changed) (GeocluePositionExt      *position,
				   GeocluePositionExtFields fields,
				   int                   timestamp,
				   double                latitude,
				   double                longitude,
				   double                altitude,
				   double                speed,
				   double                direction,
				   double                climb,
				   GeoclueAccuracy      *accuracy);
} GeocluePositionExtClass;

GType geoclue_position_ext_get_type (void);

GeocluePositionExt *geoclue_position_ext_new (const char *service,
				       const char *path);

GeocluePositionExtFields geoclue_position_ext_get_position (GeocluePositionExt  *position,
						     int              *timestamp,
						     double           *latitude,
						     double           *longitude,
						     double           *altitude,
						     double           *speed,
						     double           *direction,
						     double           *climb,
						     GeoclueAccuracy **accuracy,
						     GError          **error);

GeocluePositionExtFields geoclue_position_ext_get_last_position (GeocluePositionExt  *position,
							  int              *timestamp,
							  double           *latitude,
							  double           *longitude,
							  double           *altitude,
							  double           *speed,
							  double           *direction,
							  double           *climb,
							  GeoclueAccuracy **accuracy,
							  GError          **error);

typedef void (*GeocluePositionExtCallback) (GeocluePositionExt      *position,
					 GeocluePositionExtFields fields,
					 int                   timestamp,
					 double                latitude,
					 double                longitude,
					 double                altitude,
					 double                speed,
					 double                direction,
					 double                climb,
					 GeoclueAccuracy      *accuracy,
					 GError               *error,
					 gpointer              userdata);

void geoclue_position_ext_get_position_async (GeocluePositionExt         *position,
					  GeocluePositionExtCallback  callback,
					  gpointer                 userdata);

G_END_DECLS

#endif
