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

struct Populacao{
    static const unsigned n_individuos = 10;
    int individuos[n_individuos];
};

Populacao cria_populacao(int min, int max){
    Populacao Populacao_1;
    for(int i = 0; i < Populacao_1.n_individuos; i++){
        Populacao_1.individuos[i] = min + (rand() % (max - min + 1));
    }
    return Populacao_1;
}

// 1 = identificar o bit dentro do int
// 2 = mudar o bit dentro do int


int main(){
    srand(time(NULL));
    float crossover = 0 , mutacao = 0;
    unsigned max_geracoes = 1;
    int rand_min= 0 , rand_max = 0;
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
    crossover = crossover / 100;
    mutacao = mutacao / 100;

    Populacao teste = cria_populacao(rand_min,rand_max);
    cout << "População Inicial: " << endl;
    for(int i = 0 ; i < teste.n_individuos ; i++){
        cout << teste.individuos[i] << " | ";
    }
    cout << endl;
    for(int i = 0 ; i < max_geracoes ; i++){
        for(int n = 0 ; n < teste.n_individuos ; n++){
            
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
    }

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