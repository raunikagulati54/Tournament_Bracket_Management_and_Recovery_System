
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEAM_SIZE 40
#define MAX_MATCHES 8
#define STACK_SIZE 50
#define FILE_NAME "tournament.dat"

typedef struct MatchNode {
    int id;
    char team1[TEAM_SIZE];
    char team2[TEAM_SIZE];
    char winner[TEAM_SIZE];
    int played;
    struct MatchNode *left;
    struct MatchNode *right;
    struct MatchNode *parent;
} MatchNode;

typedef struct Snapshot {
    char team1[MAX_MATCHES][TEAM_SIZE];
    char team2[MAX_MATCHES][TEAM_SIZE];
    char winner[MAX_MATCHES][TEAM_SIZE];
    int played[MAX_MATCHES];
} Snapshot;

typedef struct Stack {
    Snapshot data[STACK_SIZE];
    int top;
} Stack;

MatchNode *matches[MAX_MATCHES];
Stack undoStack;

void saveTournament();
int loadTournament();

void initStack() {
    undoStack.top = -1;
}

void pushSnapshot() {
    int i;
    Snapshot s;

    for (i = 1; i < MAX_MATCHES; i++) {
        strcpy(s.team1[i], matches[i]->team1);
        strcpy(s.team2[i], matches[i]->team2);
        strcpy(s.winner[i], matches[i]->winner);
        s.played[i] = matches[i]->played;
    }

    if (undoStack.top == STACK_SIZE - 1) {
        for (i = 1; i < STACK_SIZE; i++) {
            undoStack.data[i - 1] = undoStack.data[i];
        }
        undoStack.top--;
    }

    undoStack.data[++undoStack.top] = s;
}

void restoreSnapshot(Snapshot s) {
    int i;

    for (i = 1; i < MAX_MATCHES; i++) {
        strcpy(matches[i]->team1, s.team1[i]);
        strcpy(matches[i]->team2, s.team2[i]);
        strcpy(matches[i]->winner, s.winner[i]);
        matches[i]->played = s.played[i];
    }
}

void createTree() {
    int i;

    for (i = 1; i < MAX_MATCHES; i++) {
        matches[i] = (MatchNode *)malloc(sizeof(MatchNode));
        if (matches[i] == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        matches[i]->id = i;
        matches[i]->team1[0] = '\0';
        matches[i]->team2[0] = '\0';
        matches[i]->winner[0] = '\0';
        matches[i]->played = 0;
        matches[i]->left = NULL;
        matches[i]->right = NULL;
        matches[i]->parent = NULL;
    }

    matches[5]->left = matches[1];
    matches[5]->right = matches[2];
    matches[1]->parent = matches[5];
    matches[2]->parent = matches[5];

    matches[6]->left = matches[3];
    matches[6]->right = matches[4];
    matches[3]->parent = matches[6];
    matches[4]->parent = matches[6];

    matches[7]->left = matches[5];
    matches[7]->right = matches[6];
    matches[5]->parent = matches[7];
    matches[6]->parent = matches[7];
}

void clearTournament() {
    int i;

    for (i = 1; i < MAX_MATCHES; i++) {
        matches[i]->team1[0] = '\0';
        matches[i]->team2[0] = '\0';
        matches[i]->winner[0] = '\0';
        matches[i]->played = 0;
    }

    initStack();
}

void setParentTeam(MatchNode *node, const char *winner) {
    MatchNode *parent;

    parent = node->parent;

    if (parent == NULL)
        return;

    if (parent->left == node)
        strcpy(parent->team1, winner);
    else
        strcpy(parent->team2, winner);
}

void createTournament() {
    int i;
    char name[TEAM_SIZE];

    clearTournament();

    printf("\nEnter names of 8 teams:\n");

    for (i = 1; i <= 4; i++) {
        printf("\nMatch %d\n", i);

        printf("Team 1: ");
        scanf(" %39[^\n]", name);
        strcpy(matches[i]->team1, name);

        printf("Team 2: ");
        scanf(" %39[^\n]", name);
        strcpy(matches[i]->team2, name);
    }

    saveTournament();
    printf("\nTournament created successfully.\n");
}

void updateFutureMatches() {
    int i;
    MatchNode *parent;

    for (i = 1; i <= 4; i++) {
        if (matches[i]->played) {
            parent = matches[i]->parent;
            if (parent != NULL)
                setParentTeam(matches[i], matches[i]->winner);
        }
    }

    if (matches[5]->played) {
        parent = matches[5]->parent;
        if (parent != NULL)
            setParentTeam(matches[5], matches[5]->winner);
    }

    if (matches[6]->played) {
        parent = matches[6]->parent;
        if (parent != NULL)
            setParentTeam(matches[6], matches[6]->winner);
    }
}

void displayMatch(int id) {
    MatchNode *m = matches[id];

    printf("Match %d : ", id);

    if (m->team1[0] == '\0')
        printf("TBD");
    else
        printf("%s", m->team1);

    printf("  vs  ");

    if (m->team2[0] == '\0')
        printf("TBD");
    else
        printf("%s", m->team2);

    if (m->played)
        printf("  -> Winner: %s", m->winner);

    printf("\n");
}

void displayBracket() {
    printf("\n================ TOURNAMENT BRACKET ================\n");

    printf("\nQUARTER FINALS\n");
    displayMatch(1);
    displayMatch(2);
    displayMatch(3);
    displayMatch(4);

    printf("\nSEMI FINALS\n");
    displayMatch(5);
    displayMatch(6);

    printf("\nFINAL\n");
    displayMatch(7);

    if (matches[7]->played)
        printf("\nCHAMPION: %s\n", matches[7]->winner);

    printf("=====================================================\n");
}

int validMatch(int id) {
    MatchNode *m = matches[id];

    if (m->team1[0] == '\0' || m->team2[0] == '\0') {
        printf("This match is not ready yet.\n");
        return 0;
    }

    if (m->played) {
        printf("This match has already been completed.\n");
        return 0;
    }

    return 1;
}

void enterResult() {
    int id, choice;
    MatchNode *m;

    printf("\nEnter match number (1-7): ");
    scanf("%d", &id);

    if (id < 1 || id > 7) {
        printf("Invalid match number.\n");
        return;
    }

    if (!validMatch(id))
        return;

    m = matches[id];

    printf("\nMatch %d\n", id);
    printf("1. %s\n", m->team1);
    printf("2. %s\n", m->team2);
    printf("Choose winner: ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2) {
        printf("Invalid choice.\n");
        return;
    }

    pushSnapshot();

    if (choice == 1)
        strcpy(m->winner, m->team1);
    else
        strcpy(m->winner, m->team2);

    m->played = 1;
    setParentTeam(m, m->winner);

    saveTournament();

    printf("Result recorded successfully.\n");
}

void undoLastResult() {
    if (undoStack.top == -1) {
        printf("\nNo action available to undo.\n");
        return;
    }

    restoreSnapshot(undoStack.data[undoStack.top]);
    undoStack.top--;

    saveTournament();
    printf("\nLast result has been recovered successfully.\n");
}

void saveTournament() {
    FILE *fp;
    int i;

    fp = fopen(FILE_NAME, "wb");

    if (fp == NULL)
        return;

    for (i = 1; i < MAX_MATCHES; i++) {
        fwrite(&matches[i]->team1, sizeof(matches[i]->team1), 1, fp);
        fwrite(&matches[i]->team2, sizeof(matches[i]->team2), 1, fp);
        fwrite(&matches[i]->winner, sizeof(matches[i]->winner), 1, fp);
        fwrite(&matches[i]->played, sizeof(matches[i]->played), 1, fp);
    }

    fclose(fp);
}

int loadTournament() {
    FILE *fp;
    int i;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL)
        return 0;

    for (i = 1; i < MAX_MATCHES; i++) {
        fread(&matches[i]->team1, sizeof(matches[i]->team1), 1, fp);
        fread(&matches[i]->team2, sizeof(matches[i]->team2), 1, fp);
        fread(&matches[i]->winner, sizeof(matches[i]->winner), 1, fp);
        fread(&matches[i]->played, sizeof(matches[i]->played), 1, fp);
    }

    fclose(fp);
    updateFutureMatches();
    initStack();

    return 1;
}

void recoverTournament() {
    if (loadTournament())
        printf("\nSaved tournament recovered successfully.\n");
    else
        printf("\nNo saved tournament found.\n");
}

void showChampion() {
    if (matches[7]->played)
        printf("\nCurrent Champion: %s\n", matches[7]->winner);
    else
        printf("\nChampion not decided yet.\n");
}

void freeMemory() {
    int i;

    for (i = 1; i < MAX_MATCHES; i++)
        free(matches[i]);
}

int main() {
    int choice;

    createTree();
    initStack();

    if (loadTournament())
        printf("Previous tournament data recovered automatically.\n");
    else
        printf("No previous tournament found. Create a new tournament.\n");

    do {
        printf("\n========== TOURNAMENT MANAGEMENT SYSTEM ==========\n");
        printf("1. Create New Tournament\n");
        printf("2. Display Tournament Bracket\n");
        printf("3. Enter Match Result\n");
        printf("4. Undo Last Result\n");
        printf("5. Recover Saved Tournament\n");
        printf("6. Show Champion\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createTournament();
                break;
            case 2:
                displayBracket();
                break;
            case 3:
                enterResult();
                break;
            case 4:
                undoLastResult();
                break;
            case 5:
                recoverTournament();
                break;
            case 6:
                showChampion();
                break;
            case 7:
                saveTournament();
                printf("\nThank you.\n");
                break;
            default:
                printf("\nInvalid choice.\n");
        }
    } while (choice != 7);

    freeMemory();
    return 0;
}
