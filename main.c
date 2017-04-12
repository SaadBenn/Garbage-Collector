//-----------------------------------------
// NAME: Saad B Mushtaq
// STUDENT NUMBER: 7785430
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: assignment 4
// 
// REMARKS: Test cases for the memory management
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "regions.h"

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------
static int assertionCount = 0;
static int errorCount = 0;

//-------------------------------------------------------------------------------------
// Prototypes
//-------------------------------------------------------------------------------------
void testNull( char *check );
void testNotNull( char *check );
void testBoolean( Boolean result );


//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------
int main() {

	Boolean rc;
  //int *ia;
  char *ca1, *ca2, *ca3, *ca4, *ca32, *ca42, *ca100;
  //char *fail;
  
   rc = rinit("hello", 1024); 
  testBoolean( rc );

  /*********************************************************
   * Check if it creates blocks equal to the buffer size 
   *********************************************************/
  ca1 = ralloc( 1 ); // 8
  testNotNull( ca1 );
  
  ca2 = ralloc( 23 ); // 24
  testNotNull( ca2 );

  ca3 = ralloc( 800 ); 
  testNotNull( ca3 );

  ca4 = ralloc( 192 );
  testNotNull( ca4 );

  /*********************************************************
   * Adding a block while the buffer has already been filled  
   *********************************************************/
  ca1 = ralloc( 1 );
  testNull( ca1 ); // 1025?
    
  ca1 = ralloc( 200 );
  testNull( ca1 );

  /*********************************************************
   * Asking for a block of size 0 
   *********************************************************/
  ca2 = ralloc ( 0 ); // size 0 not allowed
  testNull( ca2 );

  /*********************************************************
   * Adding a new memory region   
   *********************************************************/
  rc = rinit("world", 20 ); // should be processed into 24
  testBoolean( rc );

  /*********************************************************
   * Allocating a block of size 24  
   *********************************************************/
  ca1 = ralloc( 24 );
  testNotNull( ca1 );

  /*********************************************************
   * Asking for some more space 
   *********************************************************/
  ca2 = ralloc( 1 );
  testNull( ca2 );

  /*********************************************************
   * Switching regions
   *********************************************************/
  rc = rchoose( "hello");
  testBoolean( rc );

  /*********************************************************
   * Checking rchosen function
   *********************************************************/
  printf("\nChosen: %s\n", rchosen()); // hello

  /*********************************************************
   * Testing rdump for the details of the blocks and regions
   *********************************************************/
  rdump();

  /*********************************************************
   * Checking to see if we are still in the rchoose region
   *********************************************************/
  printf("\n\nChosen: %s\n", rchosen()); // hello
  

  /*********************************************************
   * Checking rdestroy function
   *********************************************************/
  rdestroy( "hello");

  /********************************************************
   * Testing rdump when a block is deleted
   ********************************************************/
  rdump();

  /*********************************************************
   * Destroying the last node
   *********************************************************/
  rdestroy("world");
  
  /*********************************************************
   * Testing if there is any output for the blocks
   *********************************************************/
  rdump();

  /********************************************************
   * Adding a memory region of size 0  
   ********************************************************/
  rc = rinit("Java", 0 ); // 
  testBoolean( !rc );

  /*********************************************************
   * Adding some more memory regions 
   *********************************************************/
  rc = rinit("Ruby", 1 ); // should be processed into 8
  testBoolean( rc );

  rc = rinit("C++", 300 ); // should be processed into 24
  testBoolean( rc );

  rc = rinit("Python", 100 ); // should be processed into 24
  testBoolean( rc );

  /*********************************************************
   * Printing out all regions with no blocks allocated
   *********************************************************/
  rdump();

  /*********************************************************
   * Choosing a particular region and allocating blocks
   *********************************************************/
  rc = rchoose( "Ruby");
  testBoolean( rc );

  ca100 = ralloc( 4 ); // 8 
  testNotNull( ca100 );
  
  ca2 = ralloc( 4 );  // same block size
  testNull( ca2 );


  /*********************************************************
   * Allocating blocks in other regions
   *********************************************************/
  rc = rchoose( "C++");
  testBoolean( rc );

  ca32 = ralloc( 288 );
  testNotNull( ca3 );
  ca42 = ralloc( 16 );
  testNotNull( ca3 );
  ca4 = ralloc( 1 );
  testNull( ca4 );

  rc = rchoose( "Python");
  testBoolean( rc );

  ca1 = ralloc( 4 );
  testNotNull( ca1 );
  ca2 = ralloc( 10 );
  testNotNull( ca2 );
  ca3 = ralloc( 32 );
  testNotNull( ca3 );
  ca4  = ralloc( 60 );
  testNull( ca4 );

  /*********************************************************
   * Printing out the structure with diffrent blocks
   *********************************************************/
  rdump();

  /*********************************************************
   * Testing rfree routine
   *********************************************************/
  rc = rfree( ca3 );
  testBoolean( rc );
  ca4  = ralloc( 60 );
  testNotNull( ca4 );
  rdump();

  /*********************************************************
   * Testing rfree routine for a size that is not there
   *********************************************************/
  rc = rfree( ca4 - 20 );
  testBoolean( !rc );

  /*********************************************************
   * Testing rfree routine for a size that is there
   *********************************************************/
  rc = rfree( ca2 );
  testBoolean( rc );

  /*********************************************************
   * Testing rchoose routine for a region that is not there
   *********************************************************/
  rc = rchoose("c++");
  testBoolean( !rc );

  /*********************************************************
   * Testing to see if rchosen points to the corect region
   *********************************************************/
  printf("\n\nChosen: %s\n", rchosen());
  //rdump();
  /*********************************************************
   * Testing rfree for deleting all blocks
   *********************************************************/
  rc = rfree( ca1 );
  testBoolean ( rc );
  
  rc = rfree( ca4 );
  testBoolean( rc );

  rc = rfree( ca3 );
  testBoolean( !rc );

  rdump();

  /*********************************************************
   * Testing rfree so that it deletes the blocks allocated
   *********************************************************/
  rc = rchoose( "C++");
  testBoolean( rc );

  rc = rfree( ca32 );
  testBoolean( rc );

  rc = rfree( ca42 );
  testBoolean( rc );

  rdump();

  /*********************************************************
   * Testing rfree for a block that is not there
   *********************************************************/
  rc = rfree( ca42+1 );
  testBoolean( !rc );



  rc = rinit("Swift", 64 ); // should be processed into 8
  testBoolean( rc );

  ca1 = ralloc( 28 );
  testNotNull( ca1 );
  ca2 = ralloc( 10 );
  testNotNull( ca2 );

  ca3 = ralloc( 8 );
  testNotNull( ca1 );
  rdump();


  /*********************************************************
   * Destroying all regions
   *********************************************************/
  rdestroy( "C++");
  rdestroy( "Python" );

  rc = rfree( ca1 );
  testBoolean( rc );

  rc = rfree( ca2 );
  testBoolean( rc );

  rc = rfree( ca3 );
  testBoolean( rc );

  rdestroy( "Swift" );

  rc = rchoose( "Ruby");
  testBoolean( rc );

  //printf("\nChosen: %s\n", rchosen());

  rc = rfree( ca100 ); // pointer to Ruby's block
  testBoolean( rc );

  rdestroy( "Ruby");
  

  rdump();

  /*********************************************************
   * Choosing a region that is destroyed
   *********************************************************/
  ca1 = ralloc( 28 );
  testNull( ca1 );
  
  rc = rchoose( "Ruby");
  testBoolean( !rc );


  /*********************************************************
   * Choosing a region's name that is destroyed
   *********************************************************/
  rc = rinit("Swift", 200 ); // should be processed into 8
  testBoolean( rc );

  ca1 = ralloc( 100 );
  testNotNull( ca1 );

  rdump();

  rc = rfree( ca1 ); 
  testBoolean( rc );

  rdump();

  rdestroy( "Swift");
  rdump();


  fprintf(stderr,"\nEnd of processing.\n");

  return EXIT_SUCCESS;
}


void testNull( char *check ) {
  
  if( check == NULL ) {
    
    assert( check == NULL );
    printf("\033[32m");
    printf("(✓) Passed %d assertions without errors", ++assertionCount);
    printf("\033[0m");
    printf("\n");
  
  } else {

    assert( check != NULL );
    printf("\033[31m");
    printf("(✖) Failed on %d of %d assertions", ++errorCount, assertionCount);
    printf("\033[0m");
    printf("\n");

  }

} // end TestNull



void testNotNull( char *check ) {
 
  if( check != NULL ) {

    assert( check != NULL );
    printf("\033[32m");
    printf("(✓) Passed %d assertions without errors", ++assertionCount);
    printf("\033[0m");
    printf("\n");
  
  } else {
    
    assert( check == NULL );
    printf("\033[31m");
    printf("(✖) Failed on %d of %d assertions", ++errorCount, ++assertionCount);
    printf("\033[0m");
    printf("\n");
  }

} // testNotNull


void testBoolean( Boolean result ) {

  if( result ) {

    assert( result );
    printf("\033[32m");
    printf("(✓) Passed %d assertions without errors", ++assertionCount);
    printf("\033[0m");
    printf("\n");
  
  } else {
    
    assert( !result );
    printf("\033[31m");
    printf("(✖) Failed on %d of %d assertions", ++errorCount, ++assertionCount);
    printf("\033[0m");
    printf("\n");
  }

} // testBoolean