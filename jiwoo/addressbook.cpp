#include<iostream>
#include<stdlib.h>
#include <algorithm>
#include "Person.h"

using namespace std;
int COUNTING(FILE *file) {
	char str[50];
	int count = 0;
	if (file != NULL) {
		while (0 != fgets(str, sizeof(str), file)) //연락처가 몇 개인지 세는 코드
			count++;
	}
	fclose(file);
	return count;
}

int main() {
	int contact_num = 0, message_num = 0, call_num = 0, favorite_num = 0;
	int b1, i, del = 0;
	char name[10], my_phone[15];

	PERSON LIST[30];
	RECENTS recent[50];
	CONTACT FAVORITE_LIST[30];


	printf("Enter you number☞ ");
	scanf_s("%s", my_phone, sizeof(my_phone));

	FILE *contact_list, *message_list, *call_list;
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
	}
	fclose(message_list);
	//take message_list.txt

	fopen_s(&call_list, "call_list.txt", "r");
	for (int i = message_num; i < call_num; i++) {
		fscanf_s(call_list, "%s %s %s %s %s", recent[i].s_bal, sizeof(recent[i].s_bal), recent[i].division, sizeof(recent[i].division), recent[i].name, sizeof(recent[i].name), recent[i].time, sizeof(recent[i].time), recent[i].date, sizeof(recent[i].date));
		fgets(recent[i].contents, sizeof(recent[i].contents), call_list);
	}
	fclose(call_list);
	//take call_list.txt


	sort(recent, recent + call_num);


	while (true) {
		printf("\n0. CONTACTS\n1. Add\n2. Search\n3. Favorite\n4. Recents\n5. Exit\n==================\nSelect: ");
		scanf_s("%d", &b1);

		if (del == 1) {
			contact_num--; del = 0;
		}

		if (contact_num != 0) { //연락처의 개수가 0이 아닐 때
			fopen_s(&contact_list, "contact_list.txt", "r");

			for (i = 0; i < contact_num; i++)
				fscanf_s(contact_list, "%s %s %s", LIST[i].name, sizeof(LIST[i].name), LIST[i].phone, sizeof(LIST[i].phone), LIST[i].email, sizeof(LIST[i].email));
			fclose(contact_list);
		}

		sort(LIST, LIST + contact_num);

		if (b1 == 0) {
			printf("\n------------------------------------------------------");
			printf("\nMy phone: %s", my_phone);
			printf("\nname\tphone\t\temail\t\n");
			for (int i = 0; i < contact_num; i++)
				printf("%s\t%s\t%s\n", LIST[i].name, LIST[i].phone, LIST[i].email);
			printf("%d contacts.\n", contact_num);
			printf("------------------------------------------------------\n");
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
			PERSON *SEARCH_LIST[30];
			char search_string[10];
			cout << "\nSearch ☞ ";
			cin >> search_string;
			int cnt = Search(LIST, SEARCH_LIST, &contact_num, search_string);
			cout << cnt << " result.\n";
			int b2, b3; int edit_num; char c, edit_string[30];
			cout << "\n1. Edit\n2. Cancle\n==================\nSelect: "; cin >> b2;

			if (b2 == 1) {
				Edit(LIST, SEARCH_LIST, FAVORITE_LIST, &contact_num, &favorite_num);

				fopen_s(&contact_list, "contact_list.txt", "w");

				for (int i = 0; i < contact_num; i++) {
					if (!strcmp(LIST[i].name, "deleted")) {
						del = 1; continue;
					}
					fprintf_s(contact_list, "%s %s %s\n", LIST[i].name, LIST[i].phone, LIST[i].email);
				}

				fclose(contact_list); cout << "\nSucceeded" << endl;

			}
		}
		if (b1 == 3) {
			printf("\nname\tphone\t\temail\t\n");
			for (int i = 0; i < favorite_num; i++)
				printf("%s\t%s\t%s\n", FAVORITE_LIST[i]->name, FAVORITE_LIST[i]->phone, FAVORITE_LIST[i]->email);
			printf("%d contacts.\n", favorite_num);
			printf("------------------------------------------------------\n");
		}

		else if (b1 == 4) {
			int look_num; char yes_or_no; PERSON *SEARCH_LIST[30];
			printf("\n------------------------------------------------------\n");
			for (int i = 0; i < call_num; i++)
				printf("%s\t%s\t%s\t%s\n", recent[i].s_bal, recent[i].division, recent[i].name, recent[i].date);
			printf("------------------------------------------------------\n");
			printf("Select the number of message do you want to look up: "); scanf_s("%d", &look_num);
			printf("\n%s\t%s\t%s\t%s\t%s\t%s\n", recent[look_num - 1].s_bal, recent[look_num - 1].division, recent[look_num - 1].name, recent[look_num - 1].contents, recent[look_num - 1].date, recent[look_num - 1].time);

			printf("Do you want more? (y/n): "); scanf_s(" %c", &yes_or_no, sizeof(&yes_or_no));

			if (yes_or_no == 'y') {
				if (Search(LIST, SEARCH_LIST, &contact_num, recent[look_num - 1].name) == 0)
					printf("No result\n");
			}
		}

		else if (b1 == 5)
			break;
	}

	return 0;
}
