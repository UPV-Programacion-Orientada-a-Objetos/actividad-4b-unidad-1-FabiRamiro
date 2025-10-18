#include <iostream>
#include "Simulador2D.h"

void demostracionFloat()
{
    std::cout << "\n";
    std::cout << "DEMOSTRACION 1: SIMULADOR CON TIPO FLOAT \n";

    std::cout << " PASO 1: Creando simulador de 5x5\n";
    Simulador2D<float> sim(5, 5);

    std::cout << "\n PASO 2: Agregando fuentes al registro\n";
    sim.agregarFuente(100.0f);
    sim.agregarFuente(50.0f);
    sim.agregarFuente(75.0f);

    std::cout << "\n PASO 3: Estableciendo valores iniciales\n";
    std::cout << "   - Fuente 1 (100.0) en posición [2,2] (centro)\n";
    std::cout << "   - Fuente 2 (50.0) en posición [4,0] (esquina inferior izquierda)\n";
    sim.establecerValor(2, 2, 100.0f);
    sim.establecerValor(4, 0, 50.0f);

    std::cout << "\n ESTADO INICIAL (Paso 0):\n";
    sim.imprimirGrid();

    std::cout << "PASO 4: Simulando 3 pasos de difusion\n";
    for (int i = 1; i <= 3; i++)
    {
        std::cout << "\n--- Simulando Paso " << i << " ---\n";
        sim.simularPaso();
        std::cout << "\n Estado despues del Paso " << i << ":\n";
        sim.imprimirGrid();
    }

    std::cout << "PASO 5: Redimensionando a 7x7\n";
    sim.redimensionarGrid(7, 7);
    std::cout << "\n Grid redimensionado:\n";
    sim.imprimirGrid();

    std::cout << "\n Demostracion FLOAT completada\n";
}

void demostracionInt()
{
    std::cout << "\n";
    std::cout << "----- DEMOSTRACION 2: SIMULADOR CON TIPO INT -----\n";

    std::cout << " PASO 1: Creando simulador de 4x4\n";
    Simulador2D<int> sim(4, 4);

    std::cout << "\n PASO 2: Agregando fuentes al registro\n";
    sim.agregarFuente(80);
    sim.agregarFuente(40);

    std::cout << "\n PASO 3: Estableciendo valores iniciales\n";
    std::cout << "   - Fuente 1 (80) en posición [1,1]\n";
    std::cout << "   - Fuente 2 (40) en posición [2,2]\n";
    sim.establecerValor(1, 1, 80);
    sim.establecerValor(2, 2, 40);

    std::cout << "\n ESTADO INICIAL (Paso 0):\n";
    sim.imprimirGrid();

    std::cout << "PASO 4: Simulando 2 pasos de difusion\n";
    for (int i = 1; i <= 2; i++)
    {
        std::cout << "\n--- Simulando Paso " << i << " ---\n";
        sim.simularPaso();
        std::cout << "\n Estado despues del Paso " << i << ":\n";
        sim.imprimirGrid();
    }

    std::cout << "\n PASO 5: Probando expansion del vector de fuentes\n";
    std::cout << "   (Agregando 5 fuentes mas para forzar expansion)\n";
    for (int i = 1; i <= 5; i++)
    {
        sim.agregarFuente(i * 10);
    }
    std::cout << "   Total de fuentes: " << sim.obtenerNumFuentes() << "\n";

    std::cout << "\n Demostracion de INT completada\n";
}

void menuInteractivo()
{
    std::cout << "\n";
    std::cout << "MODO INTERACTIVO - SIMULADOR 2D \n";

    int filas, columnas;
    std::cout << "Ingrese numero de filas: ";
    std::cin >> filas;
    std::cout << "Ingrese numero de columnas: ";
    std::cin >> columnas;

    Simulador2D<float> sim(filas, columnas);

    int opcion;
    do
    {
        std::cout << "MENU DE OPCIONES\n";
        std::cout << "---------------------------------------\n";
        std::cout << "1. Establecer valor en celda \n";
        std::cout << "2. Simular un paso \n";
        std::cout << "3. Mostrar grid \n";
        std::cout << "4. Agregar fuente \n";
        std::cout << "5. Redimensionar grid \n";
        std::cout << "0. Salir \n";
        std::cout << "---------------------------------------\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            int f, c;
            float valor;
            std::cout << "Fila: ";
            std::cin >> f;
            std::cout << "Columna: ";
            std::cin >> c;
            std::cout << "Valor: ";
            std::cin >> valor;
            sim.establecerValor(f, c, valor);
            break;
        }
        case 2:
            sim.simularPaso();
            sim.imprimirGrid();
            break;
        case 3:
            sim.imprimirGrid();
            break;
        case 4:
        {
            float valor;
            std::cout << "Valor de la fuente: ";
            std::cin >> valor;
            sim.agregarFuente(valor);
            break;
        }
        case 5:
        {
            int nf, nc;
            std::cout << "Nuevas filas: ";
            std::cin >> nf;
            std::cout << "Nuevas columnas: ";
            std::cin >> nc;
            sim.redimensionarGrid(nf, nc);
            sim.imprimirGrid();
            break;
        }
        case 0:
            std::cout << "bye bye\n";
            break;
        default:
            std::cout << "Opcion incorrecta\n";
        }
    } while (opcion != 0);
}

int main()
{
    std::cout << "\n";
    std::cout << "----- SIMULADOR GENÉRICO DE FLUIDOS 2D -----\n";
    std::cout << "----- Modelado Físico de Difusión -----\n";

    int opcion;
    std::cout << "\nSeleccione modo de ejecucion:\n";
    std::cout << "1. Demostracion automatica (FLOAT)\n";
    std::cout << "2. Demostracion automatica (INT)\n";
    std::cout << "3. Modo interactivo\n";
    std::cout << "4. Ejecutar todas las demostraciones\n";
    std::cout << "Opcion: ";
    std::cin >> opcion;

    switch (opcion)
    {
    case 1:
        demostracionFloat();
        break;
    case 2:
        demostracionInt();
        break;
    case 3:
        menuInteractivo();
        break;
    case 4:
        demostracionFloat();
        demostracionInt();
        break;
    default:
        std::cout << "Ey ey opcion invalida tio, vamos a ejecutar la demostración FLOAT que esta por defecto\n";
        demostracionFloat();
    }

    std::cout << "----- PROGRAMA FINALIZADO EXITOSAMENTE -----\n";

    return 0;
}