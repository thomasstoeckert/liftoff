#include "qr_window.h"

#include "../modules/comm.h"

static Window *s_qr_window;
static BitmapLayer *s_qr_image_layer;

static GBitmap *s_qr_image_bitmap;

static void s_qr_window_load(Window *window) {
    Layer *root_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(root_layer);

    s_qr_image_layer = bitmap_layer_create(bounds);
    bitmap_layer_set_compositing_mode(s_qr_image_layer, GCompOpSet);
    layer_add_child(root_layer, bitmap_layer_get_layer(s_qr_image_layer));
}

static void s_qr_window_unload(Window *window) {

    bitmap_layer_destroy(s_qr_image_layer);

    if(s_qr_image_bitmap) {
        gbitmap_destroy(s_qr_image_bitmap);
    }

    window_destroy(s_qr_window);
}

void s_qr_window_push() {

    s_qr_window = window_create();
    window_set_background_color(s_qr_window, GColorWhite);
    window_set_window_handlers(s_qr_window, (WindowHandlers) {
        .load = s_qr_window_load,
        .unload = s_qr_window_unload,
    });
    window_stack_push(s_qr_window, true);
}

void s_qr_window_set_command(uint32_t arg){
    //An argument sent consists of the ones place being either a 1 or a 0, with the
    // rest of the numbers being the launch id. This gets the command and calls the appropriate
    // js function to display the qr code
    // 0 - Fetch Info Command | 1 - Fetch Video Command
    // NOTE: This doesn't actually do the work, it just tells comm.c to do it
    send_request((int) arg);
}

void s_qr_window_set_data(uint8_t * data, int size) {
    if(s_qr_image_bitmap){
        gbitmap_destroy(s_qr_image_bitmap);
    }

    s_qr_image_bitmap = gbitmap_create_from_png_data(data, size);

    if(s_qr_image_bitmap) {
        bitmap_layer_set_bitmap(s_qr_image_layer, s_qr_image_bitmap);
    } else {
        APP_LOG(APP_LOG_LEVEL_ERROR, "Error generating image from data");
    }
}