#include <pebble.h>
#include "clock.h"

TextLayer *clock_text_layer;
int refCount = 0;

static char time_format[] = "00:00";

void clock_on_time_change(struct tm *myTick, TimeUnits units_changed)
{
   strftime(time_format, sizeof(time_format), "%H:%M", myTick);
   text_layer_set_text(clock_text_layer, time_format);
}

void clock_init(Layer *parent)
{ 
   APP_LOG(APP_LOG_LEVEL_INFO, "clock_init %d", (int)clock_text_layer);
   if (refCount == 0) {
      
      clock_text_layer = text_layer_create(GRect(115, 0, 30, 15));                                                                                
      tick_timer_service_subscribe(MINUTE_UNIT, clock_on_time_change); 
      // ПОМЕНЯТЬ ШРИФТ (для часов) !!!                             ↓↓↓↓↓    
      text_layer_set_font(clock_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
   }
   refCount = refCount + 1;
   APP_LOG(APP_LOG_LEVEL_INFO, "clock_init+1 %d", (int)clock_text_layer);
//-----------------------------------------TIME--------------------------------------------------↓↓↓↓↓-----------//                  
   layer_add_child(parent, text_layer_get_layer(clock_text_layer));
 //-----------------------------------------TIME--------------------------------------------------↑↑↑↑↑-----------//
}

void clock_clear()
{
   refCount = refCount - 1;
   APP_LOG(APP_LOG_LEVEL_INFO, "clock_clear %d", (int)clock_text_layer);
   if (refCount == 0) {
      text_layer_destroy(clock_text_layer);
   }
}