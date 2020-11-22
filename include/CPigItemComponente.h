/**************************************************
A classe CPigItemComponente descreve o código dos items que compõem certos componentes como checkbox, radiobox, listbox e dropdown.
Todos esses componentes se caracterizam por possuir diversos itens e por se poder marcar/selecionar um ou mais desses itens.
Os elementos principais da classe CPigItemComponente são: o texto do item (label, obrigatório), a imagem de fundo (textura básica do componente, opcional) e um ícone (imagem extra, opcional).
Além disso, os objetos da classe possuem um ponteiro para função que permite que o frame do ícone seja alterado externamente.
O ícone pode ser alterado para representar a marcação ou não do item dentro de um cehckbox ou radiobox.
O label é posicionado sempre internamente, mas pode estar alinhado à direita (com ou sem a presença do ícone), à esquerda (com ou sem a presença do ícone) ou centralizado (com ou sem a presença do ícone).
**************************************************/

#ifndef _CPIGItemComponente_
#define _CPIGItemComponente_
#include "CPIGIcone.h"

class CPigItemComponente:public CPigComponente{

private:

    void (*AjustaFrame)(CPigItemComponente*);       //ponteiro para função que será chamada sempre que algum estado do item mudar
    PIGIcone icone;
    PIG_PosicaoComponente posIcone,posRelativaLabel;

    int OnMouseClick(){
        SetAcionado(!GetAcionado());
        if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
        return PIG_SELECIONADO_TRATADO;
    }

    void IniciaBase(std::string labelItem,std::string arqImagemIcone="",int alturaIcone=0,int larguraIcone=0){
        if (arqImagemIcone!=""){
            icone = new CPIGIcone(arqImagemIcone,1,idJanela);
            icone->SetDimensoes(alturaIcone,larguraIcone);
            AlinhaIconeEsquerda();
            posIcone = PIG_COMPONENTE_ESQ_CENTRO;
        }else icone = NULL;
        SetLabel(labelItem);
        posRelativaLabel = PIG_COMPONENTE_CENTRO_CENTRO;
        SetPosicaoPadraoLabel(PIG_COMPONENTE_CENTRO_CENTRO);
        AjustaFrame = NULL;
    }

public:

    //item com icone e com fundo
    CPigItemComponente(int idComponente,int px, int py, int alturaIcone,int larguraIcone,std::string arqImagemIcone, std::string arqImagemFundo,std::string labelItem,int larguraLista,int alturaItemLista,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,alturaItemLista,larguraLista,arqImagemFundo,retiraFundo,janela){
        IniciaBase(labelItem,arqImagemIcone,alturaIcone,larguraIcone);//,larguraLista,alturaItemLista);
    }

    //item com icone e sem fundo
    CPigItemComponente(int idComponente,int px, int py, int alturaIcone,int larguraIcone,std::string arqImagemIcone,std::string labelItem,int larguraLista,int alturaItemLista,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,alturaItemLista,larguraLista,janela){
        IniciaBase(labelItem,arqImagemIcone,alturaIcone,larguraIcone);//,larguraLista,alturaItemLista);
    }

    //item sem icone e com fundo
    CPigItemComponente(int idComponente,int px, int py, std::string arqImagemFundo,std::string labelItem,int larguraLista,int alturaItemLista,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,alturaItemLista,larguraLista,arqImagemFundo,retiraFundo,janela){
        IniciaBase(labelItem,"",0,0);//,larguraLista,alturaItemLista);
    }

    //item sem icone e sem fundo
    CPigItemComponente(int idComponente,int px, int py,std::string labelItem,int larguraLista,int alturaItemLista,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,alturaItemLista,larguraLista,janela){
        IniciaBase(labelItem,"",0,0);//,larguraLista,alturaItemLista);
    }

    ~CPigItemComponente(){
        if (icone)
            delete icone;
    }

    bool GetAcionado(){
        return acionado;
    }

    void SetAcionado(bool valor){
        acionado = valor;
        if (AjustaFrame) AjustaFrame(this);
    }

    void SetHabilitado(bool valor){
        habilitado = valor;
        if (AjustaFrame) AjustaFrame(this);
    }

    void SetFoco(bool valor){
        temFoco = valor;
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
        if (AjustaFrame) AjustaFrame(this);
    }

    void DefineFuncaoAjusteFrame(void (*funcao)(CPigItemComponente*)){
        AjustaFrame = funcao;
        if (AjustaFrame) AjustaFrame(this);
    }

    int Desenha()override{
        SDL_RenderCopyEx(renderer,text,&frame,&dest,-angulo,NULL,flip);
        if (icone)
            icone->Desenha();
        DesenhaLabel();
        EscreveHint();
    }

    void AlinhaLabelDireita(){
        posRelativaLabel = PIG_COMPONENTE_DIR_CENTRO;
        int largLabel = lab->GetLargura();//CGerenciadorFontes::GetLarguraPixels(label,fonteLabel);
        if (icone){
            int largIcone,altIcone;
            icone->GetDimensoes(altIcone,largIcone);
            if (posIcone==PIG_COMPONENTE_ESQ_CENTRO){
                SetPosicaoPersonalizadaLabel(larg-largLabel,0);
            }else SetPosicaoPersonalizadaLabel(larg-largLabel-largIcone,0);
        }else{
            SetPosicaoPersonalizadaLabel(larg-largLabel,0);
        }
    }

    void AlinhaLabelEsquerda(){
        posRelativaLabel = PIG_COMPONENTE_ESQ_CENTRO;
        if (icone){
            if (posIcone==PIG_COMPONENTE_ESQ_CENTRO){
                int largIcone,altIcone;
                icone->GetDimensoes(altIcone,largIcone);
                SetPosicaoPersonalizadaLabel(largIcone,0);
            }else SetPosicaoPersonalizadaLabel(0,0);
        }else{
            SetPosicaoPersonalizadaLabel(0,0);
        }
    }

    void AlinhaLabelCentro(){
        posRelativaLabel = PIG_COMPONENTE_CENTRO_CENTRO;
        int largLabel = lab->GetLargura();//CGerenciadorFontes::GetLarguraPixels(label,fonteLabel);
        if (icone){
            int largIcone,altIcone;
            icone->GetDimensoes(altIcone,largIcone);
            if (posIcone==PIG_COMPONENTE_ESQ_CENTRO){
                SetPosicaoPersonalizadaLabel(largIcone+(larg-largIcone)/2-largLabel/2,0);
            }else SetPosicaoPersonalizadaLabel((larg-largIcone)/2-largLabel/2,0);
        }else{
            SetPosicaoPersonalizadaLabel(larg/2-largLabel/2,0);
        }
    }

    void AlinhaIconeDireita(){
        if (icone){
            int altIcone,largIcone;
            icone->GetDimensoes(altIcone,largIcone);
            posIcone=PIG_COMPONENTE_DIR_CENTRO;
            icone->Move(x+larg-largIcone,y);
            if (posRelativaLabel == PIG_COMPONENTE_ESQ_CENTRO){
                AlinhaLabelEsquerda();
            }else if (posRelativaLabel == PIG_COMPONENTE_CENTRO_CENTRO){
                AlinhaLabelCentro();
            }else if (posRelativaLabel == PIG_COMPONENTE_DIR_CENTRO){
                AlinhaLabelDireita();
            }
        }
    }

    void AlinhaIconeEsquerda(){
        if (icone){
            posIcone=PIG_COMPONENTE_ESQ_CENTRO;
            icone->Move(x,y);
            if (posRelativaLabel == PIG_COMPONENTE_ESQ_CENTRO){
                AlinhaLabelEsquerda();
            }else if (posRelativaLabel == PIG_COMPONENTE_CENTRO_CENTRO){
                AlinhaLabelCentro();
            }else if (posRelativaLabel == PIG_COMPONENTE_DIR_CENTRO){
                AlinhaLabelDireita();
            }
        }
    }

    //define a posição do label (dentre posições pré-estabelecidas)
    int SetPosicaoPadraoLabel(PIG_PosicaoComponente pos)override{
        posLabel = pos;
        if (posRelativaLabel == PIG_COMPONENTE_ESQ_CENTRO){
            AlinhaLabelEsquerda();
        }else if (posRelativaLabel == PIG_COMPONENTE_CENTRO_CENTRO){
            AlinhaLabelCentro();
        }else if (posRelativaLabel == PIG_COMPONENTE_DIR_CENTRO){
            AlinhaLabelDireita();
        }
        return 0;
    }

    int TrataEventoMouse(PIG_Evento evento)override{
        ChecaMouseOver(CMouse::PegaXY());

        if(mouseOver){
            if (habilitado==false) return PIG_SELECIONADO_DESABILITADO;
            if (visivel==false) return PIG_SELECIONADO_INVISIVEL;
            if (evento.mouse.acao==MOUSE_PRESSIONADO && evento.mouse.botao == MOUSE_ESQUERDO) return OnMouseClick();
            return PIG_SELECIONADO_MOUSEOVER;
        }

        return PIG_NAO_SELECIONADO;
    }

    int TrataEventoTeclado(PIG_Evento evento){
        return 0;
    }

    void Move(int nx, int ny)override{
        int dx = nx-x;
        int dy = ny-y;
        CPigComponente::Desloca(dx,dy);
        if (icone) icone->Desloca(dx,dy);
    }

    PIGIcone GetIcone(){
        return icone;
    }

};

typedef CPigItemComponente *PigItemComponente;
#endif //_CPIGtemComponente_
