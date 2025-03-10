#ifndef HASP_CONF_H
#define HASP_CONF_H

#ifdef USE_CONFIG_OVERRIDE
#include "user_config_override.h"
#endif

// language specific defines
#include "lang/lang.h"

// TFT defines
#ifndef TFT_BACKLIGHT_ON
#define TFT_BACKLIGHT_ON HIGH
#endif

#ifndef TFT_BCKL
#define TFT_BCKL -1
#endif

#define HASP_USE_APP 1

#ifndef HASP_USE_DEBUG
#define HASP_USE_DEBUG 1
#endif

/* Network Services */
#ifndef HASP_USE_ETHERNET
#define HASP_USE_ETHERNET 0
#endif

#ifndef HASP_USE_WIFI
#define HASP_USE_WIFI (ARDUINO_ARCH_ESP32 > 0 || ARDUINO_ARCH_ESP8266 > 0 || HASP_USE_WIFI > 0)
#endif

#define HASP_HAS_NETWORK                                                                                               \
    (ARDUINO_ARCH_ESP32 > 0 || ARDUINO_ARCH_ESP8266 > 0 || HASP_USE_ETHERNET > 0 || HASP_USE_WIFI > 0)

#ifndef HASP_USE_OTA
#define HASP_USE_OTA (HASP_HAS_NETWORK)
#endif

#ifndef HASP_USE_MQTT
#define HASP_USE_MQTT (HASP_HAS_NETWORK)
#endif

#ifndef MQTT_NODENAME
#define MQTT_NODENAME "plate"
#endif

#ifndef HASP_USE_HTTP
#define HASP_USE_HTTP (HASP_HAS_NETWORK)
#endif

#ifndef HASP_USE_MDNS
#define HASP_USE_MDNS (HASP_HAS_NETWORK)
#endif

#ifndef HASP_USE_SYSLOG
#define HASP_USE_SYSLOG (HASP_HAS_NETWORK)
#endif

#ifndef HASP_USE_TELNET
#define HASP_USE_TELNET 0
#endif

/* Filesystem */
#define HASP_HAS_FILESYSTEM (ARDUINO_ARCH_ESP32 > 0 || ARDUINO_ARCH_ESP8266 > 0)

#ifndef HASP_USE_SPIFFS
#ifndef HASP_USE_LITTLEFS
#define HASP_USE_SPIFFS (HASP_HAS_FILESYSTEM)
#else
#define HASP_USE_SPIFFS (HASP_USE_LITTLEFS <= 0)
#endif
#endif

#ifndef HASP_USE_LITTLEFS
#define HASP_USE_LITTLEFS (HASP_USE_SPIFFS <= 0)
#endif

#ifndef HASP_USE_EEPROM
#define HASP_USE_EEPROM 1
#endif

#ifndef HASP_USE_SDCARD
#define HASP_USE_SDCARD 0
#endif

#ifndef HASP_USE_GPIO
#define HASP_USE_GPIO 1
#endif

#ifndef HASP_USE_QRCODE
#define HASP_USE_QRCODE 1
#endif

#ifndef HASP_USE_PNGDECODE
#define HASP_USE_PNGDECODE 0
#endif

#ifndef HASP_NUM_GPIO_CONFIG
#define HASP_NUM_GPIO_CONFIG 8
#endif

#ifndef HASP_NUM_INPUTS
#define HASP_NUM_INPUTS 4 // Number of ACE Buttons
#endif

// #ifndef HASP_NUM_OUTPUTS
// #define HASP_NUM_OUTPUTS 3
// #endif

#ifndef HASP_NUM_PAGES
#if defined(ARDUINO_ARCH_ESP8266)
#define HASP_NUM_PAGES 4
#else
#define HASP_NUM_PAGES 12
#endif
#endif

#define HASP_OBJECT_NOTATION "p%ub%u"

/* Includes */
#ifdef WINDOWS
#include "winsock2.h"
#include "Windows.h"
#elif defined(POSIX)
#else
#include "Arduino.h"
#endif

#if HASP_USE_SPIFFS > 0
// #if defined(ARDUINO_ARCH_ESP32)
// #include "SPIFFS.h"
// #endif
// #include <FS.h> // Include the SPIFFS library
#include "hasp_filesystem.h"
#endif

#if HASP_USE_LITTLEFS > 0
// #if defined(ARDUINO_ARCH_ESP32)
// #include "LITTLEFS.h"
// #elif defined(ARDUINO_ARCH_ESP8266)
// #include <FS.h> // Include the FS library
// #include <LittleFS.h>
// #endif
#include "hasp_filesystem.h"
#endif

#if HASP_USE_SPIFFS > 0 || HASP_USE_LITTLEFS > 0
#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
#include "lv_zifont.h"
#endif
#endif

#if HASP_USE_EEPROM > 0
#include "hasp_eeprom.h"
#endif

#if HASP_USE_WIFI > 0
#include "sys/net/hasp_wifi.h"

#if defined(STM32F4xx)
#include "WiFiSpi.h"
static WiFiSpiClass WiFi;
#endif
#endif // HASP_USE_WIFI

#if HASP_USE_ETHERNET > 0
#if defined(ARDUINO_ARCH_ESP32)
#include <ETH.h>

#define ETH_ADDR 0
#define ETH_POWER_PIN -1
#define ETH_MDC_PIN 23
#define ETH_MDIO_PIN 18
#define NRST 5
#define ETH_TYPE ETH_PHY_LAN8720
#define ETH_CLKMODE ETH_CLOCK_GPIO17_OUT

#include "sys/net/hasp_ethernet_esp32.h"
#warning Using ESP32 Ethernet LAN8720

#else
#if USE_BUILTIN_ETHERNET > 0
#include <LwIP.h>
#include <STM32Ethernet.h>
#warning Use built-in STM32 Ethernet
#elif USE_UIP_ETHERNET
#include <UIPEthernet.h>
#include <utility/logging.h>
#warning Use ENC28J60 Ethernet shield
#else
#include "Ethernet.h"
#warning Use W5x00 Ethernet shield
#endif
#include "sys/net/hasp_ethernet_stm32.h"
#endif
#endif

#if HASP_USE_MQTT > 0
#include "mqtt/hasp_mqtt.h"

#if defined(WINDOWS) || defined(POSIX)
#define USE_PAHO
#else
#define USE_PUBSUBCLIENT
#endif

#endif

#if HASP_USE_GPIO > 0
#include "sys/gpio/hasp_gpio.h"
#endif

#if HASP_USE_HTTP > 0
#include "sys/svc/hasp_http.h"
#endif

#if HASP_USE_TELNET > 0
#include "sys/svc/hasp_telnet.h"
#endif

#if HASP_USE_MDNS > 0
#include "sys/svc/hasp_mdns.h"
#endif

#if HASP_USE_OTA > 0
#include "sys/svc/hasp_ota.h"
#ifndef HASP_OTA_PORT
#if defined(ARDUINO_ARCH_ESP32)
#define HASP_OTA_PORT 3232
#elif defined(ARDUINO_ARCH_ESP8266)
#define HASP_OTA_PORT 8266
#endif
#endif
#endif

#if HASP_USE_TASMOTA_CLIENT > 0
#include "sys/svc/hasp_slave.h"
#endif

#ifndef FPSTR
#define FPSTR(pstr_pointer) (reinterpret_cast<const __FlashStringHelper*>(pstr_pointer))
#endif

#ifndef PGM_P
#define PGM_P const char*
#endif

#if defined(WINDOWS) || defined(POSIX)
#ifndef __FlashStringHelper
#define __FlashStringHelper char
#endif

#ifndef F
#define F(x) (x)
#endif

#ifndef PSTR
#define PSTR(x) x
#endif

#ifndef PROGMEM
#define PROGMEM
#endif
#endif

#if defined(WINDOWS)
#include <Windows.h>
#define delay Sleep
#endif
#if defined(POSIX)
#define delay SDL_Delay
#endif
#if defined(WINDOWS) || defined(POSIX)
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define snprintf_P snprintf
#define memcpy_P memcpy
#define strcasecmp_P strcasecmp
#define strcmp_P strcmp
#define strstr_P strstr
#define halRestartMcu()
#define millis SDL_GetTicks

#define DEC 10
#define HEX 16
#define BIN 2

#define guiGetDim() 255
#define guiSetDim(x)
#define guiGetBacklight() 1
#define guiSetBacklight(x)
//#define guiCalibrate()
#endif

#endif // HASP_CONF_H
