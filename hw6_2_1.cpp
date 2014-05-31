#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
extern "C" {
#include "avl.h"
#include "rb.h"
#include "bst.h"
}
using std::string;

void preorder_string_avl (const struct avl_node *node){
	if (node == NULL){
		return;
	}
	printf("%s ", ((char *)node->avl_data));
	if (node -> avl_link[0] != NULL || node -> avl_link[1] != NULL){
		putchar('(');
		preorder_string_avl(node -> avl_link[0]);
		putchar(',');
		putchar(' ');
		preorder_string_avl(node -> avl_link[1]);
		putchar(')');
	}
}

void preorder_string_rb (const struct rb_node *node){
	if (node == NULL){
		return;
	}
	printf("%s ", ((char *)node->rb_data));
	if (node -> rb_link[0] != NULL || node -> rb_link[1] != NULL){
		putchar('(');
		preorder_string_rb(node -> rb_link[0]);
		putchar(',');
		putchar(' ');
		preorder_string_rb(node -> rb_link[1]);
		putchar(')');
	}
}

void preorder_string_bst (const struct bst_node *node){
	if (node == NULL){
		return;
	}
	printf("%s ", ((char *)node->bst_data));
	if (node -> bst_link[0] != NULL || node -> bst_link[1] != NULL){
		putchar('(');
		preorder_string_bst(node -> bst_link[0]);
		putchar(',');
		putchar(' ');
		preorder_string_bst(node -> bst_link[1]);
		putchar(')');
	}
}

int char_compare(const void *pa , const void *pb , void *param){
	string nameSequence[] = {"Chang", "Chao", "Chen", "Cheng", "Chou", "Chu", "Chuang", "Fu", "Fuh", "Hsiang", "Hsu", "Hsueh", "Hung", "Jang", "Kao", "Kuo", "Lai", "Lee", "Liao", "Lin", "Liou", "Liu",  "Lu", "Lyuu", "Ouhyoung", "Oyang", "Shih", "Tsai", "Tseng", "Wang", "Wu", "Yang"};
	bool flag_A = false;
	bool flag_B = false;

	const char *char_A = (const char *) pa;
	const char *char_B = (const char *) pb;

	int result =  strcmp(char_A,char_B);
	if (result < 0)
		return -1;
	else
		return +1;
}

int main (){
	string name[] = {"Chuang", "Chou", "Chang", "Chao", "Chen", "Cheng", "Chu", "Fu", "Fuh", "Hsiang", "Hsu", "Hsueh", "Hung", "Jang", "Kao", "Kuo", "Lai", "Lee", "Liao", "Lin", "Liou", "Liu", "Lu", "Lyuu", "Ouhyoung", "Oyang", "Shih", "Tsai", "Tseng", "Wang", "Wu", "Yang"};
	struct avl_table *avl_tree;
	avl_tree = avl_create(char_compare,NULL,NULL);
	struct rb_table *rb_tree;
	rb_tree = rb_create(char_compare,NULL,NULL);
	struct bst_table *bst_tree;
	bst_tree = bst_create(char_compare,NULL,NULL);

	for (int i = 0; i < 32; ++i)
	{
		char *element_alv = (char *)malloc(sizeof(char) * (name[i].length() + 1));
		char *element_rb = (char *)malloc(sizeof(char) * (name[i].length() + 1));
		char *element_bst = (char *)malloc(sizeof(char) * (name[i].length() + 1));
		std::strcpy(element_alv,name[i].c_str());
		std::strcpy(element_rb,name[i].c_str());
		std::strcpy(element_bst,name[i].c_str());
		*(element_alv + (sizeof(char) * name[i].length())) = '\0';
		*(element_rb + (sizeof(char) * name[i].length())) = '\0';
		*(element_bst + (sizeof(char) * name[i].length())) = '\0';
		void **p_avl = avl_probe(avl_tree, element_alv);
		void **p_rb = rb_probe(rb_tree, element_rb);
		void **p_bst = bst_probe(bst_tree, element_bst);
	}

	preorder_string_bst(bst_tree->bst_root);
	printf("\n");
	preorder_string_avl(avl_tree->avl_root);
	printf("\n");
	preorder_string_rb(rb_tree->rb_root);
	puts("");
	return 0;
}
