import e from 'express';
import express from 'express';
import mongoose from "mongoose";

const app = express();
const PORT = 3000;

app.use(express.json());

const MONGO_URI = "mongodb+srv://230726:B23CSB67@study.gsyjs26.mongodb.net/?retryWrites=true&w=majority&appName=study"

mongoose.connect(MONGO_URI)
    .then(()=>{
        console.log("Connected to DB");
    })
    .catch(err =>{
        console.error("Not connected: ", err);
    });

const userSchema = new mongoose.Schema({
  name: { type: String, required: true },
  age: Number,
});

const User = mongoose.model("User", userSchema);

app.post("/users", async (req, res) => {
  try {
    const user = new User(req.body);
    await user.save();
    res.status(201).json(user);
  } catch (err) {
    res.status(400).json({ error: err.message });
  }
});

app.get("/users", async (req, res) => {
  const users = await User.find();
  res.json(users);
});

app.put("/users/:id", async (req, res) => {
  try {
    const user = await User.findByIdAndUpdate(req.params.id, req.body, { new: true });
    if (!user) return res.status(404).send("User not found");
    res.json(user);
  } catch {
    res.status(400).send("Invalid ID");
  }
});

app.delete("/users/:id", async (req, res) => {
  try {
    const user = await User.findByIdAndDelete(req.params.id);
    if (!user) return res.status(404).send("User not found");
    res.send("User deleted");
  } catch {
    res.status(400).send("Invalid ID");
  }
});

app.get('/', (req, res)=>{
    res.send("Hello World");
})

app.listen(PORT, ()=>{
    console.log(`Server running at http://localhost:${PORT}`);
})