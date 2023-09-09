#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main (){
	FILE *CONTAS;
	int escolha1;
	
	struct{
		char nome[100];
		int num;
		float saldo;
	}contas[100];
	
	for(int i=0;escolha1!=4;i++){
		
		printf("Deseja fazer o que : \n\n1)Adicionar nova conta \n2)Ler alguma conta\n3)Ordenar as contas \n4)Sair \n");	
		scanf("%d",&escolha1);
		
		if(escolha1==1){
			if(CONTAS==NULL){
				CONTAS=fopen("contas.txt","w"); 
			}else{
				CONTAS=fopen("contas.txt","a");
			}
			
			printf("Digite o Nome: ");
			scanf("%s",&contas[i].nome);
			
			printf("Digite o Numero(5 digitos): ");
			scanf("%d",&contas[i].num);
			
			printf("Digite o Saldo: ");
			scanf("%f",&contas[i].saldo);
			
			
			
			
		}if(escolha1==2){
			
			
		}if(escolha1==3){
			
			
		}if(escolha1==4){
			printf("Saindo...");
			break;
		}
		
		
		
		
		
	}
	system("pause");
	return 0;
}
