/*                                              
* cod.cpp
 *
 *  Created on: 08/07/2015
 *  Modified by José Adalberto F. Gualeve on 30/04/16
 *      Author: soudre
 */

#include "cod.h"
#include <iostream>

//Thread para leitura do flit

void Cod::lerCod() {
    for (;;) {
        eh_cod = false;
        dado_cod = i_cod->read();
        eh_cod = true;
        dado_cod_evt.notify(SC_ZERO_TIME);
        wait(main_ack_evt);
    }
}

//Thread principal
void Cod::main() {
    	//Variavel para receber o flit proveniente do modulo
    sc_uint<32> tmp;
    	//Variavel para receber o flit modificado
    sc_uint<53> dado_m;
    for (;;) { 
            //Evento de ocorrencia do flit
        wait (dado_cod_evt);
        if (eh_cod){
            tmp = dado_cod;
                //Verifica se o flit e de cabecalho ou dado
            if (count == 0){
                    //origem <-- recebe a origem do pacote referente aos flits em questao
                origem = tmp.range(31,24);
                    //destino <-- recebe o destino do pacote referento aos flits em questao
                destino = tmp.range(23,16);
            }
                //contador de controle
            count++;
                //Se ja chegou os oito flits, formando o pacote, zera o contador
            if (count == 8){
                count = 0;
                cout << "["<< this->name() << "]: will send package from " << origem << " to " << destino << endl;
                
            }
            
                //Tabela de roteamento
            switch(destino){
                    //Se o destino for 0
                case 0:
                        //bit referente a variavel saida (declarada em router.h)
                    dado_m.range(20,20) = 0;
                    if (origem == 1){
                        dado_m.range(20,20) = 1;   //indica o sentido do roteamento
                        dado_m.range(52,21) = tmp; //recebe o dado do flit
                        dado_m.range(15,8) = 1;    //indica o x
                        dado_m.range(7,0) = 0;     //indica o y
                        dado_m.range(18,16) = 1;   //indica a entrada do flit
                        dado_m.range(19,19) = 1;   //Bit de controle da saida do flit
                            //Saida de Debug
                        if ( debug ) {
                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                    }else if (origem == 2){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 2;
                            //saida de Debug
                       if ( debug ) {
                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                       }
                       
                    }else if (origem == 3){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 0;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 3;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 4){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 4;
                        dado_m.range(19,19) = 1;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 5){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 5;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                    }
                    break;
                case 1:
                    dado_m.range(20,20) = 0;
                    if (origem == 0){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 0;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                    }else if (origem == 2){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 2;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                    }else if (origem == 3){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 3;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                    }else if (origem == 4){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 0;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 4;
                        dado_m.range(19,19) = 1;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                    }else if (origem == 5){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 5;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                    }
                    
                    break;
                case 2:
                    dado_m.range(20,20) = 0;
                    if (origem == 0){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 0;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 1){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 1;
                        dado_m.range(19,19) = 0;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 3){
                        dado_m.range(47,16) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 3;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 4){

                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 4;
                        dado_m.range(19,19) = 0;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 5){

                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 0;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 5;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                    }
                    
                    break;
                case 3:
                    dado_m.range(20,20) = 0;
                    if (origem == 0){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 0;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 0;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 1){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 1;
                        dado_m.range(19,19) = 1;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 2){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 2;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 4){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 4;
                        dado_m.range(19,19) = 1;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 5){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 5;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }
                    break;
                case 4:
                    dado_m.range(20,20) = 0;
                    if (origem == 0){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 0;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 1){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 0;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 1;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 2){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 2;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 3){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 3;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 5){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 5;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }
                    break;
                case 5:
                    dado_m.range(20,20) = 0;
                    if (origem == 0){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 0;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 1){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 1;
                        dado_m.range(19,19) = 0;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 2){
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 0;
                        dado_m.range(7,0) = 1;
                        dado_m.range(18,16) = 2;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 3){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 2;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 3;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }else if (origem == 4){
                        dado_m.range(20,20) = 1;
                        dado_m.range(52,21) = tmp;
                        dado_m.range(15,8) = 1;
                        dado_m.range(7,0) = 0;
                        dado_m.range(18,16) = 4;
                        dado_m.range(19,19) = 0;
                            //saida de Debug
                        if ( debug ) {

                            cout << "x_concat -> " << dado_m.range(15,8) << "\n";
                            cout << "y_concat -> " << dado_m.range(7,0) << "\n";
                        }
                        
                    }
                    break;
                    }//fim do switch
                    o_cod->write(dado_m);
                    cout << "["<< this->name() << "]: sent " << std::hex << dado_m << std::dec << endl;
                    
        }
        main_ack_evt.notify(SC_ZERO_TIME);
    }//fim do for
}//fim da thread
