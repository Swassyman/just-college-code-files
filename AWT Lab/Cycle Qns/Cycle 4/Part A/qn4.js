import express from "express";
const app = express();
const PORT = 3000;

app.get("/data", (req, res) => {
  res.send("This is a GET request");
});

app.put("/data", (req, res) => {
  res.send("This is a PUT request");
});

app.delete("/data", (req, res) => {
  res.send("This is a DELETE request");
});

app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}/`);
});
