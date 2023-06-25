

                                                                                                        NESTED ADT IN C 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




                                                                                                DEVISION TO FILES && TEMPLATE
                                                                                             -----------------------------------

1) Each struct will get his .c and .h files.
2) in the .c files there will only be the struct (without a typdedef) && the functions that works on that struct. 
3) in the .h files there will be a typedef struct "thestructname" *structInstancePTR, and the functions signatures that implemented in the .c files, and the related enum that belong to the struct in its .c file.                                                                              
4) when writing a nested adt in each .c .h file thats higher in the hierarchy i will need to include the .h file of the one below him in the hierarchy. so that in the higher hierarchy .h file he will recegonize thestructInstancePTR defined in the previos .h file.





                                                                                                CREATE INSTANCE FUNC IN C  
                                                                                            -----------------------------------                                                                                   
1) in all the data structers - the create instance functions should recive all the parameters needed to create the instance.

2) the return type of the create functions should always be the instance itself when its fully inizilied. 
   that way we control the only path to create an instance and we make sure that each instance that being created has its fiedls initlized correctly. 

for example:

shoppingCartInstancePTR createShoppingCart(char* cartNewName)
{
	shoppingCartInstancePTR newShoppingCartNode = (shoppingCartInstancePTR)malloc(sizeof(struct shoppingCart));
	newShoppingCartNode->cartName = (char*)malloc(strlen(cartNewName) + 1);
	strcpy(newShoppingCartNode->cartName, cartNewName);
	newShoppingCartNode->products = NULL;
	newShoppingCartNode->next = NULL;
	return newShoppingCartNode;
}

by doing so - we maintain the generic template adt. in a way where if we wish to make a transition to gnenric adt it means that the type of the parameters that being sent to the create func unknown and depends on the user.

 (thats why we use void* for paramaters of data types in the create instance function)


for example:
structInstancePTR create (recives the struct fiedls as parameters).

4) all the new/ malloc done in the create function. 

5) nore the create and the insert dialong with the user. they only recives the parameters needed to create the Instance.



                                                                                                INSERT INSTANCE FUNC IN C
                                                                                            -------------------------------------

1) in linkedList ADT - the insert instance functions should recive a *structInstancePTR . becuse i want to make changes on this instance outside the main.c func. 
    the insert function is responsible for the insertion part only!!.
for example: 
result insertNewInstanceNode_end(structInstancePTR* instanceHead, structInstancePTR newInstanceToInsert); - in this example the function recives an adress of instanceHead becuse we want to change it inside the func. the newInstanceToInsert is being sent 
                                                                                                            without a pointer becuse we aint gonna implement changes on him.

    its really important to keep that way. else when i will want to make a transformation to generic adt i will need to re write the whole program.
 (becuse the object that will be sent to the insert func is diffrent each time therefor theres a void* in the insert function for the unknown instance the user will send).

2) in all the data structures - the insert instance functions return type should be of enum result type. 
   to indicate the user whether the insertation of the instance he sent was succsefull or not.










                                                                                        MAIN.C PARAMETERS THAT BEING SENT TO THE ADT FUNCTIONS
                                                                                    ----------------------------------------------------------------

1) in the main.c dealing with LinkedList ADT i will declare a structInstancePTR type and set it to NULL. that will be the head of my the list. 
 for example:
 structInstancePTR instanceHead = NULL;

2) functions that needs to change the instanceHead,add/remove/edit etc.. will ask for (structInstancePTR* instanceHead) in their signature --> therefor from the main.c i will pass as parameter &instanceHead.

3) functions that does not need to change the instanceHead will ask for (structInstancePTR instanceHead) in therir signature --> therefor from the main.c i will pass as parameter (instanceHead).
 
 for example:
 int main()
{
    structInstancePTR instanceHead = NULL;

    structInstancePTR instance1 = create_NewProductNode("yotam", 40);

    insertNewinstanceNode_end(&instanceHead, instance1);

    printAllinstance(instanceHead);

    removeinstanceNode(&instanceHead, "yotam");

    destroyLinkedList(&instanceHead);

    return 0;
}






                                                                                                   LINKED LIST PRINCIPLES
                                                                                            -------------------------------------

1) linked list is a data structure contains of structs which has a data fields && a field which holds a pointer to the same struct. 
the most simplify example: 
struct Node
 {
    int data;
    struct Node* next;
};

2) i should always set uninilized Dynamic allocation fields inside of a node to NULL. 
  By doing so - i can assure that from anywhere in the program i will be able to indicate if that memory allocataion has been assigned - that way i will prevent sitations of accesing memory violation.
 

3) in the main.c when declaring the structInstancePTR instanceHead its important to set the instanceHead to NULL.
   structInstancePTR instanceHead = NULL; // Initialize head pointer to NULL
                                         // By initializing head to NULL, we establish an initial state where the list is empty, and this allows us to handle the insertion logic correctly.
    



                                                                                                ITERATING OVER A LINKED LIST
                                                                                            -------------------------------------

1) in order to iterate a linked list i will always need a separate variable (structInstancePTR curr) to safely traverse the list without losing the reference to its beginning,
 because when directly using the instanceHead (that being sent as a parameter to the function) i lose the reference to the beginning of the linked list --> productHead would point to the end of the list when traversal completes.
 and thats will change the instanceHead.

   

                                                                                                    DESTROY LINKED LIST
                                                                                                -----------------------------

1) we gonna have to use 2 pointers.  pointer curr will points to the instanceHead, pointer toRemove will point to curr.
   each time we gonna promote curr = curr next.
   and only then delete toRemove.

2) after we done destroying the list i must set the instanceHead that was sent to the func to NULL.
    that way the program can run again relying on the fact that if instanceHead == NULL --> it means the list is empty.

for example:
void destroyLinkedList(structInstancePTR* instanceHead)
{
	structInstancePTR curr = *instanceHead;
	while (curr != NULL)
	{
		structInstancePTR toRemove = curr;
		curr = curr->next;
		free(toRemove->name);
		free(toRemove);
	}
	printf("**LINKED LIST REMOVES SUCCESSFULLY**\n\n");
	*instanceHead = NULL;
	return;
}


                                                                                                INSERT NODE AT THE BEGININIG 
                                                                                            -------------------------------
1) insert at the begininig has 2 special case : the linked list is empty. 
    aka if *instanceHead == NULL --> then it means that the linked list is empty. therefore we will just assign it the new instanceToInsert.

2) else: we gonna have to set a new head with 2 stages.
first we must set the new instanceToInsert ->next to point to *instanceHead of the linked list.
now we can set our new head. 
we will direfrence *instanceHead and assign it to new instanceToInsert.

for example:
result insertNewProductNode_start(productInstancePTR* productHead, productInstancePTR productToInsert)
{
	if (*productHead == NULL) // if the list is empty then head = productToInsert.
	{
		*productHead = productToInsert;
		return SUCSSES;
	}

	productToInsert->next = *productHead; // prodcutToInsert now points to our prodcutHead of the list. (note: thats still aint updating our head in the main.c)
	*productHead = productToInsert;		// derefrencing our productHead of the list to points to the newly productToInsert.
										// note: thats ok becuse in the previous line we set the newly productToInsert->next to point to our prodcutHead of the list. 
										// now we have a new head which is the newly prodcutToInsert && he points to the previous prodcutHead of the list.
	return SUCSSES;
}






                                                                                            INSERT NODE AT THE END
                                                                                        --------------------------------------

1) we have 1 special case - if the linked list empty. aka head == NULL. then head = instanceToInsert.
note: it is super important to check if *head == NULL with the actual head and set *head = instanceToInsert, NOT WITH CURR.

chagtgpt explaination: 
thats related to the next-> operator that not being used in that special case.
 if we write curr = productToInsert  we simply assigns the memory address held by productToInsert to the local pointer variable curr. This doesnt affect what the original productHead in main is pointing to.
and also if *shoppingCartInstancehead is NULL, then curr is also NULL. If you then change curr to point to newCartInstance, *shoppingCartInstancehead remains NULL because you only changed the copy, not the original.










2) else - we need to iterate all over the list with curr pointer (so i wont change the actual head when travercing the list) and find the instance->next == NULL and then direfrence it to points to the instanceToInsert.

chagtgpt explaination: 
In short, the assignment curr = productToInsert; only changes where the local curr pointer is pointing, whereas curr->next = productToInsert; actually changes the structure of your linked list.











                                    
                                                                                             REMOVE NODE FROM THE MIDDLE
                                                                                        -------------------------------------
    we have 3 cases that if done by this order it assures that i checked all possible scnerios. 
    we gonna use 2 pointers, curr and toRemove
1) if the linkedlist is empty. 
2) if the head of the linked list is the node to be deleted. 
3)if we are here it means that we need to Search for the node to be deleted, &&keep track of the previous node make him points to curr->next && delete curr.(he either does not exist or in the middle).

for example: an implemention of remove from middle not with ADT (from Marcello PDF)
item *Delete(Item * head, int value)
{
    Item* curr = head;
    Item* prev = head; prev = head;
    if (head==NULL)
    {
        return head;
    }
     
    if (head->data == >data == value)
        {
            curr = head->next;
                free(head);
                return curr;
        }

 while (curr while (curr->next != NULL) >next != NULL)
    {
        prev = curr;
        curr = curr curr = curr->next;
        if(curr if (curr->data == value) >data == value)
            {
                prev->next = curr >next = curr->next;
                free(curr);
                return head;
            }
    }     
return head;
}









                                                                                        Nested LinkedList ADT in C
                                                                                   -----------------------------------------------
1) when dealing with nested linkedlist in C i will often have function that modify a field of a linkedList ADT which is also a linkedlist ADT (just lower in the hierarchy).
    in these cases as i mentioned in the singleton ADT above ^^ they gonna have to recive the adress of that ADT field that we wanna edit/remove/insertnew (which is ADT as well).

    for example:
these functions siganture will look something like that : 
 result insertProductToCart(shoppingCartInstancePTR* cartInstance, productInstancePTR productToInsert);

 i cant directly use &userInstance-> because the operator "->" has higher precedence than the & operator in C. 
This means that the "->" operator will be applied before the & operator if they are in the same expression without parentheses "( )". 
and that wil  results in a compilation error because im trying to dereference userInstance before i take his address.

so i have 2 aproaches of sending the adress of the instanceHead to the these functions:

result insertProductToUserCart(userInstancePTR* userInstance, productInstancePTR productToInsert) // direfrencing the *userInstance to the actual instance it points to and getting the adress of this instance cart field.
{
	insertProductToCart(&(*userInstance)->cart, productToInsert);

	return SUCSSES;

}

result insertProductToUserCart(userInstancePTR* userInstance, productInstancePTR productToInsert) // a tempInstance which recives the value that *userInstance points to. aka our actual instance and then directly using-> to get his cart field adress.
{
	userInstancePTR userTemp = *userInstance;
	insertProductToCart(&userTemp->cart, productToInsert);

	return SUCSSES;

}























                                                                                A WAY TO CHECK FOR MEMORY LEAKS IN C++/C WITH VISUAL STUDIO
                                                                            --------------------------------------------------------------------
1) in every c file i should add #define _CRTDBG_MAP_ALLOC
2) before each time i exit the program i should add this func signature : _CrtDumpMemoryLeaks();




                                                                                                         






