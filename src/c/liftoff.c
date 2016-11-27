#include <pebble.h>

#include "windows/splash_window.h"
#include "windows/qr_window.h"
#include "windows/next_window.h"
#include "modules/image_comm.h"
#include "modules/next_comm.h"

void init(){
  if(launch_reason() == APP_LAUNCH_TIMELINE_ACTION) {
    comm_init();
    s_qr_window_push();
    s_qr_window_set_command(launch_get_args());
  } else {
    nex_comm_init();
    s_next_window_push();
  }
}

void deinit(){
  if(launch_reason() == APP_LAUNCH_TIMELINE_ACTION) {
    comm_deinit();
  } else {
    nex_comm_deinit();
  }
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}