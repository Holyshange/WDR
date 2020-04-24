#ifndef __BMP_RW_H__
#define __BMP_RW_H__

#ifndef __BMP_STRUCT_H__
#include "bmp_struct.h"
#endif

#ifndef __STDIO_H__
#define __STDIO_H__
#include <stdio.h>
#endif

#ifndef __STDLIB_H__
#define __STDLIB_H__
#include <stdlib.h>
#endif

#ifndef __ASSERT_H__
#define __ASSERT_H__
#include <assert.h>
#endif


T_Bmp_File read_bmp(const char *file_name);

void write_bmp(const char *file_name, T_Bmp_File *bmp_file);


#endif

