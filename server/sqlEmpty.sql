USE chessGame;

DELETE FROM waitLobbys WHERE id >= 0;
DELETE FROM activeLobbys WHERE id >= 0;
DELETE FROM users WHERE id >= 0;

