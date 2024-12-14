#ifndef CONTACT_H
#define CONTACT_H
#include "types.h"

#define MAX_CONTACT 100
typedef struct  
{
    char name[50];
    long int number;
    char email[50];
}Contacts;

typedef struct 
{
    Contacts det[MAX_CONTACT];
    int count;
    char *book_data ;
    FILE *fbook_file;
}Address_Book;



/*Initializing contacts*/
Status Initialize(Address_Book *book);

/*Open file contact book for reading*/
Status open_read_files(Address_Book *book);

/*Open file contact book for writing*/
Status open_write_files(Address_Book *book);

/*Read data from the file*/
Status read_addresses_from_file(Address_Book *book);

/*To remove the trialing space in the fetched value*/
void trim_read_string(char *str);

/*Write data to the file*/
Status save_and_exit(Address_Book *book);

/*Initializing with dummy contacts*/
void populate_dummy_contacts(Address_Book *book);

/*Duplicate check of email*/
Status duplicate_email(char *email, Address_Book *book);

/*Duplicate check of phone*/
Status duplicate_phone(long int num, Address_Book *book);

/*Function to add new address*/
Status add_address(Address_Book *book);

/*Edit address*/
Status edit_address(Address_Book *book);

/*For validating phone number*/
Status phone_validation(long int num);

/*For validating mail*/
Status email_validation(char *email);

/*Function to search address*/
Status search_address(Address_Book *book);

/*Funtion to edit address*/
Status edit_address(Address_Book *book);

/*Function to delete address*/
Status delete_address(Address_Book *book);

/*Function to display the address*/
Status display_address(Address_Book *book);

#endif