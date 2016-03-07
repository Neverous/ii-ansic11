/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>
#include<stdbool.h>

struct node
{
	long double val;
	struct node* next;
};

#define HEAPSIZE 1000
unsigned int freeheap = 0;
struct node heap[HEAPSIZE];

struct node* readlist(void);
void printlist(struct node* p);
struct node* sort(struct node* p);

int main(void)
{
	struct node *root;

	root = readlist();
	printlist(root);
	root = sort(root);
	printlist(root);
	return 0;
}

struct node* readlist(void)
{
	int size;
	struct node* first = &heap[freeheap];
	printf("Give list length: ");
	scanf("%u", &size);
	for(int s = 0; s < size; ++ s)
	{
		if(s)
			heap[freeheap - 1].next = heap + freeheap;

		printf("%d element: ", s + 1);
		scanf("%Lf", &heap[freeheap].val);
		heap[freeheap ++].next = NULL;
	}

	return first;
}

void printlist(struct node* p)
{
	if(!p)
		return;

	putchar('[');
	do
	{
		printf("%.6Lf%s",  p->val, (p->next)?", ":"");
	}
	while(p = p->next);
	puts("]");

	return;
}

struct node* sort(struct node* p)
{
	bool done = true;
	struct node *prev = NULL,
				*act = NULL,
				*temp = NULL;
	while(done)
	{
		done = false;
		prev = NULL;
		for(act = p; act && act->next; act = act->next)
		{
			if(act->val > act->next->val)
			{
				temp = act->next;
				act->next = act->next->next;
				temp->next = act;
				if(prev) // change previous pointer(the one before our swap)
					prev->next = temp;

				if(act == p) // remeber first element properly
					p = temp;

				act = temp->next;
				done = true;
			}

			prev = act;
		}
	}

	return p;
}
