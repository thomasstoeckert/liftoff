#include <pebble.h>

#include "windows/splash_window.h"
#include "windows/qr_window.h"
#include "modules/comm.h"

void init(){
  comm_init();
  if(launch_reason() == APP_LAUNCH_TIMELINE_ACTION) {
    s_qr_window_push();
    s_qr_window_set_command(launch_get_args());
  } else {
    s_splash_window_push();
  }
}

void deinit(){
  comm_deinit();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}