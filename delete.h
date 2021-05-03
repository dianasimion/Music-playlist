// Copyright 2020 Simion Diana-Maria 311CA

#ifndef DELETE_H_
#define DELETE_H_

struct Node* remove_first(struct DoubleLinkedList* list);

void delete_first(struct DoubleLinkedList* list, FILE *out);

struct Node* remove_last(struct DoubleLinkedList* list);

void delete_last(struct DoubleLinkedList* list, FILE *out);

struct Node* remove_curr(struct DoubleLinkedList* list);

void delete_curr(struct DoubleLinkedList* list, FILE *out);

struct Node* remove_song(struct DoubleLinkedList* list, struct Data data_song);

void delete_song(struct DoubleLinkedList* list, struct Data data_song,
				FILE *out);

#endif  // DELETE_H_
