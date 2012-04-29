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

// Sync VCONFKEY_GPS_STATE
#define VCONF_LOCATION_PATH 		"db/location"

#define LOCATION_POSITION_PATH 		VCONF_LOCATION_PATH"/position"
#define LAST_TIMESTAMP			LOCATION_POSITION_PATH"/Timestamp"
#define LAST_POSITION 			LOCATION_POSITION_PATH"/LastPosition"
#define LAST_ACCURACY			LOCATION_POSITION_PATH"/LastAccuracy"

int setting_get_int(const char* path);
int setting_set_int(const char* path, int val);
char* setting_get_string(const char* path);
int setting_set_string(const char* path, const char* val);
#endif
