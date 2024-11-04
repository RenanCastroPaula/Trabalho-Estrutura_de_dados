#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRUTAS 100

typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
} Fruta;

void cadastrarFruta(Fruta *frutas, int *total);
void listarFrutas(Fruta *frutas, int total);
void buscarFruta(Fruta *frutas, int total);
void alterarFruta(Fruta *frutas, int total);
void excluirFruta(Fruta *frutas, int *total);
void venderFruta(Fruta *frutas, int total);
int verificaCodigo(Fruta *frutas, int total, int codigo);
void registrarVenda(const char *nome, int quantidade, float preco);

int main() {
    Fruta frutas[MAX_FRUTAS];
    int totalFrutas = 0, opcao;
  
    do {
        printf("\nMenu:\n1. Cadastrar fruta\n2. Listar frutas\n3. Buscar fruta\n4. Alterar fruta\n5. Excluir fruta\n6. Vender fruta\n7. Sair\nEscolha uma opção: ");
        scanf("%d", &opcao);
      
        switch (opcao) {
            case 1: 
              cadastrarFruta(frutas, &totalFrutas); 
              break;
            case 2: 
              listarFrutas(frutas, totalFrutas); 
              break;
            case 3: 
              buscarFruta(frutas, totalFrutas); 
              break;
            case 4: 
              alterarFruta(frutas, totalFrutas); 
              break;
            case 5: 
              excluirFruta(frutas, &totalFrutas); 
              break;
            case 6: 
              venderFruta(frutas, totalFrutas); 
              break;
            case 7: 
              printf("Saindo do programa.\n"); 
              break;
            default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 7);
    return 0;
}

void cadastrarFruta(Fruta *frutas, int *total) {
    if (*total >= MAX_FRUTAS) { 
      printf("Limite de frutas cadastradas atingido.\n"); 
        return; 
    }
    Fruta novaFruta;
      printf("Digite o código da fruta: "); 
      scanf("%d", &novaFruta.codigo);
  
    if (verificaCodigo(frutas, *total, novaFruta.codigo)){   
      printf("Código de fruta já cadastrado! Tente outro.\n"); 
        return; 
    }
    
      printf("Digite o nome da fruta: "); 
      scanf(" %[^\n]", novaFruta.nome);
  
      printf("Digite o preço da fruta: "); 
      scanf("%f", &novaFruta.preco);
  
      printf("Digite a quantidade da fruta: "); 
      scanf("%d", &novaFruta.quantidade);
  
    frutas[*total] = novaFruta; (*total)++;
      printf("Fruta cadastrada com sucesso!\n");
}

void listarFrutas(Fruta *frutas, int total) {
    printf("\nFrutas cadastradas:\n");
    for (int i = 0; i < total; i++)
        printf("Código: %d - Nome: %s - Preço: R$ %.2f - Quantidade: %d\n", frutas[i].codigo, frutas[i].nome, frutas[i].preco, frutas[i].quantidade);
}

void buscarFruta(Fruta *frutas, int total) {
    int codigo; 
    printf("Digite o código da fruta que deseja buscar: "); 
    scanf("%d", &codigo);
    
    for (int i = 0; i < total; i++)
        if (frutas[i].codigo == codigo) {
            printf("Fruta encontrada: Código: %d - Nome: %s - Preço: R$ %.2f - Quantidade: %d\n", frutas[i].codigo, frutas[i].nome, frutas[i].preco, frutas[i].quantidade);
            return;
        }
    printf("Fruta não encontrada.\n");
}

void alterarFruta(Fruta *frutas, int total) {
    int codigo; 
    printf("Digite o código da fruta que deseja alterar: "); 
    scanf("%d", &codigo);
    
    for (int i = 0; i < total; i++)
        if (frutas[i].codigo == codigo) {
            printf("Digite o novo preço da fruta: "); 
            scanf("%f", &frutas[i].preco);
            printf("Digite a nova quantidade da fruta: "); 
            scanf("%d", &frutas[i].quantidade);
            printf("Fruta alterada com sucesso!\n");
            return;
        }
    printf("Fruta não encontrada.\n");
}

void excluirFruta(Fruta *frutas, int *total) {
    int codigo; 
    printf("Digite o código da fruta que deseja excluir: "); 
    scanf("%d", &codigo);
    
    for (int i = 0; i < *total; i++)
        if (frutas[i].codigo == codigo) {
            if (frutas[i].quantidade > 0) { 
                printf("Não é possível excluir a fruta enquanto houver estoque.\n"); return; 
            }
            
            for (int j = i; j < *total - 1; j++) frutas[j] = frutas[j + 1];
            (*total)--;
            printf("Fruta excluída com sucesso!\n");
            return;
        }
    printf("Fruta não encontrada.\n");
}

void venderFruta(Fruta *frutas, int total) {
    int codigo, quantidade; 
    printf("Digite o código da fruta que deseja vender: "); 
    scanf("%d", &codigo);
    printf("Digite a quantidade a ser vendida: "); 
    scanf("%d", &quantidade);
    
    for (int i = 0; i < total; i++)
        if (frutas[i].codigo == codigo) {
            if (frutas[i].quantidade >= quantidade) {
                frutas[i].quantidade -= quantidade;
                registrarVenda(frutas[i].nome, quantidade, frutas[i].preco);
                printf("Venda realizada: %d %s(s) vendidos.\n", quantidade, frutas[i].nome);
                return;
            } else {
                printf("Quantidade insuficiente para a venda.\n");
                return;
            }
        }
    printf("Fruta não encontrada.\n");
}

int verificaCodigo(Fruta *frutas, int total, int codigo) {
    for (int i = 0; i < total; i++)
        if (frutas[i].codigo == codigo) return 1;
    return 0;
}

void registrarVenda(const char *nome, int quantidade, float preco) {
    FILE *file = fopen("vendas.txt", "a");
    if (file) {
        fprintf(file, "Venda: %d %s(s) vendidos a R$ %.2f cada\n", quantidade, nome, preco);
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo de vendas.\n");
    }
}
