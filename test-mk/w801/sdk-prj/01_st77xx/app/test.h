//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Это программное обеспечение распространяется свободно. Вы можете размещать
// его на вашем сайте, но не забудьте указать ссылку на мой YouTube-канал 
// "Электроника в объектике" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Автор: Надыршин Руслан / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef TEST
#define TEST

//#include "st77xx/types.h"

#include "wm_type_def.h"


// Тест выводит текст  по указанным координатам и плавно гасит подсветку
void Test_TextFading(char *pStr, s16 X, s16 Y);
// Тест заливает дисплей разными цветами
void Test_Colors(void);
// Тест поочерёдно выводит на дисплей картинки с SD-флешки
void Test_displayImage(const char* fname);


#endif