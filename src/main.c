#ifndef ANIM_INTRO_H
#define ANIM_INTRO_H

#include <genesis.h>
#include "movie_res.h"
#include "sound.h"

// Declaração das variáveis globais que estão no main.c
extern u8 room;    // Variável para controlar o estado do jogo ou fase atual
extern u32 frames; // Contador de quadros
u16 palette_full[64];

// Declaração da função CLEAR_VDP que está definida no main.c
extern void CLEAR_VDP(void); // A função CLEAR_VDP deve estar em main.c

// Número de quadros
#define NUMBER_OF_INTRO_FRAMES 89

// Declaração das imagens para os quadros pares e ímpares
const Image* introPar[] = {
    &frame2, &frame4, &frame6, &frame8, &frame10, &frame12, &frame14, &frame16,
    &frame18, &frame20, &frame22, &frame24, &frame26, &frame28, &frame30, &frame32,
    &frame34, &frame36, &frame38, &frame40, &frame42, &frame44, &frame46, &frame48,
    &frame50, &frame52, &frame54, &frame56, &frame58, &frame60, &frame62, &frame64,
    &frame66, &frame68, &frame70, &frame72, &frame74, &frame76, &frame78, &frame80,
    &frame82, &frame84, &frame86, &frame88, &frame90, &frame92, &frame94, &frame96,
    &frame98, &frame100, &frame102, &frame104, &frame106, &frame108, &frame110, &frame112,
    &frame114, &frame116, &frame118, &frame120, &frame122, &frame124, &frame126, &frame128,
    &frame130, &frame132, &frame134, &frame136, &frame138, &frame140, &frame142, &frame144,
    &frame146, &frame148, &frame150, &frame152, &frame154, &frame156, &frame158, &frame160,
    &frame162, &frame164, &frame166, &frame168, &frame170, &frame172, &frame174, &frame176,
    &frame178
};

const Image* introImpar[] = {
    &frame1, &frame3, &frame5, &frame7, &frame9, &frame11, &frame13, &frame15,
    &frame17, &frame19, &frame21, &frame23, &frame25, &frame27, &frame29, &frame31,
    &frame33, &frame35, &frame37, &frame39, &frame41, &frame43, &frame45, &frame47,
    &frame49, &frame51, &frame53, &frame55, &frame57, &frame59, &frame61, &frame63,
    &frame65, &frame67, &frame69, &frame71, &frame73, &frame75, &frame77, &frame79,
    &frame81, &frame83, &frame85, &frame87, &frame89, &frame91, &frame93, &frame95,
    &frame97, &frame99, &frame101, &frame103, &frame105, &frame107, &frame109, &frame111,
    &frame113, &frame115, &frame117, &frame119, &frame121, &frame123, &frame125, &frame127,
    &frame129, &frame131, &frame133, &frame135, &frame137, &frame139, &frame141, &frame143,
    &frame145, &frame147, &frame149, &frame151, &frame153, &frame155, &frame157, &frame159,
    &frame161, &frame163, &frame165, &frame167, &frame169, &frame171, &frame173, &frame175,
    &frame177
};



// Função para animar o filme
static void AnimateMovie()
{
    u16 index = 0;  // Inicialização do índice de quadros

    while (index < NUMBER_OF_INTRO_FRAMES)
    {
        // Verifica se o botão Start foi pressionado para interromper a animação
        if (JOY_readJoypad(JOY_1) & BUTTON_START)
        {
            CLEAR_VDP();  // Limpa a tela
            room = 8;     // Muda para o título ou próxima fase
            frames = 0;   // Reinicia o contador de quadros
            break;        // Interrompe a animação
        }

        // Carrega e desenha a imagem ímpar no plano A
        PAL_setPalette(PAL0, introImpar[index]->palette->data, CPU);  // Define a paleta
        VDP_drawImageEx(BG_A, introImpar[index], TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, 408), 7, 5, FALSE, CPU); // Desenha no plano A

        // Limpa o plano B
        VDP_clearPlane(BG_B, TRUE);

        // Atraso antes de desenhar o próximo quadro
        waitMs(100);

        // Carrega e desenha a imagem par no plano B
        PAL_setPalette(PAL0, introPar[index]->palette->data, CPU);  // Define a paleta
        VDP_drawImageEx(BG_B, introPar[index], TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, 1), 7, 5, FALSE, CPU); // Desenha no plano B

        // Limpa o plano A
        VDP_clearPlane(BG_A, TRUE);

        // Atraso antes de avançar para o próximo quadro
       waitMs(100);

        // Avança o índice para o próximo quadro
        index++;

        // Se o índice atingir o limite, reinicia a animação
        if (index >= NUMBER_OF_INTRO_FRAMES)
        {
            memcpy(&palette_full[16], plane_pal.data, 16 * 2); // Copia a paleta
            PAL_fadeOut(0, 31, 30, FALSE); // Inicia a transição de desvanecimento
            break;
        }
    }
}

#endif // ANIM_INTRO_H
