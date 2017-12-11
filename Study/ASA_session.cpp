//code by Heonjin

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// SIZE : test 파일에서 총 행의 최대 개수
// RESULT_SIZE : 데이터 처리 후 중복 데이터를 제거한 행의 최대 개수
#define SIZE 5000
#define RESULT_SIZE 4000

typedef struct obj 
{
   char src_ip[25];
   char src_port[10];
   char dst_ip[25];
   char dst_port[10];
   char byte[10];
}obj;

typedef struct dummy
{
   char arg0[25];
   char arg1[25];
   char arg2[25];
   char arg3[25];
   char arg4[25];
   char arg5[25];
   char arg6[25];
   char arg7[25];
   char arg8[25];
   char arg9[25];
   char arg10[25];
}dummy;

typedef struct count
{
   char value[20];
   int num;
}count;

typedef struct count_byte
{
   char src[20];
   char dst[20];
   double num;
}count_byte;

int compare_func(const void *a, const void *b);
int byte_compare_func(const void *a, const void *b);

int main()
{
   FILE *f = NULL;
   dummy dummy1 = { '\0', };
   obj obj[SIZE] = { '\0', };
   count answer_src_ip[RESULT_SIZE] = {'\0',};
   count answer_src_port[RESULT_SIZE] = { '\0', };
   count answer_dst_ip[RESULT_SIZE] = { '\0', };
   count answer_dst_port[RESULT_SIZE] = { '\0', };
   count_byte answer_byte[RESULT_SIZE] = { '\0', };
   int i, j, k;
   int index=0;

   if ((f= fopen("sess.txt", "r")) == NULL)
      return 0;

   ////////////////////
   /// 파일에서 src_ip, src_port dst_ip, dst_port, byte 뽑아오기
   ////////////////////
   printf("===============================================================================\n");
   printf("전체 목록 출력\n");
   printf("===============================================================================\n");
   while (!feof(f))
   {
      fscanf(f, "%s %s  %s %s  %s %s %s %s %s %s %s", &dummy1.arg0, &dummy1.arg1, &dummy1.arg2, &dummy1.arg3, &dummy1.arg4, &dummy1.arg5, &dummy1.arg6, &dummy1.arg7, &dummy1.arg8, &dummy1.arg9, &dummy1.arg10);

      // src_ip : arg2
      for (i = 0; dummy1.arg2[i] != ':'; i++);
      for (j = 0; j < i; j++)
         obj[index].src_ip[j] = dummy1.arg2[j];
      obj[index].src_ip[i] = '\0';


      // src_port : arg2
      for (j=i+1, k=0; dummy1.arg2[j];j++, k++)
         obj[index].src_port[k] = dummy1.arg2[j];
      obj[index].src_port[k] = '\0';
      

      // dst_ip : arg4
      for (i = 0; dummy1.arg4[i] != ':'; i++);
      for (j = 0; j < i; j++)
         obj[index].dst_ip[j] = dummy1.arg4[j];
      obj[index].dst_ip[i] = '\0';


      // dst_port : arg4
      for (j = i + 1, k = 0; dummy1.arg4[j] != ','; j++)
         obj[index].dst_port[k++] = dummy1.arg4[j];
      obj[index].dst_port[k] = '\0';


      // byte : arg8
      for (i = 0; dummy1.arg8[i] != ','; i++)
         obj[index].byte[i] = dummy1.arg8[i];
      obj[index].byte[i] = '\0';


      //printf("[%4d]%22s%10s%22s%10s%10s\n", index+1, obj[index].src_ip, obj[index].src_port, obj[index].dst_ip, obj[index].dst_port, obj[index].byte);
      
      index++;
      
   }


   ////////////////////
   /// src_ip 통계내기
   ////////////////////
   for (i = 0; i < index-1; i++)
   {   
      for (j = 0;; j++)
      {
         // 목록에 없을때 새로 추가
         if (answer_src_ip[j].value[0] == '\0')
         {
            strcpy(answer_src_ip[j].value, obj[i].src_ip);
            answer_src_ip[j].num++;
            break;
         }

         // 목록에 있으면 1 증가
         if (strcmp(obj[i].src_ip, answer_src_ip[j].value) == 0)
         {
            answer_src_ip[j].num++;
            break;
         }      
      }
   }


   ////////////////////
   /// src_port 통계내기
   ////////////////////
   for (i = 0; i < index - 1; i++)
   {
      for (j = 0;; j++)
      {
         // 목록에 없을때 새로 추가
         if (answer_src_port[j].value[0] == '\0')
         {
            strcpy(answer_src_port[j].value, obj[i].src_port);
            answer_src_port[j].num++;
            break;
         }

         // 목록에 있으면 1 증가
         if (strcmp(obj[i].src_port, answer_src_port[j].value) == 0)
         {
            answer_src_port[j].num++;
            break;
         }
      }
   }


   ////////////////////
   /// dst_ip 통계내기
   ////////////////////
   for (i = 0; i < index - 1; i++)
   {
      for (j = 0;; j++)
      {
         // 목록에 없을때 새로 추가
         if (answer_dst_ip[j].value[0] == '\0')
         {
            strcpy(answer_dst_ip[j].value, obj[i].dst_ip);
            answer_dst_ip[j].num++;
            break;
         }

         // 목록에 있으면 1 증가
         if (strcmp(obj[i].dst_ip, answer_dst_ip[j].value) == 0)
         {
            answer_dst_ip[j].num++;
            break;
         }
      }
   }
   

   ////////////////////
   /// dst_port 통계내기
   ////////////////////
   for (i = 0; i < index - 1; i++)
   {
      for (j = 0;; j++)
      {
         // 목록에 없을때 새로 추가
         if (answer_dst_port[j].value[0] == '\0')
         {
            strcpy(answer_dst_port[j].value, obj[i].dst_port);
            answer_dst_port[j].num++;
            break;
         }

         // 목록에 있으면 1 증가
         if (strcmp(obj[i].dst_port, answer_dst_port[j].value) == 0)
         {
            answer_dst_port[j].num++;
            break;
         }
      }
   }


   ////////////////////
   /// BYTE 통계내기
   ////////////////////
   for (i = 0; i < index - 1; i++)
   {
      for (j = 0;; j++)
      {
         // 목록에 없을때 새로 추가
         if (answer_byte[j].num == 0)
         {
            strcpy(answer_byte[j].src, obj[i].src_ip);
            strcpy(answer_byte[j].dst, obj[i].dst_ip);
            answer_byte[j].num += atoi(obj[i].byte);
            break;
         }

         // 목록에 있으면 1 증가
         if ((strcmp(obj[i].src_ip, answer_byte[j].src) == 0) && (strcmp(obj[i].dst_ip, answer_byte[j].dst) == 0))
         {
            answer_byte[j].num += atoi(obj[i].byte);
            break;
         }
      }
   }


   ////////////////////
   /// src_ip 정렬
   ////////////////////
   for (i = 0; answer_src_ip[i].num != 0; i++);
   qsort(answer_src_ip, i, sizeof(count), compare_func);

   ////////////////////
   /// src_port 정렬
   ////////////////////
   for (i = 0; answer_src_port[i].num != 0; i++);
   qsort(answer_src_port, i, sizeof(count), compare_func);

   ////////////////////
   /// dst_ip 정렬
   ////////////////////
   for (i = 0; answer_dst_ip[i].num != 0; i++);
   qsort(answer_dst_ip, i, sizeof(count), compare_func);

   ////////////////////
   /// dst_port 정렬
   ////////////////////
   for (i = 0; answer_dst_port[i].num != 0; i++);
   qsort(answer_dst_port, i, sizeof(count), compare_func);

   ////////////////////
   /// BYTE 정렬
   ////////////////////
   for (i = 0; answer_byte[i].num != 0; i++);
   qsort(answer_byte, i, sizeof(count_byte), byte_compare_func);


   int tmep_count=0;
   ////////////////////
   /// src_ip 결과출력
   ////////////////////
   printf("\n\n===============================================================================\n");
   printf("src_ip 목록 출력\n");
   printf("===============================================================================\n");
   for (i = 0; answer_src_ip[i].num != 0; i++)
   {
      if (i > 9) {
         break;
      }
      else {
         printf("[%4d]%22s   (%d)   ", i + 1, answer_src_ip[i].value, answer_src_ip[i].num);
         tmep_count += answer_src_ip[i].num;
         //for (j = 0; j < answer_src_ip[i].num; j++)
         //   printf("#");
         printf("\n");
      }
   }
   printf("\n총: %d개\n중복 제거 후: %d개\n", index, i);


   ////////////////////
   /// src_port 결과출력
   ////////////////////
   printf("\n\n===============================================================================\n");
   printf("src_port 목록 출력\n");
   printf("===============================================================================\n");
   tmep_count = 0;
   for (i = 0; answer_src_port[i].num != 0; i++)
   {
      if (i > 9) {
         break;
      }
      else {
         printf("[%4d]%22s    (%d)    ", i + 1, answer_src_port[i].value, answer_src_port[i].num);
         tmep_count += answer_src_port[i].num;
         //for (j = 0; j < answer_src_port[i].num; j++)
         //    printf("#");
         printf("\n");
      }
   }
   printf("\n총: %d개\n중복 제거 후: %d개\n", index, i);


   ////////////////////
   /// dst_ip 결과출력
   ////////////////////
   printf("\n\n===============================================================================\n");
   printf("dst_ip 목록 출력\n");
   printf("===============================================================================\n");
   tmep_count = 0;
   for (i = 0; answer_dst_ip[i].num != 0; i++)
   {
      if (i > 9) {
         break;
      }
      else {
         printf("[%4d]%22s   (%d)   ", i + 1, answer_dst_ip[i].value, answer_dst_ip[i].num);
         tmep_count += answer_dst_ip[i].num;
         //for (j = 0; j < answer_dst_ip[i].num; j++)
         //    printf("#");
         printf("\n");
      }
   }
   printf("\n총: %d개\n중복 제거 후: %d개\n", index, i);


   ////////////////////
   /// src_port 결과출력
   ////////////////////
   printf("\n\n===============================================================================\n");
   printf("dst_port 목록 출력\n");
   printf("===============================================================================\n");
   tmep_count = 0;
   for (i = 0; answer_dst_port[i].num != 0; i++)
   {
      if (i > 9) {
         break;
      }
      else {
         printf("[%4d]%22s   (%d)   ", i + 1, answer_dst_port[i].value, answer_dst_port[i].num);
         tmep_count += answer_dst_port[i].num;
         //for (j = 0; j < answer_dst_port[i].num; j++)
         //   printf("#");
         printf("\n");
      }
   }
   printf("\n총: %d개\n중복 제거 후: %d개\n", index, i);


   ////////////////////
   /// BYTE 결과출력
   ////////////////////
   printf("\n\n===============================================================================\n");
   printf("BYTE 목록 출력\n");
   printf("===============================================================================\n");
   for (i = 0; answer_byte[i].num != 0; i++)
   {
      if (i > 9) {
         break;
      }
      else {
         printf("[%4d]%20s -> %-15s   (%.0lf byte)\n", i + 1, answer_byte[i].src, answer_byte[i].dst, answer_byte[i].num);
      }
   }
   printf("\n총: %d개\n중복 제거 후: %d개\n", index, i);
   return 0;
}

// qsort() 함수를 사용하기 위한 비교함수
int compare_func(const void *a, const void *b)
{
   count *ptr_a = (count *)a;
   count *ptr_b = (count *)b;

   if (ptr_a->num > ptr_b->num)
      return -1;
   else if (ptr_a->num == ptr_b->num)
      return 0;
   else
      return 1;
}

// qsort() 함수를 사용하기 위한 비교함수
int byte_compare_func(const void *a, const void *b)
{
   count_byte *ptr_a = (count_byte *)a;
   count_byte *ptr_b = (count_byte *)b;

   if (ptr_a->num > ptr_b->num)
      return -1;
   else if (ptr_a->num == ptr_b->num)
      return 0;
   else
      return 1;
}
