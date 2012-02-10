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

#include <glib.h>
#include <vconf.h>
#include "setting.h"

int setting_get_int(const char *path, int *val)
{
	if (!path) {
		return FALSE;
	}

	int ret;

	if (vconf_get_int(path, val) == -1) {
		g_warning("vconf_get_int: failed [%s]", path);
		ret = FALSE;
	} else {
		g_debug("vconf_get_int: [%s]:[%d]", path, *val);
		ret = TRUE;
	}
	return ret;
}

int setting_set_int(const char *path, int val)
{
	if (!path) {
		return FALSE;
	}

	int ret = vconf_set_int(path, val);
	if (ret == 0) {
		g_debug("vconf_set_int: [%s]:[%d]", path, val);
		ret = TRUE;
	} else {
		g_warning("vconf_set_int failed, [%s]", path);
		ret = FALSE;
	}
	return ret;
}

int setting_get_double(const char *path, double *val)
{
	if (!path) {
		return FALSE;
	}

	int ret;

	if (vconf_get_dbl(path, val) == -1) {
		g_warning("vconf_get_dbl failed [%s]", path);
		ret = FALSE;
	} else {
		g_debug("vconf_get_dbl: [%s]:[%f]", path, *val);
		ret = TRUE;
	}
	return ret;
}

int setting_set_double(const char *path, double val)
{
	if (!path) {
		return FALSE;
	}

	int ret = vconf_set_dbl(path, val);
	if (ret == 0) {
		g_debug("vconf_set_dbl: [%s]:[%f]", path, val);
		ret = TRUE;
	} else {
		g_warning("vconf_set_dbl failed, [%s]", path);
		ret = FALSE;
	}
	return ret;
}
