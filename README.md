https://github.com/Fredplusplus10/caso_final_integrador_3.git
# caso_final_integrador_3


## CORRECIÓN DE ERRORES IGNACIO DE ROJAS IZQUIERDO ## 
Incoherencia en el archivo main.h:

1) No se ha incluido el archivo main.h, pero tampoco se utiliza ninguna función o declaración que pertenezca a ese archivo. Esto puede ser un error si el archivo tiene código necesario.
Falta de liberación de recursos (delete consoleBox):

2) La instancia global ConsoleBox* consoleBox no se libera correctamente, lo que puede llevar a una fuga de memoria.
Peligro de desbordamiento en filename:

3) Aunque se utiliza cin.getline, no hay garantía de que el tamaño del archivo no exceda el límite de 500 caracteres.
Uso incorrecto de fread:

4) La asignación buffer[bytes_read] = '\0'; puede generar errores si bytes_read alcanza el tamaño del búfer, ya que intentaría acceder fuera del rango.
Uso excesivo de using namespace std:

5) Es buena práctica evitar using namespace std en código global para prevenir conflictos de nombres.

## CAMBIOS REALIZADOS ##
Eliminado main.h:
No era necesario incluirlo.

Liberación de memoria:
Se agregó delete consoleBox en main() para evitar fugas de memoria.

Evitar desbordamientos:
Se usó std::getline en lugar de cin.getline.

Evitar errores de rango en buffer:
Se eliminó buffer[bytes_read] = '\0' y se reemplazó con script.append(buffer, bytes_read).

Corrección de using namespace std:
Se reemplazó con using específico de los elementos necesarios.

Comportamiento Esperado:
Este código corregido evita errores comunes, es seguro contra fugas de memoria y está más alineado con las buenas prácticas de C++. Asegúrate de probarlo con diferentes archivos para verificar su robustez.




Trabajos prácticos
1. Carga de scripts en tiny-lisp
El módulo Labmain.cpp define la función load_script(), que se utiliza para cargar un script en la memoria y aplicarle la coloración sintáctica. Esta función se basa en la librería estándar de C.

Implementa las funciones load_script() y load_script(filename, true) en CLion, de tal manera que puedas abrir y leer archivos de texto. El primer método toma el nombre de un archivo como entrada del usuario, mientras que el segundo muestra el contenido del archivo. Ambos métodos deben cargar el script en la consola.

void load_script(const char* filename, bool show_script = false);
void load_script();
2. Asegurando la robustez del código
Asegúrate de que tu código pueda manejar diferentes tipos de errores de entrada. Esto incluye, pero no se limita a:

El usuario proporciona un nombre de archivo que no existe.
El archivo proporcionado no se puede abrir por alguna razón.
Se produce un error de lectura durante la lectura del archivo.
Para manejar estos y otros errores potenciales, es posible que desees agregar comprobaciones de errores adicionales y manejar los fallos de manera más sofisticada.

Notas
Este ejercicio no requiere el uso de funciones seguras específicas de Microsoft (las funciones con sufijo _s). En cambio, deberías usar las funciones estándar de C/C++ disponibles en todas las plataformas y compiladores, como fopen, printf y scanf.


Rúbrica
Carga de scripts (50 puntos)

Se proporciona una implementación correcta de load_script(const char* filename, bool show_script = false) que carga correctamente el archivo dado y muestra su contenido si show_script es verdadero. (25 puntos)
Se proporciona una implementación correcta de load_script() que solicita al usuario un nombre de archivo, llama a la función load_script(const char* filename, bool show_script = false) y maneja cualquier error de manera apropiada. (25 puntos)
Manejo de errores (50 puntos)

El código tiene un manejo de errores sólido y completo para el caso de que el nombre del archivo proporcionado no exista. (15 puntos)
El código tiene un manejo de errores sólido y completo para el caso de que el archivo proporcionado no se pueda abrir por alguna razón. (15 puntos)
El código tiene un manejo de errores sólido y completo para el caso de que se produzca un error de lectura durante la lectura del archivo. (20 puntos)
Total: 100 puntos

Propuesta de solución
En CLion, las funciones seguras de la biblioteca estándar de C (*_s funciones) generalmente no están disponibles porque estas son específicas de Microsoft y no son estándar de C/C++. Por lo tanto, en lugar de utilizar funciones como fopen_s, printf_s y scanf_s, puedes usar sus equivalentes no seguros, que son fopen, printf y scanf.

A continuación se muestra cómo se podría reescribir el código para CLion:

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {/*...*/}
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox; // suponemos que ya está inicializado

void load_script(const char* filename, bool show_script = false)
{
    string script;
    FILE* f = nullptr;
    try
    {
        f = fopen(filename, "rb");
        if (!f)
        {
            cerr << "error de apertura de " << filename << endl;
            return;
        }

        int c;
        char buf[4001];
        while ((c = fread(buf, 1, 4000, f)) > 0)
        {
            buf[c] = 0;
            script.append(buf);
        }
        fclose(f);
        f = nullptr;

        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }
        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (...)
    {
        cerr << "error durante la lectura del archivo" << endl;
        if(f)
            fclose(f);
    }
}

void load_script()
{
    char filename[500];
    printf("Archivo: ");
    scanf("%499s", filename);
    load_script(filename, true);
}
Este código debería compilar y funcionar en CLion sin necesidad de agregar la directiva _CRT_SECURE_NO_WARNINGS, ya que no se están utilizando las versiones seguras específicas de Microsoft de las funciones de la biblioteca estándar de C.

Por último, ten en cuenta que este código no realiza una comprobación completa de errores y no es robusto contra varios tipos de errores de entrada. Dependiendo de tu caso de uso específico, es posible que desees agregar comprobaciones de errores adicionales y manejar los fallos de manera más sofisticada.

