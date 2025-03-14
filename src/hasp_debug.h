/* MIT License - Copyright (c) 2019-2021 Francis Van Roie
   For full license information read the LICENSE file in the project folder */

#ifndef HASP_DEBUG_H
#define HASP_DEBUG_H

#include "ArduinoJson.h"
#include "hasp_macro.h"
#include "lvgl.h"

#include "lang/lang.h"

#if(!defined(WINDOWS)) && (!defined(POSIX))
#include "ArduinoLog.h"

/* ===== Default Event Processors ===== */
void debugPreSetup(JsonObject settings);
void debugSetup();

/* ===== Special Event Processors ===== */

void debugStartSyslog(void);
void debugStopSyslog(void);
// void syslogSend(uint8_t log, const char * debugText);

#else

#define Print void

#include <iostream>
#include <sys/time.h>

#define LOG_LEVEL_SILENT -1

#define LOG_LEVEL_FATAL 0
#define LOG_LEVEL_ALERT 1
#define LOG_LEVEL_CRITICAL 2
#define LOG_LEVEL_ERROR 3
#define LOG_LEVEL_WARNING 4
#define LOG_LEVEL_NOTICE 5
#define LOG_LEVEL_INFO 5
#define LOG_LEVEL_TRACE 6
#define LOG_LEVEL_VERBOSE 7
#define LOG_LEVEL_DEBUG 8
#define LOG_LEVEL_OUTPUT 9

#define LOG_FATAL(x, ...)                                                                                              \
    debugPrintPrefix(x, LOG_LEVEL_FATAL, NULL);                                                                        \
    printf(__VA_ARGS__);                                                                                               \
    std::cout << std::endl;                                                                                            \
    fflush(stdout)
#define LOG_ERROR(x, ...)                                                                                              \
    debugPrintPrefix(x, LOG_LEVEL_ERROR, NULL);                                                                        \
    printf(__VA_ARGS__);                                                                                               \
    std::cout << std::endl;                                                                                            \
    fflush(stdout)
#define LOG_WARNING(x, ...)                                                                                            \
    debugPrintPrefix(x, LOG_LEVEL_WARNING, NULL);                                                                      \
    printf(__VA_ARGS__);                                                                                               \
    std::cout << std::endl;                                                                                            \
    fflush(stdout)
#define LOG_NOTICE(x, ...)                                                                                             \
    debugPrintPrefix(x, LOG_LEVEL_NOTICE, NULL);                                                                       \
    printf(__VA_ARGS__);                                                                                               \
    std::cout << std::endl;                                                                                            \
    fflush(stdout)
#define LOG_TRACE(x, ...)                                                                                              \
    debugPrintPrefix(x, LOG_LEVEL_TRACE, NULL);                                                                        \
    printf(__VA_ARGS__);                                                                                               \
    std::cout << std::endl;                                                                                            \
    fflush(stdout)
#define LOG_VERBOSE(x, ...)                                                                                            \
    debugPrintPrefix(x, LOG_LEVEL_VERBOSE, NULL);                                                                      \
    printf(__VA_ARGS__);                                                                                               \
    std::cout << std::endl;                                                                                            \
    fflush(stdout)
#define LOG_DEBUG(x, ...)                                                                                              \
    debugPrintPrefix(x, LOG_LEVEL_DEBUG, NULL);                                                                        \
    printf(__VA_ARGS__);                                                                                               \
    std::cout << std::endl;                                                                                            \
    fflush(stdout)
#define LOG_INFO(x, ...)                                                                                               \
    debugPrintPrefix(x, LOG_LEVEL_INFO, NULL);                                                                         \
    printf(__VA_ARGS__);                                                                                               \
    std::cout << std::endl;                                                                                            \
    fflush(stdout)

#endif

#ifdef __cplusplus
extern "C" {
#endif

// Functions used by ANDROID, WINDOWS and POSSIX
void debugLvglLogEvent(lv_log_level_t level, const char* file, uint32_t line, const char* funcname, const char* descr);
void debugLoop(void);
void debugEverySecond(void);
void debugStart(void);
void debugStop(void);
void debugPrintHaspHeader(Print* output);
void debugPrintTag(uint8_t tag, Print* _logOutput);
void debugPrintPrefix(uint8_t tag, int level, Print* _logOutput);

#ifdef __cplusplus
}
#endif

/* ===== Read/Write Configuration ===== */
#if HASP_USE_CONFIG > 0
bool debugGetConfig(const JsonObject& settings);
bool debugSetConfig(const JsonObject& settings);
#endif

enum {
    TAG_MAIN  = 0,
    TAG_HASP  = 1,
    TAG_ATTR  = 2,
    TAG_MSGR  = 3,
    TAG_OOBE  = 4,
    TAG_HAL   = 5,
    TAG_DRVR  = 6,
    TAG_DEV   = 7,
    TAG_EVENT = 8,

    TAG_DEBG = 10,
    TAG_TELN = 11,
    TAG_SYSL = 12,
    TAG_TASM = 13,

    TAG_CONF = 20,
    TAG_GUI  = 21,
    TAG_TFT  = 22,

    TAG_EPRM = 30,
    TAG_FILE = 31,
    TAG_GPIO = 40,

    TAG_FWUP = 50,

    TAG_ETH      = 60,
    TAG_WIFI     = 61,
    TAG_HTTP     = 62,
    TAG_OTA      = 63,
    TAG_MDNS     = 64,
    TAG_MQTT     = 65,
    TAG_MQTT_PUB = 66,
    TAG_MQTT_RCV = 67,

    TAG_LVGL = 90,
    TAG_LVFS = 91,
    TAG_FONT = 92
};

//#define TERM_COLOR_Black "\u001b[30m"
#define TERM_COLOR_GRAY "\e[37m"
#define TERM_COLOR_RED "\e[91m"
#define TERM_COLOR_GREEN "\e[92m"
#define TERM_COLOR_ORANGE "\e[38;5;214m"
#define TERM_COLOR_YELLOW "\e[93m"
#define TERM_COLOR_BLUE "\e[94m"
#define TERM_COLOR_MAGENTA "\e[35m"
#define TERM_COLOR_CYAN "\e[96m"
#define TERM_COLOR_WHITE "\e[97m"
#define TERM_COLOR_RESET "\e[0m"
#define TERM_CLEAR_LINE "\e[1000D\e[0K"

#endif
