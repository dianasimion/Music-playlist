// Copyright 2020 Simion Diana-Maria 311CA

#ifndef ADD_H_
#define ADD_H_

void add_first(struct DoubleLinkedList* list, struct Data data_song,
				FILE* out);

void add_last(struct DoubleLinkedList* list, struct Data data_song,
				FILE* out);

void add_after(struct DoubleLinkedList* list, struct Data data_song,
				FILE *out);

#endif  // ADD_H_
