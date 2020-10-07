/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "rede.h"
#include "random.h"

/* defines */

/* Define as Constantes com seus conteúdos*/
#define TAM 400
#define S 0
#define I 1
#define R 2
#define ITER 500
#define ITERM 20
#define E 2.718281828459045

enum { SIMPLE = 0, COMPLETE }; /* Para que esta sendo definida esta enumeração???*/

//#define _FILE_

int estado[TAM][TAM];
int temp[TAM][TAM];

FILE *fresult;

struct data
 {
   int ds[ITER], di[ITER], dr[ITER], dsi[ITER], dir[ITER], dis[ITER], drs[ITER];
	float da[ITER], db[ITER], dc[ITER], de[ITER], R0[ITER];
   float mds, mdi, mdr, mdsi, mdir, mdis, mdrs, mda, mdb, mdc, mde, mR0;
   int ti, maxi;
 } m;

int iPc;
int iPd;
int iPn;
int iK;
int iPerc;

void parseArgs( int qtde, char **args , float *PC, float *PD, float *PN, float *K, float *PERC_INI_I, int *iTAM, int *iSIM); 
 
int main(int argc, char *argv[]) /* arqc qtd de parâmetros passados em arqv*/
 {
   /*documentar as variáveis, para que será usada e seu respectivo conteúdo*/
   int i; /*Será utilizada como contador nos loops for*/
   int j; /*Será utilizado como contador nos loops for*/
   int k; /*Será utilizado como contador nos loops for*/
   int iTAM; // 
   int Pi; // probabilidade de infecção
   int iSec; // Parâmetro da rede conforme a REDE selecionada Ver documentação iGraph
   int iSIM;// Número da simulação 1 à 10
   int it; //Interação  100 para ca simulação
   int ds; // Quantidade de indivíduo sucetiveis da população
   int di; //Qtde de indivíduos infectados
   int dr; // Indivíduos recuperados
   int a; // Parâmetro da doença Ver artigo
   float K; /*Parâmetro da doença provavemente fixo em 1*/
   int dsi; // Qtde de indivíduos de S para I no SIR
   int dir; // Qtd indivíduos de I para R no SIR
   int dis;// qtd Indivíduos infectado que morre
   int drs; // qtd individuo recuperado que morre

   float pi; /*Probalilidade de infecção*/
   float m1; //Parâmetro auxiliar para tempo de acomodação
   float m2; // Parâmetro auxiliar para tempo de acomodação
   float p1; // Variável temporária para geração de número aleatório
   float p2; // Variaável temporária para geração de número aleatório
   float PC; // probabilidade de cura
   float PD; // probabilidade de morte pela doença
   float PN; // probabilidade de morte natural
   float PERC_INI_I; //qtde % de indivíduos infectados no início da simulação
   
   float prob;
   
   int vizI, x, y, tempi, tempj;

   char  fileepid[256];
   
   int C, r;
   
   C=5;
   r=4;
   
   /* discriminar o objetivo da atribuição de conteúdo*/
   PC=0.4; //Probalidade de cura
   PD=0.2; //probabilidade de morte
   PN=0.1; // probabilidade de morte natural
   PERC_INI_I = 0.005; //percentual de individuos infectados no início da simulação

   srand (time(NULL)); /*Numeração aleatória */
   init_genrand(rand());
   rede(r);

   iSIM=1;

	iK = 140;
   K=(float)iK/1000;
   

   // Obtem os argumentos passados na linha de commando
   parseArgs( argc, argv , &PC, &PD, &PN, &K, &PERC_INI_I, &iTAM, &iSIM);

   sprintf(fileepid, "..\\resultados\\SIRD_SIM_%02d_PC_%04d_PD_%04d_PN_%04d_K_%04d_PercIni_%04d.csv", iSIM, iPc, iPd, iPn, iK, iPerc);
   printf("\n %s \n", fileepid);

   for(i=0;i<TAM;i++)
   	for(j=0;j<TAM;j++)
      	estado[i][j]=S;

   //i - contador para garantir que 0.5% da população será infectado
   for(k=0;k<TAM*TAM*PERC_INI_I;)
    {
    	i=rand()%TAM;
      j=rand()%TAM;
      if(estado[i][j]==S)
       {
         estado[i][j]=I;
         k++;
       }
    }

   fresult = fopen(fileepid, "w");
   fprintf(fresult, "S;I;R;S->I;I->R;I->S;R->S;a;b;c;e;R0\n");

   for(it=0;it<ITER;it++)
    {
    	for(i=0;i<TAM;i++)
      	for(j=0;j<TAM;j++)
				temp[i][j] = estado[i][j];
    	
      printf("%d\n", it);
      ds=0; di=0; dr=0;
      dsi=0; dir=0; dis=0; drs=0;
      for(i=0;i<TAM;i++)
      	for(j=0;j<TAM;j++)
		       {
		       	vizI=0;
		         if(estado[i][j]==S)
		          {
		            ds++;
		            
		            for(a=0;a<C;a++){
		
							return_pos(&x, &y, r);
		
		               tempi = i+x;
		               tempj = j+y;
		               
		               if (i+x < 0)
		               tempi = TAM + (i+x);
		               
		               if (j+y < 0)
		               tempj = TAM + (j+y);
		               
		               if (i+x >= TAM)
		               tempi = i+x - TAM;
		               
		               if (j+y >= TAM)
		               tempj = j+y - TAM;
		               
		               if(estado[tempi][tempj]==I) vizI++;
		               
		               //printf("\n i = %d, j = %d, tempi = %d, tempj = %d, x = %d, y = %d, Nos = %d, vizI = %d", i, j, tempi, tempj, x, y, Nos, vizI);
		               //system("pause");
		            }
		            
		            pi=1-pow(E, -vizI*K);
		            p1=genrand_real1();
		            if(p1<pi)
		             {
		               temp[i][j] = I;
		               dsi++;
		             }
		            else
		             {
		               temp[i][j] = S;
		             }
		          }
		         else if(estado[i][j]==I)
		          {
		            di++;
		            p1=genrand_real1();
		            p2=genrand_real1();
		            temp[i][j]=I;
		            if(p1<PC)
		             {
		               temp[i][j]=R;
		               dir++;
		             }
		            else if(p2<PD)
		             {
		               temp[i][j]=S;
		               dis++;
		             }
		          }
		         else if(estado[i][j]==R)
		          {
		            dr++;
		            p1=genrand_real1();
		            if(p1<PN)
		             {
		               temp[i][j] = S;
		               drs++;
		             }
		            else
		             {
		               temp[i][j] = R;
		             }
		          }
		       }
      m.ds[it]=ds;
      m.di[it]=di;
      m.dr[it]=dr;
      m.dsi[it]=dsi;
      m.dir[it]=dir;
      m.dis[it]=dis;
      m.drs[it]=drs;
      
      if (((di) * (ds)) > 0)
      	m.da[it]=(float)dsi/((di) * (ds));
      else
      	m.da[it]= 0;
      	
      if (di > 0)
	  	m.db[it]=(float)dir/(float)di;
	  else
	    m.db[it]= 0;
	    
	  if (di > 0)
      	m.dc[it]=(1-m.db[it])*((float)dis/(float)di);
      else
        m.dc[it]= 0;
        
      if(drs > 0) 
		  m.de[it]=(float)drs/(float)dr;
      else 
		  m.de[it]=0;
		  
      if ((m.db[it] + m.dc[it]) > 0)
		  m.R0[it] = m.da[it]*TAM*TAM/(m.db[it] + m.dc[it]);
	  else
		  m.R0[it] = 0;
		  
      fprintf(fresult, "%d;%d;%d;%d;%d;%d;%d;%f;%f;%f;%f;%f\n", ds,di,dr,dsi,dir,dis,drs,
																					 m.da[it], m.db[it], m.dc[it], m.de[it], m.R0[it]);
      for(i=0;i<TAM;i++)
      	for(j=0;j<TAM;j++)
				estado[i][j] = temp[i][j];
    }
   m.mds=0;
   m.mdi=0;
   m.mdr=0;
   m.mdsi=0;
   m.mdir=0;
   m.mdis=0;
   m.mdrs=0;
   m.mda=0;
   m.mdb=0;
   m.mdc=0;
   m.mde=0;
   m.mR0=0;
   for(i=ITER-ITERM;i<ITER;i++)
    {
      m.mds=m.mds+(float)m.ds[i]/ITERM;
      m.mdi=m.mdi+(float)m.di[i]/ITERM;
      m.mdr=m.mdr+(float)m.dr[i]/ITERM;
      m.mdsi=m.mdsi+(float)m.dsi[i]/ITERM;
      m.mdir=m.mdir+(float)m.dir[i]/ITERM;
      m.mdis=m.mdis+(float)m.dis[i]/ITERM;
      m.mdrs=m.mdrs+(float)m.drs[i]/ITERM;
      
      m.mda=m.mda+(float)m.da[i]/ITERM;
      m.mdb=m.mdb+(float)m.db[i]/ITERM;
      m.mdc=m.mdc+(float)m.dc[i]/ITERM;
      m.mde=m.mde+(float)m.de[i]/ITERM;
      m.mR0=m.mR0+(float)m.R0[i]/ITERM;
      
    }
   fprintf(fresult, "Medias\n");
   fprintf(fresult, "%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f\n", m.mds,m.mdi,m.mdr,m.mdsi,m.mdir,m.mdis,m.mdrs,
																										  m.mda,m.mdb,m.mdc,m.mde,m.mR0);
   m.maxi=m.di[0];
   m.ti=0;
   for(i=1;i<ITER;i++)
    {
      if(m.di[i]>m.maxi)
       {
         m.maxi=m.di[i];
         m.ti=i;
       }
    }
   fprintf(fresult, "Pico I;%d\n", m.maxi);
   fprintf(fresult, "Inst Pico I;%d\n",m.ti);
   m2=0;
   for(i=15;i<ITER-15;i++)
    {
      m1=0;
      for(j=i-15;j<i+15;j++)
       {
         m1=m1+(float)m.di[j]/30;
       }
      if(m1*1.03 > m2 && m1*0.97 < m2) break;
      m2=m1;
    }
   fprintf(fresult, "Temp Acmd;%d\n", j);
   fclose(fresult);

   #ifdef _FILE_
      fclose(fresult);
   #endif /* _FILE_ */
   return 0;
 }
 
 //********************************************
 //* Metodo: PARSEARGS
 //*         Converte argumentos para valores
 //********************************************
void parseArgs(int qtde, char **args , float *PC, float *PD, float *PN, float *K, float *PERC_INI_I, int *iTAM, int *iSIM)
{
	int c;
	
	for( c = 0; c < qtde; c++ )
	{
		if( !(strcmp( *(args+c), "--PC" ) ) )
		{
			iPc = atoi(*(args + ++c));
			*PC = (float)iPc/1000;
			printf("PC: %f\n",*PC);
		} 
		else if( !(strcmp( *(args+c), "--PD" ) ) )
		{
			iPd = atoi(*(args + ++c));
			*PD = (float)iPd/1000;
			printf("PD: %f\n",*PD);			
		} 
		else if( !(strcmp( *(args+c), "--PN" ) ) )
		{
			iPn = atoi(*(args + ++c));
			*PN = (float)iPn/1000;
			printf("PN: %f\n",*PN);			
		}
		else if( !(strcmp( *(args+c), "--K" ) ) )
		{
			iK = atoi(*(args + ++c));
			*K = (float)iK;
			printf("K: %f\n",*K);			
		}
		else if( !(strcmp( *(args+c), "--PERC_INI_I" ) ) )
		{
			iPerc = atoi(*(args + ++c));
			*PERC_INI_I = (float)iPerc/1000;
			printf("PERC_INI_I: %f\n",*PERC_INI_I);			
		}
		else if( !(strcmp( *(args+c), "--REDE" ) ) )
		{
			*iTAM = atoi(*(args + ++c)); /*Pega o tamanho da rede*/
			printf("iTAM: %d\n", *iTAM);
       
		}
		else if( !(strcmp( *(args+c), "--SIM" ) ) )
		{
            *iSIM = atoi(*(args + ++c)); /*Pegar o número de simulações*/
			printf("iSIM: %d\n", *iSIM);
		}
	}
}


