#include<iostream>
#include<stdlib.h>
#include <algorithm>
#include "person.h"

int main() {
	FILE *contact_list, *message_list, *call_list;
	PERSON LIST[30];
	PERSON *SEARCH_LIST[30];
	PERSON *FAVORITE_LIST[30];
	RECENTS recent[50];

	int contact_num = 0, message_num = 0, call_num = 0, favorite_num = 0;
	int Default_Menu, Edit_Menu, edit_num;
	char name[10], my_number[15], search_string[10], edit_string[30], c;

	fopen_s(&contact_list, "contact_list.txt", "r");
	fopen_s(&message_list, "message_list.txt", "r");
	fopen_s(&call_list, "call_list.txt", "r");
	contact_num = COUNTING(contact_list);
	message_num = COUNTING(message_list);
	call_num = COUNTING(call_list);
	call_num += message_num;

	fopen_s(&message_list, "message_list.txt", "r");
	for (int i = 0; i < message_num; i++) {
		fscanf_s(message_list, "%s %s %s %s %s", recent[i].s_bal, sizeof(recent[i].s_bal), recent[i].division, sizeof(recent[i].division), recent[i].name, sizeof(recent[i].name), recent[i].time, sizeof(recent[i].time), recent[i].date, sizeof(recent[i].date));
		fgets(recent[i].contents, sizeof(recent[i].contents), message_list);
	} fclose(message_list);

	fopen_s(&call_list, "call_list.txt", "r");
	for (int i = message_num; i < call_num; i++) {
		fscanf_s(call_list, "%s %s %s %s %s", recent[i].s_bal, sizeof(recent[i].s_bal), recent[i].division, sizeof(recent[i].division), recent[i].name, sizeof(recent[i].name), recent[i].time, sizeof(recent[i].time), recent[i].date, sizeof(recent[i].date));
		fgets(recent[i].contents, sizeof(recent[i].contents), call_list);
	} fclose(call_list);

	printf("Enter you number☞ ");
	scanf_s("%s", my_number, sizeof(my_number));

	sort(recent, recent + call_num);

	while (true) {
		if (contact_num != 0) { //연락처의 개수가 0이 아닐 때
			fopen_s(&contact_list, "contact_list.txt", "r");
			for (int i = 0; i < contact_num; i++)
				fscanf_s(contact_list, "%s %s %s", LIST[i].name, sizeof(LIST[i].name), LIST[i].phone, sizeof(LIST[i].phone), LIST[i].email, sizeof(LIST[i].email));
			fclose(contact_list);
		}

		sort(LIST, LIST + contact_num);

		printf("\n0. CONTACTS\n1. Add\n2. Search\n3. Favorite\n4. Recents\n5. Exit\n==================\nSelect: ");
		scanf_s("%d", &Default_Menu);

		if (Default_Menu == 0)
			Print(LIST, my_number, contact_num);
		else if (Default_Menu == 1) {
			Add(LIST, contact_num); contact_num++;

			fopen_s(&contact_list, "contact_list.txt", "w");
			for (int i = 0; i < contact_num; i++)
				fprintf_s(contact_list, "%s %s %s\n", LIST[i].name, LIST[i].phone, LIST[i].email);
			fclose(contact_list);
		}

		else if (Default_Menu == 2) {
			printf("\nSearch ☞ ");
			scanf_s("%s", search_string, sizeof(search_string));
			printf("\n------------------------------------------------------");
			printf("\nname\t phone\t\temail\n");
			printf("%d result\n", Search(LIST, SEARCH_LIST, contact_num, search_string));
			printf("------------------------------------------------------\n");
			printf("\n1. Edit(edit, favorite, delete)\n2. Cancle\n==================\nSelect: ");
			scanf_s("%d", &Edit_Menu);

			if (Edit_Menu == 1) {
				Edit(LIST, SEARCH_LIST, FAVORITE_LIST, &favorite_num);

				fopen_s(&contact_list, "contact_list.txt", "w");
				for (int i = 0; i < contact_num; i++) {
					if (!strcmp(LIST[i].name, "deleted")) {
						contact_num--; continue;
					}
					fprintf_s(contact_list, "%s %s %s\n", LIST[i].name, LIST[i].phone, LIST[i].email);
				} fclose(contact_list);
				cout << "\nSucceeded." << endl;
			}
		}

		if (Default_Menu == 3)
			Favorite(FAVORITE_LIST, favorite_num);
		else if (Default_Menu == 4)
			Recents(LIST, recent, SEARCH_LIST, contact_num, call_num);
		else if (Default_Menu == 5)
			break;
	}
	return 0;
}