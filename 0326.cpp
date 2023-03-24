#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "testdata.txt"
#define STsize 1000 //size of string table
#define HTsize 100 //size of hash table
// more define variables��
typedef struct HTentry* HTpointer;
typedef struct HTentry {
	int index; //index of identifier in ST
	HTpointer next; //pointer to next identifier
} HTentry;
enum errorTypes { noerror, illsp, illid, overst };
typedef enum errorTypes ERRORtypes;
char seperators[] = " .,;:?!\t\n";
HTpointer HT[HTsize];
char ST[STsize];

// more global variables��
ERRORtypes err;
FILE* fp; //to be a pointer to FILE
char input;
//Initialize - open input file
void initialize()
{
	fp = fopen(FILE_NAME, "r");
	input = fgetc(fp);
}


//���� �߰� ����
int hash_code; // �ĺ��� �ؽ��ڵ�
int found; // �ĺ��ڰ� �̹� �����ϴ� ��츦 ���� flag
int same; // �ĺ����� ù��° �ε���(starting index)


/*ComputeHS
Compute the hash code of identifier by summing the ordinal values of its
characters and then taking the sum modulo the size of HT.*/

void ComputeHS(int nid, int nfree)
{
    int c = 0; // ���� ���� �� �ִ� ����
    int i;
    for (i = nid; i < nfree - 1; i++)
        c += (int)ST[i]; // �ݺ��� �̿��ؼ� �� ���� �� ���ϱ�
    hash_code = c % HTsize; // �ؽ����̺� ũ��� ����� �ؽ��ڵ� ���
}


/*LookupHS
For each identifier, Look it up in the hashtable for previous occurrence
of the identifier.if find a match, set the found flag as true.
Otherwise false.
if find a match, save the starting index of ST in same id. */

void LookupHS(int nid, int hscode)
{
    HTpointer htp; //����ü ���� ����
    int i, j;

    found = 0; // �ĺ��ڰ� ������ ���� ����
    if (HT[hscode] != NULL) { // ������� ���� ���
        htp = HT[hscode];
        while (htp != NULL && found == 0) {
            found = 1; // flag�� true�� ����
            i = htp->index;
            j = nid;
            same = i; // �ش� �ε����� ����

            while (ST[i] != '\0' && ST[j] != '\0' && found == 1) { // �ؽ����̺� ������ �� �ĺ��� ���ϸ鼭 ��ġ�� �� ã��

                if (ST[i] != ST[j])
                    found = 0; // �ĺ��ڰ� �� ������ ���� ���̹Ƿ� flag�� false�� ����

                else {
                    i+=1;
                    j+=1; // ���� while�� �ݺ� ����
                }
            }
            htp = htp->next;
        }
    }
}

