// CRUD PESSOA

// REGRAS DE PROGRAMAÇÃO
// CONTANTES EM MAIUSCULO
// VARIAVEIS, FUNCOES EM MINUSCULO QUEBRAS DE PALAVRAS COMEÇANDO COM LETRA MAIUSCULA
// LETRA DA PROXIMA PALAVRA EM MAIUSCULO

#include<iostream>
#include <fstream>

#define ARQUIVO_CRUD "PESSOAS.CRUD"

using namespace std;

struct PESSOA {
    char nome[50];
    char sobrenome[50];
};

long pegarTamanhoDoArquivo(){
    long tamanho;
    ifstream arquivo(ARQUIVO_CRUD, ios_base::in | // add - adicionar no final / in - leitura /
    ios_base::binary);
    arquivo.seekg(0, ios_base::end); // seekg() - Posicione para pegar / ios_base:"PESSOAS.CRUD":end - final do arquivo
    tamanho = arquivo.tellg(); //tellg() - pegar valor em bits
    cout << tamanho;
    return tamanho;
}

long pegarNumerosDePessoas(){
    long pessoas;
    pessoas = pegarTamanhoDoArquivo() / sizeof(PESSOA);
    return pessoas;
}

bool inserirArquivo(PESSOA p) {
    ofstream arquivo(ARQUIVO_CRUD, ios_base::app | ios_base::binary);
    arquivo.write(reinterpret_cast<char*>(&p.nome), sizeof(p.nome));
    arquivo.write(reinterpret_cast<char*>(&p.sobrenome), sizeof(p.sobrenome));
    return true;
}

void cadastrar(void)
{

    PESSOA pessoa;
    cout << sizeof(pessoa) << endl;
    PESSOA p;
    cout << endl << "<Cadastrar>"   << endl;

    cout << endl << "Nome: ";   cin.getline(p.nome, sizeof(p.nome));
    cout << "Sobrenome: ";      cin.getline(p.sobrenome, sizeof(p.sobrenome));
    cout << sizeof(p);
    inserirArquivo(p);

    return;
}

void listar(void)
{
    PESSOA pessoa;
    ifstream arquivo(ARQUIVO_CRUD, ios_base::in | ios_base::binary);
    for (long pos = 0; pos == pegarTamanhoDoArquivo(); pos += sizeof(pessoa)){
        arquivo.seekg(pos * sizeof(pessoa), // ios::beg - pular
          ios_base::beg);
        arquivo.read(reinterpret_cast<char*>(&pessoa.nome), sizeof(pessoa.nome));
          return;
        cout << "Valor " << pessoa.nome << " na posicao ";
    }

    return;
}

void alterar(void)
{
    return;
}

void deletar(void)
{
    return;
}

void menu(void)
{
    int OPCAO;
    do {
        cout << endl << "<CRUD PESSOA>" << endl;
        cout << "1. Cadastrar"  << endl;
        cout << "2. Listar"     << endl;
        cout << "3. Alterar"    << endl;
        cout << "4. Deletar"    << endl;
        cout << "0. Sair"       << endl;
        cout << endl << "Por favor! Entre com a opcao desejada: "; cin >> OPCAO; cin.ignore(1000, '\n');
        switch (OPCAO){
            case 1:
                cadastrar();
                break;
            case 2:
                listar();
                break;
            case 3:
                alterar();
                break;
            case 4:
                deletar();
                break;
            default:
                cerr << endl << "Entrada invalida!" << endl;
                break;
        }
    } while (OPCAO != 0);
    return;
}

int main(void)
{
    menu();
    cout << endl <<"Obrigado pela presenca!!!" << endl;
    return 0;
}
