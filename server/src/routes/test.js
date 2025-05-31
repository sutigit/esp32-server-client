import express from "express";
import axios from "axios";
import dotenv from "dotenv";
dotenv.config();

const router = express.Router();

router.get("/", async (req, res) => {

  console.log("Testing ESP32 connection...");

  try {
    const endpoint = `http://${process.env.ESP32_IP}`;
    const res = await axios.get(endpoint);

    console.log("Response from ESP32:", res.data);

  } catch (error) {
    console.error("Error forwarding blink request:", error.message);
    return res.status(500).send("Error forwarding blink request");
  }
});

export default router;