#!/bin/bash

# Copyright 2018 Alexandre-Xavier Labonté-Lamoureux
#
# JardinIoT is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# JardinIoT is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with JardinIoT. If not, see <http://www.gnu.org/licenses/>.

# Testé sur Ubuntu, Debian GNU/Linux 9 et Manjaro Linux

# Le présent répertoire devient le répertoire de travail. Le script doit rester à la base du repo git.
cd $(dirname "$0")

# Vérifier si Doxygen et Graphviz sont déjà installés
if command -v doxygen > /dev/null 2>&1; then
	if command -v dot > /dev/null 2>&1; then
		# Générer la config par défaut de Doxygen
		doxygen -g

		# Copier le README principal dans le fichier 'jardiniot-emb'
		cp ../README.md MAIN.md

		# Modifier la config pour y mettre nos options
		sed -i 's/PROJECT_NAME           = "My Project"/PROJECT_NAME           = "JardinIoT"/g' Doxyfile
		sed -i 's/RECURSIVE              = NO/RECURSIVE              = YES/g' Doxyfile
		sed -i 's/PROJECT_BRIEF          =/PROJECT_BRIEF          = "Projet de jardin autonome"/g' Doxyfile
		sed -i 's/USE_MDFILE_AS_MAINPAGE =/USE_MDFILE_AS_MAINPAGE = MAIN.md"/g' Doxyfile
		sed -i 's/OUTPUT_DIRECTORY       =/OUTPUT_DIRECTORY       = "doc"/g' Doxyfile

		# Générer le site web de documentation
		doxygen Doxyfile

		# Effacer le Doxyfile et autres fichiers temporaires
		rm Doxyfile
		rm MAIN.md
	else
		echo "Veuillez installer 'graphviz' afin que les graphiques puissent être générés"
	fi
else
	echo "Veuillez installer 'doxygen' afin de générer la documentation"
fi

echo "Script terminé"
