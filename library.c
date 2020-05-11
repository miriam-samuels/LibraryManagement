//created by Medo Miriam
// on 1st april 2020
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <direct.h>
#include <time.h>
#include <ctype.h>

void upd_bk();
void search_bk();
void view_bk();

char genre[][20] = {"action", "horror", "romance", "thriller", "drama", "slice of life", "sci-fi", "education"};

int s; //book genre
char findbook;
int getdata();
int check_id();
void staff_menu();
void user_menu();
void main_menu();
FILE *usr, *staf, *bks;

struct date
{
    int day;
    int month;
    int year;
};
struct fields
{
    char username[50];
};
struct field
{
    char name[60];
    char email[70];
    char password[20];
    char address[100];
    char genre[20];
    unsigned int number;
    struct fields staff;
    struct date reg;
} chk, upd;
struct field add;
struct books
{
    int id;
    char name[50];
    char author[30];
    int quantity;
    float price;
    int shelf_no;
    char *cat;
    struct date issue;
    struct date due;
};
struct books a;
COORD coord = {0, 0};
void gotoxy(short int x, short int y)
{
    //x and y coordinates
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void delay()
{
    for (int i = 0; i < 200000; i++)
    {
        /* code */
    }
}
void add_users()
{
    char choice[6];
    usr = fopen("users.txt", "a+");
    staf = fopen("staff.txt", "a+");
    printf("date(mm/dd/yyyy):\t");
    scanf("%d/%d/%d", &add.reg.month, &add.reg.day, &add.reg.year);
    printf("\nEnter your full name:\t");
    scanf("\n%s", add.name);
    //indicates if staff or user
    printf("staff or user:\t");
    scanf("%s", choice);
    if (strcmp("staff", choice) == 0)
    {
        printf("input staff id code as username:\t");
        scanf("%s", add.staff.username);
    }
    printf("enter a password:\t");
    scanf("%s", add.password);
    printf("Input your email address:\t");
    scanf("%s", add.email);
    printf("Input your phone number:\t");
    scanf("%d", &add.number);
    printf("Input your home address:\t");
    scanf("%s", add.address);

    if (strcmp("staff", choice) == 0)
    {
        fprintf(staf, "staff: date: %d/%d/%d \nname:%s \nusername(id code):%s \npassword:%s \nemail:%s \nphone number:%o \naddress:%s \n ", add.reg.month, add.reg.day, add.reg.year, add.name, add.staff.username, add.password, add.email, add.number, add.address);
        fclose(staf);
        printf("\naccount successfully created");
        system("cls");
        staff_menu();
    }

    else if (strcmp("user", choice) == 0)
    {
        fprintf(usr, "user: date: %d/%d/%d \nname:%s \npassword:%s \nemail:%s \nphone number:%o \naddress:%s \n", add.reg.month, add.reg.day, add.reg.year, add.name, add.password, add.email, add.number, add.address);
        fclose(usr);
        printf("\naccount successfully created");
        system("cls");
        user_menu();
    }
}
void upd_bk()
{
    system("cls");
    // int i;
    gotoxy(20, 5);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2SELECT GENRE\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(10, 7);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 1. Action");
    gotoxy(10, 9);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 2. Horror");
    gotoxy(10, 11);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 3. Romance");
    gotoxy(10, 13);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 4. Thriller");
    gotoxy(10, 15);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 5. Drama");
    gotoxy(10, 17);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 6. Slice of Life");
    gotoxy(10, 19);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 7. Sci_fi");
    gotoxy(10, 21);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 8. Education");
    gotoxy(10, 23);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 9. Return to main menu");
    gotoxy(10, 25);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
    gotoxy(10, 27);
    printf("Enter your choice:\t");
    scanf("%d", &s);
    if (s == 9)
    {
        staff_menu();
    }
    system("cls");
    bks = fopen("books.txt", "a+");
    if (getdata() == 1)
    {
        a.cat = genre[s - 1];
        fseek(bks, 0, SEEK_END);
        fwrite(&a, sizeof(a), 1, bks);
        fclose(bks);
        printf("\nThe record is successfully saved\n");
        printf("save any more (Y/N):\t");
        if (getch() == 'n')
        {
            staff_menu();
        }
        else
        {
            system("cls");
            upd_bk();
        }
    }
}
void usr_info()
{
    int i = 0, j = 4;
    usr = fopen("users.txt", "r");
    system("cls");
    gotoxy(2, 2);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Book List \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    while (fread(&add, sizeof(add), 1, usr) == 1)
    {
        gotoxy(3, j);
        printf("\xB2\xB2\xB2 Name:%s", add.name);
        gotoxy(15, j);
        printf("\xB2\xB2\xB2 Email:%s", add.email);
        gotoxy(32, j);
        printf("\xB2\xB2\xB2 Number:%o", add.number);
        gotoxy(47, j);
        printf("\xB2\xB2\xB2 Address:%s", add.address);
        gotoxy(65, j);
        printf("\xB2\xB2\xB2 Reg date:%d/%d/%d", add.reg.month, add.reg.day, add.reg.year);
        gotoxy(85, j);
        printf("\n\n");
        j++;
        i += add.number;
    }

    printf("\nTOTAL USERS: %d", i);
    fclose(usr);
    printf("HIT Enter KEY  ");
    main_menu();
}
void view_bk()
{
    int i = 0, j = 4;
    bks = fopen("books.txt", "r");
    system("cls");
    gotoxy(2, 2);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Book List \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    while (fread(&a, sizeof(a), 1, bks) == 1)
    {
        gotoxy(3, j);
        printf("\xB2\xB2\xB2 Book ID:%d", a.id);
        gotoxy(15, j);
        printf("\xB2\xB2\xB2 Genre:%s", a.cat);
        gotoxy(32, j);
        printf("\xB2\xB2\xB2 Name:%s", a.name);
        gotoxy(47, j);
        printf("\xB2\xB2\xB2 Author:%s", a.author);
        gotoxy(65, j);
        printf("\xB2\xB2\xB2 Quantity:%d", a.quantity);
        gotoxy(85, j);
        printf("\xB2\xB2\xB2 Price:%f", a.price);
        gotoxy(103, j);
        printf("\xB2\xB2\xB2 Shelf No:%d", a.shelf_no);
        printf("\n\n");
        j++;
        i += a.quantity;
    }

    printf("\nTOTAL BOOKS: %d", i);
    fclose(bks);
    printf("HIT enter key if staff and HIT space key if user");
    main_menu();
}
void search_bk()
{
    system("cls");
    int d;
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2SEARCH BOOK\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(15, 6);
    printf("\xB2\xB2\xB2\xB2\xB2 1. Search by ID");
    gotoxy(15, 10);
    printf("\xB2\xB2\xB2\xB2\xB2 2. Search by Name");
    gotoxy(10, 14);
    printf("\xB2\xB2\xB2\xB2\xB2 Enter your choice");
    bks = fopen("books.txt", "r");
    rewind(bks);
    switch (getch())
    {
    case '1':
    {
        system("cls");
        gotoxy(20, 4);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2SEARCH BY ID\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(15, 6);
        printf("\xB2\xB2\xB2\xB2\xB2 1. Enter book ID");
        scanf("%d", &d);
        gotoxy(15, 9);
        printf("searching........................");
        while (fread(&a, sizeof(a), 1, bks) == 1)
        {
            if (a.id == d)
            {
                //delay
                gotoxy(10, 11);
                printf("\xB2\xB2\xB2 Book ID:%d", a.id);
                gotoxy(10, 12);
                printf("\xB2\xB2\xB2 Genre:%s", a.cat);
                gotoxy(10, 13);
                printf("\xB2\xB2\xB2 Name:%s", a.name);
                gotoxy(10, 14);
                printf("\xB2\xB2\xB2 Author:%s", a.author);
                gotoxy(10, 15);
                printf("\xB2\xB2\xB2 Quantity:%d", a.quantity);
                gotoxy(10, 16);
                printf("\xB2\xB2\xB2 Price:%f", a.price);
                gotoxy(10, 17);
                printf("\xB2\xB2\xB2 Shelf No:%d", a.shelf_no);
                findbook = 't';
            }
        }
        if (findbook != 't')
        {
            gotoxy(10, 12);
            printf("no record found. Modify the search?, (Y/N)");
            if (getch() == 'y')
            {
                search_bk();
            }
            else
            {
                //delay
                printf("HIT enter key if staff and HIT space key if user");
                main_menu();
            }
        }
    }
    break;
    case '2':
    {
        char bk[50];
        int d = 0;
        system("cls");
        gotoxy(20, 4);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2SEARCH BY NAME\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(20, 6);
        printf("Enter book name");
        scanf("%s", bk);
        printf("searching........................");
        while (fread(&a, sizeof(a), 1, bks) == 1)
        {
            if (strcmp(a.name, bk) == 0)
            {
                //delay
                gotoxy(10, 11);
                printf("\xB2\xB2\xB2 Book ID:%d", a.id);
                gotoxy(10, 12);
                printf("\xB2\xB2\xB2 Genre:%s", a.cat);
                gotoxy(10, 13);
                printf("\xB2\xB2\xB2 Name:%s", a.name);
                gotoxy(10, 14);
                printf("\xB2\xB2\xB2 Author:%s", a.author);
                gotoxy(10, 15);
                printf("\xB2\xB2\xB2 Quantity:%d", a.quantity);
                gotoxy(10, 16);
                printf("\xB2\xB2\xB2 Price:%f", a.price);
                gotoxy(10, 17);
                printf("\xB2\xB2\xB2 Shelf No:%d", a.shelf_no);
                d++;
            }
            if (d == 0)
            {
                gotoxy(10, 19);
                printf("no record found. Modify the search?, (Y/N)");
                if (getch() == 'y')
                {
                    search_bk();
                }
                else
                {
                    //delay
                    printf("HIT enter key if staff and HIT space key if user");
                    main_menu();
                }
            }
        }
    }
    break;
    }

    fclose(bks);
}
void issue_bk()
{
}
void query_usr()
{
}
void upd_info()
{
}
void logout()
{
    system("cls");
    printf("thank you for using our services");
}
/*
===============================
info on book
===============================
 */
int getdata()
{
    int bk_id;
    gotoxy(20, 2);
    printf("Enter the information below");
    gotoxy(15, 4);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(18, 6);
    printf("Genre:\t");
    printf("%s", genre[s - 1]);
    gotoxy(18, 7);
    printf("Book ID:\t");
    scanf("%d", &bk_id);
    if (check_id(bk_id) == 0)
    {
        gotoxy(18, 9);
        printf("\a The book already exists");
        getch();
        staff_menu();
        return 0;
    }
    a.id = bk_id;
    system("cls");
    gotoxy(15, 2);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(18, 4);
    printf("Book name:\t");
    scanf("%s", a.name);
    gotoxy(18, 5);
    printf("Author:\t");
    scanf("%s", a.author);
    gotoxy(18, 6);
    printf("Quantity:\t");
    scanf("%d", &a.quantity);
    gotoxy(18, 7);
    printf("Price:\t");
    scanf("%f", &a.price); // come back
    gotoxy(18, 8);
    printf("shelf no:\t");
    scanf("%d", &a.shelf_no);
    fprintf(bks, "\nBook id: %d\nname:%s \nauthor:%s \ngenre:%s \nquantity:%d \nprice:%f \nshelf_no:%d \n", a.id, a.name, a.author, genre[s - 1], a.quantity, a.price, a.shelf_no);
    return 1;
}
/*
======================================
check book id  for existence
=====================================
 */
int check_id(int bk_id)
{
    rewind(bks);
    while (fread(&a, sizeof(a), 1, bks) == 1)
    {
        if (a.id == bk_id)
        {
            return 0; //bk exists
        }
    }
    return 1; //bk no exists
}

void staff_menu()
{
    int choice;
    system("cls");
    gotoxy(15, 3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2How can we help you\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(8, 5);
    printf("\n1.check user info\n2.view book\n3.issue book\n4.update book\n5.query user\n6.update profile info\n7.search book\n8.log out\n\n Enter your choice:\t");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        usr_info();
        break;
    case 2:
        view_bk();
        break;
    case 3:
        issue_bk();
        break;
    case 4:
        upd_bk();
        break;
    case 5:
        query_usr();
        break;
    case 6:
        upd_info();
        break;
    case 7:
        search_bk();
        break;
    case 8:
        logout();
        break;
    default:
        printf("please select a valid option");
        main_menu();
    }
}
void user_menu()
{
    int choice;
    system("cls");
    gotoxy(15, 3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2How can we help you\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(8, 5);
    printf("\n1.view books\n2.issue book\n3.update profile info\n4.search book\n5.logout");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        view_bk();
        break;
    case 2:
        issue_bk();
        break;
    case 3:
        upd_info();
        break;
    case 4:
        search_bk();
        break;
    case 5:
        logout();
        break;
    default:
        printf("please select a valid option");
        main_menu();
    }
}

void main_menu()
{
a:
    if (getch() == 13)
    {
        staff_menu();
    }
    else if (getch() == 32)
    {
        user_menu();
    }
    else
    {
        goto a;
    }
}
void staff_in()
{
    int choice;
    // login:
    system("cls");
    gotoxy(15, 3);
    printf("\t\t\t\xB2\xB2\xB2\xB2\tWELCOME\t\xB2\xB2\xB2\xB2\n");
    gotoxy(15, 5);
    printf("Do you want to\n 1.open an account \n 2.login\n\n Enter your choice:");
    scanf("%d", &choice);
    if (choice == 1)
    {
        add_users();
    }
    else if (choice == 2)
    {
        staf = fopen("staff.txt", "a+");
        system("cls");
        printf("\nEnter username: ");
        scanf("%s", chk.staff.username);
        printf("\n please input your password: ");
        scanf("%s", chk.password);
        staff_menu();
    }
}
void user_in()
{
    int choice;
    // login:
    system("cls");
    printf("\t\t\t\xB2\xB2\xB2\xB2\tWELCOME\t\xB2\xB2\xB2\xB2\n");
    printf("Do you want to\n 1.open an account \n 2.login\n\n Enter your choice:  ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        add_users();
    }
    else if (choice == 2)
    {
        usr = fopen("users.txt", "a+");
        system("cls");
        printf("\nEnter email: ");
        scanf("%s", chk.email);
        printf("\n please input your password: ");
        scanf("%s", chk.password);
        user_menu();
    }
}
int main()
{
    char choice[6];
signin_option:
    system("cls");
    gotoxy(15, 2);
    printf("\t\t\t\t\xb2\xb2\xb2\xb2\xb2\xb2\t Hi, good day\t\xb2\xb2\xb2\xb2\xb2\xb2");
    gotoxy(8, 5);
    printf("\n\n staff or user:\t  ");
    scanf("%s", choice);
    if (strcmp("staff", choice) == 0)
    {
        staff_in();
    }
    else if (strcmp("user", choice) == 0)
    {
        user_in();
    }
    else
    {
        printf("please enter a valid option");
        delay();
        goto signin_option;
    }
}
