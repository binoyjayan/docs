
Build image
------------------------------------------------------------
docker build -t myweb:latest .

Run container
------------------------------------------------------------
docker run myweb:latest

Run container [ with port forwarding ]
------------------------------------------------------------
docker run -p 8080:8080 myweb:latest
docker run -p 5050:8080 myweb:latest

Run with name and cleanup
------------------------------------------------------------
docker run --name myweb  -p 8080:8080 myweb:latest
docker stop myweb
docker rm myweb
