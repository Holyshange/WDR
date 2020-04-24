#ifndef __BMP_RW_H__
#include "bmp_rw.h"
#endif


T_Bmp_File read_bmp(const char *file_name)
{
	FILE *fp = NULL;
	T_Bmp_File bmp_file;
	T_U32 width;
	T_U32 height;
	T_U16 bit_count;
	T_U32 line_byte;
	T_U32 data_byte;

	{
		assert(NULL != (fp = fopen(file_name, "rb")));
	}

	{
		fread(&(bmp_file.file_header), 14, 1, fp);
		assert(0X4D42 == *((T_U16 *)bmp_file.file_header.bf_type));
	}

	{
		fread(&(bmp_file.info_header), 40, 1, fp);
		width = bmp_file.info_header.bi_width;
		height = bmp_file.info_header.bi_height;
		bit_count = bmp_file.info_header.bi_bit_count;
		assert( (8 == bit_count) || (24 == bit_count) );
	}

	{
		bmp_file.p_color_table = NULL;
		bmp_file.p_bmp_buffer = NULL;

		if( 8 == bit_count )
		{
			assert(NULL != (bmp_file.p_color_table = (T_Color_Table *)malloc(1024)));
			fread(bmp_file.p_color_table, 1024, 1, fp);

			line_byte = (width + 3) & ~3;
		}
		else
		{
			line_byte = (width * 3 + 3) & ~3;
		}

		data_byte = line_byte * height;
		assert(NULL != (bmp_file.p_bmp_buffer = (T_U8 *)malloc(data_byte)));
		fread(bmp_file.p_bmp_buffer, data_byte, 1, fp);
	}

	{
		fclose(fp);
	}

	return bmp_file;
}

void write_bmp(const char *file_name, T_Bmp_File *bmp_file)
{
	FILE *fp = NULL;
	T_U32 width;
	T_U32 height;
	T_U16 bit_count;
	T_U32 line_byte;

	{
		assert(0X4D42 == *((T_U16 *)bmp_file->file_header.bf_type));
		assert(NULL != bmp_file->p_bmp_buffer);
	}

	{
		width = bmp_file->info_header.bi_width;
		height = bmp_file->info_header.bi_height;
		bit_count = bmp_file->info_header.bi_bit_count;
		assert( (8 == bit_count) || (24 == bit_count) );
	}

	{
		assert(NULL != (fp = fopen(file_name, "wb")));
	}

	{
		fwrite(&bmp_file->file_header, 14, 1, fp);
		fwrite(&bmp_file->info_header, 40, 1, fp);

		if(8 == bit_count)
		{
			assert(NULL != bmp_file->p_color_table);
			fwrite(bmp_file->p_color_table, 1024, 1, fp);

			line_byte = (width + 3) & ~3;
		}
		else
		{
			line_byte = (width * 3 + 3) & ~3;
		}

		fwrite(bmp_file->p_bmp_buffer, line_byte * height, 1, fp);
	}

	{
		fclose(fp);
	}

}

