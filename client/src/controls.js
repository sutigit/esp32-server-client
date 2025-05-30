import axios from "axios";
import dotenv from "dotenv";
dotenv.config();

export const serverURL = `http://${process.env.SERVER_IP}:${process.env.SERVER_PORT}`;

export const blinkPin = async (pin) => {
  const esp32SafePins = [14, 25, 26, 27, 32, 33, 34, 35, 37, 38, 39];

  if (!esp32SafePins.includes(pin)) {
    console.error(`Pin ${pin} is not a safe pin for blinking.`);
    return;
  }

  try {
    return await axios.post(`${serverURL}/blink`, { pin });
  } catch (error) {
    console.error("Error sending request:", error.message);
  }
};
