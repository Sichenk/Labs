SELECT * FROM developers

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
ORDER BY ``ReleaseYear`` ASC

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