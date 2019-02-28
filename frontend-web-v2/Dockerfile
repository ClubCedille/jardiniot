# Multi-stage build

# 1: Build l'application
FROM node:10.15-alpine as build

RUN mkdir /srv/web
WORKDIR /srv/web

COPY ./package.json package.json

RUN npm install --silent

COPY . .

RUN npm run build

# 2: Exposer l'application builder sous un dossier avec un mini serveur web static
FROM pierrezemb/gostatic:latest@sha256:27a9d727b2d17ef9cc14bc2fd361771a16fea175c17348b61e4ac5541f3c64ff

WORKDIR /

EXPOSE 8080

COPY --from=build /srv/web/build .

ENTRYPOINT [ "/goStatic" \
           , "-path",          "." \
           , "-fallback",      "./index.html" \
           , "-port",          "8080" \
           , "-append-header", "Access-Control-Allow-methods: GET, POST, OPTIONS" \
           , "-append-header", "Access-Control-Allow-Origin: http://localhost:5000, http://api:5000" ]
