#include "regions.h"
#include <stdio.h>
#include <assert.h>
#include "table.h"
#include <string.h>

Node *current = NULL;

Boolean rinit( const char *region_name, r_size_t region_size ) {
    
    Boolean rc = false;
    
    if ( region_size > 0 ) {
        assert( region_size > 0);
        region_size = (region_size + 7) - ((region_size + 7) % 8); // round up
        
        Boolean result = search( region_name );
        
        if ( !result ) {
        	assert( !result);
            Boolean resIn = insert( region_name, region_size );
            
            if( resIn ) {
            	assert( resIn );
                rc = true;
                Boolean rch = rchoose( region_name );
                assert( rch );
            }
        }
    }
    
    return rc;
    
} // rinit
  

Boolean rchoose( const char *region_name ) {
    
    Boolean check = search( region_name );
    Boolean result = true;
    
    current = getCurr();
    //topTracker = getTopTracker();
    topTracker = current->head;
    if( check && current ) {
        assert( check );
        assert( current );
        
    } else {
        result = false;
    }
    
    return result;
    
} // rchoose


const char *rchosen() {
    
    const char* name = NULL;
    
    Node *curr = getFirstNode();
    
    if( curr ) {
    	assert( curr != NULL );
        name = curr->string;
    }
    
    return name;
    
} // rchosen


void *ralloc( r_size_t block_size ) {
    void * ptr = NULL;
    
    block_size = (block_size + 7) - ((block_size + 7) % 8); // round up
    
    if( block_size > 0 && block_size <= current->size) {
        assert( block_size > 0 );
        assert( block_size <= current->size );
        
        ptr = allocBlock(block_size, ptr);
        
    }
    
    
    return ptr;
    
} // ralloc


r_size_t rsize( void *block_ptr ) {

} // rsize


Boolean rfree( void *block_ptr ) {

} // rfree


void rdestroy( const char *region_name ) {
    Boolean result  = cleanInnerList();
    
    if( result ) {
    	assert( result );
    	delete( region_name );
    }
} // rdestroy


void rdump() {
    
    Node *traverseN = getFirstNode();
    char *regionName = NULL;
    
    if( traverseN ) {
    	assert( traverseN != NULL );

        printf("\033[44m");
        printf("\x1B[33m");
        printf("\n%s", "Printing data structure.");
        printf("\033[0m");
        regionName = traverseN->string;
        rchoose(regionName);
        printf("\n%s\n", "---------------------------------------------------------" );
        printf("Region's name: %s\n", traverseN->string );
        printf("Region's size: %d\n\n", traverseN->size );
        innerListLoop();
        
        traverseN = nextNode();
        
        while( traverseN ) {
            assert( traverseN != NULL );

            regionName = traverseN->string;
            rchoose(regionName);
            
            printf("\n%s\n", "---------------------------------------------------------" );
            printf("Region's name: %s\n", traverseN->string );
            printf("Region's size: %d\n\n", traverseN->size );
            innerListLoop();
            printf("%s\n", "---------------------------------------------------------" );
            
            traverseN = nextNode();
            
        }
        
    } else {
    	
        printf("\n%s\n", "No regions added folks!" ); 
    }
} // rdump
