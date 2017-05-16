/******************************************************************************************
 * Universidade de Brasília – UnB
 * Instituto de Ciências Exatas – IE
 * Departamento de Ciência da Computação – CIC
 * Modelagem de Sistemas em Silicio – Professor Ricardo Jacobi
 *
 * Projeto - Objetivo
 * Modelar o processador RISC16.
 *
 * Requisito 1:
 * Modelar os processos fundamentais fetch – decode – execute na forma de SC_THREADS
 * sincronizadas por eventos. Utilizar como referência o código C do RISC16 enviado em
 * anexo no mural da disciplina.
 * Incluir uma thread auxiliar start para sincronização das demais threads, de forma que a
 * primeira thread a entrar em execução seja a fetch, que busca uma instrução na memória.
 * Depois de escrever a instrução lida da memória em RI e incrementar o PC, a fetch notifica a
 * thread decode. Esta extrai os campos da instrução e sinaliza a thread execute para que
 * processe a instrução.
 *
 *
 *
 *
 * Nome: Jessé Barreto de Barros
 * Matrícula: 17/0067033
 ******************************************************************************************
*/

#include <systemc.h>

#include "sistema1.h"

int sc_main(int argc, char** argv)
{
    SystemReq1 requisito1("SysRequisito1");

    sc_start();

    return 0;
}

