#include "bitwise.h"
#include "constantes.h"

//typedef union {
//    float f;
//    unsigned int i;
//} FloatBits;

/*
*Funcao para retornar um valor Int que representa um Float
*@param floatVal  : valor a ser transformado
*
*@return unsigned int: o inteiro desejado deslocado "TIPO" bits para a direita
*********************************************************/
unsigned int floatToInt(float floatVal){
    return (*(unsigned int*)(&floatVal) >> TIPO);
}


/*
*Funcao para retornar um valor Float que estava salvo em um Int
*@param intVal  : valor a ser transformado
*
*@return float: o float desejado
*********************************************************/
float intToFloat(unsigned int intVal){
    intVal = intVal << TIPO;
    return *(float*)(&intVal);
}


/*
*Funcao para armazenar duas informa��es em um unico Int
*@param tipo  : primeira informa��o que deve ter no m�xima um tamanho "TIPO" em bits
*       valor : segunda informa��o (int ou float j� transformado em int e deslocado "TIPO" vezes
*
*@return unsigned int: a informa��o codificada
*********************************************************/
unsigned int packInfo(int tipo, int valor){
    unsigned int informacao = 0;
    informacao = (tipo << (32-TIPO)) | valor;
    return informacao;
}


/*
*Funcao para armazenar duas informa��es em um unico Int
*@param tipo  : primeira informa��o que deve ter no m�xima um tamanho "TIPO" em bits
*       valor : segunda informa��o (int)
*
*@return unsigned int: a informa��o codificada
*********************************************************/
unsigned int packInt(int tipo, int valor){
    unsigned int informacao = 0;
    informacao = (tipo << (32-TIPO)) | valor;
    return informacao;
}

/*
*Funcao para armazenar duas informa��es em um unico Int
*@param tipo  : primeira informa��o que deve ter no m�xima um tamanho "TIPO" em bits
*       valor : segunda informa��o (float)
*
*@return unsigned int: a informa��o codificada
*********************************************************/
unsigned int packFloat(int tipo, float valor){
    unsigned int informacao = 0;
    unsigned int valorInt = floatToInt(valor);
    //if(i == 1) printf("tipo ini = %d\n", tipo);

    informacao = (tipo << (32-TIPO)) | valorInt;
    //if(i == 1) printf("tipo ini = %d\n", unpackTipo(informacao));
    return informacao;
}

/*
*Funcao para retornar o 'tipo' de uma informa��o codificada
*@param info  : informa��o codificada
*
*@return int: o tipo
*********************************************************/
unsigned int unpackTipo(unsigned int info){
    unsigned int tipo = (info>>(32-TIPO));
    return tipo;
}

/*
*Funcao para retornar um Int de uma informa��o codificada
*@param info  : informa��o codificada
*
*@return int: a informa��o
*********************************************************/
unsigned int unpackInt(unsigned int info){
    int valor = (info << TIPO) >> TIPO;
    return valor;
}

/*
*Funcao para retornar um Float de uma informa��o codificada
*@param info  : informa��o codificada
*
*@return float: a informa��o
*********************************************************/
float unpackFloat(unsigned int info){
    //info = info;
    float valorF = intToFloat(info);
    return valorF;
}
