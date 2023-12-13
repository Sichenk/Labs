-- Active: 1702374532296@@127.0.0.1@3306@games
SELECT * FROM games

SELECT 
`GameID` AS `id`,
`Title` AS `name` 
FROM games

SELECT 
`GameID` id,
`Title` game_names
FROM games

SELECT
`GameID` + `ReleaseYear` AS total 
FROM games

SELECT
`GameID`, `Title`, `Genre`
FROM games
WHERE `Genre` = 'Sandbox'

SELECT
`GameID` id, `Title` name, `ReleaseYear` year 
FROM games
WHERE `ReleaseYear` > 2013 AND `ReleaseYear` < 2019

SELECT
`GameID` id, `Title` name, `ReleaseYear` year 
FROM games
WHERE `ReleaseYear` BETWEEN 2013 AND 2019

SELECT *
FROM games
WHERE `Title` LIKE '%the%'

SELECT *
FROM games
WHERE `Title` LIKE 'the%'

SELECT *
FROM games
WHERE `Title` LIKE 'the%' OR `ReleaseYear` > 2019

SELECT *
FROM games
ORDER BY `ReleaseYear`

SELECT *
FROM games
ORDER BY `ReleaseYear` DESC
LIMIT 5

SELECT *
FROM games
ORDER BY `ReleaseYear` DESC
LIMIT 10, 15

SELECT 
    games.GameID,
    games.Title, 
    gamedevelopers.`DeveloperID`
FROM 
    games
JOIN 
    gamedevelopers ON gamedevelopers.GameID = games.GameID

SELECT 
    games.Title, 
    developers.DeveloperName
FROM 
    games
JOIN 
    gamedevelopers ON gamedevelopers.GameID = games.GameID
JOIN 
    developers ON developers.DeveloperID = gamedevelopers.DeveloperID

UPDATE `storage`
SET `DiskSpaceGB` = 5
WHERE `GameID` = 5

SELECT 
    games.Title, 
    `storage`.DiskSpaceGB,
    userreviews.`Rating`,
    graphics.`GraphicsQuality`
FROM 
    games
JOIN
    `storage` ON `storage`.`GameID`= games.GameID
JOIN
    userreviews ON userreviews.`GameID`= games.GameID
JOIN
    graphics ON graphics.`GameID`= games.GameID
WHERE userreviews.`Rating` >= 4
ORDER BY userreviews.`Rating` DESC
LIMIT 3

SELECT Genre, COUNT(*) `counter`
FROM Games
GROUP BY Genre
ORDER BY `counter` DESC

