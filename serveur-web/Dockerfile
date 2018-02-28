FROM node:alpine

WORKDIR /src/web

# Install yarn
<<<<<<< HEAD
RUN apk update && apk --no-cache add yarn
=======
RUN apk update && apk add yarn
>>>>>>> 73a32cb26b7a44e67a851af9580ac50951148a31

# Install app dependencies
COPY package.json .
COPY yarn.lock .

<<<<<<< HEAD
RUN yarn install
=======
RUN yarn global add nodemon \
    && yarn install
>>>>>>> 73a32cb26b7a44e67a851af9580ac50951148a31

# Bundle app source
COPY . .

<<<<<<< HEAD
CMD ./node_modules/nodemon/bin/nodemon.js 
=======
CMD [ "nodemon", "index.js" ]
>>>>>>> 73a32cb26b7a44e67a851af9580ac50951148a31
