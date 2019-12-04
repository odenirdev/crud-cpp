// CRUD PESSOA

// REGRAS DE PROGRAMAÇÃO
// CONTANTES EM MAIUSCULO
// VARIAVEIS, FUNCOES EM MINUSCULO QUEBRAS DE PALAVRAS COMEÇANDO COM LETRA MAIUSCULA
// LETRA DA PROXIMA PALAVRA EM MAIUSCULO

#include<iostream>
#include<fstream>
#include<cstring>

#define ARQUIVO_CRUD "PESSOAS.CRUD"

using namespace std;

class PESSOA {
    private:
        int  id;
        char nome[51];
        char dataNascimento[11];
        //int  status;

    public:
        // Getters e Setters ID
        int getId(void){
            return this->id;
        }

        void setId(int id){
            this->id = id;
            return;
        }

        // Getters e Setters Nome
        char* getNome(void){
            return this->nome;
        }

        void setNome(char nome[51]){
            strcpy(this->nome, nome);
            return;
        }

        // Getters e Setters Data de nascimento
        char* getDataNascimento(void){
            return this->dataNascimento;
        }

        void setDataNascimento(char data[11]){
            strcpy(this->dataNascimento, data);
            return;
        }

        // Getters e Setters Status | Se o status for 1 = ativo se for 0 = inativo
        int getStatus(void){
            return 1;
//            return this->status;
        }

        void setStatus(int status){
          //  this->status = status;
        }
};

long int pegarTamanhoDoArquivo(){
    long tamanho = 0;
    ifstream arquivo(ARQUIVO_CRUD, ios_base::in | // add - adicionar no final / in - leitura /
    ios_base::binary);
    arquivo.seekg(0, ios_base::end); // seekg() - Posicione para pegar / ios_base:"PESSOAS.CRUD":end - final do arquivo
    tamanho = arquivo.tellg(); //tellg() - pegar valor em bits
    if (tamanho == -1) tamanho = 0;
    arquivo.close();
    return tamanho;
}

long int pegarNumerosDePessoas(){
    long pessoas = 0;
    pessoas = pegarTamanhoDoArquivo() != 0? pegarTamanhoDoArquivo() / sizeof(PESSOA): 0;
    return pessoas;
}

bool inserirArquivo(PESSOA pessoa) {
    ofstream arquivo(ARQUIVO_CRUD, ios_base::app | ios_base::binary);
    arquivo.write(reinterpret_cast<char*>(&pessoa), sizeof(pessoa));
    arquivo.flush();
    arquivo.close();
    return true;
}

void cadastrar(void)
{
    char nome[51];
    char data[11];
    PESSOA pessoa;

    cout << endl << "<Cadastrar>"   << endl;

    cout << endl << "Nome: ";
    cin.getline(nome, sizeof(nome));

    cout << "Data de nascimento: ";
    cin.getline(data, sizeof(data));

    pessoa.setNome(nome);
    pessoa.setDataNascimento(data);
    pessoa.setId(pegarNumerosDePessoas() + 1);
    //pessoa.setStatus(1);

    inserirArquivo(pessoa);

    return;
}

PESSOA buscarUm(int idRegistro){
    PESSOA pessoa;
    ifstream arquivo(ARQUIVO_CRUD, ios_base::in | ios_base::binary);
    arquivo.seekg((idRegistro - 1) * sizeof(pessoa), ios_base::beg);
    arquivo.read(reinterpret_cast<char*>(&pessoa), sizeof(pessoa));
    arquivo.close();
    return pessoa;
}

void listarTodos(void)
{
    PESSOA pessoa;
    cout << endl <<"<Lista de pessoas>" << endl;
    ifstream arquivo(ARQUIVO_CRUD, ios_base::in | ios_base::binary);
    for (long pos = 0; pos < pegarNumerosDePessoas(); pos += 1){
        arquivo.seekg(pos * sizeof(pessoa), // ios::beg - pular
        ios_base::beg);
        arquivo.read(reinterpret_cast<char*>(&pessoa), sizeof(pessoa));
        cout << endl;
        cout << "ID: "   << pessoa.getId()   << endl;
        cout << "Nome: " << pessoa.getNome() << endl;
        cout << "Data de nascimento: " << pessoa.getDataNascimento() << endl;
    }
    arquivo.close();
    return;
}

void alterarArquivo(int idRegistro, PESSOA registro){
    if (idRegistro <= pegarNumerosDePessoas()){
        ofstream arquivo(ARQUIVO_CRUD, ios_base::out | ios_base::binary);
        arquivo.seekp((idRegistro - 1) * sizeof(registro), ios_base::beg);
        arquivo.write(reinterpret_cast<char*>(&registro), sizeof(registro));
        arquivo.flush();
        arquivo.close();
    } else cerr << endl << "Identificador Invalido!" << endl;
}

void alterarNome(int idRegistro){
    PESSOA pessoa;
    char nome[51];
    cout << endl << "<Alterar Nome>" << endl;
    pessoa = buscarUm(idRegistro);
    cout << endl << "Novo Nome: ";
    cin.getline(nome, sizeof(nome));
    pessoa.setNome(nome);
    alterarArquivo(idRegistro, pessoa);
    return;
}

void alterarDataNascimento(int idRegistro){
    PESSOA pessoa;
    char data[11];
    cout << endl << "<Alterar Data de Nascimento>" << endl;
    pessoa = buscarUm(idRegistro);
    cout << endl << "Nova data de nascimento: ";
    cin.getline(data, sizeof(data));
    pessoa.setDataNascimento(data);
    alterarArquivo(idRegistro, pessoa);
    return;
}

void alterar(void)
{
    int opcao;
    int opcao1;
    do {
        cout << endl << "<Alterar registro de pessoa>" << endl;
        listarTodos();
        cout << endl << "Selecione um registro pelo ID ou para sair entre com <0>!" << endl;
        cout << "Entre com a opcao: ";
        cin >> opcao;
        cin.ignore(1000, '\n');

        if (opcao != 0)
            if (opcao <= pegarNumerosDePessoas()){
                cout << endl <<"<Opcao de Alteracao>" << endl;
                cout << "1. Alterar nome" << endl;
                cout << "2. Alterar data de nascimento" << endl;
                cout << "0. Sair" << endl;
                cout << endl << "Entre com a opcao: ";
                cin >> opcao1;
                cin.ignore(1000, '\n');

                switch(opcao1){
                    case 1:
                        alterarNome(opcao);
                        break;

                    case 2:
                        alterarDataNascimento(opcao);
                        break;

                    case 0:
                        break;

                    default:
                        cerr << endl << "Opcao Invalida!" << endl;
                        break;
                }
            } else cerr << endl << "Opcao Invalida!" << endl;
    } while(opcao != 0);
    return;
}

void deletar(void)
{
    cout << sizeof(PESSOA) << endl;
    cout << pegarTamanhoDoArquivo() << endl;
    cout << pegarNumerosDePessoas() << endl;
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
                listarTodos();
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
