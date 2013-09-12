/* 
 * File:   main.c
 * Author: orachun
 *
 * Created on September 12, 2013, 2:15 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "property.h"
#include "difsys_meta_file.h"

#define CONF_FILE "difsys.conf"

PROPERTY* p;

/*
 * 
 */
int main(int argc, char** argv) 
{
    p = prop_load(CONF_FILE, 10);
    prop_list(p, stdout);
    
    META_FILE mf;
    mf.name = "name.txt";
    mf.path = "/name.txt";
    mf.size = 100;
    mf.piece_count = 1;
    mf.pieces = (META_FILE_PIECE**)calloc(1, sizeof(META_FILE_PIECE*));
    mf.pieces[0] = (META_FILE_PIECE*)malloc(sizeof(META_FILE_PIECE));
    mf.pieces[0]->meta_file = &mf;
    mf.pieces[0]->offset = 0;
    mf.pieces[0]->length = 100;
    mf.pieces[0]->name = "name.txt.0.100";
    
    if(save_meta_file(&mf) == 1)
    {
        printf("finished");
    }
    else
    {
        printf("error");
    }
    
    return (EXIT_SUCCESS);
}

