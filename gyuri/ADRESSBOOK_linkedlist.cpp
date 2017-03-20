#include<iostream>
#include<stdlib.h>
#include<string.h>
#include"Person.h"
using namespace std;

int main() {
	LIST = (CONTACT)calloc(1, sizeof(PERSON));
	FAVORITE= (CONTACT)calloc(1, sizeof(PERSON));
	int b;
	char name[10];
	while (true) {
		printf("\n<Button>\n");
		printf("1. Add\n2. Find\n3. Show Favorites\nSelect : ");
		scanf_s("%d", &b);
		if (b == 1)
			Add(LIST);
		else if (b == 2) {
			search_cnt = 1;
			int edit_num, edit_or_delete;
			scanf("%s", name);
			Find(name, LIST);
			printf("\nWhich one do you want? : ");
			scanf("%d", &edit_num);
			printf("1. Edit\n2. Delete\n3.Add to Favorite\n");
			scanf("%d", &edit_or_delete);
			if (edit_or_delete == 1) 
				Edit(edit_num);
			else if (edit_or_delete == 2) 
				Delete(edit_num);
			else if (edit_or_delete == 3) 
				Add_to_Favorite(edit_num);

		}
		else if (b == 3)
			Show_Favorites();

	}
	free(LIST);
	return 0;
}






