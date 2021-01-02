
Generate a React project, build and start
------------------------------------------------------------
npx create-react-app frontend
cd frontend
npm run build
npm run start
Ctrl + C to stop

rm -rf build/node_modules   # Remove the dependencies

Create Dockerfile.dev in 'frontend'

Make changes
------------------------------------------------------------
Edit src/App.js

Starting container
------------------------------------------------------------
docker build -f Dockerfile.dev
docker run -it -p 3000:3000 CONTAINER_ID

Run tests in container
------------------------------------------------------------
docker run  -it -p 3000:3000 CONTAINER_ID npm run test   # New container for tests
docker exec -it -p 3000:3000 CONTAINER_ID npm run test   # Reuse existing container from docker compose

docker-compose up --build

If using the existing container and since volumes are mapped, the changes are reflected immediately

Note: If you use another service for running tests, you may not be able to use the terminal
      to interactively control the tests. This is because docker compose does not attach
      its container processes to the users terminal. 'docker attach' also cannot be used
      for this purpose since it attaches to the primary applications stdin/stdout/stderr.

Run with volumes
------------------------------------------------------------
docker run -it -p 3000:3000 -v /app/node_modules -v ${PWD}:/app

The '-v' switch without a colon tells docker to not remap that path

Fix while starting with docker compose
------------------------------------------------------------
reactapp:
  stdin_open: true

https://github.com/facebook/create-react-app/issues/8688


Older method [ deprecated ] to generate react project
------------------------------------------------------------
npm install -g create-react-app
create-react-app frontend

------------------------------------------------------------
npm commands
------------------------------------------------------------

npm run start  # Run a development server.
npm run test   # Test project tests
npm run build  # Builds a production application
npm run eject  # Removes everything

Reference
------------------------------------------------------------
https://create-react-app.dev/docs/getting-started#npx
https://reactjs.org/blog/2018/10/01/create-react-app-v2.html

