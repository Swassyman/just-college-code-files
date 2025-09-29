import express from "express";

const app = express();
const PORT = 3000;

app.use(express.json());  
app.use(logger);          

app.get("/", (req, res) => {
  res.send("Hello from Express with middleware!");
});

app.post("/data", (req, res) => {
  res.json({ received: req.body });
});

function logger(req, res, next) {
  const now = new Date().toISOString();
  console.log(`[${now}] ${req.method} ${req.url}`);
  next();
}

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
