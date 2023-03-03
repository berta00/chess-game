CREATE DATABASE chessGame;

CREATE USER 'chessGameUs'@'%' IDENTIFIED BY 'chess23CHESS';
GRANT ALL PRIVILEGES ON chessGame.* TO 'chessGameUs'@'%';
FLUSH PRIVILEGES;

USE chessGame;

CREATE TABLE waitLobbys (
	id      int          auto_increment,
	player1 varchar[255],
	player2 varchar[255],
	gameMod varchar[255],
	joinCd  int,

	PRIMARY KEY (id)
)
CREATE TABLE activeLobbys (
	id      int          auto_increment,
	player1 varchar[255] not null,
	player2 varchar[255] not null,
	gameMod varchar[255],
	joinCd  int          not null,

	PRIMARY KEY (id)
)
CREATE TABLE users (
	id      int          auto_increment,
	name    varchar[255] not null,
	gPlayed int          not null       default 0,
	jDate   date         not null,      default CURRENT_DATE();
)

