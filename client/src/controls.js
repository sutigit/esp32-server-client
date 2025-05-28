import axios from "axios";

const serverIP = "192.168.0.112" // add server ip address here
const serverPort = "3000"; // add server port here


export const serverURL = `http://${serverIP}:${serverPort}`;

export const blinkPin = async (pin) => {
    try {
        return await axios.post(`${serverURL}/blink`, { pin });
    } catch (error) {
        console.error("Error sending request:", error.message);
    }
};
