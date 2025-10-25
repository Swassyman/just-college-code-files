import http from "http";

const server = http.createServer((req, res)=>{
    res.setHeader("Content-Type", "text/plain");
    res.write("Hello World!");
    res.end();
});

const PORT = 3001;

server.listen(PORT, ()=>{
    console.log(`Server listening on port ${PORT}`);
});