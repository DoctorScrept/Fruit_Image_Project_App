#pragma once

void set_text_by_row(int row, TextLayer * text_layer);
void set_image_by_row(int row, BitmapLayer *image_layer, GBitmap *content_image);
void draw_row_callback (GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context);