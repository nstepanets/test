/*

исходники для jpeg библиотеки, взяты отсюда:
https://gitee.com/openLuat/LuatOS.git

для работы, нужен уже инициализированный дисплей 
в библиотеке mod1/UTFT.h

т.е. это продолжение её для вывода .jpg файлов

*/

#ifndef U_JPEG
#define U_JPEG

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief   UTFT_ADD_lcd_draw_jpeg
 *
 * @param[in]  const char* path - file path
 *             xpos, ypos - start coordinate
 *
 * @return 0 - OK 
 *
 */
int UTFT_ADD_lcd_draw_jpeg (const char* path, int xpos, int ypos);


#ifdef __cplusplus
}
#endif

#endif /* U_JPEG */
