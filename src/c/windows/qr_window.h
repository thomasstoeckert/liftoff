#pragma once

#include <pebble.h>

void s_qr_window_push();

void s_qr_window_set_data(uint8_t *data, int size);

void s_qr_window_set_command(uint32_t arg);