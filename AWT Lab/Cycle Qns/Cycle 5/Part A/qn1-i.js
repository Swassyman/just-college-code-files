import express from 'express';

const app = express();
const PORT = 3000;

app.use(express.json());

app.post("/data", (req, res) => {
  console.log(req.body);
  res.send(`Received: ${JSON.stringify(req.body)}`);
});

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});