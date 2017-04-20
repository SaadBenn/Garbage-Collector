//-----------------------------------------
// NAME: Saad B Mushtaq
// STUDENT NUMBER: 7785430
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: assignment 4
// 
// REMARKS: regions implementation

#include "regions.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "table.h"
#include <string.h>

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------
Node *current = NULL;
extern Chunk *topTracker;

// FUNCTIONS
//-------------------------------------------------------------------------------------
void val_Mem_Region(Node *ptr)
{
  assert(NULL != ptr);
  assert(NULL != ptr->string);
  assert(NULL != ptr->memory);
  
  assert(ptr->size > 0);
}


/**
 * @brief      creates a region within the memory
 *
 * @param[in]  region_name  The region name
 * @param[in]  region_size  The region size
 *
 * @return     { true if successful }
 */
Boolean rinit( const char *region_name, r_size_t region_size ) {
    
    Boolean rc = false;
    
    if ( region_size > 0 ) {
        assert( region_size > 0);
        region_size = (region_size + 7) - ((region_size + 7) % 8); // round up
        if( region_name != NULL ) {
            assert( region_name != NULL );
            Boolean result = search( region_name );
        
            if ( !result ) {
                assert( !result);
                Boolean resIn = insert( region_name, region_size );
            
                if( resIn ) {
                    assert( resIn );
                    rc = true;
                    Boolean rch = rchoose( region_name );
                    assert( rch );
                    val_Mem_Region( current ); // invariant
                }
            }
        }
    }
    
    return rc;
    
} // rinit


/**
 * @brief      Choose a previously-initialized memory region 
 * for subsequent ralloc, rsize, and rfree calls
 *
 * @param[in]  region_name  The region name
 *
 * @return     { true if successful }
 */
Boolean rchoose( const char *region_name ) {
    Boolean check = false;
    
    if( region_name ) {
        assert( region_name != NULL );
        check = search( region_name );
    
    
        if ( check ) {
            assert( check );
            current = getCurr();
            if( current ) {
                topTracker = current->head;
                assert( current );
                val_Mem_Region( current ); // invaraint
            }
        }
    }
    
    return check;
    
} // rchoose


/**
 * @brief      Return the name of the currently-chosen region, 
 * or NULL if no region is currently chosen.
 *
 * @return     { the name of the region }
 */
const char *rchosen() {
    
    const char* name = NULL;
    
    Node *curr = current;
    
    if( curr ) {
        assert( curr != NULL );
        name = curr->string;
        val_Mem_Region( curr );
    }
    
    return name;
    
} // rchosen

/**
 * @brief      Allocate a block that is the given number of bytes 
 * large from the currently-chosen region.
 *
 * @param[in]  block_size  The block size
 *
 * @return     { pointer to the block or NULL }
 */
void *ralloc( r_size_t block_size ) {
    void * ptr = NULL;
    
    block_size = (block_size + 7) - ((block_size + 7) % 8); // round up
    
    if( block_size > 0 && current != NULL && block_size <= current->size) {
        assert( block_size > 0 );
        assert( block_size <= current->size );
        
        ptr = allocBlock(block_size, ptr);
        val_Mem_Region( current ); // invariant
    }
    
    
    return ptr;
    
} // ralloc

/**
 * @brief      Find out how many bytes the block of memory pointed to by 
 * the pointer is, in the currently-chosen region.
 *
 * @param      block_ptr  The block pointer
 *
 * @return     { number of bytes in current block }
 */
r_size_t rsize( void *block_ptr ) {
    
    r_size_t size = 0;
    current = getCurr();
    if( block_ptr && current ) {
        assert( block_ptr );
        size = bytesSearch(block_ptr);
    
        assert( size >= 0 );
    }
    
    return size;
    
} // rsize

/**
 * @brief      Frees the block identified by the given 
 * pointer in the currently-chosen region.
 *
 * @param      block_ptr  The block pointer
 *
 * @return     { returns false on error }
 */
Boolean rfree( void *block_ptr ) {
    Boolean result = false;
    if( current != NULL && current->head ) {
        val_Mem_Region( current );
        result = deletePtr(block_ptr);
        val_Mem_Region( current );
    }
    
    return result;
    
} // rfree


/**
 * @brief      Destroy the region with the 
 * given name, freeing all memory associated with it
 *
 * @param[in]  region_name  The region name
 */
void rdestroy( const char *region_name ) {
    //Boolean result  = cleanInnerList();
    if( region_name ) {
        Node *ourRegion = getToHead( region_name );
        if( ourRegion ) {
            Boolean result = cleanInnerList( ourRegion );
    
            if( ourRegion && result ) {
                assert( ourRegion );
                assert( result );
                delete( region_name );
            }
        }
    }
} // rdestroy



void rdump() {
    
    Node *traverseN = getFirstNode();
    char *regionName = NULL;
    Chunk *header = NULL;
    
    if( traverseN ) {
        val_Mem_Region( traverseN );
        assert( traverseN != NULL );
        
        printf("\033[44m");
        printf("\x1B[33m");
        printf("\n%s", "Printing data structure.");
        printf("\033[0m");
        regionName = traverseN->string;
        
        printf("\n%s\n", "---------------------------------------------------------" );
        printf("Region's name: %s\n", traverseN->string );
        printf("Region's size: %d\n\n", traverseN->size );
        
        if( traverseN->head ) {
            header = traverseN->head;
            innerListLoop(traverseN->size, &header);
        } else {
            printf("\nPercent of memory free is %6.2f%%\n", 100.0);
        }
        
        
        traverseN = nextNode();
        
        while( traverseN ) {
            val_Mem_Region( traverseN );
            assert( traverseN != NULL );
            
            regionName = traverseN->string;
            header = traverseN->head;
            //topTracker = traverseN->head;
            //rchoose(regionName);
            
            printf("\n%s\n", "---------------------------------------------------------" );
            printf("Region's name: %s\n", traverseN->string );
            printf("Region's size: %d\n\n", traverseN->size );
            innerListLoop(traverseN->size, &header);
            //printf("%s\n", "---------------------------------------------------------" );
            
            traverseN = nextNode();
            
        }
        
    } else {
        printf("\n%s\n", "---------------------------------------------------------" );
        //printf("\n%s\n", "No regions added folks!" );
    }
} // rdump
