#include <pebble.h>
#include "main_menu.h"
#include "content_menu.h"
#include "text_factory.h"
#include "clock.h"

Window * main_menu_window;
MenuLayer* menu_layer;
Layer * clock_layer;

uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
   return 7;
}

static void window_load(Window *window)
{
         // Устанавливаем рамку для "Меню_слоя"...и сдвигаем его по Y на 16px для того, что-бы поместились часы
         menu_layer = menu_layer_create(GRect(0, 16, 144, 152));
      
         //Эта функция Задает конфигурацию кликов (разрешает делать "Клики")  в "Меню-слой" на "главном окне"
         menu_layer_set_click_config_onto_window(menu_layer, main_menu_window);
      
         //Give it it's callback
         MenuLayerCallbacks callbacks = {
            .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,//#include "text_factory.h"
            .get_num_rows =(MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
            .select_click =(MenuLayerSelectCallback) select_click_callback// from content_menu.h
         };
         menu_layer_set_callbacks(menu_layer, NULL, callbacks);
      
         
         Layer *main_window_root_layer = window_get_root_layer(main_menu_window);
         
         clock_init(main_window_root_layer);
         //layer_add_child(main_window_root_layer, clock_layer);
         //Add to window
         layer_add_child(main_window_root_layer, menu_layer_get_layer(menu_layer));
}
                          
static void window_unload(Window *window){
         menu_layer_destroy(menu_layer);
         clock_clear();
}

void init_main_menu(Layer* layer)
{
   clock_layer = layer;
   main_menu_window = window_create();

   window_set_window_handlers(main_menu_window, (WindowHandlers) {
      .load = window_load, 
      .unload = window_unload});
   
   window_stack_push(main_menu_window, false);
}

void clear_main_menu() {
   window_destroy(main_menu_window);
}