#pragma once
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

typedef struct record {
	char name[11];
	char phone[15];
	char email[30];

	bool operator < (const record right) { //struct record�� ���� < �����ڸ� �����ε�
		for (int i = 0; i < 11; i++) {
			if (name[i] < right.name[i]) {
				return true;
			}
			else if (name[i] > right.name[i]) {
				return false;
			}
		}
		/*�ݺ����� ���� < �����ڸ� �������� ���ʰ� �������� name�� ���Ѵ�. 
		������ ��Ʈ���� �������� ��Ʈ������ abc�Ǵ� ������ ������ �տ� ������ true��, �� �ݴ�� false �� ��ȯ�Ѵ�. */
	}

} PERSON;

typedef struct data {
	char division[10];
	char s_bal[5];
	char name[11];
	char time[11];
	char date[15];
	char contents[20];

	bool operator <(const data right) {//struct data�� ���� < ������ �����ε�
		return atoi(date) < atoi(right.date) || (date == right.date&&atoi(time) < atoi(right.time));
	}
	/*date�� ���ϰ�, date�� ���ٸ� time�� ���ؼ� �ð������� �ֱٱ���� �����Ѵ�.*/
} RECENTS;

int COUNTING(FILE *file) {
	char input_str[50];
	int count = 0;
	if (file != NULL) {
		while (0 != fgets(input_str, sizeof(input_str), file)) //����ó�� �� ������ ���� �ڵ�		
			count++;
	} fclose(file);

	return count;//����ó ���� return
}

//����ó�� ��� �����ִ� �Լ�
void Print(PERSON LIST[], char my_number[], int contact_num) {
	printf("\n------------------------------------------------------");
	printf("\n�� My Number: %s\nname\tphone\t\temail\t\n", my_number);
	for (int i = 0; i < contact_num; i++)
		printf("%s\t%s\t%s\n", LIST[i].name, LIST[i].phone, LIST[i].email);
	printf("\n%d contacts.\n", contact_num);
	printf("------------------------------------------------------\n");
}

//����ó �߰��Լ�
void Add(PERSON LIST[], int contact_num) {
	printf("\nInsert information\n");
	printf("name: "); scanf_s("%s", LIST[contact_num].name, sizeof(LIST[contact_num].name));
	printf("phone number: "); scanf_s("%s", LIST[contact_num].phone, sizeof(LIST[contact_num].phone));
	printf("email: "); scanf_s("%s", LIST[contact_num].email, sizeof(LIST[contact_num].email));
	printf("\nAdd succeeded.\n");
}//�ʿ��� ������ �Է¹޾� LIST�迭�� �����Ѵ�.

//����ó Ž���Լ�
int Search(PERSON LIST[], PERSON *SEARCH_LIST[], int contact_num, char *search_string) {
	int cnt = 0;
	for (int i = 0; i < contact_num; i++) {
		if (strstr(LIST[i].name, search_string) != NULL) {
			cout << "��" << LIST[i].name << " " << LIST[i].phone << "\t" << LIST[i].email << endl; cnt++;
			SEARCH_LIST[cnt - 1] = &LIST[i];
		}
		else if (strstr(LIST[i].phone, search_string) != NULL) {
			cout << LIST[i].name << "\t ��" << LIST[i].phone << "\t" << LIST[i].email << endl; cnt++;
			SEARCH_LIST[cnt - 1] = (&LIST[i]);
		}
		else if (strstr(LIST[i].email, search_string) != NULL) {
			cout << LIST[i].name << "\t " << LIST[i].phone << "\t��" << LIST[i].email << endl; cnt++;
			SEARCH_LIST[cnt - 1] = (&LIST[i]);
		}
	}

	return cnt;
}//name�̳� email�̳� phone�ѹ� �߿��� �־��� �ؽ�Ʈ�� ��ġ�ϴ� �κ��� �ִٸ� SEARCH_LIST�迭�� �� ������ ����ִ� LIST�� ����Ű�� �Ѵ�.

//����ó �����Լ�
void Edit(PERSON LIST[], PERSON *SEARCH_LIST[], PERSON *FAVORITE_LIST[], int* favorite_num) {
	int thing_to_Edit, edit_num; char edit_string[30];
	cout << "What's the number of contact that you want edit: "; cin >> edit_num; //edit�� ����� �����Ѵ�.
	cout << "\n1. edit name\n2. edit phone\n3. edit email\n4. Delete contact\n5. Add to Favorites\n==================\nSelect: ";//�� ����� � ������ edit���� ���Ѵ�.
	cin >> thing_to_Edit;

	if (thing_to_Edit == 1) {
		cout << "Enter name: "; cin >> edit_string;//�Է��� �޾Ƽ�, �� ����� �迭�ȿ� ���� �����.
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
	}//���� ���ã�⿡ �߰��� ���Ѵٸ�, FAVORIT_LIST�� �������̹Ƿ� SEARC_LIST�� ����Ű�� ���� �� �迭�� �����Ѵ�.

}

//���ã�� ����� ����Ʈ�ϴ� �Լ�
void Favorite(PERSON *FAVORITE_LIST[], int favorite_num) {
	printf("\n------------------------------------------------------\n");
	printf("�� My Favorites\nname\tphone\t\temail\t\n");

	for (int i = 0; i < favorite_num; i++)
		printf("%s\t%s\t%s\n", FAVORITE_LIST[i]->name, FAVORITE_LIST[i]->phone, FAVORITE_LIST[i]->email);

	if (favorite_num == 0)
		printf("No result\n");
	else
		printf("\n%d contacts\n", favorite_num);

	printf("------------------------------------------------------\n");
}

//�ֱٱ���� ����Ʈ�ϴ� �Լ�
void Recents(PERSON LIST[], RECENTS recent[], PERSON *SEARCH_LIST[], int contact_num, int call_num) {
	int look_num;
	char yes_or_no;
	printf("\n------------------------------------------------------\n");
	for (int i = 0; i < call_num; i++)
		printf("%s\t%s\t%s\t%s\n", recent[i].s_bal, recent[i].division, recent[i].name, recent[i].date);
	printf("------------------------------------------------------\n");
	printf("Select the number of message do you want to look up: "); scanf_s("%d", &look_num);
	printf("\n%s\t%s\t%s\t%s\t%s\t%s\n", recent[look_num - 1].s_bal, recent[look_num - 1].division, recent[look_num - 1].name, recent[look_num - 1].contents, recent[look_num - 1].date, recent[look_num - 1].time);
	
	printf("Do you want more? (y/n): "); scanf_s(" %c", &yes_or_no, sizeof(&yes_or_no));//����ó ������ �� ���ϳİ� ���´�

	if (yes_or_no == 'y')
		if (Search(LIST, SEARCH_LIST, contact_num, recent[look_num - 1].name) == 0)//���� ���� y�̸� Search�Լ� ����
			printf("No result\n");

}