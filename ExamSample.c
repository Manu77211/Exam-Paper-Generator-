#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define the Question structure
typedef struct Question {
    int id;
    char text[200];
    char topic[100];
    char difficulty[20];
    struct Question* next;
} Question;

// Function to add a question
void addQuestion(Question** head) {
    Question* newQuestion = (Question*)malloc(sizeof(Question));
    if (!newQuestion) {
        printf("Memory allocation failed!\n");
        return;
    }


    printf("Enter Question ID: ");
    scanf("%d", &newQuestion->id);

    // Clear the input buffer (to discard the newline left by scanf)
    while (getchar() != '\n');

    printf("Enter Question Text: ");
    fgets(newQuestion->text, 200, stdin);
    strtok(newQuestion->text, "\n");  // Remove the trailing newline

    
    printf("Enter Topic: ");
    scanf("%s", newQuestion->topic);


    printf("Enter Difficulty (easy/medium/hard): ");
    scanf("%s", newQuestion->difficulty);

    newQuestion->next = NULL;

    // Insert the question into the linked list
    if (*head == NULL) {
        *head = newQuestion;
    } else {
        Question* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newQuestion;
    }

    printf("Question added successfully!\n");
}

// Function to display all questions
void displayQuestions(Question* head) {
    if (head == NULL) {
        printf("No questions available.\n");
        return;
    }

    printf("List of Questions:\n");
    printf("ID\tQuestion Text\t\tTopic\t\t\tDifficulty\n");
    printf("-------------------------------------------------------------\n");

    Question* temp = head;
    while (temp != NULL) {
        printf("%d\t%s\t\t%s\t\t\t%s\n", temp->id, temp->text, temp->topic, temp->difficulty);
        temp = temp->next;
    }
}
 

// Function to remove a question
void removeQuestion(Question** head, int id) {
    if (*head == NULL) {
        printf("The question list is empty.\n");
        return;
    }

    Question* temp = *head;
    Question* prev = NULL;

    // first question to be removed(first node)
    if (temp != NULL && temp->id == id) {
        *head = temp->next;  // Update the head to the next node
        free(temp);          
        printf("Question with ID %d removed successfully.\n", id);
        return;
    }

    // Case for questions that are not the head
    while (temp != NULL && temp->id != id) {
        prev = temp;       
        temp = temp->next; 
    }

    // If the question was not found
    if (temp == NULL) {
        printf("Question with ID %d not found.\n", id);
        return;
    }

    // At this point, temp points to the question to be removed
    prev->next = temp->next;  // Bypass the node to be removed
    free(temp);  
    printf("Question with ID %d removed successfully.\n", id);
}




// Function to generate the question paper
void generateQuestionPaper(Question* head) {
    if (head == NULL) {
        printf("No questions available to generate paper.\n");
        return;
    }

    int easyCount, mediumCount, hardCount;
    printf("Enter the number of easy questions: ");
    scanf("%d", &easyCount);
    printf("Enter the number of medium questions: ");
    scanf("%d", &mediumCount);
    printf("Enter the number of hard questions: ");
    scanf("%d", &hardCount);

    // Create arrays to store questions of each difficulty
    Question* easyQuestions = NULL;
    Question* mediumQuestions = NULL;
    Question* hardQuestions = NULL;

    // Separate questions by difficulty
    Question* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->difficulty, "easy") == 0) {
            Question* newEasy = (Question*)malloc(sizeof(Question));
            *newEasy = *temp; // Copy question data
            newEasy->next = easyQuestions;
            easyQuestions = newEasy;
        } else if (strcmp(temp->difficulty, "medium") == 0) {
            Question* newMedium = (Question*)malloc(sizeof(Question));
            *newMedium = *temp; // Copy question data
            newMedium->next = mediumQuestions;
            mediumQuestions = newMedium;
        } else if (strcmp(temp->difficulty, "hard") == 0) {
            Question* newHard = (Question*)malloc(sizeof(Question));
            *newHard = *temp; // Copy question data
            newHard->next = hardQuestions;
            hardQuestions = newHard;
        }
        temp = temp->next;
    }

    // Function to randomly select questions using shuffling
    void selectQuestions(Question* difficultyHead, int count) {
        if (difficultyHead == NULL) {
            printf("No questions available for this difficulty.\n");
            return;
        }

        // Count the total available questions for the selected difficulty
        int total = 0,k,m,n,j;
        Question* temp = difficultyHead;
        while (temp != NULL) {
            total++;
            temp = temp->next;
        }

        if (count > total) {
            printf("Not enough questions available for this difficulty.\n");
            return;
        }

        // Create an array of pointers to questions for easier random access
        Question** questionArray = (Question**)malloc(total * sizeof(Question*));
        temp = difficultyHead;
        for ( k = 0; k < total; k++) {
            questionArray[k] = temp;
            temp = temp->next;
        }

        // Shuffle the array to randomize question order
        srand(time(0));
        for ( m = total - 1; m > 0; m--) {
            int j = rand() % (m + 1);
            Question* tempQuestion = questionArray[m];
            questionArray[m] = questionArray[j];
            questionArray[j] = tempQuestion;
        }

        // Select the first 'count' questions from the shuffled array
        printf("\nQuestions selected:\n");
        for ( n = 0; n < count; n++) {
            printf("%d. %s\n", questionArray[n]->id, questionArray[n]->text);
        }

        free(questionArray);
    }

    // Generate question paper based on difficulty count
    if (easyCount > 0) {
        printf("\nEasy Questions:\n");
        selectQuestions(easyQuestions, easyCount);
    }
    if (mediumCount > 0) {
        printf("\nMedium Questions:\n");
        selectQuestions(mediumQuestions, mediumCount);
    }
    if (hardCount > 0) {
        printf("\nHard Questions:\n");
        selectQuestions(hardQuestions, hardCount);
    }
}



int main() {
    Question* head = NULL;  // Initialize the linked list as empty
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Add a question\n");
        printf("2. Display questions\n");
        printf("3. Remove Questions\n");
        printf("4. Generate question paper\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addQuestion(&head);
                break;
            case 2:
                displayQuestions(head);
                break;
            case 3:
                {
                    int id;
                    printf("Enter Question ID to remove: ");
                    scanf("%d", &id);
                    removeQuestion(&head, id);
                }
                break;
            case 4:
                generateQuestionPaper(head);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

