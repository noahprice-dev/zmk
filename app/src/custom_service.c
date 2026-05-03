/*
Custom GATT Service for display updates.
*/

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/logging/log.h>

#include <zmk/display/widgets/custom_status.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);


// * Service & Characteristic UUIDs
#define CUSTOM_SERVICE_UUID \
    BT_UUID_128_ENCODE(0x6926e787, 0x019b, 0x474a, 0xb3bd, 0x269aa8d5df7c)

#define CUSTOM_CHAR_UUID \
    BT_UUID_128_ENCODE(0x55d59635, 0xb8d6, 0x4dca, 0x8701, 0x4d9d2fd2d288)
    
static struct bt_uuid_128 custom_service_uuid = BT_UUID_INIT_128(CUSTOM_SERVICE_UUID);
static struct bt_uuid_128 custom_char_uuid = BT_UUID_INIT_128(CUSTOM_CHAR_UUID);

// Buffer to hold last received text

static char current_text[MAX_TEXT_LEN] = "Waiting...";


// Write Callback - When Server sends data
static ssize_t write_custom_char(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf, uint16_t len, uint16_t offset, uint8_t flags) {
    if (offset != 0) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
    }
    
    if (len >= MAX_TEXT_LEN) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }
    
    // Copy received bytes into our buffer and null terminate.
    memcpy(current_text, buf, len);
    current_text[len] = '\0'; // Terminate our message with a 0 (null) to let LVGL know we are done.
    
    LOG_DBG("Received Display update: %s", current_text);
    zmk_widget_custom_status_set_text(current_text);
    return len;
}

static int custom_service_init(void) {
    zmk_widget_custom_status_set_text("Waiting...");
    LOG_DBG("Custom Service init");
    return 0;
}

SYS_INIT(custom_service_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

// Service declaration
BT_GATT_SERVICE_DEFINE(
    custom_svc, // Service instance name
    BT_GATT_PRIMARY_SERVICE(&custom_service_uuid.uuid), // Service UUID
    BT_GATT_CHARACTERISTIC(&custom_char_uuid.uuid, // Characteristic of the service, UUID
                           BT_GATT_CHRC_WRITE | BT_GATT_CHRC_WRITE_WITHOUT_RESP, // Characteristic properties - this service can write OR write without waiting for a response.
                           BT_GATT_PERM_WRITE, // This service has the permission to write.
                           NULL, // No read callback, we don't care
                           write_custom_char, // callback
                           NULL // User data - none here.
                        )
);