// CRUD PESSOA

// REGRAS DE PROGRAMAÇÃO
// CONTANTES EM MAIUSCULO
// VARIAVEIS, FUNCOES EM MINUSCULO QUEBRAS DE PALAVRAS COMEÇANDO COM LETRA MAIUSCULA
// LETRA DA PROXIMA PALAVRA EM MAIUSCULO

#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include<cctype>
#include<windows.h>
#include<locale>

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
            strcpy(this->nome, maiusculo(nome));
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

        char * maiusculo(char palavra[51]){
            for (int i=0; i < sizeof(palavra); i++) palavra[i] = toupper(palavra[i]);
            return palavra;
        }
};

class ARQUIVO {
    public:
        void pause(void) {
            cout << endl <<"PRESSIONE QUALQUER TECLA PARA CONTINUAR.  .  .";
            cin.get( );
        }

        void limpa(void) {
            HANDLE TELA;
            DWORD ESCRITA = 0;
            COORD POS;
            TELA = GetStdHandle(STD_OUTPUT_HANDLE);
            POS.X = 0;
            POS.Y = 0;
            FillConsoleOutputCharacter(TELA, 32, 100 * 100, POS, &ESCRITA);
        }

        void position(int LINHA, int COLUNA) {
            if (COLUNA >= 1 and COLUNA <= 80 and LINHA >= 1 and LINHA <= 24) {
                HANDLE TELA;
                COORD POS;
                TELA = GetStdHandle(STD_OUTPUT_HANDLE);
                POS.X = COLUNA - 1;
                POS.Y = LINHA - 1;
                SetConsoleCursorPosition(TELA, POS);
            }
            return;
        }

        void alterarArquivo(int idRegistro, PESSOA registro){
            if (idRegistro <= this->pegarNumerosDePessoas()){
                fstream arquivo(ARQUIVO_CRUD, ios_base::out | ios_base::in | ios_base::binary);
                arquivo.seekp((idRegistro - 1) * sizeof(registro), ios_base::beg);
                arquivo.write(reinterpret_cast<char*>(&registro), sizeof(registro));
                arquivo.close();
            } else cerr << endl << "Identificador Invalido!" << endl;
            return;
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
            int linha = 1;
            ifstream arquivo(ARQUIVO_CRUD, ios_base::in | ios_base::binary);
            limpa();
            position(1, 1);

            cout << "<Lista de pessoas cadastradas>";
            for (long pos = 0; pos < pegarNumerosDePessoas(); pos += 1){
                arquivo.seekg(pos * sizeof(pessoa), // ios::beg - pular
                ios_base::beg);
                arquivo.read(reinterpret_cast<char*>(&pessoa), sizeof(pessoa));
                if (pessoa.getStatus() == 1){
                    position(linha += 2, 1);
                    cout << "<Registro " << pessoa.getId() << ">";
                    position(linha += 1, 1);
                    cout << "ID: " << pessoa.getId();
                    position(linha += 1, 1);
                    cout << "Nome: " << pessoa.getNome();
                    position(linha += 1, 1);
                    cout << "Data de nascimento: " << pessoa.getDataNascimento();
                }
            }
            pause();
            arquivo.close();
            return;
        }

        void pesquisarArquivo(char tipo[10], char pesquisa[51]){
            PESSOA pessoa;
            int linha = 1;
            ifstream arquivo(ARQUIVO_CRUD, ios_base::in | ios_base::binary);
            cout << pesquisa;
            limpa();
            position(1, 1);
            cout << "<Pesquisa pessoa>";
            for (long pos = 0; pos < pegarNumerosDePessoas(); pos += 1){
                arquivo.seekg(pos * sizeof(pessoa), // ios::beg - pular
                ios_base::beg);
                arquivo.read(reinterpret_cast<char*>(&pessoa), sizeof(pessoa));
                if (pessoa.getStatus() == 1){
                    if (strcmp(tipo, "NOME") == 0 && strcmp(pessoa.maiusculo(pesquisa), pessoa.getNome()) == 0){
                        position(linha += 2, 1);
                        cout << "<Registro " << pessoa.getId() << ">";
                        position(linha += 1, 1);
                        cout << "ID: " << pessoa.getId();
                        position(linha += 1, 1);
                        cout << "Nome: " << pessoa.getNome();
                        position(linha += 1, 1);
                        cout << "Data de nascimento: " << pessoa.getDataNascimento();
                    } else if (strcmp(tipo, "DATA") == 0 && strcmp(pesquisa, pessoa.getDataNascimento()) == 0){
                        position(linha += 2, 1);
                        cout << "<Registro " << pessoa.getId() << ">";
                        position(linha += 1, 1);
                        cout << "ID: " << pessoa.getId();
                        position(linha += 1, 1);
                        cout << "Nome: " << pessoa.getNome();
                        position(linha += 1, 1);
                        cout << "Data de nascimento: " << pessoa.getDataNascimento();
                    }
                }
            }
            arquivo.close();
            pause();
            return;
        }
};

class SISTEMA{
    public:
        void pause(void) {
            cout << endl <<"PRESSIONE QUALQUER TECLA PARA CONTINUAR.  .  .";
            cin.get( );
        }

        void limpa(void) {
            HANDLE TELA;
            DWORD ESCRITA = 0;
            COORD POS;
            TELA = GetStdHandle(STD_OUTPUT_HANDLE);
            POS.X = 0;
            POS.Y = 0;
            FillConsoleOutputCharacter(TELA, 32, 100 * 100, POS, &ESCRITA);
        }

        void position(int LINHA, int COLUNA) {
            if (COLUNA >= 1 and COLUNA <= 80 and LINHA >= 1 and LINHA <= 24) {
                HANDLE TELA;
                COORD POS;
                TELA = GetStdHandle(STD_OUTPUT_HANDLE);
                POS.X = COLUNA - 1;
                POS.Y = LINHA - 1;
                SetConsoleCursorPosition(TELA, POS);
            }
            return;
        }

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
                limpa();
                position(1, 1);
                cout << "<Alterar registro de pessoa>";
                position(3, 1);
                cout << "Selecione um registro pelo ID ou para sair entre com <0>!";
                position(4, 1);
                cout << "Entre com a opcao: ";
                cin >> opcao;
                cin.ignore(1000, '\n');
                if (opcao != 0 && opcao <= arquivo.pegarNumerosDePessoas()){
                    limpa();
                    position(1, 1);
                    cout << "<Opcao de Alteracao>";
                    position(2, 1);
                    cout << "1. Alterar nome";
                    position(3, 1);
                    cout << "2. Alterar data de nascimento";
                    position(4, 1);
                    cout << "0. Sair";
                    position(6, 1);
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
                            cerr << "Opcao Invalida!" << endl;
                            break;
                    }
                } else cerr << "Opcao Invalida!" << endl;
            } while(opcao != 0);
            return;
        }

        void deletar(void){
            PESSOA pessoa;
            ARQUIVO arquivo;
            int opcao;
            char opcao1[5];

            do {
                limpa();
                position(1, 1);
                cout <<"<Remover registro de pessoa>";
                position(3, 1);
                cout << "Selecione um registro pelo ID ou para sair entre com <0>!";
                position(4, 1);
                cout << "Entre com a opcao: ";
                cin >> opcao;
                cin.ignore(1000, '\n');
                pessoa = arquivo.buscarUm(opcao);
                if (opcao != 0 && opcao <= arquivo.pegarNumerosDePessoas()) {
                    if (pessoa.getStatus() == 1){
                        limpa();
                        position(1, 1);
                        cout << "Tem certeza que deseja remover o registro " << opcao << " ?";
                        cout << endl << "SIM ou NAO: ";
                        cin.getline(opcao1, sizeof(opcao1));
                        if ((strcmp( opcao1, "S") == 0) || (strcmp(opcao1, "SI") == 0) || (strcmp(opcao1, "SIM") == 0)){
                            pessoa.setStatus(0);
                            arquivo.alterarArquivo(opcao, pessoa);
                        }
                    } else {
                        cerr << "Registro não encontrado";
                    }
                }
            } while(opcao != 0);
        }

        void cadastrar(void){
            limpa();
            char nome[51];
            char data[11];
            ARQUIVO arquivo;
            PESSOA pessoa;
            position(1, 1);
            cout << "<Cadastrar>";
            position(3, 1);
            cout << "Nome: ";
            cin.getline(nome, sizeof(nome));
            position(4, 1);
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
            do {
                limpa();
                position(1, 1);
                cout << "<Informacoes gerenciais>";
                position(2, 1);
                cout << "Numero de pessoas: "       << arquivo.pegarNumerosDePessoas();
                position(3, 1);
                cout << "Tamanho do arquivo: "      << arquivo.pegarTamanhoDoArquivo() / 8 << " bytes";
                position(4, 1);
                cout << "Tamanho do registro: "     << sizeof(PESSOA) / 8 << " bytes";

                position(6, 1);
                cout << "<Relatorios>";
                position(7, 1);
                cout << "1. Listar todos" << endl;
                position(8, 1);
                cout << "0. Sair" << endl;
                position(10, 1);
                cout << "Entre com a opcao :";
                cin >> opcao;
                cin.ignore(1000, '\n');
                switch (opcao){
                    case 1:
                        arquivo.buscarTodos();
                        limpa();
                        break;
                }
            } while (opcao != 0);
            return;
        }

        void pesquisarNome(){
            ARQUIVO arquivo;
            char nome[51];
            char tipo[5] = "NOME";
            limpa();
            position(1, 1);
            cout << "<Pesquisar por nome>";
            position(3, 1);
            cout << "Entre com o nome: "; cin.getline(nome, sizeof(nome));
            arquivo.pesquisarArquivo(tipo, nome);
            return;
        }

        void pesquisarDataNascimento(){
            ARQUIVO arquivo;
            char data[11];
            char tipo[5] = "DATA";
            limpa();
            position(1, 1);
            cout << "<Pesquisar por data de nascimento>";
            position(3, 1);
            cout << "Entre com o data: "; cin.getline(data, sizeof(data));
            arquivo.pesquisarArquivo(tipo, data);
            return;
        }

        void menu(void){
            int OPCAO;
            do {
                limpa();
                position(1, 1);
                cout << "<CRUD PESSOA>";
                position(2, 1);
                cout << "1. Cadastrar registro";
                position(3, 1);
                cout << "2. Pesquisar por nome";
                position(4, 1);
                cout << "3. Pesquisar por data de nascimento";
                position(5, 1);
                cout << "4. Remover registro";
                position(6, 1);
                cout << "5. Alterar registro";
                position(7, 1);
                cout << "6. Informacoes gerenciais";
                position(8, 1);
                cout << "0. Sair";
                position(10, 1);
                cout << "Por favor! Entre com a opcao desejada: "; cin >> OPCAO; cin.ignore(1000, '\n');
                switch (OPCAO){
                    case 1:
                        cadastrar();
                        break;

                    case 2:
                        pesquisarNome();
                        break;

                    case 3:
                        pesquisarDataNascimento();
                        break;

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

int main(void){
    cout << setiosflags (ios::uppercase);
    SISTEMA sistema;
    sistema.menu();
    return 0;
}
