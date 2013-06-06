-- MySQL dump 10.13  Distrib 5.5.24, for Win32 (x86)
--
-- Host: localhost    Database: store
-- ------------------------------------------------------
-- Server version	5.5.24

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `house`
--

DROP TABLE IF EXISTS `house`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `house` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `x` int(11) DEFAULT NULL,
  `y` int(11) DEFAULT NULL,
  `w` int(11) DEFAULT NULL,
  `h` int(11) DEFAULT NULL,
  `description` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `house`
--

LOCK TABLES `house` WRITE;
/*!40000 ALTER TABLE `house` DISABLE KEYS */;
INSERT INTO `house` VALUES (7,'HIT_Library',-132,-107,657,611,'A very impressive Library in HIT. Date back to 1950, the new China was set up.');
/*!40000 ALTER TABLE `house` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `item`
--

DROP TABLE IF EXISTS `item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `item` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `category` varchar(50) DEFAULT NULL,
  `num` int(11) DEFAULT NULL,
  `belong_to` int(11) DEFAULT NULL,
  `x` int(11) DEFAULT NULL,
  `y` int(11) DEFAULT NULL,
  `z` int(11) DEFAULT NULL,
  `description` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=171 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `item`
--

LOCK TABLES `item` WRITE;
/*!40000 ALTER TABLE `item` DISABLE KEYS */;
INSERT INTO `item` VALUES (146,'Marry a Rich Man','Romance',5,34,2,6,2,'This is a book about the growth of the novel, is about all women are concerned about the topic of women, friendship, family, work, and their relationship.'),(147,'Ancient furnace','Local',4,34,3,13,3,'A person, a village, a country, a nation, a paragraph of not evasive historical, Jia Pingwa for the first time to the nineteen sixties maximum historical movement of China'),(148,'The Warring States cyclone records','Martial arts',10,34,3,4,5,'Warring States \" whirlwind records, Japans Warring States period, in the cruel war warm blood man ,s survival way. '),(149,'The greatest hero in the world Fang Shiyu','Martial arts',8,35,0,5,5,'The greatest hero in the world \" Fang Shiyu \" for your presentation: a worldly, firm and unyielding character unruly teenager, a secret list cause suppression and kill...'),(150,'The spirit of Zhuang','Martial arts',5,35,0,10,1,'The best in all the land of cloud heights first night suddenly changes at Yunfeng and wife temperature slightly mysterious dead, only daughter cloud snow lose track, no news.'),(151,'On the other side of her','Foreign novels',3,35,1,3,6,'The story revolves around three different roles different experiences of women'),(152,'As blood flows','Foreign novels',7,35,1,15,3,'\" Any blood flowing \" content brief introduction: Edinburgh mayor s daughter was kidnapped, in pursuit of the way, two young kidnappers jumped into the sea and killed. At the same time,'),(153,'A family of scholar outlaws of the marsh','Four great classics',50,36,1,10,1,'According to 2005 statistics, China,s elderly population aged over 60 to nearly 144000000, 600000 people a year will enter the aged cavalcade, in which economic'),(154,'Journey to the West ( New Edition)','Four great classics',50,36,0,6,2,'Sun Wukong is the flower and fruit mountain natural stone monkey, learn to ever-young and seventy-two spells, row underwater borrowed cudgel...'),(155,'Robinson Crusoe','World famous',20,36,0,12,3,'Robinson was born in a middle class, his father used the contentment of the philosophy of education, to meet in the middle of a happy life. '),(156,'The classics of world literature','World famous',20,39,2,8,5,'\" Twenty Thousand Leagues Under the sea \" is a world famous science fiction masters, French writer Jules Verne ( 1828 - 1905 ) one representative, is a'),(157,'The contemporary hero','World famous',20,39,2,5,1,'Aristocratic officer Bi Qiaolin intelligent, be full of go, has not dogged determination and keen insight. He saw the reality'),(158,'The count of Monte Cristo ( volumes)','World famous',16,39,3,12,1,'\" The count of Monte Cristo ( 2011 version ) ( set of 2 volumes) \" is Alexandre Dumas,s most outstanding, most popular popular novels. The novel through the young seaman Tang'),(159,'Gulliver,s Travels','World famous',36,39,3,13,3,'\" Gulliver,s Travels ( 2011 version ) \" came out in 1726, immediately shocked the British society, also shocked the literary world.'),(160,'Oliver Twist','World famous',45,38,2,15,3,'Authors: Charles Dickens, Lu Guangwei /2009-04-01/ press: tomorrow Publishing House'),(161,'Elegance','Sociology',25,38,3,10,5,'When Yang Ke is carrying has spent 5 years time to complete the research monograph \" elegant \" Ode to the manuscript returned home, to greet him was his wife and vice principal lying naked in bed'),(162,'I am a teacher','Sociology',9,38,2,2,5,'Wei Hongyan is a district of the Chinese middle school teachers, and a Junsao, she to the student be full of love, expel a husband is the lonely.'),(163,'Yu Jie','Female Novels',8,38,2,10,5,'\"Strong woman\" Tales from the gossip magazine editor Concho,s occupation experience as the main line'),(164,'Seventh: Bloodline','Magic',39,37,3,4,2,'\" Seventh son \" Introduction: American president is a four year old boy assassinated! The whole nation into chaos and grief. Seven men hijacked to underground four thousand'),(165,'The city ,s tale 3','Magic',26,37,2,8,3,'Five million of the population of a modern city and lived more than 3000 monster?!They hide among humans, and even you plug'),(166,'Song: Historical Novels','Historical novel',33,37,2,1,4,'Song Huizong Zhao Ji, elegant warmth romantic suave nature, and ruled the country long live the responsibility has great conflicts...'),(167,'Hell Island','Science fiction',23,37,2,14,2,'This book is a panoramic view of the oceans of the world, to the big stage for the story background, military and anti-terrorism science fiction set in one of the novels. Hell island is a piece of'),(168,'Reserve officer','Military Novels',10,37,3,16,3,'\" A reserve officer \", \" a reserve officer \" with six new police cadets, Caohara, Chen Jiatong, Qiu great, Huang Lin, Lin Creek, coke Raorao wonderful stories.'),(169,'Military salute','Military Novels',10,37,3,6,5,'\" Salute \" content abstract: in the Long March, the Anti-Japanese War, liberation war and the Korean War, bloody in the flames of war years, from the battle of Xiangjiang out of the group of blood'),(170,'Every night there is a strange story','Thriller',19,37,3,9,5,'When I was in University, the dormitory to a strange classmate. When midnight time, he began to talk about ten years ago with the grandfather,s experiences. ');
/*!40000 ALTER TABLE `item` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `shelf`
--

DROP TABLE IF EXISTS `shelf`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `shelf` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `belong_to` int(11) DEFAULT NULL,
  `x` int(11) DEFAULT NULL,
  `y` int(11) DEFAULT NULL,
  `w` int(11) DEFAULT NULL,
  `h` int(11) DEFAULT NULL,
  `direc` int(11) DEFAULT NULL,
  `col` int(11) DEFAULT NULL,
  `layer` int(11) DEFAULT NULL,
  `thin` int(11) DEFAULT NULL,
  `description` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=40 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `shelf`
--

LOCK TABLES `shelf` WRITE;
/*!40000 ALTER TABLE `shelf` DISABLE KEYS */;
INSERT INTO `shelf` VALUES (34,'best_seller',7,-120,-98,73,584,2,20,10,2,'just the best.'),(35,'shelf_arts',7,87,-83,414,64,0,17,8,2,'love ars..'),(36,'shelf_comic',7,-14,51,356,81,0,16,9,2,'ACG!'),(37,'shelf_0',7,409,42,91,429,2,15,7,2,'not so hot.'),(38,'shelf_cold',7,210,172,107,304,2,15,7,2,'cold drink here.'),(39,'hot_shelf',7,11,170,102,306,2,16,8,2,'hot food.');
/*!40000 ALTER TABLE `shelf` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2012-11-16 20:26:00
