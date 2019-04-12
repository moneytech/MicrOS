#include "mode_06H.h"
#include "drivers/vga/modes/registerFunctions.h"
#include "memory/heap/heap.h"
#include "drivers/dal/videocard/videocard.h"

//REGISTER VALUES
unsigned char g_640x200x2[] =
	{
	/* MISC */
		0x63, 
	/* SEQ */
		0x03, 0x01, 0x01, 0x00, 0x06, 
	/* CRTC */
		0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
		0x00, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x9C, 0x8E, 0x8F, 0x28, 0x00, 0x96, 0xB9, 0xC2,
		0xFF, 
	/* GC */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00,
		0xFF, 
	/* AC */
		0x00, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17,
	    0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17,
	    0x01, 0x00, 0x01, 0x00, 0x00, 
	};

//PALETTE
unsigned char palette06H[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x2A, 0x00, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x2A, 
    0x00, 0x2A, 0x2A, 0x15, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x2A, 
    0x00, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x2A, 0x00, 0x2A, 0x2A, 0x15, 0x00, 0x2A, 0x2A, 0x2A, 
    0x15, 0x15, 0x15, 0x15, 0x15, 0x3F, 0x15, 0x3F, 0x15, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x15, 0x3F, 
    0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x15, 0x15, 0x15, 0x15, 0x3F, 0x15, 0x3F, 
    0x15, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x15, 0x3F, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x3F, 0x3F, 0x3F, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x2A, 0x00, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x2A, 
    0x00, 0x2A, 0x2A, 0x15, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x2A, 
    0x00, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x2A, 0x00, 0x2A, 0x2A, 0x15, 0x00, 0x2A, 0x2A, 0x2A, 
    0x15, 0x15, 0x15, 0x15, 0x15, 0x3F, 0x15, 0x3F, 0x15, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x15, 0x3F, 
    0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x15, 0x15, 0x15, 0x15, 0x3F, 0x15, 0x3F, 
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
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//DOUBLE BUFFER POINTER;

unsigned char *mode06h_buffer[] = {NULL, NULL};
unsigned char buffer_turned_on_06h = 0;

int8_t mode06h_set_mode()
{
    writeRegisters(g_640x200x2);
    set_vga_palette(palette06H);
    mode06h_clear_screen();
    video_card_set_turn_on_buffer_func(&mode06h_turn_on_buffer);
    video_card_set_turn_off_buffer_func(&mode06h_turn_off_buffer);
    video_card_set_is_buffer_on_func(&mode06h_is_buffer_on);
    video_card_set_swap_buffers_func(&mode06h_swap_buffers);
    video_card_set_draw_pixel_func(&mode06h_draw_pixel);
    video_card_set_draw_line_func(&mode06h_draw_line);
    video_card_set_draw_circle_func(&mode06h_draw_circle);
    video_card_set_draw_rectangle_func(&mode06h_draw_rectangle);
    video_card_set_clear_screen_func(&mode06h_clear_screen);
    return 0x06;
}

int8_t mode06h_turn_on_buffer()
{
    if(buffer_turned_on_06h) return -1;
    for(int i = 1; i >= 0; i--)
    {
        mode06h_buffer[i] = heap_kernel_alloc(MODE06H_HEIGHT * MODE06H_WIDTH / 16, 0);
        if(mode06h_buffer[i] == NULL)
        {
            for(int j = 1; j >= i; j--)
            {
                heap_kernel_dealloc(mode06h_buffer[j]);
                mode06h_buffer[j] = NULL;
            }
            return -1;
        }
    }
    video_card_set_draw_pixel_func(&mode06h_draw_pixel_buffered);
    video_card_set_draw_line_func(&mode06h_draw_line_buffered);
    video_card_set_draw_circle_func(&mode06h_draw_circle_buffered);
    video_card_set_draw_rectangle_func(&mode06h_draw_rectangle_buffered);
    video_card_set_clear_screen_func(&mode06h_clear_screen_buffered);
    buffer_turned_on_06h = 1;
    return 0;
}

int8_t mode06h_turn_off_buffer()
{
    if(!buffer_turned_on_06h) return -1;
    for(int i = 1; i >= 0; i--)
    {
        heap_kernel_dealloc(mode06h_buffer[i]);
        mode06h_buffer[i] = NULL;
    }
    video_card_set_draw_pixel_func(&mode06h_draw_pixel);
    video_card_set_draw_line_func(&mode06h_draw_line);
    video_card_set_draw_circle_func(&mode06h_draw_circle);
    video_card_set_draw_rectangle_func(&mode06h_draw_rectangle);
    video_card_set_clear_screen_func(&mode06h_clear_screen);
    buffer_turned_on_06h = 0;
    return 0;
}

uint8_t mode06h_is_buffer_on()
{
    return buffer_turned_on_06h;
}

int8_t mode06h_swap_buffers()
{
    if(!buffer_turned_on_06h) return -1;
    memcpy(VGA_VRAM_2, mode06h_buffer[0], MODE06H_WIDTH * MODE06H_HEIGHT / 16);
    memcpy(VGA_VRAM_2 + 0x2000, mode06h_buffer[1], MODE06H_WIDTH * MODE06H_HEIGHT / 16);
    //memcpy(VGA_VRAM, mode13h_buffer, MODE13H_HEIGHT * MODE13H_WIDTH);
    return 0;
}

int8_t mode06h_draw_pixel(uint8_t color, uint16_t x, uint16_t y)
{
    if((x>=MODE06H_WIDTH) || (y >=MODE06H_HEIGHT))
        return -1;
    unsigned char *fb = (unsigned char *) VGA_VRAM_2;
    unsigned int offset = (y/2 * MODE06H_WIDTH + x)/8;
	unsigned bit_no = x % 8;
	bit_write(fb[offset + (y%2 ? 0x2000 : 0)], (1<<(7 - bit_no)), (color & 0x1));
    return 0;
}

int8_t mode06h_draw_line(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
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
                mode06h_draw_pixel(color, x, a * x + b);
        else
            for(int x = ax; x <= bx; ++x)
                mode06h_draw_pixel(color, x, a * x + b);
    }
    else
    {
        float a = dx/(float)(dy);
        float b = ax - a * ay;
        if(ay > by)
            for(int y = by; y <= ay; ++ y)
                mode06h_draw_pixel(color, a * y + b, y);
        else
            for(int y = ay; y <= by; ++ y)
                mode06h_draw_pixel(color, a * y + b, y);
    }
    return 0;
}

int8_t mode06h_draw_circle(uint8_t color, uint16_t x, uint16_t y, uint16_t radius) 
{
    return 0;
}

int8_t mode06h_draw_rectangle(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    return 0;
}
int8_t mode06h_clear_screen()
{
    memset(VGA_VRAM_2, 0, 8000);
    memset(VGA_VRAM_2 + 0x2000, 0, 8000);
    return 0;
}

int8_t mode06h_draw_pixel_buffered(uint8_t color, uint16_t x, uint16_t y)
{
    if((!buffer_turned_on_06h) || (x>=MODE06H_WIDTH) || (y >=MODE06H_HEIGHT))
        return -1;
    unsigned int offset = (y/2 * MODE06H_WIDTH + x)/8;
	unsigned bit_no = x % 8;
    bit_write(mode06h_buffer[y%2][offset], (1<<(7 - bit_no)), (color & 0x1));
    return 0;
}

int8_t mode06h_draw_line_buffered(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    if(!buffer_turned_on_06h) return -1;
    if(ax == bx) return -1;
    int32_t dx = (int32_t)bx - ax;
    int32_t dy = (int32_t)by - ay;
    if(_abs(dx) >= _abs(dy))
    {
        float a = dy/(float)(dx);
        float b = ay - a * ax;
        if(ax > bx)
            for(int x = bx; x <= ax; ++x)
                mode06h_draw_pixel_buffered(color, x, a * x + b);
        else
            for(int x = ax; x <= bx; ++x)
                mode06h_draw_pixel_buffered(color, x, a * x + b);
    }
    else
    {
        float a = dx/(float)(dy);
        float b = ax - a * ay;
        if(ay > by)
            for(int y = by; y <= ay; ++ y)
                mode06h_draw_pixel_buffered(color, a * y + b, y);
        else
            for(int y = ay; y <= by; ++ y)
                mode06h_draw_pixel_buffered(color, a * y + b, y);
    }
    return 0;
}
int8_t mode06h_draw_circle_buffered(uint8_t color, uint16_t x, uint16_t y, uint16_t radius)
{
    return 0;
}
int8_t mode06h_draw_rectangle_buffered(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    return 0;
}
int8_t mode06h_clear_screen_buffered()
{
    if(!buffer_turned_on_06h) return -1;
    memset(mode06h_buffer[0], 0, 8000);
    memset(mode06h_buffer[1], 0, 8000);
    return 0;
}