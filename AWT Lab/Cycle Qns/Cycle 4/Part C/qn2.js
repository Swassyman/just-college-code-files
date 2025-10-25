import express from "express";

const app = express();
app.use(express.json());

app.post("/users", (req, res, next) => {
  const { name, email, age } = req.body;
  const errors = [];

  if (!name || typeof name !== "string" || name.length < 3) {
    errors.push({ message: "Name must be at least 3 characters" });
  }

  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  if (!email || typeof email !== "string" || !emailRegex.test(email)) {
    errors.push({ message: "Invalid email format" });
  }

  if (typeof age !== "number" || age < 18) {
    errors.push({ message: "Must be 18 or older" });
  }

  if (errors.length > 0) {
    return next({ type: "validation", details: errors });
  }

  res.status(201).json({
    message: "User created successfully",
    data: { name, email, age },
  });
});

app.use((err, req, res, next) => {
  console.error(`${req.method} ${req.url}`);
  console.error("Error stack:", err.stack || err);

  if (err.type === "validation") {
    return res.status(400).json({
      error: "Validation failed",
      details: err.details
    });
  }

  res.status(500).json({
    error: "Internal Server Error",
    message: err.message || "Unexpected error",
  });
});

app.listen(3000, () => console.log(`Server running on http://localhost:3000`));

