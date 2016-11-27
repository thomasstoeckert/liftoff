#pragma once

#include <pebble.h>

#include "../windows/next_window.h"

struct launch{
    char *name;
    char *net;
    char *location;
    int status;
} launch_data;

void nex_comm_init();

void nex_comm_deinit();

void throw();