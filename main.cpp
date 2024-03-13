/*
Integrantes do grupo:
Gustavo Paiva                   RA:
Gustavo Teixeira                RA: 2214047
Luan E. Rinaldi                 RA: 2184611 
Pedro Dezem                     RA:
*/  

#include <iostream>
#include <random>

using namespace std;

// Variáveis globais:
const unsigned n_individuos_populacao = 10;
const float taxa_de_elitismo = 0.3;
const int n_de_elites = n_individuos_populacao * taxa_de_elitismo;
int a = 1, b = 1, c = 1, d = 1, e = 1, f = 1;
// Structs:
struct Populacao{
    int individuos[n_individuos_populacao] = {0};
};

// Definição das Funções:

/*
Funções necessárias:
.cria_populacao_inicial();
.int Avalia(char F[50]);
.int Roleta(int K);
.void Cruza(int F,int G,int H);
.int Melhor(void);
.int Soma(void);//Faz Parte Indiretamente Do Método Roleta.
.void Elitismo(void);
.void CompletaCruza(int F[1000],int L);
.void Passa(void);
.void CrossOver(void); // Muda um bit aleatoriamente
*/ 

Populacao cria_populacao_inicial(int min, int max){
    Populacao Populacao_criada;
    for(int i = 0; i < n_individuos_populacao; i++){
        Populacao_criada.individuos[i] = min + (rand() % (max - min + 1));
    }
    return Populacao_criada;
}

void realiza_crossover(Populacao &populacao){
    for(int individuo ; individuo < n_individuos_populacao ; individuo++){
    int posicao_bit = rand() % 32;
    populacao.individuos[individuo] ^= (1 << posicao_bit);
    }
}

int avalia_individuo(int valor_individuo){
    int nota = abs(a*pow(valor_individuo,5)+b*pow(valor_individuo,4)+c*pow(valor_individuo,3)+d*pow(valor_individuo,2)+e*valor_individuo+f);
    return nota;
}

Populacao elitismo(Populacao &populacao){
    int lista_aux[n_individuos_populacao], aux;
    for(int i = 0 ; i < n_individuos_populacao ; i++){
        lista_aux[i] = avalia_individuo(populacao.individuos[i]);
        cout << "Nota de " << populacao.individuos[i] << " é igual a : " << avalia_individuo(populacao.individuos[i]) << endl;
    }
    for (int i = 0; i < n_individuos_populacao - 1; i++) { // Bubble sort para organizar as maiores notas no começo da lista
        for (int j = 0; j < n_individuos_populacao - i - 1; j++) {
            if (lista_aux[j] > lista_aux[j + 1]) {
                // Troca os elementos se estiverem na ordem errada
                aux = lista_aux[j];
                lista_aux[j] = lista_aux[j + 1];
                lista_aux[j + 1] = aux;

                aux = populacao.individuos[j];
                populacao.individuos[j] = populacao.individuos[j + 1];
                populacao.individuos[j + 1] = aux;
            }
        }
    }

    for (int i = 0; i < n_individuos_populacao ; i++){
        cout << lista_aux[i] << " | ";
    }
    cout << endl;
    Populacao populacao_pais;
    for(int i = 0 ; i < n_de_elites ; i++){
        populacao_pais.individuos[i] = populacao.individuos[i];
    }
    return populacao_pais;
}

void cruza(Populacao &populacao_principal, Populacao &populacao_pais , float crossover){
    // Determinar o ponto de cruzamento (metade do número de bits)
    int n_bits = sizeof(int) * 8;
    int crossover_point = n_bits * crossover;

    for(int i = n_de_elites ; i < n_individuos_populacao ; i++){
    // Criar uma máscara para selecionar a primeira metade dos bits
    unsigned int mask = (1 << crossover_point) - 1;

    // Sorteia os individuos que serão cruzados;
    int individuo1 = rand() % (n_individuos_populacao); 
    int individuo2 = 0;
    do
    {
        individuo2 = rand() % (n_individuos_populacao);
    } while (individuo2 == individuo1); // Garante que não vai cruzar um individuo com ele mesmo
    
    // Separar os bits das duas partes de cada indivíduo
    int parte_1_individuo = populacao_principal.individuos[individuo1] & mask;
    int parte_2_individuo = populacao_principal.individuos[individuo2] & ~mask;

    // Combinar as duas partes para formar o novo indivíduo
    populacao_pais.individuos[i] = parte_1_individuo | parte_2_individuo;
    }
}


// 1 = identificar o bit dentro do int
// 2 = mudar o bit dentro do int


int main(){
    srand(time(NULL));
    // Variáveis:
    float crossover = 0 , mutacao = 0;
    unsigned max_geracoes = 1;
    int rand_min= 0 , rand_max = 0;
    //
    // Coleta parametros passados pelo usuário:
    cout << "Qual será a taxa de crossover (0 -> 90%)? : ";
    cin >> crossover;
    cout << "Qual será a taxa de mutação (0 -> 90%)? : ";
    cin >> mutacao;
    cout << "Quantas gerações serão analizadas? : ";
    cin >> max_geracoes;
    cout << "Qual será o valor mínimo dos números gerados? : ";
    cin >> rand_min;
    cout << "Qual será o valor máximo dos números gerados? :";
    cin >> rand_max;
    cout << endl;
    cout << "Taxa de crossover escolhida: " << crossover << " %" << endl;
    cout << "Taxa de mutação escolhida: " << mutacao << " %" << endl;
    cout << "Número máximo de gerações : " << max_geracoes << endl;
    //
    // Tranforma porcentagem de 0 - 100% para 0 - 1:
    crossover = crossover / 100;
    mutacao = mutacao / 100;
    //

    Populacao Populacao_principal = cria_populacao_inicial(rand_min,rand_max);
    cout << "População Inicial: " << endl;
    for(int i = 0 ; i < n_individuos_populacao ; i++){
        cout << Populacao_principal.individuos[i] << " | ";
    }
    cout << endl;
    cout << "Lista de notas ordenada: " << endl;
    Populacao Populacao_de_pais = elitismo(Populacao_principal);
    cout << "\nLista principal ordenada: " << endl;
    for (int i = 0; i < n_individuos_populacao ; i++){
        cout << Populacao_principal.individuos[i] << " | ";
    }
    /*for(int i = 0 ; i < max_geracoes ; i++){
        for(int n = 0 ; n < n_individuos_populacao ; n++){
            
        }
        //if(){
            
            //fórmula p/ comparação = a*pow(n,5)+b*pow(n,4)+c*pow(n,3)+d*pow(n,2)+e*n+f = 0 , a != 0
        //}

         //verificar se a solução está aceitável (se sim, encerrar laço)
         // O melhor não é alterado.
         // Guardar os outros 4 melhores, ou sortear eles
         // Criar filhos dos mesmos com o cruzamento (preencher o vetor novamente com esse cruzamento)
         // aplicar mutaçao nos 9, com a chance dela ocorrer ou não.
         // Refazer o processo de avaliação.
    }*/
    cout << "\nLista de pais :" << endl;
    for (int i = 0; i < n_individuos_populacao ; i++){
        cout << Populacao_de_pais.individuos[i] << " | ";
    }
    cruza(Populacao_principal, Populacao_de_pais, crossover);
    cout << "\nLista de pais cruzada :" << endl;
    for (int i = 0; i < n_individuos_populacao ; i++){
        cout << Populacao_de_pais.individuos[i] << " | ";
    }
    return 0;
}

// tamanho população
// n de gerações
// taxa de mutação
// intervalo minimo e max de numero aleatório (limitante da população inicial) <-----
// inserir valores de a,b,c,d,e,f p/ equação de quinto grau (p/ futura comparação)
// tamanho do indivíduo = tamanho de um int = 4bytes = 32 bits
// chance de um bit alterar seu valor
// altera apenas 1 bit em cada indivíduo por vez (bit sorteado)
// objetivo é chegar o mais próximo possível da raiz de uma função de 5º grau