FROM node:alpine

WORKDIR /src/web

# Install yarn
RUN apk update && apk add yarn

# Install app dependencies
COPY package.json .
COPY yarn.lock .

RUN yarn global add nodemon \
    && yarn install

# Bundle app source
COPY . .

CMD [ "nodemon", "index.js" ]
