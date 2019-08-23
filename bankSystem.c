/**
Title   : Bank Management System
Team    : The Bankers
Authors : Aayush Twayana
          Anjaan Khadka
          Anish shilpakar
          Bimal Bhoyadyo
Date    : 2019
**/

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#define rootName "root"
#define rootPw "root"

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/***************************************** Border Box ***********************************************/
void box(int x, int y, int X, int Y){

  int i,j;
  system("color 3");

  for(i = 1; i <= y; i++){
	  
	  gotoxy(X, Y++);
	  
      if(i == 1 || i == y){
          for(j = 0; j < x; j++){
              printf("\xB2");
          }
      }else{
          for(j = 1; j <= x; j++){
              if(j == 1 || j == x){
                  printf("\xB2");
              }else{
                  printf(" ");
              }
          }
      }
  }
}

void secBox(char a[]){

    int i, j;

    for(i = 1; i <= 21; i++){
        if(i == 1){
            for(j = 0; j < 81; j++){
                if(j <= 30 || j >= 49){
                    printf("\xB2");
                }else{
                    printf("%c", a[j - 30]);
                }
            }
        }else if(i == 21){
             for(j = 0; j < 81; j++){
                printf("\xB2");
            }
        }else{
            for(j = 1; j <= 81; j++){
                if(j == 1 || j == 81){
                    printf("\xB2");
                }else{
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

/********************************** Users function prototype **************************/
void rootUser();
void generalUser(char [], char []);


/****************************************** Features modules prototype ********************************/
void login();
void register_(int);
void home();
void delete_();
void update();
void view();
void search();
void delay(unsigned int);
void loadingPage();

/****************************************** Structures *********************************************/

struct loginData{
    char password[20];
    char username[20];
};

struct add{
	char country[15];
	char town[15];
};

struct date{
	int year,month,day;
};

struct info{
  int accNo;
	char name[25];
  char last[25];
	char accType[10];
	char gender[5];
	struct add address;
	char phone[10];
	struct date dob;
	float bal;
	struct loginData credentials;
}add, upd, check, del, use;

/****************************************** Main Function Declaration section ******************************/

    /*Copied from programming-techniques.com*/ //sizing the console window.....

HANDLE wHnd;    // Handle to write to the console.
HANDLE rHnd;    // Handle to read from the console.

int main(){
    // Set up the handles for reading/writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    // Change the window title:
    SetConsoleTitle("BANK MANAGEMENT SYSTEM  -THE BANKERS");
    // Set up the required window size:
    SMALL_RECT windowSize = {0, 0, 80, 20};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    // Change the console window size:
    // Create a COORD to hold the buffer size:
    COORD bufferSize = {80, 20};
    SetConsoleScreenBufferSize(wHnd, bufferSize);

    //Calling on the home() function.
    system ("color 2");
    loadingPage();
    delay(1000);
    gotoxy(0,0);
    home();
    return 0;
    // Exit

}

/****************************************** Secondary Function Declaration section ******************************/
void home(){
    int choice;
    int success = 0;

    system("CLS");
    while(success != 1){

        fflush(stdin);
        gotoxy(0, 2);
        box(81, 18, 0, 2);
        gotoxy(22, 0);
        box(41, 5, 22, 0);
        gotoxy(29, 2);
        puts(" BANK MANAGEMENT SYSTEM ");

        gotoxy(31, 9);
        puts("   1. LOG IN\n\n\t\t\t\t  2. SIGN UP\n\n\t\t\t\t  3. EXIT");
        gotoxy(0, 18);
        box(81, 3, 0, 18);
        gotoxy(29, 19);
        printf(" INPUT: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                login();
                success = 1;
                break;
            case 2:
                register_(0);
                success = 1;
                break;
            case 3:
                success = 1;
                exit(1);
                break;
            default:
                system("CLS");
                gotoxy(15,4);
                box(50, 8, 15, 4);
                gotoxy(18,7);
                puts(" Please Enter the  Input in Numeral Format.\a");
                delay(1000000);
                system("CLS");
        }
    }

}


void register_(int x){
    int choice, success = 0, check = 0, i;
    char ch;
    FILE *fp;

    fp = fopen("loginInfo.TXT", "r");
    system("CLS");

    secBox("  REGISTER ACCOUNT");
 /******************************** Checking for the existance of the account**********/

        gotoxy(22, 3);
        printf("Enter User Name: ");
        scanf("%s", use.credentials.username);

        while(fscanf(fp,"%d%s%s%s%s%s%s%s%d%d%d%f%s%s",&add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,&add.dob.year,&add.dob.month,&add.dob.day,&add.bal,add.credentials.username,add.credentials.password) != EOF){
            if(strcmp(use.credentials.username, add.credentials.username) == 0){
                delay(20);
                system("CLS");

                gotoxy(15,4);
                box(50, 8, 15, 4);
                gotoxy(22,7);

                printf("** Account is already in use **\a");
                gotoxy(20,8);
                printf("Do you want to login instead? (y || N): ");
                fflush(stdin);
                ch = getchar();
                if(ch == 'Y' || ch == 'y'){
                    fclose(fp);
                    login();
                }else{
                    fclose(fp);
                    exit(1);
                }
            }
        }
        fclose(fp);

/********************************* Actual registering process *************************/
        fp = fopen("loginInfo.TXT", "a");
        fflush(stdin);
        gotoxy(22, 4);
        printf("Account No.: ");
        scanf("%d", &add.accNo);

        gotoxy(22, 5);
        printf("First Name: ");
        scanf("%s", add.name);

        gotoxy(22, 6);
        printf("Last Name: ");
        scanf("%s", add.last);

        gotoxy(22, 7);
        printf("Account Type (Current/ Saving/ Fixed): ");
        scanf("%s", add.accType);

        gotoxy(22, 8);
        printf("Gender (MALE/ FEMALE): ");
        scanf("%s", add.gender);

        gotoxy(22, 9);
        printf("Country: ");
        scanf("%s", add.address.country);

        gotoxy(22, 10);
        printf("Town: ");
        scanf("%s", add.address.town);

        gotoxy(22, 11);
        printf("Contact Number: ");
        scanf("%s", add.phone);

        gotoxy(22, 12);
        printf("Date of Birth (DD MM YYYY) (B.S.):  ");
        scanf ("%d%d%d",&add.dob.year, &add.dob.month, &add.dob.day);

        gotoxy(22, 13);
        printf("Initial Deposit (Rs.): ");
        scanf("%f",&add.bal);

        strcpy(add.credentials.username, use.credentials.username);

        gotoxy(22, 14);
        printf("Enter New Password : ");
        scanf("%s", add.credentials.password);

        fprintf(fp,"%d %s %s %s %s %s %s %s %d %d %d %f %s %s\n",add.accNo,add.name,add.last,strupr(add.accType),add.gender,add.address.country,add.address.town,add.phone,add.dob.year,add.dob.month,add.dob.day,add.bal, add.credentials.username, add.credentials.password);

        fclose(fp);

        system("CLS");
        gotoxy(15,6);
        box(50, 5, 15, 6);
        gotoxy(22,8);

        printf("** New Account Created Successfully **\a");
        delay(1000000);

        while (success != 1){
            system("CLS");
            gotoxy(15, 4);
            box(50, 8, 15, 4);
            gotoxy(22, 7);

            printf("Enter 1 to goto MAIN and 0 to EXIT");
            gotoxy(35, 8);
            printf(">> ");
            scanf("%d", &choice);
                    if(choice == 1){
                        system("CLS");
                        success = 1;
                        if(x == 0){
                            home();
                        }else if(x == 1){
                            rootUser();
                        }
                    }else if(choice == 0){
                        success = 1;
                        exit(1);
                    }else{
                        gotoxy(35, 10);
                        printf("** INVALID INPUT **\a");
                        delay(1000000);
                    }
        }
}


void login(){

    int count = 0, success = 0, i;
    char t, pass, psw[20];
    FILE *fp;

    fp = fopen("loginInfo.TXT", "r");

    while(success != 1){
    	i = 0;
        system("CLS");
        rewind(fp);

            secBox("     LOGIN PAGE   ");
            gotoxy(15, 5);
            box(50, 8, 15, 5);
            gotoxy(27, 7);

            printf("USER NAME : ");
            scanf("%s", use.credentials.username);

            gotoxy(27,9);
            printf("PASSWORD  : ");
            //scanf("%s", use.credentials.password);

            while((pass = getch()) != 13){				//ASCII value of /n is 13
       			 psw[i] = pass;
       			 printf("*");
       			 i++;
            }
            psw[i] = '\0';
            strcpy(use.credentials.password, psw);

            if(strcmp(use.credentials.username, rootName) == 0 && strcmp(use.credentials.password, rootPw) == 0){
                success = 1;
                system("CLS");
                gotoxy(15,4);
                box(50, 8, 15, 4);
                gotoxy(28,7);

                printf("** LOGIN SUCCESSFUL **\a");
                delay(10000);
                fclose(fp);
                rootUser();

            }
            while(fscanf(fp, "%d%s%s%s%s%s%s%s%d%d%d%f%s%s", &add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,&add.dob.year,&add.dob.month,&add.dob.day,&add.bal,add.credentials.username,add.credentials.password) != EOF){
                if (strcmp(use.credentials.username, add.credentials.username)== 0 && strcmp(use.credentials.password, add.credentials.password)== 0){    //strcmpi to make it non-sensitive to letter - case
                    count = 1;
                }
            }
            if(count == 1){
                success = 1;
                system("CLS");
                gotoxy(15,4);
                box(50, 8, 15, 4);
                gotoxy(28,7);

                printf("** LOGIN SUCCESSFUL **\a");
                delay(10000);
                fclose(fp);
                generalUser(use.credentials.username, use.credentials.password);

            }else if(count == 0){
                invalid2:
                    system("CLS");
                    gotoxy(15, 4);
                    box(50, 8, 15, 4);
                    gotoxy(31, 6);

                    printf("** LOGIN FAILED **\a");
                    delay(10000);


                    gotoxy(22, 8);

                    printf("Do You wish to try again? (Y || N): ");
                    gotoxy(35, 9);
                    printf(">> ");
                    fflush(stdin);
                    scanf("%c", &t);

                    if (t == 'n' || t == 'N'){
                        success = 1;
                        system("CLS");
                        fclose(fp);
                        home();
                    }else if (t == 'y' || t == 'Y'){
                        success = 0;
                    }else{
                        system("CLS");
                        gotoxy(15, 4);
                        box(50, 8, 15, 4);
                        gotoxy(29, 7);
                        puts("** Enter a valid Input **");
                        delay(10000);
                        goto invalid2;
                    }

                delay(10000);
            }
        }

}


void rootUser(){
    int option_choice, test = 0;

    while(test != 1){

        system("CLS");
        fflush(stdin);
        secBox("     ADMIN PANEL    ");

        gotoxy(27, 3);
        puts("1. View User Details");
        gotoxy(27, 4);
        puts("2. Register New User");
        gotoxy(27, 5);
        puts("3. Delete Existing User");
        gotoxy(27, 6);
        puts("4. Update User Information");
        gotoxy(27, 7);
        puts("5. Search User Information");
        gotoxy(27, 8);
        puts("0. Exit");
        gotoxy(16, 13);
        box(50, 3, 16, 13);
        gotoxy(17, 14);
        printf(" INPUT: ");
        scanf("%d", &option_choice);

        if (option_choice == 1){
            test = 1;
            view();
        }else if (option_choice == 2){
            test = 1;
            register_(1);
        }else if (option_choice == 3){
            test = 1;
            delete_();
        }else if (option_choice == 4){
            test = 1;
            update();
        }else if (option_choice == 5){
            test = 1;
            search();
        }else if (option_choice == 0){
            test = 1;
            exit(1);
        }else{
            system("CLS");
            gotoxy(15, 4);
            box(50, 8, 15, 4);
            gotoxy(29, 7);
            puts("** Enter a valid Input **\a");
            delay(10000);
        }
    }

}

void generalUser(char user[], char pw[]){

    int success = 0, accNo, input, tac;
    float initialBalance, amt;
    char name[20], choice, a;

    FILE * oldrec, * newrec;

    top:
    success = 0;
    oldrec = fopen("loginInfo.TXT", "r");
    newrec = fopen("newLoginInfo.TXT", "a");

	while(success != 1){
		system("CLS");
		rewind(oldrec);

	    while(fscanf(oldrec, "%d%s%s%s%s%s%s%s%d%d%d%f%s%s", &add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,&add.dob.year,&add.dob.month,&add.dob.day,&add.bal,add.credentials.username,add.credentials.password)!= EOF){
	        if (strcmp(add.credentials.username, user)== 0){
	            initialBalance = add.bal;
	            accNo = add.accNo;
	            strcpy(name, add.name);
	        }
	    }

	    secBox("      USER PAGE     ");

	    gotoxy(3, 3);
	    box(33, 15, 3, 3);

	    gotoxy(6, 7);
	    printf("Account Holder: %s", strupr(name));
		gotoxy(6, 9);
		printf("Account No.: %d", accNo);
		gotoxy(6, 11);
		printf("Initial Balance: %.3f", initialBalance);

	    gotoxy(50, 5);
	    printf("1. Transfer Amount");
	    gotoxy(50, 7);
		printf("2. Account Summary");
		gotoxy(50, 9);
		printf("3. Account Settings");
		gotoxy(50, 11);
		printf("4. Log Out");

		gotoxy(45, 15);
		box(30, 3, 45, 15);
		gotoxy(50, 16);
		printf("INPUT: ");
        scanf("%d", &input);
        fflush(stdin);

        switch(input){
            case 1:
                success = 1;
                system("CLS");

                secBox("     TRANSACTION     ");

                gotoxy(23, 3);
                printf("Enter the amount: ");
                scanf("%f", &amt);

				gotoxy(23, 5);
				printf("Enter the a/c No.: ");
                scanf("%d", &tac);

                gotoxy(23, 7);
				printf("Enter the date (DD MM YYYY): ");
                scanf("%d%d%d", &use.dob.day, &use.dob.month, &use.dob.year);

                fflush(stdin);
                gotoxy(17, 11);
                box(50,6,17,11);
                gotoxy(20,13);
                puts("Are you sure you want to continue? (y || N): ");
                gotoxy(35,14);
                printf(">>");
                choice = getchar();

                if(choice == 'y' || choice == 'Y'){
                    system("CLS");

                    if(amt <= initialBalance){
                    	rewind(oldrec);
	                	gotoxy(10, 4);
			            box(65, 15, 10, 4);
			            gotoxy(28, 7);

						puts("** TRANSACTION COMPLETED **\a");
						delay(15000);gotoxy(31, 9);
						printf("Date: %d-%d-%d", use.dob.day, use.dob.month, use.dob.year);
						gotoxy(31, 10);
						printf("Account No.: %d", tac);
						gotoxy(31, 11);
						printf("Amount: %.3f", amt);
						gotoxy(31, 12);
						printf("Remaining Balance: %.3f", (initialBalance-amt));
						initialBalance -= amt;
						while(fscanf(oldrec,"%d%s%s%s%s%s%s%s%d%d%d%f%s%s", &add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,&add.dob.year,&add.dob.month,&add.dob.day,&add.bal,add.credentials.username,add.credentials.password) != EOF){
						    if(strcmp(add.credentials.username, user) == 0){
						          fprintf(newrec, "%d %s %s %s %s %s %s %s %d %d %d %f %s %s\n", add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,add.dob.year,add.dob.month,add.dob.day,initialBalance,add.credentials.username,add.credentials.password);
						    }else{
						          fprintf(newrec, "%d %s %s %s %s %s %s %s %d %d %d %f %s %s\n", add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,add.dob.year,add.dob.month,add.dob.day,add.bal,add.credentials.username,add.credentials.password);
						    }
						}
						fclose(oldrec);
						fclose(newrec);
						remove("loginInfo.TXT");
						rename("newLoginInfo.TXT", "loginInfo.TXT");
                    }else{
                    	gotoxy(15, 4);
			            box(50, 8, 15, 4);
			            gotoxy(28, 7);

                        puts("** NO SUFFICIENT BALANCE **\a");
                        fclose(oldrec);
                        fclose(newrec);
                        remove("newLoginInfo.TXT");
                    }

					gotoxy(28,15);
                    puts("Press any key to continue...");
                    gotoxy(58,15);
                    fflush(stdin);
                    a = getch();
                        goto top;
                }else{
                    fclose(oldrec);
                    fclose(newrec);
                    remove("newLoginInfo.TXT");
                    goto top;
                }
                break;

            case 2:
            	system("CLS");
            	gotoxy(15, 4);
	            box(50, 8, 15, 4);
	            gotoxy(28, 7);

                puts("** UNAVAILABLE AT THE MOMENT **\a");                          //yet to define
                success = 1;

                fclose(oldrec);
                fclose(newrec);
                remove("newLoginInfo.TXT");
                delay(10000);
                goto top;
                break;

            case 3:
                success = 1;
                system("CLS");
	            gotoxy(15, 4);
	            box(50, 8, 15, 4);
	            gotoxy(22, 7);

            	rewind(oldrec);
                printf(" Change password : (Y to CONTINUE)");
                gotoxy(31,8);
                printf(">> ");
                fflush(stdin);
                a = getchar();
                if (a == 'y' || a == 'Y'){

                    pw_again:
                    system("CLS");
                    gotoxy(15, 4);
		            box(50, 8, 15, 4);
		            gotoxy(20, 7);

                    printf("Enter your old password: ");
                    scanf("%s", check.credentials.password);
                    gotoxy(20,8);
                    printf("Enter your new password: ");
                    scanf("%s", upd.credentials.password);

                    if(strcmp(check.credentials.password, pw) == 0){
                        while(fscanf(oldrec,"%d%s%s%s%s%s%s%s%d%d%d%f%s%s", &add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,&add.dob.year,&add.dob.month,&add.dob.day,&add.bal,add.credentials.username,add.credentials.password)!= EOF){
                              if(strcmp(add.credentials.password, pw) == 0){
                                    fprintf(newrec,"%d %s %s %s %s %s %s %s %d %d %d %f %s %s\n",add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,add.dob.year,add.dob.month,add.dob.day,add.bal,add.credentials.username,upd.credentials.password);
                              }else{
                                    fprintf(newrec,"%d %s %s %s %s %s %s %s %d %d %d %f %s %s\n",add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,add.dob.year,add.dob.month,add.dob.day,add.bal,add.credentials.username,add.credentials.password);
                              }
                        }
                        fclose(oldrec);
                        fclose(newrec);
                        remove("loginInfo.TXT");
                        rename("newLoginInfo.TXT", "loginInfo.TXT");

                        system("CLS");
                        gotoxy(15, 4);
			            box(50, 6, 15, 4);
			            gotoxy(23, 6);
                        puts("** PASSWORD CHANGED SUCCESSFULLY **\a");
                        delay(20000);
                        goto top;

                    }else{
						system("CLS");
						gotoxy(15, 4);
			            box(50, 5, 15, 4);
			            gotoxy(29, 6);                                                        //add option to go back as well...
                        puts("** INCORRECT PASSWORD **\a");
                        delay(15000);
                        goto pw_again;
                    }

                }else{
                    goto top;
                }break;

            case 4:
                success = 1;
                system("CLS");
	            gotoxy(15, 4);
	            box(50, 6, 15, 4);
	            gotoxy(32, 6);

                puts("** THANK YOU **");
                gotoxy(32,7);
                printf("<< The Bankers >>");

                fclose(oldrec);
                fclose(newrec);
                remove("newLoginInfo.TXT");
                delay(100000);
                exit(1);
                break;

            default:
                puts("** INVALID **\a");
                delay(1000);
                system("CLS");
        }
    }

}

void delete_(){

    int success = 0;
    char input;

    FILE * oldrec, * newrec;
    oldrec = fopen("loginInfo.TXT", "r");
    newrec = fopen("newLoginInfo.TXT", "a+");

    system("CLS");
	secBox("       DELETE     ");
	  gotoxy(13, 5);
	  box(55, 3, 13, 5);
	  gotoxy(15, 6);

    printf("Enter the account no. of the user: ");
    scanf("%d", &del.accNo);

    while(fscanf(oldrec,"%d%s%s%s%s%s%s%s%d%d%d%f%s%s", &add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,&add.dob.year,&add.dob.month,&add.dob.day,&add.bal,add.credentials.username,add.credentials.password)!= EOF){
        if(del.accNo == add.accNo){
            system("CLS");
            success = 1;

        	gotoxy(15,5);
		    box(50, 10, 15, 5);
		    gotoxy(18,7);

            printf("Account Holder: %s %s", add.name, add.last);
            gotoxy(18,7);
			printf("Account No.: %d", add.accNo);
			gotoxy(18,8);
            printf("Y to CONTINUE :");
            fflush(stdin);
            input = getchar();

            if(input == 'y' || input == 'Y'){
                system("CLS");
			  	gotoxy(15, 4);
				box(50, 6, 15, 4);
				gotoxy(27, 6);
			    puts("** INFORMATION DELETED **");
			    gotoxy(25,7);
			    puts("Returning to the Main Menu...");
			    delay(10000);
            }else{
                system("CLS");
                gotoxy(15, 4);
				box(50, 6, 15, 4);
				gotoxy(27, 6);
                puts("Returning to the Main Menu...");
                fclose(oldrec);
                fclose(newrec);
                remove("newLoginInfo.TXT");
                rootUser();
            }
        }else{
            fprintf(newrec,"%d %s %s %s %s %s %s %s %d %d %d %f %s %s\n",add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,add.dob.year,add.dob.month,add.dob.day,add.bal,add.credentials.username,add.credentials.password);
        }

    }

    fclose(oldrec);
    fclose(newrec);
    remove("loginInfo.TXT");
    rename("newLoginInfo.TXT", "loginInfo.TXT");

    if(success == 0){
        system("CLS");

	  	gotoxy(15, 4);
		box(50, 6, 15, 4);
		gotoxy(27, 6);
	    printf("** RECORD NOT FOUND **");
	    gotoxy(25,7);
	    puts("Returning Back to the main menu...");
	    delay(10000);
	    rootUser();

    }else{
        rootUser();
    }
}

void view(){

  int input, b;
  FILE *fp;
  fp = fopen("loginInfo.TXT", "r");

  system("CLS");
  secBox("     VIEW USERS     ");
  gotoxy(4,2);
  printf("%-10s %15s %15s %15s    %-10s\n","A/C Number", "A/C Holder", "A/C Type", " Balance", "Contact No.");
  gotoxy(4,3);

  b = 4;

  while(fscanf(fp,"%d%s%s%s%s%s%s%s%d%d%d%f%s%s", &use.accNo,use.name,use.last,use.accType,use.gender,use.address.country,use.address.town,use.phone,&use.dob.year,&use.dob.month,&use.dob.day,&use.bal,use.credentials.username,use.credentials.password)!= EOF){
    printf("%10d %15s %15s %15.3f    %10s",use.accNo, use.name, use.accType, use.bal, use.phone);
    gotoxy(4, b++);
  }

  fclose(fp);

  do{
  	gotoxy(20,b);
    printf("Press \'1\' to return to Main Menu: ");
    scanf("%d", &input);
    fflush(stdin);
  }while(input != 1);

  if(input == 1){
    delay(5);
    rootUser();
  }

}

void search(){

  int status = 0;
  char exit_key;
  FILE *fp;
  fp = fopen("loginInfo.TXT", "r");

  system("CLS");
  secBox("       SEARCH     ");
  gotoxy(13, 5);
  box(55, 3, 13, 5);
  gotoxy(15, 6);
  printf("Input the Account name of the user: ");
  scanf("%s", use.name);

  while(fscanf(fp,"%d%s%s%s%s%s%s%s%d%d%d%f%s%s", &add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,&add.dob.year,&add.dob.month,&add.dob.day,&add.bal,add.credentials.username,add.credentials.password)!= EOF){
    if(strcmpi(add.name, use.name) == 0){
      status = 1;
      delay(10000);
      system("CLS");
      secBox("       SEARCH     ");
      gotoxy(30, 3);
      puts("** RECORD FOUND **");
      gotoxy(15,5);
      box(50, 10, 15, 5);
      gotoxy(18,6);
      printf("Account number: %d", add.accNo );
      gotoxy(18,7);
	  printf("Initial Balance: %.3f", add.bal);
	  gotoxy(18,8);
      printf("Account Number: %s", add.name);
      gotoxy(18,9);
      printf("Account Type: %s", add.accType);
      gotoxy(18,10);
      printf("Country: %s, %s", add.address.town, add.address.country);
      gotoxy(18,11);
      printf("Gender: %s", add.gender);
      gotoxy(18,12);
      printf("D.O.B.: %d-%d-%d", add.dob.year, add.dob.month, add.dob.day);
      gotoxy(18,13);
      printf("Contact Number: %s", add.phone);

	}

  }
  fclose(fp);

  if(status != 1){
  	system("CLS");
  	gotoxy(15, 4);
	box(50, 6, 15, 4);
	gotoxy(23, 6);
    printf("** RECORD NOT FOUND **");
  }
  delay(10000);
  gotoxy(20,16);
  printf("Press any key to return: ");
  fflush(stdin);
  exit_key = getch();

    rootUser();
  

}

void update(){

  int status = 0, input;

  FILE *oldrec, *newrec;

    oldrec = fopen("loginInfo.TXT","r");
    newrec = fopen("newLoginInfo.TXT","a");
	system("CLS");

	secBox("       UPDATE     ");
	  gotoxy(13, 5);
	  box(55, 3, 13, 5);
	  gotoxy(15, 6);

    printf("Enter the Account number of the user: ");
    scanf("%d",&upd.accNo);

  while(fscanf(oldrec,"%d%s%s%s%s%s%s%s%d%d%d%f%s%s", &add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,&add.dob.year,&add.dob.month,&add.dob.day,&add.bal,add.credentials.username,add.credentials.password) != EOF){
    if(add.accNo == upd.accNo){
      status = 1;
      delay(10000);

      input_again:
      system("CLS");
      secBox("       UPDATE     ");
      gotoxy(30, 3);
      puts("** RECORD FOUND **");
      gotoxy(15,5);
      box(50, 10, 15, 5);
      gotoxy(18,6);
      printf("Which information do you want to change? ");
      gotoxy(18,7);
      puts("1. Contact Info.");
      gotoxy(18,8);
	  puts("2. Address.");
	  gotoxy(18,9);
      puts("3. Date of Birth.");
      gotoxy(20,11);
      printf("INPUT: ");
      scanf("%d", &input);

      switch(input){
        case 1:
        	system("CLS");
        	gotoxy(15, 4);
            box(50, 8, 15, 4);
            gotoxy(22, 7);
          printf("Enter new Contact Number: ");
          scanf("%s", upd.phone);
          fprintf(newrec,"%d %s %s %s %s %s %s %s %d %d %d %f %s %s\n",add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,upd.phone,add.dob.year,add.dob.month,add.dob.day,add.bal,add.credentials.username,add.credentials.password);
          break;

        case 2:
        	system("CLS");
        	gotoxy(15, 4);
            box(50, 8, 15, 4);
            gotoxy(22, 7);
          puts("Enter new Address: ");
          gotoxy(22, 8);
          printf("Enter city: ");
          scanf("%s", upd.address.town);
          fprintf(newrec,"%d %s %s %s %s %s %s %s %d %d %d %f %s %s\n",add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,upd.address.town,add.phone,add.dob.year,add.dob.month,add.dob.day,add.bal,add.credentials.username,add.credentials.password);
          break;

        case 3:
        	system("CLS");
        	gotoxy(15,5);
		      box(50, 10, 15, 5);
		      gotoxy(18,6);
          puts("Date of Birth:.. ");
          gotoxy(18,8);
          printf("Enter Day: ");
          scanf("%d", &upd.dob.day);
          gotoxy(18,9);
          printf("Enter Month: ");
          scanf("%d", &upd.dob.month);
          gotoxy(18,10);
          printf("Enter Year: ");
          scanf("%d", &upd.dob.year);
          fprintf(newrec,"%d %s %s %s %s %s %s %s %d %d %d %f %s %s\n",add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,upd.dob.year,upd.dob.month,upd.dob.day,add.bal,add.credentials.username,add.credentials.password);
          break;

        default:
          puts("** ENTER A VALID INPUT **\a");
          delay(10000);
          goto input_again;
      }

    }else{
      fprintf(newrec,"%d %s %s %s %s %s %s %s %d %d %d %f %s %s\n",add.accNo,add.name,add.last,add.accType,add.gender,add.address.country,add.address.town,add.phone,add.dob.year,add.dob.month,add.dob.day,add.bal,add.credentials.username,add.credentials.password);
    }

  }
  fclose(oldrec);
  fclose(newrec);
  remove("loginInfo.TXT");
  rename("newLoginInfo.TXT", "loginInfo.TXT");

  if(status == 0){
   system("CLS");
  	gotoxy(15, 4);
	box(50, 6, 15, 4);
	gotoxy(27, 6);
    printf("** RECORD NOT FOUND **");
    gotoxy(25,7);
    puts("Returning Back to the main menu...");
    delay(10000);
    rootUser();
  }else{
  	system("CLS");
  	gotoxy(15, 4);
	box(50, 6, 15, 4);
	gotoxy(27, 6);
    puts("** INFORMATION UPDATED **");
    gotoxy(25,7);
    puts("Returning to the Main Menu...");
    delay(10000);
    rootUser();
  }

}

void loadingPage(){
    int a, i;

    gotoxy(22,7);
    puts("*********** NOW LOADING ***********");
    gotoxy(15, 9);
    box(50, 3, 15, 9);
    gotoxy(16,10);

    a= 16;
    for(i = 1; i < 50; i++){
        printf("\xB1");
        delay(100);
        gotoxy(a++, 10);
    }
}



void delay(unsigned int x){

    int i, j;
    x *= 10000;
    for(i = 0; i <= x; i++){
        j = i;
    }
}
