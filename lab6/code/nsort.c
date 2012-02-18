#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int exit_status = 0;
int debug = 0;

typedef struct node *node_ref;
struct node {
  double item;
  node_ref link;
};

void usage () {
  printf("nsort [−d]\n");
  printf("    −d Output is printed in debug format.\n");
  exit_status = 1;
}

node_ref insert(node_ref head, double num) {
  node_ref prev = NULL;
  node_ref curr = head;

  while (curr != NULL) {
    if (curr->item > num) break;
    prev = curr;
    curr = curr->link;
  }

  node_ref new = malloc (sizeof (struct node));
  assert (new != NULL);
  new->item = num;
  new->link = curr;

  if (prev == NULL) head = new;
  else {
    prev->link = new;
  }
  return head;
}

node_ref getNums() {
  node_ref list = NULL;

  while (1) {
    double num;
    int scancount = scanf("%lg", &num);

    if (scancount == EOF) {
      printf("done\n"); break;
    } else if (scancount == 1) {
      list = insert(list, num);
    } else {
      printf("bad number\n");
    }
  }
  return list;
}


void print_list(node_ref list) {
  while (list != NULL) {
    if (debug) {
      printf ("&list= %p\n", (void*) &list);
      printf ("list= %p\n", (void*) list);
      printf ("%p -> struct node {item= %.15g, link= %p}\n",
          (void*) list, list->item, (void*) list->link);
      printf ("NULL= %p\n", (void*) NULL);
    }
    else
      printf("%24.15g\n", list->item);

    node_ref tmp = list;
    list = list->link;
    /*printf("freeing in printl");*/
    /*free (tmp);*/
  }
}

int main (int argc, char **argv) {
  char ch;

  if (argc > 2)  usage();
  else if (argc == 2) {
    ch = getopt(argc, argv, "d");
    if (ch != 'd') usage();
    else debug = 1;
  }

  if (!exit_status) {
    node_ref numlist = getNums();
    print_list(numlist);

    // free
    while (numlist != NULL) {
      printf("freeing");
      node_ref tmp = numlist->link;
      free (numlist);
      numlist = tmp;
    }
  }

  return exit_status;
}

