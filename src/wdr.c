#ifndef __WDR_H__
#include "wdr.h"
#endif


T_Bmp_File fusion_image(T_Bmp_File *bmp_file_1, T_Bmp_File *bmp_file_2)
{
	T_Bmp_File file_fusion;
	T_U32 width;
	T_U32 height;
	T_U16 bit_count;
	T_U32 line_byte;
	T_U32 data_byte;

	{
		assert(0X4D42 == *((T_U16 *)bmp_file_1->file_header.bf_type));
		assert(0X4D42 == *((T_U16 *)bmp_file_2->file_header.bf_type));
		assert(NULL != bmp_file_1->p_bmp_buffer);
		assert(NULL != bmp_file_2->p_bmp_buffer);
	}

	{
		width = bmp_file_1->info_header.bi_width;
		height = bmp_file_1->info_header.bi_height;
		assert( 24 == (bit_count = bmp_file_1->info_header.bi_bit_count) );
		line_byte = (width * 3 + 3) & ~3;
		data_byte = line_byte * height;
	}

	{
		*((T_U16 *)file_fusion.file_header.bf_type) = 0X4D42;
		*((T_U32 *)file_fusion.file_header.bf_size) = 54 + data_byte;
		*((T_U32 *)file_fusion.file_header.bf_off_bit) = 54;

		file_fusion.file_header.bf_reserved_1 = bmp_file_1->file_header.bf_reserved_1;
		file_fusion.file_header.bf_reserved_2 = bmp_file_1->file_header.bf_reserved_2;
	}

	{
		file_fusion.info_header.bi_width = width;
		file_fusion.info_header.bi_height = height;
		file_fusion.info_header.bi_size_image = data_byte;
		file_fusion.info_header.bi_bit_count = bit_count;

		file_fusion.info_header.bi_size = bmp_file_1->info_header.bi_size;
		file_fusion.info_header.bi_plane = bmp_file_1->info_header.bi_plane;
		file_fusion.info_header.bi_color_used = bmp_file_1->info_header.bi_color_used;
		file_fusion.info_header.bi_compression = bmp_file_1->info_header.bi_compression;
		file_fusion.info_header.bi_color_important = bmp_file_1->info_header.bi_color_important;
		file_fusion.info_header.bi_X_pels_per_meter = bmp_file_1->info_header.bi_X_pels_per_meter;
		file_fusion.info_header.bi_Y_pels_per_meter = bmp_file_1->info_header.bi_Y_pels_per_meter;
	}

	{
		file_fusion.p_color_table = NULL;
		file_fusion.p_bmp_buffer = fusion_buffer(bmp_file_1->p_bmp_buffer, bmp_file_2->p_bmp_buffer, width, height, line_byte);
	}

	return file_fusion;
}

T_U8 *fusion_buffer(T_U8 *buffer_1, T_U8 *buffer_2, T_U32 width, T_U32 height, T_U32 line_byte)
{
	T_U8 *buffer_fusion = NULL;
	T_U8 luminance;
	T_U8 red;
	T_U8 green;
	T_U8 blue;
	T_U32 line;
	T_U32 current_line;
	T_U32 pixel;
	T_U32 color;
	T_U8 (*line_head_1)[3];
	T_U8 (*line_head_2)[3];
	T_U8 (*line_head_fusion)[3];

	{
		assert(NULL != buffer_1);
		assert(NULL != buffer_2);
	}

	{
		assert(NULL != (buffer_fusion = (T_U8 *)malloc(line_byte * height)));
	}

	for(line = 0; line < height; line++)
	{
		current_line = height - 1 - line;
		line_head_1 = (T_U8 (*)[3])(buffer_1 + current_line * line_byte);
		line_head_2 = (T_U8 (*)[3])(buffer_2 + current_line * line_byte);
		line_head_fusion = (T_U8 (*)[3])(buffer_fusion + current_line * line_byte);

		for(pixel = 0; pixel < width; pixel++)
		{
			red = *( *(line_head_1 + pixel) + 2 );
			green = *( *(line_head_1 + pixel) + 1 );
			blue = *( *(line_head_1 + pixel) + 0 );

			luminance = (T_U8)( ( (T_U64)red * 19595 + (T_U64)green * 38469 + (T_U64)blue * 7472 + 32768 ) >> 16 );

			for(color = 0; color < 3; color++)
			{
				*(*(line_head_fusion+pixel) + color) = (T_U8)(
						(
								(( *(*(line_head_1 + pixel) + color) ) * map_table[luminance]) +
								(( *(*(line_head_2 + pixel) + color) ) * (65536 - map_table[luminance])) +
								32768
						) >> 16
				);
			}

		}

	}

	return buffer_fusion;
}

void map_table2h()
{
	const char *h_file = "./src/map_table.h";
	const char *c_file = "./src/map_table.c";
	double gama = 0.3;
	T_U32 map_table[256] = {0};
	FILE *fp_h = NULL;
	FILE *fp_c = NULL;

	for(T_U32 lum = 0; lum < 256; lum++)
	{
		map_table[lum] = (T_U32)(65536 * pow( (double)lum/255, gama) + 0.5);
	}

	{
		assert(NULL != (fp_h = fopen(h_file, "w")));
		fprintf(fp_h, "extern T_U32 map_table[];\n");
		fclose(fp_h);
	}

	{
		assert(NULL != (fp_c = fopen(c_file, "w")));
		fprintf(fp_c, "T_U32 map_table[] = {");
		for (T_U32 i = 0; i < 256; i++)
		{
			fprintf(fp_c, "%lu", *(map_table + i));
			if(i != 255)
			{
				fprintf(fp_c, ", ");
			}
		}
		fprintf(fp_c, "};\n");
		fclose(fp_c);
	}

}




