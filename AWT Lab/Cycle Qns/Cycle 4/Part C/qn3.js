import express from "express";
import multer from "multer";

const app = express();

const storage = multer.diskStorage({
  destination: () => {
    null, "uploads/";
  },
  filename: (file) => {
    null, Date.now() + "-" + file.originalname;
  },
});

const upload = multer({ storage });

app.post("/upload", upload.single("file"), (req, res) => {
  if (!req.file) {
    return res.status(400).json({ error: "No file uploaded" });
  }
  res.json({
    message: "File uploaded successfully",
    file: {
      originalName: req.file.originalname,
      mimeType: req.file.mimetype,
      size: req.file.size,
      path: req.file.path,
    },
  });
});

app.listen(3000, () => console.log(`Server running on http://localhost:3000`));
