#include "PIG.h"

PIG_Evento event;          //evento ser tratadoi a cada pssada do loop principal
PIG_Teclado myKeyboard;     //variável como mapeamento do teclado
double posX = 100, posY = 100;
double speed = 0.01;

void updateObject();

int main( int argc, char* args[] ){


    //criando o jogo (aplicação)
    CriaJogo("Meu Jogo");

    //associando o teclado (basta uma única vez) com a variável meuTeclado
    myKeyboard = GetTeclado();

    //loop principal do jogo
    while(JogoRodando()){

        //pega um evento que tenha ocorrido desde a última passada do loop
        event = GetEvento();

        //aqui o evento deve ser tratado e as coisas devem ser atualizadas

        //será feita aprepação do frame que será exibido na tela
        IniciaDesenho();

        
        updateObject();

        DesenhaRetangulo(40, 40, 100, 100, {255, 0, 0, 50});
        //o frame totalmente pronto será mostrado na tela
        EncerraDesenho();

        if(myKeyboard[TECLA_ESC]) {
            break;
        }
    }

    //o jogo será encerrado
    FinalizaJogo();

    return 0;
}

void updateObject() {
    if(myKeyboard[TECLA_a]) {
        posX -= speed;
    }
    if(myKeyboard[TECLA_d]) {
        posX += speed;
    }
    if(myKeyboard[TECLA_w]) {
        posY += speed;
    }
    if(myKeyboard[TECLA_s]) {
        posY -= speed;
    }

    DesenhaRetangulo(posX, posY, 100, 100, VERDE);
}

