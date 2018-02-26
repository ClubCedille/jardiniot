FROM node:alpine

WORKDIR /src/web

# Install yarn
RUN apk update && apk --no-cache add yarn

# Install app dependencies
COPY package.json .
COPY yarn.lock .

RUN yarn install

# Bundle app source
COPY . .

CMD ./node_modules/nodemon/bin/nodemon.js 
