//----------------------------------------------------------------------------------------------------
// Lib by YuriYuriy 2025
//----------------------------------------------------------------------------------------------------
#include "st77xx.h"
#include "commands_st7789v.h"
#include "commands_st7735s.h"

//----------------------------------------------------------------------------------------------------
// Implemented only for Pico RP2040
// If you want to use a other microcontroller. This function need to be implemented
//----------------------------------------------------------------------------------------------------
void st77xx_spi_init(void)
{
  spi_init(SPI_PORT_ST77XX, FREQUNCY_SPI_ST77XX);

  gpio_set_function(PIN_MISO_ST77XX,  GPIO_FUNC_SPI);
  gpio_set_function(PIN_CS_ST77XX,    GPIO_FUNC_SPI);
  gpio_set_function(PIN_SCK_ST77XX,   GPIO_FUNC_SPI);
  gpio_set_function(PIN_MOSI_ST77XX,  GPIO_FUNC_SPI);

  gpio_init(PIN_RST_ST77XX);
  gpio_init(PIN_DC_ST77XX);
  gpio_init(PIN_BLK_ST77XX);

  gpio_set_dir(PIN_CS_ST77XX,   GPIO_OUT);
  gpio_set_dir(PIN_RST_ST77XX,  GPIO_OUT);
  gpio_set_dir(PIN_DC_ST77XX,   GPIO_OUT);
  gpio_set_dir(PIN_BLK_ST77XX,  GPIO_OUT);

  gpio_put(PIN_CS_ST77XX,   1);
  gpio_put(PIN_RST_ST77XX,  1);
  gpio_put(PIN_DC_ST77XX,   1);
  gpio_put(PIN_BLK_ST77XX,  1);
}
void st77xx_write(uint8_t st77xx_data)
{
  #ifdef ST77XX_USED_SPI
    spi_write_blocking(SPI_PORT_ST77XX, &st77xx_data, 1);
  #endif
  #ifdef ST77XX_USED_DMA
    // None implemented
  #endif
}
void st77xx_delay_ms(uint16_t st77xx_delay_ms)
{
  sleep_ms(st77xx_delay_ms);
}
void st77xx_reset_hardwear(void)
{
  gpio_put(PIN_RST_ST77XX, 0);
  sleep_ms(10);
  gpio_put(PIN_RST_ST77XX, 1);
}
void st77xx_dc(bool ds_data)
{
  gpio_put(PIN_DC_ST77XX, ds_data);
}
//----------------------------------------------------------------------------------------------------
// This function don't need to be implemented
//----------------------------------------------------------------------------------------------------
void st77xx_send_command(uint8_t st77xx_command)
{
  st77xx_dc(ST77XX_DC_COMMAND);
  st77xx_write(st77xx_command);
}
void st77xx_send_data(uint8_t st77xx_data)
{
  st77xx_dc(ST77XX_DC_DATA);
  st77xx_write(st77xx_data);
}
void st77xx_send_color(uint16_t send_color, uint32_t size_screen)
{
  st77xx_dc(ST77XX_DC_DATA);
  for (uint32_t i = 0; i < size_screen; i++)
  {
    st77xx_write(send_color >> 8);
    st77xx_write(send_color);
  }
  st77xx_dc(ST77XX_DC_COMMAND);
}
void st77xx_send_color_buff(uint16_t *send_color_buff, uint32_t size_buff)
{
  st77xx_dc(ST77XX_DC_DATA);
  for (uint32_t i = 0; i < size_buff; i++)
  {
    st77xx_write(send_color_buff[i] >> 8);
    st77xx_write(send_color_buff[i]);
  }
  st77xx_dc(ST77XX_DC_COMMAND);
}
void st77xx_init(void)
{
  #ifdef ST77XX_USED_SPI
    st77xx_spi_init();
  #endif
  #ifdef ST77XX_USED_DMA
    // None implemented
  #endif

  st77xx_reset_hardwear();

  #ifdef ST7735S
    st77xx_send_command(ST7735S_SWRESET);
    st77xx_delay_ms(120);

    st77xx_send_command(ST7735S_SLPOUT);
    st77xx_delay_ms(120);

    st77xx_send_command(ST7735S_INVOFF);

    st77xx_send_command(ST7735S_MADCTL);
    st77xx_send_data(0x00);

    st77xx_send_command(ST7735S_COLMOD);
    st77xx_send_data(0x55);

    st77xx_send_command(ST7789V_GAMSET);
    st77xx_send_data(0x08);

    st77xx_send_command(ST7735S_NORON);
    st77xx_send_command(ST7735S_DISPON);
  #endif
  #ifdef ST7789V
    st77xx_send_command(ST7789V_SWRESET);
    st77xx_delay_ms(120);

    st77xx_send_command(ST7789V_SLPOUT);
    st77xx_delay_ms(120);

    st77xx_send_command(ST7789V_INVOFF);

    st77xx_send_command(ST7789V_MADCTL);
    st77xx_send_data(0x00);

    st77xx_send_command(ST7789V_COLMOD);
    st77xx_send_data(0x55);

    st77xx_send_command(ST7789V_GAMSET);
    st77xx_send_data(0x08);

    st77xx_send_command(ST7789V_NORON);
    st77xx_send_command(ST7789V_DISPON);
  #endif
}
void st77xx_set_col_row_addr(uint16_t cStart, uint16_t rStart, uint16_t cStop, uint16_t rStop)
{
  #ifdef ST7735S
    st77xx_send_command(ST7735S_CASET);
    st77xx_send_data(cStart >> 8);
    st77xx_send_data(cStart);
    st77xx_send_data(cStop >> 8);
    st77xx_send_data(cStop);
    st77xx_send_command(ST7735S_RASET);
    st77xx_send_data(rStart >> 8);
    st77xx_send_data(rStart);
    st77xx_send_data(rStop >> 8);
    st77xx_send_data(rStop);
    st77xx_send_command(ST7735S_RAMWR);
  #endif
  #ifdef ST7789V
    st77xx_send_command(ST7789V_CASET);
    st77xx_send_data(cStart >> 8);
    st77xx_send_data(cStart);
    st77xx_send_data(cStop >> 8);
    st77xx_send_data(cStop);
    st77xx_send_command(ST7789V_RASET);
    st77xx_send_data(rStart >> 8);
    st77xx_send_data(rStart);
    st77xx_send_data(rStop >> 8);
    st77xx_send_data(rStop);
    st77xx_send_command(ST7789V_RAMWR);
  #endif
}
