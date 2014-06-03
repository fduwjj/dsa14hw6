#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include "avl_ntudsa.h"
}
#include <string>
#include <cstring>
#include <iostream>
#include <vector>

using std::string;

#pragma pack(push)
#pragma pack(1)
struct studentGrade
{
	int studentID;
	int hw1_Grade;
	int hw2_Grade;
	int hw3_Grade;
	int hw4_Grade;
	int hw5_Grade;
	int Avg_Grade;
};
#pragma pack(pop)

std::vector<string> studentID_Hash;

void search_rank (const struct avl_node *node, int rank){
	if (node == NULL){
		printf("Invalid Rank Number!!\n");
		return;
	}
	int Newrank = (node->avl_cnode[1] + 1);
	if (Newrank == rank)
	{
		std::cout << studentID_Hash[((studentGrade*)(node->avl_data))->studentID] << '\n';
	}
	else if (Newrank > rank)
	{
		if (node -> avl_link[1] != NULL){
			search_rank (node -> avl_link[1], rank);
		}
		else{
			printf("Right side of tree build Error!!\n");
			return;
		}
	}
	else if (Newrank < rank)
	{
		if (node -> avl_link[0] != NULL){
			search_rank (node -> avl_link[0], (rank - Newrank));
		}
		else{
			printf("Left side of tree build Error or Rank out of Range!!!!\n");
			return;
		}
	}
}

int char_compare(const void *pa , const void *pb , void *param){
	const studentGrade *student_A = (const studentGrade *) pa;
	const studentGrade *student_B = (const studentGrade *) pb;
	int result; 

	// int *pTemp_1 = const_cast <int*>(&(student_A -> studentID));
	// int *pTemp_2 = const_cast <int*>(&(student_B -> studentID));

	if ((student_A -> Avg_Grade) > (student_B -> Avg_Grade))
	{
		return +1;
	}
	else if ((student_A -> Avg_Grade) < (student_B -> Avg_Grade))
	{
		return -1;
	}
	if ((student_A -> hw2_Grade) > (student_B -> hw2_Grade))
	{
		return +1;
	}
	else if ((student_A -> hw2_Grade) < (student_B -> hw2_Grade))
	{
		return -1;
	}
	if ((student_A -> hw3_Grade) > (student_B -> hw3_Grade))
	{
		return +1;
	}
	else if ((student_A -> hw3_Grade) < (student_B -> hw3_Grade))
	{
		return -1;
	}
	if ((student_A -> hw5_Grade) > (student_B -> hw5_Grade))
	{
		return +1;
	}
	else if ((student_A -> hw5_Grade) < (student_B -> hw5_Grade))
	{
		return -1;
	}
	if ((student_A -> hw4_Grade) > (student_B -> hw4_Grade))
	{
		return +1;
	}
	else if ((student_A -> hw4_Grade) < (student_B -> hw4_Grade))
	{
		return -1;
	}
	if ((student_A -> hw1_Grade) > (student_B -> hw1_Grade))
	{
		return +1;
	}
	else if ((student_A -> hw1_Grade) < (student_B -> hw1_Grade))
	{
		return -1;
	}
	
	string stu_A, stu_B;
	stu_A = studentID_Hash[(student_A -> studentID)];
	stu_B = studentID_Hash[(student_B -> studentID)];
	char *char_A = new char[stu_A.size() + 1];
	std::strcpy(char_A,stu_A.c_str());
	*(char_A + (sizeof(char) * stu_A.length())) = '\0';
	char *char_B = new char[stu_B.size() + 1];
	std::strcpy(char_B,stu_B.c_str());
	*(char_B + (sizeof(char) * stu_B.length())) = '\0';
	result =  strcmp(char_A,char_B);

	if (result > 0)
		return -1;
	else
		return +1;
}

int main (){
	string stringInput = "";
	string stringTemp = "";
	char *cstring, *cTemp, *tmp;
	struct avl_table *tree;
	int iCount = 0;
	tree = avl_create(char_compare,NULL,NULL);	
	while(std::getline(std::cin,stringInput)){
		cstring = new char[stringInput.size() + 1];
		std::strncpy(cstring, stringInput.c_str(), stringInput.size()+1);
		cTemp = std::strtok(cstring, " ");
		stringTemp.assign(cTemp);
		if (stringTemp == "push")
		{
			int grade, iTotal;
			iTotal = 0;
			tmp = strtok(NULL, " ");
			studentGrade *element = (studentGrade*)malloc(sizeof(studentGrade));
			if (element == NULL)
			{
				printf("Struct Construction Error!\n");
			}
			stringTemp.assign(tmp);
			studentID_Hash.push_back(stringTemp);
			element -> studentID = iCount;
			iCount += 1;
			int *pTemp = &(element -> studentID);
			int i = 0;
			for ( ; i < 5; ++i)
			{
				pTemp++;
				tmp = strtok(NULL, " ");
				grade = atoi(tmp);
				iTotal += grade;
				*pTemp = grade;
			}
			element -> Avg_Grade = iTotal / 5;
			// std::cout << "hw2_Grade is:" << element -> hw2_Grade << '\n';
			// std::cout << "Average score is:" << element -> Avg_Grade << '\n';
			void **p = avl_probe(tree, element);
		}
		if (stringTemp == "search")
		{
			int rank;
			tmp = strtok(NULL, " ");
			rank = atoi(tmp);
			search_rank (tree->avl_root, rank);
		}
		delete [] cstring;
		cstring = tmp = NULL;
	}
	return 0;
}
