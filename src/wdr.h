#ifndef __WDR_H__
#define __WDR_H__

#ifndef __BMP_RW_H__
#include "bmp_rw.h"
#endif

#ifndef __MAP_TABLE_H__
#include "map_table.h"
#endif

#ifndef __STRING_H__
#define __STRING_H__
#include <string.h>
#endif

#ifndef __MATH_H__
#define __MATH_H__
#include <math.h>
#endif

#ifndef __TIME_H__
#define __TIME_H__
#include <time.h>
#endif


T_Bmp_File fusion_image(T_Bmp_File *bmp_file_1, T_Bmp_File *bmp_file_2);

T_U8 *fusion_buffer(T_U8 *buffer_1, T_U8 *buffer_2, T_U32 width, T_U32 height, T_U32 line_byte);

void map_table2h();


#endif
