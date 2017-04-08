//-----------------------------------------
// NAME: Saad B Mushtaq
// STUDENT NUMBER: 7785430
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: assignment 4
// 
// REMARKS: table

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "table.h"
#include "regions.h"
//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------

Node *top = NULL;
Node *curr = NULL;
Chunk *topTracker = NULL;
Chunk *currTracker = NULL;

static int numNodes = 0;
static int trackerNumNodes = 0;
// used to track where we are for the list traversal methods
static Node *traverseNode = NULL;


//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

/******************************************************
 * Validates the string and the linked list
 *******************************************************/
static void checkState( char const * const string) {
    
    assert( string != NULL );
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
    Node *curr = top;
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
            topTracker = top->head;
            
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
} //  nextNde


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
    newChunk->blockSize = block_size;
    newChunk->next = NULL;
    
    //checking whether the node created is only node or not
    if (topTracker == NULL)
    {
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

    return rc;
} // insertTracker


void* allocBlock( r_size_t block_Required, void *ptr ) {
    r_size_t size = 0;
    Boolean result = false;
    Chunk *traverse = topTracker;
    void * trackingPtr = curr->memory;
    
    while( traverse != NULL && !result ) {
        
        
        if( trackingPtr == traverse->startLoc) {
            
            void* startPoint =traverse->startLoc;
            r_size_t bSize = traverse->blockSize;
            
            void* nextFree = startPoint + bSize;
            trackingPtr = nextFree;
            
            if( traverse->next != NULL ) {
            
                void *address = traverse->next->startLoc;
            
                size = address - nextFree;
                //printf("If part %d\n", size);
            
                if( size > block_Required) {
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
        }
        
        if( trackerNumNodes == 1) {
            r_size_t bSize = traverse->startLoc - trackingPtr;
            //printf("Node == 1 part %d\n", bSize);
            if( bSize >= block_Required) {
                insertTracker(block_Required, trackingPtr);
                for(int i = 0; i < block_Required; i++) {
                    *((char*)trackingPtr + i) = '0';
                }
                ptr = trackingPtr;
                result = true;
            } else {
                trackingPtr += bSize;
                trackingPtr += traverse->blockSize;
                
                bSize = (curr->memory+curr->size) - trackingPtr;
                if(bSize >= block_Required) {
                    insertTracker(block_Required, trackingPtr);
                    for(int i = 0; i < block_Required; i++) {
                        *((char*)trackingPtr + i) = '0';
                    }
                    ptr = trackingPtr;
                    result = true;
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



Boolean deletePtr( void* target )
{
    
    //checkState( target );
    
    Boolean deleted = false;
    Chunk *currN = topTracker;
    assert( currN == topTracker );
    
    Chunk *prev = NULL;
    assert( prev == NULL );
    
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
            
            topTracker = currN->next;
            curr->head = currN->next;
            
        }
        
        free( currN );
        currN = NULL;
        assert( currN == NULL );
        deleted = true;
        trackerNumNodes--;
    }
    
    return deleted;
    
} // end delete function


r_size_t bytesSearch( void *ptr )
{
    r_size_t blockSize = 0;
    Boolean found = false;
    currTracker = topTracker;
    assert( currTracker == topTracker );
    
    while ( currTracker != NULL && !found )
    {
        assert( currTracker != NULL );
        
        if ( currTracker->startLoc == ptr )
        {
            assert( currTracker->startLoc == ptr );
            found = true;
            blockSize = currTracker->blockSize;
        }
        
        else
        {
            assert( currTracker->startLoc != ptr );
            curr = curr->next;
        }
    }
    
    return blockSize;
} //bytesSearch


Boolean cleanInnerList() {
    
    Boolean result = false;
    
    Chunk *currPointer = topTracker;
    assert( currPointer == topTracker );
    
    while ( topTracker != NULL ) {
        
        assert( topTracker != NULL );
        topTracker = topTracker->next;
        
        free ( currPointer );
        
        currPointer  = topTracker;
        assert( currPointer == topTracker );
        
        trackerNumNodes = trackerNumNodes -1;
        
    } // while loop
    
    topTracker = NULL;
    assert( topTracker == NULL );
    
    if ( NULL == topTracker )
    { 
        result = true;
    }
    
    return result;
    
} // cleanInnerList


void innerListLoop() {
    
    r_size_t sum = 0;
    Chunk *ptrCurr = topTracker;
    
    while(ptrCurr) {
        
        void *ptr = ptrCurr->startLoc;
        
        r_size_t size = ptrCurr->blockSize;
        sum+= ptrCurr->blockSize;
        printf("Address of Block is: %p\tBlock Size: %hu\n", ptr, size);
        
        ptrCurr = ptrCurr->next;
    }
    
    if( sum == 0) {
        //printf("\033[35m");
        printf("\n%s\n", "No blocks allocated so far.");
        //printf("\033[0m");
    } else {
    
        double freePercentage = ((curr->size - sum)/(double)curr->size) * 100;
        printf("\nPercent of memory free is %6.2f%%\n", freePercentage);
    }
} // innerListLoop


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