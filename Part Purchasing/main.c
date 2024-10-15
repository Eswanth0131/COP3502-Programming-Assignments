// Headers
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Alias
typedef struct Queue Queue;
typedef struct Node Node;
typedef struct Part Part;
typedef struct Component Component;

// Struct Definitions
struct Queue
{
    Node * tail;
};
struct Node
{
    Node * next;
    int data;
};
struct Part
{
    int count; // The number of this part available
    int extra_part; // The additional part that comes when purchasing
    int price; // The price of purchasing the part
};
struct Component
{
    int known; // Is the component known to the repair crew
    int part_req; // The part required to fix
    int num_comp_rev; // Number of components revealed when fixed
    int * comp_rev; // Array of revealed components when fixed
};

// LL Prototypes
Node * createNode(int data);
Node * insertTail(Node * tail, int data);
Node * removeHead(Node * tail);

// Queue Prototypes
Queue * createQueue(void);
void deleteQueue(Queue * q);
void enqueue(Queue * q, int data);
void dequeue(Queue * q);
int front(Queue * q);
int isEmpty(Queue * q);

// LL Functions
// Function to create a Node
Node * createNode(int data)
{
    // Allocation
    Node * res = (Node *) malloc(sizeof(Node));

    // Intialization
    res->data = data;
    res->next = res; // self, because circular
    
    // Return
    return res;
}

// Function to insert a new tail into a linked list
// Returns resulting tail
Node * insertTail(Node * tail, int data)
{
    Node * newTail = createNode(data);

    // Empty list case
    if (tail == NULL) {
        return newTail;
    }

    // At least 1 node case
    // The resulting tail's next should point to old head
    newTail->next = tail->next;

    // The new tail should follow after the old tail
    tail->next = newTail;

    // Return the resulting tail
    return newTail;
}

Node * removeHead(Node * tail)
{
    // Empty list case
    if (tail == NULL) {
        return NULL;
    }
    
    // Single node list case
    if (tail->next == tail) {
        free(tail);
        return NULL;
    }

    // More than 1 node case
    // Get the new head
    Node * newHead = tail->next->next;

    // Free the oldhead
    free(tail->next);

    // Link the tail to the head
    tail->next = newHead;

    // Return the tail
    return tail;
}

// Queue Prototypes
// Function to create a Queue
Queue * createQueue()
{
    // Allocate
    Queue * res = (Queue *) malloc(sizeof(Queue));

    // Initilaize
    res->tail = NULL;

    // Return
    return res;
}

// Function to delete all the memory assoricated with queue
void deleteQueue(Queue * q)
{
    // Delete all the values in the queue
    while (!isEmpty(q)) {
        dequeue(q);
    }
    
    // Remove the queue
    free(q);
}


// Function to add some data to the queue
void enqueue(Queue * q, int data)
{
    // Use the linked list function to add a node
    q->tail = insertTail(q->tail, data);
}

// Function to remove the front of the queue
void dequeue(Queue * q)
{
    // Use the linked list function to remove a node
    q->tail = removeHead(q->tail);
    if (q->tail == NULL) {
        return;
    }
}

// Function to return the element at the front of the queue
int front(Queue * q)
{
    // Ensure that there is a value
    assert(!isEmpty(q));

    // Return the value at the head
    return q->tail->next->data;
}

// Function to check that the queue is empty
int isEmpty(Queue * q)
{
    return (q->tail == NULL);
}

int main ()
{
    // initialize varibales
    int numOfParts = 0;
    int brokenParts = 0;
    int totalCost = 0;


    scanf("%d", &numOfParts);

    // dynamically create part array
    Part * part = (Part *) malloc((numOfParts) * sizeof(Part));

    // read input
    for (int i = 0; i < numOfParts; i++)
    {
        int price = 0;
        int extra_part = 0;

        scanf("%d", &price);
        scanf("%d", &extra_part);

        part[i].price = price;
        part[i].extra_part = extra_part;
        part[i].count = 0;
    }

    scanf("%d", &brokenParts);
    // dynamically create components array
    Component * components = (Component *) malloc((brokenParts) * sizeof(Component));

    // read input
    for (int i = 0; i < brokenParts; i++)
    {
        // initialize values
        scanf("%d", &components[i].part_req);
        scanf("%d", &components[i].num_comp_rev);
        
        components[i].known = 0;
        
        if (components[i].num_comp_rev == 0)
        {
            // DO NOTHING
        }
        else
        {
            // dynamically create comp_rev array
            components[i].comp_rev = (int *) calloc(components[i].num_comp_rev, sizeof(int));
            for (int j = 0; j < components[i].num_comp_rev; j++)
            {
                // read input and initialize
                scanf("%d", &components[i].comp_rev[j]);
            }
        }
    }

    Queue * queue = createQueue();

    for (int i = 0; i < brokenParts; i++)
    {
        // loop until all parts are fixed
        if (components[i].known != 2)
        {
            
            enqueue(queue, i);
            do
            {
                // set firstQueue
                int firstQueue = queue->tail->next->data;
                if (part[components[firstQueue].part_req - 1].count == 0)
                {
                    // add to total cost, increment count of part, and increment count of extra part
                    totalCost = totalCost + part[components[firstQueue].part_req - 1].price;
                    part[components[firstQueue].part_req - 1].count++;
                    part[part[components[firstQueue].part_req - 1].extra_part - 1].count++;
                    // change known to be known
                    components[firstQueue].known = 1;
                    // use queue to add
                    enqueue(queue, firstQueue);
                    dequeue(queue);
                }
                else
                {
                    // dequeue after part is fixed
                    components[firstQueue].known = 2;
                    dequeue(queue);
                    part[components[firstQueue].part_req - 1].count--;
                    
                    // loop to find out what parts broken are revealed
                    for (int j = 0; j < components[firstQueue].num_comp_rev; j++)
                    {
                        int index = components[firstQueue].comp_rev[j] - 1;
                        
                        if (components[index].known == 0)
                        {
                            components[index].known = 1;
                            enqueue(queue, index);
                        }
                    }
                    
                }
            } while (queue->tail != NULL);
        }
    }
    // print totalCost
    printf("%d\n", totalCost);

    return 0;
}
