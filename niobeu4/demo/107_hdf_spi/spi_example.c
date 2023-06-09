/*
 * Copyright (c) 2022 Hunan OpenValley Digital Industry Development Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include "stdint.h"
#include "los_task.h"
#include "ohos_run.h"
#include "st7735.h"

#define PIC_WIDTH    (56)
#define PIC_HEIGH    (48)
#define PIC_SIZE     (336)
#define PIC_PAGE_NUM (10)
#define PIC_START_X  (40)
#define PIC_START_Y  (40)
#define PIC_SPEED    (100)

static const uint8_t taikongren[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xBD, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x20, 0xC3, 0x04, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x30, 0x10, 0x00, 0x00, 0x00, 0x00, 0x04, 0xFF, 0x21, 0x00, 0x00, 0x00, 0x00, 0x84, 0xFF,
    0x07, 0x00, 0x00, 0x00, 0x20, 0xC2, 0xFF, 0x4F, 0x00, 0x00, 0x00, 0x00, 0xE2, 0xFF, 0x5F, 0x00,
    0x00, 0x00, 0x10, 0xE0, 0xFF, 0x1F, 0x00, 0x01, 0x00, 0x10, 0xF0, 0xFF, 0x9F, 0x00, 0x00, 0x00,
    0x10, 0xF1, 0xFF, 0xBF, 0x00, 0x00, 0x00, 0x00, 0xF1, 0xFF, 0xBF, 0x00, 0x00, 0x00, 0x00, 0xF1,
    0xFF, 0xBF, 0x00, 0x20, 0x00, 0x00, 0xF1, 0xFF, 0xBF, 0x00, 0x00, 0x00, 0x10, 0xF0, 0xFF, 0x3F,
    0x00, 0x00, 0x00, 0x00, 0xF2, 0xFF, 0x7F, 0x00, 0x00, 0x08, 0x20, 0xE2, 0xFF, 0x7F, 0x01, 0x00,
    0x00, 0x00, 0xE4, 0xFF, 0x3F, 0x02, 0x00, 0x00, 0xC0, 0xC0, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00,
    0x89, 0xFF, 0x1F, 0x21, 0x00, 0x00, 0x00, 0x30, 0xFF, 0x0F, 0x02, 0x01, 0x00, 0x00, 0x42, 0xFC,
    0x03, 0x4C, 0x02, 0x00, 0x00, 0x84, 0xCB, 0x01, 0x50, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x20,
    0x05, 0x00, 0x00, 0x08, 0x30, 0x00, 0x2E, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x50, 0x09, 0x00,
    0x14, 0x00, 0x30, 0x00, 0x40, 0x10, 0x00, 0x00, 0x20, 0x00, 0x00, 0x52, 0x00, 0x00, 0x10, 0x00,
    0x00, 0x31, 0xA0, 0x20, 0x20, 0x00, 0x00, 0x40, 0x4A, 0x90, 0x00, 0x40, 0x00, 0x00, 0x40, 0x48,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x05,
    0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x05, 0x90, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x10, 0xCF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x42, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x20, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x43, 0x00, 0x00,
    0x00, 0x00, 0xE0, 0x03, 0x84, 0x40, 0x00, 0x00, 0x00, 0x70, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
    0x28, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xC2, 0x3F, 0x40, 0x00, 0x00, 0x00, 0x00, 0xF2, 0x7F, 0x40, 0x00,
    0x00, 0x00, 0x00, 0xF8, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0x81, 0x00, 0x05, 0x00,
    0x00, 0xFD, 0xFF, 0x83, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x83, 0x00, 0x02, 0x00, 0x00, 0xFF,
    0xFF, 0x87, 0x00, 0x80, 0x00, 0x00, 0xFE, 0xFF, 0x87, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x67,
    0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x67, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xC7, 0x00, 0x00,
    0x00, 0x00, 0xFC, 0xFF, 0x27, 0x02, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x13, 0x0C, 0x00, 0x00, 0x00,
    0xF8, 0xFF, 0x13, 0x20, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0x89, 0x40, 0x00, 0x00, 0x00, 0xC0, 0xFF,
    0x03, 0x82, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x20,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x00, 0x10, 0x40, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0xC0, 0x80, 0x62, 0x10, 0x00, 0x00, 0x20, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x22, 0x20, 0x00, 0x00, 0x40, 0x80, 0x00, 0x91, 0x40, 0x00, 0x00, 0x80, 0x00, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x88, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x02, 0x3A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x24, 0x8C, 0x02, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x30, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x22, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xAF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x20, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x43, 0x00, 0x00,
    0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00,
    0x18, 0x00, 0x10, 0x01, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x20, 0x02, 0x20, 0x00, 0x00, 0x0C, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x40, 0x0C, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40, 0x00,
    0x00, 0x00, 0x00, 0xF8, 0x03, 0x00, 0x10, 0x00, 0x00, 0x00, 0xFE, 0x07, 0x80, 0x00, 0x08, 0x00,
    0x00, 0xFF, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0xFF,
    0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x40, 0x00, 0x00,
    0x00, 0x00, 0xFC, 0xFF, 0x60, 0x00, 0xA0, 0x00, 0x00, 0xF8, 0xFF, 0x10, 0x01, 0x00, 0x00, 0x00,
    0xF8, 0xFF, 0x10, 0x0C, 0x40, 0x00, 0x00, 0xF0, 0x7F, 0x0C, 0x10, 0x00, 0x20, 0x00, 0xC0, 0x7F,
    0x02, 0x20, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x81, 0x40, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0xA1,
    0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x8C, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0x60, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC3,
    0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x01,
    0x03, 0x00, 0x00, 0x00, 0x5C, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x20, 0x8C, 0x02, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x08, 0x40, 0x2C, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xAF, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x20, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x1C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x10, 0x01, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x20, 0x02, 0x00, 0x00, 0x00, 0x0C, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x40, 0x0C, 0x00, 0x00, 0x00, 0x06, 0x00, 0x40, 0x10,
    0x30, 0x00, 0x00, 0x04, 0x00, 0xA0, 0x00, 0x10, 0x00, 0x00, 0x18, 0x00, 0xA0, 0x20, 0x00, 0x00,
    0x00, 0xFF, 0x01, 0x80, 0x40, 0x00, 0x00, 0x00, 0xFF, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xFF,
    0x07, 0x80, 0x80, 0x00, 0x00, 0x00, 0xFF, 0x0F, 0x80, 0x00, 0x00, 0x00, 0x10, 0xFE, 0x0F, 0x00,
    0x00, 0x01, 0x00, 0x10, 0xFE, 0x3F, 0xC0, 0x03, 0x02, 0x00, 0x00, 0xFE, 0x3F, 0x40, 0x0C, 0x00,
    0x00, 0x20, 0xFC, 0x3F, 0x60, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x3F, 0x10, 0x10, 0x00, 0x00, 0xC0,
    0xF8, 0x3F, 0xD0, 0x20, 0x00, 0x08, 0x00, 0xF0, 0x3F, 0x8C, 0x41, 0x00, 0x08, 0x00, 0xC1, 0x3F,
    0x02, 0x03, 0x00, 0x00, 0x00, 0x82, 0xFF, 0x01, 0x82, 0x00, 0x00, 0x00, 0x00, 0x80, 0x20, 0x0E,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x1C, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x9C, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x80, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x41, 0x00, 0x20, 0x00, 0x00,
    0x00, 0x31, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4A,
    0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xC0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x20, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x0C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x30,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x03, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x20, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x43, 0x00, 0x00,
    0x00, 0x00, 0x60, 0x00, 0x04, 0x40, 0x00, 0x00, 0x00, 0x10, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
    0x50, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x06, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x80, 0x00, 0x00, 0x04,
    0x00, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07,
    0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x40, 0x00, 0x00,
    0x00, 0x00, 0xFC, 0x00, 0x60, 0x02, 0x00, 0x00, 0x00, 0xF8, 0x01, 0x20, 0x0C, 0x00, 0x00, 0x00,
    0xF0, 0x01, 0x10, 0x00, 0x00, 0x30, 0x00, 0xF0, 0x01, 0x08, 0x10, 0x00, 0x00, 0x00, 0xC0, 0x01,
    0x06, 0x20, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x0D, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0C, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x80, 0x18, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x31, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x61, 0x40, 0x00, 0x03, 0x00, 0x10, 0x00, 0x63, 0x20, 0x00, 0x00, 0x00, 0x20,
    0x00, 0xC3, 0x30, 0x00, 0x04, 0x20, 0x01, 0x00, 0x44, 0x4F, 0x00, 0x00, 0x00, 0x41, 0x00, 0x9E,
    0x50, 0x00, 0x00, 0xC0, 0x80, 0x00, 0x1C, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x18, 0x20, 0x00,
    0x00, 0x00, 0x00, 0x01, 0xF0, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xE0, 0x02, 0x00, 0x00,
    0x00, 0x02, 0x80, 0x60, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x13, 0x03, 0x00, 0x00, 0x08, 0x00,
    0x00, 0x0C, 0x01, 0x00, 0x00, 0x10, 0x08, 0x00, 0x80, 0x00, 0x00, 0x00, 0x10, 0x30, 0x00, 0x2C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x20, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x81, 0x43, 0x00, 0x00,
    0x00, 0x00, 0x60, 0x00, 0x86, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x8B, 0x00, 0x14, 0x00, 0x00,
    0x08, 0x00, 0x14, 0x01, 0x04, 0x00, 0x00, 0x0C, 0x00, 0x28, 0x02, 0x14, 0x00, 0x00, 0x0C, 0x00,
    0x30, 0x02, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x40, 0x0C, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x80, 0x00, 0x08, 0x00,
    0x00, 0x01, 0x00, 0x80, 0x00, 0x08, 0x00, 0x00, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0xC0, 0x01, 0x20,
    0x00, 0x00, 0x04, 0x00, 0x60, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x90, 0x10, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x8C, 0x21, 0x00, 0x00, 0x00, 0x30, 0x00, 0x02, 0x43, 0x00, 0x00, 0x00, 0x60, 0x00,
    0x01, 0xCE, 0x00, 0x00, 0x00, 0x80, 0xCB, 0x00, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x3C,
    0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x30, 0x01, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x70, 0x01, 0x00,
    0x00, 0x00, 0x30, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x30, 0x03, 0x50, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0xAC, 0x00, 0x00, 0x00, 0x00, 0x40, 0x06, 0x91, 0x00, 0x00, 0x00, 0x00, 0x40, 0x8A,
    0x00, 0x00, 0x00, 0x10, 0x00, 0x80, 0x4E, 0x00, 0x00, 0x10, 0x00, 0x00, 0x80, 0x10, 0x00, 0x01,
    0x20, 0x00, 0x00, 0x01, 0x78, 0x10, 0x01, 0x00, 0x00, 0x00, 0x02, 0x2D, 0x90, 0x01, 0x00, 0x00,
    0x00, 0x02, 0x40, 0x70, 0x24, 0x00, 0x00, 0x10, 0x04, 0x80, 0x70, 0x02, 0x00, 0x00, 0x28, 0x08,
    0x00, 0xCF, 0x01, 0x00, 0x00, 0x08, 0x08, 0x00, 0x42, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x22,
    0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x1C, 0x00, 0x00, 0x00, 0xC0, 0x89, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x20, 0x30, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x80, 0x0F, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x04, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
    0x7F, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x7F, 0x0C, 0x00, 0x00, 0x00, 0x02, 0x00, 0x7F, 0x10,
    0x00, 0x00, 0x00, 0x02, 0x00, 0xFE, 0xC0, 0x10, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x20, 0x10, 0x00,
    0x00, 0x01, 0x00, 0xFC, 0x40, 0x00, 0x00, 0x00, 0x01, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0xF0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
    0x00, 0x01, 0x04, 0x00, 0x0A, 0x00, 0x40, 0x00, 0x02, 0x00, 0x00, 0x0C, 0x00, 0x40, 0x00, 0x00,
    0x00, 0x00, 0x14, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x28, 0x00, 0x60, 0x00, 0x08, 0x00, 0x00,
    0x08, 0x00, 0x10, 0x01, 0x00, 0x00, 0x00, 0x30, 0x00, 0x08, 0x02, 0x00, 0x00, 0x00, 0xC0, 0x00,
    0x46, 0x0C, 0x00, 0x08, 0x00, 0x00, 0xCF, 0x0B, 0x10, 0x00, 0x00, 0x00, 0x00, 0x70, 0x80, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x30, 0x14, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x22, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x4D, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xD0, 0x10, 0x00, 0x00, 0x00, 0x00, 0x40, 0xA0, 0x50, 0x04, 0x00, 0x00, 0x00, 0x80, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x30, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4A, 0x82, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x6C, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x02, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x1E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x8F, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x20, 0xC3, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0xC0, 0x0F, 0x0C, 0x00, 0x00, 0x00,
    0x08, 0xF0, 0x1F, 0x0C, 0x00, 0x00, 0x00, 0x04, 0xF0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x04, 0xF0,
    0x3F, 0x00, 0x00, 0x00, 0x00, 0x02, 0xF0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x02, 0xF0, 0x7F, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF0, 0x7F, 0x00, 0x08, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0x00, 0x04, 0x00,
    0x00, 0x01, 0xC0, 0xFF, 0x00, 0x08, 0x00, 0x00, 0x01, 0xC0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x7E,
    0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x78, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x40, 0x00, 0x00,
    0x00, 0x20, 0x04, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x08, 0x00, 0x60, 0x00, 0x28, 0x00, 0xC0,
    0x48, 0x00, 0x10, 0x01, 0x20, 0x10, 0x00, 0xD0, 0x00, 0x0C, 0x02, 0x10, 0x00, 0x00, 0x41, 0x01,
    0x02, 0x0C, 0x20, 0x00, 0x00, 0x82, 0xC7, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00,
    0x40, 0x00, 0x04, 0x00, 0x08, 0x01, 0x22, 0x80, 0x00, 0x00, 0x00, 0x84, 0x11, 0x21, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x23, 0x11, 0x00, 0x03, 0x04, 0x00, 0x08, 0x02, 0x01, 0x00, 0x04, 0x00, 0x00,
    0x30, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC4, 0x40, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1C,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x10, 0x01, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x80, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x20, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x81, 0x43, 0x00, 0x00,
    0x00, 0x00, 0xE0, 0xC1, 0x87, 0x00, 0x00, 0x00, 0x00, 0x70, 0xF8, 0x0F, 0x00, 0x00, 0x00, 0x00,
    0x38, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x14, 0xFE, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x04, 0xFE,
    0x3F, 0x20, 0x00, 0x00, 0x00, 0x02, 0xFE, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x02, 0xFF, 0x7F, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01,
    0xFE, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x7F,
    0x00, 0x04, 0x00, 0x00, 0x02, 0xFC, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x02, 0xF8, 0x7F, 0x00, 0x00,
    0x00, 0x00, 0x04, 0xF0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x01, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x10, 0x0D, 0x00, 0x04, 0x00, 0x30, 0x00, 0x0C, 0x12, 0x00, 0x08, 0x00, 0x40, 0x06,
    0x02, 0x2C, 0x00, 0x08, 0x00, 0x00, 0xCF, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x30,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0xB0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x82, 0x41, 0x00, 0x00, 0x00, 0x10, 0x00, 0x42, 0x40, 0x02, 0x00, 0x00, 0x20,
    0x40, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x91, 0x00, 0x00, 0x00, 0x40, 0x00, 0x04,
    0x00, 0x00, 0x40, 0x00, 0x80, 0x80, 0x0A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x30, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x29, 0xE0, 0x02, 0x00, 0x00,
    0x00, 0x02, 0x00, 0x60, 0x02, 0x80, 0x00, 0x00, 0x04, 0x40, 0x50, 0x01, 0x00, 0x00, 0x10, 0x00,
    0x00, 0x8D, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x22,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x20, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0x10, 0xF8, 0x0F, 0x00, 0x00, 0x00, 0x00,
    0x38, 0xFC, 0x1F, 0x81, 0x01, 0x00, 0x00, 0x1C, 0xFE, 0x3F, 0x82, 0x00, 0x00, 0x00, 0x0C, 0xFF,
    0x3F, 0x00, 0x00, 0x00, 0x00, 0x86, 0xFF, 0x7F, 0x0C, 0x00, 0x00, 0x00, 0x86, 0xFF, 0x7F, 0x10,
    0x00, 0x00, 0x00, 0xC4, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x20, 0x00, 0x00,
    0x00, 0xC1, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0xC1, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xC1,
    0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x00, 0x04, 0x00, 0x00, 0x80, 0xFF, 0x7F,
    0x00, 0x00, 0x00, 0x00, 0x82, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x02, 0xFF, 0x7F, 0x00, 0x00,
    0x00, 0x00, 0x04, 0xFF, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x1F, 0x02, 0x00, 0x00, 0x00,
    0x08, 0xF8, 0x1F, 0x0D, 0x00, 0x00, 0x00, 0x30, 0x00, 0x0C, 0x12, 0x00, 0x00, 0x00, 0x40, 0x00,
    0x02, 0x2C, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x01, 0x40, 0x00, 0x03, 0x00, 0x00, 0x38, 0x00, 0x90,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xA0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x4C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x52, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x40, 0x14,
    0x80, 0x08, 0x00, 0x00, 0x00, 0x00, 0x22, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x08, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x90, 0x02, 0x00, 0x00,
    0x00, 0x02, 0x26, 0x60, 0x02, 0x00, 0x00, 0x00, 0x04, 0x40, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x4D, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x22,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00
};

void StartHdfSPITest(void)
{
    static uint8_t const color[] = {
        32, 48, 64, 80, 96, 112, 128, 144, 160, 176,
        208, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        208, 176, 160, 144, 128, 112, 96, 80, 64, 48
    };
    uint8_t offset = 0, n = 0, m = 1;
    LcdInit();
    while (1) {
        uint16_t t = 0;
        if (m & '\x1') {
            t = color[n] >> '\x3';
        }
        if (m & '\x2') {
            t |= ((uint16_t)(color[n] >> '\x2')) << '\x5';
        }
        if (m & '\x4') {
            t |= ((uint16_t)(color[n] >> '\x3')) << '\xb';
        }
        {
            const uint8_t *s = &taikongren[offset * PIC_SIZE];
            uint16_t fc = htons(t);
            uint16_t fb = BLACK;
            for (uint8_t y = PIC_START_Y; y < (PIC_HEIGH + PIC_START_Y); ++y) {
                for (uint8_t x = PIC_START_X; x < (PIC_START_X + PIC_WIDTH); ++s) {
                    lcd_draw_point(x++, y, (*s & '\x1') ? fc : fb);
                    lcd_draw_point(x++, y, (*s & '\x2') ? fc : fb);
                    lcd_draw_point(x++, y, (*s & '\x4') ? fc : fb);
                    lcd_draw_point(x++, y, (*s & '\x8') ? fc : fb);
                    lcd_draw_point(x++, y, (*s & '\x10') ? fc : fb);
                    lcd_draw_point(x++, y, (*s & '\x20') ? fc : fb);
                    lcd_draw_point(x++, y, (*s & '\x40') ? fc : fb);
                    lcd_draw_point(x++, y, (*s & '\x80') ? fc : fb);
                }
            }
            LcdPush();
        }
        offset++;
        if (offset >= PIC_PAGE_NUM) {
            offset = 0;
        }
        LOS_Msleep(PIC_SPEED);
        if (++n >= (sizeof(color) / sizeof(color[0]))) {
            n = 0;
            if ((++m & '\x7') == 0) {
                m = 1;
            }
        }
    }
}

OHOS_APP_RUN(StartHdfSPITest);