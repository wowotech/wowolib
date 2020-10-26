/*
 * debug_test.c
 *
 * the test program of debug system
 *
 * Copyright (C) 2014 wowotech
 * Subject to the GNU Public License, version 2.
 *
 * Author:          wowo<www.wowotech.net>
 *
 * Changelog:
 *     Date         Desc
 *     2014-01-23   Created by wowo
 * 
 */

#include "debug.h"

/*
 * define the debug level of this file,
 * please see 'debug.h' for detail info
 */
DEBUG_SET_LEVEL(DEBUG_LEVEL_ERR);

int main(void) {
    ERR("This is a error message\n"); 
    INFO("This is a info message\n"); 
    DEBUG("This is a debug message\n"); 

    ASSERT();
    return 0;
}
