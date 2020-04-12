#include "photoalbum.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Photo* create_photo(int id, const char* description) {

	char* desc;
	int description_length;

	Photo *photo = (Photo*) malloc(sizeof(Photo));
	if (!photo) {
		return NULL;
	}
	if ( description != NULL ) {
		description_length = strlen(description) + 1;
		desc = (char*) malloc(description_length);
		memcpy(desc, description, description_length);	
	} else {
		desc = NULL;
	}
	

	photo->id = id;
	photo->description = desc;

	return photo;
}

void print_photo(Photo *photo) {

	char* desc;
	int id;

	if(photo == NULL) {
		return;
	}
	id = photo->id;
	desc = photo->description;
	if ( desc == NULL ) {
		printf("Photo Id: %d, Description: None\n", id);
	} else {
		printf("Photo Id: %d, Description: %s\n", id, desc);
	}
	return;
}

void initialize_album(Album *album) {

	if(album == NULL || !album) {
		return;
	}
	album->size = 0;
}

void print_album(const Album *album) {

	int size, i;
	Photo* photo;

	if( album == NULL ) {
		return;
	}
	size = album->size;
	if(size == 0) {
		printf("Album has no photos.\n");
	} else {
		for (i = 0; i < size; i++) {
			photo = album->all_photos[i];
			print_photo(photo);
		}	
	}
	return;	
}

void add_photo_to_album(Album *album, int id, const char *description) {

	int size;
	Photo* photo;

	if( album == NULL ) {
		return;
	}
	size = album->size;
	if( size >= MAX_ALBUM_SIZE ) {
		return;
	}
	if( album == NULL ) {
		return;
	}
	photo = create_photo(id, description);
	if( photo == NULL ) {
		return;
	} else {
		album->all_photos[size] = photo;
		size += 1;
		album->size = size;
	}
}

void destroy_photo(Photo *photo) {
	
	if ( photo == NULL ) {
		return;
	}
	free(photo->description);
	free(photo);
	photo->description = NULL;
	photo = NULL;
	return;
}

void destroy_album(Album *album) {
	
	int size, i;
	Photo* photo;

	if ( album == NULL ) {
		return;
	}
	size = album->size;
	for(i = 0;  i < size; i++) {
		photo = album->all_photos[i];
		destroy_photo(photo);
	}
	album->size = 0;
	return;

}

