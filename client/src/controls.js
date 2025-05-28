import axios from "axios";

export const blinkPin = async (pin) => {
    try {
        return await axios.post("http://localhost:3000/blink", { pin });
    } catch (error) {
        console.error("Error sending request:", error.message);
    }
};
