/*
 * decod.cpp
 *
 *  Created on: 09/07/2015
 *   *  Modified by José Adalberto F. Gualeve on 30/04/16
 *      Author: soudre
 */

#include "decod.h"

//Thread para leitura do flit

void Decod::lerDecod() {
    for (;;) {
        eh_decod = false;
        dado_decod = i_decod->read();
        eh_decod = true;
        dado_decod_evt.notify(SC_ZERO_TIME);
        wait(main_ack2_evt);
    }
}

//Thread principal

void Decod::main() {

    sc_uint<32> dado_m;
    
    for (;;) {
            //Evento de ocorrencia do flit
        wait (dado_decod_evt);
        if (eh_decod){
            dado_m = dado_decod.range(52,21);
                //Saida de Debug
            cout << "#####################################################\n";
            o_decod->write(dado_m);
                //Saida de Debug
                //cout << "dado_entregue " << dado_m << "\n";
        }
        main_ack2_evt.notify(SC_ZERO_TIME);
    }
}
