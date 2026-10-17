#include <stdio.h>
#include <string.h>
#define SIZE 5

int queue[SIZE];
int front = -1, rear = -1;

/* Reads one integer after showing the prompt.
   Asks again until the user types a valid number.
   Returns 1 on success, 0 if the input has ended (EOF). */
int readInt(const char *prompt, int *value)
{
    char line[64];
    int c;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL)
            return 0;

        /* Discard the rest of an over-long line */
        if (strchr(line, '\n') == NULL)
        {
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }

        if (sscanf(line, "%d", value) == 1)
            return 1;

        printf("Invalid input! Please enter a number.\n");
    }
}

/* Adds a ticket at the rear of the queue */
void bookTicket(void)
{
    int ticket;

    if ((rear + 1) % SIZE == front)
    {
        printf("Booking Queue is Full!\n");
        return;
    }

    if (!readInt("Enter Ticket Number: ", &ticket))
        return;

    if (front == -1)
        front = 0;

    rear = (rear + 1) % SIZE;
    queue[rear] = ticket;

    printf("Ticket booked successfully!\n");
}

/* Removes the oldest ticket from the front of the queue */
void processTicket(void)
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

/* Prints all tickets from front to rear */
void displayQueue(void)
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

/* Looks for a ticket number in the queue */
void searchTicket(void)
{
    int ticket, i;

    if (front == -1)
    {
        printf("Queue is Empty!\n");
        return;
    }

    if (!readInt("Enter Ticket Number to Search: ", &ticket))
        return;

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


/* Removes a ticket from any position and closes the gap */
void deleteTicket(void)
{
    int ticket, i, pos, found = 0;

    if (front == -1)
    {
        printf("Queue is Empty!\n");
        return;
    }

    if (!readInt("Enter Ticket Number to Delete: ", &ticket))
        return;

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


int main(void)
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

        if (!readInt("Enter your choice: ", &choice))
        {
            printf("\nInput ended. Exiting the system...\n");
            break;
        }

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
