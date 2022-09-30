package main

import (
	"fmt"
	"net/http"
  "github.com/gorilla/websocket"
)

// handshake function to upgrade from http to websocket
var upgrader = websocket.Upgrader{}

func server(){
	http.HandleFunc("/", webHomePage);
	http.HandleFunc("/moveInput", moveWebsocket);

	http.ListenAndServe(":8080", nil);
}

func webHomePage(w http.ResponseWriter, r *http.Request){
	fmt.Fprintf(w, "ChessOnline webserver homepage!");
}

func moveWebsocket(w http.ResponseWriter, r *http.Request){
	// upgrade http to websocket handshake
	conn, err := upgrader.upgrade(w, r, nil);
	if err != nil {
		fmt.Println("error in websocket upgrade handshake");
		return
	}
	defer conn.Close()

	// continous read and write
	for {
		mt, message, err := conn.ReadMessage()

		fmt.Println("\n\nmessage: ", message, "\n\nmt: ", mt, "\n\n")
	}
}

func main(){
	server()
}
