#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definições de tamanhos
#define INT_SIZE sizeof(int)
#define MAX_ENTRIES 50
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 50
#define AUX_SIZE (INT_SIZE * 4 + MAX_NAME_LENGTH)
#define ENTRY_SIZE (MAX_NAME_LENGTH + MAX_EMAIL_LENGTH + sizeof(int))
#define BUFFER_SIZE (MAX_ENTRIES * ENTRY_SIZE)

// Declaração da variável global e das funções
void *pBuffer = NULL;  // Variável global
void initializeBuffer();
void showMenu();
void addPerson();
void removePerson();
void findPerson();
void showAll();

int main() {
    initializeBuffer();
    showMenu();
    free(pBuffer);
    pBuffer = NULL;
    return 0;
}

// Função para inicializar o pBuffer de memória
void initializeBuffer() {
    // Alocação do pBuffer para armazenar as entradas da agenda e variáveis auxiliares
    pBuffer = malloc(AUX_SIZE + BUFFER_SIZE);
    if (!pBuffer) {
        printf("Falha ao alocar memória!\n");
        exit(0);
    }
}

// Função para exibir o menu e processar as escolhas do usuário
void showMenu() {
    int *choice = (int *)(pBuffer + sizeof(int) * 3);

    do {
        printf("\n********* MENU *********\n");
        printf("1 - Adicionar Pessoa\n");
        printf("2 - Remover Pessoa\n");
        printf("3 - Buscar Pessoa\n");
        printf("4 - Listar Todas\n");
        printf("5 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", choice);
        printf("\n");

        switch (*choice) {
            case 1:
                addPerson();
                break;
            case 2:
                removePerson();
                break;
            case 3:
                findPerson();
                break;
            case 4:
                showAll();
                break;
            case 5:
                printf("Saindo... Adeus! :)\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (*choice != 5);
}

// Função para adicionar uma pessoa à agenda
void addPerson() {
    int *totalPeople = (int *)pBuffer;
    char *name = (char *)(pBuffer + AUX_SIZE + (*totalPeople) * ENTRY_SIZE);
    int *age = (int *)(name + MAX_NAME_LENGTH);
    char *email = (char *)(age + 1);

    printf("Digite o nome: ");
    scanf("%s", name);
    printf("Digite a idade: ");
    scanf("%d", age);
    printf("Digite o email: ");
    scanf("%s", email);

    (*totalPeople)++;
}

// Função para remover uma pessoa da agenda
void removePerson() {
    int *totalPeople = (int *)pBuffer;
    if (*totalPeople == 0) {
        printf("\nNão há pessoas para remover.\n");
        return;
    }

    int *i = ( int * )( pBuffer + INT_SIZE );
    int *j = ( int * )( pBuffer + ( INT_SIZE * 2 ) );

    char *nameSearch = ( char * )pBuffer + ( INT_SIZE * 4 );
    printf("Nome da pessoa a remover: ");
    scanf("%s", nameSearch);

    for ( *i = 0; *i < *totalPeople; (*i)++) {
        char *currentPerson = (char *)(pBuffer + AUX_SIZE + (*i) * ENTRY_SIZE);
        if (strcmp(currentPerson, nameSearch) == 0) {
            // Move as pessoas restantes para preencher o espaço da pessoa removida
            for ( *j = *i; *j < *totalPeople - 1; (*j)++) {
                char *pessoa0 = (char *)(pBuffer + AUX_SIZE + (*j) * ENTRY_SIZE);
                char *pessoa1 = (char *)(pBuffer + AUX_SIZE + ((*j) + 1) * ENTRY_SIZE);
                strcpy(pessoa0, pessoa1);
                *(int *)(pessoa0 + MAX_NAME_LENGTH) = *(int *)(pessoa1 + MAX_NAME_LENGTH);
                strcpy(pessoa0 + MAX_NAME_LENGTH + sizeof(int), pessoa1 + MAX_NAME_LENGTH + sizeof(int));
            }
            (*totalPeople)--;
            printf("Pessoa removida com sucesso!\n");
            return;
        }
    }

    printf("Pessoa não encontrada.\n");
}

// Função para buscar uma pessoa na agenda
void findPerson() {
    int *totalPeople = (int *)pBuffer;
    char *nameSearch = ( char * )pBuffer + ( INT_SIZE * 4 );
    int *i = ( int * )( pBuffer + INT_SIZE );
    printf("Digite o nome da pessoa a buscar: ");
    scanf("%s", nameSearch);

    for ( *i = 0; *i < *totalPeople; (*i)++) {
        char *currentPerson = (char *)(pBuffer + AUX_SIZE + (*i) * ENTRY_SIZE);
        if (strcmp(currentPerson, nameSearch) == 0) {
            printf("\n***** Detalhes *****\n");
            printf("Nome: %s\n", currentPerson);
            printf("Idade: %d\n", *(int *)(currentPerson + MAX_NAME_LENGTH));
            printf("Email: %s\n", currentPerson + MAX_NAME_LENGTH + sizeof(int));
            printf("*********************\n");
            return;
        }
    }

    printf("\nPessoa não encontrada.\n");
}

// Função para listar todas as pessoas na agenda
void showAll() {
    int *totalPeople = (int *)pBuffer;
    if (*totalPeople == 0) {
        printf("Agenda vazia!\n");
        return;
    }
    int *i = ( int * )( pBuffer + INT_SIZE );
    for ( *i = 0; *i < *totalPeople; (*i)++) {
        char *currentPerson = (char *)(pBuffer + AUX_SIZE + (*i) * ENTRY_SIZE);
        printf("\n***** Pessoa %d *****\n", (*i) + 1);
        printf("Nome: %s\n", currentPerson);
        printf("Idade: %d\n", *(int *)(currentPerson + MAX_NAME_LENGTH));
        printf("Email: %s\n", currentPerson + MAX_NAME_LENGTH + sizeof(int));
        printf("*********************\n");
    }
}
