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


