#include <iostream>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

// variaveis globais
const unsigned n_individuos_populacao = 10;
int a = 1, b = 1, c = 1, d = 1, e = 1, f = 1; // Parâmetros para a função
float taxa_de_elitismo = 0.1;
const int n_de_elites = n_individuos_populacao * taxa_de_elitismo; // para manter apenas o melhor individu

//structs 

struct Populacao{
    int individuos[n_individuos_populacao];
};


// Funções

void seed_aleatoria(){
    srand(time(NULL));
}

Populacao criar_populacao_inicial (int min, int max) {
  Populacao populacao_criada;
  for(int i = 0; i < n_individuos_populacao; i++) {
    populacao_criada.individuos[i] = min + (rand() % (max - min + 1));  
  } 
  return populacao_criada;
}

unsigned avalia_individuo (int x){
    int formula = a * pow(x, 5) + b * pow(x, 4) + c * pow(x, 3) + d * pow(x, 2) + e * x + f;
    unsigned long nota = abs(formula);
    return nota;
}

// Seleção dos melhores individuos
Populacao elitismo(Populacao& populacao_inicial){
    Populacao elites;
    for(int i = 0; i < n_de_elites; i++){
        elites.individuos[i] = populacao_inicial.individuos[i]; // copiar o melhor individuo para a primeira posição
    }
return elites;
}
// criação da populção de pais, para o cruzamento

Populacao populacao_pais(Populacao & populacao_inicial, int numeros_elite){
    Populacao populacao_melhores = populacao_inicial;
    for(int i = 0; i < n_individuos_populacao; i++){
        for(int j = 0; j < n_individuos_populacao - i - 1; j++) {
            if(populacao_melhores.individuos[j] < populacao_melhores.individuos[j + 1]){
                int aux = populacao_melhores.individuos[j];
                populacao_melhores.individuos[j] = populacao_melhores.individuos[j + 1];
                populacao_melhores.individuos[j + 1] = aux;
            }
        }
    }
    Populacao populacao_pais;
    for(int i = 0; i < numeros_elite; i++){
        populacao_pais.individuos[i] = populacao_melhores.individuos[i];
    }
    return populacao_pais;
} 

// cruzamento dos indiviudos
void cruza(Populacao &populacao_inical, Populacao& populacao_pais){
 // Determina o ponto de cruzamento (metade dos bits)

 int n_bits = sizeof(int) * 8;
 int ponto_de_cruzamento = n_bits / 2;
// Criar uma máscara para selecionar a primeira metade dos bits
 unsigned int mask = (1 << ponto_de_cruzamento) - 1;

 // Sorteia os individuos que serão cruzados
for(int i = n_de_elites; i < n_individuos_populacao; i++){
 int individuo1 = rand() % n_individuos_populacao;
 int individuo2 = rand() % n_individuos_populacao;

 while(individuo2 == individuo1){
    individuo2 = rand() % n_individuos_populacao;
 }

 int pai1 = populacao_pais.individuos[individuo1];
 int pai2 = populacao_pais.individuos[individuo2];

 int parte_1 = (pai1 & mask);
 int parte_2 = (pai2 & mask);

 populacao_pais.individuos[i] = parte_1 | parte_2;     
}
}
void realiza_mutacao(Populacao &populacao_mutacao){ 
    for(int i = n_de_elites ; i < n_individuos_populacao; i++){
    int posicao_bit = rand() % 20; // Sorteia um bit dentre os 32 de um inteiro
    populacao_mutacao.individuos[i] ^= (1 << posicao_bit); // Altera esse bit
    }// Ele faz um rand e essa alteração pra cada individuo da lista
}

int main(){
    // variaveis
    float crossover = 0, mutacao = 0;
    unsigned max_geracoes = 1;
    int rand_min = 0, rand_max = 0;
    seed_aleatoria();
    //coleta dos primeiros passos

    cout << "Qual será a taxa de crossover (0 -> 90%)? : ";
    cin >> crossover;
    cout << "Qual será a taxa de mutação (0 -> 90%)? : ";
    cin >> mutacao;
    cout << "Quantas gerações serão analizadas? : ";
    cin >> max_geracoes;
    cout << "Qual será o valor mínimo dos números gerados? : ";
    cin >> rand_min;
    cout << "Qual será o valor máximo dos números gerados? : ";
    cin >> rand_max;
    cout << endl;
    cout << "Taxa de crossover escolhida: " << crossover << " %" << endl;
    cout << "Taxa de mutação escolhida: " << mutacao << " %" << endl;
    cout << "Número máximo de gerações: " << max_geracoes << endl;
    cout << endl;
    cout << "Agora os parâmetros para a função (a,b,c,d,e,f) : " << endl;
    cin >> a >> b >> c >> d >> e >> f;

     // Tranforma porcentagem de 0 - 100% para 0 - 1:
    crossover = crossover / 100;
    mutacao = mutacao / 100;

    Populacao populacao_inicial = criar_populacao_inicial(rand_min, rand_max);

    for(int m = 1; m <= max_geracoes; m++){
        Populacao populacao_de_pais = elitismo(populacao_inicial);
        cruza(populacao_inicial, populacao_de_pais);
        realiza_mutacao(populacao_de_pais);

        // cout << "Lista principal da geracao," << m << " antes : " << endl;
        // for(int i = 0; i < n_individuos_populacao; i++){
        //     cout << populacao_de_pais.individuos[i] << " | ";
        // }
        // cout << endl;

        for(int i = 0; i < n_individuos_populacao; i++){
            populacao_inicial.individuos[i] = populacao_de_pais.individuos[i];
            populacao_de_pais.individuos[i] = 0;
        }
        populacao_pais(populacao_de_pais , n_de_elites);
        // cout << "\nLista de pais da geracao: " << m << ":" << endl;
        // for(int i = 0; i < n_individuos_populacao; i++){
        //     cout << populacao_inicial.individuos[i] << " | ";
        // }

        // cout << "\nLista principal da geracao: " << m << ":" << endl;
        // for(int i = 0; i < n_individuos_populacao; i++){
        //     cout << populacao_inicial.individuos[i] << " | ";
        // }
        // cout << endl;

    }
    cout << "O individuo: " << populacao_inicial.individuos[0] << " Foi quem teve o melhor resultado, com a nota: " << avalia_individuo(populacao_inicial.individuos[0]) << endl;
    return 0;
}
 




