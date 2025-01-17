// Copyright 2024 AQ author, All Rights Reserved.
// This program is licensed under the AQ License. You can find the AQ license in
// the root directory.

#include "aqvm/base/linked_list/linked_list.h"

#include <stddef.h>

#include "aqvm/base/memory/memory.h"

int AqvmBaseLinkedList_AddNode(struct AqvmBaseLinkedList_LinkedList* list,
                               void* data) {
  if (list == NULL) {
    // TODO(logging)
    return -1;
  }

  struct AqvmBaseLinkedList_Node* new_node =
      (struct AqvmBaseLinkedList_Node*)AqvmBaseMemory_malloc(
          sizeof(struct AqvmBaseLinkedList_Node));
  if (new_node == NULL) {
    // TODO(logging)
    return -2;
  }
  new_node->data = data;
  new_node->prev = list->tail;
  new_node->next = NULL;
  if (list->tail != NULL) list->tail->next = new_node;
  list->tail = new_node;
  ++list->capacity;
  return 0;
}

int AqvmBaseLinkedList_CloseLinkedList(
    struct AqvmBaseLinkedList_LinkedList* list) {
  if (list == NULL) {
    // TODO(logging)
    return -1;
  }

  struct AqvmBaseLinkedList_Node* delete_node = list->head;
  struct AqvmBaseLinkedList_Node* next_node = NULL;
  while (list->capacity > 0) {
    next_node = delete_node->next;
    AqvmBaseMemory_free(delete_node);
    delete_node = next_node;
    --list->capacity;
  }
  return 0;
}

int AqvmBaseLinkedList_DeleteNode(struct AqvmBaseLinkedList_LinkedList* list,
                                  size_t index) {
  if (list == NULL || index >= list->capacity) {
    // TODO(logging)
    return -1;
  }

  struct AqvmBaseLinkedList_Node* delete_node = list->head;
  for (size_t i = 0; i != index; ++i) delete_node = delete_node->next;
  if (delete_node == NULL) {
    // TODO(logging)
    return -2;
  }
  if (list->head == delete_node) list->head = delete_node->next;
  if (list->tail == delete_node) list->tail = delete_node->prev;
  if (delete_node->prev != NULL) delete_node->prev->next = delete_node->next;
  if (delete_node->next != NULL) delete_node->next->prev = delete_node->prev;
  AqvmBaseMemory_free(delete_node);
  --list->capacity;
  return 0;
}

void* AqvmBaseLinkedList_GetData(struct AqvmBaseLinkedList_LinkedList* list,
                                 size_t index) {
  if (list == NULL || index >= list->capacity) {
    // TODO(logging)
    return NULL;
  }

  struct AqvmBaseLinkedList_Node* get_node = list->head;
  for (size_t i = 0; i != index; ++i) get_node = get_node->next;
  if (get_node == NULL) {
    // TODO(logging)
    return NULL;
  }
  return get_node->data;
}

int AqvmBaseLinkedList_InitializeLinkedList(
    struct AqvmBaseLinkedList_LinkedList* linked_list) {
  if (linked_list == NULL) {
    // TODO(logging)
    return -1;
  }
  linked_list->head = NULL;
  linked_list->tail = NULL;
  linked_list->capacity = 0;
  return linked_list;
}

int AqvmBaseLinkedList_InsertNode(struct AqvmBaseLinkedList_LinkedList* list,
                                  size_t index, void* data) {
  if (list == NULL || index >= list->capacity) {
    // TODO(logging)
    return -1;
  }

  struct AqvmBaseLinkedList_Node* prev_node = list->head;
  for (size_t i = 0; i != index; ++i) prev_node = prev_node->next;
  if (prev_node == NULL) {
    // TODO(logging)
    return -2;
  }

  struct AqvmBaseLinkedList_Node* insert_node =
      (struct AqvmBaseLinkedList_Node*)AqvmBaseMemory_malloc(
          sizeof(struct AqvmBaseLinkedList_Node));
  if (insert_node == NULL) {
    // TODO(logging)
    return -3;
  }
  insert_node->data = data;
  insert_node->prev = prev_node;
  insert_node->next = prev_node->next;
  prev_node->next = insert_node;
  if (list->tail == prev_node) {
    list->tail = insert_node;
  } else {
    insert_node->next->prev = insert_node;
  }
  ++list->capacity;
  return 0;
}

int AqvmBaseLinkedList_PrependNode(struct AqvmBaseLinkedList_LinkedList* list,
                                   void* data) {
  if (list == NULL) {
    // TODO(logging)
    return -1;
  }

  struct AqvmBaseLinkedList_Node* new_node =
      (struct AqvmBaseLinkedList_Node*)AqvmBaseMemory_malloc(
          sizeof(struct AqvmBaseLinkedList_Node));
  if (new_node == NULL) {
    // TODO(logging)
    return -2;
  }
  new_node->data = data;
  new_node->prev = NULL;
  new_node->next = list->head;
  list->head = new_node;
  if (new_node->next == NULL) {
    list->tail = new_node;
  } else {
    new_node->next->prev = new_node;
  }
  ++list->capacity;
  return 0;
}

int AqvmBaseLinkedList_SetData(struct AqvmBaseLinkedList_LinkedList* list,
                               size_t index, void* data) {
  if (list == NULL || index >= list->capacity) {
    // TODO(logging)
    return -1;
  }

  struct AqvmBaseLinkedList_Node* set_node = list->head;
  for (size_t i = 0; i != index; ++i) set_node = set_node->next;
  if (set_node == NULL) {
    // TODO(logging)
    return -2;
  }
  set_node->data = data;
  return 0;
}