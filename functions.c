/*File consist of all executable function to handle address book program.*/

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "functions.h"
#include "types.h"

/*Function to open the file for reading purpose only*/
Status open_read_files(Address_Book *book)
{
    
    book->fbook_file = fopen(book->book_data, "r+");
    
    if (book->fbook_file == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", book->book_data);
    	return failure;
    }
    return success;
}

/*Function to trim the extra space in the fetch strings.*/
void trim_read_string(char *str)
{
    int len = strlen(str);    

    while (len > 0 && isspace((unsigned char)str[len - 1])) 
    {
        str[len - 1] = '\0'; 
        len--;
    }
}


/*Function to read the data from the address book file.*/
Status read_addresses_from_file(Address_Book *book) 
{    
    char line[256];  
    int temp;

    while (fgets(line, sizeof(line), book->fbook_file)) //Loop over line by line
    {
        
        if (line[0] == '-' || !isdigit(line[0]) || line[0] == '>')  //Condition to skip header and footer lines
        {
            continue;
        }
        sscanf(line, "%d %20[^\n] %15ld %30[^\n]", &temp, book->det[book->count].name, &book->det[book->count].number,  book->det[book->count].email);
      
        trim_read_string(book->det[book->count].name);    //trim the extra spaces
        trim_read_string(book->det[book->count].email);
        
        book->count++;  //Increasing the count of the contacts.
    }
    
    fclose(book->fbook_file);
    return success;
}

/*Function to open and write the address book file*/
Status open_write_files(Address_Book *book)  
{
    book->fbook_file = fopen(book->book_data, "w+");
    
    if (book->fbook_file == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", book->book_data);
    	return failure;
    }
    return success;

}


/*Initialize the program by reading the existing contacts in the address book.*/
Status Initialize(Address_Book *book)
{
    book -> count=0;
    book->book_data = ADDRESSBOOK ;
    if(open_read_files(book) == success)
    {
        if(read_addresses_from_file(book) == success)
        {
            return success;
        }
        //populate_dummy_contacts(book);
        
    }
    return failure;
    
}

/*Function to identify the duplicate phone number*/
Status duplicate_phone(long int num, Address_Book *book)
{
    for(int i=0; i<book->count;i++)
    {
        if(book->det[i].number == num)
        {
            printf("The provided contact number already existing. User name with the same number: %s\n",book->det[i].name);
            return failure;              
        }                   
    }
    return success; 

}

/*Function to identify the duplicate mail id*/
Status duplicate_email(char *email, Address_Book *book)
{
    for(int i=0; i<book->count;i++)
    {
        if(!(strcmp(book->det[i].email,email)))
        {
            printf("The provided email already existing. User name with the same number: %s\n",book->det[i].name);
            return failure;             
        }            
    }
    return success;

}

/*Function to validate the email*/
Status email_validation(char *email)
{
    if(strcmp(email + strlen(email) - 4, ".com") != 0)  //condition to check the extension of the mail
    {
        printf("Invalid mail format provide.\n");
        return failure;
    }    
    int atcount = 0;

    if(*email == '@')  //condition to validate whether @ not exist in the first character
    {
        printf("Invalid mail format provide.\n");
        return failure;
    }
    while (*email) 
    {
        if (*email == '@') 
        {
            atcount++;
            if(atcount>1)  //Mail should only have one @ symbol
            {
                
                printf("Invalid mail format provide.\n");
                return failure;
            }
        }        
        email++;
    }

    if(atcount !=1 )   //condition to validate whether @ is exist in the provided mail and it exist only once
    {
        printf("Invalid mail format provide.\n");
        return failure;
    }
    return success;

}

/*Function to validate the phone number*/
Status phone_validation(long int num)
{
    char num_str[50];
    sprintf(num_str, "%ld" , num);
    
    if(strlen(num_str) != 10)  //Condition to check the number is having 10 digits
    {
        printf("Invalid phone number format provided.\n");
        return failure;        
    }
    for(int i=0; i<strlen(num_str); i++)  //Loop over the numbers and check it has only digits
    {    
        if (!isdigit(num_str[i])) 
        {
            printf("Invalid phone number format provided.\n");
            return failure;  
        }        
    }
    return success;   
}

/*Function to add new address information*/
Status add_address(Address_Book *book)
{
    char temp_name[50];
    long int temp_num;
    char temp_mail[50];

    printf("Enter the Name: ");
    scanf(" %[^\n]",temp_name);
    printf("Enter the Number: ");
    scanf("%ld",&temp_num);
    printf("Enter the Email: ");
    scanf(" %[^\n]",temp_mail);
    
    if(phone_validation(temp_num) == success && email_validation(temp_mail) == success
    && duplicate_phone(temp_num, book) == success   && duplicate_email(temp_mail, book) == success)  //Validation checks of phone number and email
    {
        strcpy(book->det[book->count].name,temp_name);       //Storing in the structure
        strcpy(book->det[book->count].email, temp_mail);
        book->det[book->count].number=temp_num;
        book->count++;
        
    }
    else
    {
        return failure;
    }
    return success;    
}

/*Function to edit the address in the structure*/
Status edit_address(Address_Book *book)
{
    int index, choose; 
    display_address(book);                         //Display the exiting address in the structure  
    printf("Enter the contact index to edit: ");   //Get index of the user information to be edited
    scanf("%d",&index);

    if(index<=0 || index > book->count)           //Check for invalid index
    {
        printf("Invalid index number provided to edit.\n");
        return failure;
    }

    printf("Enter the data to be edited on the index\n");
    printf("1-Edit Name\n");
    printf("2-Edit Number\n");
    printf("3-Edit mail\n");
    printf("4-Edit Name and Number\n");
    printf("5-Edit Name and Email\n");
    printf("6-Edit Number and Email\n");
    printf("7-Edit Name, Number and Email\n");

    scanf("%d",&choose);  //Get the type of edit the user want to perform

    switch (choose)    
    {
    case 1: //Edit name
    {
        char edit[50];
        printf("Enter the Name to edit: ");
        scanf(" %[^\n]",edit);
        strcpy(book->det[index-1].name,edit);        
        break;
    }
    case 2: //Edit number
    {
        long int edit;
        
        printf("Enter the Number: ");
        scanf("%ld",&edit);

        if(duplicate_phone(edit, book) == success && phone_validation(edit) == success)
        {
            book->det[index-1].number = edit;
        }
        else
        {
            return failure;
        }        
        break;
    }
    case 3: //Edit mail
    {
        char edit[50];
        
        printf("Enter the Email: ");
        scanf(" %[^\n]",edit);

        if(duplicate_email(edit, book) == success && email_validation(edit) == success)
        {
            strcpy(book->det[index-1].email,edit);
        }
        else
        {
            return failure;
        }
        
        break;
    }
    case 4: //Edit name and number
    {
        long int edit_num;
        char edit_name[50];
        
        printf("Enter the Name to edit: ");
        scanf(" %[^\n]",edit_name);
        
        
        printf("Enter the Number: ");
        scanf("%ld",&edit_num);
        
        if(duplicate_phone(edit_num, book) == success && phone_validation(edit_num) == success)
        {
            strcpy(book->det[index-1].name,edit_name);
            book->det[index-1].number = edit_num;
        }
        else
        {
            return failure;
        }
        
        break;
    }
    case 5: //Edit name and mail
    {
        char edit_mail[50];
        char edit_name[50];
        
        printf("Enter the Name to edit: ");
        scanf(" %[^\n]",edit_name);
        
        
        printf("Enter the Email: ");
        scanf(" %[^\n]",edit_mail);
        
        if(duplicate_email(edit_mail, book) == success && email_validation(edit_mail) == success)
        {
            strcpy(book->det[index-1].name,edit_name);
            strcpy(book->det[index-1].email,edit_mail);
        }
        else
        {
            return failure;
        }
        
        break;
    }

    case 6: //edit mail and number
    {
        long int edit_num;
        char edit_mail[50];
        
        printf("Enter the Number: ");
        scanf("%ld",&edit_num);

        printf("Enter the mail to edit: ");
        scanf(" %[^\n]",edit_mail);
        
        if(duplicate_phone(edit_num, book) == success && phone_validation(edit_num) == success && duplicate_email(edit_mail, book) == success && email_validation(edit_mail) == success)
        {
            strcpy(book->det[index-1].email,edit_mail);
            book->det[index-1].number = edit_num;
        }
        else
        {
            return failure;
        }
        
        break;
    }
    case 7: //Edit all details
    {
        long int edit_num;
        char edit_mail[50];
        char edit_name[50];
        
        printf("Enter the Name to edit: ");
        scanf(" %[^\n]",edit_name);
        
        printf("Enter the Number: ");
        scanf("%ld",&edit_num);

        printf("Enter the mail to edit: ");
        scanf(" %[^\n]",edit_mail);
        
        if(duplicate_phone(edit_num, book) == success && phone_validation(edit_num) == success && duplicate_email(edit_mail, book) == success && email_validation(edit_mail) == success)
        {
            strcpy(book->det[index-1].email,edit_mail);
            book->det[index-1].number = edit_num;
            strcpy(book->det[index-1].name,edit_name);
        }
        else
        {
            return failure;
        }
        
        break;
    }

    default:  //For invalid choice of request
    {
        printf("Invalid choice of edit.  Redirecting...\n");
        return failure;
        break;
    }
    }
    return success;
}

/*Function to print the address book in the structure*/
Status display_address(Address_Book *book)
{
    
    printf(">>>>>>>>>>>>>>>>>>>>>>> ADDRESS BOOK <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");  //Headers
    printf("-------------------------------------------------------------------\n");
    printf("%-5s %-20s %-15s %-30s\n", "No.", "Name", "Number", "Email");
    printf("-------------------------------------------------------------------\n");
    
    for (int i = 0; i < book->count; i++) 
    {
        printf("%-5d %-20s %-15ld %-30s\n", i + 1, book->det[i].name, book->det[i].number, book->det[i].email);  //Data
    }
    printf("-------------------------------------------------------------------\n");
    return success;
}

/*Function to search address from the structure*/
Status search_address(Address_Book *book)
{
    int choose;    
    printf("Enter the choice of search:\n");
    printf("1-search using Name\n");
    printf("2-search using Number\n");
    printf("3-seach using mail\n");
    scanf("%d",&choose);    
    switch (choose)    
    {
    case 1: //Search by name
    {
        char search[50];
        char temp[50];
        int foundflg =0;

        printf("Enter the Name: ");
        scanf(" %[^\n]",search);

        for(int i=0; i<book->count; i++)
        {
            
        }
        for(int i=0; i<book->count;i++)
        {
            //printf("%s e :: %s e\n",book->det[i].name, search);
            if(!strcmp(book->det[i].name,search))
            {
                printf("-------------------------------------------------------------------\n");
                printf("%-5s %-20s %-15s %-30s\n", "No.", "Name", "Number", "Email");
                printf("%-5d %-20s %-15ld %-30s\n", i + 1, book->det[i].name, book->det[i].number, book->det[i].email);
                printf("-------------------------------------------------------------------\n");
                foundflg=1;              
            }            
        }
        if(!foundflg)
        {            
            return failure;
        } 
        return success;       
        break;
    }
    case 2: //Search by number
    {
        long int search;
        int foundflg =0;
        printf("Enter the Number: ");
        scanf("%ld",&search);
        for(int i=0; i<book->count;i++)
        {
            if(book->det[i].number == search)
            {
                printf("-------------------------------------------------------------------\n");
                printf("%-5s %-20s %-15s %-30s\n", "No.", "Name", "Number", "Email");
                printf("%-5d %-20s %-15ld %-30s\n", i + 1, book->det[i].name, book->det[i].number, book->det[i].email);
                printf("-------------------------------------------------------------------\n");
                foundflg=1;              
            }            
        }
        if(!foundflg)
        {
            return failure;
        }
        break;
    }
    case 3: //Search by mail
    {
        char search[50];
        int foundflg =0;
        printf("Enter the Email: ");
        scanf(" %[^\n]",search);
        
        for(int i=0; i<book->count;i++)
        {
            
            if(!strcmp(book->det[i].email,search))
            {
                printf("-------------------------------------------------------------------\n");
                printf("%-5s %-20s %-15s %-30s\n", "No.", "Name", "Number", "Email");
                printf("%-5d %-20s %-15ld %-30s\n", i + 1, book->det[i].name, book->det[i].number, book->det[i].email);
                printf("-------------------------------------------------------------------\n");
                foundflg=1;              
            }            
        }
        if(!foundflg)
        {
            return failure;
        }
        break;
    }
    default:
    {
        printf("Invalid choice of search.  Redirecting...\n");
        return failure;
        break;
    }
    }
    return success;
}

/*Function to delete a address*/
Status delete_address(Address_Book *book)
{
    display_address(book);
    int index = 0;
    char confrm;
    printf("Enter the index of the contact to be deleted: ");
    scanf("%d",&index);  //Get index of the data

    if(index > book->count || index <= 0) //Validate the index
    {
        printf("Invalid index number provided to delete.\n");
        return failure;
    }

    printf("\nAre you sure you want to delete the contact? (Y/N) :");  //Get confirmation to delete
    scanf(" %c",&confrm);
    if(confrm == 'Y' || confrm == 'y')
    {
        for (int i = index - 1; i < book->count - 1; i++) 
        {
            strcpy(book->det[i].name, book->det[i+1].name);    //Replace the deleted data with the following contacts in the book
            strcpy(book->det[i].email, book->det[i+1].email);
            book->det[i].number=book->det[i+1].number;
        }

        book->count--;        //Reduce the count of the book
    }
    else
    {
        printf("Deletion process cancelled.\n");
        return failure;
    }
    return success;
}

/*Function to save the data in the address book file from the structure*/
Status save_and_exit(Address_Book *book)
{
    if(open_write_files(book) == success)
    {
        fprintf(book->fbook_file,">>>>>>>>>>>>>>>>>>>>>>> ADDRESS BOOK <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        fprintf(book->fbook_file,"-------------------------------------------------------------------\n");
        fprintf(book->fbook_file, "%-5s %-20s %-15s %-30s\n", "No.", "Name", "Number", "Email");
        fprintf(book->fbook_file,"-------------------------------------------------------------------\n");
        for (int i = 0; i < book->count; i++) 
        {
            fprintf(book->fbook_file, "%-5d %-20s %-15ld %-30s\n", i + 1, book->det[i].name, book->det[i].number, book->det[i].email);
        }
        fprintf(book->fbook_file,"-------------------------------------------------------------------\n");
        fclose(book->fbook_file);
    }
    else
    {
        return failure;
    }

    return success;    
}