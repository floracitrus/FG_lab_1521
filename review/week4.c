int myStrCmp(char *a, char *b)
{
   while (*a != '\0' && *b != '\0') {
      if (*a < *b) return -1;
      if (*a > *b) return 1;
      if (*a == *b) { a++; b++; }
   }
   if (*a == '\0' && *b != '\0') return -1;
   if (*a != '\0' && *b == '\0') return 1;
   return 0;
}