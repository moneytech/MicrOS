#include "mode_05H.h"
#include "drivers/vga/modes/registerFunctions.h"
#include "memory/heap/heap.h"
#include "drivers/dal/videocard/videocard.h"

//REGISTER VALUES
unsigned char g_320x200x4b[] =
	{
	/* MISC */
		0x63, 
	/* SEQ */
		0x03, 0x09, 0x03, 0x00, 0x02, 
	/* CRTC */
		0x2D, 0x27, 0x28, 0x90, 0x2B, 0x80, 0xBF, 0x1F,
		0x00, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x9C, 0x8E, 0x8F, 0x14, 0x00, 0x96, 0xB9, 0xA2,
		0xFF, 
	/* GC */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0F, 0x0F,
		0xFF, 
	/* AC */
		0x00, 0x13, 0x15, 0x17, 0x02, 0x04, 0x06, 0x07,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
		0x01, 0x00, 0x03, 0x00, 0x00, 
	};

//PALETTE
unsigned char palette05H[] = {
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

unsigned char *MODE05H_BUFFER[] = {NULL, NULL};
unsigned char bufferTurnedOn05H = 0;

int8_t setMode05H()
{
    writeRegisters(g_320x200x4b);
    set_vga_palette(palette05H);
    clearScreen05H();
    setTurnOnBufferFunc(&turnOnBuffer05H);
    setTurnOffBufferFunc(&turnOffBuffer05H);
    setIsBufferOnFunc(&isBufferOn05H);
    setSwapBuffersFunc(&swapBuffers05H);
    setDrawPixelFunc(&drawPixel05H);
    setDrawLineFunc(&drawLine05H);
    setDrawCircleFunc(&drawCircle05H);
    setDrawRectangleFunc(&drawRectangle05H);
    setClearScreenFunc(&clearScreen05H);
    return 0x05;
}

int8_t turnOnBuffer05H()
{
    if(bufferTurnedOn05H) return -1;
    for(int i = 1; i >= 0; i--)
    {
        MODE05H_BUFFER[i] = heap_kernel_alloc(MODE05H_HEIGHT * MODE05H_WIDTH / 8, 0);
        if(MODE05H_BUFFER[i] == NULL)
        {
            for(int j = 1; j >= i; j--)
            {
                heap_kernel_dealloc(MODE05H_BUFFER[j]);
                MODE05H_BUFFER[j] = NULL;
            }
            return -1;
        }
    }
    setDrawPixelFunc(&drawPixel05HBuffered);
    setDrawLineFunc(&drawLine05HBuffered);
    setDrawCircleFunc(&drawCircle05HBuffered);
    setDrawRectangleFunc(&drawRectangle05HBuffered);
    setClearScreenFunc(&clearScreen05HBuffered);
    bufferTurnedOn05H = 1;
    return 0;
}

int8_t turnOffBuffer05H()
{
    if(!bufferTurnedOn05H) return -1;
    for(int i = 1; i >= 0; i--)
    {
        heap_kernel_dealloc(MODE05H_BUFFER[i]);
        MODE05H_BUFFER[i] = NULL;
    }
    setDrawPixelFunc(&drawPixel05H);
    setDrawLineFunc(&drawLine05H);
    setDrawCircleFunc(&drawCircle05H);
    setDrawRectangleFunc(&drawRectangle05H);
    setClearScreenFunc(&clearScreen05H);
    bufferTurnedOn05H = 0;
    return 0;
}

uint8_t isBufferOn05H()
{
    return bufferTurnedOn05H;
}

int8_t swapBuffers05H()
{
    if(!bufferTurnedOn05H) return -1;
    memcpy(VGA_VRAM_2, MODE05H_BUFFER[0], MODE05H_WIDTH * MODE05H_HEIGHT / 8);
    memcpy(VGA_VRAM_2 + 0x2000, MODE05H_BUFFER[1], MODE05H_WIDTH * MODE05H_HEIGHT / 8);
    //memcpy(VGA_VRAM, MODE13H_BUFFER, MODE13H_HEIGHT * MODE13H_WIDTH);
    return 0;
}

int8_t drawPixel05H(uint8_t color, uint16_t x, uint16_t y)
{
    if((x>=MODE05H_WIDTH) || (y >=MODE05H_HEIGHT))
        return -1;
    unsigned char *fb = (unsigned char *) VGA_VRAM_2;
    unsigned int offset = (y/2 * MODE05H_WIDTH + x)/4;
	unsigned bit_no = x % 4;
	bit_write(fb[offset + (y%2 ? 0x2000 : 0)], 1<<(7 - (2 * bit_no)), (color & 0x2));
	bit_write(fb[offset + (y%2 ? 0x2000 : 0)], 1<<(7 - (2 * bit_no+1)), (color & 0x1));
    return 0;
}

int8_t drawLine05H(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
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
                drawPixel05H(color, x, a * x + b);
        else
            for(int x = ax; x <= bx; ++x)
                drawPixel05H(color, x, a * x + b);
    }
    else
    {
        float a = dx/(float)(dy);
        float b = ax - a * ay;
        if(ay > by)
            for(int y = by; y <= ay; ++ y)
                drawPixel05H(color, a * y + b, y);
        else
            for(int y = ay; y <= by; ++ y)
                drawPixel05H(color, a * y + b, y);
    }
    return 0;
}

int8_t drawCircle05H(uint8_t color, uint16_t x, uint16_t y, uint16_t radius) 
{
    return 0;
}

int8_t drawRectangle05H(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    return 0;
}
int8_t clearScreen05H()
{
    memset(VGA_VRAM_2, 0, 8000);
    memset(VGA_VRAM_2 + 0x2000, 0, 8000);
    return 0;
}

int8_t drawPixel05HBuffered(uint8_t color, uint16_t x, uint16_t y)
{
    if((!bufferTurnedOn05H) || (x>=MODE05H_WIDTH) || (y >=MODE05H_HEIGHT))
        return -1;
    unsigned int offset = (y/2 * MODE05H_WIDTH + x)/4;
	unsigned bit_no = x % 4;
    bit_write(MODE05H_BUFFER[y%2][offset], (1<<(7 - (2 * bit_no))), (color & 0x2));
    bit_write(MODE05H_BUFFER[y%2][offset], (1<<(7 - (2 * bit_no+1))), (color & 0x1));
    return 0;
}

int8_t drawLine05HBuffered(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    if(!bufferTurnedOn05H) return -1;
    if(ax == bx) return -1;
    int32_t dx = (int32_t)bx - ax;
    int32_t dy = (int32_t)by - ay;
    if(_abs(dx) >= _abs(dy))
    {
        float a = dy/(float)(dx);
        float b = ay - a * ax;
        if(ax > bx)
            for(int x = bx; x <= ax; ++x)
                drawPixel05HBuffered(color, x, a * x + b);
        else
            for(int x = ax; x <= bx; ++x)
                drawPixel05HBuffered(color, x, a * x + b);
    }
    else
    {
        float a = dx/(float)(dy);
        float b = ax - a * ay;
        if(ay > by)
            for(int y = by; y <= ay; ++ y)
                drawPixel05HBuffered(color, a * y + b, y);
        else
            for(int y = ay; y <= by; ++ y)
                drawPixel05HBuffered(color, a * y + b, y);
    }
    return 0;
}
int8_t drawCircle05HBuffered(uint8_t color, uint16_t x, uint16_t y, uint16_t radius)
{
    return 0;
}
int8_t drawRectangle05HBuffered(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    return 0;
}
int8_t clearScreen05HBuffered()
{
    if(!bufferTurnedOn05H) return -1;
    memset(MODE05H_BUFFER[0], 0, 8000);
    memset(MODE05H_BUFFER[1], 0, 8000);
    return 0;
}