#include"Game.h"
###exec:
import random
flag_list=[i for i in flag]
random.shuffle(flag_list)
c_string = "{" + ", ".join(f"'{c}'" for c in flag_list) + "}"

numbers = ['' for i in range(len(flag))]
flag_list.sort()
for i in range(len(flag)):
    tmp=flag_list.index(flag[i])
    numbers[i]=tmp+1
    flag_list[tmp]=''

formatted_string = "{" + ", ".join(map(str, numbers)) + "}"
###
void initializeMap(char map[MAP_HEIGHT][MAP_WIDTH]) {
    // ����ÿһ��
    for (int y = 0; y < MAP_HEIGHT; y++) {
        // ����ÿһ��
        for (int x = 0; x < MAP_WIDTH; x++) {
            // �ж��Ƿ�Ϊ�߽�λ��
            if (y == 0 || y == MAP_HEIGHT - 1 || x == 0 || x == MAP_WIDTH - 1) {
                map[y][x] = WALL_ICON;
            } else {
                map[y][x] = EMPTY_SPACE_ICON; // �ڲ�Ϊ�ո�
            }
        }
    }
}

void printMap(char map[MAP_HEIGHT][MAP_WIDTH]) {
    // ��ӡ��ͼ
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
}


void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printCharAt(int x, int y, char ch) {
    setCursorPosition(x, y);
    printf("%c", ch);
}

void updateMap(char map[MAP_HEIGHT][MAP_WIDTH], char prevMap[MAP_HEIGHT][MAP_WIDTH]) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x] != prevMap[y][x]) {
                printCharAt(x, y, map[y][x]);
            }
        }
    }
}

Player initPlayer() {
    Player player;
    player.pos.x = MAP_WIDTH / 2;
    player.pos.y = MAP_HEIGHT / 2;
    player.health = 5;
    memset(player.backup.value, 0, sizeof(player.backup.value));
    return player;
}

// �����ӵ�//�ӵ�����->�����߼�����->���紦�� (�����˺�ֵ)
int MBfly(char map[MAP_HEIGHT][MAP_WIDTH],DoublyMBLinkedList* monsterBullets){
    MBNode *current= monsterBullets->head;
    int damage = 0;
    while (current != NULL) {
        MonsterBullet bullet = current->monsterbullet;
        char tmp=map[bullet.pos.y][bullet.pos.x];
        if (tmp!=MONSTER_BULLET_ICON && tmp!=MONSTER_ICON){
            MBNode* temp = current->next;
            deleteMBNode(monsterBullets, current);
            current = temp;
            continue;
        }
        map[bullet.pos.y][bullet.pos.x] = EMPTY_SPACE_ICON;
        switch (bullet.direction) {
            case W:
                bullet.pos.y--;
                break;
            case WD:
                bullet.pos.y--;
                bullet.pos.x++;
                break;
            case D:
                bullet.pos.x++;
                break;
            case DS:
                bullet.pos.y++;
                bullet.pos.x++;
                break;
            case S:
                bullet.pos.y++;
                break;
            case SA:
                bullet.pos.y++;
                bullet.pos.x--;
                break;
            case A:
                bullet.pos.x--;
                break;
            case AW:
                bullet.pos.y--;
                bullet.pos.x--;
                break;
            case NOP:
                break;
        }
        switch (map[bullet.pos.y][bullet.pos.x]) {
        case PLAYER_ICON:
            damage++;
        case WALL_ICON:
        case MONSTER_ICON:
        case MONSTER_BULLET_ICON:
            MBNode* temp = current->next;
            deleteMBNode(monsterBullets, current);
            current = temp;
            break;
        case EMPTY_SPACE_ICON:
            map[bullet.pos.y][bullet.pos.x] = MONSTER_BULLET_ICON;
            current->monsterbullet = bullet;
            current = current->next;
            break;
        default:
            fprintf(stderr, "δ֪�ĵ�ͼԪ��\n");
            exit(EXIT_FAILURE);
            break;
        }
    }
    return damage;
}
// ����ƶ�
void PlayerMove(char map[MAP_HEIGHT][MAP_WIDTH],Player*player,char loot_value[MONSTER_NUM+1],Monster Monster_Array[MONSTER_NUM]){
    map[player->pos.y][player->pos.x]=EMPTY_SPACE_ICON;
    Position origin = player->pos;
    if(_kbhit()){
        char input = _getch();
        switch (input) {
        case 'w':
        case 'W':
            player->pos.y--;
            break;
        case 'd':
        case 'D':
            player->pos.x++;
            break;
        case 's':
        case 'S':
            player->pos.y++;
            break;
        case 'a':
        case 'A':
            player->pos.x--;
            break;
        default:
            break;
        }
    }
    char tmp=0;
    switch (map[player->pos.y][player->pos.x])
    {
    case WALL_ICON:
        player->pos=origin;
        break;
    case MONSTER_BULLET_ICON:
        player->health--;
        break;
    case MONSTER_ICON:
        // �ҵ����޲����Ϊ����,����ȡս��Ʒ��ֵ
        for(int i=0;i<MONSTER_NUM;i++){
            if(Monster_Array[i].pos.x==player->pos.x && Monster_Array[i].pos.y==player->pos.y && Monster_Array[i].state==Alive){
                Monster_Array[i].state=Dead;
                tmp=loot_value[i];
                break;
            }
        }
        // if (loot_value==0){
        //     raise("���ޱ�����ر��");
        // }
        for(int i=0;i<Backup_LEN;i++){
            if(player->backup.value[i]==0){
                player->backup.value[i]=tmp;
                break;
            }
        }
    case EMPTY_SPACE_ICON:
        break;
    default:
        fprintf(stderr, "δ֪�ĵ�ͼԪ��\n");
        exit(EXIT_FAILURE);
        break;
    }
    map[player->pos.y][player->pos.x] = PLAYER_ICON;
}

#include <time.h>    // ���� time()

// ��ʼ�������������
void initRand() {
    srand(time(NULL));
}

// ����һ������ 0 �� 1 ֮������������
double randomDouble() {
    return (double)rand() / (double)RAND_MAX;
}

// �����ƶ�
void MonsterMove(char map[MAP_HEIGHT][MAP_WIDTH], Monster Monster_Array[MONSTER_NUM], Player player,DoublyMBLinkedList* monsterBullets ) {
    Position playerPos = player.pos;
    for(int i = 0; i < MONSTER_NUM; i++) {
        if(Monster_Array[i].state == Alive) {
            map[Monster_Array[i].pos.y][Monster_Array[i].pos.x] = EMPTY_SPACE_ICON;
            Position origin = Monster_Array[i].pos;
            double actionProb = randomDouble();
            if(actionProb < 0.10){
                // �����������Ҷ��
                if(Monster_Array[i].pos.x < playerPos.x) {
                    Monster_Array[i].pos.x--;
                } else if(Monster_Array[i].pos.x > playerPos.x) {
                    Monster_Array[i].pos.x++;
                }

                if(Monster_Array[i].pos.y < playerPos.y) {
                    Monster_Array[i].pos.y--;
                } else if(Monster_Array[i].pos.y > playerPos.y) {
                    Monster_Array[i].pos.y++;
                }
            }
            else if(actionProb < 0.20){
                // ���������Զ��ǽ�ķ����ƶ�
                int left_distance = Monster_Array[i].pos.x;
                int right_distance = MAP_WIDTH - 1 - Monster_Array[i].pos.x;
                int up_distance = Monster_Array[i].pos.y;
                int down_distance = MAP_HEIGHT - 1 - Monster_Array[i].pos.y;
            
                if(left_distance > right_distance && left_distance > up_distance && left_distance > down_distance) {
                    Monster_Array[i].pos.x--;
                } else if(right_distance > up_distance && right_distance > down_distance) {
                    Monster_Array[i].pos.x++;
                } else if(up_distance > down_distance) {
                    Monster_Array[i].pos.y--;
                } else {
                    Monster_Array[i].pos.y++;
                }
            }
            switch (map[Monster_Array[i].pos.y][Monster_Array[i].pos.x]) {
            case WALL_ICON:
            case MONSTER_ICON:
            case MONSTER_BULLET_ICON:
                Monster_Array[i].pos = origin;
                break;
            case PLAYER_ICON:
                // raise("����������ص�");
                break;
            case EMPTY_SPACE_ICON:
                break;
            default:
                fprintf(stderr, "δ֪�ĵ�ͼԪ��\n");
                exit(EXIT_FAILURE);
                break;
            }
            actionProb = randomDouble();
            if(actionProb < 0.10){
                MonsterBullet newBullet;
                newBullet.pos = Monster_Array[i].pos;
                switch(rand()%8){
                    case 0:
                        newBullet.direction = W;
                        break;
                    case 1:
                        newBullet.direction = WD;
                        break;
                    case 2:
                        newBullet.direction = D;
                        break;
                    case 3:
                        newBullet.direction = DS;
                        break;
                    case 4:
                        newBullet.direction = S;
                        break;
                    case 5:
                        newBullet.direction = SA;
                        break;
                    case 6:
                        newBullet.direction = A;
                        break;
                    case 7:
                        newBullet.direction = AW;
                        break;
                }
            addMBBack(monsterBullets, newBullet);
            }
        map[Monster_Array[i].pos.y][Monster_Array[i].pos.x] = MONSTER_ICON;
        }
    }
}
// ����һ������ min �� max ֮����������
int randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

// �ڵ�ͼ������һ������
void generateMonster(char map[MAP_HEIGHT][MAP_WIDTH], Monster Monster_Array[MONSTER_NUM],int Monster_id) {
    int x, y;
    do {
        x = randomInt(0, MAP_WIDTH - 1);
        y = randomInt(0, MAP_HEIGHT - 1);
    } while(map[y][x] != EMPTY_SPACE_ICON);  // ȷ������ǿյ�

    Monster_Array[Monster_id].pos.x = x;
    Monster_Array[Monster_id].pos.y = y;
    Monster_Array[Monster_id].state = Alive;
    map[y][x] = MONSTER_ICON;
}

void clearLine(int lineNumber, int width) {
    setCursorPosition(0, lineNumber); // ������ƶ���ָ���еĿ�ʼ
    for (int i = 0; i < width; i++) {
        printf(" "); // ��ӡ�ո����������
    }
    setCursorPosition(0, lineNumber); // �ٴν�����ƻ����ף�׼���µ����
}

void printHealth(Player* player) {
    static int previous_health = -1;
    if (player->health != previous_health) {
        setCursorPosition(0, MAP_HEIGHT);  // ������ƶ�����ͼ�·�
        clearLine(MAP_HEIGHT, MAP_WIDTH);
        printf("����ֵ��%d\n", player->health);
        previous_health = player->health;
    }
}

void printBackup(Player* player) {
    static char previous_backup[Backup_LEN] = "";
    if (strcmp(player->backup.value, previous_backup) != 0) {
        setCursorPosition(0, MAP_HEIGHT + 1);
        clearLine(MAP_HEIGHT + 1, MAP_WIDTH);
        printf("ս��Ʒ��%s\n", player->backup.value);
        strcpy(previous_backup, player->backup.value);
    }
}

int calculateScore(Player* player, int *prize) {
    int score = 0;
    for(int i = 0; i < MONSTER_NUM; i++) {
        score += player->backup.value[i] * prize[i];
    }
    return score;
}

void printScore(int score) {
    static int previous_score = -1;
    if (score != previous_score) {
        setCursorPosition(0, MAP_HEIGHT + 2);
        clearLine(MAP_HEIGHT + 2, MAP_WIDTH);
        printf("�÷֣�%d\n", score);
        previous_score = score;
    }
}

Result Gamestart() {
    system("cls");
    char map[MAP_HEIGHT][MAP_WIDTH];
    char pre_map[MAP_HEIGHT][MAP_WIDTH];
    initializeMap(map);
    memcpy(pre_map, map, sizeof(map));
    printMap(map);
    Player player = initPlayer();
    DoublyMBLinkedList monsterBullets = initMBList();
    //������ս��Ʒ�б�
    Monster Monster_Array[MONSTER_NUM];
    char loot_value[MONSTER_NUM+1]=###eval:c_string###;
    for(int i=0;i<MONSTER_NUM;i++){
        Monster_Array[i].state=Nborn;
    }
    int score=0;
    int Monster_id=0;//�������ɵĹ���id
    int prize[MONSTER_NUM]=###eval:formatted_string###;
    printf("���������ʼ��Ϸ\n");
    system("pause");
    bool finished=false;
    while(!finished){

        // �����Ļ
        // system("cls");
        player.health-=MBfly(map,&monsterBullets);
        PlayerMove(map,&player,loot_value,Monster_Array);
        MonsterMove(map,Monster_Array,player,&monsterBullets);
        if (Monster_id<MONSTER_NUM){
            double prob = randomDouble();
            if(prob < 0.1){
                generateMonster(map, Monster_Array,Monster_id);
                Monster_id++;
            }
        }
        // printMap(map);
        updateMap(map, pre_map);
        memcpy(pre_map, map, sizeof(map));

        printHealth(&player);
        printBackup(&player);
        score = calculateScore(&player, prize);
        printScore(score);

        if(player.health<=0){
            break;
        }
        for(int i=0;i<MONSTER_NUM;i++){
            if(Monster_Array[i].state!=Dead){
                break;
            }
            if(i==MONSTER_NUM-1){
                finished=true;
            }
        }
        Sleep(100);
    }
    deleteMBList(&monsterBullets);
    return (Result){score,player.backup};
}