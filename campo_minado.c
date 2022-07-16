#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// definição de algumas variáveis globais necessárias para o programa, NÃO MEXER
int endgame = 0, reveladas = 0, init1, init2, modo = 2;
time_t start,end;
typedef struct{
    int status; // status de aberto/fechado
    int mina;   // status de é mina/não é
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
                }else if(campo[i][j].mina == 1){
                    printf("|_X");
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

    // se o campo não estiver revelado ainda o contador de casas reveladas aumenta, se não, nada acontece 
    if(campo[l][c].status==0){
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
    }else if(campo[l][c].numero==0){ //
        campo[l][c].status=1;
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

// função que inicia a partida
void initJogo(campo campo[lt][ct]){
    int input1, input2, i, j, cont = 1, menu;

    // imprime um campo falso apenas para parecer que o jogo começou, mas aguarda
    // as primeiras coordenadas para gerar o campo e realmente começar
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
    scanf("%d %d", &init1, &init2);
    while(valid(init1, init2)==0){
        if(valid(input1, input2)==0){
            printf("Coordenada invalida!\n");
        }
        scanf("%d %d", &init1, &init2);
    }
    init1--;
    init2--;
    
    // com as primeiras coordenadas válidas, o campo é gerado, o tempo começa a contar e
    // as primeiras casas são reveladas. (também ocorre um wincheck pois em alguns casos
    // bem específicos o jogo pode ser ganho nesse primeiro clique)
    initCampo(campo);
    start = time(NULL);
    revelar(init1, init2, campo);
    wincheck(campo);


    while(endgame==0){

        // enquanto o jogo não acabar, o campo é impresso e o usuário escolhe se quer inserir uma
        // coordenada, consultar o tempo ou pedir uma sugestão a cada loop
        printar(campo);
        printf("Digite:\n1 coordenadas\n2 tempo de jogo\n3 sugestão\n");
        scanf("%d", &menu);
        
        if(menu == 1){
            printf("Insira as coordenadas: ");
            scanf("%d %d", &input1, &input2);
            input1--;
            input2--;
            if(valid(input1, input2)==0){
                printf("Coordenada invalida!\n");
            }else{
                revelar(input1, input2, campo);
                wincheck(campo);
            }
        }
        else if (menu == 2) {
            end = time(NULL);
            printf("Tempo de jogo: %ld segundos\n", end - start);
        }
        else if (menu == 3){
            //MODO DE SUGESTAO
        }
    }
}

int main(){
    campo campo[lt][ct];

    initJogo(campo);

    end = time(NULL);
    printf("Tempo de jogo: %ld segundos", end - start);
    return 0;
}