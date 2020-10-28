package main

import (
    "fmt"
    "net/http"
)

func main() {
    http.HandleFunc("/", HelloServer)
    http.ListenAndServe(":8080", nil)
}

func HelloServer(response http.ResponseWriter, request *http.Request) {
    fmt.Fprintf(response, "Hello, %s!", request.URL.Path[1:])
}

