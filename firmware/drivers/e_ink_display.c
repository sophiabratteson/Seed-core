/**
 * @file e_ink_display.c
 * @brief Seed Device – E-Ink Display Driver (Low-Power UI System)
 *
 * This module controls the low-power e-ink screen used in the Seed hardware.
 * E-ink is chosen because:
 *   - It consumes power only when updating
 *   - It remains readable in full sunlight
 *   - It supports ultra-low-power standby operation
 *
 * Responsibilities of this module:
 *   - Initialize the e-ink controller and power rails
 *   - Draw text, icons, and UI elements
 *   - Push frame updates efficiently (partial + full refresh)
 *   - Manage deep-sleep mode and wake behavior
 *   - Interface cleanly with UI and application layers
 *
 * NOTE:
 * The functions here are hardware-agnostic. The actual SPI pins, power rails,
 * and controller timings are set inside e_ink_display.h / board_config.h.
 */

#include "e_ink_display.h"
#include "safe_memory.h"
#include "power_manager.h"
#include "radio_interface.h"   // optional, for notifications
#include <string.h>

/* -----------------------------------------------------------
 *  STATIC STATE + FRAME BUFFER
 * ----------------------------------------------------------- */

static uint8_t framebuffer[EPD_WIDTH * EPD_HEIGHT / 8];

/**
 * Track whether a full refresh is required.
 * Full refresh fixes “ghosting,” partial refresh updates only changed segments.
 */
static int needs_full_refresh = 1;

/* -----------------------------------------------------------
 *  HARDWARE-LEVEL OPERATIONS (SPI, GPIO, POWER RAILS)
 *  NOTE: These would be implemented for your specific board.
 * ----------------------------------------------------------- */

static void epd_reset(void);
static void epd_send_command(uint8_t cmd);
static void epd_send_data(const uint8_t *data, int len);
static void epd_wait_busy(void);
static void epd_power_on(void);
static void epd_power_off(void);

/* -----------------------------------------------------------
 *  PUBLIC INITIALIZATION
 * ----------------------------------------------------------- */

void e_ink_init(void)
{
    epd_power_on();
    epd_reset();

    // Example: send init commands for common EPD controllers
    epd_send_command(EPD_CMD_SW_RESET);
    epd_wait_busy();

    epd_send_command(EPD_CMD_SET_PANEL);
    uint8_t panel_cfg = 0x0F;  // example config
    epd_send_data(&panel_cfg, 1);

    memset(framebuffer, 0xFF, sizeof(framebuffer));  // screen = white
    needs_full_refresh = 1;
}

/* -----------------------------------------------------------
 *  FRAMEBUFFER OPERATIONS
 * ----------------------------------------------------------- */

/**
 * @brief Clear the entire display to white or black.
 */
void e_ink_clear(DisplayColor color)
{
    uint8_t fill = (color == DISPLAY_WHITE) ? 0xFF : 0x00;
    memset(framebuffer, fill, sizeof(framebuffer));
    needs_full_refresh = 1;
}

/**
 * @brief Draw a pixel inside the framebuffer.
 */
void e_ink_draw_pixel(int x, int y, DisplayColor color)
{
    if (x < 0 || y < 0 || x >= EPD_WIDTH || y >= EPD_HEIGHT) return;

    int index = (x + (y * EPD_WIDTH)) / 8;
    int bit   = x & 7;

    if (color == DISPLAY_BLACK)
        framebuffer[index] &= ~(1 << (7 - bit));
    else
        framebuffer[index] |=  (1 << (7 - bit));
}

/**
 * @brief Simple text rendering using 8×8 monochrome font.
 */
void e_ink_draw_text(int x, int y, const char *text, DisplayColor color)
{
    while (*text)
    {
        e_ink_draw_char(x, y, *text, color);
        x += 8;
        text++;
    }
}

/* -----------------------------------------------------------
 *  FULL + PARTIAL REFRESH LOGIC
 * ----------------------------------------------------------- */

void e_ink_update_full(void)
{
    epd_send_command(EPD_CMD_WRITE_FB);
    epd_send_data(framebuffer, sizeof(framebuffer));

    epd_send_command(EPD_CMD_DISPLAY_REFRESH);
    epd_wait_busy();

    needs_full_refresh = 0;
}

void e_ink_update_partial(int x, int y, int w, int h)
{
    if (needs_full_refresh)
    {
        e_ink_update_full();
        return;
    }

    // Hardware-specific partial refresh region commands
    epd_send_command(EPD_CMD_SET_PARTIAL_WINDOW);
    uint8_t region[4] = {x, y, w, h};
    epd_send_data(region, 4);

    epd_send_data(&framebuffer[(y * EPD_WIDTH + x) / 8], (w * h) / 8);
    epd_send_command(EPD_CMD_DISPLAY_REFRESH);
    epd_wait_busy();
}

/* -----------------------------------------------------------
 *  LOW-POWER MODES
 * ----------------------------------------------------------- */

void e_ink_sleep(void)
{
    epd_send_command(EPD_CMD_DEEP_SLEEP);
    uint8_t data = 0xA5;  // controller-specific sleep code
    epd_send_data(&data, 1);
    epd_power_off();
}

void e_ink_wake(void)
{
    epd_power_on();
    e_ink_init();
}

/* -----------------------------------------------------------
 *  STATUS + DEBUGGING
 * ----------------------------------------------------------- */

int e_ink_is_ready(void)
{
    // Some controllers have a BUSY pin; this abstracts it.
    return epd_busy_pin_read() == 0;
}

/* -----------------------------------------------------------
 *  OPTIONAL: UI SHORTCUTS
 * ----------------------------------------------------------- */

void e_ink_show_balance(float balance)
{
    char buf[32];
    snprintf(buf, sizeof(buf), "Balance: %.2f", balance);

    e_ink_clear(DISPLAY_WHITE);
    e_ink_draw_text(4, 20, buf, DISPLAY_BLACK);
    e_ink_update_full();
}

void e_ink_show_transfer_status(const char *status)
{
    e_ink_clear(DISPLAY_WHITE);
    e_ink_draw_text(4, 20, status, DISPLAY_BLACK);
    e_ink_update_partial(0, 0, EPD_WIDTH, 40);
}
