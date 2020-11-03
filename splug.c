#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct information{
    char name[10];
    char adress[80];
    char phone_number[15];
    struct information *link;
}info;

int enter_member(info *);
int information_contro(int , info *, info *, info *);
int all_member(info *, info *);
int save_data(FILE *, info *, info *);

int main(void)
{
    info *data, *tmp, *end, *start = NULL;
    int i, n = 1;
    FILE *fdata; 
    if((fdata = fopen("save.txt", "r")) != NULL){
	while(n){
	    char c[10] = {0}, tr[1] = {0};
	    end = (info *) calloc(105, sizeof(char));
	    if(start == NULL)
		start = end;
	    else
		tmp -> link = end;
	    fscanf(fdata, "%[^\"]s", end -> name);
	    fscanf(fdata, "%1c", &tr);
	    fscanf(fdata, "%[^\t]s", end -> adress); 
	    fscanf(fdata, "%1c", &tr);
	    fscanf(fdata, "%[^\n]s", end -> phone_number); 
	    fscanf(fdata, "%1c", &tr);
	    fflush(stdin);
	    if(strcmp(c, end -> name) == 0)
	    {
		free(end);
		end = tmp;
		end -> link = NULL;
		n = 0;
	    }
	    tmp = end;
	}
	fclose(fdata);
    }
    while(1){
	printf("               == 메뉴 ==               \n");
	printf("1. 모든 주소록 정보 출력\n2. 회원 등록\n3. 회원 정보 검색\n4. 회원 정보 수정\n5. 회원 삭제\n6. 프로그램 종료\n");
	printf("========================================\n");
	printf("선택할 기능의 번호를 입력하세요. : ");
	scanf("%d", &i);
	getchar();
	printf("========================================\n");
	if(i == 1){
	    if(start == NULL)
		printf("등록된 주소록이 없습니다.\n");
	    else
		all_member(start, data);
	}
	else if(i == 2){
	    end = (info *) calloc(105, sizeof(char));
	    enter_member(end);
	    if(start == NULL){
		start = end;
	    }
	    else{
		int j = 1;
		data = start;
		while(j == 1 && data != NULL)
		{
		    if(strcmp(data -> name, end -> name) > 0){
			if(data == start)
			{
			    start = end;
			    end -> link = data;
			    j = 0;
			}
			else{
			    end -> link = data;
			    tmp -> link = end;
			    j = 0;
			}
		    }
		    tmp = data;
		    data = data -> link;
		}
		if(j == 1){
		    end -> link = NULL;
		    tmp -> link = end;
		}
	    }
	}
	else if(3 <= i && i <= 5){
	    if(start == NULL)
		printf("등록된 주소록이 없습니다.\n");
	    else
		information_contro(i, start, data, tmp);
	}
	else if(i == 6) 
	    break;
	else 
	    printf("잘 못 입력하셨습니다.\n");
    }
    save_data(fdata, start, data);
    return 0;
}

int all_member(info *start, info *data)
{
    data = start;
    while(data != NULL)
    {
	printf("이름 : %s\n", data -> name);
	printf("주소 : %s\n", data -> adress);
	printf("전화번호 : %s\n", data -> phone_number);
	printf("========================================\n");
	data = data -> link;
    }

    return 0;
}

int enter_member(info *end)
{
    printf("이름을 입력하세요. : ");
    gets(end -> name);
    printf("주소를 입력하세요. : ");
    gets(end -> adress);
    printf("전화번호를 입력하세요. : ");
    gets(end -> phone_number);
    return 0;
}

int information_contro(int i, info *start, info *data, info *tmp)
{
    char *find_name[10];
    data = start;
    printf("이름을 입력하세요. : ");
    gets(find_name[10]);
    while(data != NULL)
    {
	if(strcmp(data -> name, find_name[10]) == 0)
	    break;
	else{
	    tmp = data;
	    data = data -> link;
	}
    }
    if(data == NULL){
	printf("회원이 존재하지 않습니다.\n");
	return 0;
    }

    if(i == 3){
	printf("이름 : %s\n", data -> name);
	printf("주소 : %s\n", data -> adress);
	printf("전화번호 : %s\n", data -> phone_number);
    }
    else if(i == 4){
	printf("수정을 위해 정보를 전부  다시 입력해 주세요.\n");
	printf("이름 : ");
	gets(data -> name);
	printf("주소 : ");
	gets(data -> adress);
	printf("전화번호 : ");
	gets(data -> phone_number);
	printf("정보가 수정되었습니다.\n");
    }
    else if(i == 5){
	if(start == data)
	    start = data -> link;
	else
	    tmp -> link = data -> link;
	printf("정보가 삭제되었습니다.\n");
	free(data);
    }
    return 0;

}

int save_data(FILE *fdata, info *start, info *data)
{
    data = start;
    fdata = fopen("save.txt", "w");
    while (data != NULL)
    {
	fprintf(fdata, "%s", data -> name);
	fprintf(fdata, "\"");
	fprintf(fdata, "%s", data -> adress);
	fprintf(fdata, "\t");
	fprintf(fdata, "%s", data -> phone_number);
	fprintf(fdata, "\n");
	data = data -> link;
    }
    fclose(fdata);
    return 0;
}
