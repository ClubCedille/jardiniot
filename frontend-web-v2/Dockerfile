# Multi-stage build

# 1: Build l'application
FROM node:10.15-alpine as build

RUN mkdir /srv/web
WORKDIR /srv/web

COPY ./package.json package.json

RUN npm install --silent

COPY . .

RUN npm run build

# 2: Copier le proxy
FROM pierrezemb/gostatic:latest@sha256:27a9d727b2d17ef9cc14bc2fd361771a16fea175c17348b61e4ac5541f3c64ff \
 as proxy

# 3: Rebase sur busybox avec (spécifiquement) glibc pour Go
# Busybox est nécessaire pour avoir un shell pour interpréter les variables
# d'environnement dans le ENTRYPOINT
FROM busybox:glibc

copy --from=proxy /goStatic .

WORKDIR /

EXPOSE 8080

# Exposer une variable de build pour les adresses de CORS
ARG CORS_URLS='http://localhost:5000, http://api:5000'
ENV CORS_URLS CORS_URLS

COPY --from=build /srv/web/build .

# 4: Exposer l'application builder sous un dossier avec un mini serveur web static
ENTRYPOINT /goStatic -path "." -fallback "./index.html" -port "8080" \
                     -append-header "Access-Control-Allow-Methods: GET, POST, OPTIONS" \
                     -append-header "Access-Control-Allow-Origin: ${CORS_URLS}"
