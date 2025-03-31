// Función para genera claves seguras.
#include <string>
#include <random>
#include <vector>
#include <random>
#include "fsys.hpp"




std::string pcm::GenerarClave(int longitud,
        bool digitos, bool signos)
{
    std::vector<char> numeros;
    std::vector<char> mayuscula;
    std::vector<char> minusculas;
    std::vector<char> signs;
    std::vector<int> indices;
    std::vector<int> desordenados;
    std::vector<bool> usados;
    std::string cadena;
    for (int i = 0; i < longitud; i++)
        cadena.push_back('#');

    std::random_device rd;  // semilla para el generador de números aleatorio.
    std::mt19937 gen(rd()); 

    // Generar números
    std::uniform_int_distribution<> distrib(48, 57); 

    for (int i = 0; i < longitud; i++)
    {
        auto c = distrib(gen);
        numeros.push_back(static_cast<char>(c));
    }

    // Generar mayúsculas
    std::uniform_int_distribution<> distrib2(65, 90);
    for (int i = 0; i < longitud; i++)
    {
        auto c = distrib2(gen);
        mayuscula.push_back(static_cast<char>(c));
    }

    // Generar minúsculas
    std::uniform_int_distribution<> distrib3(97, 122);
    for (int i = 0; i < longitud; i++)
    {
        auto c = distrib3(gen);
        minusculas.push_back(static_cast<char>(c));
    }

    // Generar signos.
    std::uniform_int_distribution<> distrib4(33, 47);
    for (int i = 0; i < longitud; i++)
    {
        auto c = distrib4(gen);
        signs.push_back(static_cast<char>(c));
    }

    // Generar números de 0 a longitud
    std::uniform_int_distribution<> distrib5(0, longitud -1);
    
    for (int i = 0; i < longitud; i++)
        usados.push_back(false);

    for (int i = 0; i < longitud; i++)
        indices.push_back(i);

    desordenados.reserve(longitud);

    // Desordenar indices.
    int index = 0;
    for (auto i = 0; i < longitud; i++)
    {
        do
        {
            index = distrib5(gen);
        }
        while (usados[index]);
        desordenados.push_back(indices[index]);
        usados[index] = true;
    }

    // Montar la cadena de salida.
    int M, m, s, n;
    if (signos)
    {
        s = 1;
        cadena[desordenados[1]] = signs[0];
    }
    else 
    {
        s = 0;
        cadena[desordenados[1]] = minusculas[0];
    }
    if (digitos)
    {
        cadena[desordenados[0]] = numeros[0];
        n = 1;
    }
    else 
    {
        cadena[desordenados[0]] = mayuscula[0];
        n = 0;
    }

    M = (longitud - s - n) / 3;
    m = longitud - s - n - M;

    for (int i = 2; i < 2 + m; i++)
        cadena[desordenados[i]] = minusculas[i];

    for (int i = 2 + m; i < longitud; i++)
        cadena[desordenados[i]] = mayuscula[i];

    return cadena;
}


// Programa de control
// int main(int argc, char *argv[])
// {
//     std::cout << pcm::GenerarClave(16) << std::endl;;
//     std::cout << pcm::GenerarClave(8) << std::endl;;
//     std::cout << pcm::GenerarClave(16, false) << std::endl;;
//     std::cout << pcm::GenerarClave(8, false, false) << std::endl;;
//     return 0;
// }
