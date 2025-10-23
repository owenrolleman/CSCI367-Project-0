#include "trie.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_WORD_COUNT 100
#define MAX_WORD_LENGTH 30

int main() {

  // Import first 100 Lines from text doc
  FILE *file = fopen("twl06.txt", "r");
  if (file == NULL) {
      printf("File Error\n");
      return 1;
  }

  char buffer[MAX_WORD_LENGTH];

  printf("TEST START\nTest 1: trie_create() ... ");
  trie_node *myTrie = trie_create();

  if (myTrie == NULL) {
      printf("Failed\n");
      return 1;
  } else {
      printf("Passed\n");
  }

  printf("\nTest 2: trie_insert() ... ");
  int test_insert = 0;
  int lines_read = 0;

  for (int i = 0; i < MAX_WORD_COUNT; i++) {
      if (fgets(buffer, sizeof(buffer), file) != NULL) {
          buffer[strcspn(buffer, "\n")] = '\0'; // remove newline from buffer
          lines_read++;
          test_insert += trie_insert(myTrie, buffer, strlen(buffer));
      }
  }

  fclose(file);

  if (lines_read != test_insert) {
      printf("Failed\n");
      return 1;
  } else {
      printf("Passed\n");
  }
  printf("\nTest 3: trie_search() ... ");

  char *words[] = {"abandon", "abandoned", "aback"};


  for (int i = 0; i < 3; i++) {
      if (!trie_search(myTrie, words[i], strlen(words[i]))) {
          printf("Failed\n");
          return 1;
      }
  }
  printf("Passed\n");
  printf("\nTest 4: trie_delete() ... ");

  char *myWord = "deleteme";
  int myWordLen = strlen(myWord);

  int a = trie_insert(myTrie, myWord, myWordLen); // 1
  int b = trie_search(myTrie, myWord, myWordLen); // 1

  trie_delete(myTrie, myWord, myWordLen);

  int c = trie_search(myTrie, myWord, myWordLen); // 0

  if (!a || !b || c) {
      printf("Failed\n");
      return 1;
  }
  printf("Passed\n");
  printf("\n\nALL TESTS PASSED\n");
  return 0;
}
