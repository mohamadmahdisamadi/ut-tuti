#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#define TRUE 1
#define SPACE ' '
typedef struct user USER;
typedef struct post POST;
struct user
{
    char *username;
    char *password;
    int index;
    int num_of_posts;
    POST *postsHead;
    struct user *next_user;
};
struct post
{
    int author;
    char *text;
    int num_of_likes;
    int *liked_before;
    int postID;
    POST *next_post;
};
void print_messages(int index);
void print_posts(USER *head, USER *current_user);
void print_information(USER *head, USER *current_user, int *loggedin);
int check_login(int* loggedin);
int check_logout(int* loggedin);
void goto_user(USER *head, USER **current_user, int *loggedin);
void goto_post(POST *head, POST **current_post, int id);
void get_input(char **input);
void separate_words(char **input, char **first_word, char **next_words);
void signup(USER *head, char **next_words, int *loggedin);
void login(USER *head, char **next_words, int *loggedin);
void logout(USER *head, int *loggedin);
void posting(USER *head, char **next_words, int *loggedin);
void delete_post(USER *head, char **next_words, int *loggedin);
void like_post(USER *head, char **next_words, int *loggedin);
void show_info(USER *head, int *loggedin);
void find_user(USER *head, char **next_words, int *loggedin);
void do_what(USER *head, char **input, int *loggedin);
