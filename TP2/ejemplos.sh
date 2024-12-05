#!/bin/bash
nombre="Juan"
saludo="Hola $nombre"
echo $saludo

#Variable especial
echo $$

#Estructuras condicionales
num=6
if [[ $(($num % 2)) == 0 ]]
then
    echo Par
else
    echo Impar
fi

edad=67
case $edad in
    [0-1][0-8])
        echo "Menor"
        ;;
    2[0-9])
        echo "Joven"
        ;;
   [3-5][0-9])
        echo "Adulto"
        ;;
    *)
        echo "Mayor"
        ;;
esac

#Bucles
i=0
while [ $i -lt 4 ]
do
    echo 'Repetir'
    ((i++))
done

for ((i=1;i<=4;i++))
do
    echo "$i"
done

#Subprogramas
function suma(){
    local resultado=$(($1+$2)) #variable local
    echo $resultado
}
resultado=$(suma 3 2)
echo $resultado

funcion1(){
    echo $0 #nombre del script
    echo $# #cant. de argumentos recibidos
    echo $@ #todos los argumentos recibidos
    echo $$ #ID del proceso del script
    sum=$(($1+$2))
    echo $? #salida del ultimo proceso ejecutado
    echo $sum
    echo $?
}
funcion1 2 2 3
echo $?

