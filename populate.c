#include <stdio.h>
#include "functions.h"

static Contacts dummyContacts[] = 
{
{"Prapanjan",9791319862,"rprapan@gmail.com"},
{"Raveendiran",9442256215, "prav@gmail.com"},
{"Siva",987654152, "siva12@gmail.com"},
{"genjan",9795649862,"rprtran@gmail.com"},
{"Rtrendiran",9476556215, "prav@yaail.com"},
{"Sirea",987654152, "sira12@g.be"},
{"Prtrdnjan",945519862,"rpiupan@gmail.com"},
{"Ratryziran",9445456215, "proyav@gmail.com"},
{"Sivge",987544152, "silkiu12@gmail.com"},
{"Strge",984544152, "silk452@gmail.com"},
};

void populate_dummy_contacts(Address_Book *book)
{
    int size_dum = sizeof(dummyContacts) / sizeof(dummyContacts[0]);
    for(int i=0; i< size_dum &&  book->count < MAX_CONTACT ; i++)
    {
        book->det[book->count++] = dummyContacts[i];      
        
    }
}
