
// This program implements a stack using a array list

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Typedef structures
typedef struct Stack Stack;
typedef struct Node Node;

// Structures
struct Stack
{
    Node * main;
};

struct Node
{
    int rooms;
    int isValid;
    Node * next;
};

// Function prototypes
Node * createNode(int data);
Node * insertHead(Node * head, int data);
Node * removeHead(Node * head);
Stack * createStack(void);
int isEmpty(Stack * stack);
void pop(Stack * stack);
void push(Stack * stack, int data);

// Functions
Node * createNode(int data)
{
    Node * res = (Node *) malloc(sizeof(Node));
    
    res->rooms = data;
    res->isValid = 1;
    res->next = NULL;
    
    return res;
}

Node * insertHead(Node * head, int data)
{
    Node * newHead = createNode(data);
    
    newHead->next = head;
    
    return newHead;
}

Node * removeHead(Node * head)
{
    if (head == NULL)
    {
        return NULL;
    }
    
    Node * newHead = head->next;
    
    free(head);
    
    return newHead;
}

Stack * createStack(void)
{
    Stack * res = (Stack *) malloc(sizeof(Stack));
    
    res->main = NULL;
    
    return res;
}

int isEmpty(Stack * stack)
{
    if(stack->main == NULL)
        return 1;
    
    return 0;
}

void pop(Stack * stack)
{
    stack->main = removeHead(stack->main);
}

void push(Stack * stack, int data)
{
    stack->main = insertHead(stack->main, data);
}

int secLast(Stack * stack)
{
    return stack->main->next->rooms;
}

int main(void)
{
    // Create stack
    Stack * stack = createStack();
    
    // Initialize variables
    long long int roomCount = 0;
    long long int totalCount = 0;
    long long int roomNum = 0;
    
    // While loop to run until -1
    while (roomNum != -1)
    {
        // Scan input
        scanf("%lld", &roomNum);
        
        // Case 1: Stack is empty
        if (stack->main == NULL)
        {
            push(stack, roomNum);
        }
        // Case 2: Stack has one node
        else if (stack->main->next == NULL)
        {
            stack->main->isValid = 0;
            push(stack, roomNum);
            
        }
        // Case 3: Any other
        else
        {
            if (roomNum == secLast(stack))
            {
                if (stack->main->isValid == 1)
                {
                    int fromMain = 0;
                    roomCount++;
                    
                    // Create current node to loop thorugh
                    Node * current = stack->main;
                    
                    while (current != NULL)
                    {
                        fromMain++;
                        current = current->next;
                        
                    }
                    
                    // Add fromMain -1 to totalCount
                    totalCount += fromMain - 1;
                    
                    pop(stack);
                }
                else
                {
                    pop(stack);
                }
            }
            else
            {
                stack->main->isValid = 0;
                push(stack, roomNum);
            }
        }
    }
    
    // Print the roomCount and totalCount
    printf("%lld %lld\n", roomCount, totalCount);
    
    return 0;
}
