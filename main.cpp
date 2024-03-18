/*
Integrantes do grupo:
Gustavo Paiva                   RA:
Gustavo Teixeira                RA: 2214047
Luan E. Rinaldi                 RA: 2184611 
Pedro Dezem                     RA:
*/  

#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <locale.h>

using namespace std;

// Variáveis globais:
const unsigned n_individuos_populacao = 1000; // Tamanho da população
const float taxa_de_elitismo = 0.1; // Elites = Melhores indivíduos que serão passados pra prox geração sem serem alterados
const int n_de_elites = n_individuos_populacao * taxa_de_elitismo;
int a = 1, b = 1, c = 1, d = 1, e = 1, f = 1; // Parâmetros da função
// Structs:
struct Populacao{
    int individuos[n_individuos_populacao] = {0};
};

Populacao cria_populacao_inicial(int min, int max){
    Populacao Populacao_criada;
    for(int i = 0; i < n_individuos_populacao; i++){
        Populacao_criada.individuos[i] = min + (rand() % (max - min + 1));
    }
    return Populacao_criada;
}

unsigned avalia_individuo(int x){ 
    int formula = a * pow(x, 5) + b * pow(x, 4) + c * pow(x, 3) + d * pow(x, 2) + e * x + f;
    unsigned nota = abs(formula);
    return nota;
}

void ordena_populacao(Populacao &populacao){
    unsigned lista_notas[n_individuos_populacao];
    int aux; // essa lista é meio q a lista das notas de cada individuo
    for(int i = 0 ; i < n_individuos_populacao ; i++){
        lista_notas[i] = avalia_individuo(populacao.individuos[i]);
    }
    for (int i = 0; i < n_individuos_populacao - 1; i++) { // Bubble sort para organizar as melhores notas no começo da lista
        for (int j = 0; j < n_individuos_populacao - i - 1; j++) {
            if (lista_notas[j] > lista_notas[j + 1]) {
                // Troca os elementos se estiverem na ordem errada
                aux = lista_notas[j]; 
                lista_notas[j] = lista_notas[j + 1];
                lista_notas[j + 1] = aux;

                aux = populacao.individuos[j]; // Essa parte ordena a lista original de individuos
                populacao.individuos[j] = populacao.individuos[j + 1];
                populacao.individuos[j + 1] = aux;
            }
        }
    }
}

Populacao elitismo(Populacao populacao){ // tenho q renomear a função dps, mas ela basicamente ordena a lista pela nota e separa os individuos melhores q n serão alterados
    Populacao populacao_pais; 
    for(int i = 0 ; i < n_de_elites ; i++){ // n_de_elites é o numero de individuos * taxa_de_elites q a gente definir, no caso ta 10 * 0.1 = 1 individuo
        populacao_pais.individuos[i] = populacao.individuos[i]; // Faz o primeiro individuo da populacao_pais ser o com a melhor nota
    }
    return populacao_pais; // Retorna a populacao_pais, q por enqnt tem só o melhor individuo e o resto é 0
}

void cruza(Populacao &populacao_principal, Populacao &populacao_pais, float crossover){
    // Determinar o ponto de cruzamento (metade do número de bits)
    int n_bits = sizeof(int) * 8;
    int crossover_point = n_bits / 2;

    for(int i = n_de_elites ; i < n_individuos_populacao ; i++){
    // Criar uma máscara para selecionar a primeira metade dos bits
    unsigned int mask = (1 << crossover_point) - 1;
    // Individuos minimos e máximos para cruzamento
    int min = n_de_elites;
    int max = n_individuos_populacao*crossover;

    // Sorteia os individuos que serão cruzados;
    int individuo1 = min + (rand() % (max - min + 1)); 
    int individuo2 = 0;
    do
    {
        individuo2 = min + (rand() % (max - min + 1));
    } while (individuo2 == individuo1); // Garante que não vai cruzar um individuo com ele mesmo
    
    // Separar os bits das duas partes de cada indivíduo
    int parte_1_individuo = populacao_principal.individuos[individuo1] & mask;
    int parte_2_individuo = populacao_principal.individuos[individuo2] & ~mask;

    // Combinar as duas partes para formar o novo indivíduo
    populacao_pais.individuos[i] = parte_1_individuo | parte_2_individuo;
    }
}

void realiza_mutacao(Populacao &populacao){ 
    for(int n = n_de_elites ; n < n_individuos_populacao ; n++){
    int posicao_bit = rand() % 10; // Sorteia um bit dentre os 32 de um inteiro
    populacao.individuos[n] ^= (1 << posicao_bit); // Altera esse bit
    }// Ele faz um rand e essa alteração pra cada individuo da lista
}



int main(){
    setlocale(LC_ALL , "Portuguese");
    // Seed Aleatória
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
    cout << "Qual será o valor máximo dos números gerados? : ";
    cin >> rand_max;
    cout << endl;
    cout << "Taxa de crossover escolhida: " << crossover << " %" << endl;
    cout << "Taxa de mutação escolhida: " << mutacao << " %" << endl;
    cout << "Número máximo de gerações: " << max_geracoes << endl;
    cout << endl;
    cout << "Agora os parâmetros para a função (a,b,c,d,e,f) : " << endl;
    cin >> a >> b >> c >> d >> e >> f;
    //
    // Tranforma porcentagem de 0 - 100% para 0 - 1:
    crossover = crossover / 100;
    mutacao = mutacao / 100;
    //
    Populacao Populacao_principal = cria_populacao_inicial(rand_min,rand_max);

    for(int m = 1 ; m <= max_geracoes ; m++){
    ordena_populacao(Populacao_principal);

    Populacao Populacao_de_pais = elitismo(Populacao_principal);

    cruza(Populacao_principal, Populacao_de_pais, crossover);

    realiza_mutacao(Populacao_de_pais);      
    // cout << "Lista de pais da geração " << m << " , antes :" << endl;
    // for(int i = 0; i < n_individuos_populacao; i++){
    //     cout << Populacao_de_pais.individuos[i] << " | ";
    // }
    // cout << endl;
    // cout << "Lista principal da geração " << m << " , antes :" << endl;
    // for(int i = 0; i < n_individuos_populacao; i++){
    //     cout << Populacao_principal.individuos[i] << " | ";
    // }
    // cout << endl;
    // Troca população_principal dessa geração para a principal da proxima
    for(int i = 0; i < n_individuos_populacao; i++){
        Populacao_principal.individuos[i] = Populacao_de_pais.individuos[i];
        Populacao_de_pais.individuos[i] = 0;
    }

    // cout << "Lista de pais da geração " << m << " :" << endl;
    // for(int i = 0; i < n_individuos_populacao; i++){
    //     cout << Populacao_de_pais.individuos[i] << " | ";
    // }
    // cout << endl;
    // cout << "Lista principal da geração " << m << " :" << endl;
    // for(int i = 0; i < n_individuos_populacao; i++){
    //     cout << Populacao_principal.individuos[i] << " | ";
    // }
    // cout << endl;
    }
    cout << "O indivíduo: " << Populacao_principal.individuos[0] << " foi quem teve o melhor resultado, com nota: " << avalia_individuo(Populacao_principal.individuos[0]) << endl; 
    return 0;
}