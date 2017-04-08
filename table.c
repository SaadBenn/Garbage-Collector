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


