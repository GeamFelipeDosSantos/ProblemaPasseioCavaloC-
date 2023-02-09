#include <iostream>
#include <iomanip>
#include <time.h>
#include <sys/time.h>

using namespace std;

    const int tamanhoTabuleiro = 8;
    int movimentoHorizontal[tamanhoTabuleiro + 1] = {0,2,1,-1,-2,-2,-1,1,2};
    int movimentoVertical[tamanhoTabuleiro + 1] = {0,1,2,2,1,-1,-2,-2,-1};
    int tabuleiro[tamanhoTabuleiro + 1][tamanhoTabuleiro + 1];
    int tamanhoTabuleiroUsuario;
    int static contadorAnalises = 0;


    void imprimirTabuleiro() {
      int i, j;
      for (i = 1; i <= tamanhoTabuleiroUsuario; i++) {
        for (j = 1; j <= tamanhoTabuleiroUsuario; j++)
          cout << setw(5) << tabuleiro[i][j];
        cout << endl;
      }
      cout << endl;
    }

    void tentarProximoMovimento(int valorPreencher, int linhaP, int colunaP, bool & preencheuTodasCasasP) {

      int linha;
      int coluna;
      int contador;
      bool sucesso;
      contador = 0;
      sucesso = false;
      contadorAnalises++;

      do {

        contador++;
        linha = linhaP + movimentoHorizontal[contador];
        coluna = colunaP + movimentoVertical[contador];

        if (1 <= linha
             && linha <= tamanhoTabuleiroUsuario
              && 1 <= coluna
                && coluna <= tamanhoTabuleiroUsuario
                 && tabuleiro[linha][coluna] == 0) {

          tabuleiro[linha][coluna] = valorPreencher;

          if (valorPreencher < (tamanhoTabuleiroUsuario * tamanhoTabuleiroUsuario)) {
            tentarProximoMovimento(valorPreencher + 1, linha, coluna, sucesso);
            if (!sucesso)
              tabuleiro[linha][coluna] = 0;
          } else
            sucesso = true;

        }
      } while (!sucesso && contador < tamanhoTabuleiro);

      preencheuTodasCasasP = sucesso;

    }

    int main() {

      struct timeval start, end;
      gettimeofday(&start, NULL);

      int linha, coluna;
      bool preencheuTodasCasas;

      cout << "Tamanho do tabuleiro (1-8): ";
      cin >> tamanhoTabuleiroUsuario;

      for (linha = 1; linha <= tamanhoTabuleiroUsuario; linha++)
        for (coluna = 1; coluna <= tamanhoTabuleiroUsuario; coluna++)
          tabuleiro[linha][coluna] = 0;

      cout << "Posicao inicial do cavalo (x,y): ";
      cin >> linha >> coluna;

      tabuleiro[linha][coluna] = 1;
      tentarProximoMovimento(2, linha, coluna, preencheuTodasCasas);

      cout << endl;
      cout << endl;

      gettimeofday(&end, NULL);
      long seconds = (end.tv_sec - start.tv_sec);
      long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

      printf("Codigo executado em: %d seg %d micros\n", seconds, micros);
      printf("Numero de casas analisadas foi: %u", contadorAnalises);
      cout << endl;
      cout << endl;

      if (preencheuTodasCasas)
        imprimirTabuleiro();
      else
        cout << "Caminho nao encontrado" << endl;

      return 0;
    }
