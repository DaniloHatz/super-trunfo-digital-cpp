
# Super Trunfo Digital - Sistema de Gerenciamento e Jogo Competitivo

Este projeto consiste na criação de um jogo digital inspirado no clássico **Super Trunfo**, acompanhado de um **Gerador de Cartas** para cadastrar e gerenciar o baralho utilizado durante as partidas. O sistema é dividido em dois programas distintos: **Gerador de Cartas** e **Jogo**, ambos implementados em C++.

## Descrição Técnica

### Gerador de Cartas
O Gerador de Cartas permite ao usuário cadastrar, importar, alterar, excluir e listar cartas de um baralho. As cartas são armazenadas em um arquivo binário e carregadas na memória sempre que o programa é iniciado. Ao finalizar o programa, todas as alterações são gravadas novamente no arquivo binário.

#### Principais Funcionalidades:
- **Cadastrar Cartas**: Inserir novas cartas no baralho com atributos como nome, idade, jogos, gols, títulos e salário.  
- **Importar Cartas**: Ler um arquivo texto contendo várias cartas e adicioná-las ao baralho existente.  
- **Alterar Cartas**: Atualizar os dados de qualquer carta já cadastrada.  
- **Excluir Cartas**: Remover uma carta específica do baralho.  
- **Listar Cartas**: Exibir todas as cartas armazenadas no baralho, mostrando todos os seus atributos.

### Jogo
O Jogo é uma adaptação simplificada de Super Trunfo, onde dois jogadores se enfrentam por quatro rodadas, escolhendo atributos das cartas para competir. O jogador com mais pontos ao final das quatro rodadas vence a partida.

#### Regras do Jogo:
- Cada jogador recebe 4 cartas aleatórias do baralho.  
- Os jogadores se alternam na escolha de um atributo para competir a cada rodada.  
- A vitória em uma rodada concede **2 pontos**, enquanto empates rendem **1 ponto**.  
- O jogador com maior pontuação após as 4 rodadas é declarado vencedor.

### Arquitetura do Projeto
O projeto é composto por dois programas independentes, organizados em projetos separados dentro da mesma solução do Visual Studio:
- **`gerador.cpp`**: Programa principal do Gerador de Cartas.  
- **`jogo.cpp`**: Programa principal do Jogo.  
- **`cartas.h / cartas.cpp`**: Contém as definições das estruturas de dados e funções compartilhadas pelos dois programas.  

## Funcionamento

### Gerador de Cartas:
1. O programa carrega todas as cartas existentes no arquivo binário.  
2. O usuário pode navegar pelo menu de opções para cadastrar, importar, alterar, excluir ou listar cartas.  
3. Ao sair, todas as alterações são gravadas no arquivo binário.

### Jogo:
1. O jogo lê as cartas do arquivo binário e seleciona 4 cartas aleatórias para cada jogador.  
2. Cada jogador escolhe um atributo por rodada, e o vencedor é determinado com base no maior valor do atributo selecionado.  
3. Ao final das 4 rodadas, o jogador com mais pontos vence.  

### Exemplo de Saída - Jogo:

```
Super Trunfo Futebol
--------------------
Iniciar nova partida? [S/N] S
Jogador 1: João
Jogador 2: José
---------------

[João]  
Carta: Neymar
1. Idade
2. Jogos
3. Gols
4. Títulos
5. Salário
Escolha atributo [3]

[João] Neymar | 240
[José] Kaká   | 194

Placar: João 2 x 0 José
```

## Tecnologias e Conceitos Aplicados

- **C++**: Linguagem utilizada para implementação.  
- **Vetores Estáticos e Dinâmicos**: Para gerenciamento de cartas e jogadores.  
- **Manipulação de Arquivos Binários**: Leitura e gravação do baralho em um arquivo binário compartilhado entre os dois programas.  
- **Programação Modular**: Organização dos programas em múltiplos arquivos para facilitar manutenção e escalabilidade.  

## Como Executar

### Gerador de Cartas:
1. Compile os arquivos `gerador.cpp`:
   ```g++ gerador.cpp cartas.cpp -o gerador```
2. Execute o programa:
   ```./gerador```

### Jogo:
1. Compile o arquivo `jogo.cpp`:
   ```g++ jogo.cpp cartas.cpp -o jogo```
2. Execute o programa:
   ```./jogo```
