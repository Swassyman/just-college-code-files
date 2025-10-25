import express from "express";
const app = express();
const PORT = 3000;

app.get("/", (req, res) => {
  res.send("Home Page");
});

app.get("/user/:id", (req, res) => {
  const { id }  = req.params;
  res.send(`User ID is ${id}`);
});

app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}/`);
});
