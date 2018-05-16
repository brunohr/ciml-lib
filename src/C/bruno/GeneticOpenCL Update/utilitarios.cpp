#include "utilitarios.h"
#include "constantes.h"

int rand2(int *seed){
//    const int a = 16807;
//    const int m = 2147483647;
//    const int q = 127773; // m div a
//    const int r = 2836; //m mod a
//
//    int lo, hi, test;
//
//    hi = *seed / q;
//    lo = *seed % q;
//    test = a*lo -r*hi;
//    if(test > 0)
//        *seed = test;
//    else
//        *seed = test+m;
    int s  = *seed;
    s = ((unsigned int)(s * 16807) % 2147483647);//(int)(pown(2.0, 31)-1));
    *seed = s;

    return s;
}

float randomProb(int* seed){
    return (float)rand2(seed) / 2147483647;//pown(2.0, 31);
}


void atribuiSemente(int i){
    srand(i);
}

//float randomProb(){
//    return rand()/(float)(RAND_MAX+1);
//}

int randomInterval(int inferior, int superior){
    return rand() % (superior - inferior + 1) + inferior;
}

int randomSuperior(int limiteSuperior){
    if(limiteSuperior == 0) return 0;
    return rand() % (limiteSuperior + 1);
}

int randomTerminal(int N, int* seed){
    int valor = rand2(seed) % (2*(N-1));
    return valor;
}

int randomFunctionBin(int NUM_OPBIN){
    return rand() % NUM_OPBIN;
}
int randomFunctionUn(int NUM_OPUN){
    return rand() % NUM_OPUN;
}
///.....................................


//float randomConst(int* seed, float maxDados, float minDados){
//    //int superior = 6, inferior = 0;
//    float random = (float)rand2(seed)/(float)(2147483647);
//    float range = maxDados - minDados;
//    //printf("aa = %d ",(rand2(seed)% (superior - inferior + 1) + inferior));
//    //float a = (rand2(seed)% (superior - inferior + 1) + inferior);
//    //printf("a = %f", as);
//    float result = (float)(range*random) + minDados;
//    return result;//(range*random) + minDados;//(float)(2147483647/2));
//}
float randomConst(int* seed, float maxDados, float minDados){
    //printf("const = %.32f = %.32f \n",  maxDados, minDados);
    float random = ((float)rand2(seed))/2147483647;
    float range = maxDados - minDados;
    float result = (range*random)+ minDados;
    //printf("const = %.32f\n", result);
    return result;
}


int randomType(int NUM_OPBIN, int NUM_OPUN, int N, int* seed){
    int tipoAleatorio = rand2(seed)%(NUM_OPBIN+NUM_OPUN+(1)+N-1);
    return tipoAleatorio;
}


int randomLeafType(int NUM_OPBIN, int NUM_OPUN, int N, int* seed){
    int tipoAleatorio = (rand2(seed)%N) + NUM_OPBIN + NUM_OPUN;
    return tipoAleatorio;
}

int randomNodeType(int NUM_OPBIN, int NUM_OPUN, int N, int* seed){
    int tipoAleatorio = (rand2(seed)%(NUM_OPBIN+NUM_OPUN));
    return tipoAleatorio;
}



float proDiv(float num, float div){
    if(div == 0){
        return 1;
    } else {
        return (num/div);
    }
}

float infDiv(float num, float div){
    if(div == 0){
        return INFINITY;
    } else {
        return (num/div);
    }
}

float proSqrt(float num){
    if(num < 0){
        return 1;
    } else {
        return sqrt(num);
    }
}

float infSqrt(float num){
    if(num < 0){
        return INFINITY;
    } else {
        return sqrt(num);
    }
}

void fatal(char *msg) {
    printf("%s\n", msg);
    exit (1);
}

float** readTrainingData(int *M, int *N, int *NUM_CTES, int *NUM_OPBIN, int *NUM_OPUN, char ***LABELS,
                          int **conjuntoOpTerm, float *maxDados, float *minDados, char *filename){

    std::fstream arq;
    float** dadosTreinamento;
    int i, j, k;
    int readLabel;
    int readOps;//, numOpBin, numOpUn;
    int info;

    printf("Lendo Dados Arquivo... %s\n",filename);
    arq.open(filename, std::fstream::in);

    arq >> (*M);
    arq >> (*N);
    arq >> (readLabel);

    dadosTreinamento = new float* [(*M)];
    for(i = 0; i < (*M); i++){
        dadosTreinamento[i] = new float [(*N)];
    }

    (*LABELS) = new char* [*(N)];
    for(i = 0; i < (*N); i++){
        (*LABELS)[i] = new char [10];
    }

    if(readLabel){
        for(i = 0; i < (*N); i ++){
            arq >> (*LABELS)[i];
        }
    } else {
        for(i = 0; i < (*N); i ++){
            std::stringstream ss;
            std::string str;
            char lab;

            if(i < (*N)/2)
                lab = (char)('a' + i);
            else
                lab = (char)('A' + i - ((*N)/2));
            ss << lab;
            ss >> str;

            (*LABELS)[i] = (char*)(str.c_str());
        }
    }

    for(i = 0; i < (*M); i++){
        for(j = 0; j < (*N); j++){
            arq >> dadosTreinamento[i][j];

        }
    }

    arq >> readOps;

    if(readOps){
        arq >> (*NUM_OPBIN);
        arq >> (*NUM_OPUN);

        (*conjuntoOpTerm) = new int [(*NUM_OPBIN)+(*NUM_OPUN)+(1)+(*N)-(1)];

        for (i = 0; i < (*NUM_OPBIN); i++){
            arq >> info;
            (*conjuntoOpTerm)[i] = packInt(FBIN, info);
        }
        for (j = 0; j < (*NUM_OPUN); j++, i++){
            arq >> info;
            (*conjuntoOpTerm)[i] = packInt(FUN, info);
        }

        for(j = 0; j < (*N)-(1); j++, i++){
            (*conjuntoOpTerm)[i] = packInt(VAR, j);
        }

        (*conjuntoOpTerm)[i] = packInt(CTE, 1);
        *NUM_CTES = 1;
    } else {
        *NUM_OPBIN = 4;
        *NUM_OPUN = 4;
        *NUM_CTES = 1;

        (*conjuntoOpTerm) = new int [(*NUM_OPBIN)+(*NUM_OPUN)+(1)+(*N)-(1)];
        //*conjuntoOpTerm = (int*)malloc(((*NUM_OPBIN)+(*NUM_OPUN)+(1)+(*N)-1) * sizeof(int*));

        i = 0;

        (*conjuntoOpTerm)[i++] = packInt(FBIN, PLUS);
        (*conjuntoOpTerm)[i++] = packInt(FBIN, MIN);
        (*conjuntoOpTerm)[i++] = packInt(FBIN, MULT);
        (*conjuntoOpTerm)[i++] = packInt(FBIN, DIV);


        (*conjuntoOpTerm)[i++] = packInt(FUN, SIN);
        (*conjuntoOpTerm)[i++] = packInt(FUN, COS);
        (*conjuntoOpTerm)[i++] = packInt(FUN, SQR);
        (*conjuntoOpTerm)[i++] = packInt(FUN, EXP);


        for(j = 0; j < (*N)-(1); j++, i++){
            (*conjuntoOpTerm)[i] = packInt(VAR, j);
        }

        (*conjuntoOpTerm)[i] = packFloat(CTE, 1.0);


    }


    return dadosTreinamento;
}

/*
float** readTrainingData(int* M, int* N, int* NUM_CTES, int* NUM_OPBIN, int* NUM_OPUN, char*** LABELS,
                         int** conjuntoOpTerm, float* maxDados, float* minDados, char* filename){
    FILE *arq;
    float** dadosTreinamento;
    int i = 0, j;
    int k;
    printf("Lendo Dados Arquivo... %s\n",filename);

//    char nome[100];
//    printf("\nDigite nome do arquivo:");
//    gets(nome);
//    arq = fopen(nome, "r");
    arq = fopen(filename, "r");
    int boolLabel;
    //fscanf(arq, "%d %d %d", &numLinhas, &numColunas, &boolLabel);//, &numVariaveis);
    fscanf(arq, "%d %d %d", M, N, &boolLabel);//, &numVariaveis);

//    M = numLinhas;
//    N = numColunas;
//    printf("\nN = %d\n\n", *N);
//    printf("\nM = %d\n\n", *M);

    dadosTreinamento = (float**)malloc((*M)* sizeof(float**));
    for(k = 0; k < (*M); k++){
        (dadosTreinamento)[k] = (float*)malloc((*N)*sizeof(float*));
    }

    //float dadosTreinamento[M][N];
    //printf("Inicializando Labels...\n");
    *LABELS = (char**)malloc((*N) * sizeof(char**));
//    for(k = 0; k < *N; k++){
//        (*LABELS)[k] = (char*)malloc(10*sizeof(char));
//    }


    if(boolLabel){
        char *word = NULL;
        size_t size = 2;
        long fpos;
        fpos = ftell(arq);
        //printf("pos = %d\n", fpos);
        char format [32];
        //char* labels[n];

        if ((word = (char*)malloc(size)) == NULL)                  // word memory
            fatal("Failed to allocate memory");
        sprintf (format, "%%%us", (unsigned)size-1);        // format for fscanf''

        while((fscanf(arq, format, word) == 1) && (i < (*N))) {
            while (strlen(word) >= size-1) {                // is buffer full?
                size *= 2;                                  // double buff size
                //printf ("** doubling to %u **\n", (unsigned)size);
                if ((word = (char*)realloc(word, size)) == NULL)
                    fatal("Failed to reallocate memory");
                sprintf (format, "%%%us", (unsigned)size-1);// new format spec
                fseek(arq, fpos, SEEK_SET);                  // re-read the line
                if (fscanf(arq, format, word) == 0)
                    fatal("Failed to re-read file");

        // printf ("lido2= %s\n", word);
            }
            //printf("pos = %d\n", fpos);
            (*LABELS)[i] = (char*)malloc((size));
            //printf("aaaaaaaaa");
            strcpy((*LABELS)[i], word);
            i = i + 1;

           // printf ("%s\n", word);
            //printf ("%s\n", LABELS[i]);
            fpos = ftell(arq);                               // mark file pos
        }
        fseek(arq, fpos, SEEK_SET);
        //printf("pos = %d\n", fpos);
        free(word);

    } else {
        for(k = 0; k < (*N); k++){
            (*LABELS)[k] = (char*)malloc(10*sizeof(char));
            (*LABELS)[k][0] = 'X';
            (*LABELS)[k][1] = '\0';

            char str[15];
            sprintf(str, "%d", k);
            strcat((*LABELS)[k], str);

        }
    }

//    for(i = 0; i < (*N); i++){
//        printf ("%s\n", (*LABELS)[i]);
//    }
    //printf("Lendo Dados...\n");
//    double meta = 0;
//
//    printf("\b\b\b\b0%%");
    for(i = 0; i < (*M); i++){
        for(j = 0; j < (*N); j++){
                //printf("a\n");
            if(!fscanf(arq, "%f", &dadosTreinamento[i][j]))
                break;

//            if((float)i/(*M) > meta){
//                printf("\b\b\b\b%3.f%%", meta * 100);
//                meta += 0.1;
//            }
            //printf("%f ",(dadosTreinamento)[i][j]);
        }
        if(dadosTreinamento[i][j-1] > (*maxDados)){
            (*maxDados) = dadosTreinamento[i][j-1];
        } else if (dadosTreinamento[i][j-1] < (*minDados)){
            (*minDados) = dadosTreinamento[i][j-1];
        }
    }
//    printf("\b\b\b\b100%%\n");

    int boolOps;//, numOpBin, numOpUn;
    int tipo;
    int info;

    printf("Inicializando conjunto de operacoes...\n");
    fscanf(arq, "%d", &boolOps);
    if(boolOps){
        fscanf(arq, "%d %d", NUM_OPBIN, NUM_OPUN);
//        NUM_OPBIN = numOpBin;
//        NUM_OPUN = numOpUn;

        //operacoesBin = malloc(numOpBin * sizeof(int));
        *conjuntoOpTerm = (int*)malloc(((*NUM_OPBIN)+(*NUM_OPUN)+(1)+(*N)-1) * sizeof(int*));

        for (i = 0; i < (*NUM_OPBIN); i++){
            if(!fscanf(arq, "%d", &info))
                break;
            (*conjuntoOpTerm)[i] = packInt(FBIN, info);
        }

//        if(numOpUn!= 0){
            for (j = 0; j < (*NUM_OPUN); j++, i++){
                if(!fscanf(arq, "%d", &info))
                    break;
                (*conjuntoOpTerm)[i] = packInt(FUN, info);
            }
//        }

        for(j = 0; j < (*N)-1; j++, i++){
            (*conjuntoOpTerm)[i] = packInt(VAR, j);
        }

        (*conjuntoOpTerm)[i] = packFloat(CTE, 1.0);
        *NUM_CTES = 1;
    } else {

        *NUM_OPBIN = 4;
        *NUM_OPUN = 4;
        *NUM_CTES = 1;
        *conjuntoOpTerm = (int*)malloc(((*NUM_OPBIN)+(*NUM_OPUN)+(1)+(*N)-1) * sizeof(int*));

        i = 0;

        (*conjuntoOpTerm)[i++] = packInt(FBIN, PLUS);
        (*conjuntoOpTerm)[i++] = packInt(FBIN, MIN);
        (*conjuntoOpTerm)[i++] = packInt(FBIN, MULT);
        (*conjuntoOpTerm)[i++] = packInt(FBIN, DIV);


        (*conjuntoOpTerm)[i++] = packInt(FUN, SIN);
        (*conjuntoOpTerm)[i++] = packInt(FUN, COS);
        (*conjuntoOpTerm)[i++] = packInt(FUN, SQR);
        (*conjuntoOpTerm)[i++] = packInt(FUN, EXP);


//        for (i = 0; i < (*NUM_OPBIN); i++){
//            (*conjuntoOpTerm)[i] = packInt(FBIN, i);
//        }
//        for (j = 0 ; j < (*NUM_OPUN); j++, i++){
//            (*conjuntoOpTerm)[i] = packInt(FUN, i);
//        }

        for(j = 0; j < (*N)-1; j++, i++){
            (*conjuntoOpTerm)[i] = packInt(VAR, j);
        }

        (*conjuntoOpTerm)[i] = packFloat(CTE, 1.0);

    }
    fclose(arq);

    return dadosTreinamento;

}
 */

void imprimeParametros(int M, int N, int NUM_CTES, int NUM_OPBIN, int NUM_OPUN){
    printf("/*-----------------------------------------------------------------\n");
    printf("* NUMERO INDIVIDUOS: %d \t CROSS-OVER: %.2f\n", NUM_INDIV, PROB_CROSS);
    printf("* NUMERO GERACOES  : %d \t MUTACAO   : %.2f\n", CARGA/NUM_INDIV, PROB_MUT);
    printf("* NUM MAXIMO NOS   : %d \t ELITISMO  : %.2f\n", MAX_NOS, ELITISMO);
    printf("* PROFUNDIDADE MAX : %d \t \n", MAX_DEPTH);
    printf("* M: %d \t N: %d\n", M, N);
    printf("* NUM_OPBIN: %d \t NUM_OPUN: %d\n", NUM_OPBIN, NUM_OPUN);
    printf("* NUM_CTES: %d \t SEED: %d\n", NUM_CTES, SEED);
    printf("*------------------------------------------------------------------\n");
}

bool IsPowerOf2( int n ){
   return (n & -n) == n;
}

unsigned NextPowerOf2( unsigned n ){
   n--;
   n |= n >> 1;  // handle  2 bit numbers
   n |= n >> 2;  // handle  4 bit numbers
   n |= n >> 4;  // handle  8 bit numbers
   n |= n >> 8;  // handle 16 bit numbers
   n |= n >> 16; // handle 32 bit numbers
   n++;

   return n;
}
std::string ToString( float t ){
      std::stringstream ss; ss << std::setprecision(32) << t; return ss.str();
}

//auto getTime(){
//    struct timeval tv;
//    gettimeofday(&tv,0);
//    return (double)tv.tv_sec + 1.0e-6*(double)tv.tv_usec;
//}

float mysqr(float f){
    f *= f;
    return f;
}
