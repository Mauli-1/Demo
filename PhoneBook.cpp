#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contact {
    char fname[15];
    char lname[15];
    char mobile_no[15];
    char tag[15];
};
typedef struct contact contact;

void press_to_continue() {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
    getchar();
}

void toLower(char *s) {
    while (*s) {
        if (*s >= 'A' && *s <= 'Z')
            *s = *s + 32;
        s++;
    }
}

void add_contact() {
    system("cls");
    FILE *fptr;
    contact cn;

    fptr = fopen("PhoneBook.dat","ab");

    printf("\n<Fill details>\n");

    printf("Enter First Name : ");
    scanf("%14s", cn.fname);

    printf("Enter last Name : ");
    scanf("%14s", cn.lname);

    printf("\nEnter Mobile Number : ");
    scanf("%14s", cn.mobile_no);

    printf("\nEnter Tag(Enter 'Other' for nothing) : ");
    scanf("%14s", cn.tag);

    fwrite(&cn, sizeof(contact), 1, fptr);

    fclose(fptr);
    press_to_continue();
    system("cls");
}

int directory_info() {
    FILE *fptr = fopen("PhoneBook.dat", "rb");
    if (!fptr) return 0;

    fseek(fptr, 0, SEEK_END);
    return ftell(fptr) / sizeof(contact);
}

int tag_info(char tag[]) {
    int num = 0;
    FILE *fptr;
    contact cn;
    fptr = fopen("PhoneBook.dat", "rb");
    if (!fptr) return 0;

    while (fread(&cn, sizeof(contact), 1, fptr)) {
        char t1[15], t2[15];
        strcpy(t1, cn.tag);
        strcpy(t2, tag);
        toLower(t1);
        toLower(t2);

        if (strcmp(t1, t2) == 0)
            num++;
    }
    fclose(fptr);
    return num;
}

void display() {
    system("cls");
    FILE *fptr = fopen("PhoneBook.dat", "rb");
    if (!fptr) { printf("No contacts found!"); press_to_continue(); return; }

    contact cn;
    int mode, count = 1, i, n;

    printf("1 : View by Time Created (Ascending)\n");
    printf("2 : View by Time Created (Descending)\n");
    printf("Choose Display Mode : ");
    scanf("%d", &mode);

    n = directory_info();
    printf("---------------------------------------------------------------------\n");
    printf("|Total Number of contacts : %2d                                      |\n", n);
    printf("---------------------------------------------------------------------");
    printf("\n|%-3s| %-15s%-15s%-20s%-12s|\n", "Sno", "First Name", "Last Name", "Contact Number", "Tag");
    printf("---------------------------------------------------------------------");

    if (mode == 1) {
        while (fread(&cn, sizeof(contact), 1, fptr))
            printf("\n|%-3d| %-15s%-15s%-20s%-12s|", count++, cn.fname, cn.lname, cn.mobile_no, cn.tag);
    } else if (mode == 2) {
        fseek(fptr, -sizeof(contact), SEEK_END);
        for (i = 1; i <= n; i++) {
            fread(&cn, sizeof(contact), 1, fptr);
            printf("\n|%-3d| %-15s%-15s%-20s%-12s|", count++, cn.fname, cn.lname, cn.mobile_no, cn.tag);
            fseek(fptr, -2 * sizeof(contact), SEEK_CUR);
        }
    } else {
        printf("\nInvalid Selection!");
    }

    printf("\n---------------------------------------------------------------------\n");
    fclose(fptr);
    press_to_continue();
    system("cls");
}

void display_by_tag() {
    system("cls");
    FILE *fptr = fopen("PhoneBook.dat", "rb");
    if (!fptr) { printf("No contacts found!"); press_to_continue(); return; }

    char tag[20];
    contact cn;
    int count = 1, n;

    printf("Enter Tag : ");
    scanf("%19s", tag);

    n = tag_info(tag);

    printf("---------------------------------------------------------------------\n");
    printf("|Total Number of contacts : %2d                                      |\n", n);
    printf("---------------------------------------------------------------------");
    printf("\n|%-3s| %-15s%-15s%-20s%-12s|\n", "Sno", "First Name", "Last Name", "Contact Number", "Tag");
    printf("---------------------------------------------------------------------");

    while (fread(&cn, sizeof(contact), 1, fptr)) {
        char t1[15], t2[15];
        strcpy(t1, cn.tag);
        strcpy(t2, tag);
        toLower(t1);
        toLower(t2);

        if (strcmp(t1, t2) == 0)
            printf("\n|%-3d| %-15s%-15s%-20s%-12s|", count++, cn.fname, cn.lname, cn.mobile_no, cn.tag);
    }

    printf("\n---------------------------------------------------------------------\n");
    fclose(fptr);
    press_to_continue();
    system("cls");
}

void modify_contact() {
    system("cls");
    FILE *fptr = fopen("PhoneBook.dat", "rb");
    FILE *fptr1 = fopen("helper.dat", "wb");
    if (!fptr || !fptr1) return;

    contact cn;
    char fname[15], lname[15], modify;
    int found = 0;

    printf("Enter First name: ");
    scanf("%14s", fname);
    printf("Enter Last name: ");
    scanf("%14s", lname);

    while (fread(&cn, sizeof(contact), 1, fptr)) {
        char fn[15], ln[15];
        strcpy(fn, cn.fname);
        strcpy(ln, cn.lname);
        toLower(fn); toLower(ln);
        toLower(fname); toLower(lname);

        if (strcmp(fn, fname) == 0 && strcmp(ln, lname) == 0) {
            found = 1;

            printf("\nModify First Name?<y/n> : ");
            scanf(" %c", &modify);
            if (modify == 'y' || modify == 'Y')
                scanf("%14s", cn.fname);

            printf("\nModify Last Name?<y/n> : ");
            scanf(" %c", &modify);
            if (modify == 'y' || modify == 'Y')
                scanf("%14s", cn.lname);

            printf("\nModify Mobile Number? <y/n> : ");
            scanf(" %c", &modify);
            if (modify == 'y' || modify == 'Y')
                scanf("%14s", cn.mobile_no);

            printf("\nModify Tag? <y/n> : ");
            scanf(" %c", &modify);
            if (modify == 'y' || modify == 'Y')
                scanf("%14s", cn.tag);
        }
        fwrite(&cn, sizeof(contact), 1, fptr1);
    }

    fclose(fptr);
    fclose(fptr1);

    if (found) {
        fptr1 = fopen("helper.dat", "rb");
        fptr = fopen("PhoneBook.dat", "wb");

        while (fread(&cn, sizeof(contact), 1, fptr1))
            fwrite(&cn, sizeof(contact), 1, fptr);

        printf("\nContact Modified Successfully\n");
    } else {
        printf("Contact not found");
    }

    fclose(fptr);
    fclose(fptr1);
    press_to_continue();
    system("cls");
}

void search_contact() {
    system("cls");
    FILE *fp = fopen("PhoneBook.dat", "rb");
    if (!fp) { printf("Error opening file"); press_to_continue(); return; }

    contact cn;
    int c, flag = 0;

    printf("\n1. Search by name\n2. Search by Phone number\nEnter your choice : ");
    scanf("%d", &c);

    if (c == 1) {
        char fname[15], lname[15];

        printf("Enter first name : ");
        scanf("%14s", fname);
        printf("Enter last name : ");
        scanf("%14s", lname);

        while (fread(&cn, sizeof(cn), 1, fp)) {
            char fn[15], ln[15];
            strcpy(fn, cn.fname);
            strcpy(ln, cn.lname);
            toLower(fn); toLower(ln);
            toLower(fname); toLower(lname);

            if (strcmp(fn, fname) == 0 && strcmp(ln, lname) == 0) {
                flag = 1;
                printf("\nFound Contact:\n");
                printf("---------------------------------------------------------------------\n");
                printf("|%-15s%-15s%-20s%-12s|\n", cn.fname, cn.lname, cn.mobile_no, cn.tag);
                break;
            }
        }
    } else if (c == 2) {
        char phone[15];

        printf("Enter phone number to search: ");
        scanf("%14s", phone);

        while (fread(&cn, sizeof(cn), 1, fp)) {
            if (strcmp(phone, cn.mobile_no) == 0) {
                flag = 1;
                printf("\nFound Contact:\n");
                printf("---------------------------------------------------------------------\n");
                printf("|%-15s%-15s%-20s%-12s|\n", cn.fname, cn.lname, cn.mobile_no, cn.tag);
                break;
            }
        }
    } else {
        printf("Wrong choice!");
    }

    if (!flag) printf("\nSearch not found\n");

    fclose(fp);
    press_to_continue();
    system("cls");
}

void delete_contact() {
    contact cn;
    FILE *fptr = fopen("PhoneBook.dat", "rb");
    FILE *fptr1 = fopen("helper.dat", "wb");
    if (!fptr || !fptr1) return;

    int choice, flag = 0;
    system("cls");

    printf("1.Deletion through mobile number\n2.Deletion through name\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        char mobile_no[15];

        printf("Enter CONTACT's mobile_no: ");
        scanf("%14s", mobile_no);

        while (fread(&cn, sizeof(cn), 1, fptr)) {
            if (strcmp(mobile_no, cn.mobile_no) != 0)
                fwrite(&cn, sizeof(cn), 1, fptr1);
            else flag = 1;
        }
    } else if (choice == 2) {
        char fname[15], lname[15];

        printf("Enter CONTACT's fname: ");
        scanf("%14s", fname);
        printf("Enter CONTACT's lname: ");
        scanf("%14s", lname);

        while (fread(&cn, sizeof(cn), 1, fptr)) {
            char fn[15], ln[15];
            strcpy(fn, cn.fname);
            strcpy(ln, cn.lname);

            toLower(fn); toLower(ln);
            toLower(fname); toLower(lname);

            if (!(strcmp(fn, fname) == 0 && strcmp(ln, lname) == 0))
                fwrite(&cn, sizeof(cn), 1, fptr1);
            else flag = 1;
        }
    }

    fclose(fptr);
    fclose(fptr1);

    if (!flag) {
        printf("NO CONTACT'S RECORD TO DELETE!\n");
    } else {
        fptr1 = fopen("helper.dat", "rb");
        fptr = fopen("PhoneBook.dat", "wb");

        while (fread(&cn, sizeof(contact), 1, fptr1))
            fwrite(&cn, sizeof(contact), 1, fptr);

        printf("\nContact Deleted Successfully\n");
    }

    fclose(fptr1);
    fclose(fptr);
    press_to_continue();
    system("cls");
}

int main() {
    int operation = 1;

    while (operation) {
        printf("\n1 : Create Contact\n");
        printf("2 : Display Directory\n");
        printf("3 : Display by tags\n");
        printf("4 : Modify Contact\n");
        printf("5 : Search Contact\n");
        printf("6 : Delete Contact\n");
        printf("7 : Exit Program\n");
        printf("\nChoose Operation : ");

        scanf("%d", &operation);

        switch (operation) {
            case 1: add_contact(); break;
            case 2: display(); break;
            case 3: display_by_tag(); break;
            case 4: modify_contact(); break;
            case 5: search_contact(); break;
            case 6: delete_contact(); break;
            case 7: exit(0);
            default:
                printf("\nInvalid Operation !!");
                press_to_continue();
                system("cls");
        }
    }

    return 0;
}
