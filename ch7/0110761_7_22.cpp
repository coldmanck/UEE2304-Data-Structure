#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "0110761_7_22.h"

typedef struct {
    char name[30];
    char phone[20];
} STUDENT;

int compareStu (void*, void* );
void addStu (BST_TREE*, char[], char[]);
void processStu (void*);
void saveStu (void*);
void printList  (BST_TREE*);
void deleteStu (BST_TREE*);
void findStu (BST_TREE*);
char getOption (void);

int main(){
	FILE *fp;
	fp = fopen("phones.txt", "r+");
	
	char name[30];
	char phone[20];

	BST_TREE* list;
	list = BST_Create (compareStu);

	// while(!feof(fp)){...}
	while(fscanf(fp, "%s %s", name, phone) == 2){
		// printf("%s, %s\n", name, phone);
		addStu(list, name, phone);
	};
	fclose(fp);

	char option = ' ';
	while ( (option = getOption ()) != 'Q'){
	    switch (option){
	        case 'A': 
	        		  printf("Input name: ");
	        		  scanf("%s", name);
	        		  printf("Input phone: ");
	        		  scanf("%s", phone);
	        		  addStu (list, name, phone);
	                  break;
	        case 'D': deleteStu (list);
	                  break;
	        case 'F': findStu (list);
	                  break;
	        case 'P': printList (list);
	                  break;
	      } // switch 
	   } // while 

	fp = fopen("phones.txt", "w");
	BST_Traverse (list, saveStu);
	fclose(fp);

	list = BST_Destroy (list);

	printf("\nEnd Student List\n");
	return 0;
}

int compareStu (void* stu1, void* stu2){
//	Local Definitions 
	STUDENT s1;
	STUDENT s2;
	
//	Statements 
	s1 =  *(STUDENT*)stu1;
	s2 =  *(STUDENT*)stu2;

	int i = strcmp(s1.name, s2.name);
	return (i < 0 ? -1 : (i > 0 ? 1 : 0));
}	// compareStu 

void addStu (BST_TREE* list, char name[], char phone[]){
//	Local Definitions 
	STUDENT* stuPtr;
	
//	Statements 
	stuPtr = (STUDENT*)malloc (sizeof (STUDENT));
	if (!stuPtr)
	    printf("Memory Overflow in add\n"), exit(101);

	strcpy(stuPtr->phone, phone);
	strcpy(stuPtr->name, name);
 
	BST_Insert (list, stuPtr);
}	// addStu 

void processStu (void* stuPtr){
//	Local Definitions 
	STUDENT aStu;
	
//	Statements 
	aStu = *(STUDENT*)stuPtr;
	printf("%s\t%s\n", aStu.name, aStu.phone);
	return;
}	// processStu 

void saveStu (void* stuPtr){
	STUDENT aStu;
	FILE* pFile;
	pFile = fopen("phones.txt", "a");
	
//	Statements 
	aStu = *(STUDENT*)stuPtr;
	// printf("%s\t%s\n", aStu.name, aStu.phone);
	fprintf(pFile, "%s %s\n", aStu.name, aStu.phone);

	return;
}

void printList  (BST_TREE* list){
//	Statements 
	printf("\nStudent List:\n");
	BST_Traverse (list, processStu);
	printf("End of Student List\n");
	return;
}	// printList 

void deleteStu (BST_TREE* list){
//	Local Definitions 
	char  name[30];
	//int* namePtr = &name;

//	Statements 
	printf("Enter student's name: ");
	scanf ("%s", name);

	if (!BST_Delete (list, name))
	   printf("ERROR: No Student: %s\n", name);
}	// deleteStu 

void findStu (BST_TREE* list)
{
//	Local Definitions 
	char  name[30];
	STUDENT* stuPtr;

//	Statements 
	printf("Enter student's name: ");
	scanf ("%s", name);

	stuPtr = (STUDENT*)BST_Retrieve (list, name);
	if (stuPtr){
	    printf("Student name: %s\n",  name);
	    printf("Student phone: %s\n", stuPtr->phone);
	   } // if 
	else
	   printf("Student %s not in file\n", name);
}	// findStu 

char getOption  (void)
{
//	Local Definitions 
	char option;
	bool error;
	
//	Statements 
	printf("\n ======  MENU  ======\n");
	printf(" A   Add Student\n");
	printf(" D   Delete Student\n");
	printf(" F   Find Student\n");
	printf(" P   Print Class List\n");
	printf(" Q   Quit and Save\n");
	    
	do
	   {
	    printf("\nEnter Option: ");
	    scanf(" %c", &option);
	    option = toupper(option);
	    if   (option == 'A' || option == 'D'
	       || option == 'F' || option == 'P'
	       || option == 'U' || option == 'Q')
	          error = false;
	    else	       
	         {
	          printf("Invalid option. Please re-enter: ");
	          error = true;
	         } // if 
	   } while (error == true);
	return option;
}	// getOption 