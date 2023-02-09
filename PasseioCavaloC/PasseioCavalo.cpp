#include <iostream>
#include <iomanip>

using namespace std;

    const int tamanhoTabuleiro = 8;
    int movimentoHorizontal[tamanhoTabuleiro + 1] = {0,2,1,-1,-2,-2,-1,1,2};
    int movimentoVertical[tamanhoTabuleiro + 1] = {0,1,2,2,1,-1,-2,-2,-1};
    int tabuleiro[tamanhoTabuleiro + 1][tamanhoTabuleiro + 1];
    int tamanhoTabuleiroUsuario;


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

      if (preencheuTodasCasas)
        imprimirTabuleiro();
      else
        cout << "Caminho nao encontrado" << endl;

      return 0;
    }
