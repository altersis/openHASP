/* MIT License - Copyright (c) 2020 Francis Van Roie
   For full license information read the LICENSE file in the project folder */

#ifndef HASP_DRV_STMPE610_H
#define HASP_DRV_STMPE610_H

#if TOUCH_DRIVER == 610

    #include "hasp_debug.h" // for TAG_DRVR

bool IRAM_ATTR STMPE610_getXY(int16_t * touchX, int16_t * touchY, uint8_t touchRotation, bool debug);
void STMPE610_init();

#endif
#endif