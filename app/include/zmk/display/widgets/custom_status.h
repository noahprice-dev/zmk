#pragma once

#include <lvgl.h>

// Forward declare our custom struct so consumers are aware of the type
struct zmk_widget_custom_status {
    sys_snode_t node;
    lv_obj_t *obj;
};

int zmk_widget_custom_status_init(struct zmk_widget_custom_status *widget, lv_obj_t *parent);
void zmk_widget_custom_status_set_text(struct zmk_widget_custom_status *widget, char *text);

lv_obj_t *zmk_widget_custom_status_obj(struct zmk_widget_custom_status *widget);