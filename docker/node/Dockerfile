FROM node:alpine

WORKDIR /usr/app
# Copy only package.json file here so npm install is not invalidated
# during the docker build process of other files change
COPY ./package.json ./
RUN npm install

COPY ./ ./

CMD ["npm", "start"]

