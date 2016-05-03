#include "pattern.h"

#include <fstream>
#include <iostream>

void wait();

Pattern::Pattern()
{
    _width = 0;
    _height = 0;
    _size = 0;
    inputList = NULL;
}

Pattern::Pattern(const char *fileName)
{
    _width = 0;
    _height = 0;
    _size = 0;
    inputList = NULL;

    load(fileName);
}

Pattern::~Pattern() {}

void Pattern::load(const char *fileName)
{
    std::ifstream file;
    file.open(fileName);
    char input;

    IntList l;

    if(file.is_open())
    {
        while(!file.eof())
        {
            int value;
            file >> input;

            if(input=='#')       value =  1;
            else if(input=='.')  value = -1;
            else                 value =  0;

            l.push_back(value);
        }
    }

    l.pop_back();

    populate(l);

    file.close();
}

void Pattern::populate(IntList v)
{
    inputList = new int[v.size()];
    int i = 0;

    _size = v.size();

    for(IntList::iterator it = v.begin(); it != v.end(); ++it)
        inputList[i++] = *it;
}

int Pattern::size() const {return _size;}

int Pattern::input(int i) const
{
    if(i >= 0 and i <= _size)
        return inputList[i];

    std::cout << "Pattern: Erro - Indice fora da lista." << std::endl
              << " - Numero de unidades: " << _size << std::endl
              << " - Indice: " << i << std::endl;
    wait();

    return -2;
}

int Pattern::width() const {return _width;}
int Pattern::height() const {return _height;}

bool Pattern::set_dimensions(int x, int y)
{
    if(x > 0 and y > 0 and (x*y) == size())
    {
        _width = x;
        _height = y;
        return true;
    }

    std::cout << "Pattern: Erro - Inconsistencia de dimensoes." << std::endl
              << " - Tamanho do padrao: " << _size << std::endl
              << " - Largura inconsistente: " << x << std::endl
              << " - Altura inconsitente: " << y << std::endl;
    wait();

    return false;
}

void Pattern::completePrint()
{
    std::cout << "Unidades: " << _width*_height << std::endl;
    std::cout << "Largura: " << _width << std::endl;
    std::cout << "Altura: " << _height << std::endl;

    print();

    std::cout << std::endl << std::endl;
}

Vector Pattern::toVector() const
{
    Vector v(size());

    for(int i = 0; i < size(); ++i)
        v.set_value(i, input(i));

    return v;
}

void Pattern::print()
{
    for(int a = 0; a < size(); ++a)
	    std::cout << "  " << ( inputList[a] >= 0 ? " " : "") << inputList[a];
}

std::ostream &operator<<(std::ostream &output, const Pattern p)
{
	for(int a = 0; a < p.size(); ++a)
	{
	    std::cout << "  " << ( p.inputList[a] >= 0 ? " " : "") << p.inputList[a];
	    if((a+1) % p.width() == 0) std::cout << std::endl;
	}

	return output;
}
