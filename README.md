# Analizador de directorio

Visualizador y buscador de elementos en un directorio.

## Instalación

1. Clonar el repositorio

```sh
git clone https://github.com/Antoniel03/analizador-de-directorio.git
```

1. Estando en el directorio del repositorio, cambiar al directorio `build`.

```sh
cd build
```

2. Compilar

Para el GNU Compiler Collection (GCC)

```sh
make main
```

## Roadmap

- [x] Obtención de elementos en el directorio.
- [x] Jerarquía de archivos y carpetas.
- [x] Búsqueda.
  - [x] Por nombre.
  - [x] Por extensión.
- [x] Generado de HTML con información del directorio.
  - [x] Elementos del directorio.
  - [x] Información de carpetas.
    - [x] Número de archivos.
    - [x] Espacio total ocupado.
    - [x] Porcentaje de espacio total.
    - [x] Archivo de mayor tamaño.
- [ ] Interfaz de usuario basada en texto.
- [x] Interfaz de comandos basada en texto.
