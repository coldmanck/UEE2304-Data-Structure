//	Stack ADT Type Defintions 
	typedef struct node2 
	   {
	    void*        dataPtr;
	    struct node2* link;
	   } STACK_NODE;

	typedef struct
	   {
	    int         count; 
	    STACK_NODE* top; 
	   } STACK;

