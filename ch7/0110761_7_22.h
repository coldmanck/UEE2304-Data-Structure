#include <stdbool.h>

//	Structure Declarations 
typedef struct node
	{
	 void*        dataPtr;
	 struct node* left;
	 struct node* right;
	} NODE;

typedef struct
	{
	 int   count;
	 int  (*compare) (void* argu1, void* argu2);
	 NODE*  root;
	} BST_TREE;
	
//	Prototype Declarations 
BST_TREE* BST_Create 
         (int (*compare) (void* argu1, void* argu2));
BST_TREE* BST_Destroy (BST_TREE* tree);

bool  BST_Insert   (BST_TREE* tree, void* dataPtr);
bool  BST_Delete   (BST_TREE* tree, void* dltKey);
void* BST_Retrieve (BST_TREE* tree, void* keyPtr);
void  BST_Traverse (BST_TREE* tree,
                    void (*process)(void* dataPtr));

bool BST_Empty (BST_TREE* tree);
bool BST_Full  (BST_TREE* tree);
int  BST_Count (BST_TREE* tree);

static NODE* _insert
               (BST_TREE* tree, NODE* root,
                NODE* newPtr); 
static NODE* _delete
               (BST_TREE* tree,    NODE* root,
                void*     dataPtr, bool* success);
static void* _retrieve
               (BST_TREE* tree,
              void* dataPtr, NODE* root);
static void _traverse 
               (NODE* root,
                void (*process) (void* dataPtr));
static void _destroy (NODE* root);


BST_TREE* BST_Create 
        (int  (*compare) (void* argu1, void* argu2))
{
//	Local Definitions 
	BST_TREE* tree;

//	Statements 
	tree = (BST_TREE*) malloc (sizeof (BST_TREE));
	if (tree)
	   {
	    tree->root    = NULL;
	    tree->count   = 0;
	    tree->compare = compare;
	   } // if 

	return tree;
}	// BST_Create 


bool BST_Insert (BST_TREE* tree, void* dataPtr)
{
//	Local Definitions 
	NODE* newPtr;

//	Statements 
	newPtr = (NODE*)malloc(sizeof(NODE));
	if (!newPtr)
	   return false;

	newPtr->right   = NULL;
	newPtr->left    = NULL;
	newPtr->dataPtr = dataPtr;
   
	if (tree->count == 0)
	    tree->root  =  newPtr;
	else
	    _insert(tree, tree->root, newPtr);
	    
	(tree->count)++;
	return true;
}  // BST_Insert 

NODE* _insert (BST_TREE* tree, NODE* root, NODE* newPtr)
{
      
//	Statements 
	if (!root)
	   // if NULL tree 
	   return newPtr;
 
	// Locate null subtree for insertion 
	if (tree->compare(newPtr->dataPtr, 
	                  root->dataPtr) < 0)
	   {
	    root->left = _insert(tree, root->left, newPtr);
	    return root; 
	   } // new < node 
	else 
	   // new data >= root data 
	   {
	    root->right = _insert(tree, root->right, newPtr);
	    return root;
	     } // else new data >= root data 
	return root;
}	// _insert 

bool BST_Delete (BST_TREE* tree, void* dltKey)
{
//	Local Definitions 
	bool  success;
	NODE* newRoot;
	
//	Statements 
	newRoot = _delete (tree, tree->root, dltKey, &success);
	if (success)
	   {
	    tree->root = newRoot;
	    (tree->count)--;
	    if (tree->count == 0)
	        // Tree now empty 
	        tree->root = NULL;
	   } // if 
	return success;
}  // BST_Delete


NODE*  _delete (BST_TREE* tree,    NODE* root, 
                void*     dataPtr, bool* success)
{
// Local Definitions 
	NODE* dltPtr;
	NODE* exchPtr;
	NODE* newRoot;
	void* holdPtr;

//	Statements 
	if (!root)
	   {
	    *success = false;
	    return NULL;
	   } // if 
	
	if (tree->compare(dataPtr, root->dataPtr) < 0)
	     root->left  = _delete (tree,    root->left, 
	                            dataPtr, success);
	else if (tree->compare(dataPtr, root->dataPtr) > 0)
	     root->right = _delete (tree,    root->right, 
	                            dataPtr, success);
	else
	    // Delete node found--test for leaf node 
	    {
	     dltPtr = root;
	     if (!root->left)
	         // No left subtree 
	         {
	          free (root->dataPtr);       // data memory
	          newRoot = root->right;
	          free (dltPtr);              // BST Node
	          *success = true;
	          return newRoot;             // base case 
	         } // if true 
	     else
	         if (!root->right)
	             // Only left subtree 
	             {
	              newRoot = root->left;
	              free (dltPtr);
	              *success = true;
	              return newRoot;         // base case 
	            } // if 
	         else
	             // Delete Node has two subtrees 
	             {
	              exchPtr = root->left;
	              // Find largest node on left subtree
	              while (exchPtr->right)
	                  exchPtr = exchPtr->right;

	              // Exchange Data 
	              holdPtr          = root->dataPtr;
	              root->dataPtr    = exchPtr->dataPtr;
	              exchPtr->dataPtr = holdPtr;
	              root->left       = 
	                 _delete (tree,   root->left, 
	                          exchPtr->dataPtr, success);
	             } // else 
	    } // node found 
	return root; 
}	// _delete 

void* BST_Retrieve  (BST_TREE* tree, void* keyPtr)
{
//	Statements 
	if (tree->root)
	 {
	    return _retrieve (tree, keyPtr, tree->root);
        
     } 
	else
	    return NULL;
}	// BST_Retrieve 

void* _retrieve (BST_TREE* tree, 
	              void* dataPtr, NODE* root)
{
//	Statements 
	if (root)
	    {
	     if (tree->compare(dataPtr, root->dataPtr) < 0)
	         return _retrieve(tree, dataPtr, root->left);
	     else if (tree->compare(dataPtr, root->dataPtr) > 0)
	         return _retrieve(tree, dataPtr, root->right);
	     else
	         // Found equal key 
	         return root->dataPtr;
	    }  // if root 
	else
	    // Data not in tree 
	    return NULL;
}	// _retrieve 

void BST_Traverse (BST_TREE* tree, 
                   void (*process) (void* dataPtr)) 
{
//	Statements 
	_traverse (tree->root, process);
	return;
}  // end BST_Traverse 

void _traverse (NODE* root, 
                void (*process) (void* dataPtr)) 
{
//	Statements 
if  (root)
    {
     _traverse (root->left, process);
     process   (root->dataPtr);
     _traverse (root->right, process);
    } // if 
return;
}  // _traverse

bool BST_Empty (BST_TREE* tree)
{
//	Statements 
	return (tree->count == 0);
}	// BST_Empty 

bool BST_Full (BST_TREE* tree)
{
//	Local Definitions 
	NODE* newPtr;
	
//	Statements 
	newPtr = (NODE*)malloc(sizeof (*(tree->root)));
	if (newPtr)
	   {
	    free (newPtr);
	    return false;
	   } // if 
	else
	     return true;
}	// BST_Full 

int BST_Count (BST_TREE* tree)
{
//	Statements 
	return (tree->count);
}	// BST_Count 

BST_TREE* BST_Destroy (BST_TREE* tree) 
{
//	Statements 
	if (tree)
		_destroy (tree->root);
		
	// All nodes deleted. Free structure 
	free (tree);
	return NULL;
}	// BST_Destroy 

void _destroy (NODE* root)
{
//	Statements 
	if (root)
	   {
	    _destroy (root->left);
	    free (root->dataPtr);
	    _destroy (root->right);
	    free (root);
	   } // if 
	return;
}	// _destroy