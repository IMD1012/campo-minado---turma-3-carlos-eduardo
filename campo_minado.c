#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// definição de algumas variáveis globais necessárias para o programa, NÃO MEXER
int endgame = 0, reveladas = 0, init1, init2, modo = 1, automode = 0, rodada = 1;
time_t start,end;
typedef struct{
    int status; // status de aberto(1)/fechado(0)
    int mina;   // status de é mina(1)/não é(0)
    int numero; // número correspondente a quantia de minas ao redor da casa
}campo;

// mude os números abaixos para alterar no programa inteiro
int lt = 10, ct = 20, minas = 40;
// lt = linhas totais, ct = colunas totais

// função que checa se um índice chamado está dentro do campo
int valid(int l, int c){
    if(l>=0 && l<lt && c>=0 && c<ct){
        return 1;
    }else{
        return 0;
    }
}

// função que conta e retorna quantas bombas há nas 8 casas ao redor de um determinado índice
int quantbombas(int l, int c, campo campo[lt][ct]){
    int n=0;
    
    if(valid(l-1, c-1) && campo[l-1][c-1].mina==1){
        n++;
    }
    if(valid(l-1, c) && campo[l-1][c].mina==1){
        n++;
    }
    if(valid(l-1, c+1) && campo[l-1][c+1].mina==1){
        n++;
    }
    if(valid(l, c-1) && campo[l][c-1].mina==1){
        n++;
    }
    if(valid(l, c+1) && campo[l][c+1].mina==1){
        n++;
    }
    if(valid(l+1, c-1) && campo[l+1][c-1].mina==1){
        n++;
    }
    if(valid(l+1, c) && campo[l+1][c].mina==1){
        n++;
    }
    if(valid(l+1, c+1) && campo[l+1][c+1].mina==1){
        n++;
    }
   return n;
}

// função que conta quantas casas ocultas existem ao redor de um determinado índice
int quantOcult(int l, int c, campo campo[lt][ct]){
    int n=0;
    
    if(valid(l-1, c-1) && campo[l-1][c-1].status==0){
        n++;
    }
    if(valid(l-1, c) && campo[l-1][c].status==0){
        n++;
    }
    if(valid(l-1, c+1) && campo[l-1][c+1].status==0){
        n++;
    }
    if(valid(l, c-1) && campo[l][c-1].status==0){
        n++;
    }
    if(valid(l, c+1) && campo[l][c+1].status==0){
        n++;
    }
    if(valid(l+1, c-1) && campo[l+1][c-1].status==0){
        n++;
    }
    if(valid(l+1, c) && campo[l+1][c].status==0){
        n++;
    }
    if(valid(l+1, c+1) && campo[l+1][c+1].status==0){
        n++;
    }
   return n;
}

// função que inicia o campo
void initCampo(campo campo[lt][ct]){
    int i, j, lrand, crand;

    // primeiro inicia todos os índices do struct do campo como 0 para ter a base
    for(i=0;i<lt;i++){
        for(j=0;j<ct;j++){
            campo[i][j].status = 0;
            campo[i][j].mina = 0;
            campo[i][j].numero = 0;
        }
    }
    i = 0;

    // depois distribui as X bombas
    srand(time(NULL));
    while(i!=minas){
        lrand = rand()%lt;
        crand = rand()%ct;
        if(campo[lrand][crand].mina == 0){
            campo[lrand][crand].mina = 1;
            i++;
            if(modo==1){
                if((lrand == init1 && crand == init2) || quantbombas(init1, init2, campo)!=0){
                    campo[lrand][crand].mina = 0;
                    i--;
                }
            }else if(modo==2){
                if((lrand == init1 && crand == init2) || i==minas && quantbombas(init1, init2, campo)==0){
                    campo[lrand][crand].mina = 0;
                    i--;
                }
            }
        }
    }

    // e por último transforma as casas que não viraram bombas em números correspondentes a quantidade de bombas vizinhas
    for(i=0;i<lt;i++){
        for(j=0;j<ct;j++){
            campo[i][j].numero = quantbombas(i, j, campo);
        }
    }
}

// função para printar o campo gerado
void printar(campo campo[lt][ct]){
    int i, j, cont = 1;

    //imprime o número de colunas
    printf("\n   ");
    for(i=0;i<ct;i++){
        if(i<10 && i==ct-1){
            printf(" %d\n", i+1);
        }else if(i==ct-1){
            printf("%d\n", i+1);
        }else if(i+1>=10){
            printf("%d ", i+1);
        }else{
            printf(" %d ", i+1);
        }
    }

    // imprime o número de linhas
    for(i=0;i<lt;i++){
        if(cont<10){
            printf(" %d", cont);
        }else{
            printf("%d", cont);
        }
        cont++;

        // e o campo em si (ao acertar uma mina todas as minas são expostas)
        if(endgame==0){
            for(j=0;j<ct;j++){
                if(campo[i][j].status == 0){
                    printf("|__");
                }else{
                    printf("|_%d", campo[i][j].numero);
                }
            }
        }else{
            for(j=0;j<ct;j++){
                if(campo[i][j].mina == 1){
                    printf("|_X");
                }else if(campo[i][j].status == 0){
                    printf("|__");
                }else{
                    printf("|_%d", campo[i][j].numero);
                }
            }
        }
        printf("\n");
    }
}

// função que checa se a condição de vitória foi alcançada
void wincheck(campo campo[lt][ct]){
    if(reveladas==(lt*ct)-minas){
        endgame = 1;
        printar(campo);
        printf("Vitoria! Todas as minas foram evitadas.\n");
    }
}

// função que recebe o input de linha/coluna e altera o campo
int revelar(int l, int c, campo campo[lt][ct]){

    // se o campo não estiver revelado ainda e a casa do indicada não for uma bomba, o contador de casas reveladas aumenta, se não, nada acontece 
    if(campo[l][c].status==0 && campo[l][c].mina!=1){
        reveladas++;
    }else if(campo[l][c].status==1){
        printf("Coordenada ja revelada.\n");
    }

    if(campo[l][c].numero!=0 && campo[l][c].mina==0){ // se o índice for um número, somente ele é revelado
        campo[l][c].status=1;
        return 0;
    }else if(campo[l][c].mina==1){ // se o índice for uma mina, ela é revelada e o jogo acaba
        campo[l][c].status=1;
        endgame = 1;
        printar(campo);
        printf("GAME OVER! Voce acertou uma mina.\n");
        return 0;
    }else if(campo[l][c].numero==0){ // se o índice for vazio (0), ele é revelado e a função é aplicada em todas as 
        campo[l][c].status=1;        // 8 casas vizinhas de forma recursiva

        if(valid(l-1, c-1) && campo[l-1][c-1].status==0){
            revelar(l-1, c-1, campo);
        }
        if(valid(l-1, c) && campo[l-1][c].status==0){
            revelar(l-1, c, campo);
        }
        if(valid(l-1, c+1) && campo[l-1][c+1].status==0){
            revelar(l-1, c+1, campo);
        }
        if(valid(l, c-1) && campo[l][c-1].status==0){
            revelar(l, c-1, campo);
        }
        if(valid(l, c+1) && campo[l][c+1].status==0){
            revelar(l, c+1, campo);
        }
        if(valid(l+1, c-1) && campo[l+1][c-1].status==0){
            revelar(l+1, c-1, campo);
        }
        if(valid(l+1, c) && campo[l+1][c].status==0){
            revelar(l+1, c, campo);
        }
        if(valid(l+1, c+1) && campo[l+1][c+1].status==0){
            revelar(l+1, c+1, campo);
        }
    }
    return 0;
}

// função que faz alguns cálculos e sugere uma casa com baixas chances de ser uma mina quando solicitada
void sugerir_casa(campo campo[lt][ct]){
    int sugl, sugc, temp, templ, tempc;
    float chance, chanceN = 100;
    
    // descobre qual a casa com a menor relação minas/casas ocultas
    for(int i=0;i<lt;i++){
        for(int j=0;j<ct;j++){
            temp = 100.00/quantOcult(i, j, campo);
            chance = temp*campo[i][j].numero;
            if(campo[i][j].status == 1 && campo[i][j].numero>0 && quantOcult(i, j, campo)>campo[i][j].numero && chance<chanceN){
                chanceN = chance;
                sugl = i;
                sugc = j;
            }
        }
    }
    printf("\n%.1f %% de chance de mina ao redor da casa %dx%d.\n", chanceN, sugl+1, sugc+1);

    templ = sugl;
    tempc = sugc;
    // escolhe aleatoriamente uma casa oculta ao redor da casa escolhida para revelar
    while(valid(sugl, sugc)==0 || campo[sugl][sugc].status==1){
        sugl = templ;
        sugc = tempc;
        int lrand = rand()%3+1;
        int crand = rand()%3+1;

        if(lrand==1){
            sugl--;
        }else if(lrand==3){
            sugl++;
        }

        if(crand==1){
         sugc--;
        }else if(crand==3){
         sugc++;
        }
    }

    // imprime qual casa o jogo escolheu como sugestão
    if(automode==0){
        printf("tente na casa %dx%d!\n", sugl+1, sugc+1);
    }else if(automode==1){ // OU se o jogo estiver no modo automático, o sistema declara qual casa vai tentar
        printf("tentando na casa %dx%d!\n", sugl+1, sugc+1);
        revelar(sugl, sugc, campo);
        wincheck(campo);
    }
}

// função que inicia a partida
void initJogo(campo campo[lt][ct]){
    int input1, input2, i, j, cont = 1, menu, rodada = 1;
    reveladas = 0;

    // imprime um campo falso apenas para parecer que o jogo começou, mas aguarda
    // o primeiro par de coordenadas para gerar o campo e realmente começar
    printf("   ");
    for(i=0;i<ct;i++){
        if(i<10 && i==ct-1){
            printf(" %d\n", i+1);
        }else if(i==ct-1){
            printf("%d\n", i+1);
        }else if(i+1>=10){
            printf("%d ", i+1);
        }else{
            printf(" %d ", i+1);
        }
    }
    for(i=0;i<lt;i++){
        if(cont<10){
            printf(" %d", cont);
        }else{
            printf("%d", cont);
        }
        cont++;
        
            for(j=0;j<ct;j++){
                    printf("|__");
            }
        printf("\n");
    }
  
    // pequeno loop para garantir que a primeira coordenada é válida
    if(automode==0){
        printf("Insira as coordenadas: ");
        scanf("%d %d", &init1, &init2);
        init1--;
        init2--;
        while(valid(init1, init2)==0 ||(lt==3 && ct==3 && init1==1 && init2==1 && modo==1)){
            if(valid(init1, init2)==0){
                printf("Coordenada invalida! Tente outra.\n");
            }else if(lt==3 && ct==3 && init1==1 && init2==1 && modo==1){ // a casa 2x2 não pode ser revelada de primeira em um jogo de campo 3x3 com modo "iniciar sempre com casa vazia", pois isso quebra o jogo
                printf("Coordenada invalida para o campo 3x3 modo \"Iniciar sempre com casa vazia\". Tente outra.\n");
            }
            scanf("%d %d", &init1, &init2);
            init1--;
            init2--;
        }
    }else{ // ou caso o automode esteja ligado, um par de coordenadas aleatórias é gerado para iniciar o jogo
        int lrand = rand()%lt;
        int crand = rand()%ct;

        // esse loop aqui previne a mesma situação da casa 2x2 num campo 3x3 ali de cima
        while(lt==3 && ct==3 && lrand==1 && crand==1 && modo==1){
            lrand = rand()%lt;
            crand = rand()%ct;
        }

        init1 = lrand;
        init2 = crand;
        printf("Comecando com %dx%d.\n", init1+1, init2+1);
    }

    // com as primeiras coordenadas válidas, o campo é gerado, o tempo começa a contar e
    // as primeiras casas são reveladas (também ocorre um wincheck pois em alguns casos
    // bem específicos o jogo pode ser ganho nesse primeiro clique)
    endgame = 0;
    initCampo(campo);
    start = time(NULL);
    revelar(init1, init2, campo);
    wincheck(campo);


    while(endgame==0){

        // enquanto o jogo não acabar, o campo é impresso e o usuário escolhe se quer inserir uma
        // coordenada, consultar o tempo ou pedir uma sugestão a cada loop
        if(automode==0){
            printar(campo);
            printf("Digite:\n1: Coordenadas\n2: Tempo de jogo/Rodada\n3: Sugestao\n");
            scanf("%d", &menu);
        }else{ // mas se o automode estiver ligado, o input sempre será a sugestão
            printar(campo);
            menu = 3;
            rodada++;
        }

        if(menu == 1){ // inserir coordenadas
            printf("Insira as coordenadas: ");
            scanf("%d %d", &input1, &input2);
            input1--;
            input2--;
            if(valid(input1, input2)==0){
                printf("Coordenada invalida!\n");
            }else{
                rodada++;
                revelar(input1, input2, campo);
                wincheck(campo);
            }
        }
        else if (menu == 2) { // consultar o tempo
            end = time(NULL);
            printf("\nTempo de jogo: %ld segundos\n", end - start);
            printf("Rodadas: %d\n", rodada);
        }
        else if (menu == 3){ // pedir sugestão ao jogo
            sugerir_casa(campo);
        }
    }

  end = time(NULL);
  printf("Tempo de jogo: %ld segundos\n", end - start);
  printf("Rodadas: %d\n", rodada);
}

// função que roda o menu e inicia o jogo/muda as configurações
int main(){
  int menu = 0, escolha = 0, input;
    campo campo[lt][ct];

    // enquanto o jogador não sair do programa, ele fica no loop do menu inicial
    while(menu==0){
      printf("\n(C)ampo Minado\n\n1: Iniciar Jogo\n2: Configuracoes\n3: Sair\n");
      scanf("%d", &menu);

      // loop de controle para garantir um comando válido
      while(menu!=1 && menu!=2 && menu!=3){
        printf("\nOpcao invalida. Tente novamente.\n");
        scanf("%d", &menu);
      }

      // opção do menu 1: inicia o jogo com as configurações atuais e pergunta se quer iniciar novamente ao acabar
      while(menu==1){
        initJogo(campo);
        printf("Iniciar novamente?\n1: Sim 2: Nao\n");
        scanf("%d", &escolha);

        // loop de controle para garantir um comando válido
        while(escolha!=1 && escolha!=2){
          printf("\nOpcao invalida. Tente novamente.\n");
          scanf("%d", &escolha);
        }
        
        // se não, volta ao menu
        if(escolha==2){
          menu = 0;
          escolha = 0;
        }
      }

      // opção do menu 2: acessa as configurações
      while(menu==2){
        
        // imprime as configurações atuais
        printf("\nConfiguracoes atuais:\nCampo %dx%d com %d minas\n", lt, ct, minas);
        if(modo==1){
            printf("Modo: Sempre iniciar com casa vazia\n");
        }else{
            printf("Modo: Sempre iniciar com numero\n");
        }
        if(automode==0){
            printf("Modo automatico: OFF\n");
        }else{
            printf("Modo automatico: ON\n");
        }

        // opções de mudança de configurações
        printf("1: Mudar tamanho do campo\n2: Mudar numero de minas\n3: Mudar modo\n4: Ligar/desligar automode\n5: Voltar\n");
        scanf("%d", &escolha);

        // loop de controle para garantir um comando válido
        while(escolha!= 1 && escolha!= 2 && escolha!= 3 && escolha!= 4 && escolha!= 5){
            printf("\nOpcao invalida. Tente novamente.\n");
            scanf("%d", &escolha);
        }
        
        if(escolha==1){ // 1: muda o tamanho do campo
            int input1, input2;
            printf("Escolha o novo tamanho do campo:\n");
            scanf("%d %d", &input1, &input2);

            // tratamento para que o tamanho do campo seja válido
            if(input1<2 || input2<2 || input1*input2>200){
                printf("\nTamanho de campo invalido. O campo tem que ser ao menos 2x2 e com no maximo 200 casas.\n");
            }else if(input1*input2<minas){
                printf("\nTamanho de campo invalido. O numero total de casas e menor que o numero de minas.\n");
            }else if(input1*input2<5 && modo==1){
                printf("\nTamanho de campo invalido. O campo nao pode ter menos que 9 casas se o modo de jogo for \"Sempre iniciar com casa vazia\". \n");
            }else{
                lt = input1;
                ct = input2;
            }
        }else if(escolha==2){ // 2: muda o número de minas
            printf("Escolha o novo numero de minas:\n");
            scanf("%d", &input);

            // tratamento para que o número de minas seja válido
            if(input<lt*ct){
                minas = input;
            }else{
                printf("\nNumero de minas invalido! Cheque o tamanho do campo.\n");
            }
        }else if(escolha==3){ // 3: alterna o modo de jogo entre 1(começar com 0) e 2(começar com número)
          if(modo==1){
            modo = 2;
          }else if(modo==2 && lt*ct<5){
            printf("\nNao e possivel trocar de modo pois o campo nao tem o tamanho minimo (9 casas).\n");
          }else if(modo==2){
            modo = 1;
          }
        }else if(escolha==4){ // 4: alterna o modo autómatico entre ligado e desligado
          if(automode==0){
            automode = 1;
          }else if(automode==1){
            automode = 0;
          }
        }else if(escolha==5){ // 5: volta pro menu inicial
          menu = 0;
        }
      }
        
    }
    // opção do menu 3: o loop do menu se encerra e o jogo fecha
    return 0;
}