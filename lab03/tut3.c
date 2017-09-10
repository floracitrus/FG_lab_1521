while(*a !='\0' && *b != '\0'){
	if(*a!=*b){
		return *a-*b;
	}
	a++;
	b++;
}

if(*a =='\0'&&*b=='\0'){
	return 0;
}
return *a-*b;



typedef struct _node2 Node2;
struct _node2{
	Node2 *next;
	char str[100];
}
104


Node1 *makeNode()
sql alche
