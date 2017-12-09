// Lexical_Analyzer.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;
int lex_analyzer();
void main()
{
	if (lex_analyzer() == 1)
	{
		cout << "Successful Lexical Analyzer!" << endl;
		cout << "You can see the result in file (F:\\outf.txt)" << endl;
	}
	else
		cout << "It's a pity that lexical analyzer is not successful..." << endl;
}

int lex_analyzer()
{
	FILE *fin,*fout;
	int state = 0;

	char ch;
	char token[60];
	char *keyword[27] = {"include","iostream","define","main","void","abstract",
		"static","const","auto","double","int","float",
		"struct","long","unsigned","char","if","else",
		"switch","case","return","break" ,"for","while",
		"do","continue","print"};

	//open input and output files
	fin = fopen("F:\\inf.txt","r");
	if (fin == NULL)
	{
		cout << "The input file is not exist!" << endl;
		return 0;
	}
	fout = fopen("F:\\outf.txt", "w");
	if (fout == NULL)
	{
		cout << "The output file can not be created!" << endl;
		return 0;
	}

	int i, j;
	while (true)
	{
		switch (state)
		{
			case 0:
			{
				i = 1;
				for (int k = 0;k < 60;k++)
					token[k] = '\0';
				ch = getc(fin);
				if (ch == EOF)
					return 1;
				while (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r')
					ch = getc(fin);
				token[0] = ch;
				switch (ch)
				{
					case '>':
						ch = getc(fin);
						if (ch == '=')
						{
							token[1] = ch;
							state = 1;
						}
						else {
							ungetc(ch, fin);
							state = 1;
						}
						break;
					case '=':
						ch = getc(fin);
						if (ch == '=')
						{
							token[1] = ch;
							state = 1;
						}
						else {
							ungetc(ch, fin);
							state = 1;
						}
						break;
					case '<':
						ch = getc(fin);
						if (ch == '=')
						{
							token[1] = ch;
							state = 1;
						}
						if (ch == '<')
						{
							token[1] = ch;
							state = 2;
						}
						else {
							ungetc(ch, fin);
							state = 1;
						}
						break;
					case '+':
						ch = getc(fin);
						if (ch == '+')
						{
							token[1] = ch;
							state = 1;
						}
						else {
							ungetc(ch, fin);
							state = 1;
						}
						break;
					case '-':
						ch = getc(fin);
						if (ch == '-')
						{
							token[1] = ch;
							state = 1;
						}
						else {
							ungetc(ch, fin);
							state = 1;
						}
						break;
					case '*':
						state = 1;
						break;
					case '(':
						state = 1;
						break;
					case ')':
						state = 1;
						break;
					case '[':
						state = 1;
						break;
					case ']':
						state = 1;
						break;
					case '{':
						state = 1;
						break;
					case '}':
						state = 1;
						break;
					case ':':
						state = 2;
						break;
					case ',':
						state = 2;
						break;
					case ';':
						state = 2;
						break;
					case '#':
						state = 2;
						break;
					case '"':
						state = 2;
						break;
					default:
						if (isdigit(ch))
							state = 3;
						else
							if (isalpha(ch))
								state = 4;
						break;
				}
				break;
			}
			case 1:
				fprintf(fout, "%s\t---\t%s\n", token, "<operator>");
				state = 0;
				break;
			case 2:
				fprintf(fout, "%s\t---\t%s\n", token, "<delimiter>");
				state = 0;
				break;
			case 3:
				ch = getc(fin);
				while (isdigit(ch))
				{
					token[i++] = ch;
					ch = getc(fin);
				}
				if (ch == '.')
				{
					token[i++] = ch;
					ch = getc(fin);
					while (isdigit(ch))
					{
						token[i++] = ch;
						ch = getc(fin);
					}
				}
				ungetc(ch, fin);
				fprintf(fout, "%s\t---\t%s\n", token, "<num>");
				state = 0;
				break;
			case 4:
				ch = getc(fin);
				while (isalnum(ch))
				{
					token[i++] = ch;
					ch = getc(fin);
				}
				ungetc(ch,fin);
				for (j = 0;j < 27 && strcmp(token, keyword[j]);j++)
					;
				if(j==27)
					fprintf(fout, "%s\t---\t%s\n", token, "<id>");
				else
					fprintf(fout, "%s\t---\t%s\n", token, "<keyword>");
				state = 0;
				break;
		}
	}
	return 1;
}
