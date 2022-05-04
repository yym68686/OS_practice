#ifndef _PARSE_H
#define _PARSE_H

enum {
    TREE_BACK,
    TREE_PIPE,
    TREE_REDIRICT,
    TREE_BASIC,
    TREE_TOKEN,
};

split(line) => tree(TREE_TOKEN) tree(TREE_TOKEN)

"echo abc"
+ TREE_BASIC
  + child_vector
    + TREE_TOKEN
      + token = "echo"
    + TREE_TOKEN
      + token = "abc"

"echo abc >log"
+ TREE_REDIRICT
  + TREE_BASIC
    + child_vector
      + TREE_TOKEN
        + token = "echo"
      + TREE_TOKEN
        + token = "abc"
  + TREE_TOKEN  
    + token = ">"
  + TREE_TOKEN  
    + token = "log"

#define MAX_CHILD 10
typedef struct {
    int type;
    char *token;
    int child_count;
    tree_t *child_vector[MAX_CHILD];
} tree_t;

extern tree_t *tree_new(int type);
extern tree_t *tree_get_child(tree_t *this, int index);
extern void tree_append_child(tree_t *this, tree_t *child);
extern tree_t *parse_tree();
extern void tree_dump(tree_t *this, int level);

#endif
