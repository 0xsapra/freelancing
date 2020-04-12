#include <stdio.h>
#include <string.h>
#include "document.h"

int main() {
   Document doc;
   load_file(&doc, "testfile");
   print_document(&doc);
   save_document(&doc, "testsave");

   return 0;
}
