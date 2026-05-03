#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <lvgl.h>
#include <zmk/display.h>
#include <zmk/display/widgets/custom_status.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

// 1. Our widget instance struct
// struct zmk_widget_custom_status {
//     sys_snode_t node;
//     lv_obj_t *obj;
// };

// 2. The list of all instances of this widget
static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

// 3. Setter - updates the LVGL label
static void set_status_text(lv_obj_t *label, const char *text) {
    lv_label_set_text(label, text);
}
void zmk_widget_custom_status_set_text(struct zmk_widget_custom_status *widget, char *text) {
    // Update the text
    set_status_text(widget->obj, text);
}

// 4. Initializer - creates the LVGL object and registers the instance
int zmk_widget_custom_status_init(struct zmk_widget_custom_status *widget,
                                   lv_obj_t *parent) {
    widget->obj = lv_label_create(parent);
    set_status_text(widget->obj, "Hello ZMK!");
    sys_slist_append(&widgets, &widget->node);
    return 0;
}

// 5. Expose the LVGL object to ZMK's display system
lv_obj_t *zmk_widget_custom_status_obj(struct zmk_widget_custom_status *widget) {
    return widget->obj;
}

