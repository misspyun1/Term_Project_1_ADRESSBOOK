#include<iostream>
#include<stdlib.h>
#include <algorithm>
#include "addressbook_header.h"	//각 함수들이 들어있는 헤더파일

int main() {
	FILE *contact_list, *message_list, *call_list;	//각 txt 파일을 저장할 FILE 변수
	PERSON LIST[30];	//메모장에 저장된 연락처들의 정보를 담을 구조체 배열
	PERSON *SEARCH_LIST[30];	//search된 연락처들의 정보를 담을 구조체 배열
	PERSON *FAVORITE_LIST[30];	//즐겨찾기에 추가된 연락처들의 정보를 담을 구조체 배열
	RECENTS recent[50];	//메모장에 저장된 최근 통화, 문자 기록을 담을 구조체 배열 

	int contact_num = 0, message_num = 0, call_num = 0, favorite_num = 0;	//각각 전체 연락처, 문자기록, 통화기록, 즐겨찾기에 추가된 연락처의 개수
	int Default_Menu, Edit_Menu;	//시작 메뉴와 edit 메뉴의 버튼
	char my_number[15], search_string[10];	//내 번호와 검색시 입력할 스트링을 저장하는 배열 변수

	fopen_s(&contact_list, "contact_list.txt", "r");	//contact_list.txt 파일을 읽기 모드로 연다
	fopen_s(&message_list, "message_list.txt", "r");	//message_list.txt 파일을 읽기 모드로 연다
	fopen_s(&call_list, "call_list.txt", "r");	//call_list.txt 파일을 읽기 모드로 연다
	contact_num = COUNTING(contact_list);	//contact_list.txt 파일을 읽어 연락처의 개수를 받아온다
	message_num = COUNTING(message_list);	//message_list.txt 파일을 읽어 문자 기록의 개수를 받아온다
	call_num = COUNTING(call_list);	//call_list.txt 파일을 읽어 통화 기록의 개수를 받아온다
	call_num += message_num;	//문자와 통화를 합친 전체 recent의 개수를 call_num에 저장한다

	fopen_s(&message_list, "message_list.txt", "r");	//message_list.txt 파일을 읽기 모드로 연다
	for (int i = 0; i < message_num; i++) {
		fscanf_s(message_list, "%s %s %s %s %s", recent[i].s_bal, sizeof(recent[i].s_bal), recent[i].division, sizeof(recent[i].division), recent[i].name, sizeof(recent[i].name), recent[i].time, sizeof(recent[i].time), recent[i].date, sizeof(recent[i].date));
		//message_list 파일을 차례로 읽어 수발신, 기록종류, 이름, 시간, 날짜 순으로 구조체에 저장한다
		fgets(recent[i].contents, sizeof(recent[i].contents), message_list);	//마지막 내용부분은 빈칸이 포함되어 있으므로 메모장 내에서 줄이 바뀌기 전까지 content로 저장한다.
	} fclose(message_list);	//messge_list 파일을 닫는다

	//위의 message_list와 같은 방법으로 call_list 파일도 읽어준다
	fopen_s(&call_list, "call_list.txt", "r");
	for (int i = message_num; i < call_num; i++) {
		fscanf_s(call_list, "%s %s %s %s %s", recent[i].s_bal, sizeof(recent[i].s_bal), recent[i].division, sizeof(recent[i].division), recent[i].name, sizeof(recent[i].name), recent[i].time, sizeof(recent[i].time), recent[i].date, sizeof(recent[i].date));
		fgets(recent[i].contents, sizeof(recent[i].contents), call_list);
	} fclose(call_list);

	printf("Enter you number☞ ");
	scanf_s("%s", my_number, sizeof(my_number));	//나의 전화번호를 입력받는다

	sort(recent, recent + call_num);	//recent배열에 대하여 전체 recent의 개수만큼 이름순으로 정렬한다

	while (true) {
		if (contact_num != 0) { //연락처의 개수가 0이 아닐 때
			fopen_s(&contact_list, "contact_list.txt", "r");	//contact_list.txt 파일을 읽기모드로 연다
			for (int i = 0; i < contact_num; i++)
				fscanf_s(contact_list, "%s %s %s", LIST[i].name, sizeof(LIST[i].name), LIST[i].phone, sizeof(LIST[i].phone), LIST[i].email, sizeof(LIST[i].email));
				//contact_list 파일에서 차례로 읽어와 이름, 번호, 이메일 변수에 넣어준다.
			fclose(contact_list);	//contact_list 파일을 닫는다
		}

		sort(LIST, LIST + contact_num);	//LIST배열에 대하여 전체 연락처 개수만큼 이름순으로 정렬한다

		printf("\n0. CONTACTS\n1. Add\n2. Search\n3. Favorite\n4. Recents\n5. Exit\n==================\nSelect: ");
		scanf_s("%d", &Default_Menu);	//시작 메뉴를 선택한다

		if (Default_Menu == 0)
			Print(LIST, my_number, contact_num);	//전체 연락처 목록을 보여준다
		else if (Default_Menu == 1) {
			Add(LIST, contact_num); contact_num++;	//연락처를 추가하고 연락처 개수에 1을 더한다

			fopen_s(&contact_list, "contact_list.txt", "w");	//contact_list를 쓰기모드로 연다
			for (int i = 0; i < contact_num; i++)
				fprintf_s(contact_list, "%s %s %s\n", LIST[i].name, LIST[i].phone, LIST[i].email);
				//전체 연락처의 개수만큼 돌아가며 이름, 번호, 메일을 contact_list.txt에 print해준다
			fclose(contact_list);	//contact_list를 닫는다
		}

		else if (Default_Menu == 2) {
			int search_num;	//검색된 연락처의 개수를 담는 변수
			printf("\nSearch ☞ ");
			scanf_s("%s", search_string, sizeof(search_string));	//검색할 문자열을 받는다
			printf("\n------------------------------------------------------");
			printf("\nname\t phone\t\temail\n");
			printf("\n%d result\n", search_num = Search(LIST, SEARCH_LIST, contact_num, search_string));
			//Search함수에서 return된 값을 search_num에 저장하고 이를 출력한다
			printf("------------------------------------------------------\n");
			
			if (search_num != 0) {	//검색된 연락처의 개수가 0이 아닐때
				printf("\n1. Edit(edit, favorite, delete)\n2. Cancle\n==================\nSelect: ");
				scanf_s("%d", &Edit_Menu);	//edit메뉴의 버튼을 입력받는다

				if (Edit_Menu == 1) {
					Edit(LIST, SEARCH_LIST, FAVORITE_LIST, &favorite_num);	//연락처를 edit한다

					fopen_s(&contact_list, "contact_list.txt", "w");	//contact_list 파일을 쓰기 모드로 연다
					for (int i = 0; i < contact_num; i++) {
						if (!strcmp(LIST[i].name, "deleted")) {	//delete된 연락처는 print하지 않고 건너뛰고 전체 연락처 개수에 1을 뺀다
							contact_num--; continue;
						}
						fprintf_s(contact_list, "%s %s %s\n", LIST[i].name, LIST[i].phone, LIST[i].email);	//각 연락처의 이름, 번호, 메일을 파일에 print한다
					} fclose(contact_list);
					cout << "\nSucceeded." << endl;
				}
			}
		}

		if (Default_Menu == 3)
			Favorite(FAVORITE_LIST, favorite_num);	//즐겨찾기 목록을 보여준다
		else if (Default_Menu == 4)
			Recents(LIST, recent, SEARCH_LIST, contact_num, call_num);	//최근 기록을 보여준다
		else if (Default_Menu == 5)
			break;	//프로그램을 종료한다.
	}
	return 0;
}
