/* Copyright (c) 2015 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

#ifndef SDK_CONFIG_H
#define SDK_CONFIG_H

// Peripheral Ressource Sharing seems to be needed.
#define NRFX_PRS_ENABLED 1
#define NRFX_PRS_BOX_4_ENABLED 1

/* POWER */
#define NRFX_POWER_ENABLED 1
#define NRFX_POWER_CONFIG_IRQ_PRIORITY 6

/* CLOCK */
#define NRFX_CLOCK_ENABLED 1
#define NRFX_CLOCK_CONFIG_LF_SRC 1
#define NRFX_CLOCK_CONFIG_IRQ_PRIORITY 6

/* RTC */
#define NRFX_RTC_ENABLED 1
#define NRFX_RTC0_ENABLED 1
#define NRFX_RTC1_ENABLED 1

#define NRFX_RTC_MAXIMUM_LATENCY_US 2000
#define NRFX_RTC_DEFAULT_CONFIG_FREQUENCY 32768
#define NRFX_RTC_DEFAULT_CONFIG_RELIABLE 0
#define NRFX_RTC_DEFAULT_CONFIG_IRQ_PRIORITY 6

#define NRF_LOG_ENABLED 0

#endif // SDK_CONFIG_H
