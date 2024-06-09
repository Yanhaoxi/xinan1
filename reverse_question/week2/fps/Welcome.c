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
    // 实现函数
    while (getchar() != '\n') continue;
}
void updateRankAndPrintResult(Result* result) {
    if (result->score > rank_list.log[RANK_LEN-1].score) {
        printf("恭喜！您进入了排行榜！\n");
        printf("请输入您的名字：\n");
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
        printf("什么你你你竟然打破了%s的最高记录，不可思议！！！！！！！！！！！！\n",FIRST_USER);
        printf("你才是游戏大师，是时候把作为游戏界最高荣誉的flag交给你了\n");
        printf("flag: %s \n",result->backup.value);
    }
    else{
        printf("继续努力吧！\n");
    }
    }
    else {
        printf("很遗憾，您未能进入排行榜。\n");
    }
}

int Game(){
    Result result=Gamestart();
    updateRankAndPrintResult(&result);
}
int rank() {
    system("cls");
    printf("排行榜\n");
    for(int i=0;i<RANK_LEN;i++){
        printf("%d. %s: %d\n",i+1,rank_list.log[i].name,rank_list.log[i].score);
    }
    return 0;
}

int main() {
    int choice;
    while (1) {
        system("cls");
        // 显示开始界面
        printf("欢迎来到射击小游戏！\n");
        printf("1. 开始游戏\n");
        printf("2. 排行榜\n");
        printf("3. 退出\n");
        printf("请选择一个选项：");

        // 读取用户输入
        scanf("%d", &choice);
            // 清理输入缓冲区
        ClearInputBuffer();
        // 处理用户选择
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
                printf("感谢您的游戏，再见！\n");
                system("pause");
                return 0;
            default:
                printf("无效选择，请重新选择。\n");\
                system("pause");
        }
    }
}

// 开始游戏的
