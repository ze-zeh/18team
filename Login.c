﻿#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char admin_id[] ="1234";
char admin_password[] ="1234";

int loginFunction(int* num_account) {

	FILE* memlist;
	
	memlist = fopen("./accountlist.txt", "r");
	if (memlist == NULL)
	{
		printf("파일 읽기 실패\n");
		exit(1);
	}

	char c = ' ';
	char** account_id = (char**)malloc(sizeof(char*) * (*num_account));
	char** account_password = (char**)malloc(sizeof(char*) * (*num_account));

	for (int i = 0; i < *num_account; i++) {
		account_id[i] = (char*)malloc(sizeof(char) * 13);
		account_password[i] = (char*)malloc(sizeof(char) * 13);
	}

	int j;
	for (j = 0; j < *num_account; j++) {   // for(j=0;j<num_account;j++)

		int i = 0;
		while (1) {
			c = fgetc(memlist);
			if (c == ',') {
				account_id[j][i] = NULL;
				break;
			}
			account_id[j][i++] = c;
		}
		i = 0;
		while (1) {
			c = fgetc(memlist);
			if (c == ',') {
				account_password[j][i] = NULL;
				break;
			}
			account_password[j][i++] = c;
		}
		while (fgetc(memlist) != '\n') {

		}
	}
	
	int row = 0;
	char stdid[14];
	char stdpassword[18];

	while (row == 0) {
		system("cls");
		printf("아이디를 입력하세요:");
		fgets(stdid, 14, stdin);

		// 배열 크기가 넘어가면 입력 버퍼를 비움.
		if (strlen(stdid) > 13) {
			while (getchar() != '\n');
		}
		stdid[strcspn(stdid, "\n")] = 0;
		for (int i = 0; i < *num_account; i++) {       //i<num_account 로 수정
			if (strcmp(account_id[i], stdid) == 0) {

				
					pass: printf("\n비밀번호를 입력하세요:");
				system("cls");
					fgets(stdpassword, 18, stdin);
					if (strlen(stdid) > 12) {
						while (getchar() != '\n');
					}
					stdpassword[strcspn(stdpassword, "\n")] = 0;
					if (strcmp(account_password[i], stdpassword) == 0) {
						printf("\n로그인 성공\n");
						system("pause");
						row = i + 1;
						break;
					}
					else {
						printf("비밀번호가 틀립니다.\n");
						system("pause");
						goto pass;
					}
				
			}
			else if (strcmp(admin_id, stdid) == 0) {
				pass_admin: printf("관리자 비밀번호를 입력해주세요:");
				fgets(stdpassword, 18, stdin);
				if (strlen(stdid) > 12) {
					while (getchar() != '\n');
				}
				stdpassword[strcspn(stdpassword, "\n")] = 0;
				if (strcmp(admin_password, stdpassword) == 0) {
					printf("\n로그인 성공\n");
					row = -1;
					break;
				}
				else {
					printf("비밀번호가 틀립니다.");
					system("pause");
					goto pass_admin;
				}
			}

			if (i == (*num_account - 1))
			{
				printf("존재하지 않는 아이디 입니다\n");
				system("pause");
			}
		}
	}

	free(account_id);
	free(account_password);

	fclose(memlist);
	return row;
}
