#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include <time.h>


//defenition:

#define DEFAULT 246
#define GREEN 47
#define GOLDEN 111
#define DARK 6
#define W 191
#define E 231
#define C 79
#define S 140
#define Q 135
#define MAP 112

//global variables:

int theme = DEFAULT;
struct user * list;
int list_length ;
int ships_length[10]={5,3,3,2,2,2,1,1,1,1};
struct node * h[2];
int turn;





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
struct maps{
    int main[10][10];
    int show[10][10];
}map[2];

//function declaration:

void change_txt_color(int theme);
void print_theme();
void print_menu();
void print_menu_topic();
void cls();
int get_num();
void change_theme(int * theme);
int make_user(int player_num);
int get_user();
int chose_user(int player_num);
int score_compare(const void * a1,const void * a2);
void print_users();
void save_users();
void put_ships_manual(int player_num);
void print_map(int map[10][10]);
int check_ship_placement(struct ship sh1, int player_num);
void place_ship_in_main_map(struct ship sh1, int player_num);
void put_ships_auto(int player_num,int show_bool);
void game_with_friend();
void map_initialize(int map[10][10],int init);
int check_shoot(int turn,int i,int j);
int apply_shoot(int turn,int i,int j);
void apply_completeness(int turn);
void update_score(struct user plr);
void game_with_bot();
int check_explosion(int turn,int i,int j);
void bot_i_and_j(int *i,int *j);
void save();
void make_file_name(char file_name[70]);
int save_2users(char file_name[70]);
int save_maps(char file_name[70]);
int save_ships(char file_name[70]);
int print_game_names();
void make_game_name(char game_name[70]);
int load_game(int file_num);
int load_2users(FILE * fp);
int load_maps(FILE * fp);
void load_ships(FILE * fp);
//main:

int main() {

    get_user();
    cls();
    int choice;
    int file_num;
    print_theme();
    main_menu:
    while (1) {
        map_initialize(map[0].show, -1);
        map_initialize(map[1].show, -1);
        map_initialize(map[0].main, 0);
        map_initialize(map[1].main, 0);
        print_menu();
        choice = get_num();
        switch (choice) {
            case 1:

                //play with a friend
            play_with_friend:
                choice = 0;
                while (!(choice == 1 || choice == 2)) {
                    cls();
                    print_menu_topic();
                    printf("\nfirst player:\n\tchose user:\n\t\t1)chose from available users\n\t\t2)new use\n");
                    choice = get_num();
                    if (!(choice == 1 || choice == 2)) {
                        printf("please enter a valid choice\n");
                        Sleep(1300);
                    }
                }
                switch (choice) {
                    case 1:

                        //available users
                        if (list_length == 0) {

                            printf("\n\tno user yet!\n");
                            Sleep(1300);
                            goto play_with_friend;
                        }
                        while (chose_user(0) == 0);

                        break;
                    case 2:
                        //new user
                        while (make_user(0) == 0);


                        break;

                }
                choice = 0;
                while (!(choice == 1 || choice == 2)) {
                    cls();
                    print_menu_topic();
                    printf("\nfirst player:\n\tput ships:\n\t\t1)manual\n\t\t2)auto\n");
                    choice = get_num();
                    if (!(choice == 1 || choice == 2)) {
                        printf("please enter a valid choice\n");
                        Sleep(1300);
                    }
                }
                switch (choice) {
                    case 1:
                        //manual
                        put_ships_manual(0);

                        break;
                    case 2:
                        //auto
                        put_ships_auto(0, 1);

                        break;

                }
                //second player
            second_player:
                choice = 0;
                while (!(choice == 1 || choice == 2)) {
                    cls();
                    print_menu_topic();
                    printf("\nsecond player:\n\tchose user:\n\t\t1)chose from available users\n\t\t2)new use\n");
                    choice = get_num();
                    if (!(choice == 1 || choice == 2)) {
                        printf("please enter a valid choice\n");
                        Sleep(1300);
                    }
                }
                switch (choice) {
                    case 1:
                        //available users
                        if (list_length <= 1) {

                            printf("\n\tno available user !\n");
                            Sleep(1300);
                            goto second_player;
                        }
                        while (chose_user(1) == 0);

                        break;
                    case 2:
                        //new user
                        while (make_user(1) == 0);

                        break;

                }
                choice = 0;
                while (!(choice == 1 || choice == 2)) {
                    cls();
                    print_menu_topic();
                    printf("\nsecond player:\n\tput ships:\n\t\t1)manual\n\t\t2)auto\n");
                    choice = get_num();
                    if (!(choice == 1 || choice == 2)) {
                        printf("please enter a valid choice\n");
                        Sleep(1300);
                    }
                }
                switch (choice) {
                    case 1:
                        //manual
                        put_ships_manual(1);

                        break;
                    case 2:
                        //auto
                        put_ships_auto(1, 1);

                        break;

                }
                player[0].score = 0;
                player[1].score = 0;
                turn = 0;
                game_with_friend();

                break;
            case 2:
                //play with bot
            play_with_bot:
                choice = 0;
                while (!(choice == 1 || choice == 2)) {
                    cls();
                    print_menu_topic();
                    printf("\nhuman player:\n\tchose user:\n\t\t1)chose from available users\n\t\t2)new use\n");
                    choice = get_num();
                    if (!(choice == 1 || choice == 2)) {
                        printf("please enter a valid choice\n");
                        Sleep(1300);
                    }
                }
                switch (choice) {
                    case 1:
                        //available users
                        if (list_length == 0) {

                            printf("\n\tno available user !\n");
                            Sleep(1300);
                            goto play_with_bot;
                        }

                        while (chose_user(0) == 0);

                        break;
                    case 2:
                        //new user
                        while (make_user(0) == 0);

                        break;

                }
                choice = 0;
                while (!(choice == 1 || choice == 2)) {
                    cls();
                    print_menu_topic();
                    printf("\nhuman player:\n\tput ships:\n\t\t1)manual\n\t\t2)auto\n");
                    choice = get_num();
                    if (!(choice == 1 || choice == 2)) {
                        printf("please enter a valid choice\n");
                        Sleep(1300);
                    }
                }
                switch (choice) {
                    case 1:
                        //manual
                        put_ships_manual(0);

                        break;
                    case 2:
                        //auto
                        put_ships_auto(0, 1);

                        break;

                }
                strcpy(player[1].name, "bot");
                player[1].score = 0;
                player[0].score = 0;
                put_ships_auto(1, 0);
                turn = 0;
                game_with_bot();

                break;
            case 3:
                //load game
                cls();
                print_menu_topic();
                file_num = print_game_names();
                if (file_num == 0) {

                    printf("\nno saved game!\n");

                    Sleep(2000);

                } else {
                    while (1) {
                        choice=get_num();
                        if(choice>=1 && choice <=file_num){
                            break;
                        }else{
                            printf("please enter a valid choice\n");
                            Sleep(1300);
                        }
                        cls();
                        print_menu_topic();
                        file_num = print_game_names();

                    }
                    if(load_game(choice)){
                        if(strcpy(player[1].name,"bot")){
                            game_with_bot();
                        }else{
                            game_with_friend();
                        }
                    }

                    break;
                    case 4:
                        //load last game


                        break;
                    case 5:
                        //setting
                        choice = 0;
                    while (!(choice == 1)) {
                        cls();
                        print_menu_topic();
                        printf("\nsetting:\n\t1)theme\n");
                        choice = get_num();
                        if (!(choice == 1)) {
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
                    if (list_length == 0) {

                        printf("\n\tno user yet!\n");
                        Sleep(1300);

                    } else {
                        print_users();
                        Sleep(1300);
                        printf("\npress enter to back to the main menu ");
                        fflush(stdin);
                        getchar();
                        fflush(stdin);
                    }


                    break;
                    case 7:
                        //exit
                        return 0;

                    default:
                        printf("Please enter a valid choice\n");
                    Sleep(1300);

                }
        }



    }
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
        if(strcmp(username,list[i].name)==0 || strcmp(username,"bot")==0){
            printf("\n\tthis user is unavailable");
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
    qsort(list, list_length, sizeof(struct user), score_compare);
    for(int i=0;i<list_length;i++){
        printf("\t%d)%s\t%d\n",i+1,list[i].name,list[i].score);
    }

}
void save_users(){
    qsort(list, list_length, sizeof(struct user), score_compare);
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

void delete(){




     if(current==head){
        head=head->next;
        free(current);

    }else {
        for(previous=head;previous->next!=current;previous=previous->next);
        previous->next = current->next;
        free(current);

    }

     current=NULL;
}
void put_ships_manual(int player_num){
    int i=0;
    struct ship sh1;
    while(i<10) {
        cls();
        print_menu_topic();
        printf("\n %s put ships :  \n", player[player_num].name);
        print_map(map[player_num].main);
        change_txt_color(theme);
        printf("\nput the %d space length ship :\nenter first point's i (row)  and j (column) :\n",ships_length[i]);
        sh1.length=ships_length[i];
        sh1.p1.i=get_num();
        sh1.p1.j=get_num();
        printf("enter the second point's i (row) and j (column) : \n");
        sh1.p2.i=get_num();
        sh1.p2.j=get_num();
        if(check_ship_placement(sh1,player_num)){
            place_ship_in_main_map(sh1,player_num);
            if(i==0){
                insert_first(sh1);
                h[player_num]=head;
            } else{
                head=h[player_num];
                insert_at_end(sh1);
            }
            i++;

        }else{
            printf("invalid input parameters\n");
            Sleep(1300);
        }



    }




}
void print_map(int map[10][10]){

    change_txt_color(MAP);
    printf("  ");
    for(int j=0;j<10;j++)
        printf("  %d    ",j);
    change_txt_color(theme);
    printf("\n");

    for(int i=0;i<10;i++){
        //first row

        change_txt_color(MAP);
        printf("  ");

        for(int j=0;j<10;j++){
            if(map[i][j]==0){
                change_txt_color(W);
                printf("     ");
            }else if(map[i][j]==1){
                change_txt_color(E);
                printf("     ");
            }else if(map[i][j]==2){
                change_txt_color(C);
                printf("     ");
            }else if(map[i][j]==3){
                change_txt_color(S);
                printf("     ");
            }else if(map[i][j]==-1){
            change_txt_color(Q);
            printf("     ");
            }
            change_txt_color(MAP);
            printf("  ");

        }
        //second row
        change_txt_color(theme);
        printf("\n");
        change_txt_color(MAP);
        printf(" %d",i);

        for(int j=0;j<10;j++){
            if(map[i][j]==0){
                change_txt_color(W);
                printf("  W  ");
            }else if(map[i][j]==1){
                change_txt_color(E);
                printf("  E  ");
            }else if(map[i][j]==2){
                change_txt_color(C);
                printf("  C  ");
            }else if(map[i][j]==3){
            change_txt_color(S);
            printf("  *  ");
        }else if(map[i][j]==-1){
            change_txt_color(Q);
            printf("  ?  ");
        }
            change_txt_color(MAP);
            printf("  ");

        }
        //third row
        change_txt_color(theme);
        printf("\n");
        change_txt_color(MAP);
        printf("  ");

        for(int j=0;j<10;j++){
            if(map[i][j]==0){
                change_txt_color(W);
                printf("     ");
            }else if(map[i][j]==1){
                change_txt_color(E);
                printf("     ");
            }else if(map[i][j]==2){
                change_txt_color(C);
                printf("     ");
            }else if(map[i][j]==3){
                change_txt_color(S);
                printf("     ");
            }else if(map[i][j]==-1){
                change_txt_color(Q);
                printf("     ");
            }
            change_txt_color(MAP);
            printf("  ");

        }
        //border
        change_txt_color(theme);
        printf(" \n");

        change_txt_color(MAP);
        printf("  ");
        for(int j=0;j<10;j++)
            printf("       ");
        change_txt_color(theme);
        printf(" \n");

    }
}

int get_num(){
    char buff[10];
    int bool=1;

    scanf("%s",buff);
    fflush(stdin);
    for(int i=0;i<10 && buff[i]!='\0'  ;i++){
        if(isdigit(buff[i])==0)
                bool=0;

    }
    if(bool==0){

        return -2;

    }else {
        int choice ;
        sscanf(buff,"%d",&choice);
        
        return choice;
    }


}
int check_ship_placement(struct ship sh1, int player_num){
    if((sh1.p1.i > 9 || sh1.p1.i < 0) || (sh1.p1.j > 9 || sh1.p1.j < 0) || (sh1.p2.i > 9 || sh1.p2.i < 0) ||(sh1.p2.j > 9 || sh1.p2.j < 0))
        return 0;
    if(sh1.p1.i==sh1.p2.i && abs(sh1.p1.j-sh1.p2.j)==sh1.length-1){
        int t = (sh1.p2.j-sh1.p1.j >=0) ? 1 : -1;
        sh1.p1.j-=t;
        while (sh1.p2.j!=sh1.p1.j-2*t){
            if(map[player_num].main[sh1.p1.i][sh1.p1.j]!=0)
                return 0;
            if(sh1.p1.i + 1 <=9)
                if(map[player_num].main[sh1.p1.i+1][sh1.p1.j]!=0)
                    return 0;
            if(sh1.p1.i - 1 >=0)
                if(map[player_num].main[sh1.p1.i-1][sh1.p1.j]!=0)
                    return 0;

            sh1.p1.j +=t;
        }
        return 1;


    }else if(sh1.p1.j==sh1.p2.j && abs(sh1.p1.i-sh1.p2.i)==sh1.length-1){
        int t = (sh1.p2.i-sh1.p1.i >=0)? 1 : -1 ;
        sh1.p1.i -=t;
        while (sh1.p2.i!=sh1.p1.i-2*t){
            if(map[player_num].main[sh1.p1.i][sh1.p1.j]!=0)
                return 0;
            if(sh1.p1.j + 1 <=9)
                if(map[player_num].main[sh1.p1.i][sh1.p1.j+1]!=0)
                    return 0;
            if(sh1.p1.j - 1 >=0)
                if(map[player_num].main[sh1.p1.i][sh1.p1.j-1]!=0)
                    return 0;

            sh1.p1.i +=t;
        }
        return 1;



    }else
        return 0;
}
void place_ship_in_main_map(struct ship sh1, int player_num){

    if(sh1.p1.i==sh1.p2.i){
        int t = (sh1.p2.j-sh1.p1.j >=0) ? 1 : -1;
        while (sh1.p2.j!=sh1.p1.j-t){
            map[player_num].main[sh1.p1.i][sh1.p1.j]=3;
            sh1.p1.j += t;
        }
    }else if(sh1.p1.j==sh1.p2.j){
        int t = (sh1.p2.i-sh1.p1.i >=0)? 1 : -1 ;
        while (sh1.p2.i!=sh1.p1.i-t){
            map[player_num].main[sh1.p1.i][sh1.p1.j]=3;
            sh1.p1.i += t;
        }
    }


}
void put_ships_auto(int player_num,int show_bool){
    cls();
    print_menu_topic();
    int i=0;
    srand(time(NULL));
    struct ship sh1;
    while (i<10){
        while (1){
            sh1.length=ships_length[i];
            sh1.p1.i=rand()%10;
            sh1.p1.j=rand()%10;
            int h_or_v=rand()%2;
            if(h_or_v==0){
                sh1.p2.i=sh1.p1.i;
                sh1.p2.j=sh1.p1.j+sh1.length-1;
            }else{
                sh1.p2.j=sh1.p1.j;
                sh1.p2.i=sh1.p1.i+sh1.length-1;
            }
            if(check_ship_placement(sh1,player_num)){
                place_ship_in_main_map(sh1,player_num);
                if(i==0){
                    insert_first(sh1);
                    h[player_num]=head;
                } else{
                    head=h[player_num];
                    insert_at_end(sh1);
                }
                i++;
                break;

            }

        }
    }
    if(show_bool) {
        printf("\n%s's map :\n", player[player_num].name);
        print_map(map[player_num].main);
        Sleep(1300);
        fflush(stdin);
        printf("\npress enter to continue ");
        getchar();
        fflush(stdin);
    }

}
void game_with_friend() {
    int game_bool = 1;
    int turn_bool;
    while (game_bool) {
        turn = turn % 2;
        cls();
        print_menu_topic();
        printf("\n %s's score: %d\t\t\t\t%s's score: %d\n", player[0].name, player[0].score, player[1].name,player[1].score);
        printf("\n %s's turn: \n", player[turn].name);
        print_map(map[(turn+1)%2].show);
        printf("\n chose a point to shoot!\nenter i (row) and j (column) : \n");
        int i = get_num();
        int j = get_num();
        if (check_shoot((turn+1)%2, i, j)) {
            turn_bool = apply_shoot((turn+1)%2, i, j);
            apply_completeness((turn+1)%2);
            cls();
            print_menu_topic();
            printf("\n %s's score: %d\t\t\t\t%s's score: %d\n", player[0].name, player[0].score, player[1].name,
                   player[1].score);
            printf("\n %s's move : \n", player[turn].name);
            print_map(map[(turn+1)%2].show);
            Sleep(1300);
            printf("1)continue\n2)save the game and quit\n");
            int choice;
            do {
                choice = get_num();
                if (choice == 2) {
                    //save
                    game_bool = 0;
                } else if (choice != 1) {
                    printf("enter a valid choice ");
                    Sleep(1300);
                    printf("\r                               \r");
                }
            } while (!(choice == 1 || choice == 2));

            if (turn_bool == 0) {
                turn++;
            }

        } else {
            printf("the point is unavailable\n");
            Sleep(1300);
        }
        if (h[0] == NULL || h[1] == NULL)
            game_bool = 0;


    }
    if (h[1] == NULL) {
        cls();
        print_menu_topic();
        printf("\n\tgame is over !\n\n\t%s wins!", player[0].name);

        player[1].score = player[1].score / 2;
        Sleep(1300);
        printf("press enter to continue ");
        fflush(stdin);
        getchar();
        fflush(stdin);
        update_score(player[0]);
        update_score(player[1]);
        save_users();

    } else if (h[0] == NULL) {
        cls();
        print_menu_topic();
        printf("\n\tgame is over !\n\n\t%s wins!", player[1].name);

        player[0].score = player[0].score / 2;
        Sleep(1300);
        printf("press enter to continue ");
        fflush(stdin);
        getchar();
        fflush(stdin);
        update_score(player[0]);
        update_score(player[1]);
        save_users();



    }
}
void map_initialize(int m[10][10] , int init){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            m[i][j]=init;
        }
    }
}
int check_shoot(int turn,int i,int j){

       if(i<=9 && i>= 0 && j<=9 && j>=0){
           if(map[turn].show[i][j]==-1)
               return 1;
       }
    return 0;


}
int apply_shoot(int turn,int i,int j){

    if(map[turn].main[i][j]==3) {
        map[turn].show[i][j] = 1;
        player[(turn+1)%2].score++;
        return 1;
    }
    else if(map[turn].main[i][j]==0)
        map[turn].show[i][j]=0;
    return 0;

}
void apply_completeness(int turn){

    head=h[turn];
    int loop_bool=1;
    for(current=head; current!=NULL;current=current->next){
        struct ship sh1 = current->sh;
        int bool;
        bool=1;
        if(sh1.p1.i==sh1.p2.i){

            int t = (sh1.p2.j-sh1.p1.j >=0) ? 1 : -1;
            while (sh1.p2.j!=sh1.p1.j-t){
                if(map[turn].show[sh1.p1.i][sh1.p1.j]!=1) {
                    bool = 0;
                    break;
                }
                sh1.p1.j += t;
            }
            if(bool==1){
                sh1 = current->sh;
                sh1.p1.j-=t;
                while (sh1.p2.j!=sh1.p1.j-2*t){
                    if(sh1.p2.j <=9 && sh1.p2.j>=0) {
                        map[turn].show[sh1.p1.i][sh1.p1.j] = 2;

                        if (sh1.p1.i + 1 <= 9)
                            map[turn].show[sh1.p1.i + 1][sh1.p1.j] = 0;

                        if (sh1.p1.i - 1 >= 0)
                            map[turn].show[sh1.p1.i - 1][sh1.p1.j] = 0;
                    }


                    sh1.p1.j +=t;
                }
                sh1 = current->sh;
                map[turn].show[sh1.p1.i][sh1.p1.j - t]=0;
                map[turn].show[sh1.p2.i][sh1.p2.j + t]=0;
                delete();
                h[turn]=head;
                loop_bool=0;
                player[(turn+1)%2].score+= 25/sh1.length;

            }
        }else if(sh1.p1.j==sh1.p2.j){
            int t = (sh1.p2.i-sh1.p1.i >=0)? 1 : -1 ;
            while (sh1.p2.i!=sh1.p1.i-t){
                if(map[turn].show[sh1.p1.i][sh1.p1.j]!=1) {
                    bool = 0;
                    break;
                }
                sh1.p1.i += t;
            }
            if(bool==1){
                sh1 = current->sh;
                sh1.p1.i-=t;
                while (sh1.p2.i!=sh1.p1.i-2*t){
                    if(sh1.p1.i<=9 && sh1.p1.i>=0) {
                        map[turn].show[sh1.p1.i][sh1.p1.j] = 2;

                        if (sh1.p1.j + 1 <= 9)
                            map[turn].show[sh1.p1.i][sh1.p1.j + 1] = 0;

                        if (sh1.p1.j - 1 >= 0)
                            map[turn].show[sh1.p1.i][sh1.p1.j - 1] = 0;

                    }


                    sh1.p1.i +=t;
                }
                sh1 = current->sh;
                map[turn].show[sh1.p1.i- t][sh1.p1.j ]=0;
                map[turn].show[sh1.p2.i+ t][sh1.p2.j ]=0;
                delete();
                h[turn]=head;
                loop_bool=0;
                player[(turn+1)%2].score+= 25/sh1.length;

            }

        }
        if(loop_bool==0)
            break;


    }
}
void update_score(struct user plr){
    for(int i=0;i<list_length;i++){
        if(strcmp(plr.name,list[i].name)){
            list[i].score+=plr.score;
            break;
        }
    }
}
void game_with_bot(){
    int game_bool = 1;
    int turn_bool;
    int i,j;
    while (game_bool) {
        turn = turn % 2;
        if(turn==0) {

            cls();
            print_menu_topic();
            printf("\n %s's score: %d\t\t\t\t%s's score: %d\n", player[0].name, player[0].score, player[1].name,
                   player[1].score);
            printf("\n %s's turn: \n", player[turn].name);
            print_map(map[(turn + 1) % 2].show);
            printf("\n chose a point to shoot!\nenter i (row) and j (column) : \n");
            i = get_num();
            j = get_num();
        }else{
            bot_i_and_j(&i,&j);

        }
        if (check_shoot((turn+1)%2, i, j)) {
            turn_bool = apply_shoot((turn+1)%2, i, j);
            apply_completeness((turn+1)%2);

            cls();
            print_menu_topic();
            printf("\n %s's score: %d\t\t\t\t%s's score: %d\n", player[0].name, player[0].score, player[1].name,
                   player[1].score);
            printf("\n %s's move : \n", player[turn].name);
            print_map(map[(turn+1)%2].show);
            Sleep(1300);
            printf("1)continue\n2)save the game and quit\n");
            if (turn_bool == 0) {
                turn++;
            }
            int choice;
            do {
                choice = get_num();
                if (choice == 2) {
                    save();
                    //save
                    game_bool = 0;
                } else if (choice != 1) {
                    printf("enter a valid choice ");
                    Sleep(1300);
                    printf("\r                               \r");
                }
            } while (!(choice == 1 || choice == 2));



        } else {
            printf("the point is unavailable\n");
            Sleep(1300);
        }
        if (h[0] == NULL || h[1] == NULL)
            game_bool = 0;


    }
    if (h[1] == NULL) {
        cls();
        print_menu_topic();
        printf("\n\tgame is over !\n\n\t%s wins!\n", player[0].name);

        Sleep(1300);
        printf("press enter to continue ");
        fflush(stdin);
        getchar();
        fflush(stdin);
        update_score(player[0]);
        save_users();


    } else if (h[0] == NULL) {
        cls();
        print_menu_topic();
        printf("\n\tgame is over !\n\n\t%s wins!", player[1].name);
        player[0].score = player[0].score / 2;
        Sleep(1300);
        printf("press enter to continue ");
        fflush(stdin);
        getchar();
        fflush(stdin);
        update_score(player[0]);
        save_users();

    }


}
int check_explosion(int turn,int i,int j){

    if(i<=9 && i>= 0 && j<=9 && j>=0){
        if(map[turn].show[i][j]==1)
            return 1;
    }
    return 0;


}
void bot_i_and_j(int *i,int *j){
    int i2;
    int j2;
    for(int i2=0;i2<10;i2++){
        for(int j2=0;j2<10;j2++)
            if(check_explosion(0,i2,j2)){
                if(check_explosion(0,i2+1,j2)){
                    if(check_shoot(0,i2-1,j2)){
                        *i=i2-1;
                        *j=j2;
                        return;
                    }

                }else if (check_explosion(0,i2-1,j2)){
                    if(check_shoot(0,i2+1,j2)){
                        *i=i2+1;
                        *j=j2;
                        return;
                    }

                }else if (check_explosion(0,i2,j2+1)){
                    if(check_shoot(0,i2,j2-1)){
                        *i=i2;
                        *j=j2-1;
                        return;
                    }

                }else if (check_explosion(0,i2,j2-1)){
                    if(check_shoot(0,i2,j2+1)){
                        *i=i2;
                        *j=j2+1;
                        return;
                    }

                }else{
                    if(check_shoot(0,i2,j2+1)){
                        *i=i2;
                        *j=j2+1;
                        return;
                    }else if(check_shoot(0,i2,j2-1)){
                        *i=i2;
                        *j=j2-1;
                        return;
                    }else if(check_shoot(0,i2+1,j2)){
                        *i=i2+1;
                        *j=j2;
                        return;
                    }else if(check_shoot(0,i2-1,j2)){
                        *i=i2-1;
                        *j=j2;
                        return;
                    }

                }
            }
    }
    srand(time(NULL));
    while (1){
        i2=rand()%10;
        j2=rand()%10;
        if(check_shoot(0,i2,j2)){
            *i=i2;
            *j=j2;
            break;
        }

    }
}
void save(){
    cls();
    print_menu_topic();
    printf("\n\n\t\tsaving...");
    char file_name[10];
    make_file_name(file_name);
    int success=0;
    success+=save_2users(file_name);
    success+=save_maps(file_name);
    success+=save_ships(file_name);
    cls();
    print_menu_topic();
    if(success==3) {
        char game_name[70];
        make_game_name(game_name);
        FILE *fp;
        fp = fopen("file names", "a");
        fprintf(fp,"%s",game_name);
        fclose(fp);
        printf("\n\n\tsaved successfully\n");

    }
    else
        printf("\n\n\tcould not save the game\n");

    Sleep(2000);



}

void make_game_name(char game_name[70]){
    time_t t;
    time(&t);
sprintf(game_name,"%s  vs  %s         %s",player[0].name,player[1].name,ctime(&t));

}
void make_file_name(char file_name[10]){
    char game_name[70];
    FILE * fp =fopen("file names","r");
    int i=1;
    if(fp==NULL) {
        sprintf(file_name, "%d", i);
        return;
    }
    while (1) {
        fgets(game_name,70,fp);

        if(feof(fp))
            break;
        i++;
    }
    sprintf(file_name,"%d",i);


}
int save_2users(char file_name[70]){
    FILE * fp=fopen(file_name,"wb");
    if(fp==NULL)
        return 0;
    fwrite(player,sizeof(struct user),2,fp);
    fwrite(&turn,sizeof(int),1,fp);
    fclose(fp);
    return 1;


}
int save_maps(char file_name[70]){
    FILE * fp=fopen(file_name,"ab");
    if(fp==NULL)
        return 0;
    fwrite(map,sizeof(struct maps),2,fp);
    fclose(fp);
    return 1;
}
int save_ships(char file_name[70]){
    FILE * fp=fopen(file_name,"ab");
    if(fp==NULL)
        return 0;
    head=h[0];
    int ship_num_0=0;
    for(current=head;current!=NULL;current=current->next)
        ship_num_0++;
    head=h[1];
    int ship_num_1=0;
    for(current=head;current!=NULL;current=current->next)
        ship_num_1++;
    fwrite(&ship_num_0,1,sizeof(int),fp);
    head=h[0];
    for(current=head;current!=NULL;current=current->next)
        fwrite(&current->sh,sizeof(struct ship),1,fp);

    fwrite(&ship_num_1,1,sizeof(int),fp);
    head=h[1];
    for(current=head;current!=NULL;current=current->next)
        fwrite(&current->sh,sizeof(struct ship),1,fp);

    fclose(fp);
    return 1;

}
int print_game_names(){
    cls();
    print_menu_topic();
    printf("\nchose:\n");
    FILE * fp =fopen("file names","r");
    if(fp==NULL)
        return 0;
    char game_name[70];
    int i=1;
    while (1){
        fgets(game_name,70,fp);
        if(feof(fp))
            return i-1;
        printf("\t%d) %s",i,game_name);
        i++;
    }


}
int load_game(int file_num){
    cls();
    print_menu_topic();
    printf("\n\n\tloading...");
    char file_name[10];
    sprintf(file_name,"%d",file_num);
    FILE * fp=fopen(file_name,"r");
    int succes=load_2users(fp);
    succes+=load_maps(fp);
    load_ships(fp);
    if(succes==5){
        cls();
        print_menu_topic();
        printf("\n\n\tloaded successfully\n");
        Sleep(2000);
        return 1;
    } else{
        printf("\n\n\tcould not load the game\n");
        Sleep(2000);
        return 0;
    }


}
int load_2users(FILE * fp){
    int num=fread(player,sizeof(struct user),2,fp);
    num+=fread(&turn,sizeof(int),1,fp);
    return num;

}
int load_maps(FILE * fp){
    int num=fread(map,sizeof(struct maps),2,fp);
    return num;
}
void load_ships(FILE * fp){
    int ship_num_0;
    fread(&ship_num_0,sizeof(int),1,fp);

    struct ship sh1;
    for(int i=0 ; i< ship_num_0;i++){
        fread(&sh1,sizeof(struct ship),1,fp);
        if(i==0){
            insert_first(sh1);
            h[0]=head;
        }else{
            insert_at_end(sh1);
        }
    }
    int ship_num_1;
    fread(&ship_num_1,sizeof(int),1,fp);


    for(int i=0 ; i< ship_num_1;i++){
        fread(&sh1,sizeof(struct ship),1,fp);
        if(i==0){
            insert_first(sh1);
            h[1]=head;
        }else{
            insert_at_end(sh1);
        }
    }
}