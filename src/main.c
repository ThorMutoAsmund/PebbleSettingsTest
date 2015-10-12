#include <pebble.h>

Window *my_window;
TextLayer *text_layer;

static TextLayer *create_default_text_layer(Window *window, GRect rect, GFont font, GTextAlignment alignment) {
  TextLayer *layer = text_layer_create(rect);
  text_layer_set_background_color(layer, GColorClear);
  text_layer_set_text_color(layer, GColorWhite);
  text_layer_set_font(layer, font);
  text_layer_set_text_alignment(layer, alignment);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(layer));
  return layer;
}

static void main_window_load(Window *window) {
  // Create time TextLayer
  Layer *window_layer = window_get_root_layer(window);

  text_layer = create_default_text_layer(window, GRect(0, 0, 144, 20), fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GTextAlignmentCenter);
}

static void main_window_unload(Window *window) {
    // Destroy TextLayer
    text_layer_destroy(text_layer);
}

void back_single_click_handler(ClickRecognizerRef recognizer, void *context)
{
  text_layer_set_text(text_layer, "BACK");
}
void up_single_click_handler(ClickRecognizerRef recognizer, void *context)
{
  text_layer_set_text(text_layer, "UP");
}
void down_single_click_handler(ClickRecognizerRef recognizer, void *context)
{
  text_layer_set_text(text_layer, "DOWN");
}
void select_single_click_handler(ClickRecognizerRef recognizer, void *context)
{
  text_layer_set_text(text_layer, "SELECT");
}

void config_provider(Window *window)
{
  window_single_click_subscribe(BUTTON_ID_BACK, back_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_single_click_handler);

  window_long_click_subscribe(BUTTON_ID_BACK, 0, back_single_click_handler, back_single_click_handler);
  window_long_click_subscribe(BUTTON_ID_UP, 0, up_single_click_handler, up_single_click_handler);
  window_long_click_subscribe(BUTTON_ID_DOWN, 0, down_single_click_handler, down_single_click_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 0, select_single_click_handler, select_single_click_handler);
}

void handle_init(void) {
  // Create window
  my_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(my_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_set_click_config_provider(my_window, (ClickConfigProvider)config_provider); 

  window_set_background_color(my_window, GColorBlack);
  window_stack_push(my_window, true);
}

void handle_deinit(void) {
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
