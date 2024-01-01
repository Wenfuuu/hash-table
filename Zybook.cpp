#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 27

struct Food{
	char name[100];
	int price;
	Food *next;
	Food *prev;
};

Food* foodTable[SIZE];

void initializeTable(){
	for(int i = 0; i < SIZE; i++){
		foodTable[i] = NULL;
	}
}

Food* createFood(char name[100], int price){
	Food* newFood = (Food*)malloc(sizeof(Food));
	strcpy(newFood->name, name);
	newFood->price = price;
	newFood->next = newFood->prev = NULL;
	return newFood;
}

int calculateHash(char name[]){
	char firstLetter = name[0];
	if(firstLetter >= 'a' && firstLetter <= 'z'){
		return firstLetter - 'a';
	}
	if(firstLetter >= 'A' && firstLetter <= 'Z'){
		return firstLetter - 'A';
	}
	
	return SIZE-1;
}

void insertFood(char name[], int price){
	Food* newFood = createFood(name, price);
	int idx = calculateHash(name);
	
	if(!foodTable[idx]){
		foodTable[idx] = newFood;
	}else{
		newFood->next = foodTable[idx];
		foodTable[idx]->prev = newFood;
		foodTable[idx] = newFood;
	}
}

void view(){
	for(int i = 0; i < SIZE; i++){
		printf("%c. ", i+'A');
		
		Food* curr = foodTable[i];
		while(curr){
			printf("%s %d - ", curr->name, curr->price);
			curr = curr->next;
		}
		printf("\n");
	}
}

void deleteFood(char name[]){
	int idx = calculateHash(name);
	if(!foodTable[idx]){
		printf("Food doesn't exist\n");
		return;
	}
	if(strcmp(foodTable[idx]->name, name) == 0){
		if(!foodTable[idx]->next){
			free(foodTable[idx]);
			foodTable[idx] = NULL;
		}else{
			Food* temp = foodTable[idx];
			foodTable[idx] = foodTable[idx]->next;
			foodTable[idx]->prev = NULL;
			free(temp);
			temp = NULL;
		}
	}
	else{
		Food* curr = foodTable[idx];
		while(curr && strcmp(curr->name, name) != 0){
			curr = curr->next;
		}
		if(!curr){
			printf("Food doesn't exist\n");
		}else{
			if(!curr->next){
				Food* temp = curr;
				curr = curr->prev;
				curr->next = NULL;
				free(temp);
				temp = NULL;
			}else{
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				free(curr);
				curr = NULL;
			}
		}
	}
}

int main(){
	
	initializeTable();
	
	insertFood("Babi", 50000);
	insertFood("Baba", 40000);
	insertFood("Bubu", 45000);
	insertFood("#Ayam", 20000);
	
//	view();
//	printf("\n");
	
	deleteFood("Bubu");
	
	view();
	
	return 0;
}
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 27

struct Food{
	char name[100];
	int price;
	Food *next, *prev;
}*foodTable[SIZE];

void initializeTable(){
	for(int i = 0; i < SIZE; i++){
		foodTable[i] = NULL;
	}
}

Food* createFood(char name[], int price){
	Food* newFood = (Food*)malloc(sizeof(Food));
	strcpy(newFood->name, name);
	newFood->price = price;
	newFood->next = newFood->prev = NULL;
	return newFood;
}

int calculateHash(char name[]){
	char firstLetter = name[0];
	if(firstLetter >= 'a' && firstLetter <= 'z'){
		return firstLetter - 'a';
	}
	if(firstLetter >= 'A' && firstLetter <= 'Z'){
		return firstLetter - 'A';
	}
	
	return SIZE-1;
}

void insertFood(char name[], int price){
	int idx = calculateHash(name);
	Food* newFood = createFood(name, price);
	
	if(!foodTable[idx]){
		foodTable[idx] = newFood;
	}else{
		newFood->next = foodTable[idx];
		foodTable[idx]->prev = newFood;
		foodTable[idx] = newFood;
	}
}

void view(){
	for(int i = 0; i < SIZE; i++){
		printf("%d. ", i+1);
		
		Food* curr = foodTable[i];
		while(curr){
			printf("%s %d - ", curr->name, curr->price);
			curr = curr->next;
		}
		printf("\n");
	}
}

void deleteFood(char name[]){
	int idx = calculateHash(name);
	if(!foodTable[idx]){
		printf("Food doesn't exist\n");
		return;
	}
	if(strcmp(foodTable[idx]->name, name) == 0){
		if(!foodTable[idx]->next){
			free(foodTable[idx]);
			foodTable[idx] = NULL;
		}else{
			Food* temp = foodTable[idx];
			foodTable[idx] = foodTable[idx]->next;
			foodTable[idx]->prev = NULL;
			free(temp);
			temp = NULL;
		}
	}else{
		Food* curr = foodTable[idx];
		while(curr && strcmp(curr->name, name) != 0){
			curr = curr->next;
		}
		if(!curr){
			printf("Food doesn't exist\n");
		}else{
			if(!curr->next){
				Food* temp = curr;
				curr = curr->prev;
				curr->next = NULL;
				free(temp);
				temp = NULL;
			}else{
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				free(curr);
				curr = NULL;
			}
		}
	}
}

int main(){
	
	initializeTable();
	
	insertFood("pisang goreng", 10000);
	insertFood("Pisang keju", 15000);
	insertFood("Pisang coklat keju", 25000);
	
	deleteFood("pisang goreng");
	
	view();
	
	return 0;
}
*/
