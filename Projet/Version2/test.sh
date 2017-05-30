#!/bin/bash

x=100
bin/BAMV_LZW -c input/dicoAB.txt output/dicoAB_comp.txt
a=$(wc -c<input/dicoAB.txt)
b=$(wc -c<output/dicoAB_comp.txt)
echo""
echo "Pour le fichier dicoAB.txt :"
echo""
echo "Taille avant compression"
echo $a
echo "Taille apres compression"
echo $b
z="($x/$a)"
echo "Taux de compression"
echo "$z*$b" |bc -l 
bin/BAMV_LZW -x output/dicoAB_comp.txt output/dicoAB_decomp.txt
echo""
echo""
echo""
echo "Difference fichier avant/apres compression/decompression"
echo $(diff input/dicoAB.txt output/dicoAB_decomp.txt)

echo "----------------------------------------------"

bin/BAMV_LZW -c input/lorem_ipsum.txt output/lorem_ipsum_comp.txt
a=$(wc -c<input/lorem_ipsum.txt)
b=$(wc -c<output/lorem_ipsum_comp.txt)
echo""
echo "Pour le fichier lorem_ipsum.txt :"
echo""
echo "Taille avant compression"
echo $a
echo "Taille apres compression"
echo $b
z="($x/$a)"
echo "Taux de compression"
echo "$z*$b" |bc -l
bin/BAMV_LZW -x output/lorem_ipsum_comp.txt output/lorem_ipsum_decomp.txt
echo""
echo""
echo""
echo "Difference fichier avant/apres compression/decompression"
echo $(diff input/lorem_ipsum.txt output/lorem_ipsum_decomp.txt)