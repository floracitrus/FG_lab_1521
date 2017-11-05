int sumList(Node *L)
{
   Node *cur = L;
   int   sum = 0;
   while (cur != NULL) {
      sum += cur->value;
      cur = cur->next;
   }
   return sum;
}
int sumList(Node *L)
{	
	int sum = 0;
	if(L == NULL) return sum;
	else
		return L->value + sumList(L->next);
}

Node *newNode(int v)
{
   Node *new;
   new = malloc(sizeof(Node));
   new->value = v;
   new->next = NULL;
   return new;
}

Node *append(Node *L, int v)
{
   if (L == NULL)
      L = newNode(v);
   else {
      Node *cur = L;
      while (cur->next != NULL)
         cur = cur->next;
      cur->next = newNode(v);
   }
   return L;
}

Node *append(Node *L, int v)
{
   if (L == NULL)
      return newNode(v);
   else {
      L->next = append(L->next, v);
      return L;
   }
}
