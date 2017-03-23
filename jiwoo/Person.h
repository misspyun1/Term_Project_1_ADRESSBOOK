#pragma once
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

typedef struct record {
	char name[11];
	char phone[15];
	char email[30];

	bool operator < (const record right) {
		return name[0] < right.name[0] || (name[0] == right.name[0] && name[1]<right.name[1]);
	}
}PERSON;

typedef struct data {
	char division[10];
	char s_bal[5];
	char name[11];
	char time[11];
	char date[15];
	char contents[20];

	bool operator <(const data right) {
		return atoi(date) < atoi(right.date) || (date == right.date&&atoi(time) < atoi(right.time));
	}
} RECENTS;

typedef PERSON* CONTACT;

int Search(PERSON LIST[], PERSON *SEARCH_LIST[], int* contact_num, char *search_string) {
	int cnt = 0;
	cout << "\nname\tphone\t\temail" << endl;
	for (int i = 0; i < *contact_num; i++) {
		if (strstr(LIST[i].name, search_string) != NULL) {
			cout << "¢º" << LIST[i].name << "\t" << LIST[i].phone << "\t" << LIST[i].email << endl; cnt++;
			SEARCH_LIST[cnt - 1] = &LIST[i];
		}
		else if (strstr(LIST[i].phone, search_string) != NULL) {
			cout << LIST[i].name << "\t¢º" << LIST[i].phone << "\t" << LIST[i].email << endl; cnt++;
			SEARCH_LIST[cnt - 1] = (&LIST[i]);
		}
		else if (strstr(LIST[i].email, search_string) != NULL) {
			cout << LIST[i].name << "\t" << LIST[i].phone << "\t¢º" << LIST[i].email << endl; cnt++;
			SEARCH_LIST[cnt - 1] = (&LIST[i]);
		}
	}
	return cnt;
	
}

void Edit(PERSON LIST[], PERSON *SEARCH_LIST[], PERSON *FAVORITE_LIST[], int* contact_num, int* favorite_num) {
	int b3, edit_num; char edit_string[30];
	cout << "\nEnter number of who do you want edit: "; cin >> edit_num;
	cout << "\n1. edit name\n2. edit phone\n3. edit email\n4. Delete contact\n5. Add to Favorites\n==================\nSelect: ";
	cin >> b3;
	if (b3 == 1) {
		cout << "Enter name: "; cin >> edit_string;
		strcpy_s(SEARCH_LIST[edit_num - 1]->name, 10, edit_string);
	}
	else if (b3 == 2) {
		cout << "Enter phone: "; cin >> edit_string;
		strcpy_s(SEARCH_LIST[edit_num - 1]->phone, 10, edit_string);
	}
	else if (b3 == 3) {
		cout << "Enter email: "; cin >> edit_string;
		strcpy_s(SEARCH_LIST[edit_num - 1]->email, 10, edit_string);
	}
	else if (b3 == 4) {
		int b4;
		cout << "\n1. Delect contact\n2. Cancle\n==================\nSelect: "; cin >> b4;
		if (b4 == 1) {
			strcpy_s(SEARCH_LIST[edit_num - 1]->name, 10, "deleted");
		}
	}
	else if (b3 == 5) {
		FAVORITE_LIST[*favorite_num] = SEARCH_LIST[edit_num - 1];
		*favorite_num += 1;
	}

}