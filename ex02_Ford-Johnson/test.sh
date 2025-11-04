#!/bin/bash

# Fonction pour supprimer les codes de couleur ANSI
remove_colors() {
    echo "$1" | sed 's/\x1b\[[0-9;]*m//g'
}

# Tests avec des cas spécifiques
tests=(
	"5"
    "1 2 3 4"
    "10 5 7"
    "42 27"
    "454 5 5 87 875 565 6 56 56 555 747 787874 58"
	"1 1 1 1 1 1 1 1 1"
	"78 78 78 4 1 78 45 78 25 78"
)

for args in "${tests[@]}"; do
    echo "Test avec args: $args"

    # Lance le programme et capture toute la sortie
    output=$(./PmergeMe $args 2>&1)
    
    # Supprime les couleurs et extrait les chiffres après "After:"
    clean_output=$(remove_colors "$output")
    echo "$clean_output" | grep -i "after:" | sed 's/.*After:[[:space:]]*//' | sed 's/[[:space:]]*$//' | tr -s ' ' > prog_out.txt
    
    # Génère la sortie attendue
    echo "$args" | tr " " "\n" | sort -n | tr "\n" " " | sed 's/ $//' | tr -s ' ' > ref_out.txt

    # Compare
    if diff -w prog_out.txt ref_out.txt > /dev/null; then
        echo "✅ OK"
    else
        echo "❌ KO"
        echo "Programme: '$(cat prog_out.txt)'"
        echo "Attendu:  '$(cat ref_out.txt)'"
        echo "---"
    fi
done

# Test avec 30 nombres aléatoires
echo "Test avec 100000 nombres aléatoires"
numbers=$(shuf -i 1-1000 -n 1000 | tr '\n' ' ')
#echo "Nombres: $numbers"

output=$(./PmergeMe $numbers 2>&1)
clean_output=$(remove_colors "$output")
echo "$clean_output" | grep -i "after:" | sed 's/.*After:[[:space:]]*//' | sed 's/[[:space:]]*$//' | tr -s ' ' > prog_out.txt

echo "$numbers" | tr " " "\n" | sort -n | tr "\n" " " | sed 's/ $//' | tr -s ' ' > ref_out.txt

if diff -w prog_out.txt ref_out.txt > /dev/null; then
    echo "✅ OK"
else
    echo "❌ KO"
    echo "Différences:"
    diff -w prog_out.txt ref_out.txt
    echo "Programme: '$(cat prog_out.txt)'"
    echo "Attendu:  '$(cat ref_out.txt)'"
fi

# Nettoyage
rm -f prog_out.txt ref_out.txt