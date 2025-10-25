import { Router } from "express";

const router = Router();

router.use((req, res, next) => {
  console.log(`[DATA ROUTER] ${req.method} ${req.originalUrl}`);
  next();
});

router.get("/info", (req, res) => {
  res.send("This is some information.");
});

export default router;
