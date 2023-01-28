#include "ut_tuti_functions.h"

void print_messages(int index)
{
    char *spaces = "                      "; // 22
    char *lines = "-          -         -        -       -      -     -    -   -  - -";
    char *Hello = "Hello and welcome to ut-tuti";

    switch (index)
    {
    case 0:
        printf("\n");
        int counter = 5;
        Sleep(2000);
        while (counter >= 0)
        {
            printf("\rclosing program in %d...", counter);
            Sleep(1000);
            counter--;
        }
        break;

    case 1:
        Sleep(2000);
        printf("\n\n\n\n\n\n\n");
        printf("%s", spaces);
        for (int i = 0; i < (strlen(lines) + 1); i++)
        {
            printf("%c", lines[i]);
            Sleep(17);
        }
        for (int i = 0; i < (strlen(Hello) + 1); i++)
        {
            printf("%c", Hello[i]);
            Sleep(77);
        }
        for (int i = strlen(lines) - 1; i >= 0; i--)
        {
            printf("%c", lines[i]);
            Sleep(17);
        }
        printf("%s", spaces);
        printf("\n");
        break;

    case 2:
        printf("\n____________________________________________");
        printf("\nwhat do you want to do?\n");
        break;
    }
}

void print_posts(USER *head, USER *current_user)
{
    POST *current_post = (POST *)malloc(sizeof(POST));
    int i = 0;
    if (current_user->num_of_posts == 0)
    {
        printf("\n\nthere isn't any post from this user!");
        return;
    }
    current_post = current_user->postsHead->next_post; // postsHead is empty and (postsHead->next_post) is first post
    printf("\n\nand the posts of this user (like)");
    while ((current_post != '\0') && (i < current_user->num_of_posts))
    {
        printf("\npost number %d: %s (%d)", current_post->postID, current_post->text, current_post->num_of_likes);
        i++;
        current_post = current_post->next_post;
    }
    return;
}


void print_information(USER *head, USER *current_user, int *loggedin)
{
    printf("informations of user '%s':", current_user->username);
    printf("\nusername: %s", current_user->username);
    if ((*loggedin) == (current_user->index))
    {
        printf("\npassword: %s", current_user->password);
    }
    printf("\nnumber of posts: %d", current_user->num_of_posts);
    printf("\nuser index: %d", current_user->index);
    return;
}

int check_login(int *loggedin)
{
    if (*loggedin == 0)
    {
        printf("\nplease login first!");
        return 0;
    }
    return 1;
}

int check_logout(int *loggedin)
{
    if (*loggedin != 0)
    {
        printf("\nplease logout first!");
        return 0;
    }
    return 1;
}

void goto_user(USER *head, USER **current_user, int *loggedin)
{
    int i = 1;
    (*current_user) = head->next_user;
    while (i < *loggedin)
    {
        (*current_user) = (*current_user)->next_user;
        i++;
    }
}

void goto_post(POST *head, POST **current_post, int id)
{
    int i = 0;
    (*current_post) = head;
    while (i < id)
    {
        (*current_post) = (*current_post)->next_post;
        i++;
    }
}

void get_input(char **input)
{
    input[0] = (char *)malloc(sizeof(char));
    char ch;
    int i = 0;
    ch = getchar();
    // getting input characters one by one useing a loop
    while (ch != '\n')
    {
        input[0][i] = ch;
        i++;
        input[0] = realloc(input[0], (i + 1) * sizeof(char));
        ch = getchar();
    }
    input[0][i] = '\0';
    fflush(stdin);
    return;
}

void separate_words(char **input, char **first_word, char **next_words)
{
    first_word[0] = (char *)malloc(sizeof(char));
    next_words[0] = (char *)malloc(sizeof(char));
    int i = 0, j = 0;
    // separating first word
    while (input[0][i] != SPACE)
    {
        first_word[0][j] = input[0][i];
        i++;
        j++;
        first_word[0] = realloc(first_word[0], (j + 1) * sizeof(char));
    }
    first_word[0][j] = '\0';

    // separating next words
    j = 0;
    i++; // space between first word and next words
    while (input[0][i] != '\0')
    {
        next_words[0][j] = input[0][i];
        j++;
        i++;
        next_words[0] = realloc(next_words[0], (j + 1) * sizeof(char));
    }
    next_words[0][j] = '\0';
}

void signup(USER *head, char **next_words, int *loggedin)
{
    if (!check_logout(loggedin))
        return;

    char **UserName = (char **)malloc(sizeof(char *));
    char **PassWord = (char **)malloc(sizeof(char *));
    separate_words(next_words, UserName, PassWord);
    USER *new_user = (USER *)malloc(sizeof(USER));
    USER *current_user = (USER *)malloc(sizeof(USER));
    current_user = head->next_user;
    int i = 0, num_of_users = 0;
    while (current_user != '\0') // check if this username is used before
    {
        if (strcmp((current_user->username), UserName[0]) == 0)
        {
            printf("\nthis username is already taken!");
            return;
        }
        num_of_users++;
        current_user = current_user->next_user;
    }
    // adding new user to link list
    i = 0;
    current_user = head;
    while (i < num_of_users)
    {
        current_user = current_user->next_user;
        i++;
    }
    // going to last user
    current_user->next_user = new_user;
    (new_user->username) = (char *)malloc((strlen(UserName[0]) + 1) * sizeof(char));
    (new_user->password) = (char *)malloc((strlen(PassWord[0]) + 1) * sizeof(char));
    strcpy((new_user->username), UserName[0]);
    strcpy((new_user->password), PassWord[0]);
    new_user->num_of_posts = 0;
    new_user->index = num_of_users + 1;
    POST *fakePost = (POST *)malloc(sizeof(POST));
    new_user->postsHead = fakePost;
    fakePost->next_post = '\0';
    free(UserName);
    free(PassWord);
    printf("\nsuccessfully signed up\nusername: %s\npassword: %s\nid: %d", new_user->username, new_user->password, new_user->index);
    return;
}

void login(USER *head, char **next_words, int *loggedin)
{
    if (!check_logout(loggedin))
        return;

    char **UserName = (char **)malloc(sizeof(char *));
    char **PassWord = (char **)malloc(sizeof(char *));
    separate_words(next_words, UserName, PassWord);
    USER *current_user = (USER *)malloc(sizeof(USER));
    current_user = head->next_user;
    while (current_user != NULL)
    {
        if ((strcmp(UserName[0], (current_user->username)) == 0) && (strcmp(PassWord[0], current_user->password) == 0))
        {
            *loggedin = (current_user->index);
            free(UserName);
            free(PassWord);
            printf("\nsuccessfully logged in!\n username: %s\n password: %s\n id: %d", current_user->username, current_user->password, current_user->index);
            return;
        }
        current_user = current_user->next_user;
    }
    printf("\nno such user found!");
    return;
}

void logout(USER *head, int *loggedin)
{
    if (!check_login(loggedin))
        return;

    USER *current_user = (USER *)malloc(sizeof(USER));
    goto_user(head, &current_user, loggedin);
    printf("\nsuccessfully logged out from '%s'", current_user->username);
    *loggedin = 0;
    return;
}

void posting(USER *head, char **next_words, int *loggedin)
{
    if (!check_login(loggedin))
        return;

    POST *new_post = (POST *)malloc(sizeof(POST));
    POST *current_post = (POST *)malloc(sizeof(POST));
    USER *current_user = (USER *)malloc(sizeof(USER));
    // copying next words of input to text of post
    int size = strlen(next_words[0]);
    new_post->text = (char *)malloc((size + 1) * sizeof(char));
    strcpy((new_post->text), next_words[0]);
    goto_user(head, &current_user, loggedin);
    // going to current post
    current_post = current_user->postsHead; // current post = fake post
    int i = 0;
    while (i < (current_user->num_of_posts))
    {
        current_post = current_post->next_post;
        i++;
    }
    current_post->next_post = new_post;
    new_post->author = current_user->index;
    new_post->num_of_likes = 0;
    new_post->next_post = '\0';
    new_post->postID = (current_user->num_of_posts) + 1;
    new_post->liked_before = (int *)malloc(sizeof(int));
    (new_post->liked_before)[0] = -1;
    (current_user->num_of_posts)++;
    printf("\nthis is user %s's %dth post:\n%s", current_user->username, current_user->num_of_posts, new_post->text);
}

void delete_post(USER *head, char **next_words, int *loggedin)
{
    if (!check_login(loggedin))
        return;

    USER *current_user = (USER *)malloc(sizeof(USER));
    POST *current_post = (POST *)malloc(sizeof(POST));
    goto_user(head, &current_user, loggedin);

    int i = 0, id = atoi(next_words[0]);
    if ((id > current_user->num_of_posts) || (id == 0))
    {
        printf("there isn't any post with id %d", id);
        return;
    }

    i = 1;
    current_post = current_user->postsHead;
    while (i < id)
    {
        current_post = current_post->next_post;
        i++;
    }
    POST *temp = current_post->next_post;
    current_post->next_post = current_post->next_post->next_post;
    printf("\nsuccessfully deleted post '%s' from user '%s'", temp->text, current_user->username); // dota badio chap mikone
    current_post = temp->next_post;
    free(temp);

    for (i = id; i < current_user->num_of_posts; i++)
    {
        (current_post->postID)--;
        current_post = current_post->next_post;
    }
    (current_user->num_of_posts)--;
}

void like_post(USER *head, char **next_words, int *loggedin)
{
    if (!check_login(loggedin))
        return;

    char **UserName = (char **)malloc(sizeof(char *));
    char **strID = (char **)malloc(sizeof(char *));
    separate_words(next_words, UserName, strID);
    int id = atoi(strID[0]);
    USER *current_user = (USER *)malloc(sizeof(USER));
    POST *current_post = (POST *)malloc(sizeof(POST));

    current_user = head->next_user;
    while (current_user != '\0')
    {
        if (strcmp(UserName[0], current_user->username) == 0)
        {
            if ((id > current_user->num_of_posts) || (id == 0))
            {
                printf("\nthere isn't any post with id %d", id);
                return;
            }
            goto_post(current_user->postsHead, &current_post, id);
            (current_post->num_of_likes)++;
            free(UserName);
            free(strID);
            printf("\nsuccessfully liked post '%s' from user '%s'", current_post->text, current_user->username);
            return;
        }
        current_user = current_user->next_user;
    }
    printf("\npost not found!");
    return;
}

void show_info(USER *head, int *loggedin)
{
    if (!check_login(loggedin))
        return;

    USER *current_user = (USER *)malloc(sizeof(USER));
    POST *current_post = (POST *)malloc(sizeof(POST));
    int i = 0;
    current_user = head->next_user;
    goto_user(head, &current_user, loggedin);
    print_information(head, current_user, loggedin);
    print_posts(head, current_user);
    return;
}

void find_user(USER *head, char **next_words, int *loggedin)
{
    USER *current_user = (USER *)malloc(sizeof(USER));
    POST *current_post = (POST *)malloc(sizeof(POST));
    current_user = head->next_user;
    while (current_user != '\0')
    {
        if (strcmp(next_words[0], current_user->username) == 0)
        {
            print_information(head, current_user, loggedin);
            print_posts(head, current_user);
            return;
        }
        current_user = current_user->next_user;
    }
    printf("user not found!");
    return;
}

void do_what(USER *head, char **input, int *loggedin)
{
    char **first_word = (char **)malloc(sizeof(char *));
    char **next_words = (char **)malloc(sizeof(char *));
    separate_words(input, first_word, next_words);
    if (strcmp(first_word[0], "signup") == 0)
    {
        signup(head, next_words, loggedin);
    }
    else if (strcmp(first_word[0], "login") == 0)
    {
        login(head, next_words, loggedin);
    }

    else if (strcmp(first_word[0], "logout") == 0)
    {
        logout(head, loggedin);
    }

    else if (strcmp(first_word[0], "post") == 0)
    {
        posting(head, next_words, loggedin);
    }

    else if (strcmp(first_word[0], "like") == 0)
    {
        like_post(head, next_words, loggedin);
    }

    else if (strcmp(first_word[0], "delete") == 0)
    {
        delete_post(head, next_words, loggedin);
    }

    else if (strcmp(first_word[0], "info") == 0)
    {
        show_info(head, loggedin);
    }

    else if (strcmp(first_word[0], "find_user") == 0)
    {
        find_user(head, next_words, loggedin);
    }

    else if ((strcmp(first_word[0], "end") == 0) || (strcmp(first_word[0], "exit") == 0))
    {
        print_messages(0);
        exit(0);
    }
    else
    {
        printf("invalid input!");
    }
    
    free(first_word);
    free(next_words);
}
