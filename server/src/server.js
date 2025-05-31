import express from "express";
import dgram from "dgram";
import blinkRoute from "./routes/blink.js";
import dotenv from "dotenv";
dotenv.config();

const app = express();
const port = process.env.SERVER_PORT;
const soc = dgram.createSocket("udp4");

const shutdown = () => {
  console.log("\nShutting down...");
  soc.close(() => {
    console.log("UDP socket closed.");
    process.exit(0);
  });
}
process.on("SIGINT", shutdown);
process.on("SIGTERM", shutdown);

app.use(express.json());

app.use("/blink", blinkRoute(soc));

app.listen(port, "0.0.0.0", () => {
  console.log(`Server listening at port ${port}`);
});


