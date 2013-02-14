/*
 * Geoclue
 * gc-iface-position-ext.h - GInterface for org.freedesktop.Geoclue.PositionExt
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

#ifndef _GC_IFACE_POSITION_EXT_H
#define _GC_IFACE_POSITION_EXT_H

#include <geoclue/geoclue-types.h>
#include <geoclue/geoclue-accuracy.h>

G_BEGIN_DECLS

#define GC_TYPE_IFACE_POSITION_EXT (gc_iface_position_ext_get_type ())
#define GC_IFACE_POSITION_EXT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GC_TYPE_IFACE_POSITION_EXT, GcIfacePositionExt))
#define GC_IFACE_POSITION_EXT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GC_TYPE_IFACE_POSITION_EXT, GcIfacePositionExtClass))
#define GC_IS_IFACE_POSITION_EXT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GC_TYPE_IFACE_POSITION_VELOCITY))
#define GC_IS_IFACE_POSITION_EXT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GC_TYPE_IFACE_POSITION_EXT))
#define GC_IFACE_POSITION_EXT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GC_TYPE_IFACE_POSITION_EXT, GcIfacePositionExtClass))

typedef struct _GcIfacePositionExt GcIfacePositionExt; /* Dummy typedef */
typedef struct _GcIfacePositionExtClass GcIfacePositionExtClass;

struct _GcIfacePositionExtClass {
        GTypeInterface base_iface;

	/* signals */
	void (* position_changed) (GcIfacePositionExt      *gc,
				   GeocluePositionExtFields fields,
				   int                   timestamp,
				   double                latitude,
				   double                longitude,
				   double                altitude,
				   double                speed,
				   double                direction,
				   double                climb,
				   GeoclueAccuracy      *accuracy);

	/* vtable */
	gboolean (* get_position) (GcIfacePositionExt       *gc,
				   GeocluePositionExtFields *fields,
				   int                   *timestamp,
				   double                *latitude,
				   double                *longitude,
				   double                *altitude,
				   double                *speed,
				   double                *direction,
				   double                *climb,
				   GeoclueAccuracy      **accuracy,
				   GError               **error);

	/* vtable */
	gboolean (* get_last_position) (GcIfacePositionExt 	*gc,
					GeocluePositionExtFields 	*fields,
					int			*timestamp,
					double			*latitude,
					double			*longitude,
					double			*altitude,
					double			*speed,
					double			*direction,
					double			*climb,
					GeoclueAccuracy 	**accuracy,
					GError			**error);
};

GType gc_iface_position_ext_get_type (void);

void gc_iface_position_ext_emit_position_changed (GcIfacePositionExt      *gc,
					      GeocluePositionExtFields fields,
					      int                   timestamp,
					      double                latitude,
					      double                longitude,
					      double                altitude,
					      double                speed,
					      double                direction,
					      double                climb,
					      GeoclueAccuracy      *accuracy);

G_END_DECLS

#endif
