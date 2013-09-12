#include "difsys_meta_file.h"
#include "global.h"

#include <stdio.h>

META_FILE* get_meta_file(char* metafilepath)
{
    
}
int save_meta_file(META_FILE* mf)
{
    FILE* fp;
    char path[256];
    sprintf(path, "%s%s.meta", prop_get(p, PROP_META_FS_ROOT), mf->path);
    fp = fopen(path, "w");
    if(fp == NULL)
    {
        return -1;
    }
    else
    {
        fprintf(fp, "%s\n%ld\n", mf->path, mf->size);
        int i;
        for(i=0;i<mf->piece_count;i++)
        {
            META_FILE_PIECE* mp = mf->pieces[i];
            fprintf(fp, "%s;%ld;%ld\n", mp->name, mp->offset, mp->length);
        }
        fclose(fp);
        return 1;
    }
}

void get_meta_file_path(char* filepath, char* metafilepath);