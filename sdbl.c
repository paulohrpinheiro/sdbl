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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdbl.h"

int SDBL_errno;

void _clean_up_file_s(SDBL_file_s *finfo) {
    if(finfo!=NULL) {
        if(NULL!=finfo->filename) {
            free(finfo->filename);
        }

        if(NULL!=finfo->file_handle) {
            fclose(finfo->file_handle);
        }

        free(finfo);
    }
}

SDBL_file_s *SDBL_open(const char *fname, int data_len)
{
	FILE *fh;
	SDBL_file_s *finfo;

	if(NULL==(fh=fopen(fname,"r+"))) {
		if(NULL==(fh=fopen(fname,"w+"))) {
            SDBL_errno = SDBL_CREATE_FILE_ERROR;
			return(NULL);
		}
	}

	finfo=(SDBL_file_s *)malloc(sizeof(SDBL_file_s));

	if(NULL==finfo) {
		fclose(fh);
        SDBL_errno = SDBL_MALLOC_ERROR;
		return(NULL);
	}

	finfo->filename=(char *)malloc(strlen(fname)+1);

	if(NULL==finfo->filename) {
		_clean_up_file_s(finfo);
        SDBL_errno = SDBL_MALLOC_ERROR;
		return(NULL);
	}

	strcpy(finfo->filename,fname);
	finfo->file_handle = fh;
    finfo->data_len = data_len;
	finfo->recno = 0;

    SDBL_errno = SDBL_OK;
	return(finfo);
}

int SDBL_close(SDBL_file_s *fh)
{
    _clean_up_file_s(fh);
    return(SDBL_errno = SDBL_OK);
}

int SDBL_put(SDBL_file_s *finfo, SDBL_key_t key, char *data)
{
    if(SDBL_NEW_RECORD==key) {
        fseek(finfo->file_handle,0,SEEK_END);
    }
    else {
        fseek(finfo->file_handle,key*finfo->data_len,SEEK_SET);
    }

    if(!fwrite(data,finfo->data_len,1,finfo->file_handle)) {
        return(SDBL_errno = SDBL_WRITE_ERROR);
    }

    return(SDBL_errno = SDBL_OK);
}

char *SDBL_get(SDBL_file_s *finfo, SDBL_key_t key)
{
    char *data;

    if(-1==fseek(finfo->file_handle,key*finfo->data_len,SEEK_SET)) {
        SDBL_errno = SDBL_SEEK_ERROR;
        return(NULL);
    }

    data = (char *)malloc(sizeof(char)*(finfo->data_len+1));

    if(NULL==data) {
        SDBL_errno = SDBL_MALLOC_ERROR;
        return(NULL);
    }

    if(!fread(data,finfo->data_len,1,finfo->file_handle)) {
        SDBL_errno = SDBL_READ_ERROR;
        free(data);
        return(NULL);
    }

    SDBL_errno = SDBL_OK;
    return(data);
}

int SDBL_next(SDBL_file_s *finfo)
{
    if(!fseek(finfo->file_handle,finfo->data_len,SEEK_CUR)) {
        return(SDBL_errno = SDBL_SEEK_ERROR);
    }

    return(SDBL_errno = SDBL_OK);
}

int SDBL_prev(SDBL_file_s *finfo)
{
    long cur;

    cur = ftell(finfo->file_handle);

    if(!fseek(finfo->file_handle,cur-finfo->data_len,SEEK_CUR)) {
        return(SDBL_errno = SDBL_SEEK_ERROR);
    }

    return(SDBL_errno = SDBL_OK);
}

int SDBL_top(SDBL_file_s *finfo)
{
    if(!fseek(finfo->file_handle,0,SEEK_SET)) {
        return(SDBL_errno = SDBL_SEEK_ERROR);
    }

    return(SDBL_errno = SDBL_OK);
}

int SDBL_bottom(SDBL_file_s *finfo)
{
    if(!fseek(finfo->file_handle,0,SEEK_END)) {
        return(SDBL_errno = SDBL_SEEK_ERROR);
    }

    return(SDBL_errno = SDBL_OK);
}

