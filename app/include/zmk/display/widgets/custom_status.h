#pragma once

#include <lvgl.h>

// ? Maximum message body length
#define MAX_TEXT_LEN 64
// Forward declare our custom struct so consumers are aware of the type
struct zmk_widget_custom_status {
    sys_snode_t node;
    lv_obj_t *obj;
};

int zmk_widget_custom_status_init(struct zmk_widget_custom_status *widget, lv_obj_t *parent);

void zmk_widget_custom_status_set_text(const char *text);

lv_obj_t *zmk_widget_custom_status_obj(struct zmk_widget_custom_status *widget);