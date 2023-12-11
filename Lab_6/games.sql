-- Active: 1694931223525@@127.0.0.1@3306@games

CREATE TABLE Games (
    GameID INT PRIMARY KEY,
    Title VARCHAR(200) NOT NULL,
    Genre VARCHAR(50),
    ReleaseYear INT,
    Platform VARCHAR(200)
);
CREATE TABLE Developers (
    DeveloperID INT PRIMARY KEY,
    DeveloperName VARCHAR(100) NOT NULL,
    HeadquartersLocation VARCHAR(100)
),
CREATE TABLE GameDevelopers (
    GameID INT,
    DeveloperID INT,
    PRIMARY KEY (GameID, DeveloperID),
    FOREIGN KEY (GameID) REFERENCES Games(GameID),
    FOREIGN KEY (DeveloperID) REFERENCES Developers(DeveloperID)
);

INSERT INTO Games (GameID, Title, Genre, ReleaseYear, Platform)
VALUES
    (1, 'The Witcher 3: Wild Hunt', 'Action RPG', 2015, 'PC, PlayStation 4, Xbox One'),
    (2, 'Counter-Strike: Global Offensive', 'First-person shooter', 2012, 'PC'),
    (3, 'The Legend of Zelda: Breath of the Wild', 'Action-adventure', 2017, 'Nintendo Switch, Wii U'),
    (4, 'Fortnite', 'Battle Royale', 2017, 'PC, PlayStation 4, Xbox One, Nintendo Switch, Mobile'),
    (5, 'Minecraft', 'Sandbox', 2011, 'PC, PlayStation 4, Xbox One, Nintendo Switch, Mobile'),
    (6, 'Grand Theft Auto V', 'Action-adventure', 2013, 'PC, PlayStation 4, Xbox One, PlayStation 3, Xbox 360'),
    (7, 'Overwatch', 'First-person shooter', 2016, 'PC, PlayStation 4, Xbox One'),
    (8, 'League of Legends', 'MOBA', 2009, 'PC'),
    (9, 'Red Dead Redemption 2', 'Action-adventure', 2018, 'PC, PlayStation 4, Xbox One'),
    (10, 'Dota 2', 'MOBA', 2013, 'PC'),
    (11, 'Fallout 4', 'Action RPG', 2015, 'PC, PlayStation 4, Xbox One'),
    (12, 'Among Us', 'Party', 2018, 'PC, iOS, Android'),
    (13, 'Rocket League', 'Sports', 2015, 'PC, PlayStation 4, Xbox One, Nintendo Switch'),
    (14, 'Cyberpunk 2077', 'Action RPG', 2020, 'PC, PlayStation 4, Xbox One'),
    (15, 'Apex Legends', 'Battle Royale', 2019, 'PC, PlayStation 4, Xbox One'),
    (16, 'World of Warcraft', 'MMORPG', 2004, 'PC'),
    (17, 'Genshin Impact', 'Action RPG', 2020, 'PC, PlayStation 4, iOS, Android'),
    (18, 'The Elder Scrolls V: Skyrim', 'Action RPG', 2011, 'PC, PlayStation 4, Xbox One'),
    (19, 'Among Us', 'Party', 2018, 'PC, iOS, Android'),
    (20, 'Rainbow Six Siege', 'Tactical shooter', 2015, 'PC, PlayStation 4, Xbox One'),
    (21, 'FIFA 21', 'Sports', 2020, 'PC, PlayStation 4, Xbox One'),
    (22, 'Assassin\'s Creed Valhalla', 'Action-adventure', 2020, 'PC, PlayStation 4, Xbox One'),
    (23, 'Call of Duty: Warzone', 'Battle Royale', 2020, 'PC, PlayStation 4, Xbox One'),
    (24, 'Monster Hunter: World', 'Action RPG', 2018, 'PC, PlayStation 4, Xbox One'),
    (25, 'Sekiro: Shadows Die Twice', 'Action-adventure', 2019, 'PC, PlayStation 4, Xbox One'),
    (26, 'Dead by Daylight', 'Survival horror', 2016, 'PC, PlayStation 4, Xbox One, Nintendo Switch, iOS, Android'),
    (27, 'Terraria', 'Sandbox', 2011, 'PC, PlayStation 4, Xbox One, Nintendo Switch, iOS, Android'),
    (28, 'Star Wars Jedi: Fallen Order', 'Action-adventure', 2019, 'PC, PlayStation 4, Xbox One'),
    (29, 'Civilization VI', 'Turn-based strategy', 2016, 'PC, iOS, Nintendo Switch'),
    (30, 'Hades', 'Action RPG', 2020, 'PC, Nintendo Switch'),
    (31, 'Destiny 2', 'First-person shooter', 2017, 'PC, PlayStation 4, Xbox One, Stadia'),
    (32, 'No Man\'s Sky', 'Action-adventure', 2016, 'PC, PlayStation 4, Xbox One'),
    (33, 'Resident Evil Village', 'Survival horror', 2021, 'PC, PlayStation 4, PlayStation 5, Xbox One, Xbox Series X/S'),
    (34, 'Hollow Knight', 'Metroidvania', 2017, 'PC, PlayStation 4, Xbox One, Nintendo Switch'),
    (35, 'The Sims 4', 'Life simulation', 2014, 'PC, PlayStation 4, Xbox One'),
    (36, 'Warframe', 'Action RPG', 2013, 'PC, PlayStation 4, Xbox One, Nintendo Switch'),
    (37, 'Among Us', 'Party', 2018, 'PC, iOS, Android'),
    (38, 'Rust', 'Survival', 2018, 'PC, PlayStation 4, Xbox One'),
    (39, 'The Last of Us Part II', 'Action-adventure', 2020, 'PlayStation 4, PlayStation 5'),
    (40, 'GTA Online', 'Action-adventure', 2013, 'PC, PlayStation 4, Xbox One, PlayStation 3, Xbox 360'),
    (41, 'Mortal Kombat 11', 'Fighting', 2019, 'PC, PlayStation 4, Xbox One, Nintendo Switch'),
    (42, 'StarCraft II', 'Real-time strategy', 2010, 'PC'),
    (43, 'The Outer Worlds', 'Action RPG', 2019, 'PC, PlayStation 4, Xbox One, Nintendo Switch'),
    (44, 'Among Us', 'Party', 2018, 'PC, iOS, Android'),
    (45, 'Fall Guys: Ultimate Knockout', 'Battle Royale', 2020, 'PC, PlayStation 4'),
    (46, 'Cyberpunk 2077', 'Action RPG', 2020, 'PC, PlayStation 4, Xbox One'),
    (47, 'DOOM Eternal', 'First-person shooter', 2020, 'PC, PlayStation 4, Xbox One'),
    (48, 'Cities: Skylines', 'City-building', 2015, 'PC, PlayStation 4, Xbox One, Nintendo Switch'),
    (49, 'Persona 5', 'Role-playing', 2016, 'PlayStation 4'),
    (50, 'Subnautica', 'Survival', 2018, 'PC, PlayStation 4, Xbox One');

DELETE FROM Developers;

INSERT INTO Developers (DeveloperID, DeveloperName, HeadquartersLocation)
VALUES
    (1, 'CD Projekt', 'Warsaw, Poland'),
    (2, 'Valve Corporation', 'Bellevue, Washington, USA'),
    (3, 'Nintendo EPD', 'Kyoto, Japan'),
    (4, 'Epic Games', 'Cary, North Carolina, USA'),
    (5, 'Mojang Studios', 'Stockholm, Sweden'),
    (6, 'Rockstar North', 'Edinburgh, Scotland'),
    (7, 'Blizzard Entertainment', 'Irvine, California, USA'),
    (8, 'Riot Games', 'Los Angeles, California, USA'),
    (9, 'Bethesda Game Studios', 'Rockville, Maryland, USA'),
    (10, 'InnerSloth', 'Forestville, California, USA'),
    (11, 'Psyonix', 'San Diego, California, USA'),
    (12, 'Respawn Entertainment', 'Los Angeles, California, USA'),
    (13, 'miHoYo', 'Shanghai, China'),
    (14, 'Ubisoft Montreal', 'Montreal, Canada'),
    (15, 'EA Vancouver', 'Vancouver, Canada'),
    (16, 'Infinity Ward', 'Woodland Hills, California, USA'),
    (17, 'Capcom', 'Osaka, Japan'),
    (18, 'FromSoftware', 'Tokyo, Japan'),
    (19, 'Behaviour Interactive', 'Montreal, Canada'),
    (20, 'Re-Logic', 'Indiana, USA'),
    (21, 'Firaxis Games', 'Hunt Valley, Maryland, USA'),
    (22, 'Supergiant Games', 'San Francisco, California, USA'),
    (23, 'Bungie', 'Bellevue, Washington, USA'),
    (24, 'Hello Games', 'Guildford, United Kingdom'),
    (25, 'Team Cherry', 'Adelaide, Australia'),
    (26, 'Maxis', 'Redwood City, California, USA'),
    (27, 'Digital Extremes', 'London, Ontario, Canada'),
    (28, 'Facepunch Studios', 'Walsall, United Kingdom'),
    (29, 'Naughty Dog', 'Santa Monica, California, USA'),
    (30, 'NetherRealm Studios', 'Chicago, Illinois, USA'),
    (31, 'Obsidian Entertainment', 'Irvine, California, USA'),
    (32, 'Mediatonic', 'London, United Kingdom'),
    (33, 'id Software', 'Richardson, Texas, USA'),
    (34, 'Colossal Order', 'Tampere, Finland'),
    (35, 'Atlus', 'Tokyo, Japan'),
    (36, 'Unknown Worlds Entertainment', 'San Francisco, California, USA');

    DELETE FROM GameDevelopers;
    INSERT INTO GameDevelopers (GameID, DeveloperID)
    VALUES
    (1, 1),   -- The Witcher 3: Wild Hunt (CD Projekt)
    (2, 2),   -- Counter-Strike: Global Offensive (Valve Corporation)
    (3, 3),   -- The Legend of Zelda: Breath of the Wild (Nintendo EPD)
    (4, 4),   -- Fortnite (Epic Games)
    (5, 5),   -- Minecraft (Mojang Studios)
    (6, 6),   -- Grand Theft Auto V (Rockstar North)
    (7, 7),   -- Overwatch (Blizzard Entertainment)
    (8, 8),   -- League of Legends (Riot Games)
    (9, 6),   -- Red Dead Redemption 2 (Rockstar North)
    (10, 10), -- Dota 2 (Valve Corporation)
    (11, 11), -- Fallout 4 (Bethesda Game Studios)
    (12, 12), -- Among Us (InnerSloth)
    (13, 13), -- Rocket League (Psyonix)
    (14, 1),  -- Cyberpunk 2077 (CD Projekt)
    (15, 14), -- Apex Legends (Respawn Entertainment)
    (16, 7),  -- World of Warcraft (Blizzard Entertainment)
    (17, 13), -- Genshin Impact (miHoYo)
    (18, 9),  -- The Elder Scrolls V: Skyrim (Bethesda Game Studios)
    (19, 12), -- Among Us (InnerSloth)
    (20, 15), -- Rainbow Six Siege (Ubisoft Montreal)
    (21, 16), -- FIFA 21 (EA Vancouver)
    (22, 9),  -- Assassin's Creed Valhalla (Bethesda Game Studios)
    (23, 17), -- Call of Duty: Warzone (Capcom)
    (24, 18), -- Monster Hunter: World (Capcom)
    (25, 18), -- Sekiro: Shadows Die Twice (FromSoftware)
    (26, 19), -- Dead by Daylight (Behaviour Interactive)
    (27, 20), -- Terraria (Re-Logic)
    (28, 6),  -- Star Wars Jedi: Fallen Order (Rockstar North)
    (29, 21), -- Civilization VI (Firaxis Games)
    (30, 22), -- Hades (Supergiant Games)
    (31, 23), -- Destiny 2 (Bungie)
    (32, 24), -- No Man's Sky (Hello Games)
    (33, 25), -- Resident Evil Village (Capcom)
    (34, 26), -- Hollow Knight (Team Cherry)
    (35, 27), -- The Sims 4 (Maxis)
    (36, 28), -- Warframe (Facepunch Studios)
    (37, 12), -- Among Us (InnerSloth)
    (38, 28), -- Rust (Facepunch Studios)
    (39, 29),  -- The Last of Us Part II (Naughty Dog)
    (40, 6),  -- GTA Online (Rockstar North)
    (41, 30), -- Mortal Kombat 11 (NetherRealm Studios)
    (42, 7),  -- StarCraft II (Blizzard Entertainment)
    (43, 31), -- The Outer Worlds (Obsidian Entertainment)
    (44, 12), -- Among Us (InnerSloth)
    (45, 32), -- Fall Guys: Ultimate Knockout (Mediatonic)
    (46, 1),  -- Cyberpunk 2077 (CD Projekt)
    (47, 33), -- DOOM Eternal (id Software)
    (48, 34), -- Cities: Skylines (Colossal Order)
    (49, 35), -- Persona 5 (Atlus)
    (50, 36); -- Subnautica (Unknown Worlds Entertainment)