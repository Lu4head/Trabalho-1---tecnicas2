#include <iostream>
#include <random>
#include <string>

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

int main(){
        srand(time(NULL));
        int tamanho_populacao[3] = {10,100,1000};
        float crossover = 0 , mutacao = 0;
        int geracoes = 1;
        cin >> crossover;
        cout << "Qual será a taxa de mutação (0 -> 90%)? : ";
        cin >> mutacao;
        cout << "Quantas gerações serão analizadas? : ";
        cin >> geracoes;

        cout << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << "Tamanho da população "<< i <<" = " << tamanho_populacao[i] << endl; 
        }
        cout << "Taxa de crossover escolhida: " << crossover << " %" << endl;
        cout << "Taxa de mutação escolhida: " << mutacao << " %" << endl;
        cout << "Número máximo de gerações : " << geracoes << endl;

        crossover = crossover / 100;
        mutacao = mutacao / 100;

        cout << endl;

        int populacao[10];
        int tamanho_individuo = 16;
        for (int i = 0; i < 3; i++){
            int individuo = rand() % 8589934591;
            char* ptr = toBinary(individuo, tamanho_individuo);
            for (int i = 0 ; i < tamanho_individuo ; i++){
                cout << ptr[i] << " ";
            }
            cout << "     =    " << individuo << endl;
            cout << endl;
            
        }


}