#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Função para ler o tempo de clock do Pipeline
float ler_tempo_clock() {
    float tempo_clock;
    cout << "Insira o tempo de clock do Pipeline: ";
    cin >> tempo_clock;
    return tempo_clock;
}

// Função para ler o arquivo de memória de instrução (ROM)
vector<string> ler_arquivo_rom() {
    string nome_arquivo;
    cout << "Digite o nome do arquivo com o programa em binário ou hexadecimal: ";
    cin >> nome_arquivo;
    ifstream arquivo(nome_arquivo);
    vector<string> instrucoes;
    if (arquivo.is_open()) {
        string linha;
        while (getline(arquivo, linha)) {
            instrucoes.push_back(linha);
        }
        arquivo.close();
    } else {
        cout << "Arquivo não encontrado." << endl;
    }
    return instrucoes;
}

// Função para identificar conflitos de dados e implementar a solução
vector<string> identificar_e_resolver_conflitos(const vector<string>& instrucoes) {
    cout << "Identificando e resolvendo conflitos de dados..." << endl;
    vector<string> instrucoes_modificadas;
    for (size_t i = 0; i < instrucoes.size(); ++i) {
        instrucoes_modificadas.push_back(instrucoes[i]);
        if (i < instrucoes.size() - 1) {
            // Verifica se a instrução atual e a próxima escrevem na memória
            if (instrucoes[i].substr(0, 2) == "AC" && instrucoes[i+1].substr(0, 2) == "AC") {
                cout << "Conflito de dados detectado entre as instruções " << i << " e " << i+1 << endl;
                // Conflito de dados detectado, insere NOPs
                instrucoes_modificadas.push_back("NOP");
                instrucoes_modificadas.push_back("NOP");
            }
        }
    }
    return instrucoes_modificadas;
}

// Função para calcular o sobrecusto em instruções da solução
int calcular_sobrecusto(const vector<string>& instrucoes, const vector<string>& instrucoes_modificadas) {
    int sobrecusto = instrucoes_modificadas.size() - instrucoes.size();
    return sobrecusto;
}

// Função para calcular o tempo de execução e o número de ciclos de programa
void calcular_tempo_ciclos(float tempo_clock, const vector<string>& instrucoes_modificadas, float& tempo_execucao, int& num_ciclos) {
    int num_instrucoes = instrucoes_modificadas.size();
    tempo_execucao = num_instrucoes * tempo_clock;
    num_ciclos = num_instrucoes;
}

// Função para gerar um novo arquivo com a aplicação da técnica
void gerar_novo_arquivo(const vector<string>& instrucoes_modificadas) {
    string nome_arquivo;
    cout << "Digite o nome do arquivo para salvar as instruções modificadas: ";
    cin >> nome_arquivo;
    ofstream novo_arquivo(nome_arquivo);
    if (novo_arquivo.is_open()) {
        for (const string& instrucao : instrucoes_modificadas) {
            novo_arquivo << instrucao << "\n";
        }
        novo_arquivo.close();
        cout << "Novo arquivo gerado com sucesso." << endl;
    } else {
        cout << "Erro ao criar o arquivo." << endl;
    }
}

// Função para exibir os resultados
void exibir_resultados(int sobrecusto, float tempo_execucao, int num_ciclos) {
    cout << "Sobrecusto em instruções: " << sobrecusto << endl;
    cout << "Tempo de execução: " << tempo_execucao << " segundos" << endl;
    cout << "Número de ciclos de programa: " << num_ciclos << endl;
}

// Função principal
int main() {
    float tempo_clock = ler_tempo_clock();
    if (tempo_clock <= 0) {
        cout << "O tempo de clock deve ser maior que zero." << endl;
        return 1;
    }
    vector<string> instrucoes = ler_arquivo_rom();
    if (instrucoes.empty()) {
        return 1;
    }
    vector<string> instrucoes_modificadas = identificar_e_resolver_conflitos(instrucoes);
    int sobrecusto = calcular_sobrecusto(instrucoes, instrucoes_modificadas);
    float tempo_execucao;
    int num_ciclos;
    calcular_tempo_ciclos(tempo_clock, instrucoes_modificadas, tempo_execucao, num_ciclos);
    gerar_novo_arquivo(instrucoes_modificadas);
    exibir_resultados(sobrecusto, tempo_execucao, num_ciclos);
    return 0;
}
