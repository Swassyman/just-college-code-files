import express from "express";

const app = express();
const PORT = 3000;

app.use(express.static("public"));

app.get("/", (req, res) => {
  res.send(`
    <html>
      <head>
        <link rel="stylesheet" href="/css/style.css">
      </head>
      <body>
        <h1>Hello, Static World!</h1>
        <img src="/images/cat.png" alt="cat" width="150"/>
      </body>
    </html>
  `);
});

app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});
