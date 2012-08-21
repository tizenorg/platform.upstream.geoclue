/*
 * Geoclue
 * geoclue-landmark.h
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
#ifndef _GEOCLUE_LANDMARK_H
#define _GEOCLUE_LANDMARK_H

#include <geoclue/geoclue-provider.h>
#include <geoclue/geoclue-types.h>

G_BEGIN_DECLS

#define GEOCLUE_LANDMARK (dbus_g_type_get_struct ("GValueArray", G_TYPE_INT, G_TYPE_INT, G_TYPE_DOUBLE, G_TYPE_DOUBLE, G_TYPE_DOUBLE, G_TYPE_DOUBLE, G_TYPE_DOUBLE, G_TYPE_DOUBLE, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID))

#define GEOCLUE_LANDMARK_ARRAY (dbus_g_type_get_collection ("GPtrArray", GEOCLUE_LANDMARK))

typedef struct _GeoclueLandmark {
	gint id;
	gint rank;
	gdouble lat;
	gdouble lon;
	gdouble boundary_left;
	gdouble boundary_top;
	gdouble boundary_right;
	gdouble boundary_bottom;
	gchar *name;
	gchar *icon;
	gchar *house;
	gchar *road;
	gchar *village;
	gchar *suburb;
	gchar *postcode;
	gchar *city;
	gchar *county;
	gchar *country;
	gchar *country_code;
} GeoclueLandmark;

G_END_DECLS

#endif
