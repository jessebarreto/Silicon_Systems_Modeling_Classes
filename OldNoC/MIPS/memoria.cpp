/*
 *  memoria.cpp
 *  MIPSc++
 *
 *  Created by Ricardo Jacobi on 18/4/15.
 *  Copyright 2015 Universidade de Brasilia. All rights reserved.
 *
 */


#include "globals.h"
#include "memoria.h"
using namespace std;


void mem_mips::check_address_range(uint32_t address) {
	
	if ((address>>2) > INT_MEM_SIZE) {
		cout <<"["<< this->name() << "]"<< "Erro: endereco fora dos limites da memoria - " << std::hex << address << std::dec << endl;
		exit(-1);
	}
}

uint32_t hash_add(uint32_t address){
	uint32_t variavel = address - M1_min;
	return variavel;
}


int32_t mem_mips::lb(const uint32_t address) {
	uint32_t tmp_address;
	tmp_address = hash_add(address);

	check_address_range(tmp_address);
	
    int32_t word = mem[tmp_address>>2];
    
    return (int8_t)((word >> 8*(tmp_address%4))&0xFF);
}

int32_t mem_mips::lbu(const uint32_t address) {
	uint32_t tmp_address;
	tmp_address = hash_add(address);

    check_address_range(tmp_address);
	
    int32_t word = mem[tmp_address>>2];
    
    return ((word >> 8*(tmp_address%4))&0xFF);
}


int32_t mem_mips::lhu(const uint32_t address) {
   
	uint32_t tmp_address;
	tmp_address = hash_add(address);

	check_address_range(tmp_address);
	
    if ((address%2) != 0) {
        printf("Erro: endereco de meia palavra desalinhado!");
        return -1;
    }
	
	int32_t word = mem[tmp_address>>2];
	word = (word >> 8*((tmp_address%4)&2)); // (address % 4) & 2
	
    return (word & 0xFFFF);
}

int32_t mem_mips::lh(const uint32_t address) {
   
	uint32_t tmp_address;
	tmp_address = hash_add(address);

	check_address_range(tmp_address);
	
    if ((address%2) != 0) {
        printf("Erro: endereco de meia palavra desalinhado!");
        return -1;
    }
	
	int32_t word = mem[tmp_address>>2];
	word = (word >> 8*((tmp_address%4)&2)); // (address % 4) & 2
	
    return (int16_t)(word);
}

int32_t mem_mips::lw(const uint32_t address) {
   
	uint32_t tmp_address;
	//cout <<"["<< this->name() << "]"<< "Address: " << std::hex << address << std::dec << endl;
	tmp_address = hash_add(address);
	//cout << "TESTE1" << endl;
	//cout <<"["<< this->name() << "]"<< "Address: " << std::hex << tmp_address << std::dec << endl;
	check_address_range(tmp_address);
    int32_t word = mem[tmp_address>>2];
	//cout <<"["<< this->name() << "]"<< "Word: " << std::hex << word << std::dec << endl;
    
    return word;
}

void mem_mips::sb(const uint32_t address, int8_t dado) {
   
	uint32_t tmp_address;
	tmp_address = hash_add(address);

	check_address_range(tmp_address);
	
    uint32_t bi = (tmp_address%4);
    
    uint8_t *pb = (uint8_t *)&mem[tmp_address>>2];
	pb += bi;
    //for (int i=0; i < bi; i++) pb++;
    
    *pb = (uint8_t)dado;
}

void mem_mips::sh(const uint32_t address, int16_t dado) {
   
	uint32_t tmp_address;
	tmp_address = hash_add(address);

	check_address_range(tmp_address);
	
    if ((tmp_address%2) != 0)
        printf("Erro: endereco de meia palavra desalinhado!");
    
    // com ponteiros
    uint16_t *ph = (uint16_t *)&mem[tmp_address>>2];
    
    if (tmp_address&2) ph++;
    
    *ph = (uint16_t) dado;
}

void mem_mips::sw(const uint32_t address, int32_t dado) {
   
	uint32_t tmp_address;
	tmp_address = hash_add(address);

	check_address_range(tmp_address);
	
	mem[tmp_address>>2] = dado;
}


void mem_mips::dump_mem(int start, int end, char format) {
	switch (format) {
		case 'h':
		case 'H':
			for (uint32_t i = start; i <= end; i+=4)
				printf("%x \t%x\n", i, lw(i+M1_min));
			break;
		case 'd':
		case 'D':
			for (int i = start; i <= end; i+=4)
				printf("%x \t%d\n", i, lw(i+M1_min));
			break;
		default:
			break;
	}
}

int mem_mips::load_mem(const char *fn, int start) {
	FILE *fptr;
	int *m_ptr = mem + (start>>2);  
	int size = 0;
	
	fptr = fopen(fn, "rb");
	if (!fptr) {
		printf("Arquivo nao encontrado!");
		return -1;
	}
	else {
		while (!feof(fptr)) {
			fread(m_ptr, 4, 1, fptr);
			m_ptr++;
			size++;
		}
		fclose(fptr);
	}
	return size;
}