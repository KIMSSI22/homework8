#include<stdio.h>
#include<stdlib.h>

typedef struct Node {  //리스트 구조체
	int key;  //데이터 변수
	struct Node* llink;  //이전 노드를 가르키는 포인터
	struct Node* rlink;  //다음 노드를 가르키는 포인터
} listNode;

//함수 리스트
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;  //헤드 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = "); 
		scanf(" %c", &command);  //명령 문자 입력

		switch(command) {  //케이스에 따른 함수 실행
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {  //list 초기화

	if(*h != NULL)  //NULL아 아니면 할당된 메모리 해제
		freeList(*h);

	// headNode에 대한 메모리를 할당하여 리턴
	*h = (listNode*)malloc(sizeof(listNode));  
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){  //리스트 메모리 해제

	if(h->rlink == h)  //헤드 다음노드가 헤드면 메모리 해제
	{
		free(h);
		return 1;
	}

	listNode* p = h->rlink;  //헤드 다음 변수 선언

	listNode* prev = NULL;  //이전 변수 선언 및 초기화
	while(p != NULL && p != h) {  //다음변수가 NULL이 아니고 헤드가 아니면
		prev = p;  
		p = p->rlink;
		free(prev);  //이전 메모리 해제
	}
	free(h); //헤드 메모리 해제
	return 0;
}



void printList(listNode* h) {  //출력
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {  //아무것도 없으면
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;  //헤드 다음 변수

	while(p != NULL && p != h) {  //다음변수가 NULL이 아니고 헤드가 아니면
		printf("[ [%d]=%d ] ", i, p->key);  //데이터 값
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



int insertLast(listNode* h, int key) {  //마지막 노드 삽입

	if (h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));  //메모리 할당
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h) //헤드 다음이 헤드일때
	{
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	} else {
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}

	return 1;
}



int deleteLast(listNode* h) {  //마지막 노드 삭제

	if (h->llink == h || h == NULL)  //다음변수가 헤드이고 NULL일때
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink;

	nodetoremove->llink->rlink = h;
	h->llink = nodetoremove->llink;

	free(nodetoremove);  //헤드 이전, 즉 마지막 노드 메모리 해제

	return 1;
}


int insertFirst(listNode* h, int key) {   //맨앞에 노드 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode));  //메모리 할당
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;


	node->rlink = h->rlink;
	h->rlink->llink = node;
	node->llink = h;
	h->rlink = node;


	return 1;
}


int deleteFirst(listNode* h) {  //첫번째 노드 삭제

	if (h == NULL || h->rlink == h)  //다음변수가 헤드이고 NULL일때
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink;

	nodetoremove->rlink->llink = h;
	h->rlink = nodetoremove->rlink;

	free(nodetoremove);  //해드 다음, 즉 첫번째 노드 메모리 해제

	return 1;

}


int invertList(listNode* h) {  //역순으로


	if(h->rlink == h || h == NULL) {  //다음변수가 헤드이고 NULL일때
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	h->llink = h->rlink;  //최종 바뀔 링크 유지 

	while(n != NULL && n != h){  //헤드 다음이 NULL이 아니고 헤드가 아닐때
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->rlink = middle;

	return 0;
}



int insertNode(listNode* h, int key) {  //오름차순으로 삽입

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));  //메모리 해제
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->rlink == h)  
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) {
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


int deleteNode(listNode* h, int key) {  //노드 삭제

	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) {  //헤드 다음이 NULL이 아니고 헤드가 아닐때
		if(n->key == key) {
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 0;
		}

		n = n->rlink;  //그리고 다음 링크
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}