import express from "express";
import dataRouter from "./routes/data.js";

const app = express();
const PORT = 3000;

app.use("/data", dataRouter);

app.get("/", (req, res) => {
  res.send("Home page — try /data/info");
});

app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});
