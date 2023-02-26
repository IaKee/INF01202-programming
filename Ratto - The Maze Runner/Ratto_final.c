//Programa: Mouse trap - Ratto - Trabalho final de algoritmos e programacao
//Nomes: Giordano Souza e Matheus Almansa
//Cartoes UFRGS: 00308054 e

/*BIBLIOTECAS E ARQUIVOS UTEIS UTILIZADOS*/
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

/*DEFINICOES DE CONSTANTES*/
#define N_FASES 3
#define RESOLUCAO_Y 400
#define RESOLUCAO_X 700
#define AREAJOGO_Y 330
#define AREAJOGO_X 621
#define espacamento_x_spryte_criatura 23
#define espacamento_y_spryte_criatura 30
#define espacamento_x_spryte_prop 22
#define espacamento_y_spryte_prop 21

/*ESTRUTURAS UTILIZADAS*/
typedef struct obj
{
    int wx, wy, x, y, w, h;
} CRIATURA_draw;
typedef struct location
{
    int posicao_x;
    int posicao_y;
    int inicial_x;
    int inicial_y;
} POSICAO;
typedef struct entity
{
    POSICAO CRIATURA_pos;
    int direcao;
    int vida;
    int velocidade;
    int forma; //(0 - se normal | 1- se cachorro)
    int stamina; //O quanto a criatura pode correr antes de se cansar;
    int stamina_regen; //Regeneracao de stamina
    int dano; //O dano que essa criatura causa
    int n_mortes;
} CRIATURA;
typedef struct level
{
    int n_fase;
    int score_queijo;
    int n_queijos;
    int score_ossos;
    int score_gatos;
    int score_tempo;
    float tempo_limite;
    float tempo_corrente;

    CRIATURA Rato;

    CRIATURA Gato_Askel;
    CRIATURA Gato_Charlie;
    CRIATURA Gato_Susan;
    CRIATURA Gato_Pyro;
} NIVEL;
typedef struct imenu
{
    bool menu_abriu; //Determina se o menu ja foi aberto, para nao sobrescrever o ja aberto
    int seleciona_opcao; //Opcao que foi selecionada no menu do jogo
} OPCOES;
typedef struct data
{
    int cod_erro; //Variavel que armazena o codigo de erro, para o retorno dessa funcao
    int vidas_iniciais;
    bool portas_alteradas;
    bool atualizou_cachorro;
    bool desatualizou_cachorro;
    volatile bool alterna_spryte;
    int ultima_impressao_tempo;
    int tempo_virou_cachorro;
    bool moveu_Askel;
    bool moveu_Charlie;
    bool moveu_Susan;
    bool moveu_Pyro;
    int posicao_rato_matriz_mapa_x;
    int posicao_rato_matriz_mapa_y;
    int posicao_Askel_matriz_mapa_x;
    int posicao_Askel_matriz_mapa_y;
    int posicao_Charlie_matriz_mapa_x;
    int posicao_Charlie_matriz_mapa_y;
    int posicao_Susan_matriz_mapa_x;
    int posicao_Susan_matriz_mapa_y;
    int posicao_Pyro_matriz_mapa_x;
    int posicao_Pyro_matriz_mapa_y;
    int pontuacao;
    char matriz_mapa[27][11];
    int nivel_atual;
    int tempo_segundos;
    double tempo_inicio;
    double tempo_atual;
    NIVEL Fase[N_FASES];
    OPCOES opc_menu_principal;
    OPCOES menu_instrucoes;
    CRIATURA_draw RATO;
    CRIATURA_draw G_ASKEL;
    CRIATURA_draw G_CHARLIE;
    CRIATURA_draw G_SUSAN;
    CRIATURA_draw G_PYRO;
    CRIATURA_draw PROP_s;
    CRIATURA_draw PAREDE;
    int retorno;

} VARIAVEIS;

/*VARIAVEIS GLOBAIS*/
volatile bool Fechar = false; //Variavel que permite/nao o fechamento da janela principal
char matriz_mapa[27][11]; //Matriz que armazena os caracteres lidos de arquivos texto (para a construcao dos mapas)
int nivel_atual, tempo_segundos;
double tempo_inicio, tempo_atual;
        //BITMAPS - Sprytes utilizados no programa
        BITMAP *fundo_menu_principal; //Ponteiro para a imagem de fundo do menu principal
        BITMAP *select_menu_principal; //Ponteiro para o cursor de selecao do menu principal (cabeca de um rato)
        BITMAP *select_menu_principal_rectangle; //Ponteiro para a imagem utilizada para atualizar o fundo (onde o cursor nao esta) para a cor azul, evitando uma renderizacao desnecessaria da tela como um todo
        BITMAP *fundo_menu_instrucoes; //Ponteiro para a imagem de fundo do menu de instrucoes e opcoes
        BITMAP *PROPS; //Props utilizadas no jogo - Queijos, vidas, pontuacao e etc...
        BITMAP *ratto;
        BITMAP *gatos;
        BITMAP *atualiza_pontos;
        BITMAP *paredes_mapa;
        //SAMPLES - Musicas e efeitos de audio WAV utilizados no jogo
        SAMPLE *musica_menu_principal; //Ponteiro para a musica de fundo do menu principal
        SAMPLE *som_selecao;
        SAMPLE *som_jogo;
        SAMPLE *som_dano;
        SAMPLE *fimdejogo;
        SAMPLE *gato_hurt;
        SAMPLE *vitoria_sound;
        //FONTES - Fontes de texto utilizadas no programa
        FONT *m_font; //Ponteiro para a fonte game_over
        //OPCOES (struct) - Utilizadas para controlar o processo de abertura/fechamento dos menus
        OPCOES opc_menu_principal = {false, 0};
        OPCOES menu_instrucoes = {false, 0};
        //CRIATURA_draw (struct) utilizada para controlar a parte do spryte que e exibida na tela frame a frame
        CRIATURA_draw RATO = {0, 0, 0, 0, espacamento_x_spryte_criatura, espacamento_y_spryte_criatura};
        CRIATURA_draw G_ASKEL = {0, 0, 0, 0, espacamento_x_spryte_criatura, espacamento_y_spryte_criatura};
        CRIATURA_draw G_CHARLIE = {0, (espacamento_y_spryte_criatura*2)+2, 0, 0, espacamento_x_spryte_criatura, espacamento_y_spryte_criatura};
        CRIATURA_draw G_SUSAN = {0, (espacamento_y_spryte_criatura*4)+2, 0, 0, espacamento_x_spryte_criatura, espacamento_y_spryte_criatura};
        CRIATURA_draw G_PYRO = {0, (espacamento_y_spryte_criatura*6)+2, 0, 0, espacamento_x_spryte_criatura, espacamento_y_spryte_criatura};
        CRIATURA_draw PROP_s = {0, 0, 0, 0, espacamento_x_spryte_prop, espacamento_y_spryte_prop};
        CRIATURA_draw PAREDE = {0, 0, 39, 35, espacamento_x_spryte_criatura, espacamento_y_spryte_criatura};
        //NIVEL (struct) utilizada para armazenar os dados de cada nivel
        NIVEL Fase[N_FASES]; //Cria um vetor de structs NIVEL
/*PROTOTIPACAO DE FUNCOES*/
void permite_fechar();
void menu_principal();
void menu_principal_atualiza_retangulo(int selecionador_rr);
void m_instrucoes();
void init(int resol_x, int resol_y);
void deinit() ;
int le_mapa(int nivel);
int novo_jogo(int caller);
void imprime_vidas_hud(int vidas_iniciais);
void imprime_pontos_hud(int pontos);
void imprime_mapa_tela(BITMAP *paredes_mapa, int caller, bool portas_alteradas);
int calcula_pontuacao();
void coleta_queijo(int posicao_rato_matriz_mapa_x, int posicao_rato_matriz_mapa_y);
void coleta_osso(int posicao_rato_matriz_mapa_x, int posicao_rato_matriz_mapa_y);
void reseta_posicao_criaturas(bool reseta_rato, bool reseta_Askel, bool reseta_Charlie, bool reseta_Susan, bool reseta_Pyro);
int gera_numero_aleatorio();
void imprime_tempo_hud();
void zera_variaveis_nivel();
bool salvarDados(VARIAVEIS memoria);
VARIAVEIS le_memoria();

int main()
{
    /*VARIAVEIS LOCAIS*/
    int cod_erro = 0;
    int cte_zero = 0;
    bool abriu_novo_jogo = false;
    BITMAP *vitoria_level;
    BITMAP *fim_de_jogo;


    /*INICIALIZACOES*/
    init(RESOLUCAO_X, RESOLUCAO_Y); //Inicia a janela externa da biblioteca allegro
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0)
    { //Inicia o sitema de audio do allegro, detectando automaticamente os drivers do sistema
        allegro_message("Erro: Falha ao incializar o sistema de som!\n%s\n", allegro_error);
        return 100;
    }
    for(int ind=0; ind<N_FASES; ind++){ Fase[ind].n_queijos=0; } //Inicia o numero de queijos necessario para vencer cada fase como zero

    srand(time(NULL));
    set_window_title("Ratto - Mouse Trap - Ainda desenvolvendo"); //Muda o titulo da janela
    allegro_message("Se vc consegue ler isso, o programa inicializou bem =)");
    LOCK_FUNCTION(permite_fechar); //Reserva a memoria utilizada pela variavel de fechar a janela
    set_close_button_callback(permite_fechar); //Habilita o botao de fechar a janela principal
    vitoria_level = load_bitmap("models/voce_venceu.bmp", NULL);
    fim_de_jogo = load_bitmap("models/voce_perdeu.bmp", NULL);

    /********************************SERÁ APAGADO*************************/
    printf("O tamanho da super-struct VARIAVEIS atualmente eh: %d bytes",  sizeof(VARIAVEIS));
    printf("\nInicializacao bem sucedida!");
    printf("\nPara fechar a janela, use ESC, ALT+F4 ou clique no X\n\n");
    /********************************SERÁ APAGADO*************************/

	while (!Fechar)
    { //A janela fica aberta para sempre a nao ser que seja selecionada a opcao de sair (com a variavel)
        if((key[KEY_ALT]&&key[KEY_F4]) || (key[KEY_ESC])){ Fechar=true; } //Permite o fechamento da janela

        if(opc_menu_principal.menu_abriu==false && opc_menu_principal.seleciona_opcao==0)
        { //Executa apenas uma vez, abrindo o menu principal
            opc_menu_principal.menu_abriu=true;
            menu_principal();
        }
        if(opc_menu_principal.seleciona_opcao==1)
        { //Se a opcao de "novo jogo" foi selecionada
            if(abriu_novo_jogo==false)
            {
                zera_variaveis_nivel();
                //play_sample(som_jogo,200,150,1000,0);
                abriu_novo_jogo=true;
            }
            if(nivel_atual == (N_FASES+1))
            { //Se o jogador vencer TODAS AS FASES
                draw_sprite(screen, vitoria_level, 0, 0);
                stop_sample(som_jogo);
                printf("\n\tVoce venceu todos os niveis!!!");
                rest(5000); //Espera tres segundos
                nivel_atual = 0;
            }

            rectfill(screen, (RESOLUCAO_X-AREAJOGO_X)/2, (RESOLUCAO_Y-AREAJOGO_Y)/2, ((RESOLUCAO_X-AREAJOGO_X)/2)+AREAJOGO_X, ((RESOLUCAO_Y-AREAJOGO_Y)/2)+AREAJOGO_Y, 0xa4abbf); //Desenha um quadrado cinza centralizado na tela, com a area do jogo
            cod_erro = novo_jogo(1);

            if(cod_erro == 15)
            { //Se o jgador passar de nivel
                draw_sprite(screen, vitoria_level, 0, 0);
                stop_sample(som_jogo);
                printf("\n\tVoce venceu!");
                rest(3000); //Espera tres segundos
                nivel_atual++;
            }
            if(cod_erro == 25)
            { //Se o jogador ficar sem vidas
                draw_sprite(screen, fim_de_jogo, 0, 0);
                stop_sample(som_jogo);
                printf("\n\tVoce perdeu!");
                rest(3000); //Espera tres segundos
                nivel_atual=0;
                opc_menu_principal.seleciona_opcao = 0;
                abriu_novo_jogo = false;
            }
            if(cod_erro == 20)
            { //Se o jogador sair do jogo (tab)
                abriu_novo_jogo = false;
                stop_sample(som_jogo);
            }
            if(cod_erro == 101)
            {
                /*NAO FOI ECONTRADO NENHUM MAPA*/
                Fechar = !Fechar;
                allegro_message("Houve um erro ao carregar os mapas");
                return 101;
            }

        }
        if(opc_menu_principal.seleciona_opcao==2)
        { //Se a opcao de "CONTINUAR JOGO" foi selecionada
            rectfill(screen, (RESOLUCAO_X-AREAJOGO_X)/2, (RESOLUCAO_Y-AREAJOGO_Y)/2, ((RESOLUCAO_X-AREAJOGO_X)/2)+AREAJOGO_X, ((RESOLUCAO_Y-AREAJOGO_Y)/2)+AREAJOGO_Y, 0xa4abbf); //Desenha um quadrado cinza centralizado na tela, com a area do jogo

            opc_menu_principal.seleciona_opcao=1;

            if(abriu_novo_jogo==false)
            {
                //play_sample(som_jogo,200,150,1000,0);
                abriu_novo_jogo=true;
            }

            cod_erro = novo_jogo(cte_zero);

            if(nivel_atual == (N_FASES-1))
            { //Se o jogador vencer TODAS AS FASES
                draw_sprite(screen, vitoria_level, 0, 0);
                stop_sample(som_jogo);
                printf("\n\tVoce venceu todos os niveis!!!");
                rest(5000); //Espera tres segundos
                nivel_atual = 0;
            }
            if(cod_erro == 15)
                { //Se o jgador passar de nivel
                draw_sprite(screen, vitoria_level, 0, 0);
                stop_sample(som_jogo);
                printf("\n\tVoce venceu!");
                rest(3000); //Espera tres segundos
                nivel_atual++;
            }
            if(cod_erro == 25)
            { //Se o jogador ficar sem vidas
                draw_sprite(screen, fim_de_jogo, 0, 0);
                stop_sample(som_jogo);
                printf("\n\tVoce perdeu!");
                rest(3000); //Espera tres segundos
                nivel_atual=0;
                opc_menu_principal.seleciona_opcao = 0;
                abriu_novo_jogo = false;
            }
            if(cod_erro == 20)
            { //Se o jogador sair do jogo (tab)
                abriu_novo_jogo = false;
                stop_sample(som_jogo);
            }
            if(cod_erro == 101)
            {
                /*NAO FOI ECONTRADO NENHUM MAPA*/
                Fechar = !Fechar;
                allegro_message("Houve um erro ao carregar os mapas");
                return 101;
            }
            //idk
        }
        if(opc_menu_principal.seleciona_opcao==3 && menu_instrucoes.menu_abriu==false)
        { //Se a opcao de "instrucoes" foi selecionada
            menu_instrucoes.menu_abriu=true;
            m_instrucoes();
            opc_menu_principal.menu_abriu=0;
        }
        opc_menu_principal.menu_abriu=false;
	}

    destroy_sample(musica_menu_principal);
    destroy_bitmap(vitoria_level);
    destroy_bitmap(fundo_menu_principal);
    destroy_bitmap(select_menu_principal);
    destroy_bitmap(select_menu_principal_rectangle);
    destroy_font(m_font);
	deinit();

    return cod_erro;
}
END_OF_MAIN();

/*DECLARACAO DE FUNCOES*/
void permite_fechar()
{
    Fechar = !Fechar; //Altera o estado da variavel Fechar
}
void menu_principal()
{
    menu_instrucoes.menu_abriu=false;
    int y_selecionador=(RESOLUCAO_Y/2)-35;
    musica_menu_principal =  load_wav("music/menu_loop.wav");
    som_selecao = load_wav("sounds/som_selecao.wav");
    som_jogo = load_wav("music/Somebody_I_Used_To_Know.wav");
    som_dano = load_wav("sounds/rato_hurt.wav");
    fimdejogo = load_wav("sounds/fimdejogo.wav");
    gato_hurt = load_wav("sounds/gato_hurt.wav");
    vitoria_sound = load_wav("sounds/vitoria.wav");
    set_volume(150, 150);
    play_sample(musica_menu_principal,230,150,1000,1);

    fundo_menu_principal = load_bitmap("models/fundo_menu_principal.bmp", NULL);
    select_menu_principal = load_bitmap("models/rato_select_r.bmp", NULL);
    select_menu_principal_rectangle = load_bitmap("models/selection_rectangle.bmp", NULL);
    draw_sprite(screen, fundo_menu_principal, 0, 0);

    /*IMPRIME ALGUNS TEXTOS NA TELA*/
    m_font = load_font("font/game_over.pcx", NULL, NULL);
    textout_centre_ex(screen, m_font, "v1.2 lastrev G", 180, RESOLUCAO_Y-37, 0x0AB944, -1);
    textout_ex(screen, m_font, "NOVO JOGO (N)", (RESOLUCAO_X/2)-170, (RESOLUCAO_Y/2)-40, 0x0512C3, -1);
    textout_ex(screen, m_font, "CONTINUAR JOGO (C)", (RESOLUCAO_X/2)-170, (RESOLUCAO_Y/2)-10, 0x0512C3, -1);
    textout_ex(screen, m_font, "DICAS E OPCOES (I)", (RESOLUCAO_X/2)-170, (RESOLUCAO_Y/2)+20, 0x0512C3, -1);
    textout_ex(screen, m_font, "SAIR (Q)", (RESOLUCAO_X/2)-170, (RESOLUCAO_Y/2)+50, 0x0512C3, -1);

    while((opc_menu_principal.seleciona_opcao==0)&& !((key[KEY_ALT]&&key[KEY_F4]) || (key[KEY_ESC])) && !Fechar)
    {
        /*ATUALIZA OS SPRYTES NA TELA*/
        draw_sprite(screen, select_menu_principal, (RESOLUCAO_X/2)-200, y_selecionador);
        menu_principal_atualiza_retangulo(y_selecionador); //Quando a cabeca do rato muda de lugar, é necessario colocar essa imagem nos outros

        /*CONTROLA A POSICAO DO ICONE DE SELECIONAR*/
        if (key[KEY_UP]||key[KEY_W])
        {
            if(y_selecionador != 165)
            {
                y_selecionador-=30;
            }
            else
            {
                y_selecionador = 255;
            }
        }
        if (key[KEY_DOWN]||key[KEY_S])
        {
                if(y_selecionador != 255)
                {
                    y_selecionador+=30;
                }
                else
                {
                    y_selecionador = 165;
                }
        }
        /*RESETA VARIAVEIS DOS SUBMENUS*/
        menu_instrucoes.seleciona_opcao=0;

        if (key[KEY_ENTER]||key[KEY_ENTER_PAD])
        {
            play_sample(som_selecao,200,150,1000,0);
            if(y_selecionador == 165){ opc_menu_principal.seleciona_opcao=1; } //Seleciona a opcao novo jogo
            if(y_selecionador == 195){ opc_menu_principal.seleciona_opcao=2; } //Seleciona a opcao de carregar o ultimo jogo
            if(y_selecionador == 225){ opc_menu_principal.seleciona_opcao=3; } //Seleciona a opcao de instrucoes
            if(y_selecionador == 255){ Fechar = true; } //Sai do jogo
        }
        if(key[KEY_N]){ opc_menu_principal.seleciona_opcao=1; play_sample(som_selecao,200,150,1000,0);} //Seleciona a opcao novo jogo
        if(key[KEY_C]){ opc_menu_principal.seleciona_opcao=2; play_sample(som_selecao,200,150,1000,0);} //Seleciona a opcao de carregar o ultimo jogo
        if(key[KEY_I]){ opc_menu_principal.seleciona_opcao=3; play_sample(som_selecao,200,150,1000,0);} //Seleciona a opcao de instrucoes
        if(key[KEY_Q]){ Fechar = true; } //Sai do jogo

        /*CRIA UM PEQUENO DELAY (para uma selecao mais facil) */
        rest(63);
    }
}
void m_instrucoes()
{
    /*VARIAVEIS DE CONTROLE DE ABERTURA DO MENU*/
    opc_menu_principal.menu_abriu=false;
    opc_menu_principal.seleciona_opcao=0;
    menu_instrucoes.seleciona_opcao=0;
    int cursor_pos = 0;
    int contador_mais = 0;
    int c_counter = 0;
    /*DEFINE O ENDERECO DOS SPRYTES UTILIZADOS*/
    fundo_menu_instrucoes = load_bitmap("models/FundoMenuInstrucoes1.bmp", NULL);
    select_menu_principal = load_bitmap("models/rato_select_r.bmp", NULL);
    m_font = load_font("font/game_over.pcx", NULL, NULL);

    /*DESENHA OS SPRYTES UTILIZADOS NA TELA*/
    draw_sprite(screen, fundo_menu_instrucoes, 0, 0);
    draw_sprite(screen, select_menu_principal, (RESOLUCAO_X/2)-200, (RESOLUCAO_Y/2)+74);

    /*IMPRIME TEXTOS NA TELA*/
    textout_centre_ex(screen, m_font, "v1.2 lastrev G", 180, RESOLUCAO_Y-37, 0x0AB944, -1);
    textout_ex(screen, m_font, "VOLTAR (V)", (RESOLUCAO_X/2)-170, (RESOLUCAO_Y/2)+70, 0x0512C3, -1);
    textout_ex(screen, m_font, "MAIS (M)", (RESOLUCAO_X/2), (RESOLUCAO_Y/2)+70, 0x0512C3, -1);

    while(menu_instrucoes.seleciona_opcao==0 && !Fechar && !key[KEY_ESC])
    {
        if(key[KEY_RIGHT] || key[KEY_D] || key[KEY_LEFT] || key[KEY_A])
        { //Se alguma tecla direcional for apertada...
            if(cursor_pos == 0)
            { //O cursor esta na posicao MAIS
                cursor_pos = 1;
                draw_sprite(screen, select_menu_principal, (RESOLUCAO_X/2)-30, (RESOLUCAO_Y/2)+74);
                draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-200, (RESOLUCAO_Y/2)+74);
            }
            else
            { //O cursor esta na posicao VOLTAR
                cursor_pos = 0;
                draw_sprite(screen, select_menu_principal, (RESOLUCAO_X/2)-200, (RESOLUCAO_Y/2)+74);
                draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-30, (RESOLUCAO_Y/2)+74);
            }

            /*CRIA UM DELAY PARA FACILITAR NA SELECAO DAS OPCOES*/
            rest(120);
        }
        if((key[KEY_ENTER] || key[KEY_ENTER_PAD]) && cursor_pos == 0 ||key[KEY_V])
        { //Se a opcao selecionada for a de voltar...
            play_sample(som_selecao,200,150,1000,0);
            stop_sample(musica_menu_principal);
            opc_menu_principal.menu_abriu=false;
            opc_menu_principal.seleciona_opcao=0;
            menu_instrucoes.seleciona_opcao=1;
            rest(120);
        }
        if((key[KEY_ENTER] || key[KEY_ENTER_PAD]) && cursor_pos == 1 || key[KEY_M])
        { //Se a opcao selecionada for MAIS
            play_sample(som_selecao,200,150,1000,0);
            cursor_pos = 0;
            if(contador_mais==1)
            {
                fundo_menu_instrucoes = load_bitmap("models/FundoMenuInstrucoes3.bmp", NULL);
                contador_mais++;
            }
            if(contador_mais==0)
            {
                fundo_menu_instrucoes = load_bitmap("models/FundoMenuInstrucoes2.bmp", NULL);
                contador_mais++;
            }
            draw_sprite(screen, fundo_menu_instrucoes, 0, 0);
            textout_centre_ex(screen, m_font, "v1.2 lastrev G", 180, RESOLUCAO_Y-37, 0x0AB944, -1);
            textout_ex(screen, m_font, "VOLTAR (V)", (RESOLUCAO_X/2)-170, (RESOLUCAO_Y/2)+70, 0x0512C3, -1);
            textout_ex(screen, m_font, "MAIS (M)", (RESOLUCAO_X/2), (RESOLUCAO_Y/2)+70, 0x0512C3, -1);
            draw_sprite(screen, select_menu_principal, (RESOLUCAO_X/2)-200, (RESOLUCAO_Y/2)+74);
            draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-30, (RESOLUCAO_Y/2)+74);
        }
    }
}
void menu_principal_atualiza_retangulo(int selecionador_rr)
{
            if(selecionador_rr == 165)
            {
                draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-200, 195);
                draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-200, 225);
                draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-200, 255);
            }
            if(selecionador_rr == 195)
            {
                draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-200, 165);
                draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-200, 225);
                draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-200, 255);
            }
            if(selecionador_rr == 225)
            {
                draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-200, 165);
                draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-200, 195);
                draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-200, 255);
            }
            if(selecionador_rr == 255)
            {
                draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-200, 165);
                draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-200, 195);
                draw_sprite(screen, select_menu_principal_rectangle, (RESOLUCAO_X/2)-200, 225);
            }
}
void init(int resol_x, int resol_y)
 {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED,  resol_x, resol_y, 0, 0);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,  resol_x, resol_y, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}
	install_timer();
	install_keyboard();
	/* add other initializations here */
}
void deinit()
{
	clear_keybuf();
	/* add other deinitializations here */
}
int le_mapa(int nivel)
{
    FILE *mapa_novo;
    char number = nivel;
    char n_nivel_correct[2];
    char end_mapa_novo[17] = "level/nivel"; //Armazena o endereco em que sera salvo o mapa
    if(nivel<10)
    {
        strcat(end_mapa_novo, "0");
        sprintf(n_nivel_correct, "%d", nivel);
    }
    if(nivel>9)
    {
        sprintf(n_nivel_correct, "%d", nivel);
    }
    strcat(end_mapa_novo, n_nivel_correct);
    strcat(end_mapa_novo, ".txt");
    mapa_novo = fopen(end_mapa_novo, "r");



    if(!mapa_novo)
    { //Se nao abrir o arquivo mapa retorna 101
        return 101;
    }

    for(int linha=0; linha<11; linha++)
    {
        for(int coluna=0; coluna<28; coluna++)
        {
            fscanf(mapa_novo, "%c", &matriz_mapa[coluna][linha]);
        }
    }
    nivel_atual = nivel;

    fclose(mapa_novo);

    printf("O conteudo da string eh: %s\n\n", end_mapa_novo);
    return 0;
}
int novo_jogo(int caller)
{ //Um novo jogo foi iniciado
     printf("\nIniciou a funcao novo jogo\n");
    /*VARIAVEIS LOCAIS*/
    int cod_erro = 0; //Variavel que armazena o codigo de erro, para o retorno dessa funcao
    int vidas_iniciais;
    bool portas_alteradas = false;
    bool atualizou_cachorro = false;
    bool desatualizou_cachorro = true;
    volatile bool alterna_spryte = false;
    int ultima_impressao_tempo = 0;
    int tempo_virou_cachorro = 0;
    bool moveu_Askel = false;
    bool moveu_Charlie = false;
    bool moveu_Susan = false;
    bool moveu_Pyro =false;
    int posicao_rato_matriz_mapa_x;
    int posicao_rato_matriz_mapa_y;
    int posicao_Askel_matriz_mapa_x;
    int posicao_Askel_matriz_mapa_y;
    int posicao_Charlie_matriz_mapa_x;
    int posicao_Charlie_matriz_mapa_y;
    int posicao_Susan_matriz_mapa_x;
    int posicao_Susan_matriz_mapa_y;
    int posicao_Pyro_matriz_mapa_x;
    int posicao_Pyro_matriz_mapa_y;

    printf("chegou ate aqui");
    int pontuacao = calcula_pontuacao(); //Calcula  a pontuacao (inicia com 10 pontos - exemplo)

    BITMAP *HUD; //Imagem de fundo, exibida durante o jogo
    int deslocamento_Askel, deslocamento_Charlie, deslocamento_Susan, deslocamento_Pyro;

    /***********************INICIALIZACAO DAS VARIAVEIS************************/
    pontuacao = 0;
    tempo_inicio = (double) clock () / CLOCKS_PER_SEC;
    vidas_iniciais = Fase[nivel_atual-1].Rato.vida;

    /*GERA A DIRECAO EM QUE OS GATOS VAO TENTAR SE MOVER - (0-Cima | 1-Esquerda | 2-Baixo | 3-Direita)*/
    Fase[nivel_atual-1].Gato_Askel.direcao = gera_numero_aleatorio();
    Fase[nivel_atual-1].Gato_Charlie.direcao = gera_numero_aleatorio();
    Fase[nivel_atual-1].Gato_Susan.direcao = gera_numero_aleatorio();
    Fase[nivel_atual-1].Gato_Pyro.direcao = gera_numero_aleatorio();

    printf("O valor de caller eh: %d", caller);

    if(caller==0)
    {
         VARIAVEIS Var_memoria = le_memoria();
         printf("\nLeu a memoria\n");
         if(Var_memoria.retorno == 404)
         { //Se houver algum erro lendo o arquivo de memoria
            return 101;
        }
        nivel_atual = Var_memoria.nivel_atual;
    }

    stop_sample(musica_menu_principal);
    HUD = load_bitmap("models/hud_jogo.bmp", NULL);
    PROPS = load_bitmap("models/ratto_map_props.bmp", NULL);
    paredes_mapa = load_bitmap("models/ratto_map_textures.bmp", NULL);
    ratto = load_bitmap("models/rato_retail.bmp", NULL);
    gatos = load_bitmap("models/cats_retail.bmp", NULL);
    atualiza_pontos = load_bitmap("models/pontuacao_rect.bmp", NULL);

    draw_sprite(screen, HUD, 0, 0);
    textout_ex(screen, m_font, "Versao v1.2", ((RESOLUCAO_X-AREAJOGO_X)/2), RESOLUCAO_Y-30, 0x0AB944, -1);
    textout_ex(screen, m_font, "VIDAS: ", 35, -4, 0x0AB944, -1);
    textout_ex(screen, m_font, "TEMPO: ", 220, -4, 0x0AB944, -1);

    cod_erro = le_mapa(nivel_atual);

    if(cod_erro == 101)
    { //Se houver algum erro lendo o mapa
        return cod_erro;
    }

        if(caller == 0)
        {  //Se o jogo esta sendo carregado
            VARIAVEIS Var_memoria = le_memoria();
            if(Var_memoria.retorno == 404)
            { //Se houver algum erro lendo o arquivo de memoria
                return 101;
            }
            alterna_spryte = Var_memoria.alterna_spryte;
            atualizou_cachorro= Var_memoria.atualizou_cachorro;
            desatualizou_cachorro=Var_memoria.desatualizou_cachorro;
            memccpy(Fase, Var_memoria.Fase, ':', sizeof(Fase));
            G_ASKEL=Var_memoria.G_ASKEL;
            G_CHARLIE=Var_memoria.G_CHARLIE;
            G_PYRO=Var_memoria.G_PYRO;
            G_SUSAN=Var_memoria.G_SUSAN;
            memccpy(matriz_mapa, Var_memoria.matriz_mapa, ':', sizeof(matriz_mapa));
            menu_instrucoes=Var_memoria.menu_instrucoes;
            moveu_Askel=Var_memoria.moveu_Askel;
            moveu_Charlie=Var_memoria.moveu_Charlie;
            moveu_Susan=Var_memoria.moveu_Susan;
            moveu_Pyro=Var_memoria.moveu_Pyro;
            nivel_atual=Var_memoria.nivel_atual;
            opc_menu_principal=Var_memoria.opc_menu_principal;
            PAREDE=Var_memoria.PAREDE;
            pontuacao=Var_memoria.pontuacao;
            portas_alteradas=Var_memoria.portas_alteradas;
            posicao_Askel_matriz_mapa_x=Var_memoria.posicao_Askel_matriz_mapa_x;
            posicao_Askel_matriz_mapa_y=Var_memoria.posicao_Askel_matriz_mapa_y;
            posicao_Charlie_matriz_mapa_x=Var_memoria.posicao_Charlie_matriz_mapa_x;
            posicao_Charlie_matriz_mapa_y=Var_memoria.posicao_Charlie_matriz_mapa_y;
            posicao_Susan_matriz_mapa_x=Var_memoria.posicao_Susan_matriz_mapa_x;
            posicao_Susan_matriz_mapa_y=Var_memoria.posicao_Susan_matriz_mapa_y;
            posicao_Pyro_matriz_mapa_x=Var_memoria.posicao_Pyro_matriz_mapa_x;
            posicao_Pyro_matriz_mapa_y=Var_memoria.posicao_Pyro_matriz_mapa_y;
            posicao_rato_matriz_mapa_x=Var_memoria.posicao_rato_matriz_mapa_x;
            posicao_rato_matriz_mapa_y=Var_memoria.posicao_rato_matriz_mapa_y;
            PROP_s=Var_memoria.PROP_s;
            RATO=Var_memoria.RATO;
            tempo_atual=Var_memoria.tempo_atual;
            tempo_inicio=Var_memoria.tempo_inicio;
            tempo_segundos=Var_memoria.tempo_segundos;
            tempo_virou_cachorro=Var_memoria.tempo_virou_cachorro;
            ultima_impressao_tempo=Var_memoria.ultima_impressao_tempo;
            tempo_segundos=Var_memoria.vidas_iniciais;
            Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x=Var_memoria.Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x;
    }

    imprime_vidas_hud(vidas_iniciais);
    imprime_pontos_hud(pontuacao);
    imprime_mapa_tela(paredes_mapa, caller, portas_alteradas);

     printf("\n\nO nivel %d foi carregado, com %d queijos\n\n", nivel_atual, Fase[nivel_atual-1].n_queijos);
    //Imprime o HUD (VIDAS/PONTOS/OSSOS/TEXTOS)
    //Lê ultimo estado jogado (pontuação e etc)
    //Imprime o mapa

    while(!Fechar || !key[KEY_ESC])
    {
        /*CALCULA A QUANTO TEMPO O JOGO ESTA RODANDO*/
        tempo_atual = (double) clock () / CLOCKS_PER_SEC;
        tempo_segundos = (int)(tempo_atual - tempo_inicio);

        if(tempo_segundos - ultima_impressao_tempo > 0)
        { //A cada segundo....
            imprime_tempo_hud();
            ultima_impressao_tempo = tempo_segundos;

            if(moveu_Askel == false)
            {
                Fase[nivel_atual-1].Gato_Askel.direcao = gera_numero_aleatorio(); //Gera uma nova direcao para o Askel
            }
            if(moveu_Askel == true)
            {
                moveu_Askel = false;
            }
            if(moveu_Charlie == false)
            {
                Fase[nivel_atual-1].Gato_Charlie.direcao = gera_numero_aleatorio(); //Gera uma nova direcao para o Charlie
            }
            if(moveu_Charlie == true)
            {
                moveu_Charlie = false;
            }
            if(moveu_Susan == false)
            {
                Fase[nivel_atual-1].Gato_Susan.direcao = gera_numero_aleatorio(); //Gera uma nova direcao para o Susan
            }
            if(moveu_Susan == true)
            {
                moveu_Susan = false;
            }
            if(moveu_Pyro == false)
            {
                Fase[nivel_atual-1].Gato_Pyro.direcao = gera_numero_aleatorio(); //Gera uma nova direcao para o Susan
            }
            if(moveu_Pyro == true)
            {
                moveu_Pyro = false;
            }
        }

        posicao_rato_matriz_mapa_x = (Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x-38)/23;
        posicao_rato_matriz_mapa_y = (Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y-39)/30;
        posicao_Askel_matriz_mapa_x = (Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x-38)/23;
        posicao_Askel_matriz_mapa_y = (Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y-39)/30;
        posicao_Charlie_matriz_mapa_x = (Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x-38)/23;
        posicao_Charlie_matriz_mapa_y = (Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y-39)/30;
        posicao_Susan_matriz_mapa_x = (Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x-38)/23;
        posicao_Susan_matriz_mapa_y = (Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y-39)/30;
        posicao_Pyro_matriz_mapa_x = (Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x-38)/23;
        posicao_Pyro_matriz_mapa_y = (Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y-39)/30;

        masked_blit(ratto, screen, RATO.wx, RATO.wy, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y-5, RATO.w, RATO.h+1);
        masked_blit(gatos, screen, G_ASKEL.wx, G_ASKEL.wy, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y-4, G_ASKEL.w, G_ASKEL.h+1);
        masked_blit(gatos, screen, G_CHARLIE.wx, G_CHARLIE.wy, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y-4, G_CHARLIE.w, G_CHARLIE.h+1);
        masked_blit(gatos, screen, G_SUSAN.wx, G_SUSAN.wy+2, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y-4, G_SUSAN.w, G_SUSAN.h);
        masked_blit(gatos, screen, G_PYRO.wx, G_PYRO.wy+4, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y-4, G_PYRO.w, G_PYRO.h+1);

        if(matriz_mapa[posicao_rato_matriz_mapa_x][posicao_rato_matriz_mapa_y] == 'Q')
        { //Se a posicao do rato for encima de um queijo - coleta um queijo
            coleta_queijo(posicao_rato_matriz_mapa_x, posicao_rato_matriz_mapa_y);
            pontuacao = calcula_pontuacao(); //Calcula  a pontuacao (inicia com 10 pontos - exemplo)
            imprime_pontos_hud(pontuacao);
        }
        if(matriz_mapa[posicao_rato_matriz_mapa_x][posicao_rato_matriz_mapa_y] == 'O')
        { //Se a posicao do rato for encima de um osso - coleta um osso
            coleta_osso(posicao_rato_matriz_mapa_x, posicao_rato_matriz_mapa_y);
            pontuacao = calcula_pontuacao(); //Calcula  a pontuacao (inicia com 10 pontos - exemplo)
            Fase[nivel_atual-1].Rato.forma = 1; //Modo cachorro
            tempo_virou_cachorro = tempo_segundos;
            desatualizou_cachorro = true;
            if(atualizou_cachorro == false)
            {
                masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1);
                atualizou_cachorro = true;
            }
            //ENTRA NO MODO CACHORRO POR UM TEMPO
        }
        /***********************SE APERTAR UMA TECLA*************************/
        if((((key[KEY_S]||key[KEY_DOWN]) && (matriz_mapa[posicao_rato_matriz_mapa_x][posicao_rato_matriz_mapa_y+1] != 'X'))) && !key[KEY_D] && !key[KEY_A] && !key[KEY_LEFT] && !key[KEY_RIGHT])
        { //Se mover para baixo..
            if ((portas_alteradas == false && matriz_mapa[posicao_rato_matriz_mapa_x][posicao_rato_matriz_mapa_y+1] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_rato_matriz_mapa_x-1][posicao_rato_matriz_mapa_y] != 'T'))
            {
                atualizou_cachorro = false;
                masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1); //Desenha as paredes no mapa
                Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y+=espacamento_y_spryte_criatura;
                masked_blit(ratto, screen, RATO.wx, RATO.wy, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y-5, RATO.w, RATO.h+1);
            }
        }
        if((((key[KEY_W]||key[KEY_UP]) && (matriz_mapa[posicao_rato_matriz_mapa_x][posicao_rato_matriz_mapa_y-1] != 'X'))) && !key[KEY_D] && !key[KEY_A] && !key[KEY_LEFT] && !key[KEY_RIGHT])
        { //Se mover para cima..
            if ((portas_alteradas == false && matriz_mapa[posicao_rato_matriz_mapa_x][posicao_rato_matriz_mapa_y-1] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_rato_matriz_mapa_x-1][posicao_rato_matriz_mapa_y-2] != 'T'))
            {
                atualizou_cachorro = false;
                masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1); //Desenha as paredes no mapa
                Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y-=espacamento_y_spryte_criatura;
                masked_blit(ratto, screen, RATO.wx, RATO.wy, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y-5, RATO.w, RATO.h+1);
            }
        }
        if(((key[KEY_D]||key[KEY_RIGHT]) && (matriz_mapa[posicao_rato_matriz_mapa_x+1][posicao_rato_matriz_mapa_y] != 'X')))
        { //Se mover para a direita..
            if ((portas_alteradas == false && matriz_mapa[posicao_rato_matriz_mapa_x+1][posicao_rato_matriz_mapa_y] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_rato_matriz_mapa_x][posicao_rato_matriz_mapa_y-1] != 'T'))
            {
                atualizou_cachorro = false;
                masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1); //Desenha as paredes no mapa
                Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x+=espacamento_x_spryte_criatura;
                masked_blit(ratto, screen, RATO.wx, RATO.wy, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y-5, RATO.w, RATO.h+1);
            }
        }
        if(((key[KEY_A]||key[KEY_LEFT]) && (matriz_mapa[posicao_rato_matriz_mapa_x-1][posicao_rato_matriz_mapa_y] != 'X')))
        { //Se mover para a esquerda..
            if ((portas_alteradas == false && matriz_mapa[posicao_rato_matriz_mapa_x-1][posicao_rato_matriz_mapa_y] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_rato_matriz_mapa_x-2][posicao_rato_matriz_mapa_y-1] != 'T'))
            {
                atualizou_cachorro = false;
                masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1); //Desenha as paredes no mapa
                Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x-=espacamento_x_spryte_criatura;
                masked_blit(ratto, screen, RATO.wx, RATO.wy, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y-5, RATO.w, RATO.h+1);
            }
        }
        if(key[KEY_B])
        { //Se as portas forem alteradas... (as portas tambem esmagam criaturas
            portas_alteradas = !portas_alteradas;
            if(portas_alteradas == true)
            { //Portas abrindo
                for(int linha=0; linha<11; linha++)
                {
                    for(int coluna=0; coluna<27; coluna++)
                    {
                        if(matriz_mapa[coluna][linha] == 'T')
                        {
                            /*****SE UMA PORTA ABRIR ENCIMA DE ALGUMA CRIATURA...*******/
                            if(coluna+1 == posicao_Askel_matriz_mapa_x && linha+1 == posicao_Askel_matriz_mapa_y)
                            { //Se esmagar o Askel
                                play_sample(gato_hurt,254,150,1000,0);
                                reseta_posicao_criaturas(false, true, false, false, false);
                            }
                            if(coluna+1 == posicao_Charlie_matriz_mapa_x && linha+1 == posicao_Charlie_matriz_mapa_y)
                            { //Se esmagar o Charlie
                                play_sample(gato_hurt,254,150,1000,0);
                                reseta_posicao_criaturas(false, false, true, false, false);
                            }
                            if(coluna+1 == posicao_Susan_matriz_mapa_x && linha+1 == posicao_Susan_matriz_mapa_y)
                            { //Se esmagar a Susan
                                play_sample(gato_hurt,254,150,1000,0);
                                reseta_posicao_criaturas(false, false, false, true, false);
                            }
                            if(coluna+1 == posicao_Pyro_matriz_mapa_x && linha+1 == posicao_Pyro_matriz_mapa_y)
                            { //Se esmagar o Pyro
                                play_sample(gato_hurt,254,150,1000,0);
                                reseta_posicao_criaturas(false, false, false, false, true);
                            }
                            if(coluna+1 == posicao_rato_matriz_mapa_x && linha+1 == posicao_rato_matriz_mapa_y)
                            {
                                printf("\n\tVoce perdeu uma vida!");
                                Fase[0].Rato.vida--;
                                play_sample(som_dano,250,150,1000,0);
                                imprime_vidas_hud(vidas_iniciais);
                                reseta_posicao_criaturas(true, true, true, true, true);
                            }
                            masked_blit(paredes_mapa, screen, 97, PAREDE.wy, (39+(coluna)*23), (35+(linha)*30)-1, PAREDE.w+1, PAREDE.h+1); //Deixa cinza o lugar de onde as portas sairam
                            masked_blit(paredes_mapa, screen, 73, PAREDE.wy, (39+(coluna+1)*23), (35+(linha+1)*30)-1, PAREDE.w+1, PAREDE.h+1); //Re-Desenha as portas uma coluna e uma linha para baixo
                        }
                    }
                }
            }
            else
            { //Portas fechando
                for(int linha=0; linha<11; linha++)
                {
                    for(int coluna=0; coluna<27; coluna++)
                    {
                        if(matriz_mapa[coluna][linha] == 'T')
                        {
                            /*****SE UMA PORTA ABRIR ENCIMA DE ALGUMA CRIATURA...*******/
                            if(coluna == posicao_Askel_matriz_mapa_x && linha == posicao_Askel_matriz_mapa_y)
                            { //Se esmagar o Askel
                                play_sample(gato_hurt,254,150,1000,0);
                                reseta_posicao_criaturas(false, true, false, false, false);
                            }
                            if(coluna == posicao_Charlie_matriz_mapa_x && linha == posicao_Charlie_matriz_mapa_y)
                            { //Se esmagar o Charlie
                                play_sample(gato_hurt,254,150,1000,0);
                                reseta_posicao_criaturas(false, false, true, false, false);
                            }
                            if(coluna == posicao_Susan_matriz_mapa_x && linha == posicao_Susan_matriz_mapa_y)
                            { //Se esmagar a Susan
                                play_sample(gato_hurt,254,150,1000,0);
                                reseta_posicao_criaturas(false, false, false, true, false);
                            }
                            if(coluna == posicao_Pyro_matriz_mapa_x && linha == posicao_Pyro_matriz_mapa_y)
                            { //Se esmagar a Susan
                                play_sample(gato_hurt,254,150,1000,0);
                                reseta_posicao_criaturas(false, false, false, false, true);
                            }
                            if(coluna == posicao_rato_matriz_mapa_x && linha == posicao_rato_matriz_mapa_y)
                            {
                                printf("\n\tVoce perdeu uma vida!");
                                Fase[0].Rato.vida--;
                                play_sample(som_dano,250,150,1000,0);
                                imprime_vidas_hud(vidas_iniciais);
                                reseta_posicao_criaturas(true, true, true, true, true);
                            }
                            masked_blit(paredes_mapa, screen, 97, PAREDE.wy, (39+(coluna+1)*23), (35+(linha+1)*30)-1, PAREDE.w+1, PAREDE.h+1); //Deixa cinza o lugar de onde as portas sairam
                            masked_blit(paredes_mapa, screen, 73, PAREDE.wy, (39+(coluna)*23), (35+(linha)*30)-1, PAREDE.w+1, PAREDE.h+1); //Re-Desenha as portas uma coluna e uma linha para baixo
                        }
                        if(matriz_mapa[coluna][linha]=='Q')
                        {
                            masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(coluna)*23)-1, (40+(linha)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha os queijos
                        }
                    }
                }
            }
        }
        if(key[KEY_TAB])
        { //Se a pessoa ir para o menu
            opc_menu_principal.seleciona_opcao = 0; //Desmarca a opcao selecionada no menu

            /***************SALVA O JOGO*********************/
            VARIAVEIS Var_memoria;
            Var_memoria.alterna_spryte=alterna_spryte;
            Var_memoria.atualizou_cachorro=atualizou_cachorro;
            Var_memoria.cod_erro=cod_erro;
            Var_memoria.desatualizou_cachorro=desatualizou_cachorro;
            memccpy(Var_memoria.Fase, Fase, ':', sizeof(Fase));
            Var_memoria.G_ASKEL=G_ASKEL;
            Var_memoria.G_CHARLIE=G_CHARLIE;
            Var_memoria.G_PYRO=G_PYRO;
            Var_memoria.G_SUSAN=G_SUSAN;
            memccpy(Var_memoria.matriz_mapa, matriz_mapa, ':', sizeof(matriz_mapa));
            Var_memoria.menu_instrucoes=menu_instrucoes;
            Var_memoria.moveu_Askel=moveu_Askel;
            Var_memoria.moveu_Charlie=moveu_Charlie;
            Var_memoria.moveu_Susan=moveu_Susan;
            Var_memoria.moveu_Pyro=moveu_Pyro;
            Var_memoria.nivel_atual=nivel_atual;
            Var_memoria.opc_menu_principal=opc_menu_principal;
            Var_memoria.PAREDE=PAREDE;
            Var_memoria.pontuacao=pontuacao;
            Var_memoria.portas_alteradas=portas_alteradas;
            Var_memoria.posicao_Askel_matriz_mapa_x=posicao_Askel_matriz_mapa_x;
            Var_memoria.posicao_Askel_matriz_mapa_y=posicao_Askel_matriz_mapa_y;
            Var_memoria.posicao_Charlie_matriz_mapa_x=posicao_Charlie_matriz_mapa_x;
            Var_memoria.posicao_Charlie_matriz_mapa_y=posicao_Charlie_matriz_mapa_y;
            Var_memoria.posicao_Susan_matriz_mapa_x=posicao_Susan_matriz_mapa_x;
            Var_memoria.posicao_Susan_matriz_mapa_y=posicao_Susan_matriz_mapa_y;
            Var_memoria.posicao_Pyro_matriz_mapa_x=posicao_Pyro_matriz_mapa_x;
            Var_memoria.posicao_Pyro_matriz_mapa_y=posicao_Pyro_matriz_mapa_y;
            Var_memoria.posicao_rato_matriz_mapa_x=posicao_rato_matriz_mapa_x;
            Var_memoria.posicao_rato_matriz_mapa_y=posicao_rato_matriz_mapa_y;
            Var_memoria.PROP_s=PROP_s;
            Var_memoria.RATO=RATO;
            Var_memoria.tempo_atual=tempo_atual;
            Var_memoria.tempo_inicio=tempo_inicio;
            Var_memoria.tempo_segundos=tempo_segundos;
            Var_memoria.tempo_virou_cachorro=tempo_virou_cachorro;
            Var_memoria.ultima_impressao_tempo=ultima_impressao_tempo;
            Var_memoria.vidas_iniciais=tempo_segundos;

            salvarDados(Var_memoria); //Repete até salvar em um arquivo

            return 20;
        }
        /*******************SE COLETAR TODOS OS QUEIJOS***********************/
        if(Fase[nivel_atual-1].n_queijos == 0)
        { //Nivel completo
            play_sample(vitoria_sound,230,150,1000,0);
            return 15;
        }
        /************************SE FICAR SEM VIDAS******************************/
        if(Fase[0].Rato.vida == 0)
        { //Se ficar sem vidas (so considera a primeira fase)
            play_sample(fimdejogo,200,150,1000,0);
            return 25;
        }
        /************************SE ENCONTRAR ALGUM GATO**********************/
        if((posicao_rato_matriz_mapa_x == posicao_Askel_matriz_mapa_x && posicao_rato_matriz_mapa_y == posicao_Askel_matriz_mapa_y))
        { //Se o rato estiver encima do gato Askel
            if(Fase[nivel_atual-1].Rato.forma == 0)
            { //Se estiver no modo rato
                printf("\n\tVoce perdeu uma vida!");
                Fase[0].Rato.vida--;
                play_sample(som_dano,250,150,1000,0);
                imprime_vidas_hud(vidas_iniciais);
                reseta_posicao_criaturas(true, true, true, true, true);
            }
            if(Fase[nivel_atual-1].Rato.forma == 1)
            { //Se estiver em modo cachorro
                Fase[nivel_atual-1].score_gatos += 50;
                play_sample(gato_hurt,254,150,1000,0);
                pontuacao = calcula_pontuacao(); //Calcula  a pontuacao (inicia com 10 pontos - exemplo)
                imprime_pontos_hud(pontuacao);
                reseta_posicao_criaturas(false, true, false, false, false);
            }
        }
        if((posicao_rato_matriz_mapa_x == posicao_Charlie_matriz_mapa_x && posicao_rato_matriz_mapa_y == posicao_Charlie_matriz_mapa_y))
        { //Se o rato estiver encima do gato Charlie
            if(Fase[nivel_atual-1].Rato.forma == 0)
            { //Se estiver no modo rato
                printf("\n\tVoce perdeu uma vida!");
                Fase[0].Rato.vida--;
                play_sample(som_dano,250,150,1000,0);
                imprime_vidas_hud(vidas_iniciais);
                reseta_posicao_criaturas(true, true, true, true, true);
            }
            if(Fase[nivel_atual-1].Rato.forma == 1)
            { //Se estiver em modo cachorro
                Fase[nivel_atual-1].score_gatos += 50;
                play_sample(gato_hurt,254,150,1000,0);
                pontuacao = calcula_pontuacao(); //Calcula  a pontuacao (inicia com 10 pontos - exemplo)
                imprime_pontos_hud(pontuacao);
                reseta_posicao_criaturas(false, false, true, false, false);
            }
        }
        if((posicao_rato_matriz_mapa_x == posicao_Susan_matriz_mapa_x && posicao_rato_matriz_mapa_y == posicao_Susan_matriz_mapa_y))
        { //Se o rato estiver encima do gato Susan
            if(Fase[nivel_atual-1].Rato.forma == 0)
            { //Se estiver no modo rato
                printf("\n\tVoce perdeu uma vida!");
                Fase[0].Rato.vida--;
                play_sample(som_dano,250,150,1000,0);
                imprime_vidas_hud(vidas_iniciais);
                reseta_posicao_criaturas(true, true, true, true, true);
            }
            if(Fase[nivel_atual-1].Rato.forma == 1)
            { //Se estiver em modo cachorro
                Fase[nivel_atual-1].score_gatos += 50;
                play_sample(gato_hurt,254,150,1000,0);
                pontuacao = calcula_pontuacao(); //Calcula  a pontuacao (inicia com 10 pontos - exemplo)
                imprime_pontos_hud(pontuacao);
                reseta_posicao_criaturas(false, false, false, true, false);
            }
        }
        if((posicao_rato_matriz_mapa_x == posicao_Pyro_matriz_mapa_x && posicao_rato_matriz_mapa_y == posicao_Pyro_matriz_mapa_y))
        { //Se o rato estiver encima do gato Pyro
            if(Fase[nivel_atual-1].Rato.forma == 0)
            { //Se estiver no modo rato
                printf("\n\tVoce perdeu uma vida!");
                Fase[0].Rato.vida--;
                play_sample(som_dano,250,150,1000,0);
                imprime_vidas_hud(vidas_iniciais);
                reseta_posicao_criaturas(true, true, true, true, true);
            }
            if(Fase[nivel_atual-1].Rato.forma == 1)
            { //Se estiver em modo cachorro
                Fase[nivel_atual-1].score_gatos += 50;
                play_sample(gato_hurt,254,150,1000,0);
                pontuacao = calcula_pontuacao(); //Calcula  a pontuacao (inicia com 10 pontos - exemplo)
                imprime_pontos_hud(pontuacao);
                reseta_posicao_criaturas(false, false, false, false, true);
            }
        }
        /**********************MOVIMENTOS DO GATO ASKEL**************************/
        if((((Fase[nivel_atual-1].Gato_Askel.direcao == 0) && (matriz_mapa[posicao_Askel_matriz_mapa_x][posicao_Askel_matriz_mapa_y-1] != 'X'))) && Fase[nivel_atual-1].Gato_Askel.direcao != 3 && Fase[nivel_atual-1].Gato_Askel.direcao != 1)
        { //Se mover para cima..
            if ((portas_alteradas == false && matriz_mapa[posicao_Askel_matriz_mapa_x][posicao_Askel_matriz_mapa_y-1] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Askel_matriz_mapa_x-1][posicao_Askel_matriz_mapa_y-2] != 'T'))
            {
                if(moveu_Askel == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1); //Desenha as paredes no mapa
                    if(matriz_mapa[posicao_Askel_matriz_mapa_x][posicao_Askel_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Askel_matriz_mapa_x)*23)-1, (40+(posicao_Askel_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Askel_matriz_mapa_x][posicao_Askel_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Askel_matriz_mapa_x)*23)-1, (40+(posicao_Askel_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y-=espacamento_y_spryte_criatura;
                    masked_blit(gatos, screen, G_ASKEL.wx, G_ASKEL.wy, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y-4, G_ASKEL.w, G_ASKEL.h+1);
                    moveu_Askel = true;
                }
            }
        }
        if(((Fase[nivel_atual-1].Gato_Askel.direcao == 1) && (matriz_mapa[posicao_Askel_matriz_mapa_x-1][posicao_Askel_matriz_mapa_y] != 'X')))
        { //Se mover para a esquerda..
            if ((portas_alteradas == false && matriz_mapa[posicao_Askel_matriz_mapa_x-1][posicao_Askel_matriz_mapa_y] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Askel_matriz_mapa_x-2][posicao_Askel_matriz_mapa_y-1] != 'T'))
            {
                if(moveu_Askel == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1);
                    if(matriz_mapa[posicao_Askel_matriz_mapa_x][posicao_Askel_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Askel_matriz_mapa_x)*23)-1, (40+(posicao_Askel_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Askel_matriz_mapa_x][posicao_Askel_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Askel_matriz_mapa_x)*23)-1, (40+(posicao_Askel_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x-=espacamento_x_spryte_criatura;
                    masked_blit(gatos, screen, G_ASKEL.wx, G_ASKEL.wy, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y-4, G_ASKEL.w, G_ASKEL.h+1);
                    moveu_Askel = true;
                }
            }
        }
        if((((Fase[nivel_atual-1].Gato_Askel.direcao == 2) && (matriz_mapa[posicao_Askel_matriz_mapa_x][posicao_Askel_matriz_mapa_y+1] != 'X'))) && Fase[nivel_atual-1].Gato_Askel.direcao != 3 && Fase[nivel_atual-1].Gato_Askel.direcao != 1)
        { //Se mover para baixo..
            if ((portas_alteradas == false && matriz_mapa[posicao_Askel_matriz_mapa_x][posicao_Askel_matriz_mapa_y+1] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Askel_matriz_mapa_x-1][posicao_Askel_matriz_mapa_y] != 'T'))
            {
                if(moveu_Askel == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1);
                    if(matriz_mapa[posicao_Askel_matriz_mapa_x][posicao_Askel_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Askel_matriz_mapa_x)*23)-1, (40+(posicao_Askel_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Askel_matriz_mapa_x][posicao_Askel_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Askel_matriz_mapa_x)*23)-1, (40+(posicao_Askel_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y+=espacamento_y_spryte_criatura;
                    masked_blit(gatos, screen, G_ASKEL.wx, G_ASKEL.wy, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y-4, G_ASKEL.w, G_ASKEL.h+1);
                    moveu_Askel = true;
                }
            }
        }
        if((Fase[nivel_atual-1].Gato_Askel.direcao == 3) && (matriz_mapa[posicao_Askel_matriz_mapa_x+1][posicao_Askel_matriz_mapa_y] != 'X'))
        { //Se mover para a direita..
            if ((portas_alteradas == false && matriz_mapa[posicao_Askel_matriz_mapa_x+1][posicao_Askel_matriz_mapa_y] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Askel_matriz_mapa_x][posicao_Askel_matriz_mapa_y-1] != 'T'))
            {
                if(moveu_Askel == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1);
                    if(matriz_mapa[posicao_Askel_matriz_mapa_x][posicao_Askel_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Askel_matriz_mapa_x)*23)-1, (40+(posicao_Askel_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Askel_matriz_mapa_x][posicao_Askel_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Askel_matriz_mapa_x)*23)-1, (40+(posicao_Askel_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x+=espacamento_x_spryte_criatura;
                    masked_blit(gatos, screen, G_ASKEL.wx, G_ASKEL.wy, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y-4, G_ASKEL.w, G_ASKEL.h+1);
                    moveu_Askel = true;
                }
            }
        }
        /**********************MOVIMENTOS DO GATO CHARLIE**************************/
        if((((Fase[nivel_atual-1].Gato_Charlie.direcao == 0) && (matriz_mapa[posicao_Charlie_matriz_mapa_x][posicao_Charlie_matriz_mapa_y-1] != 'X'))) && Fase[nivel_atual-1].Gato_Charlie.direcao != 3 && Fase[nivel_atual-1].Gato_Charlie.direcao != 1)
        { //Se mover para cima..
            if ((portas_alteradas == false && matriz_mapa[posicao_Charlie_matriz_mapa_x][posicao_Charlie_matriz_mapa_y-1] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Charlie_matriz_mapa_x-1][posicao_Charlie_matriz_mapa_y-2] != 'T'))
            {
                if(moveu_Charlie == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1); //Desenha as paredes no mapa
                    if(matriz_mapa[posicao_Charlie_matriz_mapa_x][posicao_Charlie_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Charlie_matriz_mapa_x)*23)-1, (40+(posicao_Charlie_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Charlie_matriz_mapa_x][posicao_Charlie_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Charlie_matriz_mapa_x)*23)-1, (40+(posicao_Charlie_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y-=espacamento_y_spryte_criatura;
                    masked_blit(gatos, screen, G_CHARLIE.wx, G_CHARLIE.wy, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y-4, G_CHARLIE.w, G_CHARLIE.h+1);
                    moveu_Charlie = true;
                }
            }
        }
        if(((Fase[nivel_atual-1].Gato_Charlie.direcao == 1) && (matriz_mapa[posicao_Charlie_matriz_mapa_x-1][posicao_Charlie_matriz_mapa_y] != 'X')))
        { //Se mover para a esquerda..
            if ((portas_alteradas == false && matriz_mapa[posicao_Charlie_matriz_mapa_x-1][posicao_Charlie_matriz_mapa_y] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Charlie_matriz_mapa_x-2][posicao_Charlie_matriz_mapa_y-1] != 'T'))
            {
                if(moveu_Charlie == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1);
                    if(matriz_mapa[posicao_Charlie_matriz_mapa_x][posicao_Charlie_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Charlie_matriz_mapa_x)*23)-1, (40+(posicao_Charlie_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Charlie_matriz_mapa_x][posicao_Charlie_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Charlie_matriz_mapa_x)*23)-1, (40+(posicao_Charlie_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x-=espacamento_x_spryte_criatura;
                    masked_blit(gatos, screen, G_CHARLIE.wx, G_CHARLIE.wy, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y-4, G_CHARLIE.w, G_CHARLIE.h+1);
                    moveu_Charlie = true;
                }
            }
        }
        if((((Fase[nivel_atual-1].Gato_Charlie.direcao == 2) && (matriz_mapa[posicao_Charlie_matriz_mapa_x][posicao_Charlie_matriz_mapa_y+1] != 'X'))) && Fase[nivel_atual-1].Gato_Charlie.direcao != 3 && Fase[nivel_atual-1].Gato_Charlie.direcao != 1)
        { //Se mover para baixo..
            if ((portas_alteradas == false && matriz_mapa[posicao_Charlie_matriz_mapa_x][posicao_Charlie_matriz_mapa_y+1] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Charlie_matriz_mapa_x-1][posicao_Charlie_matriz_mapa_y] != 'T'))
            {
                if(moveu_Charlie == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1);
                    if(matriz_mapa[posicao_Charlie_matriz_mapa_x][posicao_Charlie_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Charlie_matriz_mapa_x)*23)-1, (40+(posicao_Charlie_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Charlie_matriz_mapa_x][posicao_Charlie_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Charlie_matriz_mapa_x)*23)-1, (40+(posicao_Charlie_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y+=espacamento_y_spryte_criatura;
                    masked_blit(gatos, screen, G_CHARLIE.wx, G_CHARLIE.wy, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y-4, G_CHARLIE.w, G_CHARLIE.h+1);
                    moveu_Charlie = true;
                }
            }
        }
        if((Fase[nivel_atual-1].Gato_Charlie.direcao == 3) && (matriz_mapa[posicao_Charlie_matriz_mapa_x+1][posicao_Charlie_matriz_mapa_y] != 'X'))
        { //Se mover para a direita..
            if ((portas_alteradas == false && matriz_mapa[posicao_Charlie_matriz_mapa_x+1][posicao_Charlie_matriz_mapa_y] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Charlie_matriz_mapa_x][posicao_Charlie_matriz_mapa_y-1] != 'T'))
            {
                if(moveu_Charlie == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1);
                    if(matriz_mapa[posicao_Charlie_matriz_mapa_x][posicao_Charlie_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Charlie_matriz_mapa_x)*23)-1, (40+(posicao_Charlie_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Charlie_matriz_mapa_x][posicao_Charlie_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Charlie_matriz_mapa_x)*23)-1, (40+(posicao_Charlie_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x+=espacamento_x_spryte_criatura;
                    masked_blit(gatos, screen, G_CHARLIE.wx, G_CHARLIE.wy, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y-4, G_CHARLIE.w, G_CHARLIE.h+1);
                    moveu_Charlie = true;
                }
            }
        }
        /**********************MOVIMENTOS DO GATO SUSAN**************************/
        if((((Fase[nivel_atual-1].Gato_Susan.direcao == 0) && (matriz_mapa[posicao_Susan_matriz_mapa_x][posicao_Susan_matriz_mapa_y-1] != 'X'))) && Fase[nivel_atual-1].Gato_Susan.direcao != 3 && Fase[nivel_atual-1].Gato_Susan.direcao != 1)
        { //Se mover para cima..
            if ((portas_alteradas == false && matriz_mapa[posicao_Susan_matriz_mapa_x][posicao_Susan_matriz_mapa_y-1] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Susan_matriz_mapa_x-1][posicao_Susan_matriz_mapa_y-2] != 'T'))
            {
                if(moveu_Susan == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1); //Desenha as paredes no mapa
                    if(matriz_mapa[posicao_Susan_matriz_mapa_x][posicao_Susan_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Susan_matriz_mapa_x)*23)-1, (40+(posicao_Susan_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Susan_matriz_mapa_x][posicao_Susan_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Susan_matriz_mapa_x)*23)-1, (40+(posicao_Susan_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y-=espacamento_y_spryte_criatura;
                    masked_blit(gatos, screen, G_SUSAN.wx, G_SUSAN.wy+2, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y-4, G_SUSAN.w, G_SUSAN.h);
                    moveu_Susan = true;
                }
            }
        }
        if(((Fase[nivel_atual-1].Gato_Susan.direcao == 1) && (matriz_mapa[posicao_Susan_matriz_mapa_x-1][posicao_Susan_matriz_mapa_y] != 'X')))
        { //Se mover para a esquerda..
            if ((portas_alteradas == false && matriz_mapa[posicao_Susan_matriz_mapa_x-1][posicao_Susan_matriz_mapa_y] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Susan_matriz_mapa_x-2][posicao_Susan_matriz_mapa_y-1] != 'T'))
            {
                if(moveu_Susan == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1);
                    if(matriz_mapa[posicao_Susan_matriz_mapa_x][posicao_Susan_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Susan_matriz_mapa_x)*23)-1, (40+(posicao_Susan_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Susan_matriz_mapa_x][posicao_Susan_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Susan_matriz_mapa_x)*23)-1, (40+(posicao_Susan_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x-=espacamento_x_spryte_criatura;
                    masked_blit(gatos, screen, G_SUSAN.wx, G_SUSAN.wy+2, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y-4, G_SUSAN.w, G_SUSAN.h);
                    moveu_Susan = true;
                }
            }
        }
        if((((Fase[nivel_atual-1].Gato_Susan.direcao == 2) && (matriz_mapa[posicao_Susan_matriz_mapa_x][posicao_Susan_matriz_mapa_y+1] != 'X'))) && Fase[nivel_atual-1].Gato_Susan.direcao != 3 && Fase[nivel_atual-1].Gato_Susan.direcao != 1)
        { //Se mover para baixo..
            if ((portas_alteradas == false && matriz_mapa[posicao_Susan_matriz_mapa_x][posicao_Susan_matriz_mapa_y+1] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Susan_matriz_mapa_x-1][posicao_Susan_matriz_mapa_y] != 'T'))
            {
                if(moveu_Susan == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1);
                    if(matriz_mapa[posicao_Susan_matriz_mapa_x][posicao_Susan_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Susan_matriz_mapa_x)*23)-1, (40+(posicao_Susan_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Susan_matriz_mapa_x][posicao_Susan_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Susan_matriz_mapa_x)*23)-1, (40+(posicao_Susan_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y+=espacamento_y_spryte_criatura;
                    masked_blit(gatos, screen, G_SUSAN.wx, G_SUSAN.wy+2, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y-4, G_SUSAN.w, G_SUSAN.h);
                    moveu_Susan = true;
                }
            }
        }
        if((Fase[nivel_atual-1].Gato_Susan.direcao == 3) && (matriz_mapa[posicao_Susan_matriz_mapa_x+1][posicao_Susan_matriz_mapa_y] != 'X'))
        { //Se mover para a direita..
            if ((portas_alteradas == false && matriz_mapa[posicao_Susan_matriz_mapa_x+1][posicao_Susan_matriz_mapa_y] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Susan_matriz_mapa_x][posicao_Susan_matriz_mapa_y-1] != 'T'))
            {
                if(moveu_Susan == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1);
                    if(matriz_mapa[posicao_Susan_matriz_mapa_x][posicao_Susan_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Susan_matriz_mapa_x)*23)-1, (40+(posicao_Susan_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Susan_matriz_mapa_x][posicao_Susan_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Susan_matriz_mapa_x)*23)-1, (40+(posicao_Susan_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x+=espacamento_x_spryte_criatura;
                    masked_blit(gatos, screen, G_SUSAN.wx, G_SUSAN.wy+2, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y-4, G_SUSAN.w, G_SUSAN.h);
                    moveu_Susan = true;
                }
            }
        }
        /**********************MOVIMENTOS DO GATO PYRO**************************/
        if((((Fase[nivel_atual-1].Gato_Pyro.direcao == 0) && (matriz_mapa[posicao_Pyro_matriz_mapa_x][posicao_Pyro_matriz_mapa_y-1] != 'X'))) && Fase[nivel_atual-1].Gato_Pyro.direcao != 3 && Fase[nivel_atual-1].Gato_Pyro.direcao != 1)
        { //Se mover para cima..
            if ((portas_alteradas == false && matriz_mapa[posicao_Pyro_matriz_mapa_x][posicao_Pyro_matriz_mapa_y-1] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Pyro_matriz_mapa_x-1][posicao_Pyro_matriz_mapa_y-2] != 'T'))
            {
                if(moveu_Pyro == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1); //Desenha as paredes no mapa
                    if(matriz_mapa[posicao_Pyro_matriz_mapa_x][posicao_Pyro_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Pyro_matriz_mapa_x)*23)-1, (40+(posicao_Pyro_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Pyro_matriz_mapa_x][posicao_Pyro_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Pyro_matriz_mapa_x)*23)-1, (40+(posicao_Pyro_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y-=espacamento_y_spryte_criatura;
                    masked_blit(gatos, screen, G_PYRO.wx, G_PYRO.wy+4, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y-4, G_PYRO.w, G_PYRO.h+1);
                    moveu_Pyro = true;
                }
            }
        }
        if(((Fase[nivel_atual-1].Gato_Pyro.direcao == 1) && (matriz_mapa[posicao_Pyro_matriz_mapa_x-1][posicao_Pyro_matriz_mapa_y] != 'X')))
        { //Se mover para a esquerda..
            if ((portas_alteradas == false && matriz_mapa[posicao_Pyro_matriz_mapa_x-1][posicao_Pyro_matriz_mapa_y] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Pyro_matriz_mapa_x-2][posicao_Pyro_matriz_mapa_y-1] != 'T'))
            {
                if(moveu_Pyro == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1);
                    if(matriz_mapa[posicao_Pyro_matriz_mapa_x][posicao_Pyro_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Pyro_matriz_mapa_x)*23)-1, (40+(posicao_Pyro_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Pyro_matriz_mapa_x][posicao_Pyro_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Pyro_matriz_mapa_x)*23)-1, (40+(posicao_Pyro_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x-=espacamento_x_spryte_criatura;
                    masked_blit(gatos, screen, G_PYRO.wx, G_PYRO.wy+4, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y-4, G_PYRO.w, G_PYRO.h+1);
                    moveu_Pyro = true;
                }
            }
        }
        if((((Fase[nivel_atual-1].Gato_Pyro.direcao == 2) && (matriz_mapa[posicao_Pyro_matriz_mapa_x][posicao_Pyro_matriz_mapa_y+1] != 'X'))) && Fase[nivel_atual-1].Gato_Pyro.direcao != 3 && Fase[nivel_atual-1].Gato_Pyro.direcao != 1)
        { //Se mover para baixo..
            if ((portas_alteradas == false && matriz_mapa[posicao_Pyro_matriz_mapa_x][posicao_Pyro_matriz_mapa_y+1] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Pyro_matriz_mapa_x-1][posicao_Pyro_matriz_mapa_y] != 'T'))
            {
                if(moveu_Pyro == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1);
                    if(matriz_mapa[posicao_Pyro_matriz_mapa_x][posicao_Pyro_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Pyro_matriz_mapa_x)*23)-1, (40+(posicao_Pyro_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Pyro_matriz_mapa_x][posicao_Pyro_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Pyro_matriz_mapa_x)*23)-1, (40+(posicao_Pyro_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y+=espacamento_y_spryte_criatura;
                    masked_blit(gatos, screen, G_PYRO.wx, G_PYRO.wy+4, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y-4, G_PYRO.w, G_PYRO.h+1);
                    moveu_Pyro = true;
                }
            }
        }
        if((Fase[nivel_atual-1].Gato_Pyro.direcao == 3) && (matriz_mapa[posicao_Pyro_matriz_mapa_x+1][posicao_Pyro_matriz_mapa_y] != 'X'))
        { //Se mover para a direita..
            if ((portas_alteradas == false && matriz_mapa[posicao_Pyro_matriz_mapa_x+1][posicao_Pyro_matriz_mapa_y] != 'T') || (portas_alteradas == true && matriz_mapa[posicao_Pyro_matriz_mapa_x][posicao_Pyro_matriz_mapa_y-1] != 'T'))
            {
                if(moveu_Pyro == false)
                {
                    masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1);
                    if(matriz_mapa[posicao_Pyro_matriz_mapa_x][posicao_Pyro_matriz_mapa_y] == 'Q')
                    { //Se o gato pisar encima de um queijo
                        masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(posicao_Pyro_matriz_mapa_x)*23)-1, (40+(posicao_Pyro_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um queijo de volta no lugar
                    }
                    if(matriz_mapa[posicao_Pyro_matriz_mapa_x][posicao_Pyro_matriz_mapa_y] == 'O')
                    { //Se o gato pisar encima de um osso
                        masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(posicao_Pyro_matriz_mapa_x)*23)-1, (40+(posicao_Pyro_matriz_mapa_y)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha um osso de volta no lugar
                    }
                    Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x+=espacamento_x_spryte_criatura;
                    masked_blit(gatos, screen, G_PYRO.wx, G_PYRO.wy+4, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y-4, G_PYRO.w, G_PYRO.h+1);
                    moveu_Pyro = true;
                }
            }
        }
        /**********************OUTRAS MECANICAS*********************************/
        if(tempo_segundos-tempo_virou_cachorro > 4)
        { //Se passar 5 segundos em modo cachorro...
            Fase[nivel_atual-1].Rato.forma = 0; // Transforma num rato novamente
            if(desatualizou_cachorro==true)
            {
                masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1);
                desatualizou_cachorro = false;
            }
        }
        if(Fase[nivel_atual-1].Rato.forma == 1)
        { //Se estive em modo cachorro
            RATO.wx = 0*espacamento_x_spryte_criatura; RATO.wy = 2*espacamento_y_spryte_criatura+4;
        }
        if(Fase[nivel_atual-1].Rato.forma == 0)
        { //Se estiver em modo rato
            RATO.wx = 0*espacamento_x_spryte_criatura; RATO.wy = 0*espacamento_y_spryte_criatura;
        }
        /***************************O DELAY DO JOGO****************************/
        rest(100);
    }

    destroy_bitmap(HUD);
    destroy_bitmap(gatos);
    destroy_bitmap(PROPS);
    destroy_bitmap(ratto);

    return cod_erro;
}
void imprime_vidas_hud(int vidas_iniciais)
{
    for(int aux3=0; aux3<vidas_iniciais; aux3++)
    {
        draw_sprite(screen, select_menu_principal_rectangle, (105+(espacamento_x_spryte_prop+2)*aux3), 1);
    }
    for(int aux=0; aux<3; aux++)
    {
        masked_blit(PROPS, screen, 49, PROP_s.wy, (105+(espacamento_x_spryte_prop+2)*aux), PROP_s.y+1, PROP_s.w+1, PROP_s.h); //Desenha o coracao vazio
    }
    for(int aux2=0; aux2<Fase[0].Rato.vida; aux2++)
    {
        masked_blit(PROPS, screen, 25, PROP_s.wy, (105+(espacamento_x_spryte_prop+2)*aux2), PROP_s.y+1, PROP_s.w+1, PROP_s.h); //Desenha o coracao cheio
    }
}
void imprime_pontos_hud(int pontos)
{
    char pontuacao[9];
    sprintf(pontuacao, "%7d", pontos);
    draw_sprite(screen, atualiza_pontos, 562,-2);
    textout_ex(screen, m_font, "PONTUACAO:     ", 435, -3, 0x0AB944, -1); //431x
    textout_ex(screen, m_font, pontuacao, 565, -4, 0x0AB944, -1); //565x
    masked_blit(PROPS, screen, 97, PROP_s.wy, 646, PROP_s.y, PROP_s.w+1, PROP_s.h); //Desenha a estrela na tela
    textout_ex(screen, m_font, "NIVEL:     ", 435, RESOLUCAO_Y-30, 0x0AB944, -1); //431x
    char nivel_atual_char[2];
    sprintf(nivel_atual_char, "%d", nivel_atual);
    textout_ex(screen, m_font, nivel_atual_char, 508, RESOLUCAO_Y-30, 0x0AB944, -1); //431x
}
void imprime_mapa_tela(BITMAP *paredes_mapa, int caller, bool portas_alteradas)
{
    int gato_counter =0;

    for(int linha=0; linha<11; linha++)
    {
        for(int coluna=0; coluna<27; coluna++)
        {
            if(matriz_mapa[coluna][linha]=='X')
            {
                masked_blit(paredes_mapa, screen, 0, PAREDE.wy, (39+(coluna)*23)-1, (35+(linha)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha as paredes no mapa
            }
            if(matriz_mapa[coluna][linha]=='T' && portas_alteradas == false)
            {
                masked_blit(paredes_mapa, screen, 73, PAREDE.wy, (39+(coluna)*23), (35+(linha)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha as portas no mapa
            }
            if(matriz_mapa[coluna][linha]=='T' && portas_alteradas == true)
            {
                masked_blit(paredes_mapa, screen, 73, PAREDE.wy, (39+(coluna+1)*23), (35+(linha+1)*30)-1, PAREDE.w+1, PAREDE.h+1); //Re-Desenha as portas uma coluna e uma linha para baixo
            }
            if(matriz_mapa[coluna][linha]=='Q')
            {
                if(caller!=0)
                {
                    Fase[nivel_atual-1].n_queijos++;
                }
                if(portas_alteradas==false)
                {
                    masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(coluna)*23)-1, (40+(linha)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha os queijos
                }
                if(portas_alteradas==true)
                {
                    if(matriz_mapa[coluna-1][linha-1]!='T')
                    {
                    masked_blit(PROPS, screen, 73, PAREDE.wy, (39+(coluna)*23)-1, (40+(linha)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha os queijos
                    }
                }

            }
            if(matriz_mapa[coluna][linha]=='O')
            {
                masked_blit(PROPS, screen, 0, PAREDE.wy, (39+(coluna)*23)-1, (40+(linha)*30)-1, PAREDE.w+1, PAREDE.h+1); //Desenha os ossos
            }
            if(matriz_mapa[coluna][linha]=='M' && caller != 0)
            { //Quando a posicao do rato for encontrada
                Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x = ((39+(coluna)*23)-1);
                Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y = ((40+(linha)*30)-1);
                Fase[nivel_atual-1].Rato.CRIATURA_pos.inicial_x = Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x;
                Fase[nivel_atual-1].Rato.CRIATURA_pos.inicial_y = Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y;
                printf("\n\n\tA posicao inicial do rato (x, y) eh: (%d, %d)",Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y);
            }
            if(matriz_mapa[coluna][linha]=='G' && caller != 0)
            { //Quando a posicao do rato for encontrada
                if(gato_counter == 0)
                { //Posicao inicial do gato ASKEL
                    Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x = ((39+(coluna)*23)-1);
                    Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y = ((40+(linha)*30)-1);
                    Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.inicial_x = Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x;
                    Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.inicial_y = Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y;
                    printf("\n\n\tA posicao inicial do gato Askel (x, y) eh: (%d, %d)",Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y);
                }
                if(gato_counter == 1)
                { //Posicao inicial do gato ASKEL
                    Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x = ((39+(coluna)*23)-1);
                    Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y = ((40+(linha)*30)-1);
                    Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.inicial_x = Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x;
                    Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.inicial_y = Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y;
                    printf("\n\tA posicao inicial do gato Charlie (x, y) eh: (%d, %d)",Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y);
                }
                if(gato_counter == 2)
                { //Posicao inicial do gato ASKEL
                    Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x = ((39+(coluna)*23)-1);
                    Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y = ((40+(linha)*30)-1);
                    Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.inicial_x = Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x;
                    Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.inicial_y = Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y;
                    printf("\n\tA posicao inicial do gato Susan (x, y) eh: (%d, %d)",Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y);
                }
                if(gato_counter == 3)
                { //Posicao inicial do gato ASKEL
                    Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x = ((39+(coluna)*23)-1);
                    Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y = ((40+(linha)*30)-1);
                    Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.inicial_x = Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x;
                    Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.inicial_y = Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y;
                    printf("\n\tA posicao inicial do gato Pyro (x, y) eh: (%d, %d)\n",Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y);
                }
                gato_counter++;
            }
        }
    }
}
void coleta_queijo(int posicao_rato_matriz_mapa_x, int posicao_rato_matriz_mapa_y)
{
    Fase[nivel_atual-1].n_queijos -= 1; //Decrementa um queijo dos necessarios para vencer
    Fase[nivel_atual-1].score_queijo += 10;
    matriz_mapa[posicao_rato_matriz_mapa_x][posicao_rato_matriz_mapa_y] = 'z'; //O 'Z' indica um queijo coletado
}
int calcula_pontuacao()
{
    int pontuacao = Fase[nivel_atual-1].score_queijo + Fase[nivel_atual-1].score_gatos;
    return pontuacao;
}
void coleta_osso(int posicao_rato_matriz_mapa_x, int posicao_rato_matriz_mapa_y)
{
    Fase[nivel_atual-1].score_ossos += 1;
    matriz_mapa[posicao_rato_matriz_mapa_x][posicao_rato_matriz_mapa_y] = 'k'; //O 'k' indica um osso coletado
}
void reseta_posicao_criaturas(bool reseta_rato, bool reseta_Askel, bool reseta_Charlie, bool reseta_Susan, bool reseta_Pyro)
{
    if(reseta_rato == true)
    {
        /*RESETA A POSICAO DO RATO*/
        masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1); //Desenha um retangulo cinza no lugar onde estava o rato
        Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_x = Fase[nivel_atual-1].Rato.CRIATURA_pos.inicial_x;
        Fase[nivel_atual-1].Rato.CRIATURA_pos.posicao_y = Fase[nivel_atual-1].Rato.CRIATURA_pos.inicial_y;
    }
    if(reseta_Askel==true)
    {
        /*RESETA A POSICAO DO GATO ASKEL*/
        masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1); //Desenha um retangulo cinza no lugar onde estava o gato
        Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_x = Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.inicial_x;
        Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.posicao_y = Fase[nivel_atual-1].Gato_Askel.CRIATURA_pos.inicial_y;
    }
    if(reseta_Charlie==true)
    {
        /*RESETA A POSICAO DO GATO CHARLIE*/
        masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1); //Desenha um retangulo cinza no lugar onde estava o gato
        Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_x = Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.inicial_x;
        Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.posicao_y = Fase[nivel_atual-1].Gato_Charlie.CRIATURA_pos.inicial_y;
    }
    if(reseta_Susan==true)
    {
         /*RESETA A POSICAO DO GATO SUSAN*/
        masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1); //Desenha um retangulo cinza no lugar onde estava o gato
        Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_x = Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.inicial_x;
        Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.posicao_y = Fase[nivel_atual-1].Gato_Susan.CRIATURA_pos.inicial_y;
    }
    if(reseta_Pyro==true)
    {
        /*RESETA A POSICAO DO GATO PYRO*/
        masked_blit(paredes_mapa, screen, 97, PAREDE.wy, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x+1, Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y-5, PAREDE.w, PAREDE.h+1); //Desenha um retangulo cinza no lugar onde estava o gato
        Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_x = Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.inicial_x;
        Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.posicao_y = Fase[nivel_atual-1].Gato_Pyro.CRIATURA_pos.inicial_y;
    }
}
int gera_numero_aleatorio()
{
    int numero_aleatorio = rand()%4;
    return numero_aleatorio;
}
void imprime_tempo_hud()
{
    char tempo_seg[9];
    sprintf(tempo_seg, "%7d", tempo_segundos);
    textout_ex(screen, m_font, "TEMPO: ", 220, -4, 0x0AB944, -1);
    draw_sprite(screen, atualiza_pontos, 292,-2);
    textout_ex(screen, m_font, tempo_seg, 293, -4, 0x0AB944, -1); //565x
}
void zera_variaveis_nivel()
{
    nivel_atual = 1; //Vai para o nivel 1
    Fase[nivel_atual-1].score_ossos = 0; //Inicia o numero de ossos como 3
    Fase[nivel_atual-1].score_queijo = 0;
    Fase[nivel_atual-1].score_gatos = 0;
    Fase[nivel_atual-1].tempo_corrente = 0;
    Fase[nivel_atual-1].n_queijos = 0;
    Fase[0].Rato.vida = 3; //Inicia o numero de vidas do rato como 3
}
bool salvarDados(VARIAVEIS memoria)
{

    FILE *arquivo;
    arquivo = fopen("saves/jogoSalvo.bin", "wb");

    if(!arquivo)
    {
        return false;
    }

    fwrite(&memoria, sizeof(memoria), 1, arquivo);

    fclose(arquivo);

    return true;
}
VARIAVEIS le_memoria()
{
    VARIAVEIS memoria;

    FILE *arquivo;

    printf("\nExecutou aqui, vai tentar abrir o arquivo %d\n");

    arquivo = fopen("saves/jogoSalvo.bin", "rb");

    if(!arquivo)
    {
        printf("\nErro ao ler jogo salvo!!!\n");
        memoria.retorno = 404;
    }

    fread(&memoria, sizeof(memoria), 1, arquivo);

    printf("\nLeu a memoria\n");

    fclose(arquivo);

    return memoria;
}

