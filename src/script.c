#ifndef __SCRIPT_H__
#include "script.h"
#endif


void run_fusion()
{
	char *image_1 = "./data/fattal3.bmp";
	char *image_2 = "./data/fattal5.bmp";
	char *image_fusion = "./data/fattal_3_5_fusion.bmp";
	T_Bmp_File bmp_file_1;
	T_Bmp_File bmp_file_2;
	T_Bmp_File bmp_file_fusion;
	int begin;
	int finish;

	{
		memset(&bmp_file_1, 0, sizeof(T_Bmp_File));
		memset(&bmp_file_2, 0, sizeof(T_Bmp_File));
		memset(&bmp_file_fusion, 0, sizeof(T_Bmp_File));
	}

	{
		bmp_file_1 = read_bmp(image_1);
		bmp_file_2 = read_bmp(image_2);
		begin = clock();
		bmp_file_fusion = fusion_image(&bmp_file_1, &bmp_file_2);
		finish = clock();
	}

	write_bmp(image_fusion, &bmp_file_fusion);


	{
		free(bmp_file_1.p_bmp_buffer);
		bmp_file_1.p_bmp_buffer = NULL;
		free(bmp_file_2.p_bmp_buffer);
		bmp_file_2.p_bmp_buffer = NULL;
		free(bmp_file_fusion.p_bmp_buffer);
		bmp_file_fusion.p_bmp_buffer = NULL;
	}

	printf("Time for fusion: %f (s).\n", (float)(finish - begin) / 1000);

}

