This project was bootstrapped with [Create React App](https://github.com/facebookincubator/create-react-app).

The _Create\_React\_App_ guide is available [here](https://github.com/facebookincubator/create-react-app/blob/master/packages/react-scripts/template/README.md).

## Dockerfile

Le frontend peut être utilisé en ayant seulement _docker_:

```sh
# docker build -t jardiniot-web:latest .
# docker run -it --name jardiniot-web -p 8080:8080 jardiniot-web:latest
```

Une variable de build/runtime est fournie, `CORS_URLS` pour changer les adresses permises par CORS.

- À la compilation: 
`docker build -t jardiniot-web:latest --build-arg CORS_URLS="'http://localhost:5000, https://domaine:port/chemin'"`

- Au runtime: `docker run -it --name jardiniot-web -p 8080:8080 -e CORS_URLS="'http://localhost:5000'" jardiniot-web:latest`

  ou alternativement: `export CORS_URLS=...; docker run -it -e CORS_URLS --name ...`
