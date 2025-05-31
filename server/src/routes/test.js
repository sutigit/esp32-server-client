import express from "express";
import axios from "axios";
import dotenv from "dotenv";
dotenv.config();

const router = express.Router();

router.get("/", async (req, res) => {

  console.log("Testing ESP32 connection...");

  try {
    const endpoint = `http://${process.env.ESP32_IP}`;
    const esp32res = await axios.get(endpoint);
    res.sendStatus(esp32res.status);

  } catch (error) {
    console.error("Error forwarding blink request:", error.message);
    return res.sendStatus(500);
  }
});

export default router;