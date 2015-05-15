/*
 * Name:    debug.h
 *
 * Purpose: general debug system
 *
 * Copyright (C) 2014 wowotech
 * Subject to the GNU Public License, version 2.
 *
 * Created By:         wowo<www.wowotech.net>
 * Created Date:       2014-01-23
 *
 * ChangeList:
 * Created in 2014-01-23 by wowo;
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

/* 
 * debug control, you can switch on (delete 'x' suffix)
 * to enable log output and assert mechanism
 */
#define CONFIG_ENABLE_DEBUG

/* 
 * debug level,
 * if is DEBUG_LEVEL_DISABLE, no log is allowed output,
 * if is DEBUG_LEVEL_ERR, only ERR is allowed output,
 * if is DEBUG_LEVEL_INFO, ERR and INFO are allowed output,
 * if is DEBUG_LEVEL_DEBUG, all log are allowed output,
 */
enum debug_level {
    DEBUG_LEVEL_DISABLE = 0,
    DEBUG_LEVEL_ERR,
    DEBUG_LEVEL_INFO,
    DEBUG_LEVEL_DEBUG
};

#ifdef CONFIG_ENABLE_DEBUG

/* it can be change to others, such as file operations */
#include <stdio.h>
#define PRINT               printf

/* 
 * the macro to set debug level, you should call it 
 * once in the files you need use debug system
 */
#define DEBUG_SET_LEVEL(x)  static int debug = x

#define ASSERT()                                        \
do {                                                    \
    PRINT("ASSERT: %s %s %d",                           \
           __FILE__, __FUNCTION__, __LINE__);           \
    while (1);                                          \
} while (0)

#define ERR(...)                                        \
do {                                                    \
    if (debug >= DEBUG_LEVEL_ERR) {                     \
        PRINT(__VA_ARGS__);                             \
    }                                                   \
} while (0)

#define INFO(...)                                       \
do {                                                    \
    if (debug >= DEBUG_LEVEL_INFO) {                    \
        PRINT(__VA_ARGS__);                             \
    }                                                   \
} while (0)

#define DEBUG(...)                                      \
do {                                                    \
    if (debug >= DEBUG_LEVEL_DEBUG) {                   \
        PRINT(__VA_ARGS__);                             \
    }                                                   \
} while (0)

#else   /* CONFIG_ENABLE_DEBUG  */

#define DEBUG_SET_LEVEL(x) 
#define ASSERT()
#define ERR(...)
#define INFO(...)
#define DEBUG(...)

#endif  /* CONFIG_ENABLE_DEBUG  */

#endif  /* _DEBUG_H_ */
