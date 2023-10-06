#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

typedef struct {
    char* buffer; // Buffer to store the text
    int bufferSize; // Size of the buffer
    int scrollPosition; // Current scroll position
} TextEditor;

TextEditor* createEditor() {
    TextEditor* editor = (TextEditor*)malloc(sizeof(TextEditor));
    editor->buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
    editor->bufferSize = BUFFER_SIZE;
    editor->scrollPosition = 0;
    return editor;
}

void destroyEditor(TextEditor* editor) {
    free(editor->buffer);
    free(editor);
}

void loadText(TextEditor* editor, const char* filename) {
    FILE* file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Check if the buffer needs to be resized
    if (fileSize > editor->bufferSize) {
        editor->buffer = (char*)realloc(editor->buffer, sizeof(char) * fileSize);
        editor->bufferSize = fileSize;
    }

    // Copy file contents into the buffer
    fread(editor->buffer, sizeof(char), fileSize, file);
    fclose(file);
}

void displayText(TextEditor* editor) {
    // Calculate the portion of text to display based on scroll position
    int start = editor->scrollPosition;
    int end = start + 10; // Display 10 characters

    if (end > strlen(editor->buffer)) {
        end = strlen(editor->buffer);
    }

    // Print the portion of text
    for (int i = start; i < end; i++) {
        printf("%c", editor->buffer[i]);
    }
    printf("\n");
}

void scrollText(TextEditor* editor, int amount) {
    editor->scrollPosition += amount;

    // Ensure scroll position is within valid range
    if (editor->scrollPosition < 0) {
        editor->scrollPosition = 0;
    }
    else if (editor->scrollPosition > strlen(editor->buffer)) {
        editor->scrollPosition = strlen(editor->buffer);
    }
}

int main() {
    TextEditor* editor = createEditor();

    loadText(editor, "file.txt");
    displayText(editor);

    // User interaction (scroll down by 5 characters)
    scrollText(editor, 10);
    displayText(editor);

    destroyEditor(editor);
    return 0;
}