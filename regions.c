#include "regions.h"
#include <stdio.h>
#include <assert.h>
#include "table.h"
#include <string.h>


Boolean rinit( const char *region_name, r_size_t region_size ) {

} // rinit
  

Boolean rchoose( const char *region_name ) {

} // rchoose


const char *rchosen() {

} // rchosen


void *ralloc( r_size_t block_size ) {

} // ralloc


r_size_t rsize( void *block_ptr ) {

} // rsize


Boolean rfree( void *block_ptr ) {

} // rfree


void rdestroy( const char *region_name ) {

} // rdestroy


void rdump() {

} // rdump
