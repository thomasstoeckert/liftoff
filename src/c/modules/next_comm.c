#include "next_comm.h"

static bool s_ready;
static bool s_update_content;

Launch launchData = {"null", "null", "null", 3};

static void process_tuple(Tuple *t){
    uint32_t key = t->key;
    if(key == MESSAGE_KEY_Ready){
        APP_LOG(APP_LOG_LEVEL_INFO, "JS Ready!");
        s_ready = true;
        throw();
    }
    else if (key == MESSAGE_KEY_NextLaunchName) {
        strcpy(launchData.name, t->value->cstring);
        s_update_content = true;
    }
    else if (key == MESSAGE_KEY_NextLaunchNet) {
        strcpy(launchData.net, t->value->cstring);
        s_update_content = true;
    }
    else if (key == MESSAGE_KEY_NextLaunchLocation) {
        strcpy(launchData.location, t->value->cstring);
        s_update_content = true;
    }
    else if (key == MESSAGE_KEY_NextLaunchStatus) {
        launchData.status = t->value->int8;
        s_update_content = true;
    }
}

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
    //Launch Information!
    s_update_content = false;
    Tuple *t = dict_read_next(iter);
    while(t != NULL){
        process_tuple(t);
        t = dict_read_next(iter);
    }
    if(s_update_content) {
        set_content(launchData);
    }
}

void throw(){
    APP_LOG(APP_LOG_LEVEL_INFO, "Fetching Next Launch Information...");
    if(!s_ready){
        APP_LOG(APP_LOG_LEVEL_INFO, "JS Not ready... holding");
        return;
    }
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    Tuplet value = TupletInteger(MESSAGE_KEY_GetNextLaunch, 5); //"5" can be any number. It just has to be something
    dict_write_tuplet(iter, &value);

    app_message_outbox_send();
}

void nex_comm_init() {
    app_message_register_inbox_received(inbox_received_handler);
    const int inbox_size = 32000;
    const int outbox_size = 64;
    app_message_open(inbox_size, outbox_size);
}

void nex_comm_deinit() {
    //I have nothing to do, so I do nothing!
}