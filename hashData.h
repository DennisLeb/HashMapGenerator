// File main.c
// Date 11/12/2025
//

/* Hier werden die strings zur Namenszuweisung und die nötigen structs definiert. */

#define NAME_ARR_LENGTH 12
#define MAX_LENGTH 25		// längster Eintrag: "Emanuel Frankenstein\0" -> [21], + 4 zur Sicherheit

// 144 mögliche Kombinationen
const char *firstNameArr[12] = {"Anton", "Britta", "Daniel", "Emanuel", "Franz", "Kevin", "Magnus", "Mark", "Mikhail", "Nolan", "Paul", "Victor"};
const char *lastNameArr[12] = {"Armstrong", "Carlsen", "Davis", "Focker", "Frankenstein", "Grayson", "Lasker", "Morphy", "Naroditsky", "Smith", "Tal", "Tolkien"};

typedef struct user
{
	char fullName[MAX_LENGTH];
	char username[MAX_LENGTH + 15];	// +15 Byte zur Sicherheit
} *userData;
