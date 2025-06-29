#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


typedef struct{
    int data[100][3];
    char nameList[100][24];
    char absorbList[100][24];
    char size;
}Blood;

char noBlood[] = "noBlood";
char backupName[] = "pigBackup.bin";
char fileName[] = "pig.bin";

void initBlood(Blood *b);
void insertBlood(Blood *b, int mode);
void checkBlood(Blood *b);
void listBlood(Blood *b);
int isAbsorbed(Blood *b, char name[]);
void addAbsorbed(Blood *b);
int  inList(Blood *b, char name[], int *index);
void showAbsorbed(Blood *b);
void deleteBlood(Blood *b, char name[], int mode);

void option(Blood *b, int *runFlag);
void saveTime();
void writeData(Blood *b, char fileName[], int mode);
int readAndBackup(Blood *b);


int main(){
    system("chcp 65001");
    system("cls");
    int runFlag = 1;
    Blood blood;
    Blood *b = &blood;
    if (readAndBackup(b)) initBlood(b);
    while (runFlag) option(b, &runFlag);
}



void option(Blood *b, int *runFlag){
    int option;
    printf("\n");
    printf("0.清空屏幕\t1.添加精血\t2.精血列表\t3.删除精血\t4.已吸收精血\t5.保存数据\n6.保存并退出\t7.直接退出\t8.天品精血\t9.精血种类\t10.快速插入\t11.吸收精血\t输入指令:  ");
    scanf("%d", &option);
    printf("\n");
    if (option < 0 || option > 11){
        printf("未知指令!!!\n");
        char c;
        while (c = getchar() != '\n' && c != EOF);
        return;
    }
    switch(option){
        case 0:
            system("cls"); break;
        case 1:
            insertBlood(b, 1); break;
        case 2:
            listBlood(b); break;
        case 3:
            char name[24]; deleteBlood(b, name, 1); break;
        case 4:
            showAbsorbed(b); break;
        case 5:
            writeData(b, fileName, 1); break;
        case 6:
            writeData(b, fileName, 1); *runFlag = 0; break;
        case 7:
            *runFlag = 0; break;
        case 8:
            checkBlood(b); break;
        case 9:
            printf("精血种类:%d\n", b->size); break;
        case 10:
            insertBlood(b, 0); break;
        case 11:
            addAbsorbed(b); break;
    }
}

int inList(Blood *b, char name[], int *index){
    int find = 0;
    *index = -1;
    for (int i = 0; i < b->size; i++){
        if (!strcmp(b->nameList[i], name)){
            find = 1;
            *index = i;
            break;
        }
    }
    return find == 1;
}

void initBlood(Blood *b){
    for (int i = 0; i < 100; i++){
        strcpy(b->nameList[i], noBlood);
        strcpy(b->absorbList[i], noBlood);
        for (int j = 0; j < 3; j++)
            b->data[i][j] = 0;
    }
    b->size = 0;
    printf("初始化成功\n");
}

void insertBlood(Blood *b, int mode){
    while (1){
        if (b->size == 100){
            printf("背包已满\n");
            return;
        }
        char name[24];
        printf("输入精血名称:");
        scanf("%s", name);
        if (!strcmp(name, "###")) break;
        if (isAbsorbed(b, name)){
            printf("已吸收该精血\n");
            return;
        }
        int temp, bType, *index, find = 0, num = 1;
        index = &temp;
        printf("输入精血品质:");
        scanf("%d", &bType);
        if (bType < 0 || bType > 2){
            printf("未知品质!!!\n");
            return;
        }
        if (!mode){
            printf("输入精血数量:");
            scanf("%d", &num);
        }
        for (int i = 0; i < num; i++){
            if (inList(b, name, index)) b->data[*index][bType] += 1;
            else{
                strcpy(b->nameList[b->size], name);
                b->data[b->size++][bType] = 1;
            }
        }
        printf("\n");
        if (mode) break;
    }
}

void checkBlood(Blood *b){
    int find = 0;
    printf("可合成天品精血:\n");
    for (int i = 0; i < b->size; i++){
        int a1 = b->data[i][0], a2 = b->data[i][1], a3 = b->data[i][2];
        if (a3 >= 2 && ((a3 - 2) / 3 + a2) >= 2 && (a1 + (a2 + (a3 - 2) / 3 - 2) / 3) >= 2){
            printf("%s\n", b->nameList[i]);
            find = 1;
        }
    }
    if (!find) printf("无\n");
}

void listBlood(Blood *b){
    if (b->size == 0){
        printf("暂无精血\n");
    }
    else{
        printf("\t精血列表\n");
        printf("精血名称    地品  玄品  黄品\n");
        for (int i = 0; i < b->size; i++){
            printf("%-16s%-6d%-6d%-6d\n", b->nameList[i], b->data[i][0], b->data[i][1], b->data[i][2]);
        }
        printf("\n");
    }
}

void deleteBlood(Blood *b, char name[], int mode){
    if (mode){
        printf("输入要删除的精血:");
        strcpy(name, "");
        scanf("%s", name);
    }
    int temp, *index;
    index = &temp;
    if (inList(b, name, index)){
        for (int i = *index; i < b->size - 1; i++){
            strcpy(b->nameList[i], b->nameList[i + 1]);
            for (int j = 0; j < 3; j++)
                b->data[i][j] = b->data[i + 1][j];
        }
        strcpy(b->nameList[b->size - 1], noBlood);
        for (int i = 0; i < 3; i++)
            b->data[*index][i] = 0;
        b->size--;
    }
}


int isAbsorbed(Blood *b, char name[]){
    int find = 0;
    for (int i = 0; i < 100; i++){
        if (!strcmp(name, b->absorbList[i])){
            find = 1;
            break;
        }
    }
    return find;
}

void addAbsorbed(Blood *b){
    char name[24];
    printf("输入要吸收的精血名称:");
    scanf("%s", name);
    deleteBlood(b, name, 0);
    for (int i = 0; i < 100; i++){
        if (!strcmp(noBlood, b->absorbList[i])){
            strcpy(b->absorbList[i], name);
            break;
        }
    }
}

void showAbsorbed(Blood *b){
    if (!strcmp(noBlood, b->absorbList[0])) printf("无\n");
    else{
        for (int i = 0; i < 100; i++){
            if (!strcmp(noBlood, b->absorbList[i])) break;
            if (!(i % 5)) printf("\n");
            printf("%s\t", b->absorbList[i]);
        }
        printf("\n");
    }
}

void writeData(Blood *b, char fileName[], int mode){
    FILE *fp = fopen(fileName, "wb");
    if (fp == NULL){
        if (mode) printf("文件打开失败\n");
        else printf("备份失败\n");
        return;
    }
    fwrite(b, sizeof(Blood), 1, fp);
    fclose(fp);
    if (mode){
        saveTime();
        printf("保存成功\n");
    }
    else printf("备份成功\n");
}

int readAndBackup(Blood *b){
    
    FILE *fp = fopen(fileName, "rb");
    if (fp == NULL) return 1;
    
    writeData(b, backupName, 0);
    fread(b, sizeof(Blood), 1, fp);
    fclose(fp);
    printf("读取成功\n");
    return 0;
}

void saveTime(){
    time_t now = time(NULL);
    char *time_str = ctime(&now);
    FILE *fp = fopen("time.txt", "a");
    fprintf(fp, "%s", time_str);
    fclose(fp);
}