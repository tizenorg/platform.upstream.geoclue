/*
 * Geoclue Providers
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Contact: Youngae Kang <youngae.kang@samsung.com>, Yunhan Kim <yhan.kim@samsung.com>,
 *          Genie Kim <daejins.kim@samsung.com>, Minjune Kim <sena06.kim@samsung.com>
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * SAMSUNG ELECTRONICS ("Confidential Information").
 *
 * You agree and acknowledge that this software is owned by Samsung and you
 * shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * SAMSUNG ELECTRONICS.
 *
 * SAMSUNG make no representations or warranties about the suitability
 * of the software, either express or implied, including but not limited to
 * the implied warranties of merchantability, fitness for a particular purpose,
 * or non-infringement.
 *
 * SAMSUNG shall not be liable for any damages suffered by licensee arising
 * out of or related to this software.
 */

#ifndef __SETTING_H__
#define __SETTING_H__

#define VCONF_LOCATION_PATH 	"db/location"

#define LAST_POSITION_PATH 	VCONF_LOCATION_PATH"/lastposition"
#define METHOD_GPS 		LAST_POSITION_PATH"/gps"
#define METHOD_WPS 		LAST_POSITION_PATH"/wps"

#define LAST_GPS_TIMESTAMP 	METHOD_GPS"/Timestamp"
#define LAST_GPS_LATITUDE 	METHOD_GPS"/Latitude"
#define LAST_GPS_LONGITUDE 	METHOD_GPS"/Longitude"
#define LAST_GPS_ALTITUDE 	METHOD_GPS"/Altitude"
#define LAST_GPS_HOR_ACCURACY	METHOD_GPS"/HorAccuracy"
#define LAST_GPS_VER_ACCURACY 	METHOD_GPS"/VerAccuracy"

#define LAST_WPS_TIMESTAMP      METHOD_WPS"/Timestamp"
#define LAST_WPS_LATITUDE       METHOD_WPS"/Latitude"
#define LAST_WPS_LONGITUDE      METHOD_WPS"/Longitude"
#define LAST_WPS_ALTITUDE       METHOD_WPS"/Altitude"
#define LAST_WPS_HOR_ACCURACY   METHOD_WPS"/HorAccuracy"

int setting_get_int(const char *path, int *val);
int setting_set_int(const char *path, int val);
int setting_get_double(const char *path, double *val);
int setting_set_double(const char *path, double val);
#endif
