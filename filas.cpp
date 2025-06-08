/*
=========================================
| NOME: Stiven Richardy Silva Rodrigues |
| PRONTUÁRIO: CB3030202                 |
| TURMA: ADS 371                        |
=========================================
*/

#include <iostream>
#include <locale.h>
#include <string>
#include <conio.h>

using namespace std;

#define MAX 100

// FILAS DE ARRAY
struct FilaArray {
    float nos[MAX];
    int ini;
    int fim;
};

FilaArray* initArray() {
    FilaArray* f = new FilaArray;
    f->ini = 0;
    f->fim = 0;
    return f;
}

int isEmpty(FilaArray* f) {
    return (f->ini == f->fim);
}

int count(FilaArray* f) {
	if(f->fim >= f->ini) {
		return f->fim - f->ini;
	}
	return MAX - f->ini + f->fim;
}

int enqueue(FilaArray* f, float v) {
    int proximo_fim = (f->fim + 1) % MAX;
    if (proximo_fim == f->ini) {
        return 0;
    }
    f->nos[f->fim] = v;
    f->fim = proximo_fim;
    return 1;
}

float dequeue(FilaArray* f) {
    float ret;
    if (isEmpty(f)) {
        ret = -1;
    } else {
        ret = f->nos[f->ini];
        f->ini = (f->ini + 1) % MAX;
    }
    return ret;
}

void freeFila(FilaArray* f) {
    free(f);
}

// FILAS DE PONTEIRO
struct No {
    float dado;
    No* prox;
};

struct FilaPonteiro {
    No* ini;
    No* fim;
};

FilaPonteiro* initPonteiro() {
    FilaPonteiro* f = new FilaPonteiro;
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

int isEmpty(FilaPonteiro* f) {
    return (f->ini == NULL);
}

int count(FilaPonteiro* f) {
    int qtde = 0;
    No* no = f->ini;
    while (no != NULL) {
        qtde++;
        no = no->prox;
    }
    return qtde;
}

void enqueue(FilaPonteiro* f, float v) {
    No* no = new No;
    no->dado = v;
    no->prox = NULL;
    if (isEmpty(f)) {
        f->ini = no;
    } else {
        f->fim->prox = no;
    }
    f->fim = no;
}

float dequeue(FilaPonteiro* f) {
    float ret;
    if (isEmpty(f)) {
        ret = -1;
    } else {
        No* no = f->ini;
        ret = no->dado;
        f->ini = no->prox;
        if (f->ini == NULL) {
            f->fim = NULL;
        }
        free(no);
    }
    return ret;
}

void freeFila(FilaPonteiro* f) {
    No* no = f->ini;
    while (no != NULL) {
        No* aux = no->prox;
        free(no);
        no = aux;
    }
    free(f);
}

// FUNÇÕES DE EXIBIÇÃO
void exibeTitulo() {
    cout << string(50, '=') << endl
         << string(15, ' ') << "FILA DE ATENDIMENTO" << endl
         << string(50, '=') << endl;
}

void limpaTela() {
    cout << string(50, '=') << endl
         << "Pressione qualquer tecla..." << endl;
    _getch();
    system("cls");
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "");

    int opcao;
    int ii = 1;

    FilaArray* senhasGeradas = initArray();
    FilaPonteiro* senhasAtendidas = initPonteiro();

    exibeTitulo();
    cout << "| Bem vindo a fila de atendimento." << endl
         << "| Para controle da demanda administrativa,\n| o sistema suporta apenas 100 senhas aguardando\n| o atendimento." << endl;
    limpaTela();

    do {
        exibeTitulo();
        cout << "| Senhas aguardando atendimento: " << count(senhasGeradas) << endl
             << string(50, '=') << endl
             << "| Lista de opções: \n| 0. Sair\n| 1. Gerar senha\n| 2. Realizar atendimento" << endl
             << "| Digite a opção: ";
        cin >> opcao;
        system("cls");

        switch (opcao) {
            case 0:
                if(isEmpty(senhasGeradas)) {
					exibeTitulo();
					cout << "| Você saiu do programa!\n| Senhas atendidas: " << count(senhasAtendidas) << endl
						 << string(50, '=') << endl;
                    freeFila(senhasGeradas);
                    freeFila(senhasAtendidas);
				} else {
					opcao = -1;
					exibeTitulo();
					cout << "| Opção inválida, senhas aguardando atendimento." << endl;
					limpaTela();
				}
                break;
            case 1:
                exibeTitulo();
				if (enqueue(senhasGeradas, ii)) {
			    	cout << "| Senha gerada com sucesso!" << endl
						 << "| Senha Nº " << ii++ << endl;
				} else {
					cout << "| Não foi possível gerar a senha." << endl
						 << "| O limite de senhas aguardando atendimento\n| foi atingido." << endl;
				}
				limpaTela();
                break;
            case 2:
               	exibeTitulo();
				if(!isEmpty(senhasGeradas)) {
					float senhaAtendida = senhasGeradas->nos[senhasGeradas->ini];
					enqueue(senhasAtendidas, senhaAtendida);
				    cout << "| Senha atendida com sucesso." << endl 
						 << "| Senha Nº " << senhaAtendida << endl;
				    dequeue(senhasGeradas);
				} else {
					cout << "| Nenhuma senhas aguardando atendimento." << endl;
				}
			    limpaTela();
                break;
            default:
            	exibeTitulo();
                cout << "| Opção inválida. Tente novamente..." << endl;
                limpaTela();
        }
    } while (opcao != 0);

    return 0;
}