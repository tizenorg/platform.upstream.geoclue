/*
 * Geoclue
 * geoclue-types.h - Types for Geoclue
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

#ifndef _GEOCLUE_TYPES_H
#define _GEOCLUE_TYPES_H

#include <geoclue/geoclue-error.h>

/**
 * SECTION:geoclue-types
 * @short_description: Type definitions and defines useful for Geoclue clients
 **/


/**
 * GeoclueStatus
 *
 * defines the provider status
 **/
typedef enum {
	GEOCLUE_STATUS_ERROR,
	GEOCLUE_STATUS_UNAVAILABLE,
	GEOCLUE_STATUS_ACQUIRING,
	GEOCLUE_STATUS_AVAILABLE
} GeoclueStatus;

/**
 * GeoclueAccuracyLevel:
 *
 * Enum values used to define the approximate accuracy of
 * Position or Address information.
 **/
typedef enum {
	GEOCLUE_ACCURACY_LEVEL_NONE = 0,
	GEOCLUE_ACCURACY_LEVEL_COUNTRY,
	GEOCLUE_ACCURACY_LEVEL_REGION,
	GEOCLUE_ACCURACY_LEVEL_LOCALITY,
	GEOCLUE_ACCURACY_LEVEL_POSTALCODE,
	GEOCLUE_ACCURACY_LEVEL_STREET,
	GEOCLUE_ACCURACY_LEVEL_DETAILED,
} GeoclueAccuracyLevel;

/**
 * GeocluePositionFields:
 *
 * #GeocluePositionFields is a bitfield that defines the validity of
 * Position values.
 *
 * Example:
 * <informalexample>
 * <programlisting>
 * GeocluePositionFields fields;
 * fields = geoclue_position_get_position (. . .);
 *
 * if (fields & GEOCLUE_POSITION_FIELDS_LATITUDE &&
 *     fields & GEOCLUE_POSITION_FIELDS_LONGITUDE) {
 * 	g_print("latitude and longitude are valid");
 * }
 * </programlisting>
 * </informalexample>
 **/
typedef enum {
	GEOCLUE_POSITION_FIELDS_NONE = 0,
	GEOCLUE_POSITION_FIELDS_LATITUDE = 1 << 0,
	GEOCLUE_POSITION_FIELDS_LONGITUDE = 1 << 1,
	GEOCLUE_POSITION_FIELDS_ALTITUDE = 1 << 2
} GeocluePositionFields;

/**
 * GeoclueVelocityFields:
 *
 * GeoclueVelocityFields is a bitfield that defines the validity of
 * Velocity values.
 **/
typedef enum {
	GEOCLUE_VELOCITY_FIELDS_NONE = 0,
	GEOCLUE_VELOCITY_FIELDS_SPEED = 1 << 0,
	GEOCLUE_VELOCITY_FIELDS_DIRECTION = 1 << 1,
	GEOCLUE_VELOCITY_FIELDS_CLIMB = 1 << 2
} GeoclueVelocityFields;

/**
 * GEOCLUE_ADDRESS_KEY_COUNTRYCODE:
 *
 * A key for address hashtables. The hash value should be a ISO 3166 two
 * letter country code.
 *
 * The used hash keys match the elements of XEP-0080 (XMPP protocol
 * extension for user location), see
 * <ulink url="http://www.xmpp.org/extensions/xep-0080.html">
 * http://www.xmpp.org/extensions/xep-0080.html</ulink>
 */
#define GEOCLUE_ADDRESS_KEY_COUNTRYCODE "countrycode"
/**
 * GEOCLUE_ADDRESS_KEY_COUNTRY:
 *
 * A key for address hashtables. The hash value should be a name of a country.
 */
#define GEOCLUE_ADDRESS_KEY_COUNTRY "country"
/**
 * GEOCLUE_ADDRESS_KEY_REGION:
 *
 * A key for address hashtables. The hash value should be a name of an
 * administrative region of a nation, e.g. province or
 * US state.
 */
#define GEOCLUE_ADDRESS_KEY_REGION "region"
/**
 * GEOCLUE_ADDRESS_KEY_LOCALITY:
 *
 * A key for address hashtables. The hash value should be a name of a town
 * or city.
 */
#define GEOCLUE_ADDRESS_KEY_LOCALITY "locality"
/**
 * GEOCLUE_ADDRESS_KEY_AREA:
 *
 * A key for address hashtables. The hash value should be a name of an
 * area, such as neighborhood or campus.
 */
#define GEOCLUE_ADDRESS_KEY_AREA "area"
/**
 * GEOCLUE_ADDRESS_KEY_POSTALCODE:
 *
 * A key for address hashtables. The hash value should be a code used for
 * postal delivery.
 */
#define GEOCLUE_ADDRESS_KEY_POSTALCODE "postalcode"
/**
 * GEOCLUE_ADDRESS_KEY_STREET:
 *
 * A key for address hashtables. The hash value should be a partial or full street
 * address.
 */
#define GEOCLUE_ADDRESS_KEY_STREET "street"

/**
 * GEOCLUE_LANDMARK_KEY_COUNTRYCODE:
 *
 * A key for landmark hashtables. The hash value should be a ISO 3166 two
 * letter country code.
 *
 * The used hash keys match the elements of XEP-0080 (XMPP protocol
 * extension for user location), see
 * <ulink url="http://www.xmpp.org/extensions/xep-0080.html">
 * http://www.xmpp.org/extensions/xep-0080.html</ulink>
 */
#define GEOCLUE_LANDMARK_KEY_COUNTRYCODE GEOCLUE_ADDRESS_KEY_COUNTRYCODE
/**
 * GEOCLUE_LANDMARK_KEY_ID:
 *
 * A key for landmark hashtables. The hash value should be an id of a landmark.
 */
#define GEOCLUE_LANDMARK_KEY_ID "id"
/**
 * GEOCLUE_LANDMARK_KEY_RANK:
 *
 * A key for landmark hashtables. The hash value should be a rank of a landmark.
 */
#define GEOCLUE_LANDMARK_KEY_RANK "rank"
/**
 * GEOCLUE_LANDMARK_KEY_LAT:
 *
 * A key for landmark hashtables. The hash value should be a latitude of a landmark.
 */
#define GEOCLUE_LANDMARK_KEY_LAT "lat"
/**
 * GEOCLUE_LANDMARK_KEY_LON:
 *
 * A key for landmark hashtables. The hash value should be a longitude of a landmark.
 */
#define GEOCLUE_LANDMARK_KEY_LON "lon"
/**
 * GEOCLUE_LANDMARK_KEY_BOUNDINGBOX:
 *
 * A key for landmark hashtables. The hash value should be a bounding box of a landmark.
 */
#define GEOCLUE_LANDMARK_KEY_BOUNDINGBOX "boundingbox"
/**
 * GEOCLUE_LANDMARK_KEY_NAME:
 *
 * A key for landmark hashtables. The hash value should be a display name of a landmark.
 */
#define GEOCLUE_LANDMARK_KEY_NAME "display_name"
/**
 * GEOCLUE_LANDMARK_KEY_HOUSE:
 *
 * A key for landmark hashtables. The hash value should be a house of a landmark.
 */
#define GEOCLUE_LANDMARK_KEY_HOUSE "house"
/**
 * GEOCLUE_LANDMARK_KEY_ROAD:
 *
 * A key for landmark hashtables. The hash value should be a road of a landmark.
 */
#define GEOCLUE_LANDMARK_KEY_ROAD "road"
/**
 * GEOCLUE_LANDMARK_KEY_VILLAGE:
 *
 * A key for landmark hashtables. The hash value should be a village of a landmark.
 */
#define GEOCLUE_LANDMARK_KEY_VILLAGE "village"
/**
 * GEOCLUE_LANDMARK_KEY_SUBURB:
 *
 * A key for landmark hashtables. The hash value should be a suburb of a landmark.
 */
#define GEOCLUE_LANDMARK_KEY_SUBURB "suburb"
/**
 * GEOCLUE_LANDMARK_KEY_POSTCODE:
 *
 * A key for landmark hashtables. The hash value should be a postcode of a landmark.
 */
#define GEOCLUE_LANDMARK_KEY_POSTCODE "postcode"
/**
 * GEOCLUE_LANDMARK_KEY_CITY:
 *
 * A key for landmark hashtables. The hash value should be a city of a landmark.
 */
#define GEOCLUE_LANDMARK_KEY_CITY "city"
/**
 * GEOCLUE_LANDMARK_KEY_COUNTY:
 *
 * A key for landmark hashtables. The hash value should be a county of a landmark.
 */
#define GEOCLUE_LANDMARK_KEY_COUNTY "county"
/**
 * GEOCLUE_LANDMARK_KEY_ICON:
 *
 * A key for landmark hashtables. The hash value should be an icon path of a landmark.
 */
#define GEOCLUE_LANDMARK_KEY_ICON "icon"
/**
 * GEOCLUE_LANDMARK_KEY_COUNTRY:
 *
 * A key for landmark hashtables. The hash value should be a name of a country.
 */
#define GEOCLUE_LANDMARK_KEY_COUNTRY GEOCLUE_ADDRESS_KEY_COUNTRY
/**
 * GEOCLUE_LANDMARK_KEY_REGION:
 *
 * A key for landmark hashtables. The hash value should be a name of an
 * administrative region of a nation, e.g. province or
 * US state.
 */
#define GEOCLUE_LANDMARK_KEY_REGION GEOCLUE_ADDRESS_KEY_REGION
/**
 * GEOCLUE_LANDMARK_KEY_LOCALITY:
 *
 * A key for landmark hashtables. The hash value should be a name of a town
 * or city.
 */
#define GEOCLUE_LANDMARK_KEY_LOCALITY GEOCLUE_ADDRESS_KEY_LOCALITY
/**
 * GEOCLUE_LANDMARK_KEY_AREA:
 *
 * A key for landmark hashtables. The hash value should be a name of an
 * area, such as neighborhood or campus.
 */
#define GEOCLUE_LANDMARK_KEY_AREA GEOCLUE_ADDRESS_KEY_AREA
/**
 * GEOCLUE_LANDMARK_KEY_POSTALCODE:
 *
 * A key for landmark hashtables. The hash value should be a code used for
 * postal delivery.
 */
#define GEOCLUE_LANDMARK_KEY_POSTALCODE GEOCLUE_ADDRESS_KEY_POSTALCODE
/**
 * GEOCLUE_LANDMARK_KEY_STREET:
 *
 * A key for landmark hashtables. The hash value should be a partial or full street
 * address.
 */
#define GEOCLUE_LANDMARK_KEY_STREET GEOCLUE_ADDRESS_KEY_STREET


/**
 * GeoclueResourceFlags:
 *
 * bitfield that represents a set of physical resources.
 *
 **/
typedef enum _GeoclueResourceFlags {
	GEOCLUE_RESOURCE_NONE = 0,
	GEOCLUE_RESOURCE_NETWORK = 1 << 0,
	GEOCLUE_RESOURCE_CELL = 1 << 1,
	GEOCLUE_RESOURCE_GPS = 1 << 2,

	GEOCLUE_RESOURCE_ALL = (1 << 10) - 1
} GeoclueResourceFlags;


/**
 * GeoclueNetworkStatus:
 *
 * Enumeration for current network status.
 *
 **/
typedef enum {
	GEOCLUE_CONNECTIVITY_UNKNOWN,
	GEOCLUE_CONNECTIVITY_OFFLINE,
	GEOCLUE_CONNECTIVITY_ACQUIRING,
	GEOCLUE_CONNECTIVITY_ONLINE,
} GeoclueNetworkStatus;



void geoclue_types_init (void);

#endif
