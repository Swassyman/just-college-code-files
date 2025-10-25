import express from "express";
import z from "zod";

const app = express();
app.use(express.json());

const userSchema = z.object({
  name: z.string().min(3),
  email: z.string(),
  age: z.number().int().min(18),
});

app.post("/users", (req, res, next) => {
  try {
    const validatedData = userSchema.parse(req.body);
    res.status(201).json({
      message: "User created successfully",
      data: validatedData,
    });
  } catch (err) {
    next(err); 
  }
});

app.use((err, req, res, next) => {
  if (err instanceof z.ZodError) {
    return res.status(400).json({
      error: "Validation failed"
    });
  }

  res.status(500).json({ error: "Internal Server Error" });
});

app.get("/", (req, res)=>{
    res.send({status: "active"});
});

app.listen(3000, () => console.log(`Server running on http://localhost:3000`));
