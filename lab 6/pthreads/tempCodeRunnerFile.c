 rc = pthread_create(&thread_id, NULL, PrintHello, (void *)t);
    
    if (rc) 
    {
        printf("\n ERROR: return code from pthread_create is %d \n", rc);
        exit(1);
    }
    printf("\nCreated new thread (%lu) ... \n", thread_id);
