import dotenv from "dotenv";
dotenv.config();

const blinkRoute = (soc) => {
  return async (req, res) => {
    const { pin } = req.body;

    try {
      if (!pin) {
        console.error("Pin is required in the request body");
        return res.sendStatus(400);
      }

      const message = Buffer.from(pin.toString());
      soc.send(message, process.env.ESP32_PORT, process.env.ESP32_IP, (err) => {
        if (err) {
          console.error("Error sending blink command:", err.message);
          res.sendStatus(500);
        } else {
          console.log(`Blinking pin ${pin}`);
        }
      });

      res.sendStatus(200);
    } catch (error) {
      console.error("Error forwarding blink request:", error.message);
      return res.sendStatus(500);
    }
  };
};

export default blinkRoute;