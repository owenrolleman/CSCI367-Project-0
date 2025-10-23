#define ALPHABET_SIZE 26

typedef struct node {
    struct node *children[ALPHABET_SIZE];
    int isEndOfWord;
} trie_node;

trie_node *trie_create(void);
int trie_insert(trie_node *trie, char *word, unsigned int word_len);
int trie_search(trie_node *trie, char *word, unsigned int word_len);
void trie_delete(trie_node *trie, char *word, unsigned int word_len);

int is_empty(trie_node *trie);
trie_node* recursive_delete(trie_node *root, char *word, unsigned int depth);
