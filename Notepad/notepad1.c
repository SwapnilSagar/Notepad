#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char data;
    struct node *next;
} Node;

Node *head = NULL;

int row, col;
int x, y; // coordinates of cursor.
int l;    // max length of notepad.

Node *getnode(char v)
{
    Node *temp;
    temp = (Node *)malloc(sizeof(Node));
    temp->data = v;
    temp->next = NULL;
    return temp;
}

void insertend(char v)
{
    Node *ptr;
    ptr = getnode(v);
    if (head == NULL)
    {
        head = ptr;
    }
    else
    {
        Node *run = head;
        while (run->next != NULL)
        {
            run = run->next;
        }
        run->next = ptr;
    }
}
void display()
{
    Node *run = head;
    int i;
    for (i = 0; i < l; i++)
    {
        if (i % col == 0)
            printf("\n");
        if (run == NULL)
            break;
        printf("%c ", run->data);
        run = run->next;
    }
    printf("\nCursor is at %d row and %d column.\n", x, y);
}

Node *movecursor(int a, int b)
{
    Node *run = head;
    int i;
    for (i = 0; i < (col * a) + b; i++)
    {
        run = run->next;
    }
    display();
    return run;
}

void start(char a[])
{
    int i, j, k;
    k = strlen(a);
    if (k > l)
    {
        j = l;
        x = row;
        y = col;
    }
    else
    {
        j = k;
        x = (k / col) + 1;
        y = (k % col) + 1;
    }
    for (i = 0; i < j; i++)
    {
        insertend(a[i]);
    }
}



void insert(char v, Node *add)
{
    Node *ptr;
    Node *run = head;
    ptr = getnode(v);
    if (add == head)
    {
        ptr->next = head;
        head = ptr;
        display();
    }
    else
    {
        while (run->next != add)
        {
            run = run->next;
        }
        ptr->next = run->next;
        run->next = ptr;
        y++;
        if (y > col && x <= row)
        {
            y = 1;
            x++;
        }
        display();
    }
}

void count(char s, Node *add)
{
    int i;
    int cnt = 0;
    Node *run = head;
    for (i = 0; i < l; i++)
    {
        if (run == NULL)
        {
            break;
        }
        run = run->next;
    }
    while (add != run)
    {
        if (add->data == s)
        {
            cnt++;
        }
        add = add->next;
    }
    printf("\nNumber of '%c' in notepad after %d row and %d column is/are %d \n", s, x, y, cnt);
}



int main()
{
    Node *add;
    int i;     // i is for using functions in switch
    char c, s; // c is for inserting char, and s is for searching any character
    printf("Enter row and column in notepad.\n");
    scanf("%d %d", &row, &col);

    l = row * col;
    char a[l];
    printf("\n\nEnter string.\n");
    scanf("%s", a);

    start(a);
    add = movecursor(x - 1, y - 1);

    do
    {
        printf("\n\nSelect task to perform.\n");
        printf("1.Start (to start and move cursor at the beginning).\n");
        printf("2.Move cursor.\n");
        printf("3.Insert character.\n");
        printf("4.Count character.\n");
        printf("5.Exit.\n\n");
        scanf("%d", &i);
        printf("\n");
        switch (i)
        {
        case 1:
            x = 1;
            y = 1;
            add = movecursor(x - 1, y - 1);
            break;

        case 2:
            printf("\nEnter row column.\n");
            scanf("%d %d", &x, &y);
            add = movecursor(x - 1, y - 1);
            break;

        case 3:
            printf("\nEnter character.\n");
            scanf(" %c", &c);
            insert(c, add);
            break;

        case 4:
            printf("\nEnter character to be counted.\n");
            scanf(" %c", &s);
            count(s, add);
            break;
        default:
            printf("\nProgram ended.\n");
        }
    } while (i < 5);
    return 0;
}
