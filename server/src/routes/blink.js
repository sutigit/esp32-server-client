import express from "express";
import axios from "axios";
import dotenv from "dotenv";
dotenv.config();

const router = express.Router();

router.post("/", async (req, res) => {
  const { pin } = req.body;

  try {
    const endpoint = `http://${process.env.ESP32_IP}/blink?p=${pin}`;
    const esp32res = await axios.get(endpoint);
    res.sendStatus(esp32res.status)

  } catch (error) {
    console.error("Error forwarding blink request:", error.message);
    return res.sendStatus(500);
  }
});

export default router;
