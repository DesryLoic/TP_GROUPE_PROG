#!/bin/bash

# Se placer dans le dossier de ce script
cd "$(dirname "$0")"

# Chemin relatif vers l'ex�cutable
executable="../out/build/x64-debug/TP_GROUPE/TP_GROUPE_EX8.exe"

# Fichiers d'entr�e (ils doivent �tre dans le m�me dossier que l'ex�cutable)
fichierP1="5colis30capacite.txt"
fichierP2="4villes.txt"

# Vider le fichier r�sultat dans le dossier courant (celui de ce script)
> resultat.txt

# Lancer 20 r�plications
for graine in {1..20}
do
    "$executable" "$fichierP1" "$fichierP2" "$graine" >> resultat.txt
done
