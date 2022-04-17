#include "sdk_config.h"
#include "custom_board.h"
#include "nrfx_rtc.h"
#include "nrfx_clock.h"
#include "nrf_gzll.h"
#include "nrf_gpio.h"


/*****************************************************************************/
/** Configuration */
/*****************************************************************************/

const nrfx_rtc_t rtc_maint = NRFX_RTC_INSTANCE(0); /**< Declaring an instance of nrfx_rtc for RTC0. */
const nrfx_rtc_t rtc_deb = NRFX_RTC_INSTANCE(1); /**< Declaring an instance of nrfx_rtc for RTC1. */


// Define payload length
#define TX_PAYLOAD_LENGTH 4 ///< 3 byte payload length when transmitting

// Data and acknowledgement payloads
static uint8_t data_payload[TX_PAYLOAD_LENGTH];                ///< Payload to send to Host.
static uint8_t ack_payload[NRF_GZLL_CONST_MAX_PAYLOAD_LENGTH]; ///< Placeholder for received ACK payloads from Host.

// Debounce time (dependent on tick frequency)
#define DEBOUNCE 5
#define ACTIVITY 500

// Key buffers
static uint32_t keys, keys_snapshot;
static uint32_t debounce_ticks, activity_ticks;
static volatile bool debouncing = false;

void clock_event_handler(nrfx_clock_evt_type_t event)
{}

// Setup switch pins with pullups
static void gpio_config(void)
{
    nrf_gpio_cfg_sense_input(S00, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S01, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S02, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S03, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S04, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S05, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);

    nrf_gpio_cfg_sense_input(S10, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S11, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S12, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S13, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S14, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S15, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);

    nrf_gpio_cfg_sense_input(S20, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S21, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S22, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S23, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S24, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S25, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);

    nrf_gpio_cfg_sense_input(S30, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S31, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S32, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S33, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S34, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S35, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);

    nrf_gpio_cfg_sense_input(S40, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S41, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S42, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S43, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S44, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    nrf_gpio_cfg_sense_input(S45, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);

    nrf_gpio_cfg_sense_input(S50, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
}

// Return the key states, masked with valid key pins
static uint32_t read_keys(void)
{
    return (nrf_gpio_pin_read(S00) ? 0:1) << 31 |
           (nrf_gpio_pin_read(S01) ? 0:1) << 30 |
           (nrf_gpio_pin_read(S02) ? 0:1) << 29 |
           (nrf_gpio_pin_read(S03) ? 0:1) << 28 |
           (nrf_gpio_pin_read(S04) ? 0:1) << 27 |
           (nrf_gpio_pin_read(S05) ? 0:1) << 26 |
           (nrf_gpio_pin_read(S10) ? 0:1) << 25 |
           (nrf_gpio_pin_read(S11) ? 0:1) << 24 |
           (nrf_gpio_pin_read(S12) ? 0:1) << 23 |
           (nrf_gpio_pin_read(S13) ? 0:1) << 22 |
           (nrf_gpio_pin_read(S14) ? 0:1) << 21 |
           (nrf_gpio_pin_read(S15) ? 0:1) << 20 |
           (nrf_gpio_pin_read(S20) ? 0:1) << 19 |
           (nrf_gpio_pin_read(S21) ? 0:1) << 18 |
           (nrf_gpio_pin_read(S22) ? 0:1) << 17 |
           (nrf_gpio_pin_read(S23) ? 0:1) << 16 |
           (nrf_gpio_pin_read(S24) ? 0:1) << 15 |
           (nrf_gpio_pin_read(S25) ? 0:1) << 14 |
           (nrf_gpio_pin_read(S30) ? 0:1) << 13 |
           (nrf_gpio_pin_read(S31) ? 0:1) << 12 |
           (nrf_gpio_pin_read(S32) ? 0:1) << 11 |
           (nrf_gpio_pin_read(S33) ? 0:1) << 10 |
           (nrf_gpio_pin_read(S34) ? 0:1) << 9 |
           (nrf_gpio_pin_read(S35) ? 0:1) << 8 |
           (nrf_gpio_pin_read(S40) ? 0:1) << 7 |
           (nrf_gpio_pin_read(S41) ? 0:1) << 6 |
           (nrf_gpio_pin_read(S42) ? 0:1) << 5 |
           (nrf_gpio_pin_read(S43) ? 0:1) << 4 |
           (nrf_gpio_pin_read(S44) ? 0:1) << 3 |
           (nrf_gpio_pin_read(S45) ? 0:1) << 2 |
           (nrf_gpio_pin_read(S50) ? 0:1) << 1 |
           0 << 0;
}

// Assemble packet and send to receiver
static void send_data(void)
{
    data_payload[0] = (keys >> 24) & 0xff;
    data_payload[1] = (keys >> 16) & 0xff;
    data_payload[2] = (keys >> 8) & 0xff;
    data_payload[3] = (keys >> 0) & 0xff;

    nrf_gzll_add_packet_to_tx_fifo(PIPE_NUMBER, data_payload, TX_PAYLOAD_LENGTH);
}

// 8Hz held key maintenance, keeping the reciever keystates valid
static void handler_maintenance(nrfx_rtc_int_type_t int_type)
{
    send_data();
}

// 1000Hz debounce sampling
static void handler_debounce(nrfx_rtc_int_type_t int_type)
{
    // debouncing, waits until there have been no transitions in 5ms (assuming five 1ms ticks)
    if (debouncing)
    {
        // if debouncing, check if current keystates equal to the snapshot
        if (keys_snapshot == read_keys())
        {
            // DEBOUNCE ticks of stable sampling needed before sending data
            debounce_ticks++;
            if (debounce_ticks == DEBOUNCE)
            {
                keys = keys_snapshot;
                send_data();
            }
        }
        else
        {
            // if keys change, start period again
            debouncing = false;
        }
    }
    else
    {
        // if the keystate is different from the last data
        // sent to the receiver, start debouncing
        if (keys != read_keys())
        {
            keys_snapshot = read_keys();
            debouncing = true;
            debounce_ticks = 0;
        }
    }

    // looking for 500 ticks of no keys pressed, to go back to deep sleep
    if (read_keys() == 0)
    {
        activity_ticks++;
        if (activity_ticks > ACTIVITY)
        {
            nrfx_rtc_disable(&rtc_maint);
            nrfx_rtc_disable(&rtc_deb);
        }
    }
    else
    {
        activity_ticks = 0;
    }

}


// RTC peripheral configuration
static void rtc_config(void)
{

    nrfx_rtc_config_t rtc_maint_config = NRFX_RTC_DEFAULT_CONFIG;
    nrfx_rtc_config_t rtc_deb_config = NRFX_RTC_DEFAULT_CONFIG;

    rtc_maint_config.prescaler = RTC_FREQ_TO_PRESCALER(8);
    rtc_deb_config.prescaler = RTC_FREQ_TO_PRESCALER(1000);

    //Initialize RTC instance
    nrfx_rtc_init(&rtc_maint, &rtc_maint_config, handler_maintenance);
    nrfx_rtc_init(&rtc_deb, &rtc_deb_config, handler_debounce);

    //Enable tick event & interrupt
    nrfx_rtc_tick_enable(&rtc_maint, true);
    nrfx_rtc_tick_enable(&rtc_deb, true);
}

int main()
{
    nrfx_clock_init(clock_event_handler);
    nrfx_clock_enable();

    // Configure 16MHz xtal oscillator
    nrfx_clock_hfclk_start();
    // while (!nrfx_clock_hfclk_is_running())
    //     ;

    // Configure 32kHz xtal oscillator
    // nrfx_clock_lfclk_start();
    // while (!nrfx_clock_lfclk_is_running())
    //     ;

    // Initialize Gazell
    nrf_gzll_init(NRF_GZLL_MODE_DEVICE);

    // Attempt sending every packet up to 100 times
    nrf_gzll_set_max_tx_attempts(100);

    // Addressing
    nrf_gzll_set_base_address_0(0x01020304);
    nrf_gzll_set_base_address_1(0x05060708);

    // Enable Gazell to start sending over the air
    nrf_gzll_enable();

    keys = 1<<11;
    send_data();

    // Configure RTC peripherals with ticks
    rtc_config();

    // Configure all keys as inputs with pullups
    gpio_config();

    // Set the GPIOTE PORT event as interrupt source, and enable interrupts for GPIOTE
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_PORT_Msk;
    NVIC_EnableIRQ(GPIOTE_IRQn);


    // Main loop, constantly sleep, waiting for RTC and gpio IRQs
    while(1)
    {
        __SEV();
        __WFE();
        __WFE();
    }
}

// This handler will be run after wakeup from system ON (GPIO wakeup)
void GPIOTE_IRQHandler(void)
{
    if(NRF_GPIOTE->EVENTS_PORT)
    {
        //clear wakeup event
        NRF_GPIOTE->EVENTS_PORT = 0;

        //enable rtc interupt triggers
        nrfx_rtc_enable(&rtc_maint);
        nrfx_rtc_enable(&rtc_deb);

        debouncing = false;
        debounce_ticks = 0;
        activity_ticks = 0;
    }
}



/*****************************************************************************/
/** Gazell callback function definitions  */
/*****************************************************************************/

void  nrf_gzll_device_tx_success(uint32_t pipe, nrf_gzll_device_tx_info_t tx_info)
{
    uint32_t ack_payload_length = NRF_GZLL_CONST_MAX_PAYLOAD_LENGTH;

    if (tx_info.payload_received_in_ack)
    {
        // Pop packet and write first byte of the payload to the GPIO port.
        nrf_gzll_fetch_packet_from_rx_fifo(pipe, ack_payload, &ack_payload_length);
    }
}

// no action is taken when a packet fails to send, this might need to change
void nrf_gzll_device_tx_failed(uint32_t pipe, nrf_gzll_device_tx_info_t tx_info)
{

}

// Callbacks not needed
void nrf_gzll_host_rx_data_ready(uint32_t pipe, nrf_gzll_host_rx_info_t rx_info)
{}
void nrf_gzll_disabled()
{}
