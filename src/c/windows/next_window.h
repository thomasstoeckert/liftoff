#pragma once

#include <pebble.h>

#include "../modules/next_comm.h"

extern struct Launch;

void s_next_window_push();

void set_content(Launch *launchData);