import axios from "axios";
import dotenv from "dotenv";
dotenv.config();

export const serverURL = `http://${process.env.SERVER_IP}:${process.env.SERVER_PORT}`

export const blinkPin = async (pin) => {
    try {
        return await axios.post(`${serverURL}/blink`, { pin });
    } catch (error) {
        console.error("Error sending request:", error.message);
    }
};
