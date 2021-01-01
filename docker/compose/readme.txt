
Run containers from prebuilt images
------------------------------------------------------------
docker-compose up

Build image and run
------------------------------------------------------------
docker-compose up --build

Launch in background
------------------------------------------------------------
docker-compose up -d

Display statuses
------------------------------------------------------------
docker-compose ps

Stop only
------------------------------------------------------------
docker-compose stop

Stop and remove
------------------------------------------------------------
docker-compose down

Add restart policy to docker compose file
------------------------------------------------------------
node-app:
  restart: always

Restart policies
------------------------------------------------------------
'no'           : Do not attempt to restart
always         : Restart for any reason
never          : Restart only on failure
unless-stopped : Restart unless explicitly stopped

