#include <stdio.h>
#include <stdlib.h>

typedef struct element element;

struct element {
	int payload;
	element *next;
};

typedef struct list {
	element *head;
	element **tail;
} list;

void enqueue(list *list, element *item) {
	item->next = NULL;
	*list->tail = item;
	list->tail = &item->next;
}

list* initialize_list() {
	list *new_list = (list*) malloc(sizeof(list));
	new_list->head = NULL;
	new_list->tail = &new_list->head;
	return new_list;
}

//TODO: void enqueue_front(list *list, element* elem);
//TODO: element* dequeue(list *list);
//TODO: void delete_elements(list *list, int value);

int main(void) {
	list *all_numbers = initialize_list();
	element *elem = (element*) malloc(sizeof(element));
	elem->payload = 100;
	enqueue(all_numbers, elem);
}
