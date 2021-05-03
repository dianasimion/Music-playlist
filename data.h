// Copyright 2020 Simion Diana-Maria 311CA

#ifndef DATA_H_
#define DATA_H_

#define NMAX 100
#define NMAX_L 100
#define NMAX_data 30

struct Data {
	char title[NMAX_data];
	char artist[NMAX_data];
	char album[NMAX_data];
	char year[4];
};

struct Node {
	struct Data data;
	struct Node *next, *prev;
};

struct DoubleLinkedList {
	int size;
	struct Node *head, *tail, *cursor;
};

FILE *open_file(const char* filename, const char* mode);

int is_in_list(struct DoubleLinkedList* list, struct Data data_song);

void init_list(struct DoubleLinkedList* list);

void free_list(struct DoubleLinkedList **pp_list);

void move_next(struct DoubleLinkedList* list, FILE* out);

void move_prev(struct DoubleLinkedList* list, FILE* out);

#endif  // DATA_H_
