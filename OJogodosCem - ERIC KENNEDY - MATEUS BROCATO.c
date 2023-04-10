#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>

typedef struct no
{
    int valor;
    struct no *proximo;

} No;

typedef struct
{
    No *topo;
    int tam; // definindo tamanho da pilha
    int tam_max; // definindo tamanho maximo da pilha
} Pilha;


void linhaCol(int lin, int col);
void box(int lin1, int col1, int lin2, int col2);
int menu(int lin1, int col1, int qtd, char lista[3][40]);
void textColor(int letras, int fundo);
  //COR DA LETRA
  enum{BLACK,                 //0
       BLUE,                  //1
       GREEN,                 //2
       CYAN,                  //3
       RED,                   //4
       MAGENTA,               //5
       BROWN,                 //6
       LIGHTGRAY,             //7
       DARKGRAY,              //8
       LIGHTBLUE,             //9
       LIGHTGREEN,            //10
       LIGHTCYAN,             //11
       LIGHTRED,              //12
       LIGHTMAGENTA,          //13
       YELLOW,                //14
       WHITE                  //15

       };
  //COR DO FUNDO
  enum{_BLACK=0,                 //0
       _BLUE=16,                  //1
       _GREEN=32,                 //2
       _CYAN=48,                  //3
       _RED=64,                   //4
       _MAGENTA=80,               //5
       _BROWN=96,                 //6
       _LIGHTGRAY=112,             //7
       _DARKGRAY=128,              //8
       _LIGHTBLUE=144,             //9
       _LIGHTGREEN=160,            //10
       _LIGHTCYAN=176,             //11
       _LIGHTRED=192,              //12
       _LIGHTMAGENTA=208,          //13
       _YELLOW=224,                //14
       _WHITE=240                  //15
       };


void textColor(int letra, int fundo){
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letra + fundo);
     }

void linhaCol(int lin, int col){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){col-1,lin-1});// coorddenada na tela

     //funcao para deixar o cursor invisivel
     HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_CURSOR_INFO info;
     info.dwSize = 100;
     info.bVisible = FALSE;
     SetConsoleCursorInfo(consoleHandle, &info);
}


void box(int lin1, int col1, int lin2, int col2){ // CRIA BOX
     int i,j , tamlin, tamcol;

     tamlin = lin2 - lin1;
     tamcol = col2 - col1;


     for (i=col1; i<=col2; i++){
         linhaCol(lin1,i);
         printf("%c",196);
         linhaCol(lin2,i);
         printf("%c",196);
         }

     for (i=lin1; i<=lin2; i++){
         linhaCol(i,col1);
         printf("%c",179);
         linhaCol(i,col2);
         printf("%c",179);
         }
     for (i=lin1+1;i<lin2;i++){
         for(j=col1+1;j<col2;j++){
            linhaCol(i,j);printf(" ");
         }
         }

     linhaCol(lin1,col1);
     printf("%c",218);
     linhaCol(lin1,col2);
     printf("%c",191);
     linhaCol(lin2,col1);
     printf("%c",192);
     linhaCol(lin2,col2);
     printf("%c",217);

}
int menu(int lin1, int col1, int qtd, char lista[3][40]){ // CRIA OPÇ
     int opc=1, lin2, col2, linha,i,tamMaxItem, tecla;

     tamMaxItem = strlen(lista[0]);
     for(i=1; i<qtd;i++){
       if(strlen(lista[i])>tamMaxItem){
          tamMaxItem = strlen(lista[i]);
       }
     }
     lin2 = lin1+(qtd*2+2);
     col2 = col1+tamMaxItem+4;


     textColor(WHITE, _BLUE);
     setlocale(LC_ALL,"C");
     box(lin1,col1,lin2,col2);
     setlocale(LC_ALL,"");

     while(1){

        linha=lin1+2;
        for(i=0;i<qtd;i++){
           if(i+1==opc)textColor(BLACK, _LIGHTGREEN);
           else textColor(WHITE, _BLUE);
        linhaCol(linha,col1+2);
        printf("%s",lista[i]);
        linha +=2;
        }

       linhaCol(1,1);
       tecla= getch();
       linhaCol(22,1);
       if(tecla==27){
       opc=0; break;
       }
       else if(tecla==13){
       break;
       }
       //Seta para cima
       else if(tecla==72){
            if(opc>1)opc--;

       }
       else if(tecla==80 ){
            if (opc<qtd)opc++;

       }
     }
     return opc;
}



void posicionar_mensagem(int linha, int coluna, char *mensagem, char *variavel) {
    // Definir a posição do cursor na tela usando ANSI escape codes
    printf("\x1b[%d;%dH", linha, coluna);
    // Imprimir a mensagem na posição especificada
    printf("%s", mensagem);

    // Verificar se a variável está presente e imprimi-la junto com a mensagem
    if (variavel != NULL) {
        printf("%s", variavel);
    }
}

     void posicionar_mensagem_pilha(int linha, int coluna, char* mensagem, Pilha* pilha) {
    // Definir a posição do cursor na tela usando ANSI escape codes
    printf("\x1b[%d;%dH", linha, coluna);

    // Obter o valor do nó da pilha apontado pelo ponteiro
    int valor = 0;
    if (pilha != NULL && pilha->topo != NULL) {
        valor = pilha->topo->valor;
    }

    // Criar uma string formatada com o valor do nó da pilha
    char messagePilha[100];
    sprintf(messagePilha, "%s %d", mensagem, valor);

    // Imprimir a mensagem na posição especificada
    printf("%s", messagePilha);
}

void empilhar(Pilha *p, int x)
{
    if (p->tam >= p->tam_max) // testa o tamanho da pilha para não passar o max estipulado para fase atual
    {
        posicionar_mensagem(8,35, "Pilha cheia! Nao eh possivel empilhar mais elementos.", NULL);
        posicionar_mensagem(9,35, "Pressione qualquer tecla para continuar..", NULL);
        getch();
        textColor(WHITE, _BLACK);
        system("cls");

        return;
    }
    No *no = malloc(sizeof(No));
    no->valor = x;
    no->proximo = p->topo;
    p->topo = no;
    p->tam++;
}

No* desempilhar(Pilha *p)
{
    No *no = NULL;
    if(p->topo)
    {
        no = p->topo;
        p->topo = no->proximo;
        p->tam--;
    }
    return no;
}

void imprimir(No *no)
{
    if(no)
    {
        printf("                                                        %d\n", no->valor);
        imprimir(no->proximo);
    }
}

int somar(Pilha *p)
{
    No *no = p->topo;
    int soma = 0;
    while(no)
    {
        soma += no->valor;
        no = no->proximo;
    }
    return soma;
}

void preencherAleatoriamente(Pilha *p, int tam_max)
{
    int i;
    for (i = 0; i < tam_max; i++)
    {
        int x = rand() % 100;
        empilhar(p, x);
    }
    p->tam_max = tam_max;
}

int contarAcertos(Pilha *p, int objetivo)
{
    int acertos = 0;
    No *no = p->topo;
    int soma = 0;
    while(no)
    {
        soma += no->valor;
        if(soma >= objetivo)
        {
            if(soma == objetivo)
            {
                acertos++;
            }
            soma = 0;
        }
        no = no->proximo;
    }
    return acertos;
}

void zerarPilha(Pilha *p)
{
    No *no = p->topo;
    while (no)
    {
        No *aux = no;
        no = no->proximo;
        free(aux);
    }
    p->tam = 0;
    p->topo = NULL;
}

void fimGoodGame()
{
    char trofeu[] = "                                                  .-=======-.\n"
                    "                                                 \\'-=======-'/\n"
                    "                                                 _|   .=.   |_\n"
                    "                                                ((|  {{1}}  |))\n"
                    "                                                 \\|   /|\\   |/\n"
                    "                                                  \\__ '`' __/\n"
                    "                                                   _`) (`_\n"
                    "                                                  /_________\\\n"
                    "                                                 /___________\\\n";

    char parabens[] = "           Parabens, voce se tornou um verdadeiro matematico, digno do titulo de MATEMATICO NORMAL!!!";


    textColor(YELLOW, _BLACK);
    printf("\n\n\n\n\n\n\n\n\n\n%s\n\n\n%s\n\n", trofeu, parabens);

}

void logo()
{
    textColor(LIGHTBLUE, _BLACK);

    char logo[] =     "               ###   ####   ###   ##   ####  ###    ##         ###    ##    ###         #     ##    ##                 \n"
                      "               #  #  #     #     #  #  #      #    #  #        #  #  #  #  #          ###    #  #  #  #                \n"
                      "               #  #  ###    ##   #  #  ###    #    #  #        #  #  #  #   ##          #    #  #  #  #                \n"
                      "               #  #  #        #  ####  #      #    #  #        #  #  #  #     #         #    #  #  #  #                \n"
                      "               ###   ####  ###   #  #  #     ###    ##         ###    ##   ###         ###    ##    ##                 \n";

    printf("%s", logo);
}

int main()
{
    int op, valor;
    int opc;

    No *no;
    Pilha p;
    p.tam = 0;
    p.tam_max = 3;
    p.topo = NULL;
    srand(time(NULL));

    preencherAleatoriamente(&p, p.tam_max);

    int soma = somar(&p);

    char lista[3][40]={"Iniciar o jogo", "Como jogar", "Sair"};

    setlocale(LC_ALL,"");
    do{
        inicio:
        printf("\n\n\n\n");
        logo();
       opc = menu(15,50,3,lista);

        linhaCol(1,1);
        textColor(WHITE, _BLACK);


    switch (opc) {
        case 1:
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("                                                  Iniciando jogo...\n");
            Sleep(3000);
            system("cls");
            int acertos=0;
            int max_time = 30;
            clock_t start_time = clock();
            int opc1;

            while(acertos < 2)
            {
                textColor(WHITE, _BLACK);
                system("cls");
                posicionar_mensagem(3, 50, "----->PILHA<-----\n", NULL);
                imprimir(p.topo);
                if(acertos == 0)
                {
                                    posicionar_mensagem(7, 50, "----->PILHA<-----", NULL);
                }
                else if(acertos == 1)
                {
                                    posicionar_mensagem(8, 50, "----->PILHA<-----", NULL);
                }

                char lista1[3][40]={"Empilhar", "Desempilhar", "Checar Resultado"};
                opc1 = menu(15,48,3,lista1);

                do
                {
                    // calcula o tempo decorrido em segundos
                    clock_t current_time = clock();
                    int remaining_time = (int) (max_time - ((current_time - start_time) / CLOCKS_PER_SEC));

                    char message[100];  // criar um buffer para a mensagem
                    sprintf(message, "Tempo restante: %d", remaining_time);  // formatar a mensagem com a variável

                    posicionar_mensagem(11, 45, message, NULL);  // imprimir a mensagem formatada

                            // verifica se o tempo limite foi excedido
                        while (remaining_time <= 0) {
                            textColor(WHITE, _BLACK);
                            system("cls");
                            posicionar_mensagem(13, 40, "O seu tempo esta esgotado. Voce perdeu!", NULL);
                            posicionar_mensagem(14, 40, "Aperte qualquer tecla para voltar ao Menu!", NULL);

                            getch();
                            textColor(WHITE, _BLACK);
                            system("cls");
                            goto inicio;
                        }
                    switch(opc1)
                    {
                    case 1:
                        posicionar_mensagem(13, 45, "Valor a ser empilhado: ", NULL);
                        scanf("%d", &valor);
                        empilhar(&p, valor);
                        textColor(WHITE, _BLACK);
                        break;


                    case 2:
                        no = desempilhar(&p);
                        if(no)
                        {
                            posicionar_mensagem_pilha(13, 45, "Valor desempilhado: ", &no);
                            getch();
                            textColor(WHITE, _BLACK);
                        system("cls");
                        }
                        break;

                    case 3:
                        if(somar(&p) == 100)
                        {
                        textColor(WHITE, _BLACK);
                        system("cls");
                            textColor(GREEN, _BLACK);
                            posicionar_mensagem(15,48, "PARABENS, VOCE VENCEU!", NULL);
                            acertos+=1;
                            if(acertos == 1)
                            {
                                posicionar_mensagem(17,28, "Pressione qualquer botao para continuar para a proxima fase...", NULL);
                                getch(); // aguarda o usuário pressionar qualquer tecla
                                system("cls"); // limpa a tela
                            }
                            else if(acertos == 2)
                            {
                                posicionar_mensagem(17,29, "Pressione qualquer botao para reinvidicar o seu premio...", NULL);
                                getch(); // aguarda o usuário pressionar qualquer tecla
                                system("cls"); // limpa a tela
                            }

                            if(acertos == 1)
                            {
                                p.tam_max = 4;
                                zerarPilha(&p);
                            }
                            else if(acertos == 2)
                            {
                                    system("cls");
                                    fimGoodGame();
                                    return 0;
                            }

                            preencherAleatoriamente(&p, p.tam_max);
                            soma = somar(&p);
                            max_time = 30;
                        }
                        else if(somar(&p) > 100 || somar(&p) < 100)
                        {
                            textColor(WHITE, _BLACK);
                            system("cls"); // limpa a tela
                            printf("\n\n\n\n\n\n\n\n\n\n\n");
                            printf("                                                 Sua soma deu: %d", somar(&p));
                            zerarPilha(&p);
                            textColor(RED, _BLACK);
                            posicionar_mensagem(16,36, "Infelizmente voce perdeu... Pra voce eh GAMEOVER!", NULL);
                            textColor(WHITE, _BLACK);
                            posicionar_mensagem(18, 34, "Tente alcancar 2 acertos para chegar ao grande premio!!", NULL);
                            preencherAleatoriamente(&p, p.tam_max);
                            posicionar_mensagem(20, 34, "Pressione qualquer tecla para voltar ao menu inicial...", NULL);
                            getch(); // aguarda o usuário pressionar qualquer tecla
                            textColor(WHITE, _BLACK);
                            system("cls"); // limpa a tela
                            goto inicio; // retorna para o início do loop while
                        }
                        break;

                    default:
                        printf("\nOpcao invalida.\n");
                        break;
                    }
                }
                while (max_time == 0);

            }

        case 2:
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n");
            printf("                                                    Como jogar:\n\n");
            printf("   O jogo Desafio dos 100 eh um jogo desenvolvido com o conceito de Pilha e seu objetivo eh atingir o resultado 100. \n");
            printf("    As pilhas serao geradas com numeros aleatorios e cabe ao jogador realizar as mudancas empilhando, desempilhando\n");
            printf("                e checando o resultado para fazer com que a Pilha atinja o numero 100.\n");
            printf("    Pode ser feita apenas UMA checagem de resultado, entao a faca apenas quando tiver certeza do resultado!\n");
            printf("            Mas CUIDADO: Voce possui um tempo limite de 30 segundos para completar as duas fases.\n");
            printf("                 O tempo atualizado sera mostrado ao jogador a cada acao feita pelo mesmo. \n\n");

            getch();
            system("cls");
            goto inicio;

        case 3:
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("                                                 Encerrando o jogo...");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            Sleep(1000);
            return 0;
    }

    }while(opc != 3);

    return 0;
}
