# twisted-reality

Twisted Reality é um desafiador jogo de quebra-cabeça projetado para estimular a mente do jogador. O objetivo central é habilmente posicionar todas as peças no tabuleiro principal, levando em consideração os pinos coloridos. As peças devem encaixar nos pinos correspondentes às suas cores; caso não haja pinos para todas as peças, isso indica que elas podem ser acomodadas em qualquer local. Utilize o tabuleiro auxiliar para organizar as peças que ainda não foram colocadas, adicionando uma camada estratégica ao desafio.

Este jogo foi inspirado em dois outros títulos: IQ Twist, do qual herdou a ideia central do quebra-cabeça, e Resident Evil, incorporando o conceito de gerenciamento de itens no inventário. Em uma versão futura, planeja-se introduzir uma atmosfera de terror e uma narrativa envolvente. Os quebra-cabeças serão fundamentais para desvendar um mistério intrigante, acrescentando uma dimensão narrativa e emocional à experiência de jogo.

## Playtest - v0.1.1

### Funcionalidades para testar:

* Movimentação do cursor (W,A,S,D)
* Pegar uma peça (ESPAÇO)
* Posicionar uma peça nos tabuleiros (ESPAÇO)
* Movimentar uma peça pelos tabuleiros (W,A,S,D)
* Transição entre tabuleiros - Board (tabuleiro principal) e Stash (tabuleiro auxiliar)
* Rotacionar a peça (Q,E)
* Inverter a peça (F)
* Cancelar movimento (ESC)
* Colisões:
    * Com a parede (a peça não deve sair dos tabuleiros)
    * Peça com Peça (não deve ser possível posicionar uma peça em cima de outra)
    * Peça com Pino (Blocos sem furo no objeto da peça não podem ser posicionados em cima de pinos)
* Fim de jogo (checar se a solução foi correta e o jogo finalizou)

## To-Do list

### SOUND

- [x] SFX
- [x] SOUNDTRACK

### USER INTERFACE (UI)

- [ ] Main Menu
- [ ] GUI*
- [ ] Gameplay Submenu*
- [ ] Scene change*
- [ ] Preview of piece wireframe

### ART
- [x] Add pieces sprites v1
- [x] Add block sprites v1
- [x] Add pegs sprites v1
- [x] Add pieces sprites v2
- [x] Add block sprites v2
- [x] Add pegs sprites v2
- [ ] Add piece 3D animation*
- [ ] Add level background

### GAMEPLAY

#### Pieces

- [x] Move function
- [x] Rotate function
- [x] Flip function
- [x] Place function
- [x] Multiple Collisors
- [x] Add Pegs
- [x] Collisions:
    - [x] piece x piece
    - [x] piece x peg

#### Blocks

- [x] Create Table of blocks
- [x] Create Cursor
- [x] Move Cursor
- [x] Grab function
- [x] Collisions:
    - [x] block x piece
- [x] Manage animation:
    - [x] Enabled block
    - [x] Disabled block
- [x] Add Collision Walls
- [x] Resolve Wall Collisions:
    - [x] piece  x wall
    - [x] cursor x wall
- [x] Resolve stash-to-board/board-to-stash

#### Tables

- [x] Create board table
- [x] Create stash table
- [x] Set Table position on screen

#### Debug

- [x] Add collider polygon

#### Game

- [x] Add level parser
- [x] Add IsLevelComplete function
- [x] Handle user input
