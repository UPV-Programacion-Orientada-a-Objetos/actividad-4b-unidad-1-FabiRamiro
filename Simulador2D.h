#ifndef SIMULADOR2D_H
#define SIMULADOR2D_H

#include <iostream>

template <typename T>
class Simulador2D
{
private:
    T **_grid;
    int _filas;
    int _columnas;

    T *_fuentes;
    int _numFuentes;
    int _capacidadFuentes;

    float _constantes[3];

public:
    Simulador2D(int f, int c);
    ~Simulador2D();
    void redimensionarGrid(int nuevaF, int nuevaC);
    void agregarFuente(T valor);
    void simularPaso();

    void establecerValor(int fila, int col, T valor);
    T obtenerValor(int fila, int col) const;
    void imprimirGrid() const;
    int obtenerFilas() const { return _filas; }
    int obtenerColumnas() const { return _columnas; }
    int obtenerNumFuentes() const { return _numFuentes; }
};

template <typename T>
Simulador2D<T>::Simulador2D(int f, int c)
{
    _filas = f;
    _columnas = c;

    _grid = new T *[_filas];

    for (int i = 0; i < _filas; i++)
    {
        _grid[i] = new T[_columnas];

        for (int j = 0; j < _columnas; j++)
        {
            _grid[i][j] = static_cast<T>(0);
        }
    }

    _capacidadFuentes = 4;
    _numFuentes = 0;
    _fuentes = new T[_capacidadFuentes];

    _constantes[0] = 0.25f;
    _constantes[1] = 1.0f;
    _constantes[2] = 1.0f;

    std::cout << "Simulador creado: " << _filas << "x" << _columnas << " celdas\n";
}

template <typename T>
Simulador2D<T>::~Simulador2D()
{
    for (int i = 0; i < _filas; i++)
    {
        delete[] _grid[i];
    }

    delete[] _grid;

    delete[] _fuentes;

    std::cout << "Memoria liberada correctamente\n";
}

template <typename T>
void Simulador2D<T>::redimensionarGrid(int nuevaF, int nuevaC)
{
    std::cout << "Redimensionando de " << _filas << "x" << _columnas
              << " a " << nuevaF << "x" << nuevaC << "...\n";

    T **nuevoGrid = new T *[nuevaF];
    for (int i = 0; i < nuevaF; i++)
    {
        nuevoGrid[i] = new T[nuevaC];

        for (int j = 0; j < nuevaC; j++)
        {
            nuevoGrid[i][j] = static_cast<T>(0);
        }
    }

    int filasACopiar = (_filas < nuevaF) ? _filas : nuevaF;
    int columnasACopiar = (_columnas < nuevaC) ? _columnas : nuevaC;

    for (int i = 0; i < _filas; i++)
    {
        delete[] _grid[i];
    }
    delete[] _grid;

    _grid = nuevoGrid;
    _filas = nuevaF;
    _columnas = nuevaC;

    std::cout << "Redimension completada\n";
}

template <typename T>
void Simulador2D<T>::agregarFuente(T valor)
{
    if (_numFuentes >= _capacidadFuentes)
    {
        std::cout << "Vector de fuentes lleno asi que se expandira la capacidad\n";

        int nuevaCapacidad = _capacidadFuentes * 2;

        T *nuevosFuentes = new T[nuevaCapacidad];

        for (int i = 0; i < _numFuentes; i++)
        {
            nuevosFuentes[i] = _fuentes[i];
        }

        delete[] _fuentes;

        _fuentes = nuevosFuentes;
        _capacidadFuentes = nuevaCapacidad;

        std::cout << "Capacidad expandida a " << _capacidadFuentes << "\n";
    }

    _fuentes[_numFuentes] = valor;
    _numFuentes++;

    std::cout << "Fuente agregada (Valor: " << valor << "). Total: " << _numFuentes << "\n";
}

template <typename T>
void Simulador2D<T>::simularPaso()
{
    std::cout << "Vamos a simular el paso de difusion\n";

    T **temp = new T *[_filas];
    for (int i = 0; i < _filas; i++)
    {
        temp[i] = new T[_columnas];
    }

    for (int i = 0; i < _filas; i++)
    {
        for (int j = 0; j < _columnas; j++)
        {

            if (i == 0 || i == _filas - 1 || j == 0 || j == _columnas - 1)
            {
                temp[i][j] = _grid[i][j];
            }
            else
            {
                T arriba = _grid[i - 1][j];
                T abajo = _grid[i + 1][j];
                T izquierda = _grid[i][j - 1];
                T derecha = _grid[i][j + 1];

                temp[i][j] = (arriba + abajo + izquierda + derecha) / static_cast<T>(4);
            }
        }
    }

    for (int i = 0; i < _filas; i++)
    {
        for (int j = 0; j < _columnas; j++)
        {
            _grid[i][j] = temp[i][j];
        }
    }

    for (int i = 0; i < _filas; i++)
    {
        delete[] temp[i];
    }
    delete[] temp;

    std::cout << "Paso completado\n";
}

template <typename T>
void Simulador2D<T>::establecerValor(int fila, int col, T valor)
{
    if (fila >= 0 && fila < _filas && col >= 0 && col < _columnas)
    {
        _grid[fila][col] = valor;
    }
    else
    {
        std::cout << "Indice fuera de rango\n";
    }
}

template <typename T>
T Simulador2D<T>::obtenerValor(int fila, int col) const
{
    if (fila >= 0 && fila < _filas && col >= 0 && col < _columnas)
    {
        return _grid[fila][col];
    }
    return static_cast<T>(0);
}

template <typename T>
void Simulador2D<T>::imprimirGrid() const
{
    std::cout << "\n--- Grid Actual (" << _filas << "x" << _columnas << ") ---\n";
    for (int i = 0; i < _filas; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < _columnas; j++)
        {
            std::cout << _grid[i][j] << " | ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

#endif // SIMULADOR2D_H