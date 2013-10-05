/* Igor Domingues de Freitas - 1010310 */
/* Joao Pedro Portela Gomez Vaz - 1011141 */

#include <stdio.h>
#include <stdlib.h>

/**************************************************
* DECLARACOES								  
**************************************************/

typedef unsigned char *BigInt;
int numbytes = -1;

BigInt aux_copy (BigInt source);
BigInt aux_shr (BigInt a, int n);
BigInt aux_shl (BigInt a, int n);
static int aux_zero (BigInt a);
void bi_init (int nbits);
BigInt bi_new (int val);
void bi_destroy (BigInt a);
BigInt bi_sum (BigInt a, BigInt b);
BigInt bi_minus (BigInt a);
BigInt bi_sub (BigInt a, BigInt b);
BigInt bi_mul (BigInt a, BigInt b);
BigInt bi_shr (BigInt a, int n);
BigInt bi_shl (BigInt a, int n);

/***************************************************
* FUNCOES AUXILIARES								
***************************************************/

/****** Funcao: aux_copy (status: completo) ******/


BigInt aux_copy (BigInt source) 
{
	if (source == NULL)
	{
		printf("Erro.\n");
		return NULL;
	}
	
	int i;
	BigInt copy = bi_new(0);

	for (i=0; i<numbytes; i++)
	{
		copy[i] = source[i];
	}
	return copy;
}

/************ Fim da funcao: aux_copy ************/

/****** Funcao: aux_shr (status: completo) ******/

BigInt aux_shr (BigInt a, int n)
{
	if (a==NULL)
	{
		printf("Erro.\n");
		return NULL;
	}
	
	BigInt ret;
	unsigned short tempret = 0x0000;
	unsigned short tempa;
	unsigned short BitSig = 0x0000;
	int i=0;
	ret = aux_copy(a);
	while(i<16)
	{
		tempa = (unsigned short)a[i];

		if(i==16-1)
		{
			if(a[i]<=0x7F)
				BitSig = 0x0000;

			else
				BitSig = 0xFFFF;
		}

		else
		{
			BitSig = (unsigned short)a[i+1];
		}

		tempa = tempa >> n;
		BitSig = BitSig << (8-n);
		tempret = BitSig + tempa;
		ret[i] = (unsigned char)tempret;
		i++;
	}
	return ret;
}

/************ Fim da funcao: aux_shr ************/

/****** Funcao: aux_shl (status: completo) ******/

BigInt aux_shl (BigInt a, int n)
{
	if (a==NULL)
	{
		printf("Erro.\n");
		return NULL;
	}
		
	BigInt ret;
	unsigned short tempret = 0x0000;
	unsigned short tempa;
	unsigned short BitSig = 0x0000;
	int i=0;
	ret = aux_copy(a);
	while (i<16)
	{
		tempa = (unsigned short)a[i];
		tempa = tempa << n;
		tempret = BitSig + tempa;
		ret[i] = (unsigned char)tempret;
		BitSig = (tempret >> 8);
		i++;
	}
	return ret;
}

/************ Fim da funcao: aux_shl ************/

/****** Funcao: aux_zero (status: completo) ******/

static int aux_zero (BigInt a)
{
	if (a==NULL)
	{
		printf("Erro.\n");
		return -1;
	}
		
	int i;

	for (i = 0; i < numbytes ; i++) 
	{
		if (a[i] != 0x00)
		{
			return 1;
		}
	}	

	return 0;
}

/************ Fim da funcao: aux_zero ************/

/**************************************************
* FUNCOES PRINCIPAIS							   
**************************************************/

/****** Funcao: bi_init (status: completo) ******/

void bi_init (int nbits)
{
	if (numbytes == -1) 
	{
		if ((nbits <= 0 || nbits%8!=0) && nbits < 32)
			{
				printf("Valor invalido de bits (digite um valor maior ou igual a 32 e multiplo de 8).\n");
				return;
			}
		else
			numbytes = nbits/8;
		return;
	}
	
	else 
	{
		printf("Voce nao esta autorizado a mudar o numero de bits novamente.\n");
		return;
	}
	
}

/************ Fim da funcao: bi_init ************/

/****** Funcao: bi_new (status: completo) ******/

BigInt bi_new (int val)
{
	unsigned char v[4];
	BigInt a = (BigInt) malloc (numbytes);
	int i = 0;
	
	
	if (a==NULL)
	{
		printf("Erro.\n");
		return NULL;
	}
	
	while(i<4)
	{
		a[i] = 0x00;
		v[i] = val;
		val = val >> 8;
		i++;
	}
	
	if((v[1] == 0x00) && (v[2] == 0x00) && (v[3] == 0x00))
	{
		a[0] = v[0];
	}
	
	else if ((v[2] == 0x00) && (v[3] == 0x00))
	{
		a[0] = v[0];
		a[1] = v[1];
	}
	
	else if (v[3] == 0x00)
	{
		a[0] = v[0];
		a[2] = v[2];
		a[1] = v[1];
	}
	
	else
	{
		a[0] = v[0];
		a[3] = v[3];
		a[2] = v[2];
		a[1] = v[1];
	}
	
	while (i < numbytes)
	{
		a[i] = 0x00;
		i++;
	}
	return a;
}

/************ Fim da funcao: bi_new ************/

/****** Funcao: bi_destroy (status: completo) ******/

void bi_destroy (BigInt a)
{
	free(a);
}

/*********** Fim da funcao: bi_destroy ***********/

/****** Funcao: bi_sum (status: completo) ******/

BigInt bi_sum (BigInt a, BigInt b)
{
	
	if (a==NULL || b==NULL)
	{
		printf("Erro.\n");
		return NULL;
	}
		
	unsigned short tempret, tempa, tempb;
	unsigned short sobra = 0x0000;
	int i = 0;
	BigInt ret = bi_new(0);
	tempret = 0x0000;
	
	while(i<numbytes)
   	{	
	   tempa = (unsigned short) a[i];
	   tempb = (unsigned short) b[i];
	   tempret = tempa + tempb + sobra;
	   ret[i] = (unsigned char) tempret;
	   sobra = (tempret >> 8);
	   i++;
	}
	
	return ret;
}

/************* Fim da funcao: bi_sum *************/

/****** Funcao: bi_minus (status: completo) ******/

BigInt bi_minus (BigInt a)
{
	
	if (a==NULL)
	{
		printf("Erro.\n");
		return NULL;
	}
	
	int i = 0;
	BigInt minus, plus_one;
	plus_one = bi_new(1);
	minus = aux_copy(a);
	
	for(i = 0; i < numbytes; i++){
		minus[i] = ~a[i];
	}
	return bi_sum (minus, plus_one);
}

/************ Fim da funcao: bi_minus ************/

/****** Funcao: bi_sub (status: completo) ******/

BigInt bi_sub (BigInt a, BigInt b)
{
	if (a==NULL || b==NULL)
	{
		printf("Erro.\n");
		return NULL;
	}
		
	BigInt tempb = bi_minus (b);
	return bi_sum (a, tempb);
}

/************ Fim da funcao: bi_sub *************/

/****** Funcao: bi_mul (status: completo) ******/

BigInt bi_mul (BigInt a, BigInt b)
{
	if (a==NULL || b==NULL)
	{
		printf("Erro.\n");
		return NULL;
	}
	
	BigInt tempa = bi_new(0);
	BigInt tempb = bi_new(0);
	BigInt ret = bi_new(0);
	

	if (a[numbytes-1]>0x7F)
	{
		tempa = bi_minus(a);
	}
	else
	{
		tempa = aux_copy(a);
	}
	if (b[numbytes-1]>0x7F)
	{
		tempb = bi_minus(b);
	}
	else
	{
		tempb = aux_copy(b);
	}

	if (!(tempa[numbytes-1]>0x7F) && !(tempb[numbytes-1]>0x7F))
	{	
		while (aux_zero(tempb))
		{
			if (tempb[0] & 0x01)
			{
				ret = bi_sum(ret, tempa);
			}
			
			tempa = bi_shl(tempa,1);
			tempb = bi_shr(tempb,1);
		}
	
		if ( ((a[numbytes-1]>0x7F) && !(b[numbytes-1]>0x7F)) || (!(a[numbytes-1]>0x7F) && (b[numbytes-1]>0x7F)) )
		{
			ret = bi_minus(ret);
		}
	}
	else
	{
		ret[numbytes] = 0x80;
	}


	return ret;
}

/************ Fim da funcao: bi_mul *************/

/****** Funcao: bi_shr (status: completo) ******/

BigInt bi_shr (BigInt a, int n) 
{
	if (a==NULL)
	{
		printf("Erro.\n");
		return NULL;
	}
	
	BigInt tempa = aux_copy(a);

	while (n>8) 
	{
		tempa = aux_shr(tempa, 8);
		n = n-8;
	}
	a = aux_shr(tempa, n);

	return a;
}

/************ Fim da funcao: bi_shr *************/

/****** Funcao: bi_shl (status: completo) ******/

BigInt bi_shl (BigInt a, int n)
{
	if (a==NULL)
	{
		printf("Erro.\n");
		return NULL;
	}
	
	BigInt tempa = aux_copy(a);

	while (n>8) 
	{
		tempa = aux_shl(tempa, 8);
		n = n-8;
	}
	a = aux_shl(tempa, n);

	return a;
}

/************ Fim da funcao: bi_shl *************/

//FIM DA BIBLIOTECA
