#include "mode_11H.h"
#include "drivers/vga/modes/registerFunctions.h"
#include "memory/heap/heap.h"
#include "drivers/dal/videocard/videocard.h"

//REGISTER VALUES
unsigned char g_640x480x2[] =
    {
    /* MISC */
        0xE3, 
    /* SEQ */
        0x03, 0x01, 0x0F, 0x00, 0x06, 
    /* CRTC */
        0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0x0B, 0x3E,
        0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xEA, 0x8C, 0xDF, 0x28, 0x00, 0xE7, 0x04, 0xE3,
        0xFF, 
    /* GC */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x0F,
        0xFF, 
    /* AC */
        0x00, 0x3F, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x3F,
        0x00, 0x3F, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x3F,
        0x01, 0x00, 0x0F, 0x00, 0x00, 
    };

//PALETTE
unsigned char palette11H[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x2A, 0x00, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x2A, 
    0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x15, 0x00, 0x00, 0x3F, 0x00, 0x2A, 
    0x15, 0x00, 0x2A, 0x3F, 0x2A, 0x00, 0x15, 0x2A, 0x00, 0x3F, 0x2A, 0x2A, 0x15, 0x2A, 0x2A, 0x3F, 
    0x00, 0x15, 0x00, 0x00, 0x15, 0x2A, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x2A, 0x2A, 0x15, 0x00, 0x2A, 
    0x15, 0x2A, 0x2A, 0x3F, 0x00, 0x2A, 0x3F, 0x2A, 0x00, 0x15, 0x15, 0x00, 0x15, 0x3F, 0x00, 0x3F, 
    0x15, 0x00, 0x3F, 0x3F, 0x2A, 0x15, 0x15, 0x2A, 0x15, 0x3F, 0x2A, 0x3F, 0x15, 0x2A, 0x3F, 0x3F, 
    0x15, 0x00, 0x00, 0x15, 0x00, 0x2A, 0x15, 0x2A, 0x00, 0x15, 0x2A, 0x2A, 0x3F, 0x00, 0x00, 0x3F, 
    0x00, 0x2A, 0x3F, 0x2A, 0x00, 0x3F, 0x2A, 0x2A, 0x15, 0x00, 0x15, 0x15, 0x00, 0x3F, 0x15, 0x2A, 
    0x15, 0x15, 0x2A, 0x3F, 0x3F, 0x00, 0x15, 0x3F, 0x00, 0x3F, 0x3F, 0x2A, 0x15, 0x3F, 0x2A, 0x3F, 
    0x15, 0x15, 0x00, 0x15, 0x15, 0x2A, 0x15, 0x3F, 0x00, 0x15, 0x3F, 0x2A, 0x3F, 0x15, 0x00, 0x3F, 
    0x15, 0x2A, 0x3F, 0x3F, 0x00, 0x3F, 0x3F, 0x2A, 0x15, 0x15, 0x15, 0x15, 0x15, 0x3F, 0x15, 0x3F, 
    0x15, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x15, 0x3F, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x3F, 0x3F, 0x3F, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

//DOUBLE BUFFER POINTER;

unsigned char *mode11h_buffer = NULL;
unsigned char buffer_turned_on_11h = 0;

int8_t mode11h_set_mode()
{
    writeRegisters(g_640x480x2);
    set_vga_palette(palette11H);
    mode11h_clear_screen();
    video_card_set_turn_on_buffer_func(&mode11h_turn_on_buffer);
    video_card_set_turn_off_buffer_func(&mode11h_turn_off_buffer);
    video_card_set_is_buffer_on_func(&mode11h_is_buffer_on);
    video_card_set_swap_buffers_func(&mode11h_swap_buffers);
    video_card_set_draw_pixel_func(&mode11h_draw_pixel);
    video_card_set_draw_line_func(&mode11h_draw_line);
    video_card_set_draw_circle_func(&mode11h_draw_circle);
    video_card_set_draw_rectangle_func(&mode11h_draw_rectangle);
    video_card_set_clear_screen_func(&mode11h_clear_screen);
    return 0x11;
}

int8_t mode11h_turn_on_buffer()
{
    if(buffer_turned_on_11h) return -1;
    mode11h_buffer = heap_kernel_alloc(MODE11H_HEIGHT * MODE11H_WIDTH / 8, 0);
    if(mode11h_buffer == NULL) return -1;
    video_card_set_draw_pixel_func(&mode11h_draw_pixel_buffered);
    video_card_set_draw_line_func(&mode11h_draw_line_buffered);
    video_card_set_draw_circle_func(&mode11h_draw_circle_buffered);
    video_card_set_draw_rectangle_func(&mode11h_draw_rectangle_buffered);
    video_card_set_clear_screen_func(&mode11h_clear_screen_buffered);
    buffer_turned_on_11h = 1;
    return 0;
}

int8_t mode11h_turn_off_buffer()
{
    if(!buffer_turned_on_11h) return -1;
    heap_kernel_dealloc(mode11h_buffer);
    mode11h_buffer = NULL;
    video_card_set_draw_pixel_func(&mode11h_draw_pixel);
    video_card_set_draw_line_func(&mode11h_draw_line);
    video_card_set_draw_circle_func(&mode11h_draw_circle);
    video_card_set_draw_rectangle_func(&mode11h_draw_rectangle);
    video_card_set_clear_screen_func(&mode11h_clear_screen);
    buffer_turned_on_11h = 0;
    return 0;
}

uint8_t mode11h_is_buffer_on()
{
    return buffer_turned_on_11h;
}

int8_t mode11h_swap_buffers()
{
    if(!buffer_turned_on_11h) return -1;
    memcpy(VGA_VRAM, mode11h_buffer, MODE11H_WIDTH * MODE11H_HEIGHT / 8);
    //memcpy(VGA_VRAM, mode13h_buffer, MODE13H_HEIGHT * MODE13H_WIDTH);
    return 0;
}

int8_t mode11h_draw_pixel(uint8_t color, uint16_t x, uint16_t y)
{
    if((x>=MODE11H_WIDTH) || (y >=MODE11H_HEIGHT))
        return -1;
    unsigned char *fb = (unsigned char *) VGA_VRAM;
    unsigned int offset = (y * MODE11H_WIDTH + x)/8;
	unsigned bit_no = x % 8;
	bit_write(fb[offset], 1<<(7-bit_no), (color % 2));
    return 0;
}

int8_t mode11h_draw_line(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    if(ax == bx) return -1;
    int32_t dx = (int32_t)bx - ax;
    int32_t dy = (int32_t)by - ay;
    if(_abs(dx) >= _abs(dy))
    {
        float a = dy/(float)(dx);
        float b = ay - a * ax;
        if(ax > bx)
            for(int x = bx; x <= ax; ++x)
                mode11h_draw_pixel(color, x, a * x + b);
        else
            for(int x = ax; x <= bx; ++x)
                mode11h_draw_pixel(color, x, a * x + b);
    }
    else
    {
        float a = dx/(float)(dy);
        float b = ax - a * ay;
        if(ay > by)
            for(int y = by; y <= ay; ++ y)
                mode11h_draw_pixel(color, a * y + b, y);
        else
            for(int y = ay; y <= by; ++ y)
                mode11h_draw_pixel(color, a * y + b, y);
    }
    return 0;
}

int8_t mode11h_draw_circle(uint8_t color, uint16_t x, uint16_t y, uint16_t radius) 
{
    return 0;
}

int8_t mode11h_draw_rectangle(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    return 0;
}
int8_t mode11h_clear_screen()
{
    memset(VGA_VRAM, 0, 64*1024);
    return 0;
}

int8_t mode11h_draw_pixel_buffered(uint8_t color, uint16_t x, uint16_t y)
{
    if((!buffer_turned_on_11h) || (x>=MODE11H_WIDTH) || (y >=MODE11H_HEIGHT))
        return -1;
    unsigned int offset = (y * MODE11H_WIDTH + x)/8;
	unsigned bit_no = x % 8;
	bit_write(mode11h_buffer[offset], 1<<(7-bit_no), (color % 2));
    return 0;
}

int8_t mode11h_draw_line_buffered(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    if(!buffer_turned_on_11h) return -1;
    if(ax == bx) return -1;
    int32_t dx = (int32_t)bx - ax;
    int32_t dy = (int32_t)by - ay;
    if(_abs(dx) >= _abs(dy))
    {
        float a = dy/(float)(dx);
        float b = ay - a * ax;
        if(ax > bx)
            for(int x = bx; x <= ax; ++x)
                mode11h_draw_pixel_buffered(color, x, a * x + b);
        else
            for(int x = ax; x <= bx; ++x)
                mode11h_draw_pixel_buffered(color, x, a * x + b);
    }
    else
    {
        float a = dx/(float)(dy);
        float b = ax - a * ay;
        if(ay > by)
            for(int y = by; y <= ay; ++ y)
                mode11h_draw_pixel_buffered(color, a * y + b, y);
        else
            for(int y = ay; y <= by; ++ y)
                mode11h_draw_pixel_buffered(color, a * y + b, y);
    }
    return 0;
}
int8_t mode11h_draw_circle_buffered(uint8_t color, uint16_t x, uint16_t y, uint16_t radius)
{
    return 0;
}
int8_t mode11h_draw_rectangle_buffered(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    return 0;
}
int8_t mode11h_clear_screen_buffered()
{
    if(!buffer_turned_on_11h) return -1;
    memset(mode11h_buffer, 0, 64*1024);
    return 0;
}