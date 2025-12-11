#include <stdint.h>
#include <stdbool.h>
#include "power_manager.h"
#include "radio_interface.h"
#include "storage_manager.h"
#include "security_module.h"
#include "ledger_manager.h"
#include "input_buttons.h"
#include "timekeeping.h"

/*
===========================================================
 Seed Device – Main Loop
 ----------------------------------------------------------
 This module coordinates all subsystems:
  - Power management
  - Radio mesh send/receive
  - Ledger synchronization
  - User interactions (buttons, screen triggers)
  - Periodic background tasks
===========================================================
*/

#define MAIN_LOOP_TICK_MS 200          // How often the main loop runs
#define SYNC_INTERVAL_MS   5000        // How often to attempt ledger sync
#define HEARTBEAT_INTERVAL 10000       // Periodic mesh heartbeat
#define BUTTON_CHECK_MS      100       // Input polling interval

static uint32_t last_sync_time = 0;
static uint32_t last_heartbeat_time = 0;
static uint32_t last_button_poll = 0;

/* ---------------------------------------------------------
   Initialization
--------------------------------------------------------- */
static void system_init(void)
{
    power_manager_init();
    radio_init();
    storage_init();
    security_init();
    ledger_init();
    input_buttons_init();
    timekeeping_init();

    // Load ledger from encrypted flash
    ledger_load_from_storage();

    // Announce boot to mesh network
    radio_send_heartbeat();
}

/* ---------------------------------------------------------
   Handle incoming mesh packets
--------------------------------------------------------- */
static void handle_incoming_packets(void)
{
    mesh_packet_t packet;

    while (radio_receive(&packet))
    {
        switch (packet.type)
        {
            case PACKET_TRANSACTION:
                ledger_import_transaction(&packet.tx);
                break;

            case PACKET_LEDGER_SYNC:
                ledger_merge_remote(packet.ledger_blob, packet.ledger_length);
                break;

            case PACKET_HEARTBEAT:
                // Update neighbor table
                radio_update_neighbor(packet.src_id);
                break;

            default:
                // Unknown packet type; ignore safely
                break;
        }
    }
}

/* ---------------------------------------------------------
   Handle user interactions
--------------------------------------------------------- */
static void handle_user_input(void)
{
    button_event_t ev = input_buttons_read();

    if (ev == BUTTON_NONE) return;

    switch (ev)
    {
        case BUTTON_UP:
            // Example action: scroll interface or increase value
            break;

        case BUTTON_DOWN:
            // Example action
            break;

        case BUTTON_SELECT:
            // Example action: create a small-value test transaction
            ledger_create_transaction("LOCAL_USER", "DEMO_RECEIVER", 1);
            break;

        default:
            break;
    }
}

/* ---------------------------------------------------------
   Background sync behaviors
--------------------------------------------------------- */
static void periodic_tasks(uint32_t now)
{
    // Attempt ledger sync with neighbors
    if (now - last_sync_time >= SYNC_INTERVAL_MS)
    {
        uint8_t buffer[LEDGER_EXPORT_MAX];
        uint16_t length = ledger_export(buffer, sizeof(buffer));
        radio_broadcast_ledger(buffer, length);
        last_sync_time = now;
    }

    // Heartbeat message for neighbor discovery
    if (now - last_heartbeat_time >= HEARTBEAT_INTERVAL)
    {
        radio_send_heartbeat();
        last_heartbeat_time = now;
    }
}

/* ---------------------------------------------------------
   Main loop
--------------------------------------------------------- */
void main_loop(void)
{
    system_init();

    while (1)
    {
        uint32_t now = timekeeping_ms();

        // Power-aware sleep/wake behavior
        power_manager_tick();

        // Process mesh traffic
        handle_incoming_packets();

        // Button polling on interval
        if (now - last_button_poll >= BUTTON_CHECK_MS)
        {
            handle_user_input();
            last_button_poll = now;
        }

        // Background work
        periodic_tasks(now);

        // Save ledger state if changed
        if (ledger_has_pending_writes())
        {
            ledger_save_to_storage();
        }

        // Small sleep to reduce CPU load (device may deep-sleep)
        power_manager_delay(MAIN_LOOP_TICK_MS);
    }
}
