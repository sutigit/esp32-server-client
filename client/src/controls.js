import axios from "axios";
import dotenv from "dotenv";
dotenv.config();

export const serverURL = `http://${process.env.SERVER_IP}:${process.env.SERVER_PORT}`;

export const blinkPin = async (pin) => {
  const esp32SafePins = [
    2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33,
  ];

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
