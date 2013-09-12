/* 
 * File:   property.h
 * Author: orachun
 *
 * Created on September 12, 2013, 2:53 PM
 */

#ifndef PROPERTY_H
#define	PROPERTY_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdio.h>
    typedef struct _prop_entry_t
    {
        struct _prop_entry_t* next;
        char* key;
        char* val;
    }PROP_ENTRY;
    
    typedef struct
    {
        PROP_ENTRY* head;
        PROP_ENTRY* tail;
    }PROP_ENTRY_LIST;
    
    typedef struct
    {
        PROP_ENTRY_LIST** _table;
        int _table_size;
    } PROPERTY;
    
    PROPERTY* prop_load(char* prop_file, int table_size);
    char* prop_get(PROPERTY* p, char* key);
    int prop_set(PROPERTY* p, char* key, char* val);
    void prop_unset(PROPERTY* p, char* key);
    void prop_destroy(PROPERTY* p);
    void prop_list(PROPERTY*p , FILE* f);

#ifdef	__cplusplus
}
#endif

#endif	/* PROPERTY_H */

