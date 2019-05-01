#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <math.h>

using namespace std;

void leTxt(int *nEntradas, int *nSaidas, int *nLinhasTabela)
{
    ifstream read("tabela6+.txt");
    int aux;

    read>>aux;
    *nLinhasTabela = aux;
    *nEntradas = log2(aux);
    read>>aux;
    *nSaidas = aux;

    cout << "numero de entradas: " << *nEntradas << endl;
    cout << "numero de saidas: " << *nSaidas << endl;
}

vector< vector<int> > criaTabela(int nEntradas, int nSaidas, int nLinhasTabela, vector< vector<int> > *entrada)
{
    ifstream read("tabela6+.txt");
    vector< vector<int> > tabela(nLinhasTabela, vector<int>(nSaidas, 1));

    int aux;
    read>>aux; read>>aux;

    //cout << "Tabela:" << endl;
    for(int i = 0; i < nLinhasTabela; i++)
    {
		for(int j = 0; j < nEntradas; j++)
        {
            read>>aux;
            (*entrada)[i][j] = aux;
            cout << (*entrada)[i][j] << " ";
        }
		for(int j = 0; j < nSaidas; j++)
        {
           read>>aux;
           tabela[i][j] = aux;
           cout << tabela[i][j] << ((j == nSaidas-1) ? "\n" : " ");
        }
    }

    cout << "-------------------\nEnter pra continuar" << endl;
    cin.ignore();

    return tabela;
}

int levelBackFunc(int col, int nLinhas, int lb, int nEntradas)
{
    int lim = nEntradas+nLinhas*(col-1);
    int num = rand()%lim;

    if(col > lb)
        while((num <= ((lim-1)-lb*nLinhas)) && (num >= nEntradas))
            num = rand()%lim;

    return num;
}

void funcIn(vector< vector<int> > *in, vector<int> vec, int nEntradas, int nLinhas, int nColunas, int nSaidas, int lb, int nLinhasTabela, bool imprime)
{
    int aux = nEntradas, cont = (nLinhas*nColunas*3);
    for(int i = 0; i < nLinhasTabela; i++)
    {
        aux = nEntradas;
        for(int j = 2; j < cont; j += 3)
        {
            int aux1 = vec[j-2], aux2 = vec[j-1];

            if(vec[j] == 1) (*in)[i][aux] = ((*in)[i][aux1] == 1 && (*in)[i][aux2] == 1); //AND
            else if(vec[j] == 2) (*in)[i][aux] = ((*in)[i][aux1] == 1 || (*in)[i][aux2] == 1); //OR
            else if(vec[j] == 3) (*in)[i][aux] = ((*in)[i][aux1] != 1); //NOT
            else (*in)[i][aux] = ((*in)[i][aux1] != (*in)[i][aux2]); //XOR
            aux++;
        }
    }

    int contIn = nEntradas + (nLinhas*nColunas) + nSaidas;
    for(int i = 0; i < nLinhasTabela; i++)
    {
        int auxTotal = cont;
        for(int j = aux; j < contIn; j++)
        {
            int aux2 = vec[auxTotal];
            (*in)[i][j] = (*in)[i][aux2];
            auxTotal++;
        }
    }

//    if(imprime)
//    {
//        int auxCont = nEntradas + (nLinhas*nColunas);
//        for(int i = 0; i < nLinhasTabela; i++)
//        {
//            cout << "Entrada " << ((i+1 < 10) ? "0" : "") << i+1 << ": ";
//            for(int j = 0; j < nEntradas; j++)
//                cout << (*in)[i][j] << ((j == nEntradas-1) ? "  ->  " : " ");
//            for(int j = auxCont; j < auxCont+nSaidas; j++)
//                cout << ((j == auxCont) ? "[" : "") << (*in)[i][j] << ((j == auxCont+nSaidas-1) ? "]\n" : " ");
//        }
//    }
}

vector<int> funcVetorAleatorio(int nEntradas, int nLinhas, int nColunas, int nSaidas, int lb)
{
    vector<int> vec((nLinhas*nColunas*3)+nSaidas);
    int col = 1, cont = (nLinhas*nColunas*3);
    for(int i = 2; i < cont; i += 3)
    {
        vec[i] = rand()%4+1;

        vec[i-2] = levelBackFunc(col, nLinhas, lb, nEntradas);
        vec[i-1] = levelBackFunc(col, nLinhas, lb, nEntradas);

        if(i%nLinhas != 0)
            col++;
    }

    for(int i = cont; i < cont+nSaidas; i++)
        vec[i] = levelBackFunc(nColunas+1, nLinhas, lb, nEntradas);

    return vec;
}

int novoValor(int pos, int nLinhas, int nColunas, int lb, int nEntradas)
{
    if(pos >= nLinhas*nColunas*3) return levelBackFunc(nColunas+1, nLinhas, lb, nEntradas);
    else return ((pos+1)%3 == 0 ? rand()%4+1 : levelBackFunc((pos/(nLinhas*nColunas))+1, nLinhas, lb, nEntradas));
}

vector<int> funcAlteracao(vector<int> vec, int nEntradas, int nLinhas, int nColunas, int nSaidas, int lb, bool imprime)
{
    int cont = (nLinhas*nColunas*3) + nSaidas;

    int novoIndice = rand()%(cont);
    int aux = novoValor(novoIndice, nLinhas, nColunas, lb, nEntradas);

    if(vec[novoIndice] == aux)
        while(vec[novoIndice] == aux)
            aux = novoValor(novoIndice, nLinhas, nColunas, lb, nEntradas);
    else vec[novoIndice] = aux;

    if(imprime)
    {
        cout << "Valor do indice " << novoIndice+1 << " alterado para " << vec[novoIndice] << endl;
        cout << "Vetor alterado: ";
        for(int i = 0 ; i < cont; i++)
            cout << vec[i] << ((i+1)%3 == 0 ? ((i <= cont-nSaidas) ? " | " : " ") : " ") << ((i == cont-1) ? "\n\n" : "");
    }

    return vec;
}

void funcV5(int nEntradas, int nLinhas, int nColunas, int nSaidas, int lb, int nLinhasTabela, int rep, bool imprime)
{
    int auxAcerto = 0, cont = (nLinhas*nColunas*3), n = nEntradas + (nLinhas*nColunas) + nSaidas;
    vector< vector<int> > in(nLinhasTabela, vector<int>(n, 1));
    vector< vector<int> > tabela = criaTabela(nEntradas, nSaidas, nLinhasTabela, &in);
    vector<int> vec = funcVetorAleatorio(nEntradas, nLinhas, nColunas, nSaidas, lb);
    vector<int> vec2 = vec, vecAux = vec;

    for(int auxRep = 1; auxRep <= 1000000; auxRep++)
    {
        vec = vecAux;
        if(imprime)
        {
            cout << "Novo vetor: ";
            for(int i = 0 ; i < cont+nSaidas; i++)
                cout << vec[i] << ((i+1)%3 == 0 ? ((i <= cont) ? " | " : " ") : " ") << ((i == cont+nSaidas-1) ? "   <-------\n\n" : "");
        }
        for(int i = 0; i < rep; i++)
        {
            int acertos = 0;

            vec2 = funcAlteracao(vec, nEntradas, nLinhas, nColunas, nSaidas, lb, imprime);
            for(int j = 0; j < nLinhasTabela; j++)
            {
                funcIn(&in, vec2, nEntradas, nLinhas, nColunas, nSaidas, lb, nLinhasTabela, imprime);
                for(int k = 0; k < nSaidas; k++)
                {
                    int auxInd = nEntradas + (nLinhas*nColunas) + k;
                    if(in[j][auxInd] == tabela[j][k])
                        acertos++;
                }
            }
            cout << acertos << "/" << nLinhasTabela*nSaidas;
            if(acertos >= auxAcerto)
            {
                cout << "    -------maior---------";
                vecAux = vec2;
                auxAcerto = acertos;
                //cin.ignore();
            }
            if(imprime) cout << "\n-------------\n\n\n";
            else cout << endl;
        }
        cout << auxRep << "\n\n";
        if(imprime) cout << "\n-------------\n";
        if(auxAcerto >= nLinhasTabela*nSaidas) break;
    }
    cout << "-------------------" << endl;
    for(int i = 0; i < cont+nSaidas; i++)
        cout << vec[i] << ((i+1)%3 == 0 ? ((i <= cont) ? " | " : " ") : " ") << ((i == cont+nSaidas-1) ? "\n" : "");
    cout << "-------------------\nEnter pra continuar" << endl;
    cin.ignore();
}

int main()
{
    int seed, nLinhas, nColunas, levelback, nEntradas, nSaidas, nLinhasTabela;

    cout << "Seed:" << endl;
    cin >> seed;
    cout << "Linhas:" << endl;
    cin >> nLinhas;
    cout << "Colunas:" << endl;
    cin >> nColunas;
    cout << "Levelback:" << endl;
    cin >> levelback;

    leTxt(&nEntradas, &nSaidas, &nLinhasTabela);

    srand(seed);
    funcV5(nEntradas, nLinhas, nColunas, nSaidas, levelback, nLinhasTabela, 4, false);
    return 0;
}

