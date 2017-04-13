#include "regions.h"
#ifndef _TABLE_H
#define _TABLE_H

// Linked list chunks of block definition
typedef struct CHUNK Chunk;

struct CHUNK {
    void* startLoc;
    r_size_t blockSize;
    Chunk *next;
};

// Linked list node definition
typedef struct NODE Node;

struct NODE
{
    char *string;
    r_size_t size;
    void  *memory;
    Node *next;
    Chunk *head;
};

// add a node for storing the address of the block pointer
Boolean insertTracker( r_size_t block_size, void *address  );

// add an element to the beginning of the linked list
Boolean insert( char const * const new_string, r_size_t size );

// remove an element with the given string
Boolean delete( char const * const target );

// tells us whether or not the given string is in the list
Boolean search( char const * const target );


// gets the data at the current traversal node and increments the traversal
Node * nextNode();

// searches for enough continguoius bytes in the region
void* allocBlock( r_size_t block_Required, void *pointer );

// putting the toys away by cleaning up
Boolean cleanInnerList( Node *regionNode);

// starts a list traversal by getting the data at top
Node * getFirstNode();

// traverses the inner list
void innerListLoop( r_size_t size, Chunk **header);

// returnrs the curr node of the outer list
Node *getCurr();

// returnrus the head node of the inner list
Chunk *getTopTracker();

// delets a node in the inner list
Boolean deletePtr( void* target );

// returns the block size
r_size_t bytesSearch( void *ptr );

Node *getToHead( char const * const target );

void val_Mem_Region(Node *ptr);


#endif