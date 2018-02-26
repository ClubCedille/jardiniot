#!/bin/bash

# Copyright 2018 Alexandre-Xavier Labonté-Lamoureux
#
# ISC License:
#
# Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided
# that the above copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
# CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

# Testé sur Debian GNU/Linux 9

# Le présent répertoire devient le répertoire de travail. Le script doit rester à la base du repo git.
cd $(dirname "$0")

# Vérifier si on est sur Debian
# TODO: Ajouter Ubuntu
if cat /etc/os-release | grep -q "NAME=\"Debian GNU/Linux\""; then
	# Vérifier si Doxygen et Graphviz sont déjà installés
	if command -v doxygen > /dev/null 2>&1; then
		if command -v dot > /dev/null 2>&1; then
			# Générer la config par défaut de Doxygen
			doxygen -g

			# Copier le README principal dans le fichier 'jardiniot-emb'
			cp README.md jardiniot-emb/MAIN.md

			# Modifier la config pour y mettre nos options
			sed -i 's/PROJECT_NAME           = "My Project"/PROJECT_NAME           = "JardinIoT"/g' Doxyfile
			sed -i 's/RECURSIVE              = NO/RECURSIVE              = YES/g' Doxyfile
			sed -i 's/PROJECT_BRIEF          =/PROJECT_BRIEF          = "Projet de jardin autonome"/g' Doxyfile
			sed -i 's/USE_MDFILE_AS_MAINPAGE =/USE_MDFILE_AS_MAINPAGE = MAIN.md"/g' Doxyfile
			sed -i 's/OUTPUT_DIRECTORY       =/OUTPUT_DIRECTORY       = "doc"/g' Doxyfile
			sed -i 's/INPUT                  =/INPUT                  = "jardiniot-emb"/g' Doxyfile

			# Générer le site web de documentation
			doxygen Doxyfile

			# Effacer le Doxyfile et autres fichiers temporaires
			rm Doxyfile
			rm jardiniot-emb/MAIN.md
		else
			echo "Veuillez installer 'graphviz' afin que les graphiques puissent être générés"
		fi
	else
		echo "Veuillez installer 'doxygen' afin de générer la documentation"
	fi
else
	echo "Distribution non supportée par ce script"
fi

echo "Script terminé"
