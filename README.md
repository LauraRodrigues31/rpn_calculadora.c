##Laura de Araujo Rodrigues

# 🖩 Calculadora em Notação Polonesa Reversa (RPN)

## 📋 Descrição

Este projeto é uma calculadora que avalia expressões matemáticas na **Notação Polonesa Reversa (RPN)**, também chamada de _postfix notation_.

A notação RPN elimina a necessidade de parênteses e facilita a avaliação de expressões com o uso de uma pilha.

Exemplo de expressão RPN:

(3 + 4) × 5
→ RPN: 3 4 + 5 *

## 🎯 Objetivo da Implementação

- Ler uma expressão RPN digitada pelo usuário
- Avaliar a expressão utilizando um **TAD Pilha**
- Suportar as operações:
    - Adição (+)
    - Subtração (-)
    - Multiplicação (*)
    - Divisão (/)
- Verificar possíveis erros:
    - Divisão por zero
    - Expressão mal formada
    - Operadores em excesso
    - Tokens inválidos

## ⚙️ Como Executar o Projeto

### 1️⃣ Compilar o código

```bash
gcc rpn_calculadora.c -o rpn_calculadora
 ```
2️⃣ Executar
```
./rpn_calculadora
````

3️⃣ Digitar uma expressão RPN
Exemplo:
5 1 2 + 4 * + 3 -  
Saída esperada:
Resultado: 14.00
`````

✅ Exemplo de Uso:
3 4 +	7.00
5 1 2 + 4 * + 3
->	14.00
10 2 /	5.00
6 2 * 3 +	15.00




