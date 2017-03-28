#pragma once
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

typedef struct record {
	char name[11];
	char phone[15];
	char email[30];

	bool operator < (const record right) { //struct record에 대한 < 연산자를 오버로딩
		for (int i = 0; i < 11; i++) {
			if (name[i] < right.name[i]) {
				return true;
			}
			else if (name[i] > right.name[i]) {
				return false;
			}
		}
		/*반복문을 통해 < 연산자를 기준으로 왼쪽과 오른쪽의 name을 비교한다. 
		왼쪽의 스트링이 오른쪽의 스트링보다 abc또는 가나다 순으로 앞에 있으면 true를, 그 반대면 false 를 반환한다. */
	}

} PERSON;

typedef struct data {
	char division[10];
	char s_bal[5];
	char name[11];
	char time[11];
	char date[15];
	char contents[20];

	bool operator <(const data right) {//struct data에 대한 < 연산자 오버로딩
		return atoi(date) < atoi(right.date) || (date == right.date&&atoi(time) < atoi(right.time));
	}
	/*date를 비교하고, date가 같다면 time을 비교해서 시간순으로 최근기록을 정렬한다.*/
} RECENTS;

int COUNTING(FILE *file) {
	char input_str[50];
	int count = 0;
	if (file != NULL) {
		while (0 != fgets(input_str, sizeof(input_str), file)) //연락처가 몇 개인지 세는 코드		
			count++;
	} fclose(file);

	return count;//연락처 개수 return
}

//연락처를 모두 보여주는 함수
void Print(PERSON LIST[], char my_number[], int contact_num) {
	printf("\n------------------------------------------------------");
	printf("\n☎ My Number: %s\nname\tphone\t\temail\t\n", my_number);
	for (int i = 0; i < contact_num; i++)
		printf("%s\t%s\t%s\n", LIST[i].name, LIST[i].phone, LIST[i].email);
	printf("\n%d contacts.\n", contact_num);
	printf("------------------------------------------------------\n");
}

//연락처 추가함수
void Add(PERSON LIST[], int contact_num) {
	printf("\nInsert information\n");
	printf("name: "); scanf_s("%s", LIST[contact_num].name, sizeof(LIST[contact_num].name));
	printf("phone number: "); scanf_s("%s", LIST[contact_num].phone, sizeof(LIST[contact_num].phone));
	printf("email: "); scanf_s("%s", LIST[contact_num].email, sizeof(LIST[contact_num].email));
	printf("\nAdd succeeded.\n");
}//필요한 정보를 입력받아 LIST배열에 저장한다.

//연락처 탐색함수
int Search(PERSON LIST[], PERSON *SEARCH_LIST[], int contact_num, char *search_string) {
	int cnt = 0;
	for (int i = 0; i < contact_num; i++) {
		if (strstr(LIST[i].name, search_string) != NULL) {
			cout << "▶" << LIST[i].name << " " << LIST[i].phone << "\t" << LIST[i].email << endl; cnt++;
			SEARCH_LIST[cnt - 1] = &LIST[i];
		}
		else if (strstr(LIST[i].phone, search_string) != NULL) {
			cout << LIST[i].name << "\t ▶" << LIST[i].phone << "\t" << LIST[i].email << endl; cnt++;
			SEARCH_LIST[cnt - 1] = (&LIST[i]);
		}
		else if (strstr(LIST[i].email, search_string) != NULL) {
			cout << LIST[i].name << "\t " << LIST[i].phone << "\t▶" << LIST[i].email << endl; cnt++;
			SEARCH_LIST[cnt - 1] = (&LIST[i]);
		}
	}

	return cnt;
}//name이나 email이나 phone넘버 중에서 주어진 텍스트와 일치하는 부분이 있다면 SEARCH_LIST배열이 그 정보가 들어있는 LIST를 가리키게 한다.

//연락처 편집함수
void Edit(PERSON LIST[], PERSON *SEARCH_LIST[], PERSON *FAVORITE_LIST[], int* favorite_num) {
	int thing_to_Edit, edit_num; char edit_string[30];
	cout << "What's the number of contact that you want edit: "; cin >> edit_num; //edit할 사람을 선택한다.
	cout << "\n1. edit name\n2. edit phone\n3. edit email\n4. Delete contact\n5. Add to Favorites\n==================\nSelect: ";//그 사람의 어떤 정보를 edit할지 정한다.
	cin >> thing_to_Edit;

	if (thing_to_Edit == 1) {
		cout << "Enter name: "; cin >> edit_string;//입력을 받아서, 그 결과를 배열안에 덮어 씌운다.
		strcpy_s(SEARCH_LIST[edit_num - 1]->name, 10, edit_string);
	}
	else if (thing_to_Edit == 2) {
		cout << "Enter phone: "; cin >> edit_string;
		strcpy_s(SEARCH_LIST[edit_num - 1]->phone, 10, edit_string);
	}
	else if (thing_to_Edit == 3) {
		cout << "Enter email: "; cin >> edit_string;
		strcpy_s(SEARCH_LIST[edit_num - 1]->email, 10, edit_string);
	}
	else if (thing_to_Edit == 4) {
		int b4;
		cout << "\n1. Delect contact\n2. Cancle\n==================\nSelect: "; cin >> b4;
		if (b4 == 1) {
			strcpy_s(SEARCH_LIST[edit_num - 1]->name, 10, "deleted");
		}
	}
	else if (thing_to_Edit == 5) {
		FAVORITE_LIST[*favorite_num] = SEARCH_LIST[edit_num - 1];
		*favorite_num += 1;
	}//만약 즐겨찾기에 추가를 원한다면, FAVORIT_LIST는 포인터이므로 SEARC_LIST가 가리키는 것을 그 배열에 저장한다.

}

//즐겨찾기 목록을 프린트하는 함수
void Favorite(PERSON *FAVORITE_LIST[], int favorite_num) {
	printf("\n------------------------------------------------------\n");
	printf("☎ My Favorites\nname\tphone\t\temail\t\n");

	for (int i = 0; i < favorite_num; i++)
		printf("%s\t%s\t%s\n", FAVORITE_LIST[i]->name, FAVORITE_LIST[i]->phone, FAVORITE_LIST[i]->email);

	if (favorite_num == 0)
		printf("No result\n");
	else
		printf("\n%d contacts\n", favorite_num);

	printf("------------------------------------------------------\n");
}

//최근기록을 프린트하는 함수
void Recents(PERSON LIST[], RECENTS recent[], PERSON *SEARCH_LIST[], int contact_num, int call_num) {
	int look_num;
	char yes_or_no;
	printf("\n------------------------------------------------------\n");
	for (int i = 0; i < call_num; i++)
		printf("%s\t%s\t%s\t%s\n", recent[i].s_bal, recent[i].division, recent[i].name, recent[i].date);
	printf("------------------------------------------------------\n");
	printf("Select the number of message do you want to look up: "); scanf_s("%d", &look_num);
	printf("\n%s\t%s\t%s\t%s\t%s\t%s\n", recent[look_num - 1].s_bal, recent[look_num - 1].division, recent[look_num - 1].name, recent[look_num - 1].contents, recent[look_num - 1].date, recent[look_num - 1].time);
	
	printf("Do you want more? (y/n): "); scanf_s(" %c", &yes_or_no, sizeof(&yes_or_no));//연락처 정보를 더 원하냐고 묻는다

	if (yes_or_no == 'y')
		if (Search(LIST, SEARCH_LIST, contact_num, recent[look_num - 1].name) == 0)//만약 답이 y이면 Search함수 실행
			printf("No result\n");

}