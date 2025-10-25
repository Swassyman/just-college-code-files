import http from "http"

const server = http.createServer((req, res) => {
    res.setHeader("Content-Type", "text/plain");
    if (req.method === "GET") {
        res.write("There's nothing for you to get here");
    } else if (req.method === "POST") {
        res.write("No. You can't post here");
    } else {
        res.write("Hello");
    }
    res.end();
});

const PORT = 3001;

server.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`);
});
