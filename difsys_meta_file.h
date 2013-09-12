/* 
 * File:   difsys_meta_file.h
 * Author: orachun
 *
 * Created on September 12, 2013, 2:20 PM
 */

#ifndef DIFSYS_META_FILE_H
#define	DIFSYS_META_FILE_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct _meta_file_t META_FILE;
    typedef struct _meta_file_piece_t META_FILE_PIECE;
    
    struct _meta_file_t
    {
        char* path;
        char* name;
        long size;
        int piece_count;
        META_FILE_PIECE** pieces;
    };
    
    struct _meta_file_piece_t
    {
        META_FILE* meta_file;
        char* name;
        long offset;
        long length;
    };
    
    META_FILE* get_meta_file(char* metafilepath);
    int save_meta_file(META_FILE* mf);
    void get_meta_file_path(char* filepath, char* metafilepath);


#ifdef	__cplusplus
}
#endif

#endif	/* DIFSYS_META_FILE_H */

