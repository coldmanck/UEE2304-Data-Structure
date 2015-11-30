//	List ADT Type Defintions 
	typedef struct node 
	   {
	    void*        dataPtr;
	    struct node* link;
	    int grade;
	    string name;
	   } NODE; 

	typedef struct
	   {
	    int   count; 
	    NODE* pos;
	    NODE* head; 
	    NODE* rear;
	    int    (*compare) (void* argu1, void* argu2); 
	    
	   } LIST;

//	Prototype Declarations 
	LIST* createList   (int (*compare)
	                   (void* argu1, void* argu2));

	int   addNode   (LIST* pList, void* dataInPtr);

	static bool _insert   (LIST* pList,
	                      NODE* pPre,
	                      void* dataInPtr);

	static bool _search  (LIST*  pList,
	                      NODE** pPre,
	                      NODE** pLoc,
	                      void*  pArgu);

	LIST* createList 
     (int (*compare) (void* argu1, void* argu2))
{
//	Local Definitions 
	LIST* list;

//	Statements 
	list = (LIST*) malloc (sizeof (LIST));
	if (list)
	   {
	    list->head    = NULL;
	    list->pos     = NULL;
	    list->rear    = NULL;
	    list->count   = 0;
	    list->compare = compare;
	   } // if 

	return list;
}	// createList 

int addNode (LIST* pList, void* dataInPtr)
{
//	Local Definitions 
	bool found;
	bool success;
	
	NODE* pPre;
	NODE* pLoc;
	
//	Statements 
	found = _search (pList, &pPre, &pLoc, dataInPtr);
	if (found)
	   // Duplicate keys not allowed 
	   return (+1);

	success = _insert (pList, pPre, dataInPtr);
	if (!success)
	   // Overflow 
	   return (-1);
	return (0);
}	// addNode 

static bool _insert (LIST* pList, NODE* pPre,
                     void* dataInPtr)
{
//	Local Definitions 
	NODE* pNew;

//	Statements 
	if (!(pNew = (NODE*) malloc(sizeof(NODE))))
	   return false;

	pNew->dataPtr   = dataInPtr; 
	pNew->link      = NULL; 
 
	if (pPre == NULL)
	   {
	    // Adding before first node or to empty list. 
	    pNew->link       = pList->head;
	    pList->head      = pNew;
	    if (pList->count == 0)
	       // Adding to empty list. Set rear 
	       pList->rear = pNew;
	   } // if pPre 
	else
	   {
	    // Adding in middle or at end 
	    pNew->link  = pPre->link;
	    pPre->link  = pNew;
 
	    // Now check for add at end of list 
	    if (pNew->link     == NULL)
	         pList->rear   =  pNew;
	   } // if else 

	(pList->count)++;
	return true;
}	// _insert 

bool _search (LIST*  pList, NODE** pPre,
              NODE** pLoc,  void*  pArgu)
{
//	Macro Definition 
#define COMPARE \
	( ((* pList->compare) (pArgu, (*pLoc)->dataPtr)) )

#define COMPARE_LAST \
	((* pList->compare) (pArgu, pList->rear->dataPtr))

//	Local Definitions 
	int result;
	
//	Statements 
	*pPre  = NULL;
	*pLoc  = pList->head;
	if (pList->count == 0)
	    return false;
	
	// Test for argument > last node in list 
	if ( COMPARE_LAST > 0) 
	   {
	    *pPre = pList->rear;
	    *pLoc = NULL;
	    return false;
	   } // if 

	while ( (result = COMPARE) > 0 )
	   {
	    // Have not found search argument location 
	    *pPre = *pLoc;
	    *pLoc = (*pLoc)->link;
	   } // while 
	
	if (result == 0)
	   // argument found--success 
	   return true;
	else
	   return false;
}	// _search 
