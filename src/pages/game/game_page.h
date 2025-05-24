/**
 * @file game_page.h
 * @brief Funções para mostrar e rodar a tela principal do jogo Lletris.
 */

#ifndef GAME_PAGE_H
#define GAME_PAGE_H

/**
 * @brief Função que roda o jogo.
 * @pre O allegro deve estar inicializado e a tela precisa estar visivel.
 * @post O jogo é rodado e a tela é atualizada a cada n quadros.
 */
void run_game();

#endif