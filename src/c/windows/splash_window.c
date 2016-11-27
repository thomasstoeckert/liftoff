#include "splash_window.h"

static Window *s_splash_window;
static TextLayer *s_text_layer;

void s_window_load(Window *window){
    Layer *root = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(root);
    /*
	 * Default is used for displaying the splash screen
	 */
    GRect halfway = bounds;
    halfway.origin.y = halfway.size.h / 4;
    s_text_layer = text_layer_create(halfway);
    text_layer_set_text(s_text_layer, "Welcome! To configure what launches appear on your timeline, plase open the configuration page on your phone. Afterwards, availiable launches will appear on your timeline.");
    text_layer_set_text_color(s_text_layer, GColorWhite);
    text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
    text_layer_set_background_color(s_text_layer, GColorClear);
    layer_add_child(root, text_layer_get_layer(s_text_layer));
    text_layer_enable_screen_text_flow_and_paging(s_text_layer, 2);
}

void s_window_unload(Window *window){
	text_layer_destroy(s_text_layer);
}

void s_splash_window_push() {
	s_splash_window = window_create();
	window_set_background_color(s_splash_window, PBL_IF_COLOR_ELSE(GColorCobaltBlue, GColorBlack));
	window_set_window_handlers(s_splash_window, (WindowHandlers) {
		.load = s_window_load,
		.unload = s_window_unload,
	});
	window_stack_push(s_splash_window, true);
}