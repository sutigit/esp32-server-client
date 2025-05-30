import { stdin as input } from "node:process";
import { blinkPin } from "./controls.js";
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
  if (key === "b") {
    
    const pin = parseInt(process.env.PIN_NUM);
    const res = await blinkPin(pin);

    if (res?.status === 200) console.log("blink!");
    

  } else if (key === "q") {
    console.log("exit");
    process.exit();
  } else {
    console.log('Invalid key, please press "b" or "q".');
  }
});
