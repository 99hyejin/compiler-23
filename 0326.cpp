#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "testdata.txt"
#define STsize 1000 //size of string table
#define HTsize 100 //size of hash table
// more define variables…
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

// more global variables…
ERRORtypes err;
FILE* fp; //to be a pointer to FILE
char input;
//Initialize - open input file
void initialize()
{
	fp = fopen(FILE_NAME, "r");
	input = fgetc(fp);
}


//변수 추가 정의
int hash_code; // 식별자 해시코드
int found; // 식별자가 이미 존재하는 경우를 위한 flag
int same; // 식별자의 첫번째 인덱스(starting index)


/*ComputeHS
Compute the hash code of identifier by summing the ordinal values of its
characters and then taking the sum modulo the size of HT.*/

void ComputeHS(int nid, int nfree)
{
    int c = 0; // 문자 더한 값 넣는 변수
    int i;
    for (i = nid; i < nfree - 1; i++)
        c += (int)ST[i]; // 반복문 이용해서 각 문자 값 더하기
    hash_code = c % HTsize; // 해시테이블 크기로 나누어서 해시코드 계산
}


/*LookupHS
For each identifier, Look it up in the hashtable for previous occurrence
of the identifier.if find a match, set the found flag as true.
Otherwise false.
if find a match, save the starting index of ST in same id. */

void LookupHS(int nid, int hscode)
{
    HTpointer htp; //구조체 변수 선언
    int i, j;

    found = 0; // 식별자가 나오지 않은 상태
    if (HT[hscode] != NULL) { // 비어있지 않은 경우
        htp = HT[hscode];
        while (htp != NULL && found == 0) {
            found = 1; // flag를 true로 설정
            i = htp->index;
            j = nid;
            same = i; // 해당 인덱스를 저장

            while (ST[i] != '\0' && ST[j] != '\0' && found == 1) { // 해시테이블 끝까지 각 식별자 비교하면서 겹치는 것 찾기

                if (ST[i] != ST[j])
                    found = 0; // 식별자가 또 나오지 않은 것이므로 flag를 false로 설정

                else {
                    i+=1;
                    j+=1; // 이중 while문 반복 위해
                }
            }
            htp = htp->next;
        }
    }
}

