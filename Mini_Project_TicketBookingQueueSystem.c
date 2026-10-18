#include <stdio.h>
#define SIZE 5

int queue[SIZE];
int front = -1, rear = -1;

void bookTicket()
{
    int ticket;

    if ((rear + 1) % SIZE == front)
    {
        printf("Booking Queue is Full!\n");
        return;
    }

    printf("Enter Ticket Number: ");
    scanf("%d", &ticket);

    if (front == -1)
        front = 0;

    rear = (rear + 1) % SIZE;
    queue[rear] = ticket;

    printf("Ticket booked successfully!\n");
}

void processTicket()
{
    if (front == -1)
    {
        printf("Queue is Empty!\n");
        return;
    }

    printf("Ticket %d processed.\n", queue[front]);

    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % SIZE;
}

void displayQueue()
{
    int i;

    if (front == -1)
    {
        printf("Queue is Empty!\n");
        return;
    }

    printf("Tickets: ");
    i = front;

    while (1)
    {
        printf("%d ", queue[i]);

        if (i == rear)
            break;

        i = (i + 1) % SIZE;
    }

    printf("\n");
}

void searchTicket()
{
    int ticket, i;

    if (front == -1)
    {
        printf("Queue is Empty!\n");
        return;
    }

    printf("Enter Ticket Number to Search: ");
    scanf("%d", &ticket);

    i = front;

    while (1)
    {
        if (queue[i] == ticket)
        {
            printf("Ticket %d Found in Queue!\n", ticket);
            return;
        }

        if (i == rear)
            break;

        i = (i + 1) % SIZE;
    }

    printf("Ticket Not Found!\n");
}


void deleteTicket()
{
    int ticket, i, pos, found = 0;

    if (front == -1)
    {
        printf("Queue is Empty!\n");
        return;
    }

    printf("Enter Ticket Number to Delete: ");
    scanf("%d", &ticket);

    i = front;
    pos = 0;

    while (1)
    {
        if (queue[i] == ticket)
        {
            found = 1;
            break;
        }

        if (i == rear)
            break;

        i = (i + 1) % SIZE;
        pos++;
    }

    if (!found)
    {
        printf("Ticket Not Found!\n");
        return;
    }

    i = (front + pos) % SIZE;

    while (i != rear)
    {
        queue[i] = queue[(i + 1) % SIZE];
        i = (i + 1) % SIZE;
    }

    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        rear = (rear - 1 + SIZE) % SIZE;
    }

    printf("Ticket %d Deleted Successfully!\n", ticket);
}


int main()
{
    int choice;

    do
    {
        printf("\n--- Ticket Booking Queue System ---\n");
        printf("1. Book Ticket\n");
        printf("2. Process Ticket\n");
        printf("3. Display Queue\n");
        printf("4. Search Ticket\n");
        printf("5. Delete Ticket\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                bookTicket();
                break;

            case 2:
                processTicket();
                break;

            case 3:
                displayQueue();
                break;

            case 4:
                searchTicket();
                break;

            case 5:
                deleteTicket();
                break;

            case 6:
                printf("Exiting the system...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while (choice != 6);

    return 0;
}
