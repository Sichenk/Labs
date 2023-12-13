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
);
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

DELETE FROM Developers

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

    DELETE FROM userreviews
    WHERE `UserID` = 225

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

CREATE TABLE Graphics (
    GameID INT,
    GraphicsQuality VARCHAR(20) NOT NULL,
    FOREIGN KEY (GameID) REFERENCES Games(GameID)
);

CREATE TABLE Storage (
    GameID INT,
    DiskSpaceGB INT NOT NULL,
    FOREIGN KEY (GameID) REFERENCES Games(GameID)
);

DELETE FROM graphics

INSERT INTO Graphics (GameID, GraphicsQuality)
VALUES
    (1, 'Ultra'),
    (2, 'High'),
    (3, 'High'),
    (4, 'Epic'),
    (5, 'Low'),
    (6, 'Ultra'),
    (7, 'Epic'),
    (8, 'Medium'),
    (9, 'Ultra'),
    (10, 'Ultra'),
    (11, 'High'),
    (12, 'Low'),
    (13, 'Ultra'),
    (14, 'Epic'),
    (15, 'High'),
    (16, 'Ultra'),
    (17, 'High'),
    (18, 'Ultra'),
    (19, 'Low'),
    (20, 'Ultra'),
    (21, 'High'),
    (22, 'Epic'),
    (23, 'High'),
    (24, 'Ultra'),
    (25, 'Ultra'),
    (26, 'Medium'),
    (27, 'Low'),
    (28, 'High'),
    (29, 'Ultra'),
    (30, 'Epic'),
    (31, 'High'),
    (32, 'Ultra'),
    (33, 'Epic'),
    (34, 'Medium'),
    (35, 'Low'),
    (36, 'High'),
    (37, 'Low'),
    (38, 'High'),
    (39, 'Ultra'),
    (40, 'Ultra'),
    (41, 'High'),
    (42, 'Ultra'),
    (43, 'High'),
    (44, 'Medium'),
    (45, 'Low'),
    (46, 'Ultra'),
    (47, 'Epic'),
    (48, 'Medium'),
    (49, 'High'),
    (50, 'Low');

INSERT INTO Storage (GameID, DiskSpaceGB)
VALUES
    (1, 50),
    (2, 20),
    (3, 30),
    (4, 60),
    (5, 100),
    (6, 70),
    (7, 40),
    (8, 15),
    (9, 80),
    (10, 25),
    (11, 40),
    (12, 5),
    (13, 60),
    (14, 70),
    (15, 50),
    (16, 60),
    (17, 40),
    (18, 80),
    (19, 10),
    (20, 50),
    (21, 80),
    (22, 100),
    (23, 60),
    (24, 70),
    (25, 50),
    (26, 30),
    (27, 20),
    (28, 60),
    (29, 70),
    (30, 80),
    (31, 60),
    (32, 70),
    (33, 100),
    (34, 30),
    (35, 40),
    (36, 20),
    (37, 10),
    (38, 50),
    (39, 70),
    (40, 100),
    (41, 60),
    (42, 70),
    (43, 60),
    (44, 30),
    (45, 20),
    (46, 70),
    (47, 80),
    (48, 40),
    (49, 60),
    (50, 15);

CREATE TABLE UserReviews (
    ReviewID INT PRIMARY KEY,
    GameID INT,
    UserID INT,
    Rating INT,
    FOREIGN KEY (GameID) REFERENCES Games(GameID)
);

INSERT INTO UserReviews (ReviewID, GameID, UserID, Rating)
VALUES
    (1, 10, 201, 4),
    (2, 7, 202, 3),
    (3, 15, 203, 5),
    (4, 4, 204, 4),
    (5, 28, 205, 2),
    (6, 12, 206, 5),
    (7, 33, 207, 3),
    (8, 22, 208, 4),
    (9, 18, 209, 5),
    (10, 49, 210, 3),
    (11, 9, 211, 4),
    (12, 41, 212, 2),
    (13, 35, 213, 5),
    (14, 2, 214, 3),
    (15, 46, 215, 4),
    (16, 13, 216, 5),
    (17, 20, 217, 4),
    (18, 6, 218, 3),
    (19, 32, 219, 2),
    (20, 24, 220, 5),
    (21, 5, 221, 4),
    (22, 19, 222, 3),
    (23, 43, 223, 5),
    (24, 11, 224, 4),
    (25, 30, 225, 2),
    (26, 36, 201, 5),
    (27, 48, 202, 3),
    (28, 3, 203, 4),
    (29, 14, 204, 5),
    (30, 25, 205, 2),
    (31, 31, 206, 4),
    (32, 37, 207, 3),
    (33, 42, 208, 5),
    (34, 27, 209, 4),
    (35, 8, 210, 3),
    (36, 45, 211, 2),
    (37, 26, 212, 5),
    (38, 38, 213, 4),
    (39, 1, 214, 3),
    (40, 44, 215, 2),
    (41, 16, 216, 5),
    (42, 23, 217, 4),
    (43, 50, 218, 3),
    (44, 21, 219, 4),
    (45, 29, 220, 5),
    (46, 39, 221, 3),
    (47, 34, 222, 4),
    (48, 40, 223, 2),
    (49, 47, 224, 5),
    (50, 17, 225, 4);
