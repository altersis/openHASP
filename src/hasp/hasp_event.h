/* MIT License - Copyright (c) 2019-2021 Francis Van Roie
   For full license information read the LICENSE file in the project folder */

#ifndef HASP_EVENT_H
#define HASP_EVENT_H

#include "lvgl.h"
#include "hasp_conf.h"

#define HASP_NUM_PAGE_PREV (HASP_NUM_PAGES + 1)
#define HASP_NUM_PAGE_BACK (HASP_NUM_PAGES + 2)
#define HASP_NUM_PAGE_NEXT (HASP_NUM_PAGES + 3)

void wakeup_event_handler(lv_obj_t* obj, lv_event_t event);
void generic_event_handler(lv_obj_t* obj, lv_event_t event);
void toggle_event_handler(lv_obj_t* obj, lv_event_t event);
void slider_event_handler(lv_obj_t* obj, lv_event_t event);
void selector_event_handler(lv_obj_t* obj, lv_event_t event);
void btnmatrix_event_handler(lv_obj_t* obj, lv_event_t event);
void cpicker_event_handler(lv_obj_t* obj, lv_event_t event);
void deleted_event_handler(lv_obj_t* obj, lv_event_t event);

#if HASP_USE_GPIO > 0
void event_gpio_input(uint8_t pin, uint8_t group, uint8_t eventid);
#endif

#endif // HASP_EVENT_H