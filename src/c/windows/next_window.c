#include "next_window.h"

static Window *s_next_window;
static TextLayer *s_launch_name_layer;

static void s_next_window_load(Window *window) {
    Layer *root_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(root_layer);

    s_launch_name_layer = text_layer_create(bounds);
    text_layer_set_text(s_launch_name_layer, "Hello");
    text_layer_set_background_color(s_launch_name_layer, GColorClear);
    layer_add_child(root_layer, text_layer_get_layer(s_launch_name_layer));
}

static void s_next_window_unload(Window *window){
    text_layer_destroy(s_launch_name_layer);
    window_destroy(s_next_window);
}

void s_next_window_push() {
    s_next_window = window_create();
    window_set_background_color(s_next_window, GColorPurple);
    window_set_window_handlers(s_next_window, (WindowHandlers) {
        .load = s_next_window_load,
        .unload = s_next_window_unload,
    });
    window_stack_push(s_next_window, true);
}

void set_content(Launch *launchData){
    text_layer_set_text(s_launch_name_layer, "content.name");
}