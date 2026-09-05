// Include standard I/O library for printf, fgets, and sscanf
#include <stdio.h>
// Include string library for string manipulation functions like strstr and strcspn
#include <string.h>

// Define the maximum number of conversation turns to store in history
#define MAX_HISTORY 5
// Define the maximum character length for a single input or output string
#define MAX_STR_LEN 256

// Define a struct to manage the conversation state and memory safely
typedef struct {
    // 2D array to hold up to 5 user input strings
    char user_inputs[MAX_HISTORY][MAX_STR_LEN];
    // 2D array to hold up to 5 model output strings
    char model_outputs[MAX_HISTORY][MAX_STR_LEN];
    // Integer to track the total number of turns processed
    int turn_count;
} ConversationHistory;

// Function prototype for our mock model
void mock_model(char *input, char *output);

// Main entry point of the C program
int main() {
    // Declare a buffer to store the raw user input from the terminal
    char input_buffer[MAX_STR_LEN];
    // Declare a buffer to store the generated response from the mock model
    char output_buffer[MAX_STR_LEN];
    
    // Initialize our conversation history struct with a turn count of 0
    ConversationHistory history;
    history.turn_count = 0;

    // Print the initial startup greeting prompt to the terminal
    printf("LLM Mini-Harness Initialized. Type 'exit' to shut down.\n");
    printf("========================================================\n");

    // Start an infinite while loop that continuously asks for user input
    while (1) {
        // Prompt the user for input
        printf("\nUser> ");
        
        // Read a string from standard input (the terminal) using fgets
        if (fgets(input_buffer, MAX_STR_LEN, stdin) == NULL) {
            // If fgets fails (e.g., EOF), break out of the loop safely
            break;
        }

        // Remove the trailing newline character added by fgets
        input_buffer[strcspn(input_buffer, "\n")] = '\0';

        // Check if the user typed exactly 'exit' to trigger a safe shutdown
        if (strcmp(input_buffer, "exit") == 0) {
            // Print a shutdown message
            printf("Harness shutting down safely...\n");
            // Break the infinite loop to end the program
            break;
        }

        // Pass the user input into the mock model function to get a simulated response
        mock_model(input_buffer, output_buffer);

        // Determine the current index in our circular history buffer (0 to 4)
        int history_index = history.turn_count % MAX_HISTORY;
        
        // Copy the user's input into the history array at the correct index
        strcpy(history.user_inputs[history_index], input_buffer);
        // Copy the model's output into the history array at the correct index
        strcpy(history.model_outputs[history_index], output_buffer);
        
        // Increment the total turn count to keep track of state
        history.turn_count++;

        // Print the mock model's simulated text back to the terminal
        printf("LLM> %s\n", output_buffer);
    }

    // Return 0 to indicate successful execution
    return 0;
}

// Function that mimics an LLM and handles simulated tool execution
void mock_model(char *input, char *output) {
    // Variables to hold numbers for the mathematical calculation tool
    int num1, num2;

    // Check if the input contains the keyword "hello" as a substring
    if (strstr(input, "hello") != NULL) {
        // If it does, populate the output buffer with a hardcoded greeting
        strcpy(output, "Hello there! How can I assist you today?");
    }
    // Attempt to execute a mathematical calculation tool if the input matches a specific pattern
    // sscanf checks if the input is formatted like "calc [number] + [number]"
    else if (sscanf(input, "calc %d + %d", &num1, &num2) == 2) {
        // If the pattern matches, perform the calculation and format the output string
        sprintf(output, "[Tool Execution] The sum of %d and %d is %d.", num1, num2, num1 + num2);
    }
    // If the input doesn't match "hello" or the math tool pattern
    else {
        // Echo the user's exact input back to them
        sprintf(output, "%s", input);
    }
}
