import express from 'express';
const router = express.Router();

router.post('/', (req, res) => {
  const { pin } = req.body;
  console.log(`Blink requested on pin: ${pin}`);

  // Your logic here
  res.sendStatus(200);
});

export default router;
