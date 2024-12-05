#1a 
#Reemplace cada punto por punto y salto de línea generando un nuevo archivo.
sed 's/\./\.\n/g' breve_historia.txt > salida.txt

#1b
#Borre todas las líneas en blanco.
sed '/^$/d' breve_historia.txt > salida.txt

#1c
#Cree un nuevo archivo: “breve_historia_2.txt” con el resultado de las operaciones a y b 
#(redireccionamiento de la salida estándar)
sed 's/\./\.\n/g' breve_historia.txt > archivo.txt
sed '/^$/d' archivo.txt > breve_historia2.txt

#Alternativa 1c con pipeline
sed 's/\./\.\n/g' breve_historia.txt | sed '/^$/d' > breve_historia2.txt

#1d
#Liste todas las oraciones que contengan la palabra “independencia” sin distinguir mayúsculas y minúsculas.
grep -i -o "[^.]*independencia[^.]*\." breve_historia.txt

#1e
#Muestre las líneas que empiecen con “El” y terminen con “.” del archivo “breve_historia.txt”.
grep -o "^El.*\.$" breve_historia.txt

#1f
#Sobre el mismo archivo del punto anterior, Indique en cuántas oraciones aparece la palabra “peronismo”. Puede usar la opción -c para contar.
grep -o "^El.*\.$" breve_historia.txt | grep -c "peronismo"

#1g
#Muestre la cantidad de oraciones que contienen la palabra “Sarmiento” y la palabra “Rosas”.
grep -c -E "Sarmiento.*Rosas|Rosas.*Sarmiento" breve_historia.txt

#1h
#Muestre las oraciones que tengan fechas referidas al siglo XIX
grep -E "[^.]*18[0-9]{2}[^.]*\." breve_historia.txt

#1i 
#Borre la primera palabra de cada línea.
sed 's/^[^ ]* //g' breve_historia.txt 

#La alternativa presentada en el TP no funciono.
sed 's/^[[a-zA-Z]]*\b//g' breve_historia.txt

#1j
#Escriba un comando que enumere todos los archivos de una carpeta que contengan extensión “.txt”. (tip: pipe con el comando ls).
ls | grep '\.txt$' 

#Alternativa sin ls
dir *.txt
