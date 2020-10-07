#include "rede.h"
#include "random.h"

void rede(int rr){
	
	int i,r,x,y,Qc, cam;
	
	mountq(rr);

}


/***************************************************************/
/* Função: mountq                                             */
/* Descrição:                        */
/* Input: */
/* Output: */
/***************************************************************/
void mountq(int rr){

   int soma = 0, j, r;
   for(j=0;j<rr;j++)
      soma = soma + (j+1);
   
   q[0]=0;
   
   for(r=1;r<rr;r++)
      q[r]=(float)(((float)(rr+1-r)/(float)(rr*rr+rr-soma))+q[r-1]);
   
}

void return_pos(int *x, int *y, int rr){
	
	int c, min_number, max_number;
	float p1;

   p1 = genrand_real1();
   //printf("\n rede p1 = %f", p1);
   for(c=0;c<rr;c++){
   	//printf("\n q[%d] = %f", c, q[c]);
      if(p1<=q[c]) break;
   }
   
   min_number = -c;
   max_number = c;
   if(rand()%2){
	   if(rand()%2){
	   	*x=-c;
	   	*y=rand() % (max_number + 1 - min_number) + min_number;
	   }else{
	   	*x=c;
	   	*y=rand() % (max_number + 1 - min_number) + min_number;
	   }					   	
   }else{
	   if(rand()%2){
	   	*x=rand() % (max_number + 1 - min_number) + min_number;
	   	*y=-c;
	   }else{
	   	*x=rand() % (max_number + 1 - min_number) + min_number;
	   	*y=c;
	   }
   }
   
}
