// Copyright 2020 Simion Diana-Maria 311CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./data.h"
#include "./show.h"
#include "./delete.h"
#include "./add.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Error\n");
		return -1;
	}

	char media_in[NMAX], media_out[NMAX];
	snprintf(media_in, strlen(argv[1]) + 1, "%s", argv[1]);
	snprintf(media_out, strlen(argv[2]) + 1, "%s", argv[2]);

	// deschiderea fisierelor de intrare si de iesire
	FILE *in = open_file(media_in, "rt");
	FILE *out = open_file(media_out, "wt");

	int q;
	fscanf(in, "%d\n", &q);
	char line[NMAX_L];
	char song[NMAX];
	char path[NMAX];

	struct DoubleLinkedList *list = malloc(sizeof(struct DoubleLinkedList));
	init_list(list);
	for(int i = 0; i < q; ++i) {
		// citirea fiecarei linii
		fgets(line, NMAX_L, in);
		line[strlen(line) - 1] ='\0';
		struct Data data_song;
		char *command, *rest = NULL;

		// retinerea comenzii corespunzatoare
		if (strncmp(line, "ADD", 3) == 0 || strncmp(line, "DEL_SONG", 8) == 0) {
			command = __strtok_r(line, " ", &rest);
			command = __strtok_r(NULL, "\n", &rest);

			snprintf(song, strlen(command) + 1, "%s", command);
			snprintf(path, strlen(song) + 7, "songs/%s", song);
			snprintf(command, strlen(line) + 1, "%s", line);

			FILE *song_file = open_file(path, "rb");
			fseek(song_file, -94, SEEK_END);

			memset(&data_song, 0, sizeof(struct Data));

			// citirea datelor din fisierul binar corespunzator
			fread(&data_song, sizeof(struct Data), 1, song_file);

			fclose(song_file);
		} else {
			command = __strtok_r(line, "\n", &rest);
		}

		if (strncmp(command, "ADD", 3) == 0) {
			if (strcmp(command, "ADD_FIRST") == 0) {
				add_first(list, data_song, out);
			} else if (strcmp(command, "ADD_LAST") == 0) {
				add_last(list, data_song, out);
			} else if (strcmp(command, "ADD_AFTER") == 0) {
				add_after(list, data_song, out);
			}
		} else if (strncmp(command, "DEL", 3) == 0) {
			if (strcmp(command, "DEL_FIRST") == 0) {
				delete_first(list, out);
			} else if (strcmp(command, "DEL_LAST") == 0) {
				delete_last(list, out);
			} else if (strcmp(command, "DEL_CURR") == 0) {
				delete_curr(list, out);
			} else if (strcmp(command, "DEL_SONG") == 0) {
				delete_song(list, data_song, out);
			}
		} else if (strncmp(command, "MOVE", 4) == 0) {
			if (strcmp(command, "MOVE_NEXT") == 0) {
				move_next(list, out);
			} else if (strcmp(command, "MOVE_PREV") == 0) {
				move_prev(list, out);
			}
		} else if (strncmp(command, "SHOW", 4) == 0) {
			if (strcmp(command, "SHOW_FIRST") == 0) {
				show_first(list, out);
			} else if (strcmp(command, "SHOW_LAST") == 0) {
				show_last(list, out);
			} else if (strcmp(command, "SHOW_CURR") == 0) {
				show_curr(list, out);
			} else if (strcmp(command, "SHOW_PLAYLIST") == 0) {
				show_playlist(list, out);
			}
		}
	}

	// eliberarea memoriei si inchiderea fisierelor
	free_list(&list);
	fclose(in);
	fclose(out);
	return 0;
}
