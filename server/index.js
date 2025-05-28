import express from 'express';

const app = express();
const port = 3000;

// Example data to send to ESP32
const sensorData = {
  temperature: 24.5,
  humidity: 60
};

// Route ESP32 will request
app.get('/data', (req, res) => {
  res.json(sensorData);
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
