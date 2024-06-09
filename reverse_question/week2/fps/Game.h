#include "clarify.h"
#define MAP_WIDTH 70
#define MAP_HEIGHT 30
#define WALL_ICON '='
#define PLAYER_ICON 'P'
#define MONSTER_ICON 'M'
#define MONSTER_BULLET_ICON '@'
#define EMPTY_SPACE_ICON ' '

typedef enum {
    W, 
    WD,
    D, 
    DS,
    S, 
    SA,
    A, 
    AW,
    NOP
} Direction;

typedef struct {
    int x, y;
} Position;


typedef struct {
    Position pos;
    Direction direction;
} MonsterBullet;

typedef struct {
    Position pos;
    int health;
    Backup_List backup;
} Player;

typedef enum{
    Dead,
    Alive,
    Nborn
}State;

typedef struct {
    Position pos;
    State state;
} Monster;


typedef struct MBNode {
    MonsterBullet monsterbullet;
    struct MBNode *prev;
    struct MBNode *next;
} MBNode;


typedef struct {
    MBNode *head;
    MBNode *tail;
} DoublyMBLinkedList;

DoublyMBLinkedList initMBList() {
    DoublyMBLinkedList list;
    list.head = NULL;
    list.tail = NULL;
    return list;
}


void addMBFront(DoublyMBLinkedList *list, MonsterBullet value) {
    MBNode *mbnode = (MBNode *)malloc(sizeof(MBNode));
    mbnode->monsterbullet = value;
    mbnode->prev = NULL;
    mbnode->next = list->head;

    if (list->head != NULL) {
        list->head->prev = mbnode;
    }
    list->head = mbnode;

    if (list->tail == NULL) {
        list->tail = mbnode;
    }
}


void addMBBack(DoublyMBLinkedList *list, MonsterBullet value) {
    MBNode *mbnode = (MBNode *)malloc(sizeof(MBNode));
    mbnode->monsterbullet = value;
    mbnode->next = NULL;
    mbnode->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = mbnode;
    }
    list->tail = mbnode;

    if (list->head == NULL) {
        list->head = mbnode;
    }
}

// void printMBList(DoublyMBLinkedList *list) {
//     MBNode *current = list->head;
//     while (current != NULL) {
//         printf("%d ", current->monsterbullet);
//         current = current->next;
//     }
//     printf("\n");
// }

void deleteMBNode(DoublyMBLinkedList *list, MBNode *mbnode) {
    if (mbnode == list->head) {
        list->head = mbnode->next;
    }
    if (mbnode == list->tail) {
        list->tail = mbnode->prev;
    }
    if (mbnode->prev != NULL) {
        mbnode->prev->next = mbnode->next;
    }
    if (mbnode->next != NULL) {
        mbnode->next->prev = mbnode->prev;
    }
    free(mbnode);
}

void deleteMBList(DoublyMBLinkedList *list) {
    MBNode *current = list->head;
    while (current != NULL) {
        MBNode *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

#define MONSTER_NUM 35
