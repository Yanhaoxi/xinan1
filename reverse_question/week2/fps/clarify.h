#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
# define NAME_LEN 10
typedef struct {
    char name[NAME_LEN];
    int score;
} Player_Score;

# define RANK_LEN 10
typedef struct {
    Player_Score log[RANK_LEN];
} Rank_List;

# define Backup_LEN 36
typedef struct {
    char value[Backup_LEN];
} Backup_List;

typedef struct {
    int score;
    Backup_List backup;
} Result;


Result Gamestart();