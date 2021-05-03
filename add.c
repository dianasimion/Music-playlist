// Copyright 2020 Simion Diana-Maria 311CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./data.h"
#include "./delete.h"
#include "./add.h"

void add_first(struct DoubleLinkedList* list, struct Data data_song,
				FILE* out) {
	// daca lista este goala, ii adaugam primul nod
	if (list->size == 0) {
		struct Node *new = malloc(sizeof(struct Node));
		new->next = NULL;
		new->prev = NULL;
		list->head = new;
		list->tail = new;
		list->cursor = new;
		new->data = data_song;
		list->size++;
		return;
	} else {
		// daca melodia deja exista in playlist o stergem si o adaugam din nou
		if (is_in_list(list, data_song)) {
			delete_song(list, data_song, out);
			add_first(list, data_song, out);
			return;
		} else {
			// adaugam melodia pe prima pozitie
			struct Node *new = malloc(sizeof(struct Node));
			new->next = list->head;
			new->prev = NULL;
			list->head->prev = new;
			list->head = new;
			new->data = data_song;
			list->size++;
			return;
		}
	}
}

void add_last(struct DoubleLinkedList* list, struct Data data_song, FILE* out) {
	// daca lista este goala, ii adaugam primul nod
	if (list->size == 0) {
		struct Node* new = malloc(sizeof(struct Node));
		new->next = NULL;
		new->prev = NULL;
		list->head = new;
		list->tail = new;
		list->cursor = new;
		new->data = data_song;
		list->size++;
		return;
	} else {
		// daca melodia deja exista in playlist o stergem si o adaugam din nou
		if(is_in_list(list, data_song)) {
			delete_song(list, data_song, out);
			add_last(list, data_song, out);
			return;
		} else {
			// adaugam melodia pe ultima pozitie
			struct Node* new = malloc(sizeof(struct Node));
			new->next = NULL;
			new->prev = list->tail;
			list->tail->next = new;
			list->tail = new;
			new->data = data_song;
			list->size++;
			return;
		}
	}
}

void add_after(struct DoubleLinkedList* list, struct Data data_song,
				FILE *out) {
	// daca nu exista cursor ignoram comanda
	if (list->cursor == NULL) {
		return;
	}
	// daca dorim sa adaugam melodia dupa pozitia pe care se afla cursorul
	// ignoram comanda
	if (strcmp(list->cursor->data.title, data_song.title) == 0) {
		return;
	}
	if (list->size == 0) {
		return;
	} else {
		// daca melodia deja exista in playlist o stergem si o adaugam din nou
		if(is_in_list(list, data_song)) {
			delete_song(list, data_song, out);
			add_after(list, data_song, out);
		} else {
			// adaugam melodia pe pozitia urmatoare cursorului
			struct Node* new = malloc(sizeof(struct Node));
			new->prev = list->cursor;
			new->next = list->cursor->next;
			if(list->cursor->next ==NULL) {
				list->tail = new;
			} else {
				list->cursor->next->prev = new;
			}
			list->cursor->next = new;
			new->data = data_song;
			list->size++;
		}
	}
}
