# Carteira de Investimentos — CP2

Projeto em linguagem C para cadastrar e acompanhar uma carteira de investimentos. Os dados ficam salvos em `data/carteira.txt` e são carregados ao iniciar o programa.

## Integrantes do grupo

- Sergio Apolinario RGM:47722681
- Nickolas da Silva Coquejo Santiago RGM:74847620
- Daniel da Silva Mendes RGM:048737534
- Gustavo do Carmo Germano RGM:47880287
- Jhonatan Henrique da Cruz Carneiro RGM:37734075

## Funcionalidades

- Cadastrar ativo (nome, categoria, quantidade, preço de compra e preço atual).
- Listar os ativos cadastrados.
- Calcular o valor atual total da carteira.
- Calcular a rentabilidade geral em porcentagem.
- Salvar e recarregar os dados em arquivo texto.

## Estrutura

```text
meu-projeto-c/
├── src/
│   ├── main.c
│   ├── funcoes.c
│   └── modulo.c
├── include/
│   ├── funcoes.h
│   └── modulo.h
├── data/
│   └── carteira.txt
└── README.md
```

## Compilação

Execute o comando a partir da pasta `meu-projeto-c`:

```bash
gcc -Wall -Wextra -Iinclude src/main.c src/funcoes.c src/modulo.c -o programa
```

No Linux/macOS, execute com:

```bash
./programa
```

No Windows, caso use GCC/MinGW, execute com:

```text
programa.exe
```

**Importante:** execute o programa a partir da pasta raiz do projeto para que o caminho `data/carteira.txt` seja encontrado corretamente. O arquivo de exemplo já contém três ativos e pode ser editado antes da execução.

## Formato do arquivo de dados

Cada linha representa um ativo no formato:

```text
nome;categoria;quantidade;precoCompra;precoAtual
```

Use ponto e vírgula para separar os campos e ponto (`.`) como separador decimal. Não use ponto e vírgula dentro do nome ou da categoria.

## Fórmulas

- Valor atual de cada ativo = quantidade × preço atual.
- Valor total da carteira = soma do valor atual de todos os ativos.
- Rentabilidade geral (%) = ((valor atual total − valor investido total) / valor investido total) × 100.
