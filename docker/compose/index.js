const express = require('express');
const redis = require('redis');
const process = require('process');

const app = express();
const client = redis.createClient({
    host: 'redis-server'
});
client.set('visits', 0);

app.get('/', (req, res) => {
    client.get('visits', (err, visits) => {
        res.send('<h1>Web visits: ' + visits + '<h1>');
        client.set('visits', parseInt(visits) + 1);
    });
});

app.get('/crash', (req, res) => {
    process.exit(1);
});

app.listen(8080, () => {
    console.log('Listening on port 8080');
});
