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