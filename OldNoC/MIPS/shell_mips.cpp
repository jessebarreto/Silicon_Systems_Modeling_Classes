#include "globals.h"
#include "shell_mips.h"
using namespace std;

void shellmi_mips::check_destiny(uint32_t word, uint32_t destiny){
	if ((get_orig(word)) != destiny) {
		cout << "Erro: origem da palavra recibida nao corresponde com o destino em - " << get_orig(word) << " e " << destiny;
		exit(-1);
	}
}

uint32_t shellmi_mips::map_tab(uint32_t address){
	if(address >= M0_min && address <= M0_max)
		return M0;

	if(address >= M1_min && address <= M1_max)
		return M1;

	if(address >= DMA_min && address <= DMA_max)
		return DMA;

	if(address >= R_A_min && address <= R_A_max)
		return R_A;

	if(address >= DSPL_min && address <= DSPL_max)
		return DSPL;
}

int32_t shellmi_mips::lb(const uint32_t address, uint16_t kte) {
	uint32_t destino;
	destino = map_tab(address);

	// address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x1;
	uint32_t	flit_tmp = build_Hflit(P, destino, LB, size);
	out.write(flit_tmp);
	
	// send data flit throug fifo
	flit_tmp = tmp;
	out.write(flit_tmp);

	// receive header flit from destiny
	int32_t word_tmp = in.read();
	check_destiny(word_tmp, destino);	// check if came from actual destiny

	// receive data flit from destiny
	word_tmp = in.read();

    return (int8_t)(word_tmp);
}

int32_t shellmi_mips::lbu(const uint32_t address, uint16_t kte) {
	
	uint32_t destino;
	destino = map_tab(address);

    // address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x1;
	uint32_t	flit_tmp = build_Hflit(P, destino, LBU, size);
	out.write(flit_tmp);
	
	// send data flit throug fifo
	flit_tmp = tmp;
	out.write(flit_tmp);

	// receive header flit from destiny
	int32_t word_tmp = in.read();
	check_destiny(word_tmp, destino);	// check if came from actual destiny

	// receive data flit from destiny
	word_tmp = in.read();
    
	return (word_tmp);
}


int32_t shellmi_mips::lhu(const uint32_t address, uint16_t kte) {
    uint32_t destino;
	destino = map_tab(address);

	// address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x1;
	uint32_t	flit_tmp = build_Hflit(P, destino, LHU, size);
	out.write(flit_tmp);
	
	// send data flit throug fifo
	flit_tmp = tmp;
	out.write(flit_tmp);

	// receive header flit from destiny
	int32_t word_tmp = in.read();
	check_destiny(word_tmp, destino);	// check if came from actual destiny

	// receive data flit from destiny
	word_tmp = in.read();
	
	return (word_tmp);
}

int32_t shellmi_mips::lh(const uint32_t address, uint16_t kte) {
    uint32_t destino;
	destino = map_tab(address);

	// address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x1;
	uint32_t	flit_tmp = build_Hflit(P, destino, LH, size);
	out.write(flit_tmp);
	
	// send data flit throug fifo
	flit_tmp = tmp;
	out.write(flit_tmp);

	// receive header flit from destiny
	int32_t word_tmp = in.read();
	check_destiny(word_tmp, destino);	// check if came from actual destiny

	// receive data flit from destiny
	word_tmp = in.read();
	
    return (int16_t)(word_tmp);
}

int32_t shellmi_mips::lw(const uint32_t address, uint16_t kte) {
    uint32_t destino;
	destino = map_tab(address);

	// address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x1;
	uint32_t	flit_tmp = build_Hflit(P, destino, LW, size);
	out.write(flit_tmp);

	// send data flit throug fifo
	flit_tmp = tmp;
	out.write(flit_tmp);

	// receive header flit from destiny
	int32_t word_tmp = in.read();
	check_destiny(word_tmp, destino);	// check if came from actual destiny

	// receive data flit from destiny
	word_tmp = in.read();
    
    return(word_tmp);

}


int32_t shellmi_mips::instruction_lw(const uint32_t address, uint16_t kte) {
    // address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x1;
	uint32_t	flit_tmp = build_Hflit(P, M0, I_LW, size);
	out.write(flit_tmp);
	
	// send data flit throug fifo
	flit_tmp = tmp;
	out.write(flit_tmp);

	// receive header flit from destiny
	
	int32_t word_tmp = in.read();
	check_destiny(word_tmp, M0);	// check if came from actual destiny
	
	// receive data flit from destiny
	word_tmp = in.read();
    
    return(word_tmp);

}

void shellmi_mips::sb(const uint32_t address, uint16_t kte, int8_t dado) {
    uint32_t destino;
	destino = map_tab(address);

	// address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x2;
	uint32_t	flit_tmp = build_Hflit(P, destino, SB, size);
	out.write(flit_tmp);
	
	// send data flit throug fifo
	flit_tmp = tmp;
	out.write(flit_tmp);

	// send data flit throug fifo
	flit_tmp = dado;
	out.write(flit_tmp);

}

void shellmi_mips::sh(const uint32_t address, uint16_t kte, int16_t dado) {
    uint32_t destino;
	destino = map_tab(address);

	// address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x2;
	uint32_t	flit_tmp = build_Hflit(P, destino, SH, size);
	out.write(flit_tmp);
	
	// send data flit throug fifo
	flit_tmp = tmp;
	out.write(flit_tmp);

	// send data flit throug fifo
	flit_tmp = dado;
	out.write(flit_tmp);
}

void shellmi_mips::sw(const uint32_t address, uint16_t kte, int32_t dado) {
    uint32_t destino;
	destino = map_tab(address);

	// address + offset
    uint32_t tmp = address + kte;
    
	// send header flit throug fifo (size = 1)
	uint32_t	size = 0x2;
	uint32_t	flit_tmp = build_Hflit(P, destino, SW, size);
	out.write(flit_tmp);
	
	// send data flit throug fifo
	flit_tmp = tmp;
	out.write(flit_tmp);

	// send data flit throug fifo
	flit_tmp = dado;
	out.write(flit_tmp);

}
