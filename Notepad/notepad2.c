#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the linked list
typedef struct Node {
    char data;
    struct Node* next;
    struct Node* prev;
} Node;

// Global variables representing the current position and head of the linked list
Node* current_pos;
Node* head;

// Function to insert a character at the current position
void insertChar(char c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = c;
    
    if (current_pos == NULL) {  // If the linked list is empty
        newNode->next = NULL;
        newNode->prev = NULL;
        head = newNode;
        current_pos = newNode;
    } else {
        newNode->next = current_pos->next;
        newNode->prev = current_pos;
        
        if (current_pos->next != NULL) {
            current_pos->next->prev = newNode;
        }
        
        current_pos->next = newNode;
        current_pos = newNode;
    }
}

// Function to delete character at the current position
void deleteChar() {
    if (current_pos == NULL) {
        return;
    }
    
    Node* temp = current_pos;
    
    if (current_pos->prev != NULL) {
        current_pos->prev->next = current_pos->next;
        
        if (current_pos->next != NULL) {
            current_pos->next->prev = current_pos->prev;
            current_pos = current_pos->next;
        } else {
            current_pos = current_pos->prev;
        }
    } else {
        head = current_pos->next;
        
        if (current_pos->next != NULL) {
            current_pos->next->prev = NULL;
            current_pos = current_pos->next;
        } else {
            current_pos = NULL;
        }
    }
    
    free(temp);
}

// Function to display the contents of the linked list
void displayText() {
    Node* temp = head;
    
    while (temp != NULL) {
        printf("%c", temp->data);
        temp = temp->next;
    }
    
    printf("\n");
}

int main() {
    char choice;
    char c;
    
    current_pos = NULL;
    head = NULL;
    
    printf("Notepad Application\n");
    
    do {
        printf("\nMenu:\n");
        printf("1. Insert Character\n");
        printf("2. Delete Character\n");
        printf("3. Display Text\n");
        printf("4. Quit\n\n");
        
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        
        switch(choice) {
            case '1':
                printf("Enter character to insert: ");
                scanf(" %c", &c);
                insertChar(c);
                break;
            case '2':
                deleteChar();
                break;
            case '3':
                printf("Text: ");
                displayText();
                break;
            case '4':
                printf("Quitting the application...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != '4');
    
    return 0;
}