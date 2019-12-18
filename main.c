#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

typedef struct vertice
{
	int indice;
	char nome[100];
	float custo;
} TVertice;
int b = 0;
int total = 0;
int linha = 0;
int coluna = 0;

/**=============================== CONVERTE STRING PARA FLOAT ===========================================OK**/
float convertStringToFloat(char *token)
{
	char numF[10];
	int i, k = 0, tam, achou = 0;

	/**Procura virgula*/
	tam = strlen(token);
	while(i < tam)
	{

		if(token[i] == ',')
		{
			numF[k] = '.';
			achou = 1;
		}
		else numF[k] = token[i];
		k++;
		i++;
	}

	if(achou != 1) return atof(token);
	else return atof(numF);
}
void carregarDados(char * nome)
{
	FILE *fp;

	char string[1000];
	char *substring = (char*)malloc(5000 * sizeof(char));
	char cidades[1000];
	int i, j, v;

	if ((fp = fopen(nome, "r")) == NULL)
	{
		printf("\nO arquivo nao pode ser aberto.\n");
		exit(1);
	}
	i = -1;
	j = 0;
	v = 0;
	while (!feof(fp))
	{
		if(fgets(string, 2000, fp))
		{
			if(i == -1)
			{
				strcpy(cidades, string);

			}
			if(i > -1)
			{
				substring = strtok(string, ";\n");

				while(substring != NULL)
				{
					if (j == 0)
					{
						strcpy(cidades, substring);
						j++;
					}
					else
					{
						total++;
					}
					substring = strtok(NULL, ";\n");
				}
				substring = strtok(NULL, ";\n");
				j = 0;
			}
			i++;

		}
	}
	fclose(fp);
}
TVertice * inserirDados(TVertice vetorA[], char * nome)
{
	FILE *fp;

	char string[1000];
	char *substring = (char*)malloc(5000 * sizeof(char));
	char cidades[1000];
	float custo;
	int i, j, v, y, f;

	if ((fp = fopen(nome, "r")) == NULL)
	{
		printf("\nO arquivo nao pode ser aberto.\n");
		exit(1);
	}
	i = -1;
	j = 0;
	v = 0;
	y = 0;
	f = 0;



	int capacidade = 1;
	TVertice *vetorB = NULL;

	vetorB = (TVertice*) malloc(sizeof(TVertice) * capacidade);


	int numMatriz, tot = 0;;

	while (!feof(fp))
	{
		if(fgets(string, 2000, fp))
		{
			if(i == -1)
			{
				strcpy(cidades, string);

			}
			if(i > -1)
			{
				substring = strtok(string, ";\n");

				while(substring != NULL)
				{

					if (j == 0)
					{
						strcpy(cidades, substring);
						//strcpy(array[v].nome, substring);
						j++;
					}
					else
					{

						tot++;
						if(f < linha)
						{
							
							custo = convertStringToFloat(substring);
							v++;
							if(custo != 0.00)
							{
								//v++;
								if(y == 0)
								{
									
									if(vetorA[y].indice == -1)
									{
										vetorA[y].indice = b + 1;
									}
									//printf("%d\n", v);
									vetorB[b].indice = v;
									vetorB[b].custo = custo;
									b++;


									if(b >= capacidade)
									{
										capacidade += 1;
										vetorB = (TVertice*)realloc(vetorB, sizeof(TVertice) * capacidade);
									}
								}

								if( y > 0)
								{
								
									if(vetorA[y].indice == -1)
									{
										vetorA[y].indice = b + 1;
									}
									//printf("%d\n", v);
									vetorB[b].indice = v;
									vetorB[b].custo = custo;
									b++;

									if(b >= capacidade)
									{
										capacidade += 1;
										vetorB = (TVertice*)realloc(vetorB, sizeof(TVertice) * capacidade);
									}
								}
							}
						}
						
					}
					substring = strtok(NULL, ";\n");
				}
				v=0;
				j = 0;
				y++;
				substring = strtok(NULL, ";\n");
				
			}
			i++;
			numMatriz = pow(coluna, 2);
			if(tot == numMatriz)
			{
				vetorA[y].indice = b + 1;
			}
		}
	}
	return vetorB;
	fclose(fp);
}
TVertice * inicializarVetor(TVertice vetor[])
{
	int i;
	for(i = 0; i < linha; i++)
	{
		vetor[i].indice = -1;
	}
	return vetor;
}
void definirMatriz()
{
	linha = sqrt(total);
	coluna = linha;
}
/**=============================================== PRIM =============================================================**/

//Uma fun��o utilit�ria para imprimir o MST constru�do armazenado no pai []
int printMST(int parent[],int key[])
{
	int i;
	for (i = 1; i < linha; i++){
		printf("Edge: %d - %d    Weight: %d\n", parent[i], i,key[i]);
	}
	system("pause");
	return 0;
}

// Uma fun��o utilit�ria para encontrar o v�rtice com o valor m�nimo da chave, de
// o conjunto de v�rtices ainda n�o inclu�dos no MST
int minKey(int key[], bool mstSet[])
{
	// Inicializar valor m�nimo
	int min = 99999, min_index = 0;
    int v;
	for (v = 0; v < linha; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

float retornarValor(TVertice A[], TVertice B[],int indice1, int indice2)
{
	
	int l = 0, tot = 2, t = 1;
	int i,y;	
	for(y = 0; y < linha; y++)
	{

		if(l < b)
		{
			tot = A[y + 1].indice;
			tot -= 1;

			
			while(l < tot)
			{
				
				if(indice1 == y)
				{
					if(indice2 == B[l].indice)
					{
						return B[l].custo;
					}
				}		
			    
				//printf("Indice: %d - %d |  Custo: %.2f\n", y, B[l].indice, B[l].custo);

				t++;
				l++;
			}//percorre o vetorB de acordo com o vetorA[y+1] 
			t=1;
		}
		
	}
	return -1;
}
// Fun��o para construir e imprimir MST para um gr�fico representado usando adjac�ncia
// representa��o matricial
void primMST(TVertice A[], TVertice B[])
{
    int parent[linha]; // Matriz para armazenar o MST constru�do
    int key[linha]; // Valores-chave usados para selecionar a borda m�nima do peso no corte
    bool mstSet[linha]; // Para representar o conjunto de v�rtices ainda n�o inclu�dos no MST
 	int i;
    // Inicialize todas as chaves como INFINITE
    for (i = 1; i < linha+1; i++)
        key[i] = 999999, mstSet[i] = false;
 
    // Sempre inclua o primeiro 1� v�rtice no MST.
    key[0] = 0; // Fa�a a chave 0 para que este v�rtice seja escolhido como primeiro v�rtice
    parent[0] = -1; // O primeiro n� � sempre raiz do MST
 
    int count,v;
    float valor;
	// O MST ter� V v�rtices
    for (count = 0; count < linha; count++)
    {
        
		// Escolha o v�rtice da chave m�nima do conjunto de v�rtices
        // ainda n�o inclu�do no MST
        int u = minKey(key, mstSet);
 
        
		// Adicione o v�rtice selecionado ao conjunto MST
        mstSet[u] = true;
 
        // Atualiza o valor da chave e o �ndice pai dos v�rtices adjacentes de
        // o v�rtice escolhido. Considere apenas os v�rtices que ainda n�o est�o
        // inclu�do no MST
        for (v = 0; v <= linha; v++)
 
            // gr�fico [u] [v] � diferente de zero apenas para v�rtices adjacentes de m
            // mstSet [v] � falso para v�rtices ainda n�o inclu�dos no MST
            // Atualize a chave apenas se o gr�fico [u] [v] for menor que a chave [v]
            if(retornarValor(A,B,u,v) > -1)
            {
            	if (retornarValor(A,B,u,v) && mstSet[v-1] == false)
				{
					if(retornarValor(A,B,u,v) < key[v-1])
	            	{   
						parent[v-1] = u, key[v-1] = retornarValor(A,B,u,v);
					}
				}
			} 
			
    }
 
    
    // imprime o MST constru�do
    printMST(parent,key);
}



int main(int argc, char *argv[])
{
	
	char nome[100];
	printf("Informe o nome do arquivo:");
	gets(nome);

	carregarDados(nome);

	definirMatriz();

	TVertice vetorA[linha];

	inicializarVetor(vetorA);

	TVertice * vetorB = NULL;
	vetorB = inserirDados(vetorA,nome);

	primMST(vetorA, vetorB);


	return 0;

}

