/* MIT License - Copyright (c) 2019-2021 Francis Van Roie
   For full license information read the LICENSE file in the project folder */

#ifndef HASP_DISPATCH_H
#define HASP_DISPATCH_H

#include "ArduinoJson.h"
#include "lvgl.h"

struct dispatch_conf_t
{
    uint16_t teleperiod;
};

enum hasp_event_t { // even = released, odd = pressed
    HASP_EVENT_OFF     = 0,
    HASP_EVENT_ON      = 1,
    HASP_EVENT_UP      = 2,
    HASP_EVENT_DOWN    = 3,
    HASP_EVENT_RELEASE = 4,
    HASP_EVENT_HOLD    = 5,
    HASP_EVENT_LONG    = 6,
    HASP_EVENT_LOST    = 7,
    HASP_EVENT_DOUBLE  = 8,

    HASP_EVENT_CHANGED = 32
};

/* ===== Default Event Processors ===== */
void dispatchSetup(void);
void dispatchLoop(void);
void dispatchEverySecond(void);
void dispatchStart(void);
void dispatchStop(void);

/* ===== Special Event Processors ===== */
void dispatch_topic_payload(const char* topic, const char* payload);
void dispatch_text_line(const char* cmnd);

#ifdef ARDUINO
void dispatch_parse_jsonl(Stream& stream);
#else
void dispatch_parse_jsonl(std::istream& stream);
#endif

void dispatch_clear_page(const char* page);
void dispatch_json_error(uint8_t tag, DeserializationError& jsonError);

// void dispatch_set_page(uint8_t pageid);
void dispatch_set_page(uint8_t pageid, lv_scr_load_anim_t effectid);
void dispatch_page_next(lv_scr_load_anim_t effectid);
void dispatch_page_prev(lv_scr_load_anim_t effectid);
void dispatch_page_back(lv_scr_load_anim_t effectid);

void dispatch_dim(const char* level);
void dispatch_backlight(const char*, const char* payload);

void dispatch_web_update(const char*, const char* espOtaUrl);
void dispatch_reboot(bool saveConfig);

void dispatch_output_idle_state(uint8_t state);
void dispatch_output_statusupdate(const char*, const char*);
void dispatch_current_state();
void dispatch_output_current_page();

void dispatch_gpio_input_event(uint8_t pin, uint8_t group, uint8_t eventid);

void dispatch_object_value_changed(lv_obj_t* obj, int16_t state);

void dispatch_normalized_group_value(uint8_t groupid, lv_obj_t* obj, int16_t val, int16_t min, int16_t max);

void dispatch_state_subtopic(const char* subtopic, const char* payload);

void dispatch_config(const char* topic, const char* payload);

/* ===== Getter and Setter Functions ===== */

/* ===== Read/Write Configuration ===== */

/* ===== Structs and Constants ===== */
struct haspCommand_t
{
    const char* p_cmdstr;
    void (*func)(const char*, const char*);
};

#endif