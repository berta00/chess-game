package main

import (
	"log"
	"fmt"
	"net/http"
	"database/sql"
	_ "github.com/go-sql-driver/mysql"
)

// env vars
databaseIp   := "";
databasePort := "";
databaseUser := "chessGameUs";
databasePass := "";
databaseDb   := "chessGame";
databaseTbLobbyAtt := "waitLobbys";
databaseTbLobby    := "activeLobbys";

databaseConnString := databaseUser + ":" + databasePass + "@tcp(" + databaseIp + ":" + databasePort + ")/" + databaseDb;

// player1 is the creator
struct gameLobby (
	id      int,
	player1 String,
	player2 String,
	board   char[][]
);

func server(){
	http.HandleFunc("/", webHomePage);
	http.HandleFunc("/move", move);
	http.HandleFunc("/gameVersion", gameVersion);

	http.ListenAndServe(":8080", nil);
}

func webHomePage(w http.ResponseWriter, r *http.Request){
	fmt.Fprintf(w, "ChessOnline webserver homepage!");
}

func createLobby(w http.ResponseWriter, r *http.Request){
	switch(r.Method){
		case "POST":
			err := r.FormParse;
			if(err != nil){
				log.Fatal(err);
			}
			// get game data
			gameId := 0; // random number
			gamePlayer1 := r.Form.Get("player1Name");
			gamePlayer2 := "";
			gameBoard := [[]]; // get board from form
			// create lobby struct
			partita := gameLobby {
				id:      gameId,
				player1: gamePlayer1,
				player2: gamePlayer2,
				board:   gameBoard
			}
			// push it to db
			dbConn, err := sql.Open("mysql", databaseConnString);
			if err != nil {
				log.Fatal(err);
			}
			defer dbConn.Close();
			
			query := "INSERT INTO " + databaseTbLobbyAtt;
			// tell the host to wait for opponent

			break;
		default:
			fmt.Fprintf("Contact this route with post request");
			break;
	}
}

func joinLobby(w http.ResponseWriter, r *http.Request){
	switch(r.Method){
		case "POST":
			err := r.FormParse;
			if(err != nil){
				log.Fatal(err);
			}
			dbConn := 
			// get game id
			gameId := r.Form.Get("gameId");
			// see if it's avalible
			query := "SELECT * FROM gameLobby WHERE id=" + gameId + ";";
			
			// connect
			
			break;
		default:
			fmt.Fprintf("Contact this route with post request");
			break;
	}
}

func move(w http.ResponseWriter, r *http.Request){
	switch(r.Method){
		case "POST":
			// get the game id
			
			// browse and find the correct game

			// ceck and move

			// push in db the move

			break;
		default:
			fmt.Fprintf("Contact this server with post request");
			break;
	}
}

func gameVersion(w http.ResponseWriter, r *http.Request){
	// return the current version of the game
	fmt.Fprintf(w, "1.0.0");
}

func main(){
	server()
}
