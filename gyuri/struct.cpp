#include<iostream>
#include<stdlib.h>
#include <string>
#include<string.h>
#include<conio.h>
#include <algorithm>
#include "Person.h"
using namespace std;

void Search(PERSON LIST[], PERSON SEARCH_LIST[]);

PERSON LIST[30];


int main() {
	int contact_num = 0;
	int b1, i;
	char name[11];
	char str[50];

	FILE *contact_list;
	fopen_s(&contact_list, "contact_list.txt", "r");

	//list에 아무것도 없을 경우 제외
	if (contact_list != NULL) {
		while (0 != fgets(str, sizeof(str), contact_list)) //연락처가 몇 개인지 세는 코드
			contact_num++;

		fclose(contact_list);
	}

	while (true) {
		printf("\n<Address Book>\n");
		printf("0. CONTACTS\n1. Add\n2. Find\n3. Favorites\nSelect : ");
		scanf_s("%d", &b1);

		if (contact_num != 0) { //연락처의 개수가 0이 아닐 때

			fopen_s(&contact_list, "contact_list.txt", "r");

			for (i = 0; i < contact_num; i++)
				fscanf_s(contact_list, "%s %s %s", LIST[i].name, sizeof(LIST[i].name), LIST[i].phone, sizeof(LIST[i].phone), LIST[i].email, sizeof(LIST[i].email));

			fclose(contact_list);
		}

		sort(LIST, LIST + contact_num);// LIST sort
		printf("sort complete\n");

		if (b1 == 0) {
			printf("name\tphone\t\t\temail\n");
			for (int i = 0; i < contact_num; i++)
				printf("%s\t%s\t%s\n", LIST[i].name, LIST[i].phone, LIST[i].email);
		}
		else if (b1 == 1) {
			printf("\nInsert your information\n");
			printf("name: "); scanf_s("%s", LIST[contact_num].name, sizeof(LIST[contact_num].name));
			printf("phone number: "); scanf_s("%s", LIST[contact_num].phone, sizeof(LIST[contact_num].phone));
			printf("email: "); scanf_s("%s", LIST[contact_num].email, sizeof(LIST[contact_num].email));
			printf("\nSucceeded.\n");
			contact_num++;

			fopen_s(&contact_list, "contact_list.txt", "w");

			for (int i = 0; i < contact_num; i++)
				fprintf_s(contact_list, "%s %s %s\n", LIST[i].name, LIST[i].phone, LIST[i].email);
			fclose(contact_list);
		}
		else if (b1 == 2) {
			PERSON SEARCH_LIST[30] = {};
			Search(LIST, SEARCH_LIST);
			int b2, b3; char c;
			cout << "\n1. Edit\n2. Undo\n"; cin >> b2;
			if (b2 == 1) {
				cout << "\n1. add phone\n2. add email\n3. add url\n4. add address\n5. add date\n6. add related name\n";
				cout << "7. add social profile\n8. add instant message\n9. Delete\n10. Delete contact\n";
				cin >> b3;
				if (b3 == 10) {
					cout << "Delete Contact(d)\nCancle(c)" << endl; cin >> c;
					if (c == 'd') {}
					//delete
					if (c == 'c') {}
					//cancle;
				}
			}
		}
	}

	return 0;
}

void Search(PERSON LIST[], PERSON SEARCH_LIST[]) {
	char search_string[10]; int cnt = 0;
	cout << "Search ☞ ";
	cin >> search_string;
	cout << "name\tphone\t\temail" << endl;
	for (int i = 0; i < sizeof(LIST); i++) {
		if (strstr(LIST[i].name, search_string) != NULL) {
			cout << "▶" << LIST[i].name << "\t\t" << LIST[i].phone << "\t\t\t" << LIST[i].email << endl; cnt++;
			SEARCH_LIST[cnt - 1] = LIST[i];
		}
		else if (strstr(LIST[i].phone, search_string) != NULL) {
			cout << LIST[i].name << "\t▶" << LIST[i].phone << "\t\t\t" << LIST[i].email << endl; cnt++;
			SEARCH_LIST[cnt - 1] = LIST[i];
		}
		else if (strstr(LIST[i].email, search_string) != NULL) {
			cout << LIST[i].name << "\t\t" << LIST[i].phone << "\t \t ▶" << LIST[i].email << endl; cnt++;
			SEARCH_LIST[cnt - 1] = LIST[i];
		}
	}
	cout << cnt << " result.\n";
}