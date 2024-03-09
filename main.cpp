#include <iostream>
#include <random>
#include <string>
#include <math.h>

using namespace std;

char* toBinary(int n, int tamanho) {
  static char r[100] = {0};
  std::fill_n(r, tamanho, '0');
  int i = tamanho - 1;
  while (n != 0 && i >= 0) {
        r[i] = (n % 2 == 0 ? '0' : '1');
        i--;
        n /= 2;
  }
  return r;
}

string toBinary(int n, int tamanho) {
  string r = "";
  while (n != 0) {
        r.append = (n % 2 == 0 ? '0' : '1');
        n /= 2;
  }
  return r;
}

// tamanho população
// n de gerações
// taxa de mutação
// intervalo minimo e max de numero aleatório (limitante da população inicial)
// inserir valores de a,b,c,d,e,f p/ equação de quinto grau (p/ futura comparação)
// tamanho do indivíduo = tamanho de um int = 4bytes = 32 bits
// chance de um bit alterar seu valor
// altera apenas 1 bit em cada indivíduo por vez (bit sorteado)


int main(){
        srand(time(NULL)); // Cria seed para geração de numeros aleatórios com base  
        const int tamanho_populacao = 10;
        float crossover = 0 , mutacao = 0;
        int geracoes = 1;
        cout << "Qual será a taxa de crossover (0 -> 90%)? : ";
        cin >> crossover;
        cout << "Qual será a taxa de mutação (0 -> 90%)? : ";
        cin >> mutacao;
        cout << "Quantas gerações serão analizadas? : ";
        cin >> geracoes;

        cout << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << "Tamanho da população "<< i <<" = " << tamanho_populacao << endl; 
        }
        cout << "Taxa de crossover escolhida: " << crossover << " %" << endl;
        cout << "Taxa de mutação escolhida: " << mutacao << " %" << endl;
        cout << "Número máximo de gerações : " << geracoes << endl;

        crossover = crossover / 100;
        mutacao = mutacao / 100;

        cout << endl;

        const unsigned short tamanho_individuo = 16;
        char* indiv_binario;
        char populacao[tamanho_populacao][tamanho_individuo];
        for (int i = 0; i < tamanho_populacao; i++){
            long range = pow(2 , tamanho_individuo);
            individuo = rand() % range;
            indiv_binario = toBinary(individuo, tamanho_individuo);
            for (int j = 0 ; j < tamanho_individuo ; j++){
                populacao[i][j] = indiv_binario[j];
                cout << indiv_binario[j] << " ";
            }
            cout << "     =    " << individuo << endl;
            cout << endl;
        }           
}