/*
 * Copyright (c) 2008 Paulo Henrique Rodrigues Pinheiro <ppinheiro@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __SDBL_H__
#define __SDBL_H__

typedef int SDBL_status_t;
typedef unsigned long SDBL_key_t;
typedef unsigned long SDBL_record_size_t;

extern int SDBL_errno;

enum SDBL_errors_e {
	SDBL_OK,
    SDBL_MALLOC_ERROR,
	SDBL_CREATE_FILE_ERROR,
    SDBL_WRITE_ERROR,
    SDBL_SEEK_ERROR,
    SDBL_READ_ERROR,
	SDBL_ERROR
};

#define SDBL_NEW_RECORD (-1)

typedef struct {
	char *filename;
	unsigned int data_len;
	FILE *file_handle;
	SDBL_key_t recno;
} SDBL_file_s;

SDBL_file_s *SDBL_open(const char *, int);
int SDBL_close(SDBL_file_s *);

int SDBL_put(SDBL_file_s *file, SDBL_key_t key, char * data);
char *SDBL_get(SDBL_file_s *file, SDBL_key_t key);

int SDBL_next(SDBL_file_s *);
int SDBL_prev(SDBL_file_s *);
int SDBL_top(SDBL_file_s *);
int SDBL_bottom(SDBL_file_s *);

#endif

