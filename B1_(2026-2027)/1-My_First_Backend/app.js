const express = require('express');
const app = express();
const host = '0.0.0.0';
const port = 8080;
 
const songs = [
    "Fly Me to the Moon",
    "My Way",
    "New York, New York",
    "Strangers in the Night",
    "I've Got You Under My Skin",
    "That's Life",
    "The Way You Look Tonight",
    "Come Fly with Me",
    "Night and Day",
    "All or Nothing at All",
    "Summer Wind",
    "It Was a Very Good Year",
    "Luck Be a Lady",
    "Softly, As I Leave You",
    "Somethin' Stupid",
    "My Kind of Town",
    "Young at Heart",
    "In the Wee Small Hours of the Morning",
    "Witchcraft",
    "Love and Marriage"
];



app.get('/', (req, res) => {
    const randomSong = songs[Math.floor(Math.random() * songs.length)];
    res.send(randomSong);
});

app.get('/birth_date', (req, res) => {
    res.send('December 12, 1915');
});

app.get('/birth_city', (req, res) => {
    res.send('Hoboken, New Jersey');
});

app.get('/wives', (req, res) => {
    res.send('Nancy Barbato, Ava Gardner, Mia Farrow, Barbara Marx');
});

app.get('/picture', (req, res) => {
    res.redirect('https://en.wikipedia.org/wiki/Frank_Sinatra#/media/File:Frank_Sinatra2,_Pal_Joey.jpg');
});

app.get('/public', (req, res) => {
  res.send('Everybody can see this page');
})

app.get('/protected', (req, res) => {
    const authHeader = req.headers.authorization;

    if (!authHeader || !authHeader.startsWith('Basic')) {
      res.set('WWW-Authenticate', 'Basic realm="Restricted Area"');
      return res.status(401).send('Not Authorized.');
    }

    const base64Credentials = authHeader.split(' ')[1]; 
    const credentials = Buffer.from(base64Credentials, 'base64').toString('utf-8'); 
    const [username, password] = credentials.split(':');

    if (username === 'admin' && password === 'admin') {
      return res.send('Welcome, authenticated client');
    }

    res.set('WWW-Authenticate', 'Basic realm="Restricted Area"');
    return res.status(401).send('Not Authorized');
});

app.listen(port, () => {
    console.log("Server Started on http://", host, ":", port);
});