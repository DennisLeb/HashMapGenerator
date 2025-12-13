// File main.c
// Date 11/12/2025
//

/* In diesem Programm wird eine hashmap generiert, deren Länge der Nutzer
	bestimmen darf (mit Rücksicht auf Obergrenze). Es werden zufällige
	Vor- und Nachnamen als values und usernames als keys verwendet.
	Im Anschluss wird die Userliste in der Konsole ausgegeben, wonach
	der Nutzer einen username benutzen kann, um den entsprechenden
	vollen Namen zu finden. */

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "hashData.h"

char** generateNames(int arrLen);
char** generateUsernames(int arrLen, char **fullNames);
unsigned long hash(unsigned char* str, int arrLen);
userData fillHashMap(int arrLen, char **fullNames, char **usernames);
int readHashMap(int arrLen, userData hashMap);

int main(void) {

	int ans, ansType, index;
	char ans2;

	srand((unsigned int)time(NULL));

	puts("*****\tHashMap Generator\t*****\n");
		
	while (1) {
		printf("How many pairs of full names and usernames would you like your hashmap to hold? (1-150) ");
		ansType = scanf_s(" %d", &ans);

		if (ansType != 1 /*falscher Datentyp*/) {

			// buffer leeren
			while (getchar() != '\n') {}

			puts("\nInvalid data input! Try again!\n");
			continue;
		}
		else if (ans < 1 || ans > 150) {
			puts("\nInput out of range! Try again!\n");
			continue;
		}

		break;
	}
	
	char **fullNames = generateNames(ans);
	char **usernames = generateUsernames(ans, fullNames);

	puts("\n***\tUser list\t***\n");

	for (int i = 0; i < ans; i++) {
		printf("Full name #%d:\t%s\n", i + 1, *(fullNames + i));
		printf("Username:\t%s\n\n", *(usernames + i));
	}

	userData hashMap = fillHashMap(ans, fullNames, usernames);

	// Speicher kann jetzt freigegeben werden
	for (int i = 0; i < ans; i++) {
		
		// Zuerst pointer
		free(*(fullNames + i));
		free(*(usernames + i));
	}

	// dann double pointer
	free(fullNames);
	free(usernames);
	
	do {
		index = readHashMap(ans, hashMap);

		if (index == -1) {
			puts("\nUsername not found in database!\n");
		}
		else {
			puts("\n***\tUser found!\t***\n");
			printf("Full name:\t%s\n", hashMap[index].fullName);
			printf("Username:\t%s\n\n", hashMap[index].username);
		}

		do {
			// buffer leeren
			while (getchar() != '\n') {}

			printf("Would you like to look for another user? (Y/N) ");
			ans2 = getchar();

			if (toupper(ans2) == 'Y' || toupper(ans2) == 'N') {
				break;
			}
			else {
				puts("\nInvalid input! Try again!\n");
			}

		} while (1);

	} while (toupper(ans2) == 'Y');

	// Speicher freigeben
	free(hashMap);

	return (0);
}

// Funktion um die vollen Namen zufällig zu erstellen
char** generateNames(int arrLen) {

	// Speicher für den string array names/fullNames reservieren
	char** names = (char**)malloc(arrLen * sizeof(char*));
	if (!names) {
		puts("generateNames: names: Memory allocation failed!");
		exit(1);
	}

	// Speicher für die Elemente von names reservieren
	for (int i = 0; i < arrLen; i++) {
		*(names + i) = (char*)malloc(MAX_LENGTH);	// sizeof(char) = 1
		if (!(*(names + 1))) {
			puts("generateNames: *(names + i): Memory allocation failed!");
			exit(1);
		}

		// Namen zufällig generieren und zuordnen (Duplikate werden akzeptiert)
		sprintf_s(*(names + i), MAX_LENGTH, "%s %s", firstNameArr[(rand() % NAME_ARR_LENGTH)], lastNameArr[(rand() % NAME_ARR_LENGTH)]);
	}

	return (names);
}

// Funktion um die usernames zufällig zu erstellen (voller Name + Zahl)
char** generateUsernames(int arrLen, char** fullNames) {

	char firstName[MAX_LENGTH], lastName[MAX_LENGTH];	// zum Zwischenspeichern
	char randomNum[4] = { '\0' };
	int ret;	// hält den Rückgabewert von sscanf_s()
	size_t elementSize;

	// Speicher für den string array names/usernames reservieren
	char** names = (char**)malloc(arrLen * sizeof(char*));
	if (!names) {
		puts("generateUsernames: names: Memory allocation failed!");
		exit(1);
	}

	// Speicher für die Elemente von names reservieren
	for (int i = 0; i < arrLen; i++) {
		 elementSize = (sizeof(*(fullNames + i)) + 15);	// +15 Byte zur Sicherheit

		names[i] = (char*)malloc(elementSize);	// sizeof(char) = 1
		if (!names[i]) {
			puts("generateUsernames: names[i]: Memory allocation failed!");
			exit(1);
		}

		// liest den vollen Namen aus und speichert ihn zwischen
		ret = sscanf_s(*(fullNames + i), "%s %s", &firstName, (unsigned int)sizeof(firstName), &lastName, (unsigned int)sizeof(lastName));

		// vollen Namen zu Kleinbuchstaben
		for (int j = 0;j < sizeof(firstName); j++) {
			firstName[j] = tolower(firstName[j]);
		}
		for (int j = 0; j < sizeof(lastName); j++) {
			lastName[j] = tolower(lastName[j]);
		}

		// zufällige Zahl als string
		for (int j = 0; j < 3; j++) {
			randomNum[j] = (char)((rand() % 10) + 48);	// 48-57 -> ASCII von 0-9
		}

		// fügt username aus lower case Vor- und Nachnamen + zufälliger Zahl zusammen
		sprintf_s(names[i], elementSize, "%s%s%s", firstName, lastName, randomNum);
	}

	return (names);
}

// Funktion um username strings in Indexe umzuwandeln und dabei möglichst Kollisionen zu vermeiden (djb2 hash)
unsigned long hash(unsigned char* str, int arrLen) {

	// 5381 führt in der Rechnung zu möglichst wenigen Kollisionen von verschiedenen string inputs
	unsigned long hash = 5381;
	int c;

	// iteriert durch jeden einzelnen char und weist c den ASCII Wert des chars zu. '\0' wird als false interpretiert
	while (c = *str++) {

		// left shift Operator << verschiebt bits um 5 Stellen
		// hash << 5 == hash * 2**5 == hash * 32
		// << ist effizienter als andere Operatoren
		hash = ((hash << 5) + hash) + c;	/* hash * 33 + c */
	}

	hash %= arrLen;	// für arrLen == 20 -> hash == 0-19

	return (hash);
}

// Funktion um usernames als Index mit den vollen Namen zu verknüpfen
userData fillHashMap(int arrLen, char** fullNames, char** usernames) {

	int hashMapLen = arrLen + 25, index;

	// Speicher reservieren. Mehr als nötig zur Sicherheit
	userData hashMap = (userData)calloc(hashMapLen, sizeof(struct user));
	if (!hashMap) {
		puts("fillHashMap: hashMap: Memory allocation failed!");
		exit(1);
	}

	// einfüllen
	for (int i = 0; i < arrLen; i++) {

		index = hash(*(usernames + i), arrLen);

		while (1) {

			// prüft ob Stelle in der hashmap leer ist. Hierzu wurde calloc() statt malloc() benutzt
			// Wenn fullName leer ist, muss username auch leer sein
			if (hashMap[index].fullName[0] == '\0') {
				sprintf_s(hashMap[index].fullName, sizeof(hashMap[index].fullName), "%s", *(fullNames + i));
				sprintf_s(hashMap[index].username, sizeof(hashMap[index].username), "%s", *(usernames + i));
				break;
			}
			// andernfalls erhöht sich Index und er sucht weiter nach freier Stelle. Hierzu wurde hashmap mehr Speicher zugewiesen 
			else {
				index++;
			}
		}
	}

	return (hashMap);
}

// Funktion die es ermöglicht Nutzerdaten aus hashmap zu holen
int readHashMap(int arrLen, userData hashMap) {

	int ansType, index;
	char unameInput[MAX_LENGTH + 15] = { '\0' };	// MAX_LENGTH + 15 gleicht dem username string in struct user

	while (1) {

		printf("\nPlease enter a username to access the according full name: ");
		ansType = scanf_s(" %s", &unameInput, (unsigned int)sizeof(unameInput));

		if (ansType != 1 /*falscher Datentyp ODER sizeof(unameInput) überschritten*/) {
			
			// buffer leeren
			while (getchar() != '\n') {}
			
			puts("\nInvalid data input! Try again!\n");
			continue;
		}

		break;
	}

	index = hash(unameInput, arrLen);

	// sucht nach Nutzer, bis eine leere Stelle in der hashmap gefunden wurde
	while (strcmp(unameInput, hashMap[index].username) != 0) {	// strcmp() gibt 0 zurück, wenn strings identisch sind

		// bei leerer Stelle existiert der Nutzer nicht
		// Wenn fullName leer ist, muss username auch leer sein
		if (hashMap[index].fullName[0] == '\0') {
			printf("%s", hashMap[index].fullName);
			return (-1);
		}

		// sucht weiter
		index++;
	}
	
	return (index);
}
