#include <stdio.h>
#include <stdlib.h>

#define LINE "________________________\n"

void welcome()
{
  printf(
    "Welcome to the Flag Management System!\n\n"
    "################################################\n"
    "#                                              #\n"
    "#  #######   #       #    #####                #\n"
    "#  #     #   ##     ##   #     #    ##   ##    #\n"
    "#  #         ##     ##   #     #    ##   ##    #\n"
    "#  #         # #   # #   #          ##   ##    #\n"
    "#  ####      # #   # #    #####                #\n"
    "#  #         #  # #  #         #   #       #   #\n"
    "#  #         #  # #  #         #    #######    #\n"
    "#  #         #   #   #         #      ###      #\n"
    "#  #         #   #   #   #     #               #\n"
    "#  #         #       #    #####                #\n"
    "#                                              #\n"
    "################################################\n\n");
};

void main_menu()
{
  printf(LINE
	 "  ~~Main menu~~ \n"
	 " 1. Register\n"
	 " 2. Login\n");
  fflush(stdin);
  fflush(stdout);
}

void register_menu()
{
  printf(LINE
	 "  ~~Registration~~ \n");
  fflush(stdin);
  fflush(stdout);
}

void login_menu()
{
  printf(LINE
	 "  ~~Login~~ \n");
  fflush(stdin);
  fflush(stdout);
}

void auth(char *buf)
{
  char tmp[1000];
  printf("Login: ");
  fflush(stdout);
  scanf("%999s", buf);
  printf("Password: ");
  fflush(stdout);
  scanf("%999s", tmp);
}

int main(){
  int choise = 0;
  char login[1000] = "";
  welcome();
  
  goto main_m;

  main_m:
  main_menu();
  scanf("%d", &choise);
  switch (choise) {
    case 2: goto login_m;
    case 1: goto register_m;
    defalut:
    printf("Invalid choise: %d\n", choise);
    goto main_m;
  }

  login_m:
  login_menu();
  auth(login);
  if (!strcmp(login, "root")) {
    printf(
      "Login:        ok...\n"
      "Password:     ok...\n"
      "Fingerprint:  fail...\n\n"
      "Access denied!!\n");
  } else if (!strcmp(login, "admin")) {
    printf(
      "Login:              ok...\n"
      "Password:           ok...\n"
      "Fingerprint:        fail...\n"
      "Typing Rhythm:      fail...\n\n"
      "Access denied!!\n");
  } else {
    printf(
      "User does not exist!\n");
  }
  goto main_m;

  register_m:
  register_menu();
  auth(login);
  if ( !strcmp(login, "admin") || !strcmp(login, "root") ) {
    printf("User already exists!\n");
    goto main_m;
  }
  printf("Welcome!\n"
	 "Currently logged in as ");
  printf(login);
  printf("\n"
	 "You are not allowed to create new flags.\n"
	 "You have no flags.\n\n");
  goto main_m;

  return 0;
}
