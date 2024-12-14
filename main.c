#include<stdio.h>
#include "functions.h"

int main()
{
    Address_Book book;
    if(Initialize(&book) != success)
    {
        printf("Failed to proceed further.  Try after sometime.  Sorry for the inconvenience...\n");
        return 0;
    }

    int choice;
    do
    {
        printf("Enter your choice:\n");
        printf("1-Create new address\n");
        printf("2-Edit the address\n");
        printf("3-Search address\n");
        printf("4-Delete address\n");
        printf("5-Display address\n");
        printf("6-Save and Exit\n");
        
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
        {
            if(add_address(&book) == success)
            {
                printf("Contact added sucessfully...\n");
            }
            else
            {
                printf("Failed to add contact...\n");
            }
            printf("-------------------------------------------------------------------\n");
            break;
        }
        case 2:
        {
            if(edit_address(&book) == success)
            {
                printf("Contact edited successfully...\n");
            }
            else
            {
                printf("Failed to edit contact...\n");
            }
            printf("-------------------------------------------------------------------\n");
            break;
        }
        case 3:
        {
            if(search_address(&book) == success)
            {
                printf("Contact found successfully...\n");
            }
            else
            {
                printf("Contact not found...\n");
            }
            printf("-------------------------------------------------------------------\n");
            break;
        }
        case 4:
        {
            if(delete_address(&book) == success)
            {
                printf("Contact deleted successfully.\n");
            }
            else
            {
                printf("Deletion process cancelled/invalid request...\n");
            }
            printf("-------------------------------------------------------------------\n");
            break;
        }
        case 5:
        {
            if(display_address(&book) == success)
            {
                printf("Contact displayed...\n");
            }
            else
            {
                printf("Contacts cannot displayed...\n");
            }
            printf("-------------------------------------------------------------------\n");
            break;
        }
        case 6:
        {
            if(save_and_exit(&book) == success)
            {
                printf("Saving and Exit...\n");
            }
            else
            {
                printf("Failed to save data..\n");
            }
            printf("-------------------------------------------------------------------\n");
            break;
        }           
        
        default:
        {
            printf("Invalid input.  Please enter the choice based on the displayed numbers\n");
            printf("-------------------------------------------------------------------\n");
            break;
        }

        }
    } while (choice !=6);
    

}