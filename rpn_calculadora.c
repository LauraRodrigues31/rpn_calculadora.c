
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX 100  // Tamanho máximo da pilha

typedef struct {
    double itens[MAX];  // Pilha para armazenar número
    int topo;           // Índice do topo da pilha
} Pilha;

//A pilha guarda números do tipo double
//A posição do topo indica onde está o último número inserido.

// Inicializa a pilha
void inicializaPilha(Pilha *p) {
    p->topo = -1;
}

// Verifica se a pilha está vazia
int estaVazia(Pilha *p) {
    return p->topo == -1;
}

// Empilha um valor
void push(Pilha *p, double valor) {
    if (p->topo < MAX - 1) {
        p->itens[++(p->topo)] = valor;
    } else {
        printf("Erro: pilha cheia.\n");
        exit(1);
    }
}

// Desempilha um valor
double pop(Pilha *p) {
    if (!estaVazia(p)) {
        return p->itens[(p->topo)--];
    } else {
        printf("Erro: pilha vazia.\n");
        exit(1);
    }
}
// Função para checar se um token é operador
int ehOperador(char *token) {
    return (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0);
}

int main() {
    Pilha p;
    inicializaPilha(&p);

    char expressao[256];
    printf("Digite a expressao em RPN:\n");
    fgets(expressao, sizeof(expressao), stdin);

    char *token = strtok(expressao, " \n");

    while (token != NULL) {
        if (ehOperador(token)) {
            if (p.topo < 1) {
                printf("Erro: operacao invalida (pilha com poucos operandos).\n");
                return 1;
            }

            double b = pop(&p);
            double a = pop(&p);
            double res;

            if (strcmp(token, "+") == 0) {
                res = a + b;
            } else if (strcmp(token, "-") == 0) {
                res = a - b;
            } else if (strcmp(token, "*") == 0) {
                res = a * b;
            } else if (strcmp(token, "/") == 0) {
                if (b == 0) {
                    printf("Erro: divisao por zero.\n");
                    return 1;
                }
                res = a / b;
            }

            push(&p, res);
        } else {
            // Teste se o token é número válido
            char *endptr;
            double valor = strtod(token, &endptr);
            if (*endptr != '\0') {
                printf("Erro: token invalido [%s]\n", token);
                return 1;
            }
            push(&p, valor);
        }

        token = strtok(NULL, " \n");
    }

    if (p.topo != 0) {
        printf("Erro: expressao incompleta ou operadores em excesso.\n");
        return 1;
    }

    double resultado = pop(&p);
    printf("Resultado: %.2f\n", resultado);

    return 0;
}
