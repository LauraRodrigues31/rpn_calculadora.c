#include <stdio.h>    // Para printf, fgets
#include <stdlib.h>   // Para exit, strtod
#include <string.h>   // Para strtok, strcmp
#include <ctype.h>    // Para isdigit (se fosse necessário)

// Define o tamanho máximo da pilha
#define MAX 100

// Estrutura de dados da pilha (TAD Pilha)
typedef struct {
    double itens[MAX];  // Vetor para armazenar os números da pilha (double)
    int topo;           // Índice do topo da pilha (inicialmente -1)
} Pilha;

/* Função: inicializaPilha
 * Inicializa a pilha, definindo topo como -1 (indicando que está vazia)
 */
void inicializaPilha(Pilha *p) {
    p->topo = -1;
}

/* Função: estaVazia
 * Retorna 1 se a pilha estiver vazia (topo == -1), ou 0 se não estiver vazia
 */
int estaVazia(Pilha *p) {
    return p->topo == -1;
}

/* Função: push
 * Insere (empilha) um número no topo da pilha
 */
void push(Pilha *p, double valor) {
    if (p->topo < MAX - 1) {
        p->itens[++(p->topo)] = valor;
    } else {
        printf("Erro: pilha cheia.\n");
        exit(1);  // Encerra o programa com erro
    }
}

/* Função: pop
 * Remove (desempilha) e retorna o número no topo da pilha
 */
double pop(Pilha *p) {
    if (!estaVazia(p)) {
        return p->itens[(p->topo)--];
    } else {
        printf("Erro: pilha vazia.\n");
        exit(1);  // Encerra o programa com erro
    }
}

/* Função: ehOperador
 * Verifica se o token atual é um dos operadores suportados: + - * /
 * Retorna 1 se for operador, ou 0 se não for
 */
int ehOperador(char *token) {
    return (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0);
}

/* Programa principal (main)
 * Executa a calculadora RPN
 */
int main() {
    Pilha p;
    inicializaPilha(&p);  // Inicializa a pilha

    char expressao[256];  // Buffer para armazenar a expressão digitada pelo usuário

    // Solicita ao usuário para digitar a expressão RPN
    printf("Digite a expressao em RPN:\n");
    fgets(expressao, sizeof(expressao), stdin);  // Lê a linha de entrada

    // Tokeniza a expressão usando delimitadores de espaço e nova linha
    char *token = strtok(expressao, " \n");

    // Processa cada token da expressão
    while (token != NULL) {
        if (ehOperador(token)) {
            // Se for operador, precisamos de pelo menos 2 números na pilha
            if (p.topo < 1) {
                printf("Erro: operacao invalida (pilha com poucos operandos).\n");
                return 1;
            }

            // Desempilha os dois operandos
            double b = pop(&p);
            double a = pop(&p);
            double res;

            // Aplica a operação correspondente
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

            // Empilha o resultado da operação
            push(&p, res);

        } else {
            // Se não for operador, assume que é um número
            // Converte o token para double
            char *endptr;
            double valor = strtod(token, &endptr);

            // Verifica se a conversão foi bem sucedida
            if (*endptr != '\0') {
                printf("Erro: token invalido [%s]\n", token);
                return 1;
            }

            // Empilha o número convertido
            push(&p, valor);
        }

        // Pega o próximo token
        token = strtok(NULL, " \n");
    }

    // No final, a pilha deve conter exatamente um valor (o resultado final)
    if (p.topo != 0) {
        printf("Erro: expressao incompleta ou operadores em excesso.\n");
        return 1;
    }

    // Exibe o resultado
    double resultado = pop(&p);
    printf("Resultado: %.2f\n", resultado);

    return 0;
}

/* Exemplo de execução:

| Ação               | Pilha   |
| ------------------ | ------- |
| push(5)            | 5       |
| push(1)            | 5 1     |
| push(2)            | 5 1 2   |
| + → pop(2,1) → 3   | 5 3     |
| push(4)            | 5 3 4   |
| * → pop(4,3) → 12  | 5 12    |
| + → pop(12,5) → 17 | 17      |
| push(3)            | 17 3    |
| - → pop(3,17) → 14 | 14      |

Resultado: 14.00
*/
