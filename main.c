#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>


//defenition:

#define DEFAULT 246
#define GREEN 47
#define GOLDEN 111
#define DARK 6
#define W 191
#define E 231
#define C 79
#define MAP 112

//global variables:

int theme = DEFAULT;
struct user * list;
int list_length ;


//structs

struct user{
    char name[50];
    int score;
}player[2];
struct position{
    int i;
    int j;
};
struct ship{
    struct position p1;
    struct position p2;
    int length;
};

//function declaration:

void change_txt_color(int theme);
void print_theme();
void print_menu();
void print_menu_topic();
void cls();
void change_theme(int * theme);
int make_user(int player_num);
int get_user();
int chose_user(int player_num);
int score_compare(const void * a1,const void * a2);
void print_users();
void save_users();

//main:

int main() {
    get_user();
    cls();
    int choice;
    print_theme();
    main_menu:
    while (1) {
        print_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:

                //play with a friend
            play_with_friend:
                choice=0;
                while (!(choice==1 || choice==2)) {
                    cls();
                    print_menu_topic();
                    printf("\nfirst player:\n\tchose user:\n\t\t1)chose from available users\n\t\t2)new use\n");
                    scanf("%d", &choice);
                    if(!(choice==1 || choice==2)){
                        printf("please enter a valid choice\n");
                        Sleep(1300);
                    }
                }
                    switch (choice) {
                        case 1:

                            //available users
                            if(list_length==0){

                                printf("\n\tno user yet!\n");
                                Sleep(1300);
                                goto play_with_friend;
                            }
                            while(chose_user(0)==0);

                            break;
                        case 2:
                            //new user
                            while (make_user(0)==0);


                            break;

                    }
                choice=0;
                while (!(choice==1 || choice==2)) {
                    cls();
                    print_menu_topic();
                    printf("\nfirst player:\n\tput ships:\n\t\t1)manual\n\t\t2)auto\n");
                    scanf("%d", &choice);
                    if(!(choice==1 || choice==2)){
                        printf("please enter a valid choice\n");
                        Sleep(1300);
                    }
                }
                switch (choice) {
                    case 1:
                        //manual

                        break;
                    case 2:
                        //auto

                        break;

                }
                //second player
            second_player:
                choice=0;
                while (!(choice==1 || choice==2)) {
                    cls();
                    print_menu_topic();
                    printf("\nsecond player:\n\tchose user:\n\t\t1)chose from available users\n\t\t2)new use\n");
                    scanf("%d", &choice);
                    if(!(choice==1 || choice==2)){
                        printf("please enter a valid choice\n");
                        Sleep(1300);
                    }
                }
                switch (choice) {
                    case 1:
                        //available users
                        if(list_length<=1){

                            printf("\n\tno available user !\n");
                            Sleep(1300);
                            goto second_player;
                        }
                        while(chose_user(1)==0);

                        break;
                    case 2:
                        //new user
                        while (make_user(1)==0);

                        break;

                }
                choice=0;
                while (!(choice==1 || choice==2)) {
                    cls();
                    print_menu_topic();
                    printf("\nsecond player:\n\tput ships:\n\t\t1)manual\n\t\t2)auto\n");
                    scanf("%d", &choice);
                    if(!(choice==1 || choice==2)){
                        printf("please enter a valid choice\n");
                        Sleep(1300);
                    }
                }
                switch (choice) {
                    case 1:
                        //manual

                        break;
                    case 2:
                        //auto

                        break;

                }





                break;
            case 2:
                //play with bot
            play_with_bot:
                choice=0;
                while (!(choice==1 || choice==2)) {
                    cls();
                    print_menu_topic();
                    printf("\nhuman player:\n\tchose user:\n\t\t1)chose from available users\n\t\t2)new use\n");
                    scanf("%d", &choice);
                    if(!(choice==1 || choice==2)){
                        printf("please enter a valid choice\n");
                        Sleep(1300);
                    }
                }
                switch (choice) {
                    case 1:
                        //available users
                        if(list_length==0){

                            printf("\n\tno available user !\n");
                            Sleep(1300);
                            goto play_with_bot;
                        }

                        while(chose_user(1)==0);

                        break;
                    case 2:
                        //new user
                        while (make_user(0)==0);

                        break;

                }
                choice=0;
                while (!(choice==1 || choice==2)) {
                    cls();
                    print_menu_topic();
                    printf("\nhuman player:\n\tput ships:\n\t\t1)manual\n\t\t2)auto\n");
                    scanf("%d", &choice);
                    if(!(choice==1 || choice==2)){
                        printf("please enter a valid choice\n");
                        Sleep(1300);
                    }
                }
                switch (choice) {
                    case 1:
                        //manual

                        break;
                    case 2:
                        //auto

                        break;

                }

                break;
            case 3:
                //load game

                break;
            case 4:
                //load last game

                break;
            case 5:
                //setting
                choice=0;
                while (!(choice==1)) {
                    cls();
                    print_menu_topic();
                    printf("\nsetting:\n\t1)theme\n");
                    scanf("%d", &choice);
                    if(!(choice==1)){
                        printf("please enter a valid choice\n");
                        Sleep(1300);
                    }
                    switch (choice) {
                        case 1:
                            change_theme(&theme);
                            break;

                    }
                }


                break;
            case 6:
                //score board
                cls();
                print_menu_topic();
                printf("\nscore board:\n");
                if(list_length==0){

                    printf("\n\tno user yet!\n");
                    Sleep(1300);
                    goto main_menu;
                }
                print_users();

                qsort(list,list_length,sizeof(struct user),score_compare);


                break;
            case 7:
                //exit
                return 0;

            default:
                printf("Please enter a valid choice\n");
                Sleep(1300);

        }
    }


    return 0;
}

//function defenition:

void change_txt_color(int theme){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , theme);
}
void cls(){
    change_txt_color(theme);
    system("cls");
}
void print_theme(){
    printf("\n");
    for(int t=0;t<2;t++)
        for(int i=0;i<3;i++){
            change_txt_color(theme);
            printf("\t\t");
            change_txt_color(178+i);
            printf("MY ");
            change_txt_color(179+i);
            printf("BATTLE ");
            change_txt_color(180+i);
            printf("SHIPS !");
            Sleep(500);
            printf("\r");
        }

}
void print_menu_topic(){
    change_txt_color(182);
    printf("\n\t\tMY BATTLE SHIPS !\n");
    change_txt_color(theme);
}
void print_menu(){
    cls();
    print_menu_topic();
    printf("\n\nChose:\n1) Play with a friend\n2) Play whit bot\n3) Load game\n4) Load last game\n5) Setting\n6) Score board\n7) Exit\n");

}
void change_theme(int * theme){
    while (1){
        int choice;
         cls();
         print_menu_topic();
         printf("\nThemes:\n");
         change_txt_color(DEFAULT);
         printf("1)Default\n");
         change_txt_color(GREEN);
         printf("2)Green\n");
         change_txt_color(GOLDEN);
         printf("3)Golden\n");
         change_txt_color(DARK);
         printf("4)Dark mode\n");

        scanf("%d", &choice);
        switch (choice) {
            case 1:
                *theme=DEFAULT;
                return;
                break;
            case 2:
                *theme=GREEN;
                return;
                break;
            case 3:
                *theme=GOLDEN;
                return;
                break;
            case 4:
                *theme=DARK;
                return;
                break;
            default :
                printf("please enter a valid choice\n");





        }
    }
}
int get_user(){
    FILE * fp = fopen("save/users","r");
    list = (struct user *) malloc(sizeof(struct user));
    if (fp==NULL)
        return 0;

    for(list_length=0;1;list_length++){
        fread(&list[list_length],sizeof(struct user),1,fp);
        if(feof(fp)!=0){
            return 1;
        }
        list = realloc(list,(list_length+2) * sizeof(struct user));

    }


}
int make_user(int player_num){
    char username[50];
    cls();
    print_menu_topic();
    printf("\nnew user:\n\tenter your user name :");
    getchar();
    gets(username);

    for(int i=0;i<list_length;i++){
        if(strcmp(username,list[i].name)==0){
            printf("\n\tthis user is already exists");
            Sleep(1300);
            return 0;
        }

    }
    realloc(list,(list_length+1)*sizeof(struct user));
    list_length ++;
    strcpy(list[list_length-1].name,username);
    list[list_length-1].score=0;
    player[player_num]=list[list_length-1];
    save_users();

    return 1;


}
int chose_user(int player_num){
    int choice;
    cls();
    print_menu_topic();
    print_users();
    printf("\nchose user:\n");

    scanf("%d",&choice);
    if(choice>list_length || choice<=0){
        printf("please enter a valid choice");
        Sleep(1300);
        return 0;
    }else if(player_num==1 && strcmp(player[0].name,list[choice-1].name)==0){
        printf("user is token !");
        Sleep(1300);
        return 0;
    }else{
        player[player_num]=list[choice-1];
    }
}
int score_compare(const void * a1,const void * a2){
    struct user * u1 = (struct user * ) a1;
    struct user * u2 = (struct user * ) a2;
    return (u2->score >= u1->score)? 1 : -1;

}
void print_users(){
    for(int i=0;i<list_length;i++){
        printf("\t%d)%s\t%d\n",i+1,list[i].name,list[i].score);
    }

}
void save_users(){
    mkdir("save");
    FILE * fp=fopen("save/users","w");
    fwrite(list,list_length,sizeof(struct user),fp);
    fclose(fp);
}
struct node {
    struct ship sh;
    struct node * next;
};
struct node *head , *current;
struct node * previous;
struct node * make_node(struct ship sh){
    struct node* p=(struct node *) malloc(sizeof(struct node));
    p->sh=sh;
    p->next=NULL;
    return p;
}

void insert_first(struct ship sh){

    head = make_node(sh);
    current = head;

}
void insert_at_end(struct ship sh){

        for (current = head; current->next != NULL; current = current->next);
        current->next = make_node(sh);

}

void delete(long int id){


     if(current==head){
        head=head->next;
        free(current);

    }else {
        previous->next = current->next;
        free(current);

    }
}
