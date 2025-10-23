

/* trie.c - code for trie data structure.
 *  Author: Owen Rolleman
 *  Date:   21 Oct 2025
 *  Used sources:
        Geeksforgeeks (https://www.geeksforgeeks.org/c/implementation-of-trie-prefix-tree-in-c/)
 */

#include "trie.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/**
 * Create an empty trie
 *
 * @return Pointer to the root node.
 *
 */
trie_node *trie_create(void) {

    trie_node *node = malloc(sizeof(trie_node));

    if (node == NULL) {
        printf("Malloc failed\n");
        return node;
    }

    node->isEndOfWord = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }

    return node;
}

/**
 * Insert a word in the given trie.
 *
 * @param root node of a trie
 * @param word to insert
 * @return 1 on success, 0 on failure. If the word already exists, return 1.
 */
int trie_insert(trie_node *root, char *word, unsigned int word_len) {

    trie_node *current = root;
    for (int i = 0; i < word_len; i++) {

        char c = word[i];
       // Skip non-lowercase letters
       if (c < 'a' || c > 'z') continue;
       int index = c - 'a';

        if (current->children[index] == NULL) {
            current->children[index] = trie_create();
             if (!current->children[index]) return 0; // malloc failure
        }
        current = current->children[index];
    }
    current->isEndOfWord = 1;
    return 1;
}


/**
 * Search a word in the given trie. Return 1 if word exists, otherwise return 0.
 *
 * @param root node of a trie
 * @param word Word to search in the trie
 * @param word_len Length of the word
 * @return 1 if the word exists in the trie, otherwise returns 0
 */
int trie_search(trie_node *root, char *word, unsigned int word_len) {

  trie_node *current = root;
  for (int i = 0; i < word_len; i++) {
      int index = word[i] - 'a';
      if (current->children[index] == NULL) {
          return 0;
      }
      current = current->children[index];
  }
  return (current != NULL && current->isEndOfWord);
}


/**
 * Delete a word in the given trie.
 *
 * @param root node of a trie
 * @param word Word to search in the trie
 * @param word_len Length of the word
 */
void trie_delete(trie_node *root, char *word, unsigned int word_len) {
    recursive_delete(root, word, 0);
}

/**
 * Delete a word in the given trie.
 *
 * @param root node of a trie
 * @param word Word to search in the trie
 * @param depth Current depth in trie
 */
trie_node* recursive_delete(trie_node *root, char *word, unsigned int depth) {
    // Base case: reached a null node
    // Nothing to delete here, so just return
    if (root == NULL) {
        return root;
    }

    // If we've reached the end of the word
    if (depth == strlen(word)) {
        // Unmark the current node as the end of a word
        if (root->isEndOfWord) {
            root->isEndOfWord = 0;
        }

        // If this current node has no children, free it
        if (is_empty(root)) {
            free(root);
            root = NULL;
        }
        return root;
    }

    int index = word[depth] - 'a';

    // Recursively delete the child corresponding to this character
    // Assign it back to ensure that if the child was freed, the parent pointer is updated
    root->children[index] = recursive_delete(root->children[index], word, depth + 1);

    // If original root has no children and is not the end of another word, free it
    if (is_empty(root) && !root->isEndOfWord) {
        free(root);
        root = NULL;
    }
    return root;
}

    /**
    * Check if a given node in a trie has any children
    *
    * @param root node of the trie
    * @returns 1 if the trie is empty, 0 if it is not empty
    */
int is_empty(trie_node *root) {

  for (int i = 0; i < ALPHABET_SIZE; i++) {
      if (root->children[i] != NULL) {
          return 0;
      }
  }
  return 1;
}
