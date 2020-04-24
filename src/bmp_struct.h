#ifndef __BMP_STRUCT_H__
#define __BMP_STRUCT_H__

#ifndef __BASE_TYPE_H__
#include "base_type.h"
#endif


typedef struct
{
	T_U8	bf_type[2];
	T_U8	bf_size[4];
	T_U16	bf_reserved_1;
	T_U16	bf_reserved_2;
	T_U8	bf_off_bit[4];

}T_File_Header;

typedef struct
{
	T_U32	bi_size;
	T_U32	bi_width;
	T_U32	bi_height;
	T_U16	bi_plane;
	T_U16	bi_bit_count;
	T_U32	bi_compression;
	T_U32	bi_size_image;
	T_U32	bi_X_pels_per_meter;
	T_U32	bi_Y_pels_per_meter;
	T_U32	bi_color_used;
	T_U32	bi_color_important;

}T_Info_Header;

typedef struct
{
	T_U8	color_blue;
	T_U8	color_green;
	T_U8	color_red;
	T_U8	color_reserved;

}T_Color_Table;

typedef struct
{
	T_File_Header file_header;
	T_Info_Header info_header;
	T_Color_Table *p_color_table;
	T_U8 *p_bmp_buffer;

}T_Bmp_File;


#endif

