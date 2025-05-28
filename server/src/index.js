import express from 'express';
import blinkRoute from './routes/blink.js';

const app = express();
const port = 3000;

app.use(express.json());

app.use('/blink', blinkRoute)

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
