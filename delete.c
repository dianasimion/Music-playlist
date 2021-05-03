// Copyright 2020 Simion Diana-Maria 311CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./data.h"
#include "./delete.h"

struct Node* remove_first(struct DoubleLinkedList* list) {
	// stergem primul nod din lista
	struct Node* removed;
	removed = list->head;
    list->head = removed->next;
    if (list->size != 1) {
    	list->head->prev = NULL;
    }
    list->size--;
	return removed;
}

void delete_first(struct DoubleLinkedList* list, FILE *out) {
	if (list->size == 0) {
		fprintf(out, "Error: delete from empty playlist\n");
	} else {
		// gasim nodul pe care dorim sa-l stergem
		struct Node* removed = remove_first(list);
		// mutam cursorul la dreapta; daca nu este posibil, la stanga
		if (removed == list->cursor) {
			// daca lista ramane goala, cursorul devine NULL
			if (list->size == 0) {
				list->cursor = NULL;
			} else if (list->cursor->next != NULL){
				move_next(list, out);
			} else if (list->cursor->prev != NULL) {
				move_prev(list, out);
			}
		}
		// eliberam memoria alocata nodului pe care l-am sters
		free(removed);
	}
}

struct Node* remove_last(struct DoubleLinkedList* list) {
	// stergem ultimul nod din lista
	struct Node* removed;
	removed = list->tail;
    list->tail = removed->prev;
    if (list->size != 1) {
    	list->tail->next = NULL;
    }
    list->size--;
	return removed;
}

void delete_last(struct DoubleLinkedList* list, FILE *out) {
	if (list->size == 0) {
		fprintf(out, "Error: delete from empty playlist\n");
	} else {
		// gasim nodul pe care dorim sa-l stergem
		struct Node* removed = remove_last(list);
		// mutam cursorul la dreapta; daca nu este posibil, la stanga
		if (removed == list->cursor) {
			// daca lista ramane goala, cursorul devine NULL
			if (list->size == 0) {
				list->cursor = NULL;
			} else if (list->cursor->next != NULL){
				move_next(list, out);
			} else if (list->cursor->prev != NULL) {
				move_prev(list, out);
			}
		}
		// eliberam memoria alocata nodului pe care l-am sters
		free(removed);
	}
}

struct Node* remove_curr(struct DoubleLinkedList* list) {
	if (list->size == 0) {
		return NULL;
	}
	// stergem nodul pe care se afla cursorul
	struct Node* removed = list->cursor;
	if (list->size == 1) {
		list->head = NULL;
		list->tail = NULL;
		list->cursor = NULL;
	} else {
		// refacem legaturile intre nodurile vecine
		// celui pe care se afla cursorul
		if(removed->prev == NULL) {
			removed->next->prev = NULL;
			list->head = removed->next;
		}
		if (removed->next == NULL) {
			removed->prev->next = NULL;
			list->tail = removed->prev;
		}
		if (removed->next!= NULL && removed->prev != NULL) {
			removed->prev->next = removed->next;
			removed->next->prev = removed->prev;
		}
	}
	list->size--;
	return removed;
}

void delete_curr(struct DoubleLinkedList* list, FILE *out) {
	if (list->size == 0) {
		fprintf(out, "Error: no track playing\n");
	} else if (list->cursor == NULL) {
		fprintf(out, "Error: no track playing\n");
	} else {
		// gasim nodul pe care dorim sa-l stergem
		struct Node* removed = remove_curr(list);
		// mutam cursorul la dreapta; daca nu este posibil, la stanga
		if (removed->next != NULL){
			move_next(list, out);
		} else if (removed->prev != NULL) {
			move_prev(list, out);
		}
		// eliberam memoria alocata nodului pe care l-am sters
		free(removed);
		return;
	}
}

struct Node* remove_song(struct DoubleLinkedList* list, struct Data data_song) {
	struct Node* removed = list->head;
	if (list->size == 1) {
		list->head = NULL;
		list->tail = NULL;
		list->cursor = NULL;
	} else {
		int ok = 0, okx = 0;
		// daca melodia se afla pe ultima pozitie
		if (strcmp(list->tail->data.title, data_song.title) == 0) {
			removed = remove_last(list);
			ok = 1;
			okx = 1;
		} else if (strcmp(list->head->data.title, data_song.title) == 0) {
			// daca melodia se afla pe prima pozitie
			removed = remove_first(list);
			ok = 1;
			okx = 1;
		}

		while(removed->next != NULL && ok == 0) {
			if (strcmp(removed->data.title, data_song.title) == 0) {
				ok = 1;
			}
			removed = removed->next;
		}
		// refacem legaturile intre nodurile vecine nodului pe care l-am sters
		if (ok == 1 && okx == 0){
			removed = removed->prev;
			if(removed->prev == NULL) {
				removed->next->prev = NULL;
				list->head = removed->next;
			}
			if (removed->next == NULL) {
				removed->prev->next = NULL;
				list->tail = removed->prev;
			}
			if (removed->next != NULL && removed->prev != NULL) {
				removed->prev->next = removed->next;
				removed->next->prev = removed->prev;
			}
		}
	}
	list->size--;
	return removed;
}

void delete_song(struct DoubleLinkedList* list, struct Data data_song,
				FILE *out) {
	if (!is_in_list(list, data_song)) {
		fprintf(out , "Error: no song found to delete\n");
	} else {
		if(list->head != NULL) {
			struct Node* it = list->head;
			// daca cursorul se afla pe melodia pe care o stergem
			// si este prima din lista
			if (it == list->cursor && strcmp(it->data.title, data_song.title) == 0) {
				delete_curr(list, out);
				return;
			} else if (strcmp(list->cursor->data.title, data_song.title) == 0) {
				// daca cursorul se afla pe melodia pe care o stergem
				delete_curr(list, out);
				return;
			} else {
				// daca cursorul se afla pe melodia pe care dorim sa o stergem
				// si este ultima din lista
				if (strcmp(list->tail->data.title, data_song.title) == 0) {
					delete_last(list, out);
					return;
				} else {
					// daca cursorul nu se afla pe melodia pe care dorim sa o stergem
					int ok = 0;
					while (it->next != NULL && ok == 0) {
						if (strcmp(it->data.title, data_song.title) == 0) {
							ok = 1;
						}
						it = it->next;
					}
					it = it->prev;
					it = remove_song(list, data_song);
					free(it);
					return;
				}
			}
		}
	}
}
