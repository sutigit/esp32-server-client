import express from "express";
import axios from "axios";
import dotenv from "dotenv";
dotenv.config();

const router = express.Router();

router.post("/", async (req, res) => {
  const { pin } = req.body;
  console.log(`Blink requested on pin: ${pin}`);

  try {
    const endpoint = `http://${process.env.ESP32_IP}/blink?p=${pin}`;
    console.log(`${endpoint}`);

    const res = await axios.get(endpoint);
    console.log("Response from ESP32:", res.status);
    res.status(200).send("Pin blinked successfully on ESP32");

  } catch (error) {
    console.error("Error forwarding blink request:", error.message);
    return res.status(500).send("Error forwarding blink request");
  }
});

export default router;