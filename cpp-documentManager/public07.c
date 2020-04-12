#include <stdio.h>
#include <string.h>
#include "document.h"

int main() {
   Document doc;
   char doc_name[] = "Loading Document ";
   int data_lines = 8;
   char data[20][MAX_STR_SIZE + 1] = {
   "The first tomorrow is you need to take",
	"is cmsc131.  This course will be",
	"followed by cmsc132 (which is also based on Java).",
	"",
	"The next course you will take is cmsc216.",
	"This course relies on C.",
	"",
	"Ruby and Ocaml will be covered in cmsc330"
   };

   init_document(&doc, doc_name);
   load_document(&doc, data, data_lines);
   // replace_text(&doc, "tomorrow", "o");
   // print_document(&doc);
   // remove_text(&doc, "is");
   // print_document(&doc);
   // highlight_text(&doc, "course");
   print_document(&doc);

   return 0;
}
