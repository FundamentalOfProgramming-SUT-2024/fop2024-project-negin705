// Negin Taeibi
// 403011204



#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

char rooms[10][10][10];
char map[6][34][121];
char running_map[6][34][121];
char monster_map[6][34][121];
int score = 0;
int number_of_game = 0;
int highest_score = 0;
int position_x = 0, position_y = 0;
int level = 1;
int health = 20, number_traps = 5, number_secret_doors = 5, number_password_doors = 3;
int hunger = 0;

int number_health_spell = 3, number_damage_spell = 3, number_speed_spell = 3;
int number_normal_food = 3;
int number_normal_gold = 3, number_black_gold = 2;
int number_dagger = 3, number_magic_wand = 3, number_normal_arrow = 3, number_sword = 3;

int count_master_key = 0, count_broken_master_key = 0;
int count_health_spell = 0, count_damage_spell = 0, count_speed_spell = 0;
int count_normal_food = 0;
int count_normal_gold = 0, count_black_gold = 0;
int count_mace = 1, count_dagger = 0, count_magic_wand = 0, count_normal_arrow = 0, count_sword = 0;

int number_deamon_health = 5, number_fire_health = 10, number_giant_health = 15, number_snake_health = 20, number_undeed_health = 30;
int number_giant_move = 5, number_snake_move = 1, number_undeed_move = 5;

int power_mace = 5, power_dagger = 12, power_magic_wand = 15, power_normal_arrow = 5, power_sword = 10;

int count_land = 0;
int land[1000][2];
char last = '.';
int last_color = 0;
int last_password;
char know_weapon = ' ';
char direction = ' ';
int repeat_shot = 0;
int move_count = 0;

int count_move_health_spell = 0, count_move_speed_spell = 0, count_move_damage_spell = 0;
int count_rotten_food = 0, count_excellent_food = 0, count_magic_food = 0;

typedef struct {
    int x, y;
    int x2, y2;
    int door_x, door_y;
} Rectangle;
Rectangle rectangles[6];

typedef struct {
    int x, y;
    int area_x1, area_x2, area_y1, area_y2;
} Coordinate;
Coordinate deamon_coordinate[6];
Coordinate fire_coordinate[6];
Coordinate giant_coordinate[6];
Coordinate snake_coordinate[6];
Coordinate undeed_coordinate[6];
Coordinate staircase_coordinate[6];

void start_game();
void movemennt();
int check_and_move(int, int);
void final_move(int, int);
void collect();
void free_up();
void print_running_map();
void print_menu_margin();
void print_corridor(int, int, int, int);
void make_rooms();
void clean_the_map();
void margin_the_map();
void print_margin();
void placing_room_and_fill_the_map();
void placing_door();
void placing_in_map(char, int, int, int);
void placing_password_door();
int check_collision(int, int, int);
void battle_room();
void secret_doors_room();
void give_password();
void opening_door(int, int);
void password_room();
void master_key(int, int);
void backpack_menu();
void food_list();
void key_list();
void spell_list();
void gold_list();
void weapon_list();
void fix_monsters_coordinate(char, int, int);
void fix_monsters_area();
void check_monster_area();
void follow1();
void follow2();
void follow3();
void use_menu();
void use_weapon();
void use_spell();
void use_food();
void use_short_weapon();
void use_long_weapon();
void mace_info_menu();
void dagger_info_menu();
void magic_wand_info_menu();
void normal_arrow_info_menu();
void sword_info_menu();
void hit();
void mace_hit();
void dagger_hit();
void magic_wand_hit();
void normal_arrow_hit();
void sword_hit();
void staircase();
void return_game_to_original();
void deamon_death();
void fire_death();
void giant_death();
void snake_death();
void undeed_death();
void deamo_damage();
void fire_damage();
void giant_damage();
void snake_damage();
void undeed_damage();
void hero_damage();
void lost_game();
void fix_hunger();
void use_health_spell();
void use_speed_spell();
void use_damage_spell();
void fix_filling_life();
void fix_fast_move(char);
void fix_damage();
void treasure_room();
void win_game();
void fix_rooms_area();
void fix_fast_move_to_end(char);
void show_hidden();
void show_few_steps();
void empty_monster_map();
void show_rooms();
void print_desired_room(int);
void show_map();
void low_staircase();
void fix_change_foods();


//-------------------------------------------------------------------------
#define MAX_PEOPLE 100
#define MAX_LETTER 100
char username[MAX_LETTER], password[MAX_LETTER], email[MAX_LETTER];
char people_name[MAX_PEOPLE][MAX_LETTER];
int people_score[MAX_PEOPLE];
int people_gold[MAX_PEOPLE];
int people_number_of_game[MAX_PEOPLE];
char reminder[100];
int people_count = 0;
int type_of_user = 1;
int music_mark = 1;
int music_choice = 1;


void introduction();
int welcome_menu();
void sign_up_menu();
void check_username();
void check_password();
void check_email();
void sign_in_menu();
int username_existence();
void password_existence(int);
void scoreboard_menu(int);
void settings_menu(int);
void start_menu();
void print_board();
void save_game(char*);
void initialization();
void pre_game_menu_sign_in();
void pre_game_menu_sign_up();
void back_to_game();
void print_scoreboard_margin();
void sort_people();
void main_menu();
void main_menu_for_guest();
void difficulty_menu();
void set_to_easy();
void set_to_medium();
void set_to_hard();
void random_password();
void profile_menu(int);
void set_email();
void choose_music();











int main() {
    setlocale(LC_CTYPE, "");
    initscr();
    curs_set(0);
    srand(time(NULL)); 
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair (0, COLOR_WHITE, COLOR_BLACK);
    init_pair (1, COLOR_RED, COLOR_BLACK);
    init_pair (2, COLOR_GREEN, COLOR_BLACK);
    init_pair (3, COLOR_YELLOW, COLOR_BLACK);
    init_pair (4, 214, COLOR_BLACK);  //orange
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Quit();
        return 1;
    }
    Mix_Music *music1 = Mix_LoadMUS("music.mp3");
    Mix_Music *music2 = Mix_LoadMUS("music2.mp3");
    Mix_Music *music3 = Mix_LoadMUS("music3.mp3");
    Mix_PlayMusic(music1, -1); 

    // settings_menu(0);



    //treasure_room();

    initialization();


    introduction();
    start_game();


    Mix_HaltMusic();
    Mix_FreeMusic(music1);
    Mix_FreeMusic(music2);
    Mix_FreeMusic(music3);
    Mix_CloseAudio();
    SDL_Quit();
    refresh(); 
    endwin(); 
    return 0;
}
void print_board() {
    for (int i=0; i<120; i++) {     
        mvprintw (0, i, "%%");
        mvprintw (33, i, "%%");
    }
    for (int i=0; i<=33; i++) {
        mvprintw (i, 0, "%%");
        mvprintw (i, 120, "%%");
    }
}
void introduction () {
    print_board();
    print_menu_margin();
    int choice = welcome_menu();
    switch (choice) {
        case 0:
            curs_set(TRUE);
            sign_up_menu();
            break;
        case 1:
            curs_set(TRUE);
            sign_in_menu();
        case 2:
            type_of_user = 0;
            clear();
            difficulty_menu();
        case 3:
            endwin();
            exit(0);
    }
}
int welcome_menu () {
    mvprintw (10, 49, "Welcome To The GAME :)");
    mvprintw (29, 69, "Negin Taeibi");

    int ch;
    int highlight = 0;
    char *choice[4] = {"Sing Up", "Sing In", "Log in as a guest", "Exit"};
    int num_choice = 4;

    while (1) {

        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
                mvprintw(2*i+16, 50, "%s", choice[i]);
                attroff(A_REVERSE);
            }
            else {
                mvprintw(2*i+16, 50, "%s", choice[i]);
            }
        }

        ch = getch();

        switch (ch) {
            case '8':
                highlight = (highlight == 0) ? num_choice - 1 : highlight - 1;
                break;
            case '2':
                highlight = (highlight == num_choice - 1) ? 0 : highlight  + 1;
                break;
            default:
                refresh();
                return highlight;
        }
    }
}
void sign_up_menu() {
    clear();
    echo();
    print_board();
    print_menu_margin();

    FILE *file;
    file = fopen("menu.txt", "a");

    mvprintw (10, 52, "Create an account");
    mvprintw (15, 45, "Username: ");
    mvprintw (17, 45, "password: ");
    mvprintw (19, 45, "email: ");


    mvgetstr (15, 55, username);
    username[strcspn (username, "\n")] = 0;
    check_username ();
    fprintf (file, "%s\n", username);

    mvgetstr (17, 55, password);
    password[strcspn (password, "\n")] = 0;
    if (strcmp (password, "random") == 0) {
        random_password();
    }
    else {
        check_password ();
    }
    fprintf (file, "%s\n", password);

    mvgetstr (19, 52, email);
    email[strcspn (email, "\n")] = 0;
    check_email ();
    fprintf (file, "%s\n", email);

    fclose(file);
    noecho();
    clear();
    pre_game_menu_sign_up();
}
void check_username () {
    FILE *file2;
    char line[100];
    int linenumber = 0, found = 0;
    file2 = fopen ("menu.txt", "r");

    while (fgets (line, sizeof(line), file2)) {
        linenumber++;

        if (linenumber % 3 == 1) {
            if (strstr (line, username) != NULL) {
                found = 1;
            }
        }
    }

    if (found) {
        mvprintw (25, 49, "Username already exists");

        for (int i=0; i<strlen(username); i++) {
            mvprintw (15, (55+i), " ");
        }

        mvgetstr (15, 55, username);
        check_username ();
    }
    else {
        mvprintw (25, 41, "                                       ");
    }
    fclose (file2);
}
void check_password () {
    mvprintw (25, 41, "                                       ");
    mvprintw (26, 41, "                                       ");
    if (strlen (password) < 7) {
        mvprintw (25, 47, "The password is too short");

        for (int i=0; i<strlen(password); i++) {
            mvprintw (17, (55+i), " ");
        }

        mvgetstr (17, 55, password);
        check_password ();
    }

    else {
        int x = 0;
        for (int i=0; i<strlen(password); i++) {
            if (password[i] >= 48 && password[i] <= 57){
                x = 1;
            }
        }
        if (!x) {
            mvprintw (25, 47, "The password must contain");
            mvprintw (26, 49, "a numeric character");
            for (int i=0; i<strlen(password); i++) {
                mvprintw (17, (55+i), " ");
            }

            mvgetstr (17, 55, password);
            check_password ();
        }

        x = 0;
        for (int i=0; i<strlen(password); i++) {
            if (password[i] >= 65 && password[i] <= 90){
                x = 1;
            }
        }
        if (!x) {
            mvprintw (25, 47, "The password must contain");
            mvprintw (26, 50, "an uppercase letter");
            for (int i=0; i<strlen(password); i++) {
                mvprintw (17, (55+i), " ");
            }

            mvgetstr (17, 55, password);
            check_password ();
        }

        x = 0;
        for (int i=0; i<strlen(password); i++) {
            if (password[i] >= 97 && password[i] <= 122){
                x = 1;
            }
        }
        if (!x) {
            mvprintw (25, 47, "The password must contain");
            mvprintw (26, 50, "a lowercase letter");
            for (int i=0; i<strlen(password); i++) {
                mvprintw (17, (55+i), " ");
            }

            mvgetstr (17, 55, password);
            check_password ();
        }
    }
}
void check_email () {
    int x = 0;
    int sign = 0;

    for (int i=0; i<strlen(email); i++) {
        if (email[i] == '@') {
            x++;
            sign = i;
            break;
        }
    }

    if (!x) {
        mvprintw (25, 50, "The email is invalid");
        for (int i=0; i<strlen(email); i++) {
            mvprintw (19, (52+i), " ");
        }

        mvgetstr (19, 52, email);
        check_email ();
    }
    
    x = 0;
    for (int i=sign; i<strlen(email); i++) {
        if (email[i] == '.') {
            x++;
            sign = i;
            break;
        }
    }

    if (!x) {
        mvprintw (25, 50, "The email is invalid");
        for (int i=0; i<strlen(email); i++) {
            mvprintw (19, (52+i), " ");
        }

        mvgetstr (19, 52, email);
        check_email ();
    }

    else if (email[sign+1] == '\0') {
        mvprintw (25, 50, "The email is invalid");
        for (int i=0; i<strlen(email); i++) {
            mvprintw (19, (52+i), " ");
        }

        mvgetstr (19, 52, email);
        check_email ();
    }
}
void sign_in_menu () {
    clear();
    echo();
    print_board();
    print_menu_margin();

    mvprintw (10, 50, "Login to your account");
    mvprintw (15, 45, "Username: ");
    mvprintw (17, 45, "password: ");
    
    mvgetstr (15, 55, username);
    username[strcspn (username, "\n")] = 0;
    int line = username_existence ();

    mvgetstr (17, 55, password);
    password[strcspn (password, "\n")] = 0;
    password_existence (line);
    set_email(line+1);

    noecho();
    clear();
    pre_game_menu_sign_in();
}
int username_existence() {
    FILE *file;
    file = fopen("menu.txt", "r");
    char line[100];
    int linenumber = 0, found = 0;

    while (fgets (line, sizeof(line), file)) {
        linenumber++;

        if (linenumber % 3 == 1) {
            if (strstr (line, username) != NULL) {
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        mvprintw (25, 47, "This username does not exist");

        for (int i=0; i<strlen(username); i++) {
            mvprintw (15, (55+i), " ");
        }

        mvgetstr (15, 55, username);
        username_existence ();
    }
    else {
        mvprintw (25, 42, "                                      ");
    }
    fclose (file);
    return(linenumber);
}
void password_existence(int true_linenumber) {
    FILE *file;
    file = fopen("menu.txt", "r");
    char line[100];
    int found = 0, linenumber = 0;
    char true_password[100];

    while (fgets (line, sizeof(line), file)) {
        if (linenumber == true_linenumber) {
            strcpy(true_password, line);
            line[strlen(line) - 1] = '\0';
            if (strcmp (line, password) == 0) {
                found = 1;
                break;
            }
        }
        linenumber++;
    }

    if (!found) {
        mvprintw (25, 47, "The password is not correct");
        mvprintw (26, 47, "Your password starts with %c%c%c", true_password[0], true_password[1], true_password[2]);

        for (int i=0; i<strlen(password); i++) {
            mvprintw (17, (55+i), " ");
        }

        mvgetstr (17, 55, password);
        password_existence (true_linenumber);
    }


    fclose (file);
    clear();
}
void initialization() {
    for (int i=0; i<=5; i++) {
        deamon_coordinate[i].x = 0;
        deamon_coordinate[i].y = 0;
        deamon_coordinate[i].area_x1 = 0;
        deamon_coordinate[i].area_x2 = 0;
        deamon_coordinate[i].area_y1 = 0;
        deamon_coordinate[i].area_y2 = 0;
        fire_coordinate[i].x = 0;
        fire_coordinate[i].y = 0;
        fire_coordinate[i].area_x1 = 0;
        fire_coordinate[i].area_x2 = 0;
        fire_coordinate[i].area_y1 = 0;
        fire_coordinate[i].area_y2 = 0;
        giant_coordinate[i].x = 0;
        giant_coordinate[i].y = 0;
        giant_coordinate[i].area_x1 = 0;
        giant_coordinate[i].area_x2 = 0;
        giant_coordinate[i].area_y1 = 0;
        giant_coordinate[i].area_y2 = 0;
        snake_coordinate[i].x = 0;
        snake_coordinate[i].y = 0;
        snake_coordinate[i].area_x1 = 0;
        snake_coordinate[i].area_x2 = 0;
        snake_coordinate[i].area_y1 = 0;
        snake_coordinate[i].area_y2 = 0;
        undeed_coordinate[i].x = 0;
        undeed_coordinate[i].y = 0;
        undeed_coordinate[i].area_x1 = 0;
        undeed_coordinate[i].area_x2 = 0;
        undeed_coordinate[i].area_y1 = 0;
        undeed_coordinate[i].area_y2 = 0;
        staircase_coordinate[i].x = 0;
        staircase_coordinate[i].y = 0;
        staircase_coordinate[i].area_x1 = 0;
        staircase_coordinate[i].area_x2 = 0;
        staircase_coordinate[i].area_y1 = 0;
        staircase_coordinate[i].area_y2 = 0;
    }
    for (int i=0; i<6; i++) {
        for (int j=0; j<34; j++) {
            for (int z=0; z<121; z++) {
                map[i][j][z] = ' ';
                running_map[i][j][z] = ' ';
            }
        }
    }
}
void pre_game_menu_sign_up() {
    clear();
    print_board();
    print_menu_margin();
    curs_set(0);
    mvprintw (10, 57, "ROGUE");

    int ch;
    int highlight = 0;
    char *choice[4] = {"Start a new game", "Scoreboard", "Settings", "Profile"};
    int num_choice = 4;

    while (1) {

        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
                mvprintw(2*i+16, 50, "%s", choice[i]);
                attroff(A_REVERSE);
            }
            else {
                mvprintw(2*i+16, 50, "%s", choice[i]);
            }
        }

        ch = getch();

        if (ch == '8') {
            if (highlight == 0) {
                highlight = num_choice - 1;
            }
            else {
                highlight--;
            }
        }
        else if (ch == '2') {
            if (highlight == num_choice - 1) {
                highlight = 0;
            }
            else {
                highlight++;
            }
        }
        else {
            break;
        }
        refresh();
    }

    if (highlight == 0) {
        clear();
        difficulty_menu();
    }
    else if (highlight == 1) {
        clear();
        scoreboard_menu(0);
    }
    else if (highlight == 2) {
        clear();
        settings_menu(0);
    }
    else if (highlight == 3) {
        clear();
        profile_menu(0);

    }
}
void pre_game_menu_sign_in() {
    clear();
    print_board();
    print_menu_margin();
    curs_set(0);
    mvprintw (10, 57, "ROGUE");

    int ch;
    int highlight = 0;
    char *choice[5] = {"Start a new game", "Back to last game", "Scoreboard", "Settings", "Profile"};
    int num_choice = 5;

    while (1) {

        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
                mvprintw(2*i+16, 50, "%s", choice[i]);
                attroff(A_REVERSE);
            }
            else {
                mvprintw(2*i+16, 50, "%s", choice[i]);
            }
        }

        ch = getch();

        if (ch == '8') {
            if (highlight == 0) {
                highlight = num_choice - 1;
            }
            else {
                highlight--;
            }
        }
        else if (ch == '2') {
            if (highlight == num_choice - 1) {
                highlight = 0;
            }
            else {
                highlight++;
            }
        }
        else {
            break;
        }
        refresh();
    }

    if (highlight == 0) {
        clear();
        difficulty_menu();
    }
    else if (highlight == 1) {
        clear();
        back_to_game();
    }
    else if (highlight == 2) {
        clear();
        scoreboard_menu(1);
    }
    else if (highlight == 3) {
        clear();
        settings_menu(1);
    }
    else if (highlight == 4) {
        clear();
        profile_menu(1);
    }
}
void scoreboard_menu(int mark) {
    clear();
    mvprintw (5, 55, "Scoreboard");
    attron (A_BOLD);
    mvprintw (9, 15, "Rank       Name                     Score       Gold       Number of Games       Experience");
    attroff (A_BOLD);

    FILE *file;
    file = fopen("menu.txt", "r");
    char line[100];
    int linenumber = 0;
    sort_people();
    

    for (int i=0; i<people_count; i++) {
        people_name[i][strlen(people_name[i]) - 1] = '\0';
        if (i == 0 || i == 1 || i == 2) {
            attron(COLOR_PAIR(4));
            mvprintw (11 + i, 16, "%d", i+1);
            mvprintw (11 + i, 26, "%s", people_name[i]);
            mvprintw (11 + i, 53, "%d", people_score[i]);
            mvprintw (11 + i, 64, "%d", people_gold[i]);
            mvprintw (11 + i, 80, "%d", people_number_of_game[i]);
            attroff(COLOR_PAIR(4));
            if (i == 0) {
                int x = strlen(people_name[i]);
                mvprintw (11 + i, 27+x, "(Legendary)");
                mvprintw (11 + i, 18, "🥇");
            }
            else if (i == 1) {
                int x = strlen(people_name[i]);
                mvprintw (11 + i, 27+x, "(Master)");
                mvprintw (11 + i, 18, "🥈");
            }
            else if (i == 2) {
                int x = strlen(people_name[i]);
                mvprintw (11 + i, 27+x, "(Pro)");
                mvprintw (11 + i, 18, "🥉");
            }
        }
        else if (strcmp(people_name[i], username) == 0) {
            attron(COLOR_PAIR(2));
            mvprintw (11 + i, 16, "%d", i+1);
            mvprintw (11 + i, 26, "%s", people_name[i]);
            mvprintw (11 + i, 53, "%d", people_score[i]);
            mvprintw (11 + i, 64, "%d", people_gold[i]);
            mvprintw (11 + i, 80, "%d", people_number_of_game[i]);
            attroff(COLOR_PAIR(2));
        }
        else {
            mvprintw (11 + i, 16, "%d", i+1);
            mvprintw (11 + i, 26, "%s", people_name[i]);
            mvprintw (11 + i, 53, "%d", people_score[i]);
            mvprintw (11 + i, 64, "%d", people_gold[i]);
            mvprintw (11 + i, 80, "%d", people_number_of_game[i]);
        }
        
    }
    
    print_board();
    print_scoreboard_margin();
    
    fclose (file);
    attron (A_REVERSE);
    mvprintw (28, 103, "Back");
    attroff (A_REVERSE);
    getch();
    if (mark) {
        pre_game_menu_sign_in();
    }
    else {
        pre_game_menu_sign_up();
    }
}
void print_scoreboard_margin() {
    for (int i=10; i<110; i++) {     
        mvprintw (3, i, "%%");
        mvprintw (30, i, "%%");
        mvprintw (7, i, "%%");
    }
    for (int i=3; i<=30; i++) {
        mvprintw (i, 10, "%%");
        mvprintw (i, 110, "%%");
    }
}
void sort_people() {
    FILE *savefile;
    savefile = fopen ("save.txt", "r");
    char line[100];
    int linenumber = 0;
    people_count = 0;
    
    while (fgets(line, sizeof(line), savefile)) {
        if (strcmp (line, "end\n") == 0) {
            fgets(line, sizeof(line), savefile);
            strcpy (people_name[people_count], line);
            fgets(line, sizeof(line), savefile);
            fgets(line, sizeof(line), savefile);
            int x = atoi (line);
            people_number_of_game[people_count] = x;
            fgets(line, sizeof(line), savefile);
            x = atoi (line);
            people_score[people_count] = x;
            fgets(line, sizeof(line), savefile);
            x = atoi (line);
            fgets(line, sizeof(line), savefile);
            x += atoi (line) * 3;
            people_gold[people_count] = x;
            people_count++;
        }
    }

    for (int i=0; i<people_count-1; i++) {
        for (int j=0; j<people_count-1; j++) {
            if (people_score[j] < people_score[j+1]) {
                int temp = people_score[j];
                people_score[j] = people_score[j+1];
                people_score[j+1] = temp;

                char temp2[100];
                strcpy(temp2, people_name[j]);
                strcpy(people_name[j], people_name[j+1]);
                strcpy(people_name[j+1], temp2);

                temp = people_gold[j];
                people_gold[j] = people_gold[j+1];
                people_gold[j+1] = temp;

                temp = people_number_of_game[j];
                people_number_of_game[j] = people_number_of_game[j+1];
                people_number_of_game[j+1] = temp;
            }
        }
    }
    fclose (savefile);
}
void back_to_game() {
    FILE *savefile;
    savefile = fopen("save.txt", "r");
    char line[200];
    int linenumber = 0;
    int found = 0;

    while (fgets(line, sizeof(line), savefile)) {
        if (strcmp (line, "start\n") == 0) {
            fgets(line, sizeof(line), savefile);
            line[strlen(line) - 1] = '\0';
            if (strcmp (line, username) == 0) {
                found = 1;
                fgets(line, sizeof(line), savefile);
                int x = atoi (line);
                score = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_of_game = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                highest_score = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_normal_gold = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_black_gold = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                position_x = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                position_y = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                level = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                health = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_traps = x;
                
                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_secret_doors = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_password_doors = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                hunger = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_health_spell = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_damage_spell = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_speed_spell = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_normal_food = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_normal_gold = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_black_gold = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_dagger = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_magic_wand = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_normal_arrow = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_sword = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_master_key = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_broken_master_key = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_health_spell = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_damage_spell = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_speed_spell = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_normal_food = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_mace = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_dagger = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_magic_wand = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_normal_arrow = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_sword = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_deamon_health = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_fire_health = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_giant_health = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_snake_health = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_undeed_health = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_giant_move = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_snake_move = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                number_undeed_move = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                power_mace = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                power_dagger = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                power_magic_wand = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                power_normal_arrow = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                power_sword = x;

                fgets(line, sizeof(line), savefile);
                last = line[0];

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                last_color = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                last_password = x;

                fgets(line, sizeof(line), savefile);
                know_weapon = line[0];

                fgets(line, sizeof(line), savefile);
                direction = line[0];

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                repeat_shot = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                move_count = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_move_health_spell = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_move_speed_spell = x;

                fgets(line, sizeof(line), savefile);
                x = atoi (line);
                count_move_damage_spell = x;
                
                for (int i=1; i<=level; i++) {
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    deamon_coordinate[i].x = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    deamon_coordinate[i].y = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    deamon_coordinate[i].area_x1 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    deamon_coordinate[i].area_x2 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    deamon_coordinate[i].area_y1 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    deamon_coordinate[i].area_y2 = x;
                }

                for (int i=1; i<=level; i++) {
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    fire_coordinate[i].x = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    fire_coordinate[i].y = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    fire_coordinate[i].area_x1 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    fire_coordinate[i].area_x2 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    fire_coordinate[i].area_y1 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    fire_coordinate[i].area_y2 = x;
                }

                for (int i=1; i<=level; i++) {
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    giant_coordinate[i].x = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    giant_coordinate[i].y = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    giant_coordinate[i].area_x1 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    giant_coordinate[i].area_x2 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    giant_coordinate[i].area_y1 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    giant_coordinate[i].area_y2 = x;
                }

                for (int i=1; i<=level; i++) {
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    snake_coordinate[i].x = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    snake_coordinate[i].y = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    snake_coordinate[i].area_x1 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    snake_coordinate[i].area_x2 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    snake_coordinate[i].area_y1 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    snake_coordinate[i].area_y2 = x;
                }

                for (int i=1; i<=level; i++) {
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    undeed_coordinate[i].x = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    undeed_coordinate[i].y = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    undeed_coordinate[i].area_x1 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    undeed_coordinate[i].area_x2 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    undeed_coordinate[i].area_y1 = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    undeed_coordinate[i].area_y2 = x;
                }

                for (int i=1; i<=3; i++) {
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    staircase_coordinate[i].x = x;
                    fgets(line, sizeof(line), savefile);
                    x = atoi (line);
                    staircase_coordinate[i].y = x;
                }
                
                for (int i=1; i<=level; i++) {
                    for (int j=0; j<34; j++) {
                        fgets (line, sizeof(line), savefile);
                        line[strlen(line) - 1] = '\0';
                        strcpy(map[i][j], line);
                    }
                }

                for (int i=1; i<=level; i++) {
                    for (int j=0; j<34; j++) {
                        fgets (line, sizeof(line), savefile);
                        line[strlen(line) - 1] = '\0';
                        strcpy(running_map[i][j], line);
                    }
                }
                print_running_map();
                movemennt();
            }
        }
    }
    if (!found) {
        pre_game_menu_sign_in();
    }
    fclose (savefile);
}
void main_menu() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 57, "ROGUE");

    int ch;
    int highlight = 0;
    char *choice[4] = {"Return", "Save and exit", "Misic","Exit"};
    int num_choice = 4;

    while (1) {

        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
                mvprintw(2*i+16, 53, "%s", choice[i]);
                attroff(A_REVERSE);
            }
            else {
                mvprintw(2*i+16, 53, "%s", choice[i]);
            }
        }

        ch = getch();

        if (ch == '8') {
            if (highlight == 0) {
                highlight = num_choice - 1;
            }
            else {
                highlight--;
            }
        }
        else if (ch == '2') {
            if (highlight == num_choice - 1) {
                highlight = 0;
            }
            else {
                highlight++;
            }
        }
        else {
            break;
        }
        refresh();
    }

    if (highlight == 0) {
        print_running_map();
    }
    else if (highlight == 1) {
        save_game("start");
    }
    else if (highlight == 2) {
        if(music_mark) {
            Mix_HaltMusic();
            music_mark = 0;
            main_menu();
        }
        else {
            Mix_HaltMusic();
            Mix_Music *music3 = Mix_LoadMUS("music3.mp3");
            Mix_PlayMusic(music3, -1); 
            music_mark = 1;
            main_menu();
        }
    }
    else if (highlight == 3) {
        endwin();
        exit(0);
    }


    getch();
}
void save_game(char* type) {
    FILE *file;
    file = fopen("save.txt", "a");
    fprintf (file, "%s\n", type);
    fprintf (file, "%s\n", username);
    fprintf (file, "%d\n", score);
    fprintf (file, "%d\n", number_of_game);
    fprintf (file, "%d\n", highest_score);
    fprintf (file, "%d\n", count_normal_gold);
    fprintf (file, "%d\n", count_black_gold);
    fprintf (file, "%d\n", position_x);
    fprintf (file, "%d\n", position_y);
    fprintf (file, "%d\n", level); 
    fprintf (file, "%d\n", health);
    fprintf (file, "%d\n", number_traps);
    fprintf (file, "%d\n", number_secret_doors);
    fprintf (file, "%d\n", number_password_doors);
    fprintf (file, "%d\n", hunger);
    fprintf (file, "%d\n", number_health_spell);
    fprintf (file, "%d\n", number_damage_spell);
    fprintf (file, "%d\n", number_speed_spell);
    fprintf (file, "%d\n", number_normal_food);
    fprintf (file, "%d\n", number_normal_gold);
    fprintf (file, "%d\n", number_black_gold);
    fprintf (file, "%d\n", number_dagger);
    fprintf (file, "%d\n", number_magic_wand);
    fprintf (file, "%d\n", number_normal_arrow);
    fprintf (file, "%d\n", number_sword);
    fprintf (file, "%d\n", count_master_key);
    fprintf (file, "%d\n", count_broken_master_key);
    fprintf (file, "%d\n", count_health_spell);
    fprintf (file, "%d\n", count_damage_spell);
    fprintf (file, "%d\n", count_speed_spell);
    fprintf (file, "%d\n", count_normal_food);
    fprintf (file, "%d\n", count_mace);
    fprintf (file, "%d\n", count_dagger);
    fprintf (file, "%d\n", count_magic_wand);
    fprintf (file, "%d\n", count_normal_arrow);
    fprintf (file, "%d\n", count_sword);
    fprintf (file, "%d\n", number_deamon_health);
    fprintf (file, "%d\n", number_fire_health);
    fprintf (file, "%d\n", number_giant_health);
    fprintf (file, "%d\n", number_snake_health);
    fprintf (file, "%d\n", number_undeed_health);
    fprintf (file, "%d\n", number_giant_move);
    fprintf (file, "%d\n", number_snake_move);
    fprintf (file, "%d\n", number_undeed_move);
    fprintf (file, "%d\n", power_mace);
    fprintf (file, "%d\n", power_dagger);
    fprintf (file, "%d\n", power_magic_wand);
    fprintf (file, "%d\n", power_normal_arrow);
    fprintf (file, "%d\n", power_sword);
    fprintf (file, "%c\n", last);
    fprintf (file, "%d\n", last_color);
    fprintf (file, "%d\n", last_password);
    fprintf (file, "%c\n", know_weapon);
    fprintf (file, "%c\n", direction);
    fprintf (file, "%d\n", repeat_shot);
    fprintf (file, "%d\n", move_count);
    fprintf (file, "%d\n", count_move_health_spell);
    fprintf (file, "%d\n", count_move_speed_spell);
    fprintf (file, "%d\n", count_move_damage_spell);    
    for (int i=1; i<=level; i++) {
        fprintf (file, "%d\n", deamon_coordinate[i].x);
        fprintf (file, "%d\n", deamon_coordinate[i].y);
        fprintf (file, "%d\n", deamon_coordinate[i].area_x1);
        fprintf (file, "%d\n", deamon_coordinate[i].area_x2);
        fprintf (file, "%d\n", deamon_coordinate[i].area_y1);
        fprintf (file, "%d\n", deamon_coordinate[i].area_y2);
    }
    for (int i=1; i<=level; i++) {
        fprintf (file, "%d\n", fire_coordinate[i].x);
        fprintf (file, "%d\n", fire_coordinate[i].y);
        fprintf (file, "%d\n", fire_coordinate[i].area_x1);
        fprintf (file, "%d\n", fire_coordinate[i].area_x2);
        fprintf (file, "%d\n", fire_coordinate[i].area_y1);
        fprintf (file, "%d\n", fire_coordinate[i].area_y2);
    }
    for (int i=1; i<=level; i++) {
        fprintf (file, "%d\n", giant_coordinate[i].x);
        fprintf (file, "%d\n", giant_coordinate[i].y);
        fprintf (file, "%d\n", giant_coordinate[i].area_x1);
        fprintf (file, "%d\n", giant_coordinate[i].area_x2);
        fprintf (file, "%d\n", giant_coordinate[i].area_y1);
        fprintf (file, "%d\n", giant_coordinate[i].area_y2);
    }
    for (int i=1; i<=level; i++) {
        fprintf (file, "%d\n", snake_coordinate[i].x);
        fprintf (file, "%d\n", snake_coordinate[i].y);
        fprintf (file, "%d\n", snake_coordinate[i].area_x1);
        fprintf (file, "%d\n", snake_coordinate[i].area_x2);
        fprintf (file, "%d\n", snake_coordinate[i].area_y1);
        fprintf (file, "%d\n", snake_coordinate[i].area_y2);
    }
    for (int i=1; i<=level; i++) {
        fprintf (file, "%d\n", undeed_coordinate[i].x);
        fprintf (file, "%d\n", undeed_coordinate[i].y);
        fprintf (file, "%d\n", undeed_coordinate[i].area_x1);
        fprintf (file, "%d\n", undeed_coordinate[i].area_x2);
        fprintf (file, "%d\n", undeed_coordinate[i].area_y1);
        fprintf (file, "%d\n", undeed_coordinate[i].area_y2);
    }
    for (int i=1; i<=3; i++) {
        fprintf (file, "%d\n", staircase_coordinate[i].x);
        fprintf (file, "%d\n", staircase_coordinate[i].y);
    }
    for (int z=1; z<=level; z++) {
        for (int i=0; i<34; i++) {
            for (int j=0; j<121; j++) {
                fprintf (file, "%c", map[z][i][j]);
            }
            fprintf (file, "\n");
        }
    }
    for (int z=1; z<=level; z++) {
        for (int i=0; i<34; i++) {
            for (int j=0; j<121; j++) {
                fprintf (file, "%c", running_map[z][i][j]);
            }
            fprintf (file, "\n");
        }
    }
    fclose (file);
}
void main_menu_for_guest() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 57, "ROGUE");

    int ch;
    int highlight = 0;
    char *choice[3] = {"Return", "Music","Exit"};
    int num_choice = 3;

    while (1) {

        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
                mvprintw(2*i+16, 53, "%s", choice[i]);
                attroff(A_REVERSE);
            }
            else {
                mvprintw(2*i+16, 53, "%s", choice[i]);
            }
        }

        ch = getch();

        if (ch == '8') {
            if (highlight == 0) {
                highlight = num_choice - 1;
            }
            else {
                highlight--;
            }
        }
        else if (ch == '2') {
            if (highlight == num_choice - 1) {
                highlight = 0;
            }
            else {
                highlight++;
            }
        }
        else {
            break;
        }
        refresh();
    }

    if (highlight == 0) {
        print_running_map();
    }
    else if (highlight == 1) {
        if(music_mark) {
            Mix_HaltMusic();
            music_mark = 0;
            main_menu_for_guest();
        }
        else {
            Mix_HaltMusic();
            Mix_Music *music3 = Mix_LoadMUS("music3.mp3");
            Mix_PlayMusic(music3, -1); 
            music_mark = 1;
            main_menu_for_guest();
        }
    }
    else if (highlight == 2) {
        endwin();
        exit(0);
    }
    getch();
}
void settings_menu(int mark) {
    clear();
    print_board();
    print_menu_margin();
    mvprintw (10, 56, "Settings");

    int ch;
    int highlight = 0;
    char *choice[2] = {"Music", "Back"};
    int num_choice = 2;

    while (1) {
        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                if (strcmp(choice[i], "Back") == 0) {
                    attron(A_REVERSE);
                    mvprintw(26, 72, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
                else {
                    attron(A_REVERSE);
                    mvprintw(2*i+15, 57, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
            }
            else {
                if (strcmp(choice[i], "Back") == 0) {
                    mvprintw(26, 72, "%s", choice[i]);
                }
                else {
                    mvprintw(2*i+15, 57, "%s", choice[i]);
                }
            }
        }
        ch = getch();
        if (ch == '8') {
            if (highlight == 0) {
                highlight = num_choice - 1;
            }
            else {
                highlight--;
            }
        }
        else if (ch == '2') {
            if (highlight == num_choice - 1) {
                highlight = 0;
            }
            else {
                highlight++;
            }
        }
        else {
            break;
        }
        refresh();
    }
    if (highlight == 0) {
        choose_music(mark);
    }
    else if (highlight == 1) {
        if (mark) {
            pre_game_menu_sign_in();
        }
        else {
            pre_game_menu_sign_up();
        }
    }
   


    // attron(A_REVERSE);
    // mvprintw (26, 72, "Back");
    // attroff(A_REVERSE);
    // getch();
    // if (mark) {
    //     pre_game_menu_sign_in();
    // }
    // else {
    //     pre_game_menu_sign_up();
    // }

}
void difficulty_menu() {
    clear();
    print_board();
    print_menu_margin();
    curs_set(0);
    mvprintw (10, 55, "Difficulty");
    int ch;
    int highlight = 0;
    char *choice[3] = {"Easy", "Medium", "Hard"};
    int num_choice = 3;

    while (1) {

        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
                mvprintw(2*i+16, 57, "%s", choice[i]);
                attroff(A_REVERSE);
            }
            else {
                mvprintw(2*i+16, 57, "%s", choice[i]);
            }
        }

        ch = getch();

        if (ch == '8') {
            if (highlight == 0) {
                highlight = num_choice - 1;
            }
            else {
                highlight--;
            }
        }
        else if (ch == '2') {
            if (highlight == num_choice - 1) {
                highlight = 0;
            }
            else {
                highlight++;
            }
        }
        else {
            break;
        }
        refresh();
    }

    if (highlight == 0) {
        clear();
        set_to_easy();
    }
    else if (highlight == 1) {
        clear();
        set_to_medium();
    }
    else if (highlight == 2) {
        clear();
        set_to_hard();
    }

    start_game();
}
void set_to_easy() {
    number_traps = 3;
    number_health_spell = 3;
    number_damage_spell = 3;
    number_speed_spell = 3;
    number_normal_food = 4;
    number_normal_gold = 4;
    number_black_gold = 3;
    number_dagger = 3;
    number_magic_wand = 3; 
    number_normal_arrow = 3; 
    number_sword = 3;
    
    score = 0;
    position_x = 0;
    position_y = 0;
    level = 1;
    health = 20;
    hunger = 0;

    count_master_key = 0;
    count_broken_master_key = 0;
    count_health_spell = 0;
    count_speed_spell = 0;
    count_damage_spell = 0;
    count_normal_food = 0;
    count_normal_gold = 0;
    count_black_gold = 0;
    count_mace = 0;
    count_dagger = 0;
    count_magic_wand = 0;
    count_normal_arrow = 0;
    count_sword = 0;
    count_move_health_spell = 0;
    count_move_speed_spell = 0;
    count_move_damage_spell = 0;
    count_rotten_food = 0;
    count_excellent_food = 0;
    count_magic_food = 0;

    count_land = 0;
    last = '.';
    last_color = 0;
    know_weapon = ' ';
    direction = ' ';
    repeat_shot = 0;
    move_count = 0;
}
void set_to_medium() {
    number_traps = 4;
    number_health_spell = 2;
    number_damage_spell = 2;
    number_speed_spell = 2;
    number_normal_food = 3;
    number_normal_gold = 3;
    number_black_gold = 2;
    number_dagger = 2;
    number_magic_wand = 2; 
    number_normal_arrow = 2; 
    number_sword = 2;

    score = 0;
    position_x = 0;
    position_y = 0;
    level = 1;
    health = 20;
    hunger = 0;

    count_master_key = 0;
    count_broken_master_key = 0;
    count_health_spell = 0;
    count_speed_spell = 0;
    count_damage_spell = 0;
    count_normal_food = 0;
    count_normal_gold = 0;
    count_black_gold = 0;
    count_mace = 0;
    count_dagger = 0;
    count_magic_wand = 0;
    count_normal_arrow = 0;
    count_sword = 0;
    count_move_health_spell = 0;
    count_move_speed_spell = 0;
    count_move_damage_spell = 0;
    count_rotten_food = 0;
    count_excellent_food = 0;
    count_magic_food = 0;

    count_land = 0;
    last = '.';
    last_color = 0;
    know_weapon = ' ';
    direction = ' ';
    repeat_shot = 0;
    move_count = 0;
}
void set_to_hard() {
    number_traps = 5;
    number_health_spell = 1;
    number_damage_spell = 1;
    number_speed_spell = 1;
    number_normal_food = 2;
    number_normal_gold = 2;
    number_black_gold = 1;
    number_dagger = 1;
    number_magic_wand = 1;
    number_normal_arrow = 1;
    number_sword = 1;

    score = 0;
    position_x = 0;
    position_y = 0;
    level = 1;
    health = 20;
    hunger = 0;

    count_master_key = 0;
    count_broken_master_key = 0;
    count_health_spell = 0;
    count_speed_spell = 0;
    count_damage_spell = 0;
    count_normal_food = 0;
    count_normal_gold = 0;
    count_black_gold = 0;
    count_mace = 0;
    count_dagger = 0;
    count_magic_wand = 0;
    count_normal_arrow = 0;
    count_sword = 0;
    count_move_health_spell = 0;
    count_move_speed_spell = 0;
    count_move_damage_spell = 0;
    count_rotten_food = 0;
    count_excellent_food = 0;
    count_magic_food = 0;

    count_land = 0;
    last = '.';
    last_color = 0;
    know_weapon = ' ';
    direction = ' ';
    repeat_shot = 0;
    move_count = 0;
}
void random_password() {
    char charset[100] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < 8; i++) {
        int key = rand() % 62; 
        password[i] = charset[key];
    }
    password[8] = '\0'; 
    mvprintw (17, 55, "%s", password);
}
void profile_menu(int mark) {
    mvprintw (10, 56, "Profile");
    mvprintw (15, 45, "Username:");
    mvprintw (17, 45, "Password:");
    mvprintw (19, 45, "Email:");
    mvprintw (15, 55, "%s", username);
    mvprintw (17, 55, "%s", password);
    mvprintw (19, 52, "%s", email);
    print_board();
    print_menu_margin();
    attron(A_REVERSE);
    mvprintw (26, 72, "Back");
    attroff(A_REVERSE);
    getch();
    if (mark) {
        pre_game_menu_sign_in();
    }
    else {
        pre_game_menu_sign_up();
    }
}
void set_email(int target) {
    FILE *file;
    file = fopen("menu.txt", "r");
    int linenumber = 0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (linenumber == target) {
            strcpy(email, line);
            break;
        }
        linenumber++;
    }
    fclose(file);
}
void choose_music(int mark) {
    clear();
    print_board();
    print_menu_margin();
    mvprintw (10, 57, "Music");

    int ch;
    int highlight = 0;
    char *choice[4] = {"Music1", "Misic2", "Music3", "Back"};
    int num_choice = 4;

    while (1) {
        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                if (strcmp(choice[i], "Back") == 0) {
                    attron(A_REVERSE);
                    mvprintw(26, 72, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
                else {
                    attron(A_REVERSE);
                    mvprintw(2*i+15, 56, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
            }
            else {
                if (strcmp(choice[i], "Back") == 0) {
                    mvprintw(26, 72, "%s", choice[i]);
                }
                else {
                    mvprintw(2*i+15, 56, "%s", choice[i]);
                }
            }
        }
        ch = getch();
        if (ch == '8') {
            if (highlight == 0) {
                highlight = num_choice - 1;
            }
            else {
                highlight--;
            }
        }
        else if (ch == '2') {
            if (highlight == num_choice - 1) {
                highlight = 0;
            }
            else {
                highlight++;
            }
        }
        else {
            break;
        }
        refresh();
    }
    if (highlight == 0) {
        Mix_HaltMusic();
        Mix_Music *music3 = Mix_LoadMUS("music3.mp3");
        Mix_PlayMusic(music3, -1); 
        music_choice = 1;
        sleep(3);
        Mix_HaltMusic();
        Mix_Music *music1 = Mix_LoadMUS("music.mp3");
        Mix_PlayMusic(music1, -1); 
        choose_music(mark);
    }
    else if (highlight == 1) {
        Mix_HaltMusic();
        Mix_Music *music4 = Mix_LoadMUS("music4.mp3");
        Mix_PlayMusic(music4, -1); 
        music_choice = 2;
        sleep(3);
        Mix_HaltMusic();
        Mix_Music *music1 = Mix_LoadMUS("music.mp3");
        Mix_PlayMusic(music1, -1); 
        choose_music(mark);
    }
    else if (highlight == 2) {
        Mix_HaltMusic();
        Mix_Music *music5 = Mix_LoadMUS("music5.mp3");
        Mix_PlayMusic(music5, -1); 
        music_choice = 3;
        sleep(3);
        Mix_HaltMusic();
        Mix_Music *music1 = Mix_LoadMUS("music.mp3");
        Mix_PlayMusic(music1, -1); 
        choose_music(mark);
    }
    else if (highlight == 3) {
        settings_menu(mark);
    }
}











//------------------------------------------
void start_game() {
    noecho();
    curs_set(0);
    if (music_choice == 1) {
        Mix_HaltMusic();
        Mix_Music *music3 = Mix_LoadMUS("music3.mp3");
        Mix_PlayMusic(music3, -1); 
    }
    else if (music_choice == 2) {
        Mix_HaltMusic();
        Mix_Music *music4 = Mix_LoadMUS("music4.mp3");
        Mix_PlayMusic(music4, -1); 
    }
    else if (music_choice == 2) {
        Mix_HaltMusic();
        Mix_Music *music5 = Mix_LoadMUS("music5.mp3");
        Mix_PlayMusic(music5, -1); 
    }
    make_rooms ();
    clean_the_map(level);
    return_game_to_original();
    margin_the_map();
    print_margin();
    placing_room_and_fill_the_map();
    placing_door();
    empty_monster_map();
    for (int i=0; i<5; i++) {       //Placing corridors1
        print_corridor(rectangles[i].door_x, rectangles[i].door_y, rectangles[i+1].door_x, rectangles[i+1].door_y);
    }
    count_land = 0;
    for (int i=0; i<34; i++) {      //Find empty rooms1
        for (int j=0; j<121; j++) {
            if (map[level][i][j] == '.') {
                land[count_land][0] = i;
                land[count_land][1] = j;
                count_land++;
            }
        }
    }
    count_land--;

    if (level == 4) {
        placing_in_map('*', 1, 0, 4);
    }
    else {
        placing_in_map('<', 1, 0, 0);
    }
    if (level == 2 || level == 3) {
        placing_in_map('>', 1, 0, 0);
    }
    placing_in_map('^', number_traps, 0, 0);
    placing_in_map('?', number_secret_doors, 0, 0);
    placing_password_door();
    placing_in_map('!', 1, 0, 4);
    placing_in_map('h', number_health_spell, 0, 0);
    placing_in_map('s', number_speed_spell, 0, 0);
    placing_in_map('d', number_damage_spell, 0, 0);
    placing_in_map('f', number_normal_food, 0, 0);
    placing_in_map('$', number_normal_gold, 0, 0);
    placing_in_map('g', number_black_gold, 0, 0);
    placing_in_map('r', number_dagger, 0, 0);
    placing_in_map('w', number_magic_wand, 0, 0);
    placing_in_map('a', number_normal_arrow, 0, 0);
    placing_in_map('l', number_sword, 0, 0);
    placing_in_map('p', 1, 0, 0);
    placing_in_map('t', 1, 0, 0);
    placing_in_map('e', 1, 0, 0);
    placing_in_map('D', 1, 0, 0);
    placing_in_map('F', 1, 0, 0);
    placing_in_map('G', 1, 0, 0);
    placing_in_map('S', 1, 0, 0);
    placing_in_map('U', 1, 0, 0);
    fix_monsters_area();
    fix_rooms_area();
    print_desired_room(0);
    

    position_x = rectangles[0].x + 1;
    position_y = rectangles[0].y + 1;

    movemennt();

    refresh(); 
    endwin(); 
}
int check_collision(int count, int x, int y) {
    for (int i = 0; i < count; i++) {
        if (x < rectangles[i].x + 11 &&
            x + 11 > rectangles[i].x &&
            y < rectangles[i].y + 11 &&
            y + 11 > rectangles[i].y) {
            return 1; 
        }
    }
    return 0; 
}
void make_rooms () {
    strcpy (rooms[0][0], "______  ");
    strcpy (rooms[0][1], "|....|  ");
    strcpy (rooms[0][2], "|....|  ");
    strcpy (rooms[0][3], "|.o..|  ");
    strcpy (rooms[0][4], "|....|  ");
    strcpy (rooms[0][5], "|____|  ");
    strcpy (rooms[0][6], "        ");
    strcpy (rooms[0][7], "        ");

    strcpy (rooms[1][0], "_______ ");
    strcpy (rooms[1][1], "|.....| ");
    strcpy (rooms[1][2], "|..oo.| ");
    strcpy (rooms[1][3], "|.....| ");
    strcpy (rooms[1][4], "|.....| ");
    strcpy (rooms[1][5], "|_____| ");
    strcpy (rooms[1][6], "        ");
    strcpy (rooms[1][7], "        ");
    
    strcpy (rooms[2][0], "________");
    strcpy (rooms[2][1], "|......|");
    strcpy (rooms[2][2], "|...o..|");
    strcpy (rooms[2][3], "|.o....|");
    strcpy (rooms[2][4], "|......|");
    strcpy (rooms[2][5], "|______|");
    strcpy (rooms[2][6], "        ");
    strcpy (rooms[2][7], "        ");

    strcpy (rooms[3][0], "_______ ");
    strcpy (rooms[3][1], "|.....| ");
    strcpy (rooms[3][2], "|..o..| ");
    strcpy (rooms[3][3], "|.....| ");
    strcpy (rooms[3][4], "|.o...| ");
    strcpy (rooms[3][5], "|.....| ");
    strcpy (rooms[3][6], "|_____| ");
    strcpy (rooms[3][7], "        ");

    strcpy (rooms[4][0], "________");
    strcpy (rooms[4][1], "|......|");
    strcpy (rooms[4][2], "|......|");
    strcpy (rooms[4][3], "|.o....|");
    strcpy (rooms[4][4], "|...o..|");
    strcpy (rooms[4][5], "|......|");
    strcpy (rooms[4][6], "|______|");
    strcpy (rooms[4][7], "        ");

    strcpy (rooms[5][0], "________");
    strcpy (rooms[5][1], "|......|");
    strcpy (rooms[5][2], "|.o....|");
    strcpy (rooms[5][3], "|......|");
    strcpy (rooms[5][4], "|...o..|");
    strcpy (rooms[5][5], "|.o....|");
    strcpy (rooms[5][6], "|......|");
    strcpy (rooms[5][7], "|______|");
}
void clean_the_map() {
    for (int i=0; i<=33; i++) {     
        for (int j=0; j<=120; j++) {
            map[level][i][j] = ' ';
            running_map[level][i][j] = ' ';
        }
    }
}
void margin_the_map() {
    for (int i=0; i<120; i++) {     
        running_map[level][0][i] = '%';
        running_map[level][3][i] = '%';
        running_map[level][33][i] = '%';

        map[level][0][i] = '%';
        map[level][33][i] = '%';
        map[level][3][i] = '%';
    }
    for (int i=0; i<=33; i++) {
        running_map[level][i][0] = '%';
        running_map[level][i][120] = '%';

        map[level][i][0] = '%';
        map[level][i][120] = '%';
    }
}
void print_margin() {
    for (int i=0; i<120; i++) {     
        mvprintw (0, i, "%%");
        mvprintw (33, i, "%%");
        mvprintw (3, i, "%%");
    }
    for (int i=0; i<=33; i++) {
        mvprintw (i, 0, "%%");
        mvprintw (i, 120, "%%");
    }
    mvprintw (1, 13, "Health:");
    for (int i=0; i<health; i++) {
        mvaddch(1, 22+i, '*');
    }
    mvprintw (1, 53, "Hunger:");
    mvprintw (1, 82, ",");
    for (int i=0; i<hunger; i++) {
        mvaddch(1, 62+i, 'f');
    }
    mvprintw (1, 95, "Floor:  %d", level);
}
void placing_room_and_fill_the_map() {
    int count = 0;
    while (count < 6) {     //Placing rooms1
        int x = rand() % (110);
        x++;
        int y = rand() % (20);
        y += 4;

        if (!check_collision(count, x, y)) {
            rectangles[count].x = x;
            rectangles[count].y = y;
            count++;
        }
    }
    for (int i = 0; i < count; i++) {       //print map1
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                // mvaddch(rectangles[i].y + j, rectangles[i].x + k, rooms[i][j][k]);
                // running_map[level][rectangles[i].y + j][rectangles[i].x + k] = rooms[i][j][k];
            }
        }
    }   
    for (int i=0; i<8; i++) {       //Fill the map1
        for (int j=0; j<8; j++) {
            if (rooms[0][i][j] == '|') {
                map[level][rectangles[0].y + i][rectangles[0].x + j] = '|';
            }
            else if (rooms[0][i][j] == '_') {
                map[level][rectangles[0].y + i][rectangles[0].x + j] = '_';
            }
            else if (rooms[0][i][j] == '.') {
                map[level][rectangles[0].y + i][rectangles[0].x + j] = '.';
            }
            else if (rooms[0][i][j] == ' ') {
                map[level][rectangles[0].y + i][rectangles[0].x + j] = ' '; 
            }
            else if (rooms[0][i][j] == 'o') {
                map[level][rectangles[0].y + i][rectangles[0].x + j] = 'o'; 
            }
        }
    }
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (rooms[1][i][j] == '|') {
                map[level][rectangles[1].y + i][rectangles[1].x + j] = '|';
            }
            else if (rooms[1][i][j] == '_') {
                map[level][rectangles[1].y + i][rectangles[1].x + j] = '_';
            }
            else if (rooms[1][i][j] == '.') {
                map[level][rectangles[1].y + i][rectangles[1].x + j] = '.';
            }
            else if (rooms[1][i][j] == ' ') {
                map[level][rectangles[1].y + i][rectangles[1].x + j] = ' '; 
            }
            else if (rooms[1][i][j] == 'o') {
                map[level][rectangles[1].y + i][rectangles[1].x + j] = 'o'; 
            }
        }
    }
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (rooms[2][i][j] == '|') {
                map[level][rectangles[2].y + i][rectangles[2].x + j] = '|';
            }
            else if (rooms[2][i][j] == '_') {
                map[level][rectangles[2].y + i][rectangles[2].x + j] = '_';
            }
            else if (rooms[2][i][j] == '.') {
                map[level][rectangles[2].y + i][rectangles[2].x + j] = '.';
            }
            else if (rooms[2][i][j] == ' ') {
                map[level][rectangles[2].y + i][rectangles[2].x + j] = ' '; 
            }
            else if (rooms[2][i][j] == 'o') {
                map[level][rectangles[2].y + i][rectangles[2].x + j] = 'o'; 
            }
        }
    }
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (rooms[3][i][j] == '|') {
                map[level][rectangles[3].y + i][rectangles[3].x + j] = '|';
            }
            else if (rooms[3][i][j] == '_') {
                map[level][rectangles[3].y + i][rectangles[3].x + j] = '_';
            }
            else if (rooms[3][i][j] == '.') {
                map[level][rectangles[3].y + i][rectangles[3].x + j] = '.';
            }
            else if (rooms[3][i][j] == ' ') {
                map[level][rectangles[3].y + i][rectangles[3].x + j] = ' '; 
            }
            else if (rooms[3][i][j] == 'o') {
                map[level][rectangles[3].y + i][rectangles[3].x + j] = 'o'; 
            }
        }
    }
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (rooms[4][i][j] == '|') {
                map[level][rectangles[4].y + i][rectangles[4].x + j] = '|';
            }
            else if (rooms[4][i][j] == '_') {
                map[level][rectangles[4].y + i][rectangles[4].x + j] = '_';
            }
            else if (rooms[4][i][j] == '.') {
                map[level][rectangles[4].y + i][rectangles[4].x + j] = '.';
            }
            else if (rooms[4][i][j] == ' ') {
                map[level][rectangles[4].y + i][rectangles[4].x + j] = ' '; 
            }
            else if (rooms[4][i][j] == 'o') {
                map[level][rectangles[4].y + i][rectangles[4].x + j] = 'o'; 
            }
        }
    }
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (rooms[5][i][j] == '|') {
                map[level][rectangles[5].y + i][rectangles[5].x + j] = '|';
            }
            else if (rooms[5][i][j] == '_') {
                map[level][rectangles[5].y + i][rectangles[5].x + j] = '_';
            }
            else if (rooms[5][i][j] == '.') {
                map[level][rectangles[5].y + i][rectangles[5].x + j] = '.';
            }
            else if (rooms[5][i][j] == ' ') {
                map[level][rectangles[5].y + i][rectangles[5].x + j] = ' '; 
            }
            else if (rooms[5][i][j] == 'o') {
                map[level][rectangles[5].y + i][rectangles[5].x + j] = 'o'; 
            }
        }
    }
}
void placing_door() {
    if (rand() % 2) {      
        rectangles[0].door_x = rand() % 4;
        rectangles[0].door_x += rectangles[0].x + 1;
        if (rand() % 2) {
            rectangles[0].door_y = rectangles[0].y;
        }
        else {
            rectangles[0].door_y = rectangles[0].y + 5;
        }
    }
    else {
        rectangles[0].door_y = rand() % 4;
        rectangles[0].door_y += rectangles[0].y + 1;
        if (rand() % 2) {
            rectangles[0].door_x = rectangles[0].x;
        }
        else {
            rectangles[0].door_x = rectangles[0].x + 5;
        }
    }
    if (rand() % 2) {
        rectangles[1].door_x = rand() % 5;
        rectangles[1].door_x += rectangles[1].x + 1;
        if (rand() % 2) {
            rectangles[1].door_y = rectangles[1].y;
        }
        else {
            rectangles[1].door_y = rectangles[1].y + 5;
        }
    }
    else {
        rectangles[1].door_y = rand() % 4;
        rectangles[1].door_y += rectangles[1].y + 1;
        if (rand() % 2) {
            rectangles[1].door_x = rectangles[1].x;
        }
        else {
            rectangles[1].door_x = rectangles[1].x + 6;
        }
    }
    if (rand() % 2) {
        rectangles[2].door_x = rand() % 6;
        rectangles[2].door_x += rectangles[2].x + 1;
        if (rand() % 2) {
            rectangles[2].door_y = rectangles[2].y;
        }
        else {
            rectangles[2].door_y = rectangles[2].y + 5;
        }
    }
    else {
        rectangles[2].door_y = rand() % 4;
        rectangles[2].door_y += rectangles[2].y + 1;
        if (rand() % 2) {
            rectangles[2].door_x = rectangles[2].x;
        }
        else {
            rectangles[2].door_x = rectangles[2].x + 7;
        }
    }
    if (rand() % 2) {
        rectangles[3].door_x = rand() % 5;
        rectangles[3].door_x += rectangles[3].x + 1;
        if (rand() % 2) {
            rectangles[3].door_y = rectangles[3].y;
        }
        else {
            rectangles[3].door_y = rectangles[3].y + 6;
        }
    }
    else {
        rectangles[3].door_y = rand() % 5;
        rectangles[3].door_y += rectangles[3].y + 1;
        if (rand() % 2) {
            rectangles[3].door_x = rectangles[3].x;
        }
        else {
            rectangles[3].door_x = rectangles[3].x + 6;
        }
    }
    if (rand() % 2) {
        rectangles[4].door_x = rand() % 6;
        rectangles[4].door_x += rectangles[4].x + 1;
        if (rand() % 2) {
            rectangles[4].door_y = rectangles[4].y;
        }
        else {
            rectangles[4].door_y = rectangles[4].y + 6;
        }
    }
    else {
        rectangles[4].door_y = rand() % 5;
        rectangles[4].door_y += rectangles[4].y + 1;
        if (rand() % 2) {
            rectangles[4].door_x = rectangles[4].x;
        }
        else {
            rectangles[4].door_x = rectangles[4].x + 7;
        }
    }
    if (rand() % 2) {
        rectangles[5].door_x = rand() % 6;
        rectangles[5].door_x += rectangles[5].x + 1;
        if (rand() % 2) {
            rectangles[5].door_y = rectangles[5].y;
        }
        else {
            rectangles[5].door_y = rectangles[5].y + 7;
        }
    }
    else {
        rectangles[5].door_y = rand() % 6;
        rectangles[5].door_y += rectangles[5].y + 1;
        if (rand() % 2) {
            rectangles[5].door_x = rectangles[5].x;
        }
        else {
            rectangles[5].door_x = rectangles[5].x + 7;
        }
    }
}
void placing_password_door() {
    for (int j=0; j<number_password_doors; j++) {
        int random = rand() % count_land;
        int x = land[random][0];
        int y = land[random][1];
        map[level][x][y] = '@';
        attron(COLOR_PAIR(1));
        // mvaddch(x, y, '@');
        // running_map[level][x][y] = '@';
        attroff(COLOR_PAIR(1));
        for (int i=random; i<count_land-1; i++) {
            land[i][0] = land[i+1][0];
            land[i][1] = land[i+1][1];
        }
        count_land--;
        land[count_land][0] = 0;
        land[count_land][1] = 0;
        if (rand() % 2) {
            while (map[level][x-1][y] != '_' && map[level][x-1][y] != '|' && map[level][x-1][y] != '+') {
                x--;
            }
            while (map[level][x][y-1] != '_' && map[level][x][y-1] != '|' && map[level][x][y-1] != '+') {
                y--;
            }
        }
        else {
            while (map[level][x+1][y] != '_' && map[level][x+1][y] != '|' && map[level][x+1][y] != '+') {
                x++;
            }
            while (map[level][x][y+1] != '_' && map[level][x][y+1] != '|' && map[level][x][y+1] != '+') {
                y++;
            }
        }
        if (map[level][x][y] != '.' && map[level][x][y] != '^' && map[level][x][y] != '?') {
            if (rand() % 2) {
                while (map[level][x-1][y] != '_' && map[level][x-1][y] != '|' && map[level][x-1][y] != '+') {
                    x--;
                }
                while (map[level][x][y+1] != '_' && map[level][x][y+1] != '|' && map[level][x][y+1] != '+') {
                    y++;
                }
            }
            else {
                while (map[level][x+1][y] != '_' && map[level][x+1][y] != '|' && map[level][x+1][y] != '+') {
                    x++;
                }
                while (map[level][x][y-1] != '_' && map[level][x][y-1] != '|' && map[level][x][y-1] != '+') {
                    y--;
                }
            }
        }
        attron(COLOR_PAIR(2));
        // mvaddch(x, y, '&');
        attroff(COLOR_PAIR(2));
        map[level][x][y] = '&';
        // running_map[level][x][y] = '&';
        for (int i=0; i<count_land; i++) {
            if (land[i][0] == x && land[i][1] == y) {
                random = i;
                for (int j=random; j<count_land-1; j++) {
                    land[j][0] = land[j+1][0];
                    land[j][1] = land[j+1][1];
                }
                count_land--;
                land[count_land][0] = 0;
                land[count_land][1] = 0;
                break;
            }
        }            
    }
}
void print_corridor (int x1, int y1, int x2, int y2) {
    int current_x = x1;
    int current_y = y1;
    
    // mvaddch(current_y, current_x, '+');
    map[level][current_y][current_x] = '+';
    // running_map[level][current_y][current_x] = '+';

    while (current_x != x2 || current_y != y2) {
        if (rand() % 2) {
            if (current_x < x2) {
                current_x++;  
            }
            else if (current_x > x2) {
                current_x--;   
            }
        }

        else {
            if (current_y < y2) {
                current_y++;  
            } 
            else if (current_y > y2) {
                current_y--;    
            }
        }

        if (map[level][current_y][current_x] == '|' || map[level][current_y][current_x] == '_') {
            // mvaddch(current_y, current_x, '+');
            map[level][current_y][current_x] = '+';
            // running_map[level][current_y][current_x] = '+';
        }

        if (map[level][current_y][current_x] == ' ') {
            // mvaddch(current_y, current_x, '#');
            map[level][current_y][current_x] = '#';
            // running_map[level][current_y][current_x] = '#';
        }
    }

    if (map[level][current_y][current_x] == '|' || map[level][current_y][current_x] == '_') {
        // mvaddch(current_y, current_x, '+');
        map[level][current_y][current_x] = '+';
        // running_map[level][current_y][current_x] = '+';
    }

    if (map[level][current_y][current_x] == ' ') {
        // mvaddch(current_y, current_x, '#');
        map[level][current_y][current_x] = '#';
        // running_map[level][current_y][current_x] = '#';
    }
}
void placing_in_map(char target, int n, int sign, int color) {
    for (int i=0; i<n; i++){     
        int random = rand() % count_land;
        int x = land[random][0];
        int y = land[random][1];
        fix_monsters_coordinate(target, y, x);
        if(target == '<') {
            staircase_coordinate[level].x = y;
            staircase_coordinate[level].y = x;
        }
        if (sign) {
            attron(COLOR_PAIR(color));
            mvaddch (x, y, target);
            attroff(COLOR_PAIR(color));
            running_map[level][x][y] = target;
        }
        if (target != 'D' && target != 'F' && target != 'G' && target != 'S' && target != 'U') {
            map[level][x][y] = target;
        }
        for (int i=random; i<count_land-1; i++) {
            land[i][0] = land[i+1][0];
            land[i][1] = land[i+1][1];
        }
        count_land--;
        land[count_land][0] = 0;
        land[count_land][1] = 0;
    }
}
void print_menu_margin() {
    for (int i=40; i<80; i++) {
        mvaddch (8, i, '%');
        mvaddch (28, i, '%');
        mvaddch (12, i, '%');
    }
    for (int i=8; i<=28; i++) {
        mvaddch (i, 40, '%');
        mvaddch (i, 80, '%');
    }
}
void print_running_map() {
    clear();
    for (int i=0; i<34; i++) {
        for (int j=0; j<121; j++) {
            if (running_map[level][i][j] == '@') {
                attron(COLOR_PAIR(1));
                mvaddch(i, j, running_map[level][i][j]);
                attroff(COLOR_PAIR(1));
            }
            else if (running_map[level][i][j] == '&') {
                attron(COLOR_PAIR(2));
                mvaddch(i, j, running_map[level][i][j]);
                attroff(COLOR_PAIR(2));
            }
            else if (running_map[level][i][j] == '!') {
                attron(COLOR_PAIR(4));
                mvaddch(i, j, running_map[level][i][j]);
                attroff(COLOR_PAIR(4));
            }
            else {
                mvaddch (i, j, running_map[level][i][j]);
            }
        }
    }
    mvprintw (1, 13, "Health:");
    for (int i=0; i<health; i++) {
        mvaddch(1, 22+i, '*');
    }
    mvprintw (1, 53, "Hunger:");
    mvprintw (1, 82, ",");
    for (int i=0; i<hunger; i++) {
        mvaddch(1, 62+i, 'f');
    }
    mvprintw (1, 95, "Floor:  %d", level);
    if (music_mark) {
        if (music_choice == 1) {
            Mix_HaltMusic();
            Mix_Music *music3 = Mix_LoadMUS("music3.mp3");
            Mix_PlayMusic(music3, -1); 
        }
        else if (music_choice == 2) {
            Mix_HaltMusic();
            Mix_Music *music4 = Mix_LoadMUS("music4.mp3");
            Mix_PlayMusic(music4, -1); 
        }
        else if (music_choice == 3) {
            Mix_HaltMusic();
            Mix_Music *music5 = Mix_LoadMUS("music5.mp3");
            Mix_PlayMusic(music5, -1); 
        }
    }
    else {
        Mix_HaltMusic();
    }
}
void fix_rooms_area() {
    for (int i=0; i<6; i++) {
        rectangles[i].x2 = rectangles[i].x;
        rectangles[i].y2 = rectangles[i].y;
        while (map[level][rectangles[i].y2 + 1][rectangles[i].x2] != ' ' && map[level][rectangles[i].y2 + 1][rectangles[i].x2] != '#') {
            rectangles[i].y2++;
        }
        while (map[level][rectangles[i].y2][rectangles[i].x2 + 1] != ' ' && map[level][rectangles[i].y2][rectangles[i].x2 + 1] != '#') {
            rectangles[i].x2++;
        }
    }
}
void empty_monster_map() {
    for (int i=0; i<34; i++) {
        for (int j=0; j<121; j++) {
            monster_map[level][i][j] = ' ';
        }
    }
}








void movemennt() {
    mvaddch(position_y, position_x, 'H');
    running_map[level][position_y][position_x];
    while(1) {
        if (level == 5 && number_deamon_health <= 0 && number_fire_health <= 0 && number_giant_health <= 0 &&
            number_snake_health <= 0 && number_undeed_health <= 0) {
            win_game();
        }

        char move;
        move = getch();
        move_count++;

        if (move == '8') {
            int x = position_x;
            int y = position_y - 1;
            if (check_and_move(y, x)) {
                position_y--;
            }
        }
        else if (move == '2') {
            int x = position_x;
            int y = position_y + 1;
            if (check_and_move(y, x)) {
                position_y++;
            }
        }
        else if (move == '4') {
            int x = position_x - 1;
            int y = position_y;
            if (check_and_move(y, x)) {
                position_x--;
            }
        }
        else if (move == '6') {
            int x = position_x + 1;
            int y = position_y;
            if (check_and_move(y, x)) {
                position_x++;
            }
        }
        else if (move == '7') {
            int x = position_x - 1;
            int y = position_y - 1;
            if (check_and_move(y, x)) {
                position_x--;
                position_y--;
            }
        }
        else if (move == '9') {
            int x = position_x + 1;
            int y = position_y - 1;
            if (check_and_move(y, x)) {
                position_x++;
                position_y--;
            }
        }
        else if (move == '1') {
            int x = position_x - 1;
            int y = position_y + 1;
            if (check_and_move(y, x)) {
                position_x--;
                position_y++;
            }
        }
        else if (move == '3') {
            int x = position_x + 1;
            int y = position_y + 1;
            if (check_and_move(y, x)) {
                position_x++;
                position_y++;
            }
        }
        else if (move == '5') {
            collect();
        }
        else if (move == 'b') {
            backpack_menu();
        }
        else if (move == 'u') {
            use_menu();
        }
        else if (move == ' ') {
            repeat_shot = 0;
            hit();
        }
        else if (move == 'a') {
            repeat_shot = 1;
            hit();
        }
        else if (move == 'f') {
            char target_move;
            target_move = getch();
            fix_fast_move_to_end(target_move);
        }
        else if (move == 's') {
            show_hidden();
        }
        else if (move == 'm') {
            if (type_of_user) {
                main_menu();
            }
            else {
                main_menu_for_guest();
            }
        }
        else if (move == 't') {
            show_map();
        }
        else if (move == 'w') {
            know_weapon = ' ';
            mvprintw (2, 13, "Your gun was placed in the backpack");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                   ");
        }
        else {
            break;
        }
        check_monster_area();
        fix_filling_life();
        fix_hunger();
        fix_fast_move(move);
        fix_damage();
        fix_change_foods();
        count_move_health_spell--;
        count_move_speed_spell--;
        count_move_damage_spell--;
    }
}
void show_hidden() {
    clear();
    for (int i=0; i<34; i++) {
        for (int j=0; j<121; j++) {
            if (map[level][i][j] == '|' || map[level][i][j] == '_' || map[level][i][j] == '.' ||
                map[level][i][j] == '+' || map[level][i][j] == '%' || map[level][i][j] == ' ' ||
                map[level][i][j] == '^' || map[level][i][j] == '?') {
                mvaddch (i, j, map[level][i][j]);
            }
            else if (map[level][i][j] == '#') {
                mvaddch (i, j, ' ');
            }
            else {
                mvaddch (i, j, '.');
            }
        }
    }
    print_margin();
    while(1) {
        char target;
        target = getch();
        if (target == 's') {
            break;
        }
    }
    print_running_map();
}
void fix_fast_move_to_end(char move) {
    for (int i=0; i<120; i++) {
        if (move == '8') {
            int x = position_x;
            int y = position_y - 1;
            if (check_and_move(y, x)) {
                position_y--;
            }
        }
        else if (move == '2') {
            int x = position_x;
            int y = position_y + 1;
            if (check_and_move(y, x)) {
                position_y++;
            }
        }
        else if (move == '4') {
            int x = position_x - 1;
            int y = position_y;
            if (check_and_move(y, x)) {
                position_x--;
            }
        }
        else if (move == '6') {
            int x = position_x + 1;
            int y = position_y;
            if (check_and_move(y, x)) {
                position_x++;
            }
        }
        else if (move == '7') {
            int x = position_x - 1;
            int y = position_y - 1;
            if (check_and_move(y, x)) {
                position_x--;
                position_y--;
            }
        }
        else if (move == '9') {
            int x = position_x + 1;
            int y = position_y - 1;
            if (check_and_move(y, x)) {
                position_x++;
                position_y--;
            }
        }
        else if (move == '1') {
            int x = position_x - 1;
            int y = position_y + 1;
            if (check_and_move(y, x)) {
                position_x--;
                position_y++;
            }
        }
        else if (move == '3') {
            int x = position_x + 1;
            int y = position_y + 1;
            if (check_and_move(y, x)) {
                position_x++;
                position_y++;
            }
        }
    }
}
void fix_damage() {
    if(count_move_damage_spell > 0) {
        power_mace = 10;
        power_dagger = 24;
        power_magic_wand = 30;
        power_normal_arrow = 10;
        power_sword = 20;
    }
    else {
        power_mace = 5;
        power_dagger = 12;
        power_magic_wand = 15;
        power_normal_arrow = 5;
        power_sword = 10;
    }
}
void fix_fast_move(char move) {
    if(count_move_speed_spell > 0) {
        if (move == '8') {
            int x = position_x;
            int y = position_y - 1;
            if (check_and_move(y, x)) {
                position_y--;
            }
        }
        else if (move == '2') {
            int x = position_x;
            int y = position_y + 1;
            if (check_and_move(y, x)) {
                position_y++;
            }
        }
        else if (move == '4') {
            int x = position_x - 1;
            int y = position_y;
            if (check_and_move(y, x)) {
                position_x--;
            }
        }
        else if (move == '6') {
            int x = position_x + 1;
            int y = position_y;
            if (check_and_move(y, x)) {
                position_x++;
            }
        }
        else if (move == '7') {
            int x = position_x - 1;
            int y = position_y - 1;
            if (check_and_move(y, x)) {
                position_x--;
                position_y--;
            }
        }
        else if (move == '9') {
            int x = position_x + 1;
            int y = position_y - 1;
            if (check_and_move(y, x)) {
                position_x++;
                position_y--;
            }
        }
        else if (move == '1') {
            int x = position_x - 1;
            int y = position_y + 1;
            if (check_and_move(y, x)) {
                position_x--;
                position_y++;
            }
        }
        else if (move == '3') {
            int x = position_x + 1;
            int y = position_y + 1;
            if (check_and_move(y, x)) {
                position_x++;
                position_y++;
            }
        }
    }
}
void fix_filling_life() {
    if (health < 20) {
        if (count_move_health_spell <= 0) {
            if(hunger == 0) {
                health++;
                mvprintw (1, 22, "                  ");
                for (int i=0; i<health; i++) {
                    mvaddch(1, 22+i, '*');
                }
            }
        }
        else {
            health++;
            mvprintw (1, 22, "                  ");
            for (int i=0; i<health; i++) {
                mvaddch(1, 22+i, '*');
            }
            if(hunger == 0) {
                health++;
                mvprintw (1, 22, "                  ");
                for (int i=0; i<health; i++) {
                    mvaddch(1, 22+i, '*');
                }
            }
        }
    }
}
void fix_hunger() {
    if (hunger >= 20) {
        if (move_count % 10 == 0) {
            health--;
            hero_damage();
        }
    }
    else if (move_count % 10 == 0) {
        hunger++;
        for (int i=0; i<hunger; i++) {
            mvaddch(1, 62+i, 'f');
        }
    } 
}
void fix_change_foods() {
    if (move_count % 30 == 0) {
        if (count_normal_food > 0) {
            count_normal_food--;
            count_rotten_food++;
        }
        if (count_magic_food > 0) {
            count_magic_food--;
            count_normal_food++;
        }
        if (count_excellent_food > 0) {
            count_excellent_food--;
            count_normal_food++;
        }
    }
}
int check_and_move(int y, int x) {
    int mark = 0;
    if (map[level][y][x] == '.' || map[level][y][x] == '#' || map[level][y][x] == '+') {
        mark = 1;
        final_move(y, x);
    }
    else if (map[level][y][x] == '<') {
        running_map[level][position_y][position_x] = '.';
        mark = 1;
        staircase();
    }
    else if (map[level][y][x] == '>') {
        low_staircase();
    }
    else if (map[level][y][x] == '^') {
        mark = 1;
        battle_room();
        final_move(y, x);
    }
    else if (map[level][y][x] == '?') {
        mark = 1;
        secret_doors_room();
        final_move(y, x);
    }
    else if (map[level][y][x] == '&') {
        mark = 1;
        give_password();
        final_move(y, x);
    }
    else if (map[level][y][x] == '@') {
        mark = 1;
        opening_door(y, x);
        final_move(y, x);
    }
    else if (map[level][y][x] == '*') {
        mark = 1;
        treasure_room();
    }
    else if(map[level][y][x] == '!' || map[level][y][x] == 's' || map[level][y][x] == 'd' || map[level][y][x] == 'f' ||
            map[level][y][x] == '$' || map[level][y][x] == 'g' || map[level][y][x] == 'r' || map[level][y][x] == 'w' ||
            map[level][y][x] == 'a' || map[level][y][x] == 'l' || map[level][y][x] == 'h' || map[level][y][x] == 'R' ||
            map[level][y][x] == 'W' || map[level][y][x] == 'A' || map[level][y][x] == 'p' || map[level][y][x] == 't' ||
            map[level][y][x] == 'e') {
        mark = 1;
        final_move(y, x);
    }
    return mark;
}
void final_move(int y, int x) {
    show_few_steps();
    attron(COLOR_PAIR(last_color));
    mvaddch (position_y, position_x, last);
    attroff(COLOR_PAIR(last_color));
    running_map[level][position_y][position_x] = last;
    last = map[level][y][x];
    if (last == '&') {
        last_color = 2;
    }
    else if (last == '@') {
        last_color = 1;
    }
    else if (last == '!') {
        last_color = 4;
    }
    else {
        last_color = 0;
    }
    mvaddch (y, x, 'H');
    running_map[level][y][x] = 'H';
}
void collect() {
    if (map[level][position_y][position_x] == '!') {
        master_key(position_y, position_x);
    }

    else if (map[level][position_y][position_x] == 'h') {
        count_health_spell++;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up a health spell");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                            ");
    }

    else if (map[level][position_y][position_x] == 's') {
        count_speed_spell++;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up a speed spell");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                           ");
    }

    else if (map[level][position_y][position_x] == 'd') {
        count_damage_spell++;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up a damage spell");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                            ");
    }

    else if (map[level][position_y][position_x] == 'f') {
        count_normal_food++;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up a normal food");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                           ");
    }

    else if (map[level][position_y][position_x] == '$') {
        count_normal_gold++;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up a gold");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                    ");
    }

    else if (map[level][position_y][position_x] == 'g') {
        count_black_gold++;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up a black gold");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                          ");
    }

    else if (map[level][position_y][position_x] == 'r') {
        count_dagger += 10;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up a dagger pack");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                           ");
    }

    else if (map[level][position_y][position_x] == 'w') {
        count_magic_wand += 8;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up a magic wand pack");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                               ");
    }

    else if (map[level][position_y][position_x] == 'a') {
        count_normal_arrow += 20;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up an arrow pack");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                           ");
    }

    else if (map[level][position_y][position_x] == 'l') {
        count_sword = 1;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up a sword");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                     ");
    }

    else if (map[level][position_y][position_x] == 'R') {
        count_dagger++;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up a thrown dagger");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                             ");
    }

    else if (map[level][position_y][position_x] == 'W') {
        count_magic_wand++;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up a thrown magic wand");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                                 ");
    }

    else if (map[level][position_y][position_x] == 'A') {
        count_normal_arrow++;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up a thrown arrow");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                            ");
    }

    else if (map[level][position_y][position_x] == 'p') {
        count_rotten_food++;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up a rotten food");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                            ");
    }

    else if (map[level][position_y][position_x] == 't') {
        count_excellent_food++;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up an excellent food");
        refresh();
        sleep(1);
        mvprintw (2, 13, "          n                     ");
    }

    else if (map[level][position_y][position_x] == 'e') {
        count_magic_food++;
        free_up(position_y, position_x);
        mvprintw (2, 13, "You picked up a magic food");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                          ");
    }
}
void hit() {
    if (know_weapon == 'm') {
        mace_hit();
    }
    else if (know_weapon == 'r') {
        if(count_dagger <= 0) {
            know_weapon = ' ';
            mvprintw (2, 13, "You have run out of daggers, please change your weapon");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                                      ");
        }
        else {
            dagger_hit();
        }
    }
    else if (know_weapon == 'w') {
        if(count_magic_wand <= 0) {
            know_weapon = ' ';
            mvprintw (2, 13, "You have run out of magic wands, please change your weapon");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                                          ");
        }
        else {
            magic_wand_hit();
        }
    }
    else if (know_weapon == 'a') {
        if(count_normal_arrow <= 0) {
            know_weapon = ' ';
            mvprintw (2, 13, "You have run out of arrows, please change your weapon");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                                     ");
        }
        else {
            normal_arrow_hit();
        }
    }
    else if (know_weapon == 'l') {
        sword_hit();
    }
    else if (know_weapon == ' ') {
        mvprintw (2, 13, "Your hand is empty, please take a gun and shoot");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                                               ");
    }
}
void free_up(int y, int x) {
    map[level][y][x] = '.';
    running_map[level][y][x] = '.';
    last = '.';
    last_color = 0;
}
void show_few_steps() {
    if (map[level][position_y][position_x] == '#') {
        for (int i=1; i<=5; i++) {
            if (map[level][position_y + i][position_x] == '#' || map[level][position_y + i][position_x] == '+') {
                mvaddch (position_y + i, position_x, map[level][position_y + i][position_x]);
                running_map[level][position_y + i][position_x] = map[level][position_y + i][position_x];
            }
            else {
                break;
            }
        }
        for (int i=1; i<=5; i++) {
            if (map[level][position_y - i][position_x] == '#' || map[level][position_y - i][position_x] == '+') {
                mvaddch (position_y - i, position_x, map[level][position_y - i][position_x]);
                running_map[level][position_y - i][position_x] = map[level][position_y - i][position_x];
            }
            else {
                break;
            }
        }
        for (int i=1; i<=5; i++) {
            if (map[level][position_y][position_x + i] == '#' || map[level][position_y][position_x + i] == '+') {
                mvaddch (position_y, position_x + i, map[level][position_y][position_x + i]);
                running_map[level][position_y][position_x + i] = map[level][position_y][position_x + i];
            }
            else {
                break;
            }
        }
        for (int i=1; i<=5; i++) {
            if (map[level][position_y][position_x - i] == '#' || map[level][position_y][position_x - i] == '+') {
                mvaddch (position_y, position_x - i, map[level][position_y][position_x - i]);
                running_map[level][position_y][position_x - i] = map[level][position_y][position_x - i];
            }
            else {
                break;
            }
        }
        for (int i=1; i<=5; i++) {
            if (map[level][position_y + i][position_x + i] == '#' || map[level][position_y + i][position_x + i] == '+') {
                mvaddch (position_y + i, position_x + i, map[level][position_y + i][position_x + i]);
                running_map[level][position_y + i][position_x + i] = map[level][position_y + i][position_x + i];
            }
            else {
                break;
            }
        }
        for (int i=1; i<=5; i++) {
            if (map[level][position_y - i][position_x + i] == '#' || map[level][position_y - i][position_x + i] == '+') {
                mvaddch (position_y - i, position_x + i, map[level][position_y - i][position_x + i]);
                running_map[level][position_y - i][position_x + i] = map[level][position_y - i][position_x + i];
            }
            else {
                break;
            }
        }
        for (int i=1; i<=5; i++) {
            if (map[level][position_y + i][position_x - i] == '#' || map[level][position_y + i][position_x - i] == '+') {
                mvaddch (position_y + i, position_x - i, map[level][position_y + i][position_x - i]);
                running_map[level][position_y + i][position_x - i] = map[level][position_y + i][position_x - i];
            }
            else {
                break;
            }
        }
        for (int i=1; i<=5; i++) {
            if (map[level][position_y - i][position_x - i] == '#' || map[level][position_y - i][position_x - i] == '+') {
                mvaddch (position_y - i, position_x - i, map[level][position_y - i][position_x - i]);
                running_map[level][position_y - i][position_x - i] = map[level][position_y - i][position_x - i];
            }
            else {
                break;
            }
        }
    }

    else {
        show_rooms();
    }
    
}
void show_rooms() {
    for (int i=0; i<6; i++) {
        if (position_x >= rectangles[i].x && position_x <= rectangles[i].x2 &&
            position_y >= rectangles[i].y && position_y <= rectangles[i].y2) {
            print_desired_room(i);
            break;
        }
    }
} 
void print_desired_room(int target) {
    int color = 0;
    for (int i=rectangles[target].y; i<=rectangles[target].y2; i++) {
        for (int j=rectangles[target].x; j<=rectangles[target].x2; j++) {
            if (map[level][i][j] == '@') {
                color = 1;
                attron(COLOR_PAIR(color));
                mvaddch (i, j, map[level][i][j]);
                attroff(COLOR_PAIR(color));
                running_map[level][i][j] = map[level][i][j];
            }
            else if (map[level][i][j] == '&') {
                color = 2;
                attron(COLOR_PAIR(color));
                mvaddch (i, j, map[level][i][j]);
                attroff(COLOR_PAIR(color));
                running_map[level][i][j] = map[level][i][j];
            }
            else if (map[level][i][j] == '!') {
                color = 4;
                attron(COLOR_PAIR(color));
                mvaddch (i, j, map[level][i][j]);
                attroff(COLOR_PAIR(color));
                running_map[level][i][j] = map[level][i][j];
            }
            else if (map[level][i][j] == '^' || map[level][i][j] == '?') {
                mvaddch (i, j, '.');
                color = 0;
                running_map[level][i][j] = '.';
            }
            else if (map[level][i][j] == 'p') {
                mvaddch (i, j, 'f');
                color = 0;
                running_map[level][i][j] = 'f';
            }
            else {
                color = 0;
                attron(COLOR_PAIR(color));
                mvaddch (i, j, map[level][i][j]);
                attroff(COLOR_PAIR(color));
                running_map[level][i][j] = map[level][i][j];
            }
            if (monster_map[level][i][j] != ' ') {
                mvaddch (i, j, monster_map[level][i][j]);
                running_map[level][i][j] = monster_map[level][i][j];
            }
        }
    }
}
void show_map() {
    clear();
    print_margin();
    for (int i=4; i<34; i++) {
        for (int j=0; j<121; j++) {
            if (map[level][i][j] == '^' || map[level][i][j] == '?') {
                mvaddch (i, j, '.');
            }
            else if (map[level][i][j] == '@') {
                attron (COLOR_PAIR(1));
                mvaddch (i, j, map[level][i][j]);
                attroff (COLOR_PAIR(1));
            }
            else if (map[level][i][j] == '&') {
                attron (COLOR_PAIR(2));
                mvaddch (i, j, map[level][i][j]);
                attroff (COLOR_PAIR(2));
            }
            else if (map[level][i][j] == '!') {
                attron (COLOR_PAIR(4));
                mvaddch (i, j, map[level][i][j]);
                attroff (COLOR_PAIR(4));
            }
            else {
                mvaddch (i, j, map[level][i][j]);
            }
        }
    }

    while(1) {
        char x;
        x = getch();
        if (x == 't') {
            break;
        }
    }

    clear();
    print_running_map();
}
 











void fix_monsters_coordinate(char target, int x, int y) {
    if (target == 'D') {
        deamon_coordinate[level].x = x;
        deamon_coordinate[level].y = y;
    }
    else if (target == 'F') {
        fire_coordinate[level].x = x;
        fire_coordinate[level].y = y;
    }
    else if (target == 'G') {
        giant_coordinate[level].x = x;
        giant_coordinate[level].y = y;
    }
    else if (target == 'S') {
        snake_coordinate[level].x = x;
        snake_coordinate[level].y = y;
    }
    else if (target == 'U') {
        undeed_coordinate[level].x = x;
        undeed_coordinate[level].y = y;
    }
}
void deamon_death() {
    mvaddch (deamon_coordinate[level].y, deamon_coordinate[level].x, '.');
    running_map[level][deamon_coordinate[level].y][deamon_coordinate[level].x] = '.';
    monster_map[level][deamon_coordinate[level].y][deamon_coordinate[level].x] = ' ';
    mvprintw (2, 13, "You shot the Deamon and it died");
    refresh();
    sleep(1);
    mvprintw (2, 13, "                               ");
    deamon_coordinate[level].x = -1;
    deamon_coordinate[level].y = -1;
    deamon_coordinate[level].area_x1 = -1;
    deamon_coordinate[level].area_x2 = -1;
    deamon_coordinate[level].area_y1 = -1;
    deamon_coordinate[level].area_y2 = -1;
}
void fire_death() {
    mvaddch (fire_coordinate[level].y, fire_coordinate[level].x, '.');
    running_map[level][fire_coordinate[level].y][fire_coordinate[level].x] = '.';
    monster_map[level][fire_coordinate[level].y][fire_coordinate[level].x] = ' ';
    mvprintw (2, 13, "You shot the Fire Breathing Monster and it died");
    refresh();
    sleep(1);
    mvprintw (2, 13, "                                                ");
    fire_coordinate[level].x = -1;
    fire_coordinate[level].y = -1;
    fire_coordinate[level].area_x1 = -1;
    fire_coordinate[level].area_x2 = -1;
    fire_coordinate[level].area_y1 = -1;
    fire_coordinate[level].area_y2 = -1;
}
void giant_death() {
    mvaddch (giant_coordinate[level].y, giant_coordinate[level].x, '.');
    running_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = '.';
    monster_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = ' ';
    mvprintw (2, 13, "You shot the Giant and it died");
    refresh();
    sleep(1);
    mvprintw (2, 13, "                              ");
    giant_coordinate[level].x = -1;
    giant_coordinate[level].y = -1;
    giant_coordinate[level].area_x1 = -1;
    giant_coordinate[level].area_x2 = -1;
    giant_coordinate[level].area_y1 = -1;
    giant_coordinate[level].area_y2 = -1;
}
void snake_death() {
    mvaddch (snake_coordinate[level].y, snake_coordinate[level].x, '.');
    running_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = '.';
    monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = ' ';
    mvprintw (2, 13, "You shot the Snake and it died");
    refresh();
    sleep(1);
    mvprintw (2, 13, "                               ");
    snake_coordinate[level].x = -1;
    snake_coordinate[level].y = -1;
    snake_coordinate[level].area_x1 = -1;
    snake_coordinate[level].area_x2 = -1;
    snake_coordinate[level].area_y1 = -1;
    snake_coordinate[level].area_y2 = -1;
}
void undeed_death() {
    mvaddch (undeed_coordinate[level].y, undeed_coordinate[level].x, '.');
    running_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = '.';
    monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = ' ';
    mvprintw (2, 13, "You shot the Undeed and it died");
    refresh();
    sleep(1);
    mvprintw (2, 13, "                               ");
    undeed_coordinate[level].x = -1;
    undeed_coordinate[level].y = -1;
    undeed_coordinate[level].area_x1 = -1;
    undeed_coordinate[level].area_x2 = -1;
    undeed_coordinate[level].area_y1 = -1;
    undeed_coordinate[level].area_y2 = -1;
}
void deamo_damage() {
    mvprintw (2, 13, "You shot the Deamon. Deamon health: %d out of 5", number_deamon_health);
    refresh();
    sleep(1);
    mvprintw (2, 13, "                                               ");
}
void fire_damage() {
    mvprintw (2, 13, "You shot the Fire Breathing Monster. Fire Breathing Monster health: %d out of 10", number_fire_health);
    refresh();
    sleep(1);
    mvprintw (2, 13, "                                                                                ");
}
void giant_damage() {
    mvprintw (2, 13, "You shot the Giant. Giant health: %d out of 15", number_giant_health);
    refresh();
    sleep(1);
    mvprintw (2, 13, "                                              ");
}
void snake_damage() {
    mvprintw (2, 13, "You shot the Snake. Snake health: %d out of 20", number_snake_health);
    refresh();
    sleep(1);
    mvprintw (2, 13, "                                              ");
}
void undeed_damage() {
    mvprintw (2, 13, "You shot the Undeed. Undeed health: %d out of 30", number_undeed_health);
    refresh();
    sleep(1);
    mvprintw (2, 13, "                                                ");
}
void hero_damage() {
    if (health > 0) {
        mvprintw (1, 20, "                              ");
        for (int i=0; i<health; i++) {
            mvaddch(1, 22+i, '*');
        }
    }
    else {
        lost_game();
    }
}
void mace_hit() {
    if ((position_x == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) ||
        (position_x - 1 == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) ||
        (position_x + 1 == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) ||
        (position_x == deamon_coordinate[level].x && position_y + 1 == deamon_coordinate[level].y) ||
        (position_x == deamon_coordinate[level].x && position_y - 1 == deamon_coordinate[level].y) ||
        (position_x - 1 == deamon_coordinate[level].x && position_y - 1 == deamon_coordinate[level].y) ||
        (position_x - 1 == deamon_coordinate[level].x && position_y + 1 == deamon_coordinate[level].y) ||
        (position_x + 1 == deamon_coordinate[level].x && position_y + 1== deamon_coordinate[level].y)) {
        number_deamon_health -= power_mace;
        if (number_deamon_health > 0) {
            deamo_damage();
        }
        else {
            deamon_death();
        }
    }
    else if ((position_x == fire_coordinate[level].x && position_y == fire_coordinate[level].y) ||
        (position_x - 1 == fire_coordinate[level].x && position_y == fire_coordinate[level].y) ||
        (position_x + 1 == fire_coordinate[level].x && position_y == fire_coordinate[level].y) ||
        (position_x == fire_coordinate[level].x && position_y + 1 == fire_coordinate[level].y) ||
        (position_x == fire_coordinate[level].x && position_y - 1 == fire_coordinate[level].y) ||
        (position_x - 1 == fire_coordinate[level].x && position_y - 1 == fire_coordinate[level].y) ||
        (position_x - 1 == fire_coordinate[level].x && position_y + 1 == fire_coordinate[level].y) ||
        (position_x + 1 == fire_coordinate[level].x && position_y + 1== fire_coordinate[level].y)) {
        number_fire_health -= power_mace;
        if (number_fire_health > 0) {
            fire_damage();
        }
        else {
            fire_death();
        }
    }
    else if ((position_x == giant_coordinate[level].x && position_y == giant_coordinate[level].y) ||
        (position_x - 1 == giant_coordinate[level].x && position_y == giant_coordinate[level].y) ||
        (position_x + 1 == giant_coordinate[level].x && position_y == giant_coordinate[level].y) ||
        (position_x == giant_coordinate[level].x && position_y + 1 == giant_coordinate[level].y) ||
        (position_x == giant_coordinate[level].x && position_y - 1 == giant_coordinate[level].y) ||
        (position_x - 1 == giant_coordinate[level].x && position_y - 1 == giant_coordinate[level].y) ||
        (position_x - 1 == giant_coordinate[level].x && position_y + 1 == giant_coordinate[level].y) ||
        (position_x + 1 == giant_coordinate[level].x && position_y + 1== giant_coordinate[level].y)) {
        number_giant_health -= power_mace;
        if (number_giant_health > 0) {
            giant_damage();
        }
        else {
            giant_death();
        }
    }
    else if ((position_x == snake_coordinate[level].x && position_y == snake_coordinate[level].y) ||
        (position_x - 1 == snake_coordinate[level].x && position_y == snake_coordinate[level].y) ||
        (position_x + 1 == snake_coordinate[level].x && position_y == snake_coordinate[level].y) ||
        (position_x == snake_coordinate[level].x && position_y + 1 == snake_coordinate[level].y) ||
        (position_x == snake_coordinate[level].x && position_y - 1 == snake_coordinate[level].y) ||
        (position_x - 1 == snake_coordinate[level].x && position_y - 1 == snake_coordinate[level].y) ||
        (position_x - 1 == snake_coordinate[level].x && position_y + 1 == snake_coordinate[level].y) ||
        (position_x + 1 == snake_coordinate[level].x && position_y + 1== snake_coordinate[level].y)) {
        number_snake_health -= power_mace;
        if (number_snake_health > 0) {
            snake_damage();
        }
        else {
            snake_death();
        }
    }
    else if ((position_x == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) ||
        (position_x - 1 == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) ||
        (position_x + 1 == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) ||
        (position_x == undeed_coordinate[level].x && position_y + 1 == undeed_coordinate[level].y) ||
        (position_x == undeed_coordinate[level].x && position_y - 1 == undeed_coordinate[level].y) ||
        (position_x - 1 == undeed_coordinate[level].x && position_y - 1 == undeed_coordinate[level].y) ||
        (position_x - 1 == undeed_coordinate[level].x && position_y + 1 == undeed_coordinate[level].y) ||
        (position_x + 1 == undeed_coordinate[level].x && position_y + 1== undeed_coordinate[level].y)) {
        number_undeed_health -= power_mace;
        if (number_undeed_health > 0) {
            undeed_damage();
        }
        else {
            undeed_death();
        }
    }
}
void dagger_hit() {
    int mark = 0;
    if (!repeat_shot) {
        direction = getch();
    }
    if (position_x == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) {
        number_deamon_health -= power_dagger;
        count_dagger--;
        if (number_deamon_health > 0) {
            deamo_damage();
        }
        else {
            deamon_death();
        }
    }
    else if (position_x == fire_coordinate[level].x && position_y == fire_coordinate[level].y) {
        number_fire_health -= power_dagger;
        count_dagger--;
        if (number_fire_health > 0) {
            fire_damage();
        }
        else {
            fire_death();
        }
    }
    else if (position_x == giant_coordinate[level].x && position_y == giant_coordinate[level].y) {
        number_giant_health -= power_dagger;
        count_dagger--;
        if (number_giant_health > 0) {
            giant_damage();
        }
        else {
            giant_death();
        }
    }
    else if (position_x == snake_coordinate[level].x && position_y == snake_coordinate[level].y) {
        number_snake_health -= power_dagger;
        count_dagger--;
        if (number_snake_health > 0) {
            snake_damage();
        }
        else {
            snake_death();
        }
    }
    else if (position_x == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) {
        number_undeed_health -= power_dagger;
        count_dagger--;
        if (number_undeed_health > 0) {
            undeed_damage();
        }
        else {
            undeed_death();
        }
    }
    else if (direction == '8') {
        mark = 0;
        for (int i=1; i<=5; i++) {
            if(position_x == deamon_coordinate[level].x && position_y - i == deamon_coordinate[level].y) {
                number_deamon_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_deamon_health > 0) {
                    deamo_damage();
                }
                else {
                    deamon_death();
                }
                break;
            }
            else if(position_x == fire_coordinate[level].x && position_y - i == fire_coordinate[level].y) {
                number_fire_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_fire_health > 0) {
                    fire_damage();
                }
                else {
                    fire_death();
                }
                break;
            }
            else if(position_x == giant_coordinate[level].x && position_y - i == giant_coordinate[level].y) {
                number_giant_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_giant_health > 0) {
                    giant_damage();
                }
                else {
                    giant_death();
                }
                break;
            }
            else if(position_x == snake_coordinate[level].x && position_y - i == snake_coordinate[level].y) {
                number_snake_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_snake_health > 0) {
                    snake_damage();
                }
                else {
                    snake_death();
                }
                break;
            }
            else if(position_x == undeed_coordinate[level].x && position_y - i == undeed_coordinate[level].y) {
                number_undeed_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_undeed_health > 0) {
                    undeed_damage();
                }
                else {
                    undeed_death();
                }
                break;
            }
            else if (map[level][position_y-i][position_x] == '|' || map[level][position_y-i][position_x] == '_' ||
                     map[level][position_y-i][position_x] == '+') {
                map[level][position_y-i+1][position_x] = 'R';
                mvaddch(position_y-i+1, position_x, 'R');
                running_map[level][position_y-i+1][position_x] = 'R';
                count_dagger--;
                mark = 1;
                break;
            }
        }
        if(!mark) {
            map[level][position_y-5][position_x] = 'R';
            mvaddch(position_y-5, position_x, 'R');
            running_map[level][position_y-5][position_x] = 'R';
        }
        refresh();
    }
    else if (direction == '2') {
        for (int i=1; i<=5; i++) {
            if(position_x == deamon_coordinate[level].x && position_y + i == deamon_coordinate[level].y) {
                number_deamon_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_deamon_health > 0) {
                    deamo_damage();
                }
                else {
                    deamon_death();
                }
                break;
            }
            else if(position_x == fire_coordinate[level].x && position_y + i == fire_coordinate[level].y) {
                number_fire_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_fire_health > 0) {
                    fire_damage();
                }
                else {
                    fire_death();
                }
                break;
            }
            else if(position_x == giant_coordinate[level].x && position_y + i == giant_coordinate[level].y) {
                number_giant_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_giant_health > 0) {
                    giant_damage();
                }
                else {
                    giant_death();
                }
                break;
            }
            else if(position_x == snake_coordinate[level].x && position_y + i == snake_coordinate[level].y) {
                number_snake_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_snake_health > 0) {
                    snake_damage();
                }
                else {
                    snake_death();
                }
                break;
            }
            else if(position_x == undeed_coordinate[level].x && position_y + i == undeed_coordinate[level].y) {
                number_undeed_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_undeed_health > 0) {
                    undeed_damage();
                }
                else {
                    undeed_death();
                }
                break;
            }
            else if (map[level][position_y+i][position_x] == '|' || map[level][position_y+i][position_x] == '_' ||
                     map[level][position_y+i][position_x] == '+') {
                map[level][position_y+i-1][position_x] = 'R';
                mvaddch(position_y+i-1, position_x, 'R');
                running_map[level][position_y+i-1][position_x] = 'R';
                count_dagger--;
                mark = 1;
                break;
            }
        }
        if(!mark) {
            map[level][position_y+5][position_x] = 'R';
            mvaddch(position_y+5, position_x, 'R');
            running_map[level][position_y+5][position_x] = 'R';
        }
        refresh();
    }
    else if (direction == '4') {
        for (int i=1; i<=5; i++) {
            if(position_x - i == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) {
                number_deamon_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_deamon_health > 0) {
                    deamo_damage();
                }
                else {
                    deamon_death();
                }
                break;
            }
            else if(position_x - i == fire_coordinate[level].x && position_y == fire_coordinate[level].y) {
                number_fire_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_fire_health > 0) {
                    fire_damage();
                }
                else {
                    fire_death();
                }
                break;
            }
            else if(position_x - i == giant_coordinate[level].x && position_y == giant_coordinate[level].y) {
                number_giant_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_giant_health > 0) {
                    giant_damage();
                }
                else {
                    giant_death();
                }
                break;
            }
            else if(position_x - i == snake_coordinate[level].x && position_y == snake_coordinate[level].y) {
                number_snake_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_snake_health > 0) {
                    snake_damage();
                }
                else {
                    snake_death();
                }
                break;
            }
            else if(position_x - i == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) {
                number_undeed_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_undeed_health > 0) {
                    undeed_damage();
                }
                else {
                    undeed_death();
                }
                break;
            }
            else if (map[level][position_y][position_x-i] == '|' || map[level][position_y][position_x-i] == '_' ||
                     map[level][position_y][position_x-i] == '+') {
                map[level][position_y][position_x-i+1] = 'R';
                mvaddch(position_y, position_x-i+1, 'R');
                running_map[level][position_y][position_x-i+1] = 'R';
                count_dagger--;
                mark = 1;
                break;
            }
        }
        if(!mark) {
            map[level][position_y][position_x-5] = 'R';
            mvaddch(position_y, position_x-5, 'R');
            running_map[level][position_y][position_x-5] = 'R';
        }
        refresh();
    }
    else if (direction == '6') {
        for (int i=1; i<=5; i++) {
            if(position_x + i == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) {
                number_deamon_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_deamon_health > 0) {
                    deamo_damage();
                }
                else {
                    deamon_death();
                }
                break;
            }
            else if(position_x + i == fire_coordinate[level].x && position_y == fire_coordinate[level].y) {
                number_fire_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_fire_health > 0) {
                    fire_damage();
                }
                else {
                    fire_death();
                }
                break;
            }
            else if(position_x + i == giant_coordinate[level].x && position_y == giant_coordinate[level].y) {
                number_giant_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_giant_health > 0) {
                    giant_damage();
                }
                else {
                    giant_death();
                }
                break;
            }
            else if(position_x + i == snake_coordinate[level].x && position_y == snake_coordinate[level].y) {
                number_snake_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_snake_health > 0) {
                    snake_damage();
                }
                else {
                    snake_death();
                }
                break;
            }
            else if(position_x + i == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) {
                number_undeed_health -= power_dagger;
                count_dagger--;
                mark = 1;
                if (number_undeed_health > 0) {
                    undeed_damage();
                }
                else {
                    undeed_death();
                }
                break;
            }
            else if (map[level][position_y][position_x+i] == '|' || map[level][position_y][position_x+i] == '_' ||
                     map[level][position_y][position_x+i] == '+') {
                map[level][position_y][position_x+i-1] = 'R';
                mvaddch(position_y, position_x+i-1, 'R');
                running_map[level][position_y][position_x+i-1] = 'R';
                count_dagger--;
                mark = 1;
                break;
            }
        }
        if(!mark) {
            map[level][position_y][position_x+5] = 'R';
            mvaddch(position_y, position_x+5, 'R');
            running_map[level][position_y][position_x+5] = 'R';
        }
        refresh();
    }
}
void magic_wand_hit() {
    int mark = 0;
    if (!repeat_shot) {
        direction = getch();
    }
    if (position_x == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) {
        number_deamon_health -= power_magic_wand;
        count_magic_wand--;
        if (number_deamon_health > 0) {
            deamo_damage();
        }
        else {
            deamon_death();
        }
    }
    else if (position_x == fire_coordinate[level].x && position_y == fire_coordinate[level].y) {
        number_fire_health -= power_magic_wand;
        count_magic_wand--;
        if (number_fire_health > 0) {
            fire_damage();
        }
        else {
            fire_death();
        }
    }
    else if (position_x == giant_coordinate[level].x && position_y == giant_coordinate[level].y) {
        number_giant_health -= power_magic_wand;
        count_magic_wand--;
        number_giant_move = 0;
        if (number_giant_health > 0) {
            giant_damage();
        }
        else {
            giant_death();
        }
    }
    else if (position_x == snake_coordinate[level].x && position_y == snake_coordinate[level].y) {
        number_snake_health -= power_magic_wand;
        count_magic_wand--;
        number_snake_move = 0;
        if (number_snake_health > 0) {
            snake_damage();
        }
        else {
            snake_death();
        }
    }
    else if (position_x == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) {
        number_undeed_health -= power_magic_wand;
        count_magic_wand--;
        number_undeed_move = 0;
        if (number_undeed_health > 0) {
            undeed_damage();
        }
        else {
            undeed_death();
        }
    }
    else if (direction == '8') {
        mark = 0;
        for (int i=1; i<=10; i++) {
            if(position_x == deamon_coordinate[level].x && position_y - i == deamon_coordinate[level].y) {
                number_deamon_health -= power_magic_wand;
                count_magic_wand--;
                number_giant_move = 0;
                mark = 1;
                if (number_deamon_health > 0) {
                    deamo_damage();
                }
                else {
                    deamon_death();
                }
                break;
            }
            else if(position_x == fire_coordinate[level].x && position_y - i == fire_coordinate[level].y) {
                number_fire_health -= power_magic_wand;
                count_magic_wand--;
                mark = 1;
                if (number_fire_health > 0) {
                    fire_damage();
                }
                else {
                    fire_death();
                }
                break;
            }
            else if(position_x == giant_coordinate[level].x && position_y - i == giant_coordinate[level].y) {
                number_giant_health -= power_magic_wand;
                count_magic_wand--;
                mark = 1;
                if (number_giant_health > 0) {
                    giant_damage();
                }
                else {
                    giant_death();
                }
                break;
            }
            else if(position_x == snake_coordinate[level].x && position_y - i == snake_coordinate[level].y) {
                number_snake_health -= power_magic_wand;
                count_magic_wand--;
                number_snake_move = 0;
                mark = 1;
                if (number_snake_health > 0) {
                    snake_damage();
                }
                else {
                    snake_death();
                }
                break;
            }
            else if(position_x == undeed_coordinate[level].x && position_y - i == undeed_coordinate[level].y) {
                number_undeed_health -= power_magic_wand;
                count_magic_wand--;
                number_undeed_move = 0;
                mark = 1;
                if (number_undeed_health > 0) {
                    undeed_damage();
                }
                else {
                    undeed_death();
                }
                break;
            }
            else if (map[level][position_y-i][position_x] == '|' || map[level][position_y-i][position_x] == '_' ||
                     map[level][position_y-i][position_x] == '+') {
                map[level][position_y-i+1][position_x] = 'W';
                mvaddch(position_y-i+1, position_x, 'W');
                running_map[level][position_y-i+1][position_x] = 'W';
                count_magic_wand--;
                mark = 1;
                break;
            }
        }
        if(!mark) {
            map[level][position_y-5][position_x] = 'W';
            mvaddch(position_y-5, position_x, 'W');
            running_map[level][position_y-5][position_x] = 'W';
        }
        refresh();
    }
    else if (direction == '2') {
        for (int i=1; i<=10; i++) {
            if(position_x == deamon_coordinate[level].x && position_y + i == deamon_coordinate[level].y) {
                number_deamon_health -= power_magic_wand;
                count_magic_wand--;
                mark = 1;
                if (number_deamon_health > 0) {
                    deamo_damage();
                }
                else {
                    deamon_death();
                }
                break;
            }
            else if(position_x == fire_coordinate[level].x && position_y + i == fire_coordinate[level].y) {
                number_fire_health -= power_magic_wand;
                count_magic_wand--;
                mark = 1;
                if (number_fire_health > 0) {
                    fire_damage();
                }
                else {
                    fire_death();
                }
                break;
            }
            else if(position_x == giant_coordinate[level].x && position_y + i == giant_coordinate[level].y) {
                number_giant_health -= power_magic_wand;
                count_magic_wand--;
                number_giant_move = 0;
                mark = 1;
                if (number_giant_health > 0) {
                    giant_damage();
                }
                else {
                    giant_death();
                }
                break;
            }
            else if(position_x == snake_coordinate[level].x && position_y + i == snake_coordinate[level].y) {
                number_snake_health -= power_magic_wand;
                count_magic_wand--;
                number_snake_move = 0;
                mark = 1;
                if (number_snake_health > 0) {
                    snake_damage();
                }
                else {
                    snake_death();
                }
                break;
            }
            else if(position_x == undeed_coordinate[level].x && position_y + i == undeed_coordinate[level].y) {
                number_undeed_health -= power_magic_wand;
                count_magic_wand--;
                number_undeed_move = 0;
                mark = 1;
                if (number_undeed_health > 0) {
                    undeed_damage();
                }
                else {
                    undeed_death();
                }
                break;
            }
            else if (map[level][position_y+i][position_x] == '|' || map[level][position_y+i][position_x] == '_' ||
                     map[level][position_y+i][position_x] == '+') {
                map[level][position_y+i-1][position_x] = 'W';
                mvaddch(position_y+i-1, position_x, 'W');
                running_map[level][position_y+i-1][position_x] = 'W';
                count_magic_wand--;
                mark = 1;
                break;
            }
        }
        if(!mark) {
            map[level][position_y+5][position_x] = 'W';
            mvaddch(position_y+5, position_x, 'W');
            running_map[level][position_y+5][position_x] = 'W';
        }
        refresh();
    }
    else if (direction == '4') {
        for (int i=1; i<=10; i++) {
            if(position_x - i == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) {
                number_deamon_health -= power_magic_wand;
                count_magic_wand--;
                mark = 1;
                if (number_deamon_health > 0) {
                    deamo_damage();
                }
                else {
                    deamon_death();
                }
                break;
            }
            else if(position_x - i == fire_coordinate[level].x && position_y == fire_coordinate[level].y) {
                number_fire_health -= power_magic_wand;
                count_magic_wand--;
                mark = 1;
                if (number_fire_health > 0) {
                    fire_damage();
                }
                else {
                    fire_death();
                }
                break;
            }
            else if(position_x - i == giant_coordinate[level].x && position_y == giant_coordinate[level].y) {
                number_giant_health -= power_magic_wand;
                count_magic_wand--;
                number_giant_move = 0;
                mark = 1;
                if (number_giant_health > 0) {
                    giant_damage();
                }
                else {
                    giant_death();
                }
                break;
            }
            else if(position_x - i == snake_coordinate[level].x && position_y == snake_coordinate[level].y) {
                number_snake_health -= power_magic_wand;
                count_magic_wand--;
                number_snake_move = 0;
                mark = 1;
                if (number_snake_health > 0) {
                    snake_damage();
                }
                else {
                    snake_death();
                }
                break;
            }
            else if(position_x - i == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) {
                number_undeed_health -= power_magic_wand;
                count_magic_wand--;
                number_undeed_move = 0;
                mark = 1;
                if (number_undeed_health > 0) {
                    undeed_damage();
                }
                else {
                    undeed_death();
                }
                break;
            }
            else if (map[level][position_y][position_x-i] == '|' || map[level][position_y][position_x-i] == '_' ||
                     map[level][position_y][position_x-i] == '+') {
                map[level][position_y][position_x-i+1] = 'W';
                mvaddch(position_y, position_x-i+1, 'W');
                running_map[level][position_y][position_x-i+1] = 'W';
                count_magic_wand--;
                mark = 1;
                break;
            }
        }
        if(!mark) {
            map[level][position_y][position_x-5] = 'W';
            mvaddch(position_y, position_x-5, 'W');
            running_map[level][position_y][position_x-5] = 'W';
        }
        refresh();
    }
    else if (direction == '6') {
        for (int i=1; i<=10; i++) {
            if(position_x + i == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) {
                number_deamon_health -= power_magic_wand;
                count_magic_wand--;
                mark = 1;
                if (number_deamon_health > 0) {
                    deamo_damage();
                }
                else {
                    deamon_death();
                }
                break;
            }
            else if(position_x + i == fire_coordinate[level].x && position_y == fire_coordinate[level].y) {
                number_fire_health -= power_magic_wand;
                count_magic_wand--;
                mark = 1;
                if (number_fire_health > 0) {
                    fire_damage();
                }
                else {
                    fire_death();
                }
                break;
            }
            else if(position_x + i == giant_coordinate[level].x && position_y == giant_coordinate[level].y) {
                number_giant_health -= power_magic_wand;
                count_magic_wand--;
                number_giant_move = 0;
                mark = 1;
                if (number_giant_health > 0) {
                    giant_damage();
                }
                else {
                    giant_death();
                }
                break;
            }
            else if(position_x + i == snake_coordinate[level].x && position_y == snake_coordinate[level].y) {
                number_snake_health -= power_magic_wand;
                count_magic_wand--;
                number_snake_move = 0;
                mark = 1;
                if (number_snake_health > 0) {
                    snake_damage();
                }
                else {
                    snake_death();
                }
                break;
            }
            else if(position_x + i == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) {
                number_undeed_health -= power_magic_wand;
                count_magic_wand--;
                number_undeed_move = 0;
                mark = 1;
                if (number_undeed_health > 0) {
                    undeed_damage();
                }
                else {
                    undeed_death();
                }
                break;
            }
            else if (map[level][position_y][position_x+i] == '|' || map[level][position_y][position_x+i] == '_' ||
                     map[level][position_y][position_x+i] == '+') {
                map[level][position_y][position_x+i-1] = 'W';
                mvaddch(position_y, position_x+i-1, 'W');
                running_map[level][position_y][position_x+i-1] = 'W';
                count_magic_wand--;
                mark = 1;
                break;
            }
        }
        if(!mark) {
            map[level][position_y][position_x+5] = 'W';
            mvaddch(position_y, position_x+5, 'W');
            running_map[level][position_y][position_x+5] = 'W';
        }
        refresh();
    }
}
void normal_arrow_hit() {
    int mark = 0;
    if (repeat_shot == 0) {
        direction = getch();
    }
    if (position_x == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) {
        number_deamon_health -= power_normal_arrow;
        count_normal_arrow--;
        if (number_deamon_health > 0) {
            deamo_damage();
        }
        else {
            deamon_death();
        }
    }
    else if (position_x == fire_coordinate[level].x && position_y == fire_coordinate[level].y) {
        number_fire_health -= power_normal_arrow;
        count_normal_arrow--;
        if (number_fire_health > 0) {
            fire_damage();
        }
        else {
            fire_death();
        }
    }
    else if (position_x == giant_coordinate[level].x && position_y == giant_coordinate[level].y) {
        number_giant_health -= power_normal_arrow;
        count_normal_arrow--;
        if (number_giant_health > 0) {
            giant_damage();
        }
        else {
            giant_death();
        }
    }
    else if (position_x == snake_coordinate[level].x && position_y == snake_coordinate[level].y) {
        number_snake_health -= power_normal_arrow;
        count_normal_arrow--;
        if (number_snake_health > 0) {
            snake_damage();
        }
        else {
            snake_death();
        }
    }
    else if (position_x == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) {
        number_undeed_health -= power_normal_arrow;
        count_normal_arrow--;
        if (number_undeed_health > 0) {
            undeed_damage();
        }
        else {
            undeed_death();
        }
    }
    else if (direction == '8') {
        mark = 0;
        for (int i=1; i<=5; i++) {
            if(position_x == deamon_coordinate[level].x && position_y - i == deamon_coordinate[level].y) {
                number_deamon_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_deamon_health > 0) {
                    deamo_damage();
                }
                else {
                    deamon_death();
                }
                break;
            }
            else if(position_x == fire_coordinate[level].x && position_y - i == fire_coordinate[level].y) {
                number_fire_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_fire_health > 0) {
                    fire_damage();
                }
                else {
                    fire_death();
                }
                break;
            }
            else if(position_x == giant_coordinate[level].x && position_y - i == giant_coordinate[level].y) {
                number_giant_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_giant_health > 0) {
                    giant_damage();
                }
                else {
                    giant_death();
                }
                break;
            }
            else if(position_x == snake_coordinate[level].x && position_y - i == snake_coordinate[level].y) {
                number_snake_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_snake_health > 0) {
                    snake_damage();
                }
                else {
                    snake_death();
                }
                break;
            }
            else if(position_x == undeed_coordinate[level].x && position_y - i == undeed_coordinate[level].y) {
                number_undeed_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_undeed_health > 0) {
                    undeed_damage();
                }
                else {
                    undeed_death();
                }
                break;
            }
            else if (map[level][position_y-i][position_x] == '|' || map[level][position_y-i][position_x] == '_' ||
                     map[level][position_y-i][position_x] == '+') {
                map[level][position_y-i+1][position_x] = 'A';
                mvaddch(position_y-i+1, position_x, 'A');
                running_map[level][position_y-i+1][position_x] = 'A';
                count_normal_arrow--;
                mark = 1;
                break;
            }
        }
        if(!mark) {
            map[level][position_y-5][position_x] = 'A';
            mvaddch(position_y-5, position_x, 'A');
            running_map[level][position_y-5][position_x] = 'A';
        }
        refresh();
    }
    else if (direction == '2') {
        for (int i=1; i<=5; i++) {
            if(position_x == deamon_coordinate[level].x && position_y + i == deamon_coordinate[level].y) {
                number_deamon_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_deamon_health > 0) {
                    deamo_damage();
                }
                else {
                    deamon_death();
                }
                break;
            }
            else if(position_x == fire_coordinate[level].x && position_y + i == fire_coordinate[level].y) {
                number_fire_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_fire_health > 0) {
                    fire_damage();
                }
                else {
                    fire_death();
                }
                break;
            }
            else if(position_x == giant_coordinate[level].x && position_y + i == giant_coordinate[level].y) {
                number_giant_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_giant_health > 0) {
                    giant_damage();
                }
                else {
                    giant_death();
                }
                break;
            }
            else if(position_x == snake_coordinate[level].x && position_y + i == snake_coordinate[level].y) {
                number_snake_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_snake_health > 0) {
                    snake_damage();
                }
                else {
                    snake_death();
                }
                break;
            }
            else if(position_x == undeed_coordinate[level].x && position_y + i == undeed_coordinate[level].y) {
                number_undeed_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_undeed_health > 0) {
                    undeed_damage();
                }
                else {
                    undeed_death();
                }
                break;
            }
            else if (map[level][position_y+i][position_x] == '|' || map[level][position_y+i][position_x] == '_' ||
                     map[level][position_y+i][position_x] == '+') {
                map[level][position_y+i-1][position_x] = 'A';
                mvaddch(position_y+i-1, position_x, 'A');
                running_map[level][position_y+i-1][position_x] = 'A';
                count_normal_arrow--;
                mark = 1;
                break;
            }
        }
        if(!mark) {
            map[level][position_y+5][position_x] = 'A';
            mvaddch(position_y+5, position_x, 'A');
            running_map[level][position_y+5][position_x] = 'A';
        }
        refresh();
    }
    else if (direction == '4') {
        for (int i=1; i<=5; i++) {
            if(position_x - i == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) {
                number_deamon_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_deamon_health > 0) {
                    deamo_damage();
                }
                else {
                    deamon_death();
                }
                break;
            }
            else if(position_x - i == fire_coordinate[level].x && position_y == fire_coordinate[level].y) {
                number_fire_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_fire_health > 0) {
                    fire_damage();
                }
                else {
                    fire_death();
                }
                break;
            }
            else if(position_x - i == giant_coordinate[level].x && position_y == giant_coordinate[level].y) {
                number_giant_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_giant_health > 0) {
                    giant_damage();
                }
                else {
                    giant_death();
                }
                break;
            }
            else if(position_x - i == snake_coordinate[level].x && position_y == snake_coordinate[level].y) {
                number_snake_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_snake_health > 0) {
                    snake_damage();
                }
                else {
                    snake_death();
                }
                break;
            }
            else if(position_x - i == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) {
                number_undeed_health -= power_normal_arrow;
                count_normal_arrow--;
                mark = 1;
                if (number_undeed_health > 0) {
                    undeed_damage();
                }
                else {
                    undeed_death();
                }
                break;
            }
            else if (map[level][position_y][position_x-i] == '|' || map[level][position_y][position_x-i] == '_' ||
                     map[level][position_y][position_x-i] == '+') {
                map[level][position_y][position_x-i+1] = 'A';
                mvaddch(position_y, position_x-i+1, 'A');
                running_map[level][position_y][position_x-i+1] = 'A';
                count_normal_arrow--;
                mark = 1;
                break;
            }
        }
        if(!mark) {
            map[level][position_y][position_x-5] = 'A';
            mvaddch(position_y, position_x-5, 'A');
            running_map[level][position_y][position_x-5] = 'A';
        }
        refresh();
    }
    else if (direction == '6') {
        for (int i=1; i<=5; i++) {
            if(position_x + i == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) {
                number_deamon_health -= 5;
                count_normal_arrow--;
                mark = 1;
                if (number_deamon_health > 0) {
                    deamo_damage();
                }
                else {
                    deamon_death();
                }
                break;
            }
            else if(position_x + i == fire_coordinate[level].x && position_y == fire_coordinate[level].y) {
                number_fire_health -= 5;
                count_normal_arrow--;
                mark = 1;
                if (number_fire_health > 0) {
                    fire_damage();
                }
                else {
                    fire_death();
                }
                break;
            }
            else if(position_x + i == giant_coordinate[level].x && position_y == giant_coordinate[level].y) {
                number_giant_health -= 5;
                count_normal_arrow--;
                mark = 1;
                if (number_giant_health > 0) {
                    giant_damage();
                }
                else {
                    giant_death();
                }
                break;
            }
            else if(position_x + i == snake_coordinate[level].x && position_y == snake_coordinate[level].y) {
                number_snake_health -= 5;
                count_normal_arrow--;
                mark = 1;
                if (number_snake_health > 0) {
                    snake_damage();
                }
                else {
                    snake_death();
                }
                break;
            }
            else if(position_x + i == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) {
                number_undeed_health -= 5;
                count_normal_arrow--;
                mark = 1;
                if (number_undeed_health > 0) {
                    undeed_damage();
                }
                else {
                    undeed_death();
                }
                break;
            }
            else if (map[level][position_y][position_x+i] == '|' || map[level][position_y][position_x+i] == '_' ||
                     map[level][position_y][position_x+i] == '+') {
                map[level][position_y][position_x+i-1] = 'A';
                mvaddch(position_y, position_x+i-1, 'A');
                running_map[level][position_y][position_x+i-1] = 'A';
                count_normal_arrow--;
                mark = 1;
                break;
            }
        }
        if(!mark) {
            map[level][position_y][position_x+5] = 'A';
            mvaddch(position_y, position_x+5, 'A');
            running_map[level][position_y][position_x+5] = 'A';
        }
        refresh();
    }
}
void sword_hit() {
    if ((position_x == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) ||
        (position_x - 1 == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) ||
        (position_x + 1 == deamon_coordinate[level].x && position_y == deamon_coordinate[level].y) ||
        (position_x == deamon_coordinate[level].x && position_y + 1 == deamon_coordinate[level].y) ||
        (position_x == deamon_coordinate[level].x && position_y - 1 == deamon_coordinate[level].y) ||
        (position_x - 1 == deamon_coordinate[level].x && position_y - 1 == deamon_coordinate[level].y) ||
        (position_x - 1 == deamon_coordinate[level].x && position_y + 1 == deamon_coordinate[level].y) ||
        (position_x + 1 == deamon_coordinate[level].x && position_y + 1== deamon_coordinate[level].y)) {
        number_deamon_health -= power_sword;
        if (number_deamon_health > 0) {
            deamo_damage();
        }
        else {
            deamon_death();
        }
    }
    else if ((position_x == fire_coordinate[level].x && position_y == fire_coordinate[level].y) ||
        (position_x - 1 == fire_coordinate[level].x && position_y == fire_coordinate[level].y) ||
        (position_x + 1 == fire_coordinate[level].x && position_y == fire_coordinate[level].y) ||
        (position_x == fire_coordinate[level].x && position_y + 1 == fire_coordinate[level].y) ||
        (position_x == fire_coordinate[level].x && position_y - 1 == fire_coordinate[level].y) ||
        (position_x - 1 == fire_coordinate[level].x && position_y - 1 == fire_coordinate[level].y) ||
        (position_x - 1 == fire_coordinate[level].x && position_y + 1 == fire_coordinate[level].y) ||
        (position_x + 1 == fire_coordinate[level].x && position_y + 1== fire_coordinate[level].y)) {
        number_fire_health -= power_sword;
        if (number_fire_health > 0) {
            fire_damage();
        }
        else {
            fire_death();
        }
    }
    else if ((position_x == giant_coordinate[level].x && position_y == giant_coordinate[level].y) ||
        (position_x - 1 == giant_coordinate[level].x && position_y == giant_coordinate[level].y) ||
        (position_x + 1 == giant_coordinate[level].x && position_y == giant_coordinate[level].y) ||
        (position_x == giant_coordinate[level].x && position_y + 1 == giant_coordinate[level].y) ||
        (position_x == giant_coordinate[level].x && position_y - 1 == giant_coordinate[level].y) ||
        (position_x - 1 == giant_coordinate[level].x && position_y - 1 == giant_coordinate[level].y) ||
        (position_x - 1 == giant_coordinate[level].x && position_y + 1 == giant_coordinate[level].y) ||
        (position_x + 1 == giant_coordinate[level].x && position_y + 1== giant_coordinate[level].y)) {
        number_giant_health -= power_sword;
        if (number_giant_health > 0) {
            giant_damage();
        }
        else {
            giant_death();
        }
    }
    else if ((position_x == snake_coordinate[level].x && position_y == snake_coordinate[level].y) ||
        (position_x - 1 == snake_coordinate[level].x && position_y == snake_coordinate[level].y) ||
        (position_x + 1 == snake_coordinate[level].x && position_y == snake_coordinate[level].y) ||
        (position_x == snake_coordinate[level].x && position_y + 1 == snake_coordinate[level].y) ||
        (position_x == snake_coordinate[level].x && position_y - 1 == snake_coordinate[level].y) ||
        (position_x - 1 == snake_coordinate[level].x && position_y - 1 == snake_coordinate[level].y) ||
        (position_x - 1 == snake_coordinate[level].x && position_y + 1 == snake_coordinate[level].y) ||
        (position_x + 1 == snake_coordinate[level].x && position_y + 1== snake_coordinate[level].y)) {
        number_snake_health -= power_sword;
        if (number_snake_health > 0) {
            snake_damage();
        }
        else {
            snake_death();
        }
    }
    else if ((position_x == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) ||
        (position_x - 1 == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) ||
        (position_x + 1 == undeed_coordinate[level].x && position_y == undeed_coordinate[level].y) ||
        (position_x == undeed_coordinate[level].x && position_y + 1 == undeed_coordinate[level].y) ||
        (position_x == undeed_coordinate[level].x && position_y - 1 == undeed_coordinate[level].y) ||
        (position_x - 1 == undeed_coordinate[level].x && position_y - 1 == undeed_coordinate[level].y) ||
        (position_x - 1 == undeed_coordinate[level].x && position_y + 1 == undeed_coordinate[level].y) ||
        (position_x + 1 == undeed_coordinate[level].x && position_y + 1== undeed_coordinate[level].y)) {
        number_undeed_health -= power_sword;
        if (number_undeed_health > 0) {
            undeed_damage();
        }
        else {
            undeed_death();
        }
    }
}
void check_monster_area() {
    if (position_x >= deamon_coordinate[level].area_x1 && position_x <= deamon_coordinate[level].area_x2 &&
        position_y >= deamon_coordinate[level].area_y1 && position_y <= deamon_coordinate[level].area_y2) {
        if ((deamon_coordinate[level].x == position_x && deamon_coordinate[level].y == position_y) ||
            (deamon_coordinate[level].x == position_x-1 && deamon_coordinate[level].y == position_y) ||
            (deamon_coordinate[level].x == position_x+1 && deamon_coordinate[level].y == position_y) ||
            (deamon_coordinate[level].x == position_x && deamon_coordinate[level].y == position_y-1) ||
            (deamon_coordinate[level].x == position_x && deamon_coordinate[level].y == position_y+1) ||
            (deamon_coordinate[level].x == position_x-1 && deamon_coordinate[level].y == position_y-1) ||
            (deamon_coordinate[level].x == position_x-1 && deamon_coordinate[level].y == position_y+1) ||
            (deamon_coordinate[level].x == position_x+1 && deamon_coordinate[level].y == position_y-1) ||
            (deamon_coordinate[level].x == position_x+1 && deamon_coordinate[level].y == position_y+1)) {
            health--;
            hero_damage();
        }
    }
    if (position_x >= fire_coordinate[level].area_x1 && position_x <= fire_coordinate[level].area_x2 &&
        position_y >= fire_coordinate[level].area_y1 && position_y <= fire_coordinate[level].area_y2) {
        if ((fire_coordinate[level].x == position_x && fire_coordinate[level].y == position_y) ||
            (fire_coordinate[level].x == position_x-1 && fire_coordinate[level].y == position_y) ||
            (fire_coordinate[level].x == position_x+1 && fire_coordinate[level].y == position_y) ||
            (fire_coordinate[level].x == position_x && fire_coordinate[level].y == position_y-1) ||
            (fire_coordinate[level].x == position_x && fire_coordinate[level].y == position_y+1) ||
            (fire_coordinate[level].x == position_x-1 && fire_coordinate[level].y == position_y-1) ||
            (fire_coordinate[level].x == position_x-1 && fire_coordinate[level].y == position_y+1) ||
            (fire_coordinate[level].x == position_x+1 && fire_coordinate[level].y == position_y-1) ||
            (fire_coordinate[level].x == position_x+1 && fire_coordinate[level].y == position_y+1)) {
            health--;
            hero_damage();
        }    
    }
    if (position_x >= giant_coordinate[level].area_x1 && position_x <= giant_coordinate[level].area_x2 &&
        position_y >= giant_coordinate[level].area_y1 && position_y <= giant_coordinate[level].area_y2) {
        if ((giant_coordinate[level].x == position_x && giant_coordinate[level].y == position_y) ||
            (giant_coordinate[level].x == position_x-1 && giant_coordinate[level].y == position_y) ||
            (giant_coordinate[level].x == position_x+1 && giant_coordinate[level].y == position_y) ||
            (giant_coordinate[level].x == position_x && giant_coordinate[level].y == position_y-1) ||
            (giant_coordinate[level].x == position_x && giant_coordinate[level].y == position_y+1) ||
            (giant_coordinate[level].x == position_x-1 && giant_coordinate[level].y == position_y-1) ||
            (giant_coordinate[level].x == position_x-1 && giant_coordinate[level].y == position_y+1) ||
            (giant_coordinate[level].x == position_x+1 && giant_coordinate[level].y == position_y-1) ||
            (giant_coordinate[level].x == position_x+1 && giant_coordinate[level].y == position_y+1)) {
            health--;
            hero_damage();
        }
        else {
            if (number_giant_move) {
                follow1();
            }
        }
    }
    if (position_x >= snake_coordinate[level].area_x1 && position_x <= snake_coordinate[level].area_x2 &&
        position_y >= snake_coordinate[level].area_y1 && position_y <= snake_coordinate[level].area_y2) {
        if ((snake_coordinate[level].x == position_x && snake_coordinate[level].y == position_y) ||
            (snake_coordinate[level].x == position_x-1 && snake_coordinate[level].y == position_y) ||
            (snake_coordinate[level].x == position_x+1 && snake_coordinate[level].y == position_y) ||
            (snake_coordinate[level].x == position_x && snake_coordinate[level].y == position_y-1) ||
            (snake_coordinate[level].x == position_x && snake_coordinate[level].y == position_y+1) ||
            (snake_coordinate[level].x == position_x-1 && snake_coordinate[level].y == position_y-1) ||
            (snake_coordinate[level].x == position_x-1 && snake_coordinate[level].y == position_y+1) ||
            (snake_coordinate[level].x == position_x+1 && snake_coordinate[level].y == position_y-1) ||
            (snake_coordinate[level].x == position_x+1 && snake_coordinate[level].y == position_y+1)) {
            health--;
            hero_damage();
        }
        else {
            if (number_snake_move) {
                follow2();
            }
        }
    }
    if (position_x >= undeed_coordinate[level].area_x1 && position_x <= undeed_coordinate[level].area_x2 &&
        position_y >= undeed_coordinate[level].area_y1 && position_y <= undeed_coordinate[level].area_y2) {
        if ((undeed_coordinate[level].x == position_x && undeed_coordinate[level].y == position_y) ||
            (undeed_coordinate[level].x == position_x-1 && undeed_coordinate[level].y == position_y) ||
            (undeed_coordinate[level].x == position_x+1 && undeed_coordinate[level].y == position_y) ||
            (undeed_coordinate[level].x == position_x && undeed_coordinate[level].y == position_y-1) ||
            (undeed_coordinate[level].x == position_x && undeed_coordinate[level].y == position_y+1) ||
            (undeed_coordinate[level].x == position_x-1 && undeed_coordinate[level].y == position_y-1) ||
            (undeed_coordinate[level].x == position_x-1 && undeed_coordinate[level].y == position_y+1) ||
            (undeed_coordinate[level].x == position_x+1 && undeed_coordinate[level].y == position_y-1) ||
            (undeed_coordinate[level].x == position_x+1 && undeed_coordinate[level].y == position_y+1)) {
            health--;
            hero_damage();
        }
        else {
            if (number_undeed_move) {
                follow3();
            }
        }
    }
}
void follow1() {
    if (rand() % 2) {
        if (position_x > giant_coordinate[level].x) {
            if (map[level][giant_coordinate[level].y][giant_coordinate[level].x+1] != '|' &&
                map[level][giant_coordinate[level].y][giant_coordinate[level].x+1] != '+' &&
                map[level][giant_coordinate[level].y][giant_coordinate[level].x+1] != '_' &&
                monster_map[level][giant_coordinate[level].y][giant_coordinate[level].x+1] == ' ') {
                number_giant_move--;
                mvaddch(giant_coordinate[level].y, giant_coordinate[level].x, map[level][giant_coordinate[level].y][giant_coordinate[level].x]);
                running_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = map[level][giant_coordinate[level].y][giant_coordinate[level].x];
                monster_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = ' ';
                giant_coordinate[level].x++;
                mvaddch (giant_coordinate[level].y, giant_coordinate[level].x, 'G');
                running_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = 'G';
                monster_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = 'G';
            }
        }
        else {
            if (map[level][giant_coordinate[level].y][giant_coordinate[level].x-1] != '|' &&
                map[level][giant_coordinate[level].y][giant_coordinate[level].x-1] != '+' &&
                map[level][giant_coordinate[level].y][giant_coordinate[level].x-1] != '_' &&
                monster_map[level][giant_coordinate[level].y][giant_coordinate[level].x-1] == ' ') {
                number_giant_move--;
                mvaddch(giant_coordinate[level].y, giant_coordinate[level].x, map[level][giant_coordinate[level].y][giant_coordinate[level].x]);
                running_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = map[level][giant_coordinate[level].y][giant_coordinate[level].x];
                monster_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = ' ';
                giant_coordinate[level].x--;
                mvaddch (giant_coordinate[level].y, giant_coordinate[level].x, 'G');
                running_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = 'G';
                monster_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = 'G';
            }
        }
    }
    else {
        if (position_y > giant_coordinate[level].y) {
            if (map[level][giant_coordinate[level].y+1][giant_coordinate[level].x] != '|' &&
                map[level][giant_coordinate[level].y+1][giant_coordinate[level].x] != '+' &&
                map[level][giant_coordinate[level].y+1][giant_coordinate[level].x] != '_' &&
                monster_map[level][giant_coordinate[level].y+1][giant_coordinate[level].x] == ' ') {
                number_giant_move--;
                mvaddch(giant_coordinate[level].y, giant_coordinate[level].x, map[level][giant_coordinate[level].y][giant_coordinate[level].x]);
                running_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = map[level][giant_coordinate[level].y][giant_coordinate[level].x];
                monster_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = ' ';
                giant_coordinate[level].y++;
                mvaddch (giant_coordinate[level].y, giant_coordinate[level].x, 'G');
                running_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = 'G';
                monster_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = 'G';
            }
        }
        else {
            if (map[level][giant_coordinate[level].y-1][giant_coordinate[level].x] != '|' &&
                map[level][giant_coordinate[level].y-1][giant_coordinate[level].x] != '+' &&
                map[level][giant_coordinate[level].y-1][giant_coordinate[level].x] != '_' &&
                monster_map[level][giant_coordinate[level].y-1][giant_coordinate[level].x] == ' ') {
                number_giant_move--;
                mvaddch(giant_coordinate[level].y, giant_coordinate[level].x, map[level][giant_coordinate[level].y][giant_coordinate[level].x]);
                running_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = map[level][giant_coordinate[level].y][giant_coordinate[level].x];
                monster_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = ' ';
                giant_coordinate[level].y--;
                mvaddch (giant_coordinate[level].y, giant_coordinate[level].x, 'G');
                running_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = 'G';
                monster_map[level][giant_coordinate[level].y][giant_coordinate[level].x] = 'G';
            }
        }
    }    
}
void follow2() {
    if (rand() % 2) {
        if (position_x > snake_coordinate[level].x) {
            if (map[level][snake_coordinate[level].y][snake_coordinate[level].x+1] != '|' &&
                map[level][snake_coordinate[level].y][snake_coordinate[level].x+1] != '+' &&
                map[level][snake_coordinate[level].y][snake_coordinate[level].x+1] != '_' &&
                monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x+1] == ' ') {
                mvaddch(snake_coordinate[level].y, snake_coordinate[level].x, map[level][snake_coordinate[level].y][snake_coordinate[level].x]);
                running_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = map[level][snake_coordinate[level].y][snake_coordinate[level].x];
                monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = ' ';
                snake_coordinate[level].x++;
                mvaddch (snake_coordinate[level].y, snake_coordinate[level].x, 'S');
                running_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
                monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
            }
        }
        else {
            if (map[level][snake_coordinate[level].y][snake_coordinate[level].x-1] != '|' &&
                map[level][snake_coordinate[level].y][snake_coordinate[level].x-1] != '+' &&
                map[level][snake_coordinate[level].y][snake_coordinate[level].x-1] != '_' &&
                monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x-1] == ' ') {
                mvaddch(snake_coordinate[level].y, snake_coordinate[level].x, map[level][snake_coordinate[level].y][snake_coordinate[level].x]);
                running_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = map[level][snake_coordinate[level].y][snake_coordinate[level].x];
                monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = ' ';
                snake_coordinate[level].x--;
                mvaddch (snake_coordinate[level].y, snake_coordinate[level].x, 'S');
                running_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
                monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
            }
        }
    }
    else {
        if (position_y > snake_coordinate[level].y) {
            if (map[level][snake_coordinate[level].y+1][snake_coordinate[level].x] != '|' &&
                map[level][snake_coordinate[level].y+1][snake_coordinate[level].x] != '+' &&
                map[level][snake_coordinate[level].y+1][snake_coordinate[level].x] != '_' &&
                monster_map[level][snake_coordinate[level].y+1][snake_coordinate[level].x] == ' ') {
                mvaddch(snake_coordinate[level].y, snake_coordinate[level].x, map[level][snake_coordinate[level].y][snake_coordinate[level].x]);
                running_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = map[level][snake_coordinate[level].y][snake_coordinate[level].x];
                monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = ' ';
                snake_coordinate[level].y++;
                mvaddch (snake_coordinate[level].y, snake_coordinate[level].x, 'S');
                running_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
                monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
            }
        }
        else {
            if (map[level][snake_coordinate[level].y-1][snake_coordinate[level].x] != '|' &&
                map[level][snake_coordinate[level].y-1][snake_coordinate[level].x] != '+' &&
                map[level][snake_coordinate[level].y-1][snake_coordinate[level].x] != '_' &&
                monster_map[level][snake_coordinate[level].y-1][snake_coordinate[level].x] == ' ') {
                mvaddch(snake_coordinate[level].y, snake_coordinate[level].x, map[level][snake_coordinate[level].y][snake_coordinate[level].x]);
                running_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = map[level][snake_coordinate[level].y][snake_coordinate[level].x];
                monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = ' ';
                snake_coordinate[level].y--;
                mvaddch (snake_coordinate[level].y, snake_coordinate[level].x, 'S');
                running_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
                monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
            }
        }
    }    






    // mvaddch(snake_coordinate[level].y, snake_coordinate[level].x, map[level][snake_coordinate[level].y][snake_coordinate[level].x]);
    // running_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = map[level][snake_coordinate[level].y][snake_coordinate[level].x];
    // monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = ' ';
    // if (rand() % 2) {
    //     if (position_x > snake_coordinate[level].x) {
    //         snake_coordinate[level].x++;
    //         mvaddch (snake_coordinate[level].y, snake_coordinate[level].x, 'S');
    //         running_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
    //         monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
    //     }
    //     else {
    //         snake_coordinate[level].x--;
    //         mvaddch (snake_coordinate[level].y, snake_coordinate[level].x, 'S');
    //         running_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
    //         monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
    //     }
    // }
    // else {
    //     if (position_y > snake_coordinate[level].y) {
    //         snake_coordinate[level].y++;
    //         mvaddch (snake_coordinate[level].y, snake_coordinate[level].x, 'S');
    //         running_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
    //         monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
    //     }
    //     else {
    //         snake_coordinate[level].y--;
    //         mvaddch (snake_coordinate[level].y, snake_coordinate[level].x, 'S');
    //         running_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
    //         monster_map[level][snake_coordinate[level].y][snake_coordinate[level].x] = 'S';
    //     }
    // }    
}
void follow3() {
     if (rand() % 2) {
        if (position_x > undeed_coordinate[level].x) {
            if (map[level][undeed_coordinate[level].y][undeed_coordinate[level].x+1] != '|' &&
                map[level][undeed_coordinate[level].y][undeed_coordinate[level].x+1] != '+' &&
                map[level][undeed_coordinate[level].y][undeed_coordinate[level].x+1] != '_' &&
                monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x+1] == ' ') {
                number_undeed_move--;
                mvaddch(undeed_coordinate[level].y, undeed_coordinate[level].x, map[level][undeed_coordinate[level].y][undeed_coordinate[level].x]);
                running_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = map[level][undeed_coordinate[level].y][undeed_coordinate[level].x];
                monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = ' ';
                undeed_coordinate[level].x++;
                mvaddch (undeed_coordinate[level].y, undeed_coordinate[level].x, 'U');
                running_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
                monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
            }
        }
        else {
            if (map[level][undeed_coordinate[level].y][undeed_coordinate[level].x-1] != '|' &&
                map[level][undeed_coordinate[level].y][undeed_coordinate[level].x-1] != '+' &&
                map[level][undeed_coordinate[level].y][undeed_coordinate[level].x-1] != '_' &&
                monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x-1] == ' ') {
                number_undeed_move--;
                mvaddch(undeed_coordinate[level].y, undeed_coordinate[level].x, map[level][undeed_coordinate[level].y][undeed_coordinate[level].x]);
                running_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = map[level][undeed_coordinate[level].y][undeed_coordinate[level].x];
                monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = ' ';
                undeed_coordinate[level].x--;
                mvaddch (undeed_coordinate[level].y, undeed_coordinate[level].x, 'U');
                running_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
                monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
            }
        }
    }
    else {
        if (position_y > undeed_coordinate[level].y) {
            if (map[level][undeed_coordinate[level].y+1][undeed_coordinate[level].x] != '|' &&
                map[level][undeed_coordinate[level].y+1][undeed_coordinate[level].x] != '+' &&
                map[level][undeed_coordinate[level].y+1][undeed_coordinate[level].x] != '_' &&
                monster_map[level][undeed_coordinate[level].y+1][undeed_coordinate[level].x] == ' ') {
                number_undeed_move--;
                mvaddch(undeed_coordinate[level].y, undeed_coordinate[level].x, map[level][undeed_coordinate[level].y][undeed_coordinate[level].x]);
                running_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = map[level][undeed_coordinate[level].y][undeed_coordinate[level].x];
                monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = ' ';
                undeed_coordinate[level].y++;
                mvaddch (undeed_coordinate[level].y, undeed_coordinate[level].x, 'U');
                running_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
                monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
            }
        }
        else {
            if (map[level][undeed_coordinate[level].y-1][undeed_coordinate[level].x] != '|' &&
                map[level][undeed_coordinate[level].y-1][undeed_coordinate[level].x] != '+' &&
                map[level][undeed_coordinate[level].y-1][undeed_coordinate[level].x] != '_' &&
                monster_map[level][undeed_coordinate[level].y-1][undeed_coordinate[level].x] == ' ') {
                number_undeed_move--;
                mvaddch(undeed_coordinate[level].y, undeed_coordinate[level].x, map[level][undeed_coordinate[level].y][undeed_coordinate[level].x]);
                running_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = map[level][undeed_coordinate[level].y][undeed_coordinate[level].x];
                monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = ' ';
                undeed_coordinate[level].y--;
                mvaddch (undeed_coordinate[level].y, undeed_coordinate[level].x, 'U');
                running_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
                monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
            }
        }
    }    










    // number_undeed_move--;
    // mvaddch(undeed_coordinate[level].y, undeed_coordinate[level].x, map[level][undeed_coordinate[level].y][undeed_coordinate[level].x]);
    // running_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = map[level][undeed_coordinate[level].y][undeed_coordinate[level].x];
    // monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = ' ';
    // if (rand() % 2) {
    //     if (position_x > undeed_coordinate[level].x) {
    //         undeed_coordinate[level].x++;
    //         mvaddch (undeed_coordinate[level].y, undeed_coordinate[level].x, 'U');
    //         running_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
    //         monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
    //     }
    //     else {
    //         undeed_coordinate[level].x--;
    //         mvaddch (undeed_coordinate[level].y, undeed_coordinate[level].x, 'U');
    //         running_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
    //         monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
    //     }
    // }
    // else {
    //     if (position_y > undeed_coordinate[level].y) {
    //         undeed_coordinate[level].y++;
    //         mvaddch (undeed_coordinate[level].y, undeed_coordinate[level].x, 'U');
    //         running_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
    //         monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
    //     }
    //     else {
    //         undeed_coordinate[level].y--;
    //         mvaddch (undeed_coordinate[level].y, undeed_coordinate[level].x, 'U');
    //         running_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
    //         monster_map[level][undeed_coordinate[level].y][undeed_coordinate[level].x] = 'U';
    //     }
    // }
}
void fix_monsters_area() {
    deamon_coordinate[level].area_x1 = deamon_coordinate[level].x;
    deamon_coordinate[level].area_x2 = deamon_coordinate[level].x;
    deamon_coordinate[level].area_y1 = deamon_coordinate[level].y;
    deamon_coordinate[level].area_y2 = deamon_coordinate[level].y;
    while (map[level][deamon_coordinate[level].area_y1][deamon_coordinate[level].area_x1 - 1] != '_' &&
           map[level][deamon_coordinate[level].area_y1][deamon_coordinate[level].area_x1 - 1] != '|' &&
           map[level][deamon_coordinate[level].area_y1][deamon_coordinate[level].area_x1 - 1] != '+') {
        deamon_coordinate[level].area_x1--;
    }
    while (map[level][deamon_coordinate[level].area_y1 - 1][deamon_coordinate[level].area_x1] != '_' &&
           map[level][deamon_coordinate[level].area_y1 - 1][deamon_coordinate[level].area_x1] != '|' &&
           map[level][deamon_coordinate[level].area_y1 - 1][deamon_coordinate[level].area_x1] != '+') {
        deamon_coordinate[level].area_y1--;
    }
    while (map[level][deamon_coordinate[level].area_y2][deamon_coordinate[level].area_x2 + 1] != '_' &&
           map[level][deamon_coordinate[level].area_y2][deamon_coordinate[level].area_x2 + 1] != '|' &&
           map[level][deamon_coordinate[level].area_y2][deamon_coordinate[level].area_x2 + 1] != '+') {
        deamon_coordinate[level].area_x2++;
    }
    while (map[level][deamon_coordinate[level].area_y2 + 1][deamon_coordinate[level].area_x2] != '_' &&
           map[level][deamon_coordinate[level].area_y2 + 1][deamon_coordinate[level].area_x2] != '|' &&
           map[level][deamon_coordinate[level].area_y2 + 1][deamon_coordinate[level].area_x2] != '+') {
        deamon_coordinate[level].area_y2++;
    }
    
    fire_coordinate[level].area_x1 = fire_coordinate[level].x;
    fire_coordinate[level].area_x2 = fire_coordinate[level].x;
    fire_coordinate[level].area_y1 = fire_coordinate[level].y;
    fire_coordinate[level].area_y2 = fire_coordinate[level].y;
    while (map[level][fire_coordinate[level].area_y1][fire_coordinate[level].area_x1 - 1] != '_' &&
           map[level][fire_coordinate[level].area_y1][fire_coordinate[level].area_x1 - 1] != '|' &&
           map[level][fire_coordinate[level].area_y1][fire_coordinate[level].area_x1 - 1] != '+') {
        fire_coordinate[level].area_x1--;
    }
    while (map[level][fire_coordinate[level].area_y1 - 1][fire_coordinate[level].area_x1] != '_' &&
           map[level][fire_coordinate[level].area_y1 - 1][fire_coordinate[level].area_x1] != '|' &&
           map[level][fire_coordinate[level].area_y1 - 1][fire_coordinate[level].area_x1] != '+') {
        fire_coordinate[level].area_y1--;
    }
    while (map[level][fire_coordinate[level].area_y2][fire_coordinate[level].area_x2 + 1] != '_' &&
           map[level][fire_coordinate[level].area_y2][fire_coordinate[level].area_x2 + 1] != '|' &&
           map[level][fire_coordinate[level].area_y2][fire_coordinate[level].area_x2 + 1] != '+') {
        fire_coordinate[level].area_x2++;
    }
    while (map[level][fire_coordinate[level].area_y2 + 1][fire_coordinate[level].area_x2] != '_' &&
           map[level][fire_coordinate[level].area_y2 + 1][fire_coordinate[level].area_x2] != '|' &&
           map[level][fire_coordinate[level].area_y2 + 1][fire_coordinate[level].area_x2] != '+') {
        fire_coordinate[level].area_y2++;
    }

    giant_coordinate[level].area_x1 = giant_coordinate[level].x;
    giant_coordinate[level].area_x2 = giant_coordinate[level].x;
    giant_coordinate[level].area_y1 = giant_coordinate[level].y;
    giant_coordinate[level].area_y2 = giant_coordinate[level].y;
    while (map[level][giant_coordinate[level].area_y1][giant_coordinate[level].area_x1 - 1] != '_' &&
           map[level][giant_coordinate[level].area_y1][giant_coordinate[level].area_x1 - 1] != '|' &&
           map[level][giant_coordinate[level].area_y1][giant_coordinate[level].area_x1 - 1] != '+') {
        giant_coordinate[level].area_x1--;
    }
    while (map[level][giant_coordinate[level].area_y1 - 1][giant_coordinate[level].area_x1] != '_' &&
           map[level][giant_coordinate[level].area_y1 - 1][giant_coordinate[level].area_x1] != '|' &&
           map[level][giant_coordinate[level].area_y1 - 1][giant_coordinate[level].area_x1] != '+') {
        giant_coordinate[level].area_y1--;
    }
    while (map[level][giant_coordinate[level].area_y2][giant_coordinate[level].area_x2 + 1] != '_' &&
           map[level][giant_coordinate[level].area_y2][giant_coordinate[level].area_x2 + 1] != '|' &&
           map[level][giant_coordinate[level].area_y2][giant_coordinate[level].area_x2 + 1] != '+') {
        giant_coordinate[level].area_x2++;
    }
    while (map[level][giant_coordinate[level].area_y2 + 1][giant_coordinate[level].area_x2] != '_' &&
           map[level][giant_coordinate[level].area_y2 + 1][giant_coordinate[level].area_x2] != '|' &&
           map[level][giant_coordinate[level].area_y2 + 1][giant_coordinate[level].area_x2] != '+') {
        giant_coordinate[level].area_y2++;
    }

    snake_coordinate[level].area_x1 = snake_coordinate[level].x;
    snake_coordinate[level].area_x2 = snake_coordinate[level].x;
    snake_coordinate[level].area_y1 = snake_coordinate[level].y;
    snake_coordinate[level].area_y2 = snake_coordinate[level].y;
    while (map[level][snake_coordinate[level].area_y1][snake_coordinate[level].area_x1 - 1] != '_' &&
           map[level][snake_coordinate[level].area_y1][snake_coordinate[level].area_x1 - 1] != '|' &&
           map[level][snake_coordinate[level].area_y1][snake_coordinate[level].area_x1 - 1] != '+') {
        snake_coordinate[level].area_x1--;
    }
    while (map[level][snake_coordinate[level].area_y1 - 1][snake_coordinate[level].area_x1] != '_' &&
           map[level][snake_coordinate[level].area_y1 - 1][snake_coordinate[level].area_x1] != '|' &&
           map[level][snake_coordinate[level].area_y1 - 1][snake_coordinate[level].area_x1] != '+') {
        snake_coordinate[level].area_y1--;
    }
    while (map[level][snake_coordinate[level].area_y2][snake_coordinate[level].area_x2 + 1] != '_' &&
           map[level][snake_coordinate[level].area_y2][snake_coordinate[level].area_x2 + 1] != '|' &&
           map[level][snake_coordinate[level].area_y2][snake_coordinate[level].area_x2 + 1] != '+') {
        snake_coordinate[level].area_x2++;
    }
    while (map[level][snake_coordinate[level].area_y2 + 1][snake_coordinate[level].area_x2] != '_' &&
           map[level][snake_coordinate[level].area_y2 + 1][snake_coordinate[level].area_x2] != '|' &&
           map[level][snake_coordinate[level].area_y2 + 1][snake_coordinate[level].area_x2] != '+') {
        snake_coordinate[level].area_y2++;
    }

    undeed_coordinate[level].area_x1 = undeed_coordinate[level].x;
    undeed_coordinate[level].area_x2 = undeed_coordinate[level].x;
    undeed_coordinate[level].area_y1 = undeed_coordinate[level].y;
    undeed_coordinate[level].area_y2 = undeed_coordinate[level].y;
    while (map[level][undeed_coordinate[level].area_y1][undeed_coordinate[level].area_x1 - 1] != '_' &&
           map[level][undeed_coordinate[level].area_y1][undeed_coordinate[level].area_x1 - 1] != '|' &&
           map[level][undeed_coordinate[level].area_y1][undeed_coordinate[level].area_x1 - 1] != '+') {
        undeed_coordinate[level].area_x1--;
    }
    while (map[level][undeed_coordinate[level].area_y1 - 1][undeed_coordinate[level].area_x1] != '_' &&
           map[level][undeed_coordinate[level].area_y1 - 1][undeed_coordinate[level].area_x1] != '|' &&
           map[level][undeed_coordinate[level].area_y1 - 1][undeed_coordinate[level].area_x1] != '+') {
        undeed_coordinate[level].area_y1--;
    }
    while (map[level][undeed_coordinate[level].area_y2][undeed_coordinate[level].area_x2 + 1] != '_' &&
           map[level][undeed_coordinate[level].area_y2][undeed_coordinate[level].area_x2 + 1] != '|' &&
           map[level][undeed_coordinate[level].area_y2][undeed_coordinate[level].area_x2 + 1] != '+') {
        undeed_coordinate[level].area_x2++;
    }
    while (map[level][undeed_coordinate[level].area_y2 + 1][undeed_coordinate[level].area_x2] != '_' &&
           map[level][undeed_coordinate[level].area_y2 + 1][undeed_coordinate[level].area_x2] != '|' &&
           map[level][undeed_coordinate[level].area_y2 + 1][undeed_coordinate[level].area_x2] != '+') {
        undeed_coordinate[level].area_y2++;
    }
}





void battle_room(){
    health--;
    hero_damage();
}
void secret_doors_room() {     //enchant room
    Mix_HaltMusic();
    Mix_Music *music3 = Mix_LoadMUS("music2.mp3");
    Mix_PlayMusic(music3, -1); 
    clear();
    char secret_doors_map[34][121];
    for (int i=0; i<34; i++) {      //Clear the map
        for (int j=0; j<121; j++) {
            secret_doors_map[i][j] = ' ';
        }
    }
    print_margin();
    for (int i=0; i<120; i++) {     //Margin map
        secret_doors_map[0][i] = '%';
        secret_doors_map[33][i] = '%';
        secret_doors_map[3][i] = '%';
    }
    for (int i=0; i<=33; i++) {
        secret_doors_map[i][0] = '%';
        secret_doors_map[i][120] = '%';
    }

    char secret_room[100][100];
    strcpy (secret_room[0], "_________________________________________");
    strcpy (secret_room[1], "|...#.................#.............#...|");
    strcpy (secret_room[2], "|......#.......#..........#.....#.......|");
    strcpy (secret_room[3], "|.................#.....................|");
    strcpy (secret_room[4], "|.#...#...#####....###....#####...#...#.|");
    strcpy (secret_room[5], "|.##..#...#.......#.........#.....##..#.|");
    strcpy (secret_room[6], "|.#.#.#...####....#.###.....#.....#.#.#.|");
    strcpy (secret_room[7], "|.#..##...#.......#...#.....#.....#..##.|");
    strcpy (secret_room[8], "|.#...#...#####....###....#####...#...#.|");
    strcpy (secret_room[9], "|...#...................................|");
    strcpy (secret_room[10], "|..............#......#.................|");
    strcpy (secret_room[11], "|...#....#.........#.......#......#.....|");
    strcpy (secret_room[12], "|_______________________________________|");

    for (int i=0; i<13; i++) {       //print room
        mvprintw(10+i, 37, "%s", secret_room[i]);
        for (int j=0; j<41; j++){
            secret_doors_map[10+i][37+j] = secret_room[i][j];
        }
    }

    int empty[1000][2];
    int count = 0;
    for (int i=0; i<13; i++) {       //find empty room
        for (int j=0; j<42; j++) {
            if (secret_room[i][j] == '.') {
                empty[count][0] = i+10;
                empty[count][1] = j+37;
                count++;
            }
        }
    }
    
    for (int i=0; i<5; i++) {       //fix random doors
        int random = rand() % count;
        int x = empty[random][0];
        int y = empty[random][1];
        secret_doors_map[x][y] = '&';
    }
    for (int i=0; i<5; i++) {       //fix random health spell
        int random = rand() % count;
        int x = empty[random][0];
        int y = empty[random][1];
        secret_doors_map[x][y] = 'h';
        mvaddch (x, y, 'h');
    }
    for (int i=0; i<5; i++) {       //fix random damage spell
        int random = rand() % count;
        int x = empty[random][0];
        int y = empty[random][1];
        secret_doors_map[x][y] = 'd';
        mvaddch (x, y, 'd');
    }
    for (int i=0; i<5; i++) {       //fix random speed spell
        int random = rand() % count;
        int x = empty[random][0];
        int y = empty[random][1];
        secret_doors_map[x][y] = 's';
        mvaddch (x, y, 's');
    }

    mvaddch(11, 38, 'H');
    char last = '.';
    int secret_position_x = 38;
    int secret_position_y = 11;
    int count_move = 0;
    while(1) {      //movemennt
        char move;
        move = getch();
        if (count_move > 15) {
            health--;
            count_move = 0;
        }
        if (move == '8') {
            if (secret_doors_map[secret_position_y - 1][secret_position_x] == '.') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y--;
                last = secret_doors_map[secret_position_y][secret_position_x];
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y - 1][secret_position_x] == '&') {
                break;
            }
            else if (secret_doors_map[secret_position_y - 1][secret_position_x] == 'h') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y--;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_health_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y - 1][secret_position_x] == 'd') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y--;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_damage_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y - 1][secret_position_x] == 's') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y--;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_speed_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
        }
        else if (move == '2') {
            if (secret_doors_map[secret_position_y + 1][secret_position_x] == '.') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y++;
                last = secret_doors_map[secret_position_y][secret_position_x];
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y + 1][secret_position_x] == '&') {
                break;
            }
            else if (secret_doors_map[secret_position_y + 1][secret_position_x] == 'h') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y++;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_health_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y + 1][secret_position_x] == 'd') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y++;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_damage_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y + 1][secret_position_x] == 's') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y++;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_speed_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
        }
        else if (move == '4') {
            if (secret_doors_map[secret_position_y][secret_position_x - 1] == '.') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_x--;
                last = secret_doors_map[secret_position_y][secret_position_x];
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y][secret_position_x - 1] == '&') {
                break;
            }
            else if (secret_doors_map[secret_position_y][secret_position_x - 1] == 'h') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_x--;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_health_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y][secret_position_x - 1] == 'd') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_x--;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_damage_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y][secret_position_x - 1] == 's') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_x--;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_speed_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
        }
        else if (move == '6') {
            if (secret_doors_map[secret_position_y][secret_position_x + 1] == '.') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_x++;
                last = secret_doors_map[secret_position_y][secret_position_x];
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y][secret_position_x + 1] == '&') {
                break;
            }
            else if (secret_doors_map[secret_position_y][secret_position_x + 1] == 'h') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_x++;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_health_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y][secret_position_x + 1] == 'd') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_x++;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_damage_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y][secret_position_x + 1] == 's') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_x++;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_speed_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
        }
        else if (move == '7') {
            if (secret_doors_map[secret_position_y - 1][secret_position_x - 1] == '.') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y--;
                secret_position_x--;
                last = secret_doors_map[secret_position_y][secret_position_x];
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y - 1][secret_position_x - 1] == '&') {
                break;
            }
            else if (secret_doors_map[secret_position_y - 1][secret_position_x - 1] == 'h') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y--;
                secret_position_x--;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_health_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y - 1][secret_position_x - 1] == 'd') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y--;
                secret_position_x--;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_damage_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y - 1][secret_position_x - 1] == 's') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y--;
                secret_position_x--;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_speed_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
        }
        else if (move == '9') {
            if (secret_doors_map[secret_position_y - 1][secret_position_x + 1] == '.') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y--;
                secret_position_x++;
                last = secret_doors_map[secret_position_y][secret_position_x];
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y - 1][secret_position_x + 1] == '&') {
                break;
            }
            else if (secret_doors_map[secret_position_y - 1][secret_position_x + 1] == 'h') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y--;
                secret_position_x++;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_health_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y - 1][secret_position_x + 1] == 'd') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y--;
                secret_position_x++;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_damage_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y - 1][secret_position_x + 1] == 's') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y--;
                secret_position_x++;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_speed_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
        }
        else if (move == '1') {
            if (secret_doors_map[secret_position_y + 1][secret_position_x - 1] == '.') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y++;
                secret_position_x--;
                last = secret_doors_map[secret_position_y][secret_position_x];
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y + 1][secret_position_x - 1] == '&') {
                break;
            }
            else if (secret_doors_map[secret_position_y + 1][secret_position_x - 1] == 'h') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y++;
                secret_position_x--;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_health_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y + 1][secret_position_x - 1] == 'd') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y++;
                secret_position_x--;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_damage_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y + 1][secret_position_x - 1] == 's') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y++;
                secret_position_x--;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_speed_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
        }
        else if (move == '3') {
            if (secret_doors_map[secret_position_y + 1][secret_position_x + 1] == '.') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y++;
                secret_position_x++;
                last = secret_doors_map[secret_position_y][secret_position_x];
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y + 1][secret_position_x + 1] == '&') {
                break;
            }
            else if (secret_doors_map[secret_position_y + 1][secret_position_x + 1] == 'h') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y++;
                secret_position_x++;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_health_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y + 1][secret_position_x + 1] == 'd') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y++;
                secret_position_x++;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_damage_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
            else if (secret_doors_map[secret_position_y + 1][secret_position_x + 1] == 's') {
                mvaddch (secret_position_y, secret_position_x, last);
                secret_position_y++;
                secret_position_x++;
                last = '.';
                secret_doors_map[secret_position_y][secret_position_x] = '.';
                count_speed_spell++;
                mvaddch (secret_position_y, secret_position_x, 'H');
                count_move++;
            }
        }
        else {
            break;
        }
    }

    print_running_map();
}
void give_password() {
    last_password = rand() % 9000 + 1000;
    clear();
    print_margin();
    for (int i=37; i<78; i++) {
        mvaddch (13, i, '#');
        mvaddch (23, i, '#');
    }
    for (int i=13; i<=23; i++) {
        mvaddch (i, 37, '#');
        mvaddch (i, 78, '#');
    }
    mvprintw (17, 47, "The Password Is: %d", last_password);
    attron (COLOR_PAIR(2));
    mvprintw (21, 41, "Don't forget directed by negin =)");
    attroff (COLOR_PAIR(2));
    refresh();
    sleep(3);
    print_running_map();
}
void opening_door(int y, int x) {
    clear();
    print_margin();
    for (int i=30; i<85; i++) {
        mvaddch (8, i, '#');
        mvaddch (23, i, '#');
        mvaddch (12, i, '#');
    }
    for (int i=8; i<=23; i++) {
        mvaddch (i, 30, '#');
        mvaddch (i, 85, '#');
    }
    mvprintw (10, 48, "Enter The Password");
    mvprintw (15, 35, "Enter 'Y' if you want to use your ancient key,");
    mvprintw (16, 35, "otherwise enter 'N'");
    char opinion;
    noecho();
    opinion = getch();
    echo();
    if (opinion == 'n') {
        mvprintw (15, 35, "                                              ");
        mvprintw (16, 35, "                   ");
    }
    else if (opinion == 'y') {
        if (count_master_key > 0) {
            count_master_key--;
            goto here;
        }
        else if (count_broken_master_key > 1) {
            count_broken_master_key -= 2;
            goto here;
        }
        else {
            mvprintw (15, 32, "You don't have enough ancient keys to open the door");
            mvprintw (16, 35, "                   ");
            noecho();
            getch();
            echo();
            mvprintw (15, 32, "                                                   ");
        }
    }
    mvprintw (15, 42, "Password:");
    echo();
    for (int i=0; i<3; i++) {
        int pass;
        mvscanw (15, 53, "%d", &pass);
        if (pass == last_password) {
            here:
            map[level][y][x] = '.';
            running_map[level][y][x] = '.';
            last = '.';
            last_color = 0;
            clear();
            password_room();
            print_running_map();
            noecho();
            return;
        }
        else {
            mvprintw (15, 53, "    ");
            if (i == 0) {
                attron(COLOR_PAIR(4));
                mvprintw (19, 43, "The password is not correct.");
                mvprintw (21, 36, "You only have two more chances, be careful!");
                attroff(COLOR_PAIR(4));
            }
            else if (i == 1) {
                attron(COLOR_PAIR(1));
                mvprintw (19, 43, "The password is not correct.");
                mvprintw (21, 36, "You only have one more chances, be careful!");
                attroff(COLOR_PAIR(1));
            }
            else if (i == 2) {
                clear();
                for (int i=0; i<120; i++) {
                    mvaddch (0, i, '%');
                    mvaddch (33, i, '%');
                }
                for (int i=0; i<=33; i++) {
                    mvaddch (i, 0, '%');
                    mvaddch (i, 120, '%');
                }
                mvprintw (16, 28, "=== This door is destroyed by entering wrong passwords ===");
                getch();
                clear();
                map[level][y][x] = '.';
                running_map[level][y][x] = '.';
                last = '.';
                last_color = 0;
                print_running_map();
                noecho();
                return;
            }
        }
    }
}
void password_room() {
    return;
}
void master_key(int y, int x) {
    if ((rand() % 10) == 5) {
        count_broken_master_key++;
        mvprintw (2, 13, "You picked up a broken ancient key");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                                  ");
    }
    else {
        count_master_key++;
        mvprintw (2, 13, "You picked up an ancient key");
        refresh();
        sleep(1);
        mvprintw (2, 13, "                            ");
    }
    map[level][y][x] = '.';
    running_map[level][y][x] = '.';
    last = '.';
    last_color = 0;
}
void treasure_room() {
    clear();
    Mix_HaltMusic();
    Mix_Music *music3 = Mix_LoadMUS("music2.mp3");
    Mix_PlayMusic(music3, -1); 
    level++;
    clean_the_map(level);
    return_game_to_original();
    margin_the_map();
    print_margin();

    char secret_room[100][100];
    strcpy (secret_room[0], "_________________________________________");
    strcpy (secret_room[1], "|...............................o.......|");
    strcpy (secret_room[2], "|......o.............o...............o..|");
    strcpy (secret_room[3], "|.......................................|");
    strcpy (secret_room[4], "|...........o........o.....o.....o......|");
    strcpy (secret_room[5], "|................o.....o.............o..|");
    strcpy (secret_room[6], "|.o........o.....o.o.o..................|");
    strcpy (secret_room[7], "|...............o...o.o...o......o......|");
    strcpy (secret_room[8], "|............o....o...o.................|");
    strcpy (secret_room[9], "|...o..........................o........|");
    strcpy (secret_room[10], "|.........o.........o.............o.....|");
    strcpy (secret_room[11], "|...o........o..............o...........|");
    strcpy (secret_room[12], "|_______________________________________|");
    clean_the_map(level);
    for (int i=0; i<13; i++) {       //print room
        mvprintw(10+i, 37, "%s", secret_room[i]);
        for (int j=0; j<41; j++){
            map[level][10+i][37+j] = secret_room[i][j];
            running_map[level][i+10][j+37] = secret_room[i][j];
        }
    }
    
    count_land = 0;
    for (int i=0; i<34; i++) {      //Find empty rooms1
        for (int j=0; j<121; j++) {
            if (map[level][i][j] == '.') {
                land[count_land][0] = i;
                land[count_land][1] = j;
                count_land++;
            }
        }
    }
    count_land--;
    position_y = 11;
    position_x = 38;
    for(int i=0; i<6; i++) {
        rectangles[i].y = 5;
        rectangles[i].x = 5;
        rectangles[i].y2 = 5;
        rectangles[i].x2 = 5;
    }
    

    placing_in_map('^', 10, 0, 0);
    placing_in_map('$', number_normal_gold, 1, 0);
    placing_in_map('g', number_black_gold, 1, 0);
    placing_in_map('D', 1, 1, 0);
    placing_in_map('F', 1, 1, 0);
    placing_in_map('G', 1, 1, 0);
    placing_in_map('S', 1, 1, 0);
    placing_in_map('U', 1, 1, 0);
    deamon_coordinate[5].area_x1 = 38;
    deamon_coordinate[5].area_y1 = 11;
    deamon_coordinate[5].area_x2 = 77;
    deamon_coordinate[5].area_y2 = 22;

    fire_coordinate[5].area_x1 = 38;
    fire_coordinate[5].area_y1 = 11;
    fire_coordinate[5].area_x2 = 77;
    fire_coordinate[5].area_y2 = 22;

    giant_coordinate[5].area_x1 = 38;
    giant_coordinate[5].area_y1 = 11;
    giant_coordinate[5].area_x2 = 77;
    giant_coordinate[5].area_y2 = 22;

    snake_coordinate[5].area_x1 = 38;
    snake_coordinate[5].area_y1 = 11;
    snake_coordinate[5].area_x2 = 77;
    snake_coordinate[5].area_y2 = 22;

    undeed_coordinate[5].area_x1 = 38;
    undeed_coordinate[5].area_y1 = 11;
    undeed_coordinate[5].area_x2 = 77;
    undeed_coordinate[5].area_y2 = 22;
    
    number_giant_move = 5;
    number_snake_move = 1;
    number_undeed_move = 5;
    movemennt();

}






void use_menu() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 55, "Use list:");

    int ch;
    int highlight = 0;
    char *choice[4] = {"Use Weapons", "Use Spells", "Use Food", "Back"};
    int num_choice = 4;

    while (1) {
        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                if (strcmp(choice[i], "Back") == 0) {
                    attron(A_REVERSE);
                    mvprintw(26, 72, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
                else {
                    attron(A_REVERSE);
                    mvprintw(2*i+15, 55, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
            }
            else {
                if (strcmp(choice[i], "Back") == 0) {
                    mvprintw(26, 72, "%s", choice[i]);
                }
                else {
                    mvprintw(2*i+15, 55, "%s", choice[i]);
                }
            }
        }
        ch = getch();
        if (ch == '8') {
            if (highlight == 0) {
                highlight = num_choice - 1;
            }
            else {
                highlight--;
            }
        }
        else if (ch == '2') {
            if (highlight == num_choice - 1) {
                highlight = 0;
            }
            else {
                highlight++;
            }
        }
        else {
            break;
        }
        refresh();
    }

    if (highlight == 0) {
        use_weapon();
    }
    else if (highlight == 1) {
        use_spell();
    }
    else if (highlight == 2) {
        use_food();
    }
    else if (highlight == 3) {
        print_running_map();
    }
}
void use_weapon() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 51, "Weapon usage list:");

    int ch;
    int highlight = 0;
    char *choice[3] = {"Short range weapons", "Long range weapons", "Back"};
    int num_choice = 3;

    while (1) {
        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                if (strcmp(choice[i], "Back") == 0) {
                    attron(A_REVERSE);
                    mvprintw(26, 72, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
                else {
                    attron(A_REVERSE);
                    mvprintw(2*i+15, 51, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
            }
            else {
                if (strcmp(choice[i], "Back") == 0) {
                    mvprintw(26, 72, "%s", choice[i]);
                }
                else {
                    mvprintw(2*i+15, 51, "%s", choice[i]);
                }
            }
        }
        ch = getch();
        if (ch == '8') {
            if (highlight == 0) {
                highlight = num_choice - 1;
            }
            else {
                highlight--;
            }
        }
        else if (ch == '2') {
            if (highlight == num_choice - 1) {
                highlight = 0;
            }
            else {
                highlight++;
            }
        }
        else {
            break;
        }
        refresh();
    }

    if (highlight == 0) {
        use_short_weapon();
    }
    else if (highlight == 1) {
        use_long_weapon();
    }
    else if (highlight == 2) {
        use_menu();
    }
}
void use_short_weapon() { 
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 50, "Short range weapons:");
    mvprintw (15, 47, "Mace");
    mvprintw (19, 47, "Sword");

    int ch;
    int highlight = 0;
    char *choice[5] = {"Use", "Info", "Use", "Info", "Back"};
    int num_choice = 5;

    while (1) {
        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                if (strcmp(choice[i], "Back") == 0) {
                    attron(A_REVERSE);
                    mvprintw(26, 72, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
                else if (i == 2 && count_sword <= 0) {
                    attron(A_REVERSE);
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                    attroff(A_REVERSE);
                }
                else {
                    attron(A_REVERSE);
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
            }
            else {
                if (strcmp(choice[i], "Back") == 0) {
                    mvprintw(26, 72, "%s", choice[i]);
                }
                else if (i == 2 && count_sword <= 0) {
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                }
                else {
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                }
            }
        }
        ch = getch();
        if (ch == '8') {
            if (highlight == 0) {
                highlight = num_choice - 1;
            }
            else {
                highlight--;
            }
        }
        else if (ch == '2') {
            if (highlight == num_choice - 1) {
                highlight = 0;
            }
            else {
                highlight++;
            }
        }
        else {
            break;
        }
        refresh();
    }

    if (highlight == 0) {
        if (know_weapon == ' ') {
            know_weapon = 'm';
            mvprintw (2, 13, "Your weapon is changed to mace");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                              ");
            print_running_map();
        }
        else {
            mvprintw (2, 13, "Please put your weapon in the backpack first");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                            ");
            print_running_map();
        }
        
    }
    else if (highlight == 1) {
        mace_info_menu();
    }
    else if (highlight == 2) {
        if (count_sword <= 0) {
            mvprintw (2, 13, "You don't have a sword in your backpack");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                       ");
            use_short_weapon();
        }
        else if (know_weapon == ' ') {
            know_weapon = 's';
            mvprintw (2, 13, "Your weapon is changed to sword");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                               ");
            print_running_map();
        }
        else {
            mvprintw (2, 13, "Please put your weapon in the backpack first");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                            ");
            print_running_map();
        }
    }
    else if (highlight == 3) {
        sword_info_menu();
    }
    else if (highlight == 4) {
        use_weapon();
    }
}
void use_long_weapon() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 50, "Long range weapons:");
    mvprintw (15, 47, "Dagger");
    mvprintw (19, 47, "Magic Wand");
    mvprintw (23, 47, "Arrow");

    int ch;
    int highlight = 0;
    char *choice[7] = {"Use", "Info", "Use", "Info", "Use", "Info", "Back"};
    int num_choice = 7;

    while (1) {
        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                if (strcmp(choice[i], "Back") == 0) {
                    attron(A_REVERSE);
                    mvprintw(26, 72, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
                else if (i == 0 && count_dagger <= 0) {
                    attron(A_REVERSE);
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                    attroff(A_REVERSE);
                }
                else if (i == 2 && count_magic_wand <= 0) {
                    attron(A_REVERSE);
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                    attroff(A_REVERSE);
                }
                else if (i == 4 && count_normal_arrow <= 0) {
                    attron(A_REVERSE);
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                    attroff(A_REVERSE);
                }
                else {
                    attron(A_REVERSE);
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
            }
            else {
                if (strcmp(choice[i], "Back") == 0) {
                    mvprintw(26, 72, "%s", choice[i]);
                }
                else if (i == 0 && count_dagger <= 0) {
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                }
                else if (i == 2 && count_magic_wand <= 0) {
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                }
                else if (i == 4 && count_normal_arrow <= 0) {
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                }
                else {
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                }
            }
        }
        ch = getch();
        if (ch == '8') {
            if (highlight == 0) {
                highlight = num_choice - 1;
            }
            else {
                highlight--;
            }
        }
        else if (ch == '2') {
            if (highlight == num_choice - 1) {
                highlight = 0;
            }
            else {
                highlight++;
            }
        }
        else {
            break;
        }
        refresh();
    }

    if (highlight == 0) {
        if (count_dagger <= 0) {
            mvprintw (2, 13, "You don't have a dagger in your backpack");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                        ");
            use_long_weapon();
        }
        else if (know_weapon == ' '){
            know_weapon = 'r';
            mvprintw (2, 13, "Your weapon is changed to dagger");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                ");
            print_running_map();
        }
        else {
            mvprintw (2, 13, "Please put your weapon in the backpack first");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                            ");
            print_running_map();
        }
    }
    else if (highlight == 1) {
        dagger_info_menu();
    }
    else if (highlight == 2) {
        if (count_magic_wand <= 0) {
            mvprintw (2, 13, "You don't have a magic wand in your backpack");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                            ");
            use_long_weapon();
        }
        else if (know_weapon == ' '){
            know_weapon = 'w';
            mvprintw (2, 13, "Your weapon is changed to magic wand");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                    ");
            print_running_map();
        }
        else {
            mvprintw (2, 13, "Please put your weapon in the backpack first");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                            ");
            print_running_map();
        }
    }
    else if (highlight == 3) {
        magic_wand_info_menu();
    }
    else if (highlight == 4) {
        if (count_normal_arrow <= 0) {
            mvprintw (2, 13, "You don't have a arrow in your backpack");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                        ");
            use_long_weapon();
        }
        else if (know_weapon == ' '){
            know_weapon = 'a';
            mvprintw (2, 13, "Your weapon is changed to arrow");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                ");
            print_running_map();
        }
        else {
            mvprintw (2, 13, "Please put your weapon in the backpack first");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                            ");
            print_running_map();
        }
    }
    else if (highlight == 5) {
        normal_arrow_info_menu();
    }
    else if (highlight == 6) {
        use_weapon();
    }
}
void mace_info_menu() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 51, "Mace information:");

    mvprintw (15, 47, "Power:");
    mvprintw (17, 47, "Symbol:");
    mvprintw (19, 47, "Available Quantity:");

    mvprintw (15, 73, "5");
    mvprintw (17, 73, "m");
    mvprintw (19, 73, "1");

    attron(A_REVERSE);
    mvprintw (26, 72, "Back");
    attroff(A_REVERSE);
    getch();
    use_short_weapon();
}
void dagger_info_menu() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 50, "Dagger information:");

    mvprintw (15, 47, "Power:");
    mvprintw (17, 47, "Symbol:");
    mvprintw (19, 47, "Available Quantity:");
    mvprintw (21, 47, "Range:");

    mvprintw (15, 73, "12");
    mvprintw (17, 73, "r");
    mvprintw (19, 73, "%d", count_dagger);
    mvprintw (21, 73, "5");

    attron(A_REVERSE);
    mvprintw (26, 72, "Back");
    attroff(A_REVERSE);
    getch();
    use_long_weapon();
}
void magic_wand_info_menu() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 48, "Magic Wand information:");

    mvprintw (15, 47, "Power:");
    mvprintw (17, 47, "Symbol:");
    mvprintw (19, 47, "Available Quantity:");
    mvprintw (21, 47, "Range:");

    mvprintw (15, 73, "15");
    mvprintw (17, 73, "w");
    mvprintw (19, 73, "%d", count_magic_wand);
    mvprintw (21, 73, "10");

    attron(A_REVERSE);
    mvprintw (26, 72, "Back");
    attroff(A_REVERSE);
    getch();
    use_long_weapon();
}
void normal_arrow_info_menu() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 50, "Arrow information:");

    mvprintw (15, 47, "Power:");
    mvprintw (17, 47, "Symbol:");
    mvprintw (19, 47, "Available Quantity:");
    mvprintw (21, 47, "Range:");

    mvprintw (15, 73, "5");
    mvprintw (17, 73, "a");
    mvprintw (19, 73, "%d", count_normal_arrow);
    mvprintw (21, 73, "5");

    attron(A_REVERSE);
    mvprintw (26, 72, "Back");
    attroff(A_REVERSE);
    getch();
    use_long_weapon();
}
void sword_info_menu() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 51, "Sword information:");

    mvprintw (15, 47, "Power:");
    mvprintw (17, 47, "Symbol:");
    mvprintw (19, 47, "Available Quantity:");

    mvprintw (15, 73, "10");
    mvprintw (17, 73, "l");
    mvprintw (19, 73, "%d", count_sword);

    attron(A_REVERSE);
    mvprintw (26, 72, "Back");
    attroff(A_REVERSE);
    getch();
    use_short_weapon();
}
void use_spell() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 57, "Spells");
    mvprintw (15, 47, "Health Spells");
    mvprintw (17, 47, "Speed Spells");
    mvprintw (19, 47, "Damage Spells");

    int ch;
    int highlight = 0;
    char *choice[4] = {"Use", "Use", "Use", "Back"};
    int num_choice = 4;

    while (1) {
        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                if (strcmp(choice[i], "Back") == 0) {
                    attron(A_REVERSE);
                    mvprintw(26, 72, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
                else if (i == 0 && count_health_spell <= 0) {
                    attron(A_REVERSE);
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                    attroff(A_REVERSE);
                }
                else if (i == 1 && count_speed_spell <= 0) {
                    attron(A_REVERSE);
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                    attroff(A_REVERSE);
                }
                else if (i == 2 && count_damage_spell <= 0) {
                    attron(A_REVERSE);
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                    attroff(A_REVERSE);
                }
                else {
                    attron(A_REVERSE);
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
            }
            else {
                if (strcmp(choice[i], "Back") == 0) {
                    mvprintw(26, 72, "%s", choice[i]);
                }
                else if (i == 0 && count_health_spell <= 0) {
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                }
                else if (i == 1 && count_speed_spell <= 0) {
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                }
                else if (i == 2 && count_damage_spell <= 0) {
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                }
                else {
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                }
            }
        }
        ch = getch();
        if (ch == '8') {
            if (highlight == 0) {
                highlight = num_choice - 1;
            }
            else {
                highlight--;
            }
        }
        else if (ch == '2') {
            if (highlight == num_choice - 1) {
                highlight = 0;
            }
            else {
                highlight++;
            }
        }
        else {
            break;
        }
        refresh();
    }
    if (highlight == 0) {
        if (count_health_spell <= 0) {
            mvprintw (2, 13, "You don't have a health spell in your backpack");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                              ");
            use_spell();
        }
        else {
            use_health_spell();
            mvprintw (2, 13, "The desired spell was used");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                          ");
            count_health_spell--;
            print_running_map();
        }
    }
    if (highlight == 1) {
        if (count_speed_spell <= 0) {
            mvprintw (2, 13, "You don't have a speed spell in your backpack");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                              ");
            use_spell();
        }
        else {
            use_speed_spell();
            mvprintw (2, 13, "The desired spell was used");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                          ");
            count_speed_spell--;
            print_running_map();
        }
    }
    if (highlight == 2) {
        if (count_damage_spell <= 0) {
            mvprintw (2, 13, "You don't have a damage spell in your backpack");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                              ");
            use_spell();
        }
        else {
            use_damage_spell();
            mvprintw (2, 13, "The desired spell was used");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                          ");
            count_damage_spell--;
            print_running_map();
        }
    }
    else if (highlight == 3) {
        use_menu();
    }
}
void use_food() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 57, "Foods");
    mvprintw (15, 47, "Normal Food");
    mvprintw (17, 47, "Excellent Food");
    mvprintw (19, 47, "Magic Food");

    int ch;
    int highlight = 0;
    char *choice[4] = {"Use", "Use", "Use", "Back"};
    int num_choice = 4;

    while (1) {
        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                if (strcmp(choice[i], "Back") == 0) {
                    attron(A_REVERSE);
                    mvprintw(26, 72, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
                else if (i == 0 && count_normal_food <= 0 && count_rotten_food <= 0) {
                    attron(A_REVERSE);
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                    attroff(A_REVERSE);
                }
                else if (i == 1 && count_excellent_food <= 0) {
                    attron(A_REVERSE);
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                    attroff(A_REVERSE);
                }
                else if (i == 2 && count_magic_food <= 0) {
                    attron(A_REVERSE);
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                    attroff(A_REVERSE);
                }
                else {
                    attron(A_REVERSE);
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(A_REVERSE);
                }
            }
            else {
                if (strcmp(choice[i], "Back") == 0) {
                    mvprintw(26, 72, "%s", choice[i]);
                }
                else if (i == 0 && count_normal_food <= 0 && count_rotten_food <= 0) {
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                }
                else if (i == 1 && count_excellent_food <= 0) {
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                }
                else if (i == 2 && count_magic_food <= 0) {
                    attron(COLOR_PAIR(1));
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                    attroff(COLOR_PAIR(1));
                }
                else {
                    mvprintw(2*i+15, 70, "%s", choice[i]);
                }
            }
        }
        ch = getch();
        if (ch == '8') {
            if (highlight == 0) {
                highlight = num_choice - 1;
            }
            else {
                highlight--;
            }
        }
        else if (ch == '2') {
            if (highlight == num_choice - 1) {
                highlight = 0;
            }
            else {
                highlight++;
            }
        }
        else {
            break;
        }
        refresh();
    }
    if (highlight == 0) {
        if (count_normal_food <= 0 && count_rotten_food <= 0) {
            mvprintw (2, 13, "You don't have a normal food in your backpack");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                      ");
            use_food();
        }
        else {
            if (count_rotten_food > 0) {
                hunger += 4;
                mvprintw (1, 62, "                  ");
                mvprintw (2, 13, "The desired food was eaten");
                refresh();
                sleep(1);
                mvprintw (2, 13, "                          ");
                count_rotten_food--;
                print_running_map();
            }
            else {
                hunger = 0;
                mvprintw (1, 62, "                  ");
                mvprintw (2, 13, "The desired food was eaten");
                refresh();
                sleep(1);
                mvprintw (2, 13, "                          ");
                count_normal_food--;
                print_running_map();
            }
        }
    }
    else if (highlight == 1) {
        if (count_excellent_food <= 0) {
            mvprintw (2, 13, "You don't have an excellent food in your backpack");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                                 ");
            use_food();
        }
        else {
            hunger = 0;
            mvprintw (1, 62, "                  ");
            mvprintw (2, 13, "The desired food was eaten");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                          ");
            count_excellent_food--;
            use_damage_spell();
            print_running_map();
        }
    }
    else if (highlight == 2) {
        if (count_magic_food <= 0) {
            mvprintw (2, 13, "You don't have a magic food in your backpack");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                                            ");
            use_food();
        }
        else {
            hunger = 0;
            mvprintw (1, 62, "                  ");
            mvprintw (2, 13, "The desired food was eaten");
            refresh();
            sleep(1);
            mvprintw (2, 13, "                          ");
            count_magic_food--;
            use_speed_spell();
            print_running_map();
        }
    }
    else if (highlight == 3) {
        use_menu();
    }
}
void use_health_spell(){
    count_move_health_spell = 10;
}
void use_speed_spell(){
    count_move_speed_spell = 10;
}
void use_damage_spell(){
    count_move_damage_spell = 10;
}









void backpack_menu() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 53, "Backpack list:");

    int ch;
    int highlight = 0;
    char *choice[6] = {"List of foods", "List of keys", "List of spells", "List of golds", "List of weapons", "Back"};
    int num_choice = 6;

    while (1) {
        for (int i=0; i<num_choice; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
                mvprintw(2*i+15, 52, "%s", choice[i]);
                attroff(A_REVERSE);
            }
            else {
                mvprintw(2*i+15, 52, "%s", choice[i]);
            }
        }
        ch = getch();
        if (ch == '8') {
            if (highlight == 0) {
                highlight = num_choice - 1;
            }
            else {
                highlight--;
            }
        }
        else if (ch == '2') {
            if (highlight == num_choice - 1) {
                highlight = 0;
            }
            else {
                highlight++;
            }
        }
        else {
            break;
        }
        refresh();
    }
    
    if (highlight == 0) {
        food_list();
    }
    else if (highlight == 1) {
        key_list();
    }
    else if (highlight == 2) {
        spell_list();
    }
    else if (highlight == 3) {
        gold_list();
    }
    else if (highlight == 4) {
        weapon_list();
    }
    else if (highlight == 5) {
        print_running_map();
    }
}
void food_list() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 53, "List of foods:");
    mvprintw (15, 45, "Normal Foods:");
    mvprintw (17, 45, "Excellent Foods:");
    mvprintw (19, 45, "Magic Foods:");
    mvprintw (15, 70, "%d   ", count_normal_food + count_rotten_food);
    mvprintw (17, 70, "%d   ", count_excellent_food);
    mvprintw (19, 70, "%d   ", count_magic_food);
    attron(A_REVERSE);
    mvprintw (26, 72, "Back");
    attroff(A_REVERSE);
    getch();
    backpack_menu();
}
void key_list() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 53, "List of keys:");
    mvprintw (15, 45, "Ancient Keys:");
    mvprintw (15, 70, "%d", count_master_key);
    mvprintw (17, 45, "Broken Ancient Keys:");
    mvprintw (17, 70, "%d", count_broken_master_key);
    attron(A_REVERSE);
    mvprintw (26, 72, "Back");
    attroff(A_REVERSE);
    getch();
    backpack_menu();
}
void spell_list() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 53, "List of spells:");
    mvprintw (15, 45, "Health Spell:");
    mvprintw (15, 70, "%d", count_health_spell);
    mvprintw (17, 45, "Speed Spell:");
    mvprintw (17, 70, "%d", count_speed_spell);
    mvprintw (19, 45, "Damage Spell:");
    mvprintw (19, 70, "%d", count_damage_spell);
    attron(A_REVERSE);
    mvprintw (26, 72, "Back");
    attroff(A_REVERSE);
    getch();
    backpack_menu();
}
void gold_list() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 53, "List of golds:");
    mvprintw (15, 45, "Golds:");
    mvprintw (15, 70, "%d", count_normal_gold);
    mvprintw (17, 45, "Black Golds:");
    mvprintw (17, 70, "%d", count_black_gold);
    attron(A_REVERSE);
    mvprintw (26, 72, "Back");
    attroff(A_REVERSE);
    getch();
    backpack_menu();
}
void weapon_list() {
    clear();
    print_margin();
    print_menu_margin();
    mvprintw (10, 53, "List of weapons:");
    mvprintw (15, 45, "Mace:");
    mvprintw (15, 70, "%d", count_mace);
    mvprintw (17, 45, "Dagger:");
    mvprintw (17, 70, "%d", count_dagger);
    mvprintw (19, 45, "Magic Wand:");
    mvprintw (19, 70, "%d", count_magic_wand);
    mvprintw (21, 45, "Normal Arrows:");
    mvprintw (21, 70, "%d", count_normal_arrow);
    mvprintw (23, 45, "Sword:");
    mvprintw (23, 70, "%d", count_sword);
    attron(A_REVERSE);
    mvprintw (26, 72, "Back");
    attroff(A_REVERSE);
    getch();
    backpack_menu();
}







void staircase() {
    level++;
    clear();
    start_game();
}
void low_staircase() {
    level--;
    clear();
    position_x = staircase_coordinate[level].x;
    position_y = staircase_coordinate[level].y;
    print_running_map();
}
void return_game_to_original() {
    number_deamon_health = 5;
    number_fire_health = 10;
    number_giant_health = 15;
    number_snake_health = 20;
    number_undeed_health = 30;
    number_giant_move = 5;
    number_undeed_move = 5;
    number_snake_move = 1;
}
void lost_game() {
    clear();
    noecho();
    print_board();
    mvprintw (16, 45, "*** You Are A Loser ***");
    score = count_normal_gold;
    score += count_black_gold * 3;
    if (score > highest_score) {
        highest_score = score;
    }
    number_of_game++;
    mvprintw (17, 53, "Score: %d", score);
    getch();
    if (type_of_user) {
        save_game("end");
        clear();
        introduction();
    }
    else {
        clear();
        introduction();
    }
}
void win_game() {
    clear();
    print_board();
    mvprintw (16, 51, "*** You Win ***");
    score = count_normal_gold;
    score += count_black_gold * 3;
    score += 20;
    if (score > highest_score) {
        highest_score = score;
    }
    number_of_game++;
    mvprintw (16, 53, "Score: %d", score);
    getch();
    if (type_of_user) {
        save_game("end");
        clear();
        introduction();
    }
    else {
        clear();
        introduction();
    }
}