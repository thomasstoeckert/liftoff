#include "image_comm.h"

static uint8_t *s_img_data;
static int s_img_size;

static bool s_ready;

uint32_t message_cmd;

static void inbox_received_handler(DictionaryIterator *iter, void *context) {

    //Ready chunk
    Tuple *ready_t = dict_find(iter, MESSAGE_KEY_Ready);
    if(ready_t) {
        APP_LOG(APP_LOG_LEVEL_INFO, "JS Ready!");
        s_ready = true;
        send_request(message_cmd);
    }

    // Get the received image chunk
    Tuple *img_size_t = dict_find(iter, MESSAGE_KEY_DataLength);
    if (img_size_t) {
		s_img_size = img_size_t->value->int32;

		// Allocate buffer for image data
		s_img_data = (uint8_t *)malloc(s_img_size * sizeof(uint8_t));
    }

    // An image chunk
    Tuple *chunk_t = dict_find(iter, MESSAGE_KEY_DataChunk);
    if (chunk_t) {
		uint8_t *chunk_data = chunk_t->value->data;

		Tuple *chunk_size_t = dict_find(iter, MESSAGE_KEY_ChunkSize);
		int chunk_size = chunk_size_t->value->int32;

		Tuple *index_t = dict_find(iter, MESSAGE_KEY_Index);
		int index = index_t->value->int32;

		// Save the chunk
		memcpy(&s_img_data[index], chunk_data, chunk_size);
    }

    // Complete?
    Tuple *complete_t = dict_find(iter, MESSAGE_KEY_Complete);
    if (complete_t) {
		// Show the image
		s_qr_window_set_data(s_img_data, s_img_size);
    }
}

void send_request(uint32_t command) {
    APP_LOG(APP_LOG_LEVEL_INFO, "I was told to send request command %d", (int) command);
    if(!s_ready){
        APP_LOG(APP_LOG_LEVEL_INFO, "JS not yet ready, saving until it is OK");
        message_cmd = command;
        return;
    }
    DictionaryIterator *iter;
	app_message_outbox_begin(&iter);
    dict_write_int(iter, MESSAGE_KEY_qr_outbound, &command, sizeof(command), true);

	app_message_outbox_send();
}

void comm_init() {
    app_message_register_inbox_received(inbox_received_handler);

    const int inbox_size = 32000;
    const int outbox_size = 64;
    app_message_open(inbox_size, outbox_size);
}

void comm_deinit() {
    // Free image data buffer
    if (s_img_data) {
		free(s_img_data);
    }
}