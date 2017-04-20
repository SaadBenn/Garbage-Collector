//-----------------------------------------
// NAME: Saad B Mushtaq
// STUDENT NUMBER: 7785430
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: assignment 4
//
// REMARKS: table

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "table.h"
#include "regions.h"


//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------

Node *top = NULL;
Node *curr = NULL;
static int numNodes = 0;
static int trackerNumNodes = 0;
Chunk *topTracker = NULL;
Chunk *currTracker = NULL;

// used to track where we are for the list traversal methods
static Node *traverseNode = NULL;


//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

// invariant
static void checkState( char const * const string);
void valInnerList(Chunk *block);

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

/******************************************************
 * Validates the string and the linked list
 *******************************************************/
static void checkState( char const * const string) {
    
    //assert( string != NULL );
    assert( '\0' == string[strlen( string )] );
    assert( numNodes >= 0 );
    
    if ( numNodes == 0 ) {
        
        assert( top == NULL );
        
    } else if ( numNodes == 1 ) {
        
        assert( top->next == NULL );
        
    } else {
        
        assert( top != NULL );
        //   assert( top->next != NULL );
    }
    
} // checkState

void valInnerList(Chunk *block) {
    assert( block->blockSize > 0 );
    assert( block->startLoc != NULL );
}


/****************************************************
 *add an element to the beginning of the linked list
 @new-string word to be added
 *@returns true if string inserted
 ****************************************************/
Boolean insert( char const * const new_string, r_size_t size )
{
    checkState( new_string ); // invariant
    
    Boolean rc = true;
    
    Node *newNode = NULL;
    
    newNode = (Node *)malloc( sizeof( Node ) );
    assert( newNode ); // checking that malloc actually allocated memory
    
    newNode->next = top;
    assert( newNode->next == top );
    top = newNode;
    
    // note that we need to have space for the string as well!
    newNode->string = (char *)malloc( strlen(new_string) + 1 );
    assert( newNode->string ); // post condition
    
    if ( newNode->string ) {
        strcpy( newNode->string, new_string );
        newNode->size = size;
        
        newNode->memory = (char *)malloc(size); // set to 0
        assert( newNode->memory );
        newNode->head = NULL;
        
        if( !(newNode->memory) ) {
            free(newNode->string);
            rc = false;
            
        } else {
            numNodes++;
        }
        
    } else {
        
        free( newNode );
        rc = false;
    }
    
    checkState( newNode->string ); // invariant
    
    return rc;
} // insert



/****************************************************
 *tells us whether or not the given string is in the list
 @target word to be added
 @returns true if item was found
 ****************************************************/
Boolean search( char const * const target )
{
    checkState( target ); // invariant
    
    Boolean found = false;
    curr = top;
    assert( curr == top );
    
    while ( curr != NULL && !found )
    {
        assert( curr != NULL );
        
        if ( strcmp( target, curr->string ) == 0 )
        {
            assert( strcmp(target, curr->string) == 0 );
            found = true;
        }
        
        else
        {
            assert( strcmp(target, curr->string) != 0 );
            curr = curr->next;
        }
    }
    
    return found;
} // search



/****************************************************
 *remove an element with the given string
 @target word to be added
 *@returns true item was deleted
 ****************************************************/
Boolean delete( char const * const target )
{
    
    checkState( target );
    
    Boolean deleted = false;
    curr = top;
    assert( curr == top );
    
    Node *prev = NULL;
    assert( prev == NULL );
    
    while ( curr != NULL && strcmp( target, curr->string ) != 0 )
    {
        assert( curr != NULL );
        assert( strcmp( target, curr->string) != 0 );
        
        prev = curr;
        curr = curr->next;
    }
    
    
    if ( curr != NULL )
    {
        assert( curr != NULL );
        
        if ( prev != NULL ) {
            
            assert( prev != NULL );
            prev->next = curr->next;
            topTracker = prev->head;
            
        } else {
            
            top = curr->next;
            if(top)
                topTracker = top->head;
        }
        
        if( curr->string != NULL ) {
            
            if( curr != NULL ) {
                
                free( curr->memory);
                free( curr->string );
            } // end innner if
            
            free( curr );
        } // end outer if
        
        
        curr = NULL;
        assert( curr == NULL );
        
        deleted = true;
        numNodes--;
    }
    
    return deleted;
    
} // end delete function


/****************************************************
 *starts a list traversal by getting the data at top
 *return string
 ****************************************************/
Node * getFirstNode()
{
    
    Node *result = NULL;
    
    if( top != NULL ) {
        
        assert( top != NULL );
        traverseNode = top->next;
        result = top;
    }
    
    return result;
} // end getFirstNode


/****************************************************
 *gets the data at the current traversal node and
 *increments the traversal
 *returns the string if node is not null
 ****************************************************/
Node * nextNode()
{
    Node *cNode = NULL;
    
    // no need to go past the end of the list...
    if ( traverseNode != NULL )
    {
        assert( traverseNode != NULL );
        cNode = traverseNode;
        traverseNode = traverseNode->next;
    }
    
    return cNode;
}

/****************************************************
 *Creates a new node which is ordered
 *@block_size the size of the block required
 *@address the starting address of the block
 *returns the true if insertion is successful
 ****************************************************/
Boolean insertTracker( r_size_t block_size, void *address  ) {
    
    Boolean rc = true;
    
    //create new node
    Chunk *newChunk = (Chunk*)malloc(sizeof(Chunk));
    //check whether node is created or not
    assert( newChunk );
    
    Chunk *temp;
    Chunk *previous;
    
    //Updating different parts of the node
    newChunk->startLoc = address;
    assert( newChunk->startLoc == address );

    newChunk->blockSize = block_size;
    assert( newChunk->blockSize == block_size );

    newChunk->next = NULL;
    
    //checking whether the node created is only node or not
    if (topTracker == NULL)
    {
        assert( topTracker == NULL );
        topTracker = newChunk;
        curr->head = topTracker;
    }
    //If value is less than the value of first node
    else if(address < topTracker ->startLoc)
    {
        newChunk->next = topTracker;
        topTracker = newChunk;
        curr->head = topTracker;
    }
    else
    {
        previous = topTracker;
        temp = topTracker->next;
        
        
        //Go to the position where node is to be inserted
        while(temp != NULL && address > temp->startLoc)
        {
            previous = temp;
            temp = temp->next;
        }
        
        
        //Insert the node at particular position
        if(temp == NULL)
        {
            previous->next = newChunk;
        }
        else
        {
            newChunk->next = temp;
            previous->next = newChunk;
        }
    }
    trackerNumNodes++;
    
    valInnerList( newChunk );
    return rc;
} // insertTracker

/****************************************************
 *Allocates a block of memory inside the buffer
 *@block_Required the size of the chunk
 *@ptr pointer to the block
 *returns a void pointer to the block
 ****************************************************/
void* allocBlock( r_size_t block_Required, void *ptr ) {
    long size = 0;
    Boolean result = false;
    Chunk *traverse = topTracker;
    void * trackingPtr = curr->memory;
    
    while( traverse != NULL && !result ) {
        
        assert( traverse != NULL );
        if( trackingPtr == traverse->startLoc) {
            
            void* startPoint =traverse->startLoc;
            r_size_t bSize = traverse->blockSize;
            
            void* nextFree = startPoint + bSize;
            trackingPtr = nextFree;
            assert( trackingPtr == nextFree );
            if( traverse->next != NULL ) {
                
                void *address = traverse->next->startLoc;
                
                size = address - nextFree;
                //printf("If part %d\n", size);
                
                if( size >= block_Required) {
                    insertTracker(block_Required, nextFree);
                    for(int i = 0; i < block_Required; i++) {
                        *((char*)trackingPtr + i) = '0';
                    }
                    ptr = nextFree;
                    result = true;
                } else {
                    trackingPtr += size;
                }
                
            } else {
                
                size = (curr->memory+curr->size) - trackingPtr;
                //printf("Else part %d\n", size);
                
                if(size >= block_Required) {
                    insertTracker(block_Required, trackingPtr);
                    for(int i = 0; i < block_Required; i++) {
                        *((char*)trackingPtr + i) = '0';
                    }
                    ptr = trackingPtr;
                    result = true;
                } else {
                    trackingPtr += size;
                }
                
            }
        } else {
            size = traverse->startLoc - trackingPtr;
            if(size >= block_Required) {
                insertTracker(block_Required, trackingPtr);
                for(int i = 0; i < block_Required; i++) {
                    *((char*)trackingPtr + i) = '0';
                }
                ptr = trackingPtr;
                result = true;
                
            } else {
                
                if( traverse->next == NULL ) {
                    trackingPtr = traverse->startLoc + traverse->blockSize;
                    size = curr->memory+curr->size - trackingPtr;
                    if(size >= block_Required) {
                        insertTracker(block_Required, trackingPtr);
                        for(int i = 0; i < block_Required; i++) {
                            *((char*)trackingPtr + i) = '0';
                        }
                        ptr = trackingPtr;
                        result = true;
                    }
                    
                }
            }
        }     
        traverse = traverse->next;
        
    }
    
    if( topTracker == NULL ) {
        
        insertTracker( block_Required, curr->memory);
        
        for(int i = 0; i < block_Required; i++) {
            *((char*)curr->memory + i) = '0';
            //*((int*)(current->memory[i])) = 0;
        }
        
        ptr = curr->memory;
    }
    
    return ptr;
} // end allocBlock

/****************************************************
 *deletes a block by traversing the list and 
 *getting the starting pointer
 *@target the target pointer
 *returns true if successful
 ****************************************************/
Boolean deletePtr( void* target )
{
    
    //checkState( target );
    
    Boolean deleted = false;
    Chunk *currN = topTracker;
    assert( currN == topTracker );
    
    Chunk *prev = NULL;
    assert( prev == NULL );
    const char *regionName = rchosen();
    Boolean result = rchoose( regionName );
    
    if ( result ) {
        while ( currN != NULL && (currN->startLoc != target) )
        {
            assert( currN != NULL );
            assert( currN->startLoc != target );
            
            prev = currN;
            currN = currN->next;
        }
        
        
        if ( currN != NULL )
        {
            assert( currN != NULL );
            
            if ( prev != NULL ) {
                
                assert( prev != NULL );
                prev->next = currN->next;
                
            } else {
                
                if( currN->next ) {
                    topTracker = currN->next;
                    
                    if( curr ) {
                        curr->head = currN->next;
                    }
                } else {
                    topTracker = NULL;
                    curr->head = NULL;
                }
                
            }
            
            free( currN );
            currN = NULL;
            assert( currN == NULL );
            deleted = true;
            trackerNumNodes--;
        }
    }
    
    return deleted;
    
} // end delete function

/****************************************************
 *Looks for contiguous bytes in the buffer
 *@ptr to the starting point from which to find bytes
 *returns the contiguous number of  bytes
 ****************************************************/
r_size_t bytesSearch( void *ptr )
{
    r_size_t blockSize = 0;
    Boolean found = false;
    currTracker = topTracker;
    assert( ptr != NULL );
    assert( currTracker == topTracker );
    
    while ( currTracker != NULL && !found )
    {
        assert( currTracker != NULL );
        valInnerList( currTracker );
        if ( currTracker->startLoc == ptr )
        {
            assert( currTracker->startLoc == ptr );
            found = true;
            blockSize = currTracker->blockSize;
        }
        
        else
        {
            assert( currTracker->startLoc != ptr );
            //if( currTracker->next )
            currTracker = currTracker->next;
        }
    }
    

    return blockSize;
} //bytesSearch


/**
 * @brief      Traverses the inner list
 *
 * @param[in]  size    The size of buffer
 * @param      header  the starting node
 */
void innerListLoop(r_size_t size, Chunk **header) {
    
    r_size_t sum = 0;
    assert( size > 0 );
    if( header != NULL ) {
        Chunk *ptrCurr = *(header);
        
        while(ptrCurr) {
            
            void *ptr = ptrCurr->startLoc;
            
            r_size_t size = ptrCurr->blockSize;
            sum+= ptrCurr->blockSize;
            printf("Address of Block is: %p\tBlock Size: %hu\n", ptr, size);
            
            ptrCurr = ptrCurr->next;
        }
    }
    
    double freePercentage = ((size - sum)/(double)size) * 100;
    printf("\nPercent of memory free is %6.2f%%\n", freePercentage);
    
} // innerListLoop


/**
 * @brief      frees up the inner linked list 
 *
 * @return     { true if successful }
 */
Boolean cleanInnerList(Node *regionNode) {
    
    Boolean result = false;
    
    Chunk *currPointer = regionNode->head;
    assert( currPointer == regionNode->head );
    Chunk *headerPtr = regionNode->head;
    
    while ( headerPtr != NULL ) {
        
        assert( headerPtr != NULL );
        headerPtr = headerPtr->next;
        
        free ( currPointer );
        
        currPointer  = headerPtr;
        assert( currPointer == headerPtr );
        
        //trackerNumNodes = trackerNumNodes -1;
        
    } // while loop
    
    headerPtr = NULL;
    assert( headerPtr == NULL );
    
    if ( NULL == headerPtr )
    {
        result = true;
    }
    
    return result;
    
} // cleanInnerList


/**************************************************************
 * Getter functions to returnr the topTracker and curr node
 * @return     The top tracker and curr node.
 **************************************************************/
Chunk *getTopTracker() {
    return topTracker;
} // getTopTracker


Node *getCurr() {
    return curr;
} // getCurr

/**
 * @brief      gets to the head node of the current region
 *
 * @param      target  The target region
 *
 * @return     the head node of the inner list
 */
Node *getToHead( char const * const target ) {
    
    assert( target != NULL );
    Node *outerCurr = top;
    
    Node *result = NULL;
    
    while( outerCurr != NULL && strcmp(target, outerCurr->string) != 0 ) {
        
        outerCurr = outerCurr->next;
    }
    
    if( outerCurr != NULL ) {
        
        result = outerCurr;
    }
    
    return result;
}
