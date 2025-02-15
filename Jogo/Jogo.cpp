#include <iostream>
#include <fstream>
#include <cstring>
#include <random>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ios_base;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

struct Carta
{
	char nome[30];
	unsigned idade, jogos, gols, titulos;
};

void Menu();

int main()
{
	system("chcp 1252 > nul");

	char nomeCab[8], op;
	unsigned short qtdCartas = 0;

	ifstream fin;
	fin.open("..\\baralho.bin", ios_base::in | ios_base::binary);
	if (!fin.is_open())
	{
		cout << "Não foi possível carregar o baralho." << endl;
		exit(EXIT_FAILURE);
	}

	fin.read((char*)nomeCab, sizeof(nomeCab));
	
	if (strcmp(nomeCab, "BARALHO"))
	{
		cout << "Arquivo não possui o formato esperado." << endl;
		fin.close();
		exit(EXIT_FAILURE);
	}

	fin.read((char*)&qtdCartas, sizeof(unsigned short));

	Carta* cartas = new Carta[qtdCartas];

	for (unsigned short i = 0; i < qtdCartas; ++i)
	{
		fin.read((char*)cartas[i].nome, sizeof(cartas[i].nome));
		fin.read((char*)&cartas[i].idade, sizeof(unsigned));
		fin.read((char*)&cartas[i].jogos, sizeof(unsigned));
		fin.read((char*)&cartas[i].gols, sizeof(unsigned));
		fin.read((char*)&cartas[i].titulos, sizeof(unsigned));
	}
	fin.close();

	Menu();
	cin >> op;
	op = tolower(op);
	while (op != 'n')
	{
		if (op == 's')
		{
			char jogador[2][20];
			Carta* cartasJogador[2][4];
			unsigned atributoJogador[2];
			unsigned short pontosJogador1 = 0, pontosJogador2 = 0;

			random_device rd;
			mt19937 mt(rd());
			uniform_int_distribution<int> dist(0, qtdCartas - 1);

			for (unsigned short i = 0; i < 2; ++i)
				for (unsigned short j = 0; j < 4; ++j)
					cartasJogador[i][j] = &cartas[dist(mt)];

			cout << "Jogador 1: ";
			cin >> jogador[0];
			cout << "Jogador 2: ";
			cin >> jogador[1];
			cout << "-----------" << endl;

			for (short i = 0; i < 4; ++i)
			{
				cout << endl;
				cout << "[" << jogador[i % 2] << "]" << endl;
				cout << "Carta: " << cartasJogador[i % 2][i]->nome << endl;
				cout << "1. Idade" << endl;
				cout << "2. Jogos" << endl;
				cout << "3. Gols" << endl;
				cout << "4. Títulos" << endl;
				cout << "Escolha atributo [_]" << '\b' << '\b';
				unsigned short opcao;
				cin >> opcao;

				cout << endl;
				
				for (short j = 0; j < 2; ++j)
				{
					cout << "[" << jogador[abs((i % 2) - (j % 2))] << "] " << cartasJogador[abs((i % 2) - (j % 2))][i]->nome << " | ";
					switch (opcao)
					{
					case 1:
						atributoJogador[abs((i % 2) - (j % 2))] = cartasJogador[abs((i % 2) - (j % 2))][i]->idade;
						break;
					case 2:
						atributoJogador[abs((i % 2) - (j % 2))] = cartasJogador[abs((i % 2) - (j % 2))][i]->jogos;
						break;
					case 3:
						atributoJogador[abs((i % 2) - (j % 2))] = cartasJogador[abs((i % 2) - (j % 2))][i]->gols;
						break;
					case 4:
						atributoJogador[abs((i % 2) - (j % 2))] = cartasJogador[abs((i % 2) - (j % 2))][i]->titulos;
						break;
					default:
						break;
					}
					cout << atributoJogador[abs((i % 2) - (j % 2))] << endl;
				}

				if (atributoJogador[0] > atributoJogador[1]) ++pontosJogador1;
				else if (atributoJogador[0] < atributoJogador[1]) ++pontosJogador2;
				else
				{
					++pontosJogador1;
					++pontosJogador2;
				}
				cout << endl;
				cout << "Placar: " << jogador[0] << " " << pontosJogador1 << " x " << pontosJogador2 << " " << jogador[1] << endl;
				cout << endl;
				cout << "------------------------" << endl;
			}
		}
		else cout << "Opção Inválida." << endl;

		Menu();
		cin >> op;
		op = tolower(op);
	}

	delete[] cartas;

	cout << "Tchau!" << endl;

	return 0;
}

void Menu()
{
	cout << endl;
	cout << "Super Trunfo Futebol" << endl;
	cout << "--------------------" << endl;
	cout << "Iniciar Nova Partida? [S/N] ";
}