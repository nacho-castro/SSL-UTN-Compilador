# 🌟 **Trabajos Prácticos - Sintaxis y Semántica de los Lenguajes** 🌟

¡Bienvenido a mi repositorio! Acá encontrarás los trabajos prácticos que desarrollé durante la cursada de **Sintaxis y Semántica de los Lenguajes**. Cada proyecto aborda diferentes aspectos de lenguajes formales y programación, combinando teoría y práctica. 💻

---

## 🗂️ **Contenido**
1. [TP1 - Generador de Palabras de un Lenguaje Regular](#-tp1---generador-de-palabras-de-un-lenguaje-regular)
2. [TP2 - Expresiones Regulares y Extendidas](#-tp2---expresiones-regulares-y-extendidas)
3. [TP3 - Intérprete del Lenguaje MICRO](#-tp3---intérprete-del-lenguaje-micro)

---

## 📚 **Proyectos**

### 📝 **TP1 - Generador de Palabras de un Lenguaje Regular**
- **Descripción:** Programa en C que genera palabras a partir de una gramática regular ingresada por el usuario.
- **Habilidades aplicadas:**
  - Representación de gramáticas regulares.
  - Manejo de estructuras dinámicas en C.
  - Generación de cadenas en base a reglas.
- **Cómo ejecutarlo:**
  1. Ir al directorio `TP1`.
  2. Ejecutar el programa:  
     ```bash
     ./main.c
     ```
  3. Ingresar las reglas de la gramática según las indicaciones del programa.

---

### 🖥️ **TP2 - Expresiones Regulares y Extendidas**
- **Descripción:** Script en Bash que utiliza comandos de procesamiento de texto para manipular un archivo de texto llamado `breve_historia.txt`.
- **Habilidades aplicadas:**
  - Uso avanzado de herramientas como `grep` y `sed`.
  - Validación y transformación de texto en el shell.
- **Cómo ejecutarlo:**
  1. Ir al directorio `TP2`.
  2. Ejecútalo con:  
     ```bash
     ./script.sh
     ```
  3. Seguir las instrucciones en pantalla para probar diferentes patrones.

---

### 🔧 **TP3 - Intérprete del Lenguaje MICRO**
- **Descripción:** Desarrollo de un intérprete para el lenguaje MICRO utilizando **Flex** y **Bison**, integrados con lenguaje C.
- **Habilidades aplicadas:**
  - Análisis léxico con **Flex**.
  - Análisis sintáctico con **Bison**.
  - Construcción de un intérprete funcional para un lenguaje específico.
- **Cómo ejecutarlo:**
  1. Ir al directorio `TP3`.
  2. Generar los archivos necesarios:  
     ```bash
     flex scanner.l
     bison -d parser.y
     gcc -o micro parser.tab.c lex.yy.c TS.c
     ```
  3. Ejecutarlo:  
     ```bash
     ./micro
     ```
  4. Ingresar el código en lenguaje MICRO según las reglas soportadas.

---

## 💡 **Sobre la cursada**
Esta serie de trabajos prácticos representa la base de mi aprendizaje en la materia, cubriendo desde los fundamentos de lenguajes formales hasta el desarrollo de herramientas prácticas como intérpretes.

---

## 🛠️ **Tecnologías**
- Lenguaje C
- Bash scripting
- Flex y Bison

---

## 🤝 **Contribuciones**
Realizados en conjunto con mis compañeros de cursada. 

---

