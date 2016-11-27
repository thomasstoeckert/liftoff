#pragma once

#include <pebble.h>

#include "../windows/qr_window.h"

void comm_init();

void comm_deinit();

void send_request(uint32_t command);