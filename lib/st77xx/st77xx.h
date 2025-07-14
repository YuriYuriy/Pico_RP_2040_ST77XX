//----------------------------------------------------------------------------------------------------
// Lib by YuriYuriy 2025
//----------------------------------------------------------------------------------------------------
#ifndef _ST77XX
#define _ST77XX

#include "main.h"
#include "st77xx_graph.h"
#include "st77xx_fonts.h"
#include "st77xx_img.h"

//----------------------------------------------------------------------------------------------------
// Used screen driver
//----------------------------------------------------------------------------------------------------
//#define ST7735S
#define ST7789V

//----------------------------------------------------------------------------------------------------
// Used interface ST77XX
//----------------------------------------------------------------------------------------------------
#define ST77XX_USED_SPI
//#define ST77XX_USED_DMA

//----------------------------------------------------------------------------------------------------
// Screen size
//----------------------------------------------------------------------------------------------------
#define ST77XX_X_OFFSET  0
#define ST77XX_Y_OFFSET  0
#define ST77XX_X_SIZE    240
#define ST77XX_Y_SIZE    320

//----------------------------------------------------------------------------------------------------
// Pins SPI ST77XX
//----------------------------------------------------------------------------------------------------
#define SPI_PORT_ST77XX  spi1
#define PIN_MISO_ST77XX  12
#define PIN_SCK_ST77XX   10
#define PIN_MOSI_ST77XX  11
#define PIN_CS_ST77XX    13
#define PIN_RST_ST77XX   15
#define PIN_DC_ST77XX    14
#define PIN_BLK_ST77XX   1

//----------------------------------------------------------------------------------------------------
// Frequncy SPI ST77XX
//----------------------------------------------------------------------------------------------------
#define FREQUNCY_SPI_ST77XX  125 * 1000 * 1000

//----------------------------------------------------------------------------------------------------
// CS data
//----------------------------------------------------------------------------------------------------
#define ST77XX_DC_DATA     true
#define ST77XX_DC_COMMAND  false

//----------------------------------------------------------------------------------------------------
// Colors ST77XX
//----------------------------------------------------------------------------------------------------
#define ST77XX_BLACK    0x0000
#define ST77XX_BLUE     0x001F
#define ST77XX_RED      0xF800
#define ST77XX_GREEN    0x07E0
#define ST77XX_CYAN     0x07FF
#define ST77XX_MAGENTA  0xF81F
#define ST77XX_YELLOW   0xFFE0
#define ST77XX_WHITE    0xFFFF

//----------------------------------------------------------------------------------------------------
// Function lib
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
// Implemented only for Pico RP2040
// If you want to use a other microcontroller. This function need to be implemented
//----------------------------------------------------------------------------------------------------
//void st77xx_spi_init(void);
void st77xx_write(uint8_t st77xx_data);
void st77xx_delay_ms(uint16_t st77xx_delay_ms);
//void st77xx_reset_hardwear(void);
void st77xx_dc(bool ds_data);

//----------------------------------------------------------------------------------------------------
// This function don't need to be implemented
//----------------------------------------------------------------------------------------------------
void st77xx_send_command(uint8_t st77xx_command);
void st77xx_send_data(uint8_t st77xx_data);
void st77xx_send_color(uint16_t send_color, uint32_t size_screen);
void st77xx_send_color_buff(uint16_t *send_color_buff, uint32_t size_screen_buff);
void st77xx_init(void);
void st77xx_set_col_row_addr(uint16_t cStart, uint16_t rStart, uint16_t cStop, uint16_t rStop);

#endif