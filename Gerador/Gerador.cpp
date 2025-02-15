//#include "Gerador.h"

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios_base;

const unsigned short TAM_MAX = 32;

struct Carta
{
	char nome[30];
	unsigned idade, jogos, gols, titulos;
};

void Menu();
void Cadastrar(Carta*, unsigned short*);
void Importar(Carta[], unsigned short*);
void Alterar(Carta[], unsigned short*);
void Excluir(Carta[], unsigned short*);
void Listar(Carta[], unsigned short*);

int main()
{
	system("chcp 1252 > nul");

	char nomeCab[8] = "BARALHO", op = '\0';
	unsigned short qtdCartas = 0;
	Carta cartas[TAM_MAX];

	ifstream fin;
	fin.open("..\\baralho.bin", ios_base::in | ios_base::binary);
	if (fin.is_open())
	{
		fin.read((char*)nomeCab, sizeof(nomeCab));
		fin.read((char*)&qtdCartas, sizeof(unsigned short));

		for (unsigned short i = 0; i < qtdCartas; ++i)
		{
			fin.read((char*)&cartas[i].nome, sizeof(cartas[i].nome));
			fin.read((char*)&cartas[i].idade, sizeof(unsigned));
			fin.read((char*)&cartas[i].jogos, sizeof(unsigned));
			fin.read((char*)&cartas[i].gols, sizeof(unsigned));
			fin.read((char*)&cartas[i].titulos, sizeof(unsigned));
		}
	}
	fin.close();

	Menu();
	cin >> op;
	op = tolower(op);
	while (op != 's')
	{
		switch (op)
		{
			case 'c':
			case 'C':
				if (qtdCartas == 32) cout << "O baralho já atingiu sua capacidade máxima de " << TAM_MAX << " cartas." << endl;
				else Cadastrar(&cartas[qtdCartas], &qtdCartas);
				break;
			case 'i':
			case 'I':
				Importar(cartas, &qtdCartas);
				break;
			case 'a':
			case 'A':
				if (qtdCartas == 0) cout << "Não existem cartas no baralho." << endl;
				else Alterar(cartas, &qtdCartas);
				break;
			case 'e':
			case 'E':
				if (qtdCartas == 0) cout << "Não existem cartas no baralho." << endl;
				else Excluir(cartas, &qtdCartas);
				break;
			case 'l':
			case 'L':
				if (qtdCartas == 0) cout << "Não existem cartas no baralho." << endl;
				else Listar(cartas, &qtdCartas);
				break;
			default:
				cout << "Opção Inválida!" << endl;
				break;
		}

		Menu();
		cin >> op;
		op = tolower(op);
	}

	if (qtdCartas != 0)
	{
		ofstream fout;
		fout.open("..\\baralho.bin", ios_base::out | ios_base::trunc | ios_base::binary);
		if (!fout.is_open())
		{
			cout << "Falha ao abrir arquivo para gravação." << endl;
			exit(EXIT_FAILURE);
		}

		fout.write((char*)nomeCab, sizeof(nomeCab));
		fout.write((char*)&qtdCartas, sizeof(unsigned short));
		for (unsigned short i = 0; i < qtdCartas; ++i)
		{
			fout.write((char*)&cartas[i].nome, sizeof(cartas[i].nome));
			fout.write((char*)&cartas[i].idade, sizeof(unsigned));
			fout.write((char*)&cartas[i].jogos, sizeof(unsigned));
			fout.write((char*)&cartas[i].gols, sizeof(unsigned));
			fout.write((char*)&cartas[i].titulos, sizeof(unsigned));
		}
		fout.close();
	}

	cout << "Tchau!" << endl;

	return 0;
}

void Menu()
{
	cout << endl;
	cout << "Gerador de Cartas" << endl;
	cout << "-----------------" << endl;
	cout << "(C)adastrar" << endl;
	cout << "(I)mportar" << endl;
	cout << "(A)lterar" << endl;
	cout << "(E)xcluir" << endl;
	cout << "(L)istar" << endl;
	cout << "(S)air" << endl;
	cout << endl;
	cout << "Escolha uma opção [_]" << '\b' << '\b';
}

void Cadastrar(Carta* c, unsigned short* q)
{
	cout << endl;
	cout << "Cadastrar Carta" << endl;
	cout << "---------------" << endl;
	cout << "Nome    : ";
	cin >> c->nome;
	cout << "Idade   : ";
	cin >> c->idade;
	cout << "Jogos   : ";
	cin >> c->jogos;
	cout << "Gols    : ";
	cin >> c->gols;
	cout << "Títulos : ";
	cin >> c->titulos;
	++*q;
	cout << "Cadastro realizado com sucesso." << endl;
}

void Importar(Carta c[], unsigned short* q)
{
	if (*q == 32) cout << "O baralho já atingiu sua capacidade máxima de " << TAM_MAX << " cartas." << endl;
	else
	{
		char nomeArquivo[20];
		cout << endl;
		cout << "Importar Cartas" << endl;
		cout << "---------------" << endl;
		cout << "Arquivo: ";
		cin >> nomeArquivo;

		ifstream fin;
		fin.open(nomeArquivo, ios_base::in);
		if (!fin.is_open())
		{
			cout << "Falha ao abrir arquivo de importação." << endl;
			exit(EXIT_FAILURE);
		}
		
		cout << endl;
		cout << "Importando:" << endl;
		while (!fin.eof())
		{
			if (*q == 32)
			{
				cout << "O baralho já atingiu sua capacidade máxima de " << TAM_MAX << " cartas." << endl;
				cout << "Não foi possível importar todas as cartas." << endl;
				break;
			}
			else
			{
				fin >> c[*q].nome >> c[*q].idade >> c[*q].jogos >> c[*q].gols >> c[*q].titulos;
				cout << c[*q].nome << ' ' << c[*q].idade << ' ' << c[*q].jogos << ' ' << c[*q].gols << ' ' << c[*q].titulos << endl;
				++*q;
			}
		}
		fin.close();

		cout << "Importação realizada com sucesso;" << endl;
	}
}

void Alterar(Carta c[], unsigned short* q)
{
	unsigned short posicao;

	cout << endl;
	cout << "Atualizar Cartas" << endl;
	cout << "----------------" << endl;
	for (unsigned short i = 0; i < *q; ++i)
		cout << i + 1 << ") " << c[i].nome << endl;
	cout << endl;
	cout << "Digite o número da carta [_]" << '\b' << '\b';
	cin >> posicao;
	cout << endl;
	cout << "Alterando Carta: " << c[posicao - 1].nome << endl;
	cout << "Nome    : ";
	cin >> c[posicao - 1].nome;
	cout << "Idade   : ";
	cin >> c[posicao - 1].idade;
	cout << "Jogos   : ";
	cin >> c[posicao - 1].jogos;
	cout << "Gols    : ";
	cin >> c[posicao - 1].gols;
	cout << "Títulos : ";
	cin >> c[posicao - 1].titulos;
	cout << "Alteração realizada com sucesso." << endl;
}

void Excluir(Carta c[], unsigned short* q)
{
	unsigned short posicao;
	char nome[30];

	cout << endl;
	cout << "Excluir Carta" << endl;
	cout << "-------------" << endl;
	for (unsigned short i = 0; i < *q; ++i)
		cout << i + 1 << ") " << c[i].nome << endl;
	cout << endl;
	cout << "Digite o número da carta [_]" << '\b' << '\b';
	cin >> posicao;
	strcpy(nome, c[posicao - 1].nome);

	strcpy(c[posicao - 1].nome, c[*q - 1].nome);
	c[posicao - 1].idade = c[*q - 1].idade;
	c[posicao - 1].jogos = c[*q - 1].jogos;
	c[posicao - 1].gols = c[*q - 1].gols;
	c[posicao - 1].titulos = c[*q - 1].titulos;
	--*q;

	cout << endl;
	cout << "Carta " << nome << " foi excluída com sucesso." << endl;
}

void Listar(Carta c[], unsigned short* q)
{
	cout << endl;
	cout << "Cartas no Baralho" << endl;
	cout << "-----------------" << endl;
	for (unsigned short i = 0; i < *q; ++i)
		cout << "#" << i + 1 << ' ' << c[i].nome << '\t' << c[i].idade << '\t' << c[i].jogos << '\t' << c[i].gols << '\t' << c[i].titulos << endl;
}