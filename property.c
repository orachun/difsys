#include "property.h"
#include "helper.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


PROPERTY* _prop_create(int size)
{
    PROPERTY* p = NULL;
    p = (PROPERTY*)malloc(sizeof(PROPERTY));
    if(p == NULL)
    {
        return NULL;
    }
    p->_table_size = size;
    p->_table = (PROP_ENTRY_LIST**)calloc(size, sizeof(PROP_ENTRY_LIST));
    if(p->_table == NULL)
    {
        prop_destroy(p);
        return NULL;
    }
    return p;
}
PROP_ENTRY* _prop_get_entry(PROPERTY* p, char* key)
{
    if(key == NULL)
    {
        return NULL;
    }
    int hash = _str_hash(key);
    PROP_ENTRY_LIST* list = p->_table[hash%p->_table_size];
    PROP_ENTRY* c;
    if(list == NULL)
    {
        return NULL;
    }
    for(c = list->head;c != NULL; c = c->next)
    {
        if(strcmp(c->key, key) == 0)
        {
            return c;
        }
    }
    return NULL;
}

PROPERTY* prop_load(char* prop_file, int table_size)
{
    FILE* fp = fopen(prop_file, "r");
    if(fp == NULL)
    {
        return NULL;
    }
    else
    {
        PROPERTY* p = _prop_create(table_size);
        char buffer[256];
        if(p == NULL)
        {
            return NULL;
        }
        
        while(fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            char* key;
            char* val;
            char* line;
            char* equal;
            PROP_ENTRY* pe;
            line = trim(buffer);
            if(line[0] == '\0' || line[0] == '#')
            {
                continue;
            }
            for(equal = line;
                    *equal!='\0'&&*equal != '=';
                    equal++);
            if(*equal == '=')
            {
                *equal = '\0';
                key = trim(line);
                val = trim(equal+1);
                if(prop_set(p, key, val) != 1)
                {
                    prop_destroy(p);
                    return NULL;
                }
            }
        }
        return p;
        
        
        
    }
}
char* prop_get(PROPERTY* p, char* key)
{
    PROP_ENTRY* e = _prop_get_entry(p, key);
    return e == NULL ? NULL : e->val;
}
int prop_set(PROPERTY* p, char* key, char* val)
{
    if(key == NULL)
    {
        return -1;
    }
    else if(val == NULL)
    {
        return -2;
    }
    else
    {
        int hash = _str_hash(key);
        PROP_ENTRY_LIST* list = p->_table[hash%p->_table_size];
        PROP_ENTRY* entry;
        
        entry = _prop_get_entry(p, key);
        if(entry == NULL)
        {
            entry = (PROP_ENTRY*)malloc(sizeof(PROP_ENTRY));
            if(entry == NULL)
            {
                return -3;
            }
            entry->key = strdup(key);
            entry->val = strdup(val);
            entry->next = NULL;
            if(list == NULL)
            {
                list = (PROP_ENTRY_LIST*)malloc(sizeof(PROP_ENTRY_LIST));
                if(list == NULL)
                {
                    return -4;
                }
                list->head = NULL;
                list->tail = NULL;
                p->_table[hash%p->_table_size] = list;
            }
            if(list->head == NULL)
            {
                list->head = entry;
            }
            else
            {
                list->tail->next = entry;
            }
            list->tail = entry;
            return 1;       
        }
        else
        {
            free(entry->val);
            entry->val = strdup(val);
            return 1;
        }
    }
}

void prop_unset(PROPERTY* p, char* key)
{
    prop_set(p, key, NULL);
}

int _str_hash(char* str)
{
    int hash = 0;
    char* c;
    for(c = str; *c != '\0'; c++)
    {
        hash = hash * 17 + *c;
    }
    return hash;
}

void prop_destroy(PROPERTY* p)
{
    PROP_ENTRY_LIST* l;
    int i;
    for(i=0;i<p->_table_size;i++)
    {
        PROP_ENTRY* e;
        l = p->_table[i];
        PROP_ENTRY* nextE;
        for(e = l->head;e != NULL; e = nextE)
        {
            nextE = e->next;
            free(e);
        }
        free(l);
    }
    free(p->_table);
    free(p);
}

void prop_list(PROPERTY*p , FILE* f)
{
    int i;
    for(i=0;i<p->_table_size;i++)
    {
        PROP_ENTRY_LIST* l = p->_table[i];
        if(l == NULL) continue;
        PROP_ENTRY* e;
        for(e = l->head;e!=NULL;e = e->next)
        {
            fprintf(f, "%s: %s\n", e->key, e->val);
        }
    }
}

