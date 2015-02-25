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
#include "sdbl.h"

#define LEN_RECORD 30

int main (void)
{
    char str_to_put[LEN_RECORD+1];
    SDBL_file_s *db;
    int i;

    db = SDBL_open("test.sdbl",LEN_RECORD);

    if(NULL==db) {
        fprintf(stderr,"can't open file. [err=%d]\n",SDBL_errno);
        exit(EXIT_FAILURE);
    }

    for(i=0;i<10;i++) {
        sprintf(str_to_put,"%*d",LEN_RECORD,i);

        if(SDBL_OK!=SDBL_put(db,SDBL_NEW_RECORD,str_to_put)) {
            fprintf(stderr,"error (%d) to write str [%s]\n",SDBL_errno,str_to_put);
            exit(EXIT_FAILURE);
        }
    }

    for(i=0;i<10;i=i+2) {
        sprintf(str_to_put,"%*d",LEN_RECORD,i*10);

        if(SDBL_OK!=SDBL_put(db,i,str_to_put)) {
            fprintf(stderr,"error (%d) to write str [%s]\n",SDBL_errno,str_to_put);
            exit(EXIT_FAILURE);
        }
    }

    puts(SDBL_get(db,3));
    SDBL_close(db);
}

