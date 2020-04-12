#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calendar.h"
#include "event.h"

int init_calendar(const char *name, int days,
                  int (*comp_func) (const void *ptr1, const void *ptr2),
                  void (*free_info_func) (void *ptr), Calendar ** calendar) {

	if ( !calendar || !(*calendar) || name == NULL || days < 1 ) {
		return FAILURE;
	}
	*calendar = (Calendar*)malloc(sizeof(Calendar));
	if (!(*calendar)) {
		return FAILURE;
	}
	(*calendar)->days = days;
	(*calendar)->total_events = 0;
	(*calendar)->comp_func = comp_func;
	(*calendar)->free_info_func = free_info_func;
	/* Setting Name */
	(*calendar)->name = (char *)malloc(strlen(name) + 1); /* +1 is important */
	if ( !(*calendar)->name ) {
		return FAILURE;
	}
	strcpy((*calendar)->name, name);
	/* Setting Events */
	(*calendar)->events = (Event **)calloc(days, sizeof(Event));
	if ( !(*calendar)->events ) {
		return FAILURE;
	}
	return SUCCESS;
}

int print_calendar(Calendar *calendar, FILE *output_stream, int print_all) {
	int i, days, total_events;
	Event *event;

	if (calendar == NULL || output_stream == NULL ) {
		return FAILURE;
	}
	if (print_all) {
		fprintf(output_stream, "Calendar's Name: \"%s\"\n", calendar->name);
		fprintf(output_stream, "Days: %d\n", calendar->days);
		fprintf(output_stream, "Total Events: %d\n\n", calendar->total_events);
	}
	fprintf(output_stream, "**** Events ****\n");
	days = calendar->days;
	for (i = 0; i < days; i++) { 
		total_events = calendar->total_events;
		event = calendar->events[i];
		if ( total_events <= 0 ) { break; }
		fprintf(output_stream, "Day %d\n", i + 1);
		while ( event ) {
			fprintf(output_stream, "Event's Name: \"%s\", ", event->name);
			fprintf(output_stream, "Start_time: %d, ", event->start_time);
			fprintf(output_stream, "Duration: %d\n", event->duration_minutes);
			event = event->next;
		}
	}
	return SUCCESS;
}

int destroy_calendar(Calendar *calendar) {
	int i, days;
	Event *event, *temp = NULL;
	
	if (!calendar) {
		return FAILURE;
	}
	days = calendar->days;
	for (i = 0; i < days; i++) {
		event = calendar->events[i];
		while (event) {
	  		temp = event;
	  		if (calendar->free_info_func && temp->info) {
	    		calendar->free_info_func(temp->info);
		  	}
	  		event = event->next;
	  		free(temp->name);
	  		free(temp);
		}
	}
	free(calendar->events);
	free(calendar->name);
	free(calendar);
	return SUCCESS;
}

int add_event(Calendar *calendar, const char *name, int start_time,
              int duration_minutes, void *info, int day) {

	Event *event, *curr_event, *temp = NULL;

	if (calendar == NULL || !name || start_time < 0 || start_time > 2400 ||
		duration_minutes <= 0 || day < 1) {
		return FAILURE;
  	}
  	if (day > calendar->days) {
  		return FAILURE;
  	}
  	event = (Event *)malloc(sizeof(Event));
  	if ( !event ) {
  		return FAILURE;
  	}
  	event->name = (char*) malloc( strlen(name) + 1 );
  	if (!event->name) {
  		return FAILURE;
  	}
  	strcpy(event->name, name);
  	event->start_time = start_time;
  	event->duration_minutes = duration_minutes;
  	event->info = info;
  	/* Get correct location to put this event to */
  	curr_event = calendar->events[day - 1];
	while ( curr_event ) {
		if (calendar->comp_func(event, curr_event) >= 0) {
			temp = curr_event;
			curr_event = curr_event->next;
		} else {
			break;
		}
	}
	if ( temp ) {
		temp->next = event;
		event->next = curr_event;
	} else {
		calendar->events[day - 1] = event;
		event->next = curr_event;
	}
	calendar->total_events++;
	return SUCCESS;
}

int find_event(Calendar *calendar, const char *name, Event **event);
int find_event_in_day(Calendar *calendar, const char *name, int day,
                      Event **event);
int remove_event(Calendar *calendar, const char *name);
void *get_event_info(Calendar *calendar, const char *name);
int clear_calendar(Calendar *calendar);
int clear_day(Calendar *calendar, int day);




