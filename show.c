// Copyright 2020 Simion Diana-Maria 311CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./data.h"
#include "./show.h"

void show_first(struct DoubleLinkedList* list, FILE* out) {
	if (list->size == 0) {
		fprintf(out, "Error: show empty playlist\n");
	} else {
		fprintf(out, "Title: %.30s\n", list->head->data.title);
		fprintf(out, "Artist: %.30s\n", list->head->data.artist);
		fprintf(out, "Album: %.30s\n", list->head->data.album);
		fprintf(out, "Year: %.4s\n", list->head->data.year);
	}
}

void show_last(struct DoubleLinkedList* list, FILE* out) {
	if (list->size == 0) {
		fprintf(out, "Error: show empty playlist\n");
	} else {
		fprintf(out, "Title: %.30s\n", list->tail->data.title);
		fprintf(out, "Artist: %.30s\n", list->tail->data.artist);
		fprintf(out, "Album: %.30s\n", list->tail->data.album);
		fprintf(out, "Year: %.4s\n", list->tail->data.year);
	}
}

void show_curr(struct DoubleLinkedList* list, FILE* out) {
	if (list->size == 0 || list->cursor == NULL) {
		fprintf(out, "Error: show empty playlist\n");
	} else {
		fprintf(out, "Title: %.30s\n", list->cursor->data.title);
		fprintf(out, "Artist: %.30s\n", list->cursor->data.artist);
		fprintf(out, "Album: %.30s\n", list->cursor->data.album);
		fprintf(out, "Year: %.4s\n", list->cursor->data.year);
	}
}

void show_playlist(struct DoubleLinkedList* list, FILE* out) {
	if (list->size == 0) {
		fprintf(out, "[]\n");
	} else {
		struct Node* curr = list->head;
		fprintf(out, "[");
		while(curr->next != NULL) {
			// afisarea titlului melodiei
			fprintf(out, "%.30s; ", curr->data.title);
			curr = curr->next;
		}
		fprintf(out, "%.30s]\n", curr->data.title);
	}
}
