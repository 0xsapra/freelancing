#include <stdio.h>
#include <string.h>
#include "text_manipulation.h"

/******************************************************** 
 * Prints a pass or fail message for the specified test.* 
 ********************************************************/
void test_assert(int test_result, const char *test_name, int test_number) {
   if (test_result)  {
      printf("pass %s %d\n", test_name, test_number);
   } else {
      printf("fail %s %d\n", test_name, test_number);
   }
}

int main() {
   char result[MAX_STR_LEN + 1]; 
   int spaces_removed, test_result;
   int prev_spaces = spaces_removed;

   remove_spaces("test    is", result, &spaces_removed);
   test_result = strcmp(result, "test    is") == 0 && spaces_removed == prev_spaces;
   test_assert(test_result, "remove_spaces", 2);

   remove_spaces("   test    is     ", result, &spaces_removed);
   test_result = strcmp(result, "test    is") == 0 && spaces_removed == 8;
   test_assert(test_result, "remove_spaces", 2);


   remove_spaces("   ", result, &spaces_removed);
   test_result = strcmp(result, "") == 0 && spaces_removed == 3;
   test_assert(test_result, "remove_spaces", 2);

   center("terps", 13, result);
   test_assert(strcmp(result, "    terps    ") == 0, "center", 1);

   center("terps", 33, result);
   test_assert(strcmp(result, "              terps              ") == 0, "center", 1);

   center("terps", 3, result);
   test_assert(strcmp(result, "") == 0, "center", 1);

   center("te  ra [] ]    )( ps", 30, result);
   test_assert(strcmp(result, "     te  ra [] ]    )( ps     ") == 0, "center", 1);

   center("", 1, result);
   test_assert(strcmp(result, "") == 0, "center", 1);

   center("", 2, result);
   test_assert(strcmp(result, "") == 0, "center", 1);

   center(NULL, 3, result);
   test_assert(strcmp(result, "") == 0, "center", 1);

   return 0;
}
