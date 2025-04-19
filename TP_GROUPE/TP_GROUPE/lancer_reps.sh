#!/bin/bash

# Se placer dans le dossier de ce script
cd "$(dirname "$0")"

executable="../out/build/x64-debug/TP_GROUPE/TP_GROUPE_EX8.exe"

fichierP1="8colis40capacite.txt"
fichierP2="5villes.txt"

> resultat.txt


for graine in {1..20}
do
    "$executable" "$fichierP1" "$fichierP2" "$graine" >> resultat.txt
done
