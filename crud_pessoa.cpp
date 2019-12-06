// CRUD PESSOA

// REGRAS DE PROGRAMAÇÃO
// CONTANTES EM MAIUSCULO
// VARIAVEIS, FUNCOES EM MINUSCULO QUEBRAS DE PALAVRAS COMEÇANDO COM LETRA MAIUSCULA
// LETRA DA PROXIMA PALAVRA EM MAIUSCULO

#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include<windows.h>

#define ARQUIVO_CRUD "PESSOAS.CRUD"

using namespace std;

class PESSOA {
    private:
        int  id;
        char nome[51];
        char dataNascimento[11];
        int  status;

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
            return this->status;
        }

        void setStatus(int status){
          this->status = status;
        }
};

class ARQUIVO {
    public:
        void alterarArquivo(int idRegistro, PESSOA registro){
            if (idRegistro <= this->pegarNumerosDePessoas()){
                fstream arquivo(ARQUIVO_CRUD, ios_base::out | ios_base::in | ios_base::binary);
                arquivo.seekp((idRegistro - 1) * sizeof(registro), ios_base::beg);
                arquivo.write(reinterpret_cast<char*>(&registro), sizeof(registro));
                arquivo.close();
            } else cerr << endl << "Identificador Invalido!" << endl;
        }

        long int pegarNumerosDePessoas(){
            long pessoas = 0;
            pessoas = pegarTamanhoDoArquivo() != 0? pegarTamanhoDoArquivo() / sizeof(PESSOA): 0;
            return pessoas;
        }

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

        bool inserirArquivo(PESSOA pessoa){
            ofstream arquivo(ARQUIVO_CRUD, ios_base::app | ios_base::binary);
            arquivo.write(reinterpret_cast<char*>(&pessoa), sizeof(pessoa));
            arquivo.flush();
            arquivo.close();
            return true;
        }

        PESSOA buscarUm(int idRegistro){
            PESSOA pessoa;
            ifstream arquivo(ARQUIVO_CRUD, ios_base::in | ios_base::binary);
            arquivo.seekg((idRegistro - 1) * sizeof(pessoa), ios_base::beg);
            arquivo.read(reinterpret_cast<char*>(&pessoa), sizeof(pessoa));
            arquivo.close();
            return pessoa;
        }

        void buscarTodos(void){
            PESSOA pessoa;
            ifstream arquivo(ARQUIVO_CRUD, ios_base::in | ios_base::binary);

            cout << "<Lista de pessoas cadastradas>" << endl;
            for (long pos = 0; pos < pegarNumerosDePessoas(); pos += 1){
                arquivo.seekg(pos * sizeof(pessoa), // ios::beg - pular
                ios_base::beg);
                arquivo.read(reinterpret_cast<char*>(&pessoa), sizeof(pessoa));
                cout << endl << "<Registro " << pessoa.getId() << ">" << endl;
                cout << "ID: " << pessoa.getId() << endl;
                cout << "Nome: " << pessoa.getNome() << endl;
                cout << "Data de nascimento: " << pessoa.getDataNascimento() << endl;
            }
            arquivo.close();
            return;
        }
};

class SISTEMA{
    public:
        void alterarNome(int idRegistro){
            ARQUIVO arquivo;
            PESSOA pessoa;
            char nome[51];
            cout << endl << "<Alterar Nome>" << endl;
            pessoa = arquivo.buscarUm(idRegistro);
            cout << endl << "Novo Nome: ";
            cin.getline(nome, sizeof(nome));
            pessoa.setNome(nome);
            arquivo.alterarArquivo(idRegistro, pessoa);
            return;
        }

        void alterarDataNascimento(int idRegistro){
            ARQUIVO arquivo;
            PESSOA pessoa;
            char data[11];
            cout << endl << "<Alterar Data de Nascimento>" << endl;
            pessoa = arquivo.buscarUm(idRegistro);
            cout << endl << "Nova data de nascimento: ";
            cin.getline(data, sizeof(data));
            pessoa.setDataNascimento(data);
            arquivo.alterarArquivo(idRegistro, pessoa);
            return;
        }

        void alterar(void){
            ARQUIVO arquivo;
            int opcao;
            int opcao1;
            do {
                cout << endl << "<Alterar registro de pessoa>" << endl;
                arquivo.buscarTodos();
                cout << endl << "Selecione um registro pelo ID ou para sair entre com <0>!" << endl;
                cout << "Entre com a opcao: ";
                cin >> opcao;
                cin.ignore(1000, '\n');
                if (opcao != 0 && opcao <= arquivo.pegarNumerosDePessoas()){
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
                            cout << endl << "<< " << endl;
                            break;

                        default:
                            cerr << endl << "Opcao Invalida!" << endl;
                            break;
                    }
                } else cerr << endl << "Opcao Invalida!" << endl;
            } while(opcao != 0);
            return;
        }

        void deletar(void){

        }

        void cadastrar(void){
            char nome[51];
            char data[11];
            ARQUIVO arquivo;
            PESSOA pessoa;

            cout << endl << "<Cadastrar>"   << endl;
            cout << endl << "Nome: ";
            cin.getline(nome, sizeof(nome));
            cout << "Data de nascimento: ";
            cin.getline(data, sizeof(data));

            pessoa.setNome(nome);
            pessoa.setDataNascimento(data);
            pessoa.setId(arquivo.pegarNumerosDePessoas() + 1);
            pessoa.setStatus(1);

            arquivo.inserirArquivo(pessoa);

            return;
        }

        void informacoesGerenciais(){
            int opcao;
            ARQUIVO arquivo;

            cout << endl << "<Informacoes gerenciais>"  << endl;
            cout << endl << "Numero de pessoas: "       << arquivo.pegarNumerosDePessoas() << endl;
            cout << endl << "Tamanho do arquivo: "      << arquivo.pegarTamanhoDoArquivo() / 8 << " bytes" << endl;
            cout << endl << "Tamanho do registro: "     << sizeof(PESSOA) / 8 << " bytes" << endl;

            do {
                cout << endl << "<Relatorios>"  << endl;
                cout << "1. Listar todos" << endl;
                cout << "0. Sair" << endl;
                cout << endl << "Entre com a opcao :";
                cin >> opcao;
                cin.ignore(1000, '\n');
                switch (opcao){
                    case 1:
                        arquivo.buscarTodos();
                        break;
                }
            } while (opcao != 0);
            return;
        }

        void menu(void){
            int OPCAO;
            do {
                cout << endl << "<CRUD PESSOA>" << endl;
                cout << "1. Cadastrar registro"  << endl;
                cout << "2. Pesuisar por nome" << endl;
                cout << "3. Pesuisar por data de nascimento" << endl;
                cout << "4. Remover registro" << endl;
                cout << "5. Alterar registro" << endl;
                cout << "6. Informacoes gerenciais" << endl;
                cout << "0. Sair" << endl;
                cout << endl << "Por favor! Entre com a opcao desejada: "; cin >> OPCAO; cin.ignore(1000, '\n');
                switch (OPCAO){
                    case 1:
                        cadastrar();
                        break;

                    case 2:
                        pesquisarNome();
                        break;

                    case 3:
                        pesquisarDataNascimento();

                    case 4:
                        deletar();
                        break;
                    case 5:
                        alterar();
                        break;

                    case 6:
                        informacoesGerenciais();
                        break;

                    case 0:
                        cout << endl <<"Obrigado pela presenca!!!" << endl;
                        break;

                    default:
                        cerr << endl << "Entrada invalida!" << endl;
                        OPCAO = 99;
                        break;
                }
            } while (OPCAO != 0);
            return;
        }
};

int main(void)
{
    SISTEMA sistema;
    sistema.menu();
    return 0;
}
