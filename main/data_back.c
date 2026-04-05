/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "data_back.h"
#include "sdkconfig.h"
#include "tinyusb.h"

#ifndef CONFIG_UART_ENABLE
#define CONFIG_UART_ENABLE 0
#endif

#if CFG_TUD_CDC
#include "tusb_cdc_acm.h"
#define ITF_NUM_CDC   0
#elif CONFIG_UART_ENABLE
#include "driver/uart.h"
#define UART_NUM    (CONFIG_UART_PORT_NUM)
#endif

void esp_data_back(void* data_buf, size_t length, bool flush)
{
#if CFG_TUD_CDC
    tinyusb_cdcacm_write_queue(ITF_NUM_CDC, (uint8_t*)data_buf, length);
    if (flush) {
        tinyusb_cdcacm_write_flush(ITF_NUM_CDC, 0);
    }
#elif CONFIG_UART_ENABLE
    uart_write_bytes(UART_NUM, (char*)data_buf, length);
#endif /* CFG_TUD_CDC */
}
