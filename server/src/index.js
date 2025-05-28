import express from 'express';
import blinkRoute from './routes/blink.js';

const app = express();
const port = 3000;

app.use(express.json());

app.use('/blink', blinkRoute)

app.listen(port, '0.0.0.0', () => {
  console.log(`Server listening at port ${port}`);
});
