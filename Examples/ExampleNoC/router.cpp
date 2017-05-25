/*
 *  router.cpp
 *  NoC router
 *
 *  Created by Ricardo Jacobi on 27/5/15.
 *  Copyright 2015 Universidade de Brasilia. All rights reserved.
 *
 */

#include "router.h"

//Thread para leitura da entrada oeste do modulo de roteamento

void Router::lerOeste() {
    for (;;) {
        eh_oeste = false;
        dado_oeste = i_oeste->read();
        eh_oeste = true;
        dado_oeste_evt.notify(SC_ZERO_TIME); 
        wait(main_ack_evt);
    }
}

//Thread para leitura da entrada sul do modulo de roteamento

void Router::lerSul() {
    for (;;) {
        eh_sul = false;
        dado_sul = i_sul->read();
        eh_sul = true;
        dado_sul_evt.notify(SC_ZERO_TIME);
        wait(main_ack_evt);
    }
}

//Thread para leitura da entrada leste do modulo de roteamento

void Router::lerLeste() {
    for (;;) {
        eh_leste = false;
        dado_leste = i_leste->read();
        eh_leste = true;
        dado_leste_evt.notify(SC_ZERO_TIME);
        wait(main_ack_evt);
    }
}

//Thread para leitura da entrada norte do modulo de roteamento

void Router::lerNorte() {
    for (;;) {
        eh_norte = false;
        dado_norte = i_norte->read();
        eh_norte = true;
        dado_norte_evt.notify(SC_ZERO_TIME); 
        wait(main_ack_evt);
    }
}

//Thread principal

void Router::main() {
    sc_uint<53> tmp;
    for (;;) {
            //Aguarda a ocorrencia de um evento em uma das entradas do modulo de roteamento
        wait (dado_norte_evt | dado_oeste_evt | dado_sul_evt | dado_leste_evt);
            //Se o evento ocorreu na entrada norte do modulo de roteamento
        if (eh_norte){
                //tmp recebe o flit
            tmp = dado_norte;
        }
        if (eh_oeste){
            tmp = dado_oeste;
        }
        if (eh_sul){
            tmp = dado_sul;
        }
        if (eh_leste){
            tmp = dado_leste;
        }
            //Notifica o evento principal, bloqueando a presente thread
        main_ack_evt.notify(SC_ZERO_TIME);
            // x <-- coordenada x a ser decrementada
        x = tmp.range(15, 8);
            // y <-- coordenada y a ser decrementada
        y = tmp.range(7, 0);
            // ent <-- Entrado do roteador pela qual o flit entrou
        ent = tmp.range(18, 16);
            // saida <-- Bit de controle indicando o sentido do roteamento
        saida = tmp.range(20,20);
            //Bit de controle da saida do flit
        said = tmp.range(19, 19);
            //Algoritmo de roteamento x,y por decremento
            //Se o flit entrou pelo elemento de roteamento 0
        if(ent == 0){
		//Se o x for maior que zero decrementa e escreve na saida sul do elemento de roteamento
            if (x > 0) {
                x = x - 1;
                    //Saida de debug
                cout <<"["<< this->name() << "]: (Saida de Debug) x ---> " << tmp.range(15, 8) << "\n";
                tmp.range(15, 8) = x;
                o_sul->write(tmp);
                    //Se o y for maior que zero decrementa e escreve na saida leste do elemento de roteamento
            } else if (y > 0) {
                y = y - 1;
                    //Saida de debug
                cout << "["<< this->name() << "]:(Saida de Debug) y ---> " << tmp.range(7, 0) << "\n";
                tmp.range(7, 0) = y;
                o_leste->write(tmp);
                    //Se o x e y forem zero, achou o elemento de roteamento ao qual esta conectado o modulo de destino
            } else {
                    //Saida de Debug
                cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento\n";
                    //Se o roteamento foi da direita para a esquerda escreve na saida oeste
                if (saida == 1){
                    o_oeste->write(tmp);}
                else{
                    o_leste->write(tmp);
                }
            }
                //Se o flit entrou pelo elemento de roteamento 1.(Procedimeto analogo ao explicado para a entrada 0
        }else if (ent == 1){
                //Se o roteador de destino do flit esta acima do elemento de roteamento em questao
            if (said == 1){
                if (x > 0) {
                    x = x - 1;
                        //Saida de Debug
                    cout << "["<< this->name() << "]:(Saida de Debug) x ---> " << tmp.range(15, 8) << "\n";
                    tmp.range(15, 8) = x;
                    o_norte->write(tmp);
                } else if (y > 0) {
                    y = y - 1;
                        //Saida de Debug
                    cout << "["<< this->name() << "]:(Saida de Debug) y ---> " << tmp.range(7, 0) << "\n";
                    tmp.range(7, 0) = y;
                    o_leste->write(tmp);
                } else {
                        //Saida de Debug
                    cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento\n";
                    if (saida == 1){
                        o_oeste->write(tmp);}
                    else{
                        o_leste->write(tmp);
                    }
                }
                    //Se o roteador de destino do flit esta abaixo do elemento de roteamento em questao
            }else if (said == 0){
                if (x > 0) {
                    x = x - 1;
                        //Saida de Debug
                    cout << "["<< this->name() << "]:(Saida de Debug) x ---> " << tmp.range(15, 8) << "\n";
                    tmp.range(15, 8) = x;
                    o_sul->write(tmp);
                } else if (y > 0) {
                    y = y - 1;
                        //Saida de Debug
                    cout << "["<< this->name() << "]:(Saida de Debug) y ---> " << tmp.range(7, 0) << "\n";
                    tmp.range(7, 0) = y;
                    o_leste->write(tmp);
                } else {
                        //Saida de Debug
                    cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento\n";
                    if (saida == 1){
                        o_oeste->write(tmp);}
                    else{
                        o_leste->write(tmp);
                    }
                }
            }
                //Se o flit entrou pelo elemento de roteamento 2.(Procedimeto analogo ao explicado para a entrada 0)
        }else if (ent == 2){
            if (x > 0) {
                x = x - 1;
                    //Saida de Debug
                cout << "["<< this->name() << "]:(Saida de Debug) x ---> " << tmp.range(15, 8) << "\n";
                tmp.range(15, 8) = x;
                o_norte->write(tmp);
            } else if (y > 0) {
                y = y - 1;
                    //Saida de Debug
                cout << "["<< this->name() << "]:(Saida de Debug) y ---> " << tmp.range(7, 0) << "\n";
                tmp.range(7, 0) = y;
                o_leste->write(tmp);
            } else {
                    //Saida de Debug
                cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento\n";
                if (saida == 1){
                    o_oeste->write(tmp);}
                else{
                    o_leste->write(tmp);
                }
            }
                //Se o flit entrou pelo elemento de roteamento 3.(Procedimeto analogo ao explicado para a entrada 0)
        }else if(ent == 3){
            if (x > 0) {
                x = x - 1;
                    //Saida de Debug
                cout << "["<< this->name() << "]:(Saida de Debug) x ---> " << tmp.range(15, 8) << "\n";
                tmp.range(15, 8) = x;
                o_sul->write(tmp);
            } else if (y > 0) {
                y = y - 1;
                    //Saida de Debug
                cout << "["<< this->name() << "]:(Saida de Debug) y ---> " << tmp.range(7, 0) << "\n";
                tmp.range(7, 0) = y;
                o_oeste->write(tmp);
            } else {
                    //Saida de Debug
                cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento\n";
                if (saida == 1){
                    o_leste->write(tmp);}
                else{
                    o_oeste->write(tmp);
                }
            }
                //Se o flit entrou pelo elemento de roteamento 4.(Procedimeto analogo ao explicado para a entrada 0)
        }else if (ent == 4){
                //Se o roteador de destino do flit esta acima do elemento de roteamento em questao
            if (said == 1){
                if (x > 0) {
                    x = x - 1;
                        //Saida de Debug
                    cout << "["<< this->name() << "]: x ---> " << tmp.range(15, 8) << "\n";
                    tmp.range(15, 8) = x;
                    o_norte->write(tmp);
                } else if (y > 0) {
                    y = y - 1;
                        //Saida de Debug
                    cout << "["<< this->name() << "]: y ---> " << tmp.range(7, 0) << "\n";
                    tmp.range(7, 0) = y;
                    o_oeste->write(tmp);
                } else {
                        //Saida de Debug
                    cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento\n";
                    if (saida == 1){
                        o_leste->write(tmp);}
                    else{
                        o_oeste->write(tmp);
                    }
                }
                    //Se o roteador de destino do flit esta abaixo do elemento de roteamento em questao
            }else if (said == 0){
                if (x > 0) {
                    x = x - 1;
                        //Saida de Debug
                    cout << "["<< this->name() << "]: x ---> " << tmp.range(15, 8) << "\n";
                    tmp.range(15, 8) = x;
                    o_sul->write(tmp);
                } else if (y > 0) {
                    y = y - 1;
                        //Saida de Debug
                    cout << "["<< this->name() << "]: y ---> " << tmp.range(7, 0) << "\n";
                    tmp.range(7, 0) = y;
                    o_oeste->write(tmp);
                } else {
                        //Saida de Debug
                    cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento\n";
                    if (saida == 1){
                        o_leste->write(tmp);}
                    else{
                        o_oeste->write(tmp);
                    }
                }
            }
                //Se o flit entrou pelo elemento de roteamento 5.(Procedimeto analogo ao explicado para a entrada 0)
        }else if (ent == 5){
            if (x > 0) {
                x = x - 1;
                    //Saida de Debug
                cout << "["<< this->name() << "]: x ---> " << tmp.range(15, 8) << "\n";
                tmp.range(15, 8) = x;
                o_norte->write(tmp);
            } else if (y > 0) {
                y = y - 1;
                    //Saida de Debug
                cout << "["<< this->name() << "]: y ---> " << tmp.range(7, 0) << "\n";
                tmp.range(7, 0) = y;
                o_oeste->write(tmp);
            } else {
                    //Saida de Debug
                cout << "["<< this->name() << "]:(Saida de Debug) Achou o elemento de roteamento\n";
                if (saida == 1){
                    o_leste->write(tmp);}
                else{
                    o_oeste->write(tmp);
                }
            }
        }//fim do algoritmo de roteamento
    }//Fim do for
}//Fim da thread
