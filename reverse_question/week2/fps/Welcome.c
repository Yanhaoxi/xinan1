#include"clarify.h"
###exec:
flag_list=[ord(i) for i in flag]
#flag_list.sort(reverse=True)
flag_list.sort()
score=sum([flag_list[i]*(i+1) for i in range(35)])-1
###
# define FIRST_SCORE ###eval:score###
# define FIRST_USER "yhx"
Rank_List rank_list={{FIRST_USER,FIRST_SCORE}};
void ClearInputBuffer(void) {
    // ʵ�ֺ���
    while (getchar() != '\n') continue;
}
void updateRankAndPrintResult(Result* result) {
    if (result->score > rank_list.log[RANK_LEN-1].score) {
        printf("��ϲ�������������а�\n");
        printf("�������������֣�\n");
        char name[NAME_LEN];
        fgets(name, NAME_LEN, stdin);
        char *newline = strchr(name, '\n');
        if (newline) *newline = '\0';
        for(int i = 0; i < RANK_LEN; i++) {
            if(result->score > rank_list.log[i].score) {
                for(int j = RANK_LEN - 1; j > i; j--) {
                    rank_list.log[j] = rank_list.log[j - 1];
                }
                strcpy(rank_list.log[i].name, name);
                rank_list.log[i].score = result->score;
                break;
            }
        }
    if(result->score>FIRST_SCORE){
        printf("ʲô�����㾹Ȼ������%s����߼�¼������˼�飡����������������������\n",FIRST_USER);
        printf("�������Ϸ��ʦ����ʱ�����Ϊ��Ϸ�����������flag��������\n");
        printf("flag: %s \n",result->backup.value);
    }
    else{
        printf("����Ŭ���ɣ�\n");
    }
    }
    else {
        printf("���ź�����δ�ܽ������а�\n");
    }
}

int Game(){
    Result result=Gamestart();
    updateRankAndPrintResult(&result);
}
int rank() {
    system("cls");
    printf("���а�\n");
    for(int i=0;i<RANK_LEN;i++){
        printf("%d. %s: %d\n",i+1,rank_list.log[i].name,rank_list.log[i].score);
    }
    return 0;
}

int main() {
    int choice;
    while (1) {
        system("cls");
        // ��ʾ��ʼ����
        printf("��ӭ�������С��Ϸ��\n");
        printf("1. ��ʼ��Ϸ\n");
        printf("2. ���а�\n");
        printf("3. �˳�\n");
        printf("��ѡ��һ��ѡ�");

        // ��ȡ�û�����
        scanf("%d", &choice);
            // �������뻺����
        ClearInputBuffer();
        // �����û�ѡ��
        switch (choice) {
            case 1:
                Game();
                system("pause");
                break;
            case 2:
                rank();
                system("pause");
                break;
            case 3:
                printf("��л������Ϸ���ټ���\n");
                system("pause");
                return 0;
            default:
                printf("��Чѡ��������ѡ��\n");\
                system("pause");
        }
    }
}

// ��ʼ��Ϸ��
