#include "regions.h"
#include <stdio.h>
#include <assert.h>
#include "table.h"
#include <string.h>


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

} // rdump
