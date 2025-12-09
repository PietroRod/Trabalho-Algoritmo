#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define AZUL "\033[1;32m"
#define RESET "\033[0m"

typedef struct {
    int id;
    char nome [50];
    int estoque;
    float preco;
} produto;

void carregamento(){
    for(int i = 0; i <= 100; i++){
        printf("%s\rCarregando: %d%%%s", AZUL, i, RESET);
        fflush(stdout);
        Sleep(10);
    }
    printf("\n");
}

void expandirVetor(produto **pacote, int *limite){
    *limite = *limite + 1;
    produto *teste = realloc(*pacote, *limite * sizeof(produto));
    
    if (teste != NULL) {
        *pacote = teste;
    } else {
        printf("\n[Erro] Memoria insuficiente para criar nova vaga!\n");
        exit(1);
    }
}

int cadastro (produto **pacote, int qntProdutos, int *limite){
    int continuar;

    for(qntProdutos; qntProdutos < *limite; qntProdutos++){
            printf("---------- CADASTRO DE PRODUTOS %d ----------\n", qntProdutos+1);

            setbuf(stdin, NULL);
            printf("Digite o nome do produto: ");
            fgets((*pacote)[qntProdutos].nome, 50, stdin);
            
            char *resultado = strstr((*pacote)[qntProdutos].nome, "\n");
            if(resultado != NULL){
                *resultado = '\0';
            }

            setbuf(stdin, NULL);
            printf("Digite o ID do produto: ");
            scanf("%d", &(*pacote)[qntProdutos].id);

            setbuf(stdin, NULL);
            printf("Digite o preco do produto: ");
            scanf("%f", &(*pacote)[qntProdutos].preco);

            printf("Digite a quantidade em estoque do produto: ");
            scanf("%d", &(*pacote)[qntProdutos].estoque);

            carregamento();

            printf("\nCadastro finalizado!");
            
            printf("\n\nVoce deseja cadastrar outro produto ou sair ?");
            printf("\n(1) Cadastrar outro produto");
            printf("\n(2) Retornar ao menu principal");
            printf("\nDigite sua opcao: ");
            scanf("%d", &continuar);

            if(continuar == 1){
                expandirVetor(pacote, limite); 
            } else {
                return qntProdutos + 1;
            }
        }
    return qntProdutos + 1;
}

int main (){
    setbuf(stdin, NULL);
    produto *pacote; 
    int limite = 1; 

    pacote = (produto *) malloc(limite * sizeof(produto));
    
    int qntProdutos = 0;
    int opcao;

    char usuario[20];
    char senha[20];

    printf("---------- SISTEMA DE LOGIN ----------\n");
    printf("Digite o nome de usuario: ");
    fgets(usuario, 20, stdin);
    usuario[strcspn(usuario, "\n")] = '\0';

    printf("Digite a senha: ");
    fgets(senha, 20, stdin);
    senha[strcspn(senha, "\n")] = '\0';

    if(strcmp(usuario, "admin") == 0 && strcmp(senha, "1234") == 0){
    carregamento();
    printf("Login bem-sucedido!\n");
    } else {
    printf("Usuario ou senha incorretos. Saindo do sistema.\n");
    free(pacote);
    return 1;
}

do{
        printf("%s\n---------- SISTEMA DE PRODUTOS ----------\n", AZUL);
        printf("Vagas totais no sistema: %d\n\n", limite);
        printf("(1) Registrar Produtos\n");
        printf("(2) Listar Produtos\n");
        printf("(3) Relatorio de valor total\n");
        printf("(4) Sair\n");
        printf("Opcao: %s ", RESET);
        scanf("%d", &opcao);

        switch (opcao){
        case 1:
            if(qntProdutos < limite){
                qntProdutos = cadastro(&pacote, qntProdutos, &limite);
            } else {
                 printf("\nVoce ja preencheu toda a lista de produtos.\n");
                 printf("Deseja adicionar um novo produto? (1-Sim / 2-Nao): ");
                 int resp;
                 scanf("%d", &resp);
                 if(resp == 1){
                     expandirVetor(&pacote, &limite);
                     qntProdutos = cadastro(&pacote, qntProdutos, &limite);
                 }
            }
            break;
            
        case 2:
        carregamento();
            printf("\n---------- Lista de produtos cadastrados ----------");
            for(int k=0; k < qntProdutos; k++){
                printf("\nNome do produto: %s", pacote[k].nome);
                printf("\nID do produto: %d", pacote[k].id);
                printf("\nPreco do produto: %.2f", pacote[k].preco);
                printf("\nEstoque do produto: %d", pacote[k].estoque);
                printf("\n-------------------------------------------------");
            }
            break;

        case 3:
                carregamento();
                float valorTotalGeral = 0;
                float subtotal = 0;

                printf("\n---------- Relatorio de valor total ----------\n");
            
                for(int k = 0; k < qntProdutos; k++){
                subtotal = pacote[k].preco * pacote[k].estoque;
                
                valorTotalGeral += subtotal;

                printf("Produto: %s | Qtd: %d | Total: R$ %.2f\n", pacote[k].nome, pacote[k].estoque, subtotal);
            }

            printf("-------------------------------------------------\n");
            printf("O VALOR TOTAL DO ESTOQUE E: R$ %.2f\n", valorTotalGeral); 
            printf("-------------------------------------------------\n");
            
            break;

        case 4:
            printf("Saindo...\n");
            free(pacote); 
            break;

        default:
            printf("Opcao invalida\n");
        }

    }while (opcao != 4);
    
    return 0;
}