import express from "express";
import blinkRoute from "./routes/blink.js";
import testRoute from "./routes/test.js";
import dotenv from "dotenv";
dotenv.config();

const app = express();
const port = process.env.SERVER_PORT;

app.use(express.json());

app.use("/", testRoute);
app.use("/blink", blinkRoute);

app.listen(port, "0.0.0.0", () => {
  console.log(`Server listening at port ${port}`);
});
