import axios from "axios";
import dotenv from "dotenv";
dotenv.config();

export const serverURL = `http://${process.env.SERVER_IP}:${process.env.SERVER_PORT}`;

export const testConnection = async () => {
  try {
    const res = await axios.get(`${serverURL}`);
    if (res.status === 200) {
      console.log("Connected to server successfully!");
    } else {
      console.error("Failed to connect to server.");
    }
  } catch (error) {
    console.error("Error connecting to server:", error.message);
  }
};

export const blinkPin = async (pin) => {
  const esp32SafePins = [13,14,15,18,19,25,26,27,32,33];

  if (!esp32SafePins.includes(pin)) {
    console.error(`Pin ${pin} does not exist or is not a safe pin for blinking.`);
    return;
  }

  try {
    const res = await axios.post(`${serverURL}/blink`, { pin });
    if (res.status === 200) {
      console.log(`Blink ${pin}!`);
    } 
  } catch (error) {
    console.error("Error sending request:", error.message);
  }
};
