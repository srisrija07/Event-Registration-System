#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Participant {
    char name[50];
    int age;
    char email[50];
} participants[MAX];

int count = 0;

void addParticipant() {
    FILE *fp = fopen("participants.txt", "a");
    if (!fp) return;
    printf("Enter Name: ");
    scanf(" %[^\n]", participants[count].name);
    printf("Enter Age: ");
    scanf("%d", &participants[count].age);
    printf("Enter Email: ");
    scanf(" %[^\n]", participants[count].email);
    fprintf(fp, "%s,%d,%s\n", participants[count].name, participants[count].age, participants[count].email);
    fclose(fp);
    count++;
    printf("Participant added!\n");
}

void viewParticipants() {
    FILE *fp = fopen("participants.txt", "r");
    if (!fp) {
        printf("No participants found.\n");
        return;
    }
    char line[200];
    printf("\n--- Registered Participants ---\n");
    while (fgets(line, sizeof(line), fp))
        printf("%s", line);
    fclose(fp);
}

void searchParticipant() {
    char searchName[50], line[200], name[50], email[50];
    int age;
    printf("Enter name to search: ");
    scanf(" %[^\n]", searchName);
    FILE *fp = fopen("participants.txt", "r");
    if (!fp) return;
    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^,],%d,%[^\n]", name, &age, email);
        if (strcasecmp(name, searchName) == 0) {
            printf("\nFound: %s, %d, %s\n", name, age, email);
            found = 1;
            break;
        }
    }
    if (!found) printf("No participant found with that name.\n");
    fclose(fp);
}

int main() {
    int choice;
    while (1) {
        printf("\n=== EVENT REGISTRATION SYSTEM ===\n");
        printf("1. Add Participant\n");
        printf("2. View All Participants\n");
        printf("3. Search Participant\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addParticipant(); break;
            case 2: viewParticipants(); break;
            case 3: searchParticipant(); break;
            case 4: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
}

