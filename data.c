// Copyright 2020 Simion Diana-Maria 311CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./data.h"

FILE *open_file(const char* filename, const char* mode) {
	// deschiderea fisierelor
	FILE *f = fopen(filename, mode);
	if(!f) {
		fprintf(stderr, "Could not open %s\n", filename);
	}
	return f;
}

// functie care verifica daca o melodie se afla in lista, comparand titlurile
// pe care le-am considerat unice
int is_in_list(struct DoubleLinkedList* list, struct Data data_song) {
	struct Node* it = list->head;
	while(it != NULL) {
		if (strcmp(it->data.title, data_song.title) == 0) {
			return 1;
		}
		it = it->next;
	}
	return 0;
}

// initializarea listei
void init_list(struct DoubleLinkedList* list) {
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->cursor = NULL;
}

// eliberarea memoriei
void free_list(struct DoubleLinkedList **pp_list) {
	// daca lista este goala
    if ((*pp_list)->size == 0) {
    	free(*pp_list);
    	return;
    } else {
	    struct Node* it = (*pp_list)->head;
	    struct Node* curr;
	    curr = it->next;
	    while (curr != NULL) {
	    	// elliberam fiecare nod
	        free(it);
	        it = curr;
	        curr = it->next;
	    }
	    free(it);
	    free(*pp_list);
	}
}

// mutarea cursorului la dreapta
void move_next(struct DoubleLinkedList* list, FILE* out) {
	if (list->size == 0) {
		fprintf(out, "Error: no track playing\n");
	} else if (list->cursor->next != NULL) {
		list->cursor = list->cursor->next;
	}
}

// mutarea cursorului la stanga
void move_prev(struct DoubleLinkedList* list, FILE* out) {
	if (list->size == 0) {
		fprintf(out, "Error: no track playing\n");
	} else if (list->cursor->prev != NULL){
		list->cursor = list->cursor->prev;
	}
}
