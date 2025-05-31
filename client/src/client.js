import { stdin as input } from "node:process";
import { blinkPin } from "./controls/blink.js";
import { testConnection } from "./controls/test.js";
import dotenv from "dotenv";
dotenv.config();

if (!input.isTTY) {
  console.error("stdin is not a TTY. This script must be run in a terminal.");
  process.exit(1);
}

input.setRawMode(true);
input.resume();
input.setEncoding("utf8");

console.log('Press "b" for blink or for "q" quits');

input.on("data", async (key) => {

  switch (key) {
    case "b":
      const pin = parseInt(process.env.PIN_NUM);
      await blinkPin(pin);
      break;

    case "t":
      console.log("Testing connection...");
      await testConnection();
      break;

    case "q":
      console.log("exit");
      process.exit();

    default:
      console.log('Invalid key, please press "b" or "q".');
  }
});
