#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _item {
    char *entry;
    struct _item *next;
} Item;

Item *addFront(Item *, char *);
Item *buildList();
Item *searchList(Item *, char *);
void printList(Item *);
void freeList(Item *);

int main()  {
    // build a linked list from a text file
    Item *head = buildList();
    if (!head) 
        return 1;
    // search the file
    Item *results;
    char target[20];
    while (1) {
        printf("Enter a query, EOF to quit: ");
        scanf("%s", target);
        if (feof(stdin)) break;

        results = searchList(head, target);
        if (results)
            printList(results);
        else
            printf("No results\n");
    }

    freeList(head);
    free(results);
    return 0;
}

Item *addFront(Item *head, char *data)    {
    Item *h = malloc(sizeof(Item));
    h->next = head;
    h->entry = data;
    return h;
}

Item *searchList(Item *head, char *target) {
    Item *results = NULL;
    int len = strlen(target);
    while (head != NULL)    {
        int match = 0;
        // record how many consecutive characters match the target
        for (int i = 0; i < len; i++)   {
            if (tolower(target[i]) != tolower(head->entry[i]))
                break;
            match++;
        }
        // if it's a full match, add to new linked list
        if (match == len)
            results = addFront(results, head->entry);
        head = head->next;
    }
    return results;
}

void printList(Item *head)  {
    while (head != NULL)    {
        printf("%s\n", head->entry);
        head = head->next;
    }
}

Item *buildList()   {
    char fileName[20];
    Item *head = NULL;
    printf("Enter the file name: ");
    scanf("%s", fileName);

    FILE *fp = fopen(fileName, "r");
    if (!fp)    {
        printf("Could not open '%s'\n", fileName);
        return NULL;
    }
    while (1)    {
        if (feof(fp))    break;
        char *w = malloc(sizeof(char) * 50);
        fscanf(fp, "%s", w);
        head = addFront(head, w);
    }
    fclose(fp);
    return head;
}

void freeList(Item *head)   {
    while (head != NULL)    {
        free(head->entry);
        head = head->next;
    }
    free(head);
}
