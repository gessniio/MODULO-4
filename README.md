# MODULO-4
PROGRAMA PARA CONSULTA DE REPORTE. GRABA EN TXT
AUTENTICA 4 / SEMESTRE 2 (PROGRAMACION ESTRUCTURADA)

# 🖥️ MARVIN — Control de Visitantes (UNRC)

Sistema de control de visitantes para salas de cómputo, desarrollado en C++ con arreglos estáticos y manejo de archivos. Pensado como proyecto educativo de estructuras de datos básicas.

Manual: [https://sites.google.com/view/autentica4/modulo_4](https://sites.google.com/view/autentica4/modulo_4?authuser=0)

SE AGREGA MANUAL DE PROGRAMA 4 EN FORMATO WEB SENCILLO Y DE IGUAL MANERA EN FORMATO PODCATS.

---

## ¿Qué hace este programa?

Simula la administración diaria de una sala de cómputo:

| Función | Descripción |

| Ver equipos | Muestra qué equipos están disponibles u ocupados |
| Registrar visitante | Guarda ID, nombre y hora de entrada en una bitácora |
| Ver bitácora | Lista todos los visitantes registrados en el día |
| Generar reporte | Exporta la bitácora a un archivo `reporte_dia.txt` |
| Consultar reporte | Lee e imprime el archivo generado en pantalla |



## Estructura de datos

El programa usa **dos arreglos globales** en lugar de estructuras dinámicas:

```cpp
int  equipos[20];          // 0 = disponible, 1 = ocupado
char bitacora[10][3][50];  // [registro][campo][texto]
                           //  campo 0 → ID
                           //  campo 1 → Nombre
                           //  campo 2 → Hora de entrada
```

> ⚠️ La bitácora soporta **máximo 10 visitantes por sesión**. Al cerrar el programa, los datos en memoria se pierden (solo persiste el archivo `.txt`).

---

## Requisitos

- Compilador C++ con soporte **C++11 o superior**
- Compatible con: `g++`, `clang++`, MinGW (Windows), o cualquier IDE como Code::Blocks o Dev-C++

---

## Compilar y ejecutar

```bash
# Compilar
g++ -o marvin main.cpp

# Ejecutar
./marvin          # Linux / macOS
marvin.exe        # Windows
```

---

## Flujo típico de uso

```
1. Ejecutar el programa
2. Opción 2 → Registrar visitante (ID, nombre, hora)
   └─ Al terminar pregunta si asignar un equipo
3. Opción 1 → Ver qué equipos quedaron ocupados
4. Opción 3 → Ver bitácora del día en pantalla
5. Opción 4 → Guardar reporte en archivo .txt
6. Opción 6 → Salir
```

---

## Cosas importantes a saber

- **Los datos NO se guardan automáticamente.** Debes usar la opción 4 antes de salir si quieres conservar el registro.
- **El archivo `reporte_dia.txt`** se crea en la misma carpeta donde se ejecuta el programa. Se sobreescribe cada vez que usas la opción 4.
- **`cin.ignore()`** se usa en varios puntos para limpiar el buffer de entrada y evitar que `getline` se salte líneas. Es normal en C++ al mezclar `cin >>` con `cin.getline()`.
- El arreglo `bitacora` es un arreglo 3D de `char` (cadenas estilo C), no usa `std::string`. Esto es intencional para practicar manejo de strings en bajo nivel.
- No hay validación de formato en los campos (hora, ID). El usuario puede escribir cualquier texto.

---

## Posibles mejoras futuras

- [ ] Persistencia automática al iniciar (cargar bitácora desde archivo)
- [ ] Validación de formato de hora (HH:MM)
- [ ] Liberar equipo cuando el visitante se va
- [ ] Usar `std::string` y `std::vector` para eliminar los límites fijos
- [ ] Interfaz con fecha del sistema (`<ctime>`)


---

## 👨‍💻 Autor

**Marvin Valdez**
Ingeniero en Sistemas, Electronica y Electromecanica | Redes | Ciberseguridad | IA

---
---

## Tecnologías

![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=c%2B%2B&logoColor=white)
![File I/O](https://img.shields.io/badge/File_I/O-fstream-green?style=flat)
![Arrays](https://img.shields.io/badge/Estructuras-Arreglos_estáticos-orange?style=flat)
