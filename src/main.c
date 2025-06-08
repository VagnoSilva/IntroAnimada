
#include <genesis.h>
#include "movie_res.h"
#include "sound_res.h"
#define NUMBER_OF_INTRO_FRAMES 89
// Definições reais (uma vez só)
u32 frames = 0;
u16 palette_full[64];
u16 index;

// Arrays de ponteiros para os frames pares e ímpares
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

// Função de animação
void AnimateMovie()
{


    while (index < NUMBER_OF_INTRO_FRAMES)
    {
        if (index == 0)
        {
            //SND_PCM_startPlay(snd_intro, sizeof(snd_intro), SOUND_PCM_RATE_22050, 3, 0);
            SND_DPCM2_startPlay(snd_intro, sizeof(snd_intro), SOUND_PCM_CH1, 0);

        }
        PAL_setPalette(PAL0, introImpar[index]->palette->data, CPU);
        VDP_drawImageEx(BG_A, introImpar[index],
                        TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, 408),
                        7, 5, FALSE, CPU);
        VDP_clearPlane(BG_B, TRUE);

        for (u8 i = 0; i < 6; i++) SYS_doVBlankProcess();

        PAL_setPalette(PAL0, introPar[index]->palette->data, CPU);
        VDP_drawImageEx(BG_B, introPar[index],
                        TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, 1),
                        7, 5, FALSE, CPU);
        VDP_clearPlane(BG_A, TRUE);

        for (u8 i = 0; i < 6; i++) SYS_doVBlankProcess();

        index++;
    }

    memcpy(&palette_full[16], intro_pal.data, 16 * 2);
    PAL_fadeOut(0, 31, 30, FALSE);
}




// Função principal do jogo, ode as demais funções são carregadas
int main(bool hardReset){
    //inicializacao da VDP (Video Display Processor)
	SYS_disableInts();
	 VDP_init();

	 VDP_setPlaneSize(64, 64, TRUE);
	 VDP_setScreenWidth320();
	 VDP_setScreenHeight224();
	 VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	SYS_enableInts();


	//inicializacao de sprites
	VDP_setBackgroundColor(0); //Range 0-63 //4 Paletas de 16 cores = 64 cores

    index = 0;
while (TRUE) // MAIN LOOP
{



            AnimateMovie();  // Animação da introdução



}

    return 0;
}


//EOF; End of File
