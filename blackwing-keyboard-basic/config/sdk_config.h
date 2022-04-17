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

/**
 * Provide a non-zero value here in applications that need to use several
 * peripherals with the same ID that are sharing certain resources
 * (for example, SPI0 and TWI0). Obviously, such peripherals cannot be used
 * simultaneously. Therefore, this definition allows to initialize the driver
 * for another peripheral from a given group only after the previously used one
 * is uninitialized. Normally, this is not possible, because interrupt handlers
 * are implemented in individual drivers.
 * This functionality requires a more complicated interrupt handling and driver
 * initialization, hence it is not always desirable to use it.
 */
#define PERIPHERAL_RESOURCE_SHARING_ENABLED  0

/* CLOCK */
#define NRFX_POWER_ENABLED 1
#define NRFX_POWER_CONFIG_IRQ_PRIORITY 7

/* CLOCK */
#define NRFX_CLOCK_ENABLED 1
#define NRFX_CLOCK_CONFIG_LF_SRC 1
#define NRFX_CLOCK_CONFIG_IRQ_PRIORITY 7

#define NRF_MAXIMUM_LATENCY_US 2000

/* UART */
#define UART_ENABLED 0
#define NRF_LOG_ENABLED 0


// #define RTC_ENABLED 1
// #define RTC0_ENABLED 1
// #define RTC1_ENABLED 1
#define NRFX_RTC_ENABLED 1
#define NRFX_RTC0_ENABLED 1
#define NRFX_RTC1_ENABLED 1

#define NRFX_RTC_MAXIMUM_LATENCY_US 2000
#define NRFX_RTC_DEFAULT_CONFIG_FREQUENCY 32768
#define NRFX_RTC_DEFAULT_CONFIG_IRQ_PRIORITY 7
#define NRFX_RTC_DEFAULT_CONFIG_RELIABLE 0

#endif // SDK_CONFIG_H
