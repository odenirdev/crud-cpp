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
    int  id;
    char nome[50];
};

long int pegarTamanhoDoArquivo(){
    long tamanho = 0;
    ifstream arquivo(ARQUIVO_CRUD, ios_base::in | // add - adicionar no final / in - leitura /
    ios_base::binary);
    arquivo.seekg(0, ios_base::end); // seekg() - Posicione para pegar / ios_base:"PESSOAS.CRUD":end - final do arquivo
    tamanho = arquivo.tellg(); //tellg() - pegar valor em bits
    if (tamanho == -1) tamanho = 0;
    return tamanho;
}

long int pegarNumerosDePessoas(){
    long pessoas = 0;
    pessoas = pegarTamanhoDoArquivo() != 0? pegarTamanhoDoArquivo() / sizeof(PESSOA): 0;
    return pessoas;
}

bool inserirArquivo(PESSOA pessoa) {
    ofstream arquivo(ARQUIVO_CRUD, ios_base::app | ios_base::binary);
    arquivo.write(reinterpret_cast<char*>(&pessoa.id),   sizeof(pessoa.id));
    arquivo.write(reinterpret_cast<char*>(&pessoa.nome), sizeof(pessoa.nome));
    arquivo.close();
    return true;
}

void cadastrar(void)
{
    PESSOA pessoa;

    cout << endl << "<Cadastrar>"   << endl;
    cout << endl << "Nome: ";
    cin.getline(pessoa.nome, sizeof(pessoa.nome));

    pessoa.id = pegarNumerosDePessoas() + 1;
    inserirArquivo(pessoa);

    return;
}

void listar(void)
{
    cout << pegarNumerosDePessoas();
    cout << endl <<"<Lista de pessoas>" << endl;
    PESSOA pessoa;
    ifstream arquivo(ARQUIVO_CRUD, ios_base::in | ios_base::binary);
    for (long pos = 0; pos < pegarNumerosDePessoas(); pos += 1){
        arquivo.seekg(pos * sizeof(pessoa), // ios::beg - pular
          ios_base::beg);
        arquivo.read(reinterpret_cast<char*>(&pessoa),   sizeof(pessoa));
        cout << endl;
        cout << "ID: "   << pessoa.id << endl;
        cout << "Nome: " << pessoa.nome << endl;
    }
    arquivo.close();
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

            case 0:
                cout << endl <<"Obrigado pela presenca!!!" << endl;
                break;

            default:
                cerr << endl << "Entrada invalida!" << endl;
                OPCAO = 5;
                break;
        }
    } while (OPCAO != 0);
    return;
}

int main(void)
{
    menu();
    return 0;
}
